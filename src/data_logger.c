#include "data_logger.h"
#include "logger.h"
#include "stdio.h"
#include "time.h"
#include "inttypes.h"


FILE *f_raw_data, *f_txt, *f_in, *f_out;


uint64_t CLOG_get_microseconds() {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return (t.tv_sec*1e6 + (t.tv_nsec/1000.0f));
}

void CLOG_init() {
    f_raw_data = fopen("raw_data.csv", "a"); // NOTE: formato di f_raw_data (10.0000) primary FFF#01FF00 
    if (f_raw_data == NULL)
        LOG_write(LOGLEVEL_ERR, "[DATA] Cannot open raw_data file in append mode");

    f_txt = fopen("messages.csv", "a");
    if (f_txt == NULL)
        LOG_write(LOGLEVEL_ERR, "[DATA] Cannot open messages_log file in append mode");
    fprintf(f_txt, "Started logging at timestamp: %"PRIu64"\n", CLOG_get_microseconds());

    CLOG_flush_file_buffers();

    f_in = fopen("model_input.csv", "a");
    if (f_in == NULL)
        LOG_write(LOGLEVEL_ERR, "[DATA] Cannot open model_input file in append mode");
    fprintf(f_in, "tstamp_us,omega_rl,omega_fr,omega_rr,omega_fl,torque_map,map_sc,map_tv,delta,brake,dreq,omega,ax_g");
    anziche omega e ax_g
    gyro_z, accel_x

    f_out = fopen("control_output.csv", "a");
    if (f_in == NULL)
        LOG_write(LOGLEVEL_ERR, "[DATA] Cannot open control_output file in append mode");
    fprintf(f_in, "tstamp_us,processing_time,estimated_velocity,tmax_r,tmax_l,torque_r,torque_l");
}

/**
 * @brief     Log the contents of the raw buffer containing a packet
 * @note      The newline character is printed at the beginning to avoid problems
 *            if a read is interrupted at shutdown
 */
void CLOG_log_raw_packet(struct can_frame &msg, int can_network) {
    if (f_raw_data == NULL)
        return;
    
    static char buff[22];
    static char id[3];
    static char val[2];

    sprintf(id, "%03d", msg.can_id)
    sprintf(buff, "%s#", id);

    for (int i = 0; i < msg.can_dlc; i++)
    {
        sprintf(val, "%02d", msg.data[i])
        strcat(buff, val);
    }

    fprintf(f_raw_data, "\n(%"PRIu64 ") ", CLOG_get_microseconds(),);
    if (can_network == 0)
    {
        fprintf(f_raw_data, "primary ");
    } else if (can_network == 1)
    {
        fprintf(f_raw_data, "secondary ");
    }
    
    fprintf(f_raw_data, "%s", buff);
}

void CLOG_log_model_input(VES_DataInTypeDef* vest_data_in, VES_DataOutTypeDef* vest_data_out) {
    if (f_frames == NULL)
        return;

    fprintf(
        f_frames, "\n%"PRIu64",%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
        CLOG_get_microseconds(), vest_data_in->omega_rl, vest_data_in->omega_fr, vest_data_in->omega_rr, vest_data_in->omega_fl, vest_data_in->torque_map, model_input->map_sc, model_input->map_tv, model_input->delta, model_input->brake, model_input->dreq, model_input->omega, vest_data_in->ax_g
    );
}

void CLOG_log_control_output(VES_DataOutTypeDef* vest_data_out, CTRL_ModelOutputTypeDef* model_output, uint64_t processing_time) {
    if (f_frames == NULL)
        return;

    fprintf(
        f_frames, "\n%"PRIu64",%"PRIu64",%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
        CLOG_get_microseconds(), processing_time, vest_data_out->bar, vest_data_out->tmax_r, vest_data_out->tmax_l, model_output->tm_rr, model_output->tm_rl, 
    );
}

void CLOG_log_text(uint8_t *txt) {
    if (f_txt == NULL)
        return;
    
    fprintf(f_txt, "%"PRIu64" - %s\n", CLOG_get_microseconds(), txt);
}

void CLOG_flush_file_buffers() {
    fflush(f_raw_data);
    fflush(f_txt);
    fflush(f_in);
    fflush(f_out);
}