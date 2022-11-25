#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "time.h"
#include "models_interface.h"
#include "uart_interface.h"
#include "ctrl-nwk-utils.h"
#include "velocity_estimation.h"
#include "logger.h"
#include "data_logger.h"


VES_DataInTypeDef vest_data_in = { 0U };
VES_DataOutTypeDef vest_data_out = { 0U };
CTRL_ModelInputTypeDef model_input = { 0U };
CTRL_ModelOutputTypeDef model_output = { 0U };

const uint8_t UART_MAX_BUF_LEN = 127;
bool is_response_timer_elapsed = false;


void _set_model_param(uint8_t id, float val) {
    if (id == CTRL_PARAMID_CSW) {
        CTRL_change_mode((CTRL_ModeTypeDef)val);
        return;
    }

    switch (id) {
        case CTRL_PARAMID_DREQ:
            model_input.dreq = val;
            break;
        case CTRL_PARAMID_STEER_ANG:
            model_input.delta = val;
            break;
        case CTRL_PARAMID_YAW:
            model_input.omega = val;
            break;
        case CTRL_PARAMID_O_RR:
            vest_data_in.omega_rr = val;
            model_input.omega_rr = val;
            break;
        case CTRL_PARAMID_O_RL:
            vest_data_in.omega_rl = val;
            model_input.omega_rl = val;
            break;
        case CTRL_PARAMID_O_FR:
            vest_data_in.omega_fr = val;
            break;
        case CTRL_PARAMID_O_FL:
            vest_data_in.omega_fl = val;
            break;
        case CTRL_PARAMID_AX_G:
            vest_data_in.ax_g = val;
            break;
        case CTRL_PARAMID_BRAKE:
            model_input.brake = val;
            break;
        default:
            LOG_write(LOGLEVEL_WARN, "[MAIN] Unknown param id: %d", id);
            break;
    }
}

void _update_models() {
    vest_data_in.torque_map = 6.0f;
    VES_step_model(&vest_data_in, &vest_data_out);

    model_input.map_sc = 0.3f;
    model_input.map_tv = 1.0f;
    model_input.bar = vest_data_out.bar;
    model_input.tmax_rl = vest_data_out.tmax_rl;
    model_input.tmax_rr = vest_data_out.tmax_rr;

    CTRL_step_model(&model_input, &model_output);
}

void _send_frame(CTRL_PayloadTypeDef *frame) {
    uint8_t buf[UART_MAX_BUF_LEN];
    uint8_t pkt_len = CTRL_compose_frame(frame, buf);
    CLOG_log_raw_packet(buf, pkt_len);
    CLOG_log_ctrl_frame(frame);
    UART_send_packet_sync(buf, pkt_len);
}

void _send_torque() {
    CTRL_PayloadTypeDef frame;
    frame.CRC16 = 0x0;

    frame.ParamID = CTRL_PARAMID_TMLL;
    frame.ParamVal = model_output.tm_rl;
    _send_frame(&frame);

    frame.ParamID = CTRL_PARAMID_TMRR;
    frame.ParamVal = model_output.tm_rr;
    _send_frame(&frame);
}

void signal_handler(int signum) {
    is_response_timer_elapsed = true;
}

int main() {
    LOG_init(LOGLEVEL_DEBUG, false, true, false);
    LOG_write(LOGLEVEL_INFO, "[MAIN] Initialized textual logger");

    CLOG_init();
    LOG_write(LOGLEVEL_INFO, "[MAIN] Initialized raw-data logger");

    UART_init();
    LOG_write(LOGLEVEL_INFO, "[MAIN] Initialized UART interface");
    
    VES_init();
    LOG_write(LOGLEVEL_INFO, "[MAIN] Initialized Velocity-Estimation interface");
    
    CTRL_change_mode(CTRL_Mode_None);
    LOG_write(LOGLEVEL_INFO, "[MAIN] Initialized Traction-Control interface");

    signal(SIGALRM, signal_handler);
    LOG_write(LOGLEVEL_INFO, "[MAIN] Initialized signal handler");

    struct itimerval timer_info;
    timer_info.it_interval.tv_sec = timer_info.it_value.tv_sec = 0;
    timer_info.it_interval.tv_usec = timer_info.it_value.tv_usec = 50000;
    
    if (setitimer(ITIMER_REAL, &timer_info, NULL) == 0) {
        LOG_write(LOGLEVEL_INFO, "[MAIN] Initialized SIGALRM timer");
    } else {
        LOG_write(LOGLEVEL_ERR, "[MAIN] Timer set failed");
    }

    LOG_write(LOGLEVEL_INFO, "[MAIN] Program is ready! Beginning main loop.");
    fflush(stdout);

    while (1) {
        CTRL_PayloadTypeDef ctrl_frame;
        uint8_t UART_rx_buf[UART_MAX_BUF_LEN];
        uint8_t pkt_len;
        
        pkt_len = UART_get_packet_sync(UART_rx_buf, UART_MAX_BUF_LEN);

        if (pkt_len != 0) {
            CLOG_log_raw_packet(UART_rx_buf, pkt_len);
            CTRL_read_frame(UART_rx_buf, pkt_len, &ctrl_frame);
            CLOG_log_ctrl_frame(&ctrl_frame);

            _set_model_param(ctrl_frame.ParamID, ctrl_frame.ParamVal);
        }

        if (is_response_timer_elapsed) {
            _update_models();
            _send_torque();
            CLOG_flush_file_buffers();
            is_response_timer_elapsed = false;
        }
    }
}

void _LOG_write_raw(char *txt) {
    printf("%llu - %s\n", CLOG_get_microseconds(), txt);
    CLOG_log_text((uint8_t*)txt);
}