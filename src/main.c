#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "models_interface.h"
#include "uart_interface.h"
#include "ctrl-nwk-utils.h"
#include "velocity_estimation.h"
#include "logger.h"


VES_DataInTypeDef vest_data_in = {};
VES_DataOutTypeDef vest_data_out = {};
CTRL_ModelInputTypeDef model_input = {};
CTRL_ModelOutputTypeDef model_output = {};

const uint8_t UART_MAX_BUF_LEN = 30;


void _update_model(float dreq) {
    model_input.dreq = dreq;
    // printf("Model input set at %.2f\n", model_input.dreq);
    CTRL_step_model(&model_input, &model_output);
    // printf("mdoel returned: %.2f %.2f\n", model_output.rtY_Tm_rl, model_output.rtY_Tm_rr);
}

void _send_frame(CTRL_PayloadTypeDef frame) {
    uint8_t buf[UART_MAX_BUF_LEN];
    uint8_t pkt_len = CTRL_compose_frame(&frame, buf);
    UART_send_packet_sync(buf, pkt_len);
}

void _send_torque(float tl, float tr) {
    CTRL_PayloadTypeDef frame;
    frame.CRC = 0x0;

    frame.ParamID = CTRL_PARAMID_TMLL;
    frame.ParamVal = tl;
    _send_frame(frame);

    frame.ParamID = CTRL_PARAMID_TMRR;
    frame.ParamVal = tr;
    _send_frame(frame);
}

void signal_handler(int signum) {
    printf("Sending torque: %.2f, %.2f\n", model_output.tm_rl, model_output.tm_rr);
    _send_torque(model_output.tm_rl, model_output.tm_rr);
}

int main() {
    UART_init();
    CTRL_change_mode(CTRL_NONE);

    signal(SIGALRM, signal_handler);
    struct itimerval timer_info;
    timer_info.it_interval.tv_sec = timer_info.it_value.tv_sec = 0;
    timer_info.it_interval.tv_usec = timer_info.it_value.tv_usec = 50000;
    
    if (setitimer(ITIMER_REAL, &timer_info, NULL) == 0)
        printf("Timer set OK\n");
    else
        printf("Timer set failed\n");

    while (1) {
        CTRL_PayloadTypeDef ctrl_frame;
        uint8_t UART_rx_buf[UART_MAX_BUF_LEN];
        uint8_t pkt_len;
        
        pkt_len = UART_get_packet_sync(UART_rx_buf, UART_MAX_BUF_LEN);

        if (pkt_len == 0)
            continue;

        CTRL_read_frame(UART_rx_buf, pkt_len, &ctrl_frame);

        // printf("\nRead frame:\n");
        // printf("     ParamID: 0x%02x\n", ctrl_frame.ParamID);
        // printf("    ParamVal: %.2f\n", ctrl_frame.ParamVal);
        // printf("       CRC16: 0x%04x\n", ctrl_frame.CRC);

        if (ctrl_frame.ParamID != CTRL_PARAMID_DREQ) {
            printf("Parameter not yet supported\n");
            continue;
        }

        _update_model(ctrl_frame.ParamVal);
    }
}

void _LOG_write_raw(char *txt) {
    printf(txt);
}