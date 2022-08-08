#ifndef CTRL_LOGGER_H
#define CTRL_LOGGER_H

#include "ctrl-nwk-utils.h"


void CLOG_init();
void CLOG_log_raw_packet(uint8_t *buf, uint8_t buf_len);
void CLOG_log_ctrl_frame(CTRL_PayloadTypeDef *frame);
void CLOG_log_text(uint8_t *txt);

#endif