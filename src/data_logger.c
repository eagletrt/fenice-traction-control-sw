#include "data_logger.h"
#include "logger.h"
#include "stdio.h"
#include "time.h"


FILE *f_raw_data, *f_frames, *f_txt;


uint64_t CLOG_get_microseconds() {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return (t.tv_sec*1e6 + (t.tv_nsec/1000.0f));
}

void CLOG_init() {
    f_raw_data = fopen("raw_data.csv", "a");
    if (f_raw_data == NULL)
        LOG_write(LOGLEVEL_ERR, "[DATA] Cannot open raw_data file in append mode");
    
    f_frames = fopen("frames_log.csv", "a");
    if (f_frames == NULL)
        LOG_write(LOGLEVEL_ERR, "[DATA] Cannot open frames_log file in append mode");
    fprintf(f_frames, "tstamp_us,param_id,param_val,crc16");

    f_txt = fopen("messages.csv", "a");
    if (f_txt == NULL)
        LOG_write(LOGLEVEL_ERR, "[DATA] Cannot open messages_log file in append mode");
    fprintf(f_txt, "Started logging at timestamp: %llu\n", CLOG_get_microseconds());

    CLOG_flush_file_buffers();
}

/**
 * @brief     Log the contents of the raw buffer containing a packet
 * @note      The newline character is printed at the beginning to avoid problems
 *            if a read is interrupted at shutdown
 */
void CLOG_log_raw_packet(uint8_t *buf, uint8_t buf_len) {
    if (f_raw_data == NULL)
        return;
    
    fprintf(f_raw_data, "\n%llu", CLOG_get_microseconds());

    for (uint8_t i = 0; i < buf_len; i++)
        fprintf(f_raw_data, ",%03d", buf[i]);
}

void CLOG_log_ctrl_frame(CTRL_PayloadTypeDef *frame) {
    if (f_frames == NULL)
        return;

    fprintf(
        f_frames, "\n%llu,%d,%.3f,%d",
        CLOG_get_microseconds(), frame->ParamID, frame->ParamVal, frame->CRC16
    );
}

void CLOG_log_text(uint8_t *txt) {
    if (f_txt == NULL)
        return;
    
    fprintf(f_txt, "%llu - %s\n", CLOG_get_microseconds(), txt);
}

void CLOG_flush_file_buffers() {
    fflush(f_raw_data);
    fflush(f_frames);
    fflush(f_txt);
}