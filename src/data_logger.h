#ifndef CTRL_LOGGER_H
#define CTRL_LOGGER_H

#include "stdint.h"
#include "velocity_estimation.h"
#include "models_interface.h"
#include <linux/can.h>
#include <linux/can/raw.h>

#include "ctrl-nwk-utils.h"


void CLOG_init();
void CLOG_log_raw_packet(struct can_frame *msg, int can_network);
void CLOG_log_model_input(VES_DataInTypeDef* vest_data_in, CTRL_ModelInputTypeDef* model_input);
void CLOG_log_control_output(VES_DataOutTypeDef* vest_data_out, CTRL_ModelOutputTypeDef* model_output, uint64_t processing_time);
void CLOG_log_text(uint8_t *txt);
void CLOG_flush_file_buffers();
uint64_t CLOG_get_microseconds();

#endif