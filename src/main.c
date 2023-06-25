#include "can.h"
#include "ctrl-nwk-utils.h"
#include "data_logger.h"
#include "invlib/inverter.h"
#include "logger.h"
#include "models_interface.h"
#include "queue.h"
#include "time.h"
#include "uart_interface.h"
#include "velocity_estimation.h"
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "can/lib/primary/primary_network.h"
#include "can/lib/secondary/secondary_network.h"

#define primary_NETWORK_IMPLEMENTATION
#define secondary_NETWORK_IMPLEMENTATION

typedef struct thread_data_t {
  can_t *can;
  int can_id;
} thread_data_t;

thread_data_t thread_data_1, thread_data_0;

const int NETWORK_PRIMARY = 0;
const int NETWORK_SECONDARY = 1;

VES_DataInTypeDef vest_data_in = {0U};
VES_DataOutTypeDef vest_data_out = {0U};
CTRL_ModelInputTypeDef model_input = {0U};
CTRL_ModelOutputTypeDef model_output = {0U};

const uint8_t UART_MAX_BUF_LEN = 127;
bool is_response_timer_elapsed = false;

queue_t queue;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

can_t can_primary;
can_t can_secondary;

void _update_models() {
  VES_step_model(&vest_data_in, &vest_data_out);

  model_input.bar = vest_data_out.bar;
  model_input.tmax_rl = vest_data_out.tmax_rl;
  model_input.tmax_rr = vest_data_out.tmax_rr;

  CTRL_step_model(&model_input, &model_output);
}

void _send_vest_out() {

  primary_control_output_t raw;
  uint8_t data[8];
  primary_control_output_conversion_to_raw(&raw, vest_data_out.bar, vest_data_out.tmax_rr, vest_data_out.tmax_rl, model_output.tm_rl, model_output.tm_rr);
  primary_control_output_pack(data, &raw, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE);

  // can_send(int id, char *data, int len, struct can_t *can);
  can_send(PRIMARY_CONTROL_OUTPUT_FRAME_ID, (char *)data, PRIMARY_CONTROL_OUTPUT_BYTE_SIZE, &can_primary);
}

void _send_map(){
  secondary_control_state_t raw;
  uint8_t data[8];
  secondary_control_state_conversion_to_raw(&raw, vest_data_in.torque_map, model_input.map_sc, model_input.map_tv);

  secondary_control_state_pack(data, &raw, SECONDARY_CONTROL_STATE_BYTE_SIZE);

  can_send(SECONDARY_CONTROL_STATE_FRAME_ID, (char *)data, SECONDARY_CONTROL_STATE_BYTE_SIZE, &can_secondary);
}

void signal_handler(int signum) { is_response_timer_elapsed = true; }

void canread(thread_data_t *thread_data) {
  queue_element_t msg;
  while (1) {
    can_receive(&msg.frame, thread_data->can);
    msg.can_network = thread_data->can_id;
    msg.timestamp = CLOG_get_microseconds();

    pthread_mutex_lock(&mtx);
    enqueue(msg, &queue);
    pthread_mutex_unlock(&mtx);
  }
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

  CTRL_change_mode(CTRL_Mode_Complete);
  LOG_write(LOGLEVEL_INFO, "[MAIN] Initialized Traction-Control interface");

  signal(SIGALRM, signal_handler);
  LOG_write(LOGLEVEL_INFO, "[MAIN] Initialized signal handler");

  queue_init(&queue);

  struct itimerval timer_info;
  timer_info.it_interval.tv_sec = timer_info.it_value.tv_sec = 0;
  timer_info.it_interval.tv_usec = timer_info.it_value.tv_usec = 5000;

  if (setitimer(ITIMER_REAL, &timer_info, NULL) == 0) {
    LOG_write(LOGLEVEL_INFO, "[MAIN] Initialized SIGALRM timer");
  } else {
    LOG_write(LOGLEVEL_ERR, "[MAIN] Timer set failed");
  }

  LOG_write(LOGLEVEL_INFO, "[MAIN] Program is ready! Beginning main loop.");
  fflush(stdout);

  can_init("can1", &can_primary);
  can_init("can0", &can_secondary);

  if(can_open_socket(&can_primary) < 0){
    LOG_write(LOGLEVEL_ERR, "Error opening can primary");
    LOG_write(LOGLEVEL_ERR, can_primary.device);
    return -1;
  }
  if(can_open_socket(&can_secondary) < 0){
    LOG_write(LOGLEVEL_ERR, "Error opening can secondary");
    LOG_write(LOGLEVEL_ERR, can_secondary.device);
    return -1;
  }

  thread_data_0.can = &can_primary;
  thread_data_0.can_id = NETWORK_PRIMARY;
  thread_data_1.can = &can_secondary;
  thread_data_1.can_id = NETWORK_SECONDARY;
  pthread_t _thread_id_0;
  pthread_t _thread_id_1;
  pthread_create(&_thread_id_0, NULL, canread, &thread_data_0);
  pthread_create(&_thread_id_1, NULL, canread, &thread_data_1);

  while (1) {
    CTRL_PayloadTypeDef ctrl_frame;
    uint8_t UART_rx_buf[UART_MAX_BUF_LEN];
    uint8_t pkt_len;
    queue_element_t q_element;
    uint16_t readMessage = 0; // 0 = no message, 1 = message read

    pthread_mutex_lock(&mtx);
    if(queue_first(&queue, &q_element)){
      CLOG_log_raw_packet(&q_element.frame, q_element.can_network);
      dequeue(&queue);
      readMessage = 1;
    } else {
      readMessage = 0;
    }
    pthread_mutex_unlock(&mtx);

    if (q_element.can_network == NETWORK_PRIMARY) {

      switch (q_element.frame.can_id) {

      case PRIMARY_INV_L_RESPONSE_FRAME_ID: {
        primary_inv_l_response_t canlib_response;
        primary_inv_l_response_unpack(&canlib_response,
                                      &q_element.frame.data,
                                      PRIMARY_INV_L_RESPONSE_BYTE_SIZE);
        inverter_message_INV_RESPONSE inv_response =
            *(inverter_message_INV_RESPONSE *)(&canlib_response);
        static inverter_data_t inverters_data[2];

        if (q_element.frame.data[0] == INV_REG_SPEED) {
          parse_inverter(&inv_response, INV_IDX_LEFT, inverters_data);
          vest_data_in.omega_rl = inverters_data[0].inverter_speed.speed * 4.5f;
          model_input.omega_rl = inverters_data[0].inverter_speed.speed * 4.5f;
        }
      } break;

      case PRIMARY_INV_R_RESPONSE_FRAME_ID: {

        primary_inv_r_response_t canlib_response;
        primary_inv_r_response_unpack(&canlib_response,
                                      &q_element.frame.data,
                                      PRIMARY_INV_R_RESPONSE_BYTE_SIZE);
        inverter_message_INV_RESPONSE inv_response =
            *(inverter_message_INV_RESPONSE *)(&canlib_response);
        static inverter_data_t inverters_data[2];

        if (q_element.frame.data[0] == INV_REG_SPEED) {
          parse_inverter(&inv_response, INV_IDX_RIGHT, inverters_data);
          vest_data_in.omega_rr = inverters_data[1].inverter_speed.speed * 4.5f;
          model_input.omega_rr = inverters_data[1].inverter_speed.speed * 4.5f;
        }
      } break;

      case PRIMARY_SPEED_FRAME_ID: {

        primary_speed_t message;
        primary_speed_converted_t conversion;
        // deserialize
        primary_speed_unpack(&message, &q_element.frame.data, PRIMARY_SPEED_BYTE_SIZE);
        // raw to conversion
        primary_speed_raw_to_conversion(&conversion, message.encoder_r,
                                        message.encoder_l, message.inverter_r,
                                        message.inverter_l);

        vest_data_in.omega_fr = conversion.encoder_r;
        vest_data_in.omega_fl = conversion.encoder_l;
      } break;

      case PRIMARY_STEER_STATUS_FRAME_ID: {

        primary_steer_status_t message;
        primary_steer_status_converted_t conversion;
        // deserialize
        primary_steer_status_unpack(&message, &q_element.frame.data, PRIMARY_STEER_STATUS_BYTE_SIZE);
        // raw to conversion
        primary_steer_status_raw_to_conversion_struct(&conversion, &message);

        vest_data_in.torque_map = conversion.map_pw;
        model_input.map_sc = conversion.map_sc;
        model_input.map_tv = conversion.map_tv;
      } break;

      default:
        continue;
      }
    } else if (q_element.can_network == NETWORK_SECONDARY) {

      switch (q_element.frame.can_id) {
      case SECONDARY_STEERING_ANGLE_FRAME_ID: {

        secondary_steering_angle_t message;
        // deserialize
        secondary_steering_angle_unpack(&message, &q_element.frame.data, SECONDARY_STEERING_ANGLE_BYTE_SIZE);

        model_input.delta = message.angle;
      } break;

      case SECONDARY_PEDALS_OUTPUT_FRAME_ID: {

        secondary_pedals_output_t message;
        secondary_pedals_output_converted_t conversion;
        // deserialize
        secondary_pedals_output_unpack(&message, &q_element.frame.data, SECONDARY_PEDALS_OUTPUT_BYTE_SIZE);
        // raw to conversion
        secondary_pedals_output_raw_to_conversion_struct(&conversion, &message);

        model_input.brake = conversion.bse_front / 100.0f;
        model_input.dreq = conversion.apps / 100.0f;
      } break;
      case SECONDARY_IMU_ANGULAR_RATE_FRAME_ID: {

        secondary_imu_angular_rate_t message;
        secondary_imu_angular_rate_converted_t conversion;
        // deserialize
        secondary_imu_angular_rate_unpack(&message, &q_element.frame.data, SECONDARY_IMU_ANGULAR_RATE_BYTE_SIZE);
        // raw to conversion
        secondary_imu_angular_rate_raw_to_conversion_struct(&conversion,
                                                            &message);

        model_input.omega = conversion.ang_rate_z * 0.017453f;
      } break;
      case SECONDARY_IMU_ACCELERATION_FRAME_ID: {

        secondary_imu_acceleration_t message;
        secondary_imu_acceleration_converted_t conversion;
        // deserialize
        secondary_imu_acceleration_unpack(&message, &q_element.frame.data, SECONDARY_IMU_ACCELERATION_BYTE_SIZE);
        // raw to conversion
        secondary_imu_acceleration_raw_to_conversion_struct(&conversion,
                                                            &message);

        vest_data_in.ax_g = conversion.accel_x * 9.81f;
      } break;
      default:
        continue;
      }
    }

    if (is_response_timer_elapsed) {
      uint64_t processing_time = CLOG_get_microseconds();
      _update_models();
      processing_time = CLOG_get_microseconds() - processing_time;
      _send_vest_out();
      _send_map();
      CLOG_log_model_input(&vest_data_in, &model_input);
      CLOG_log_control_output(&vest_data_out, &model_output, processing_time);
      CLOG_flush_file_buffers();
      is_response_timer_elapsed = false;
    }
  }
}

void _LOG_write_raw(char *txt) {
  printf("%" PRIu64 " - %s\n", CLOG_get_microseconds(), txt);
  CLOG_log_text((uint8_t *)txt);
}