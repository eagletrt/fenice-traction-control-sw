#include <stdio.h>
#include <unistd.h>
#include "models_interface.h"
#include "uart_interface.h"
#include "ctrl-nwk-utils.h"


CTRL_ModelInputTypeDef model_input = {};
CTRL_ModelOutputTypeDef model_output = {};

const uint8_t UART_MAX_BUF_LEN = 30;


void update_model(float dreq) {
    model_input.rtU_Driver_req = dreq;
    model_output = step_model(model_input);
}

void send_frame(CTRL_PayloadTypeDef frame) {
    uint8_t buf[UART_MAX_BUF_LEN];
    uint8_t pkt_len = CTRL_compose_frame(&frame, buf);
    UART_send_packet_sync(buf, pkt_len);
}

void send_torque(float tl, float tr) {
    CTRL_PayloadTypeDef frame;
    frame.ParamID = CTRL_PARAMID_TMLL;
    frame.CRC = 0x0;

    frame.ParamVal = tl;
    send_frame(frame);
    frame.ParamVal = tr;
    send_frame(frame);
}

int main() {
    UART_init();
    change_ctrl_mode(CTRL_NONE);

    while (1) {
        CTRL_PayloadTypeDef ctrl_frame;
        uint8_t UART_rx_buf[UART_MAX_BUF_LEN];
        uint8_t pkt_len;
        
        pkt_len = UART_get_packet_sync(UART_rx_buf, UART_MAX_BUF_LEN);

        if (pkt_len == 0)
            continue;

        CTRL_read_frame(UART_rx_buf, pkt_len, &ctrl_frame);

        printf("\nRead frame:\n");
        printf("     ParamID: 0x%02x\n", ctrl_frame.ParamID);
        printf("    ParamVal: %.2f\n", ctrl_frame.ParamVal);
        printf("       CRC16: 0x%04x\n", ctrl_frame.CRC);

        if (ctrl_frame.ParamID != CTRL_PARAMID_DREQ) {
            printf("Parameter not yet supported\n");
            continue;
        }

        update_model(ctrl_frame.ParamVal);
        send_torque(model_output.rtY_Tm_rl, model_output.rtY_Tm_rr);
    }
}