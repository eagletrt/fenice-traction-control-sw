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

#include "can/lib/primary/c/ids.h"
#include "can/lib/secondary/c/ids.h"

#define primary_NETWORK_IMPLEMENTATION
#define secondary_NETWORK_IMPLEMENTATION
#include "can/lib/primary/c/network.h"
#include "can/lib/secondary/c/network.h"

typedef struct thread_data_t {
  can_t *can;
  int can_id;
} thread_data_t;

thread_data_t thread_data_1, thread_data_2;

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

void _set_model_param(uint8_t id, float val) {
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
  case CTRL_PARAMID_PW_MAP:
    vest_data_in.torque_map = val;
    break;
  case CTRL_PARAMID_SC_MAP:
    model_input.map_sc = val;
    break;
  case CTRL_PARAMID_TV_MAP:
    model_input.map_tv = val;
    break;
  default:
    LOG_write(LOGLEVEL_WARN, "[MAIN] Unknown param id: %d", id);
    break;
  }
}

void _update_models() {
  VES_step_model(&vest_data_in, &vest_data_out);

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

void _send_vest_out() {
  CTRL_PayloadTypeDef frame;
  frame.CRC16 = 0x0;

  // NOTE: devo fare la serialize dei dati

  frame.ParamID = CTRL_PARAMID_TLMAX;
  frame.ParamVal = vest_data_out.tmax_rl;
  _send_frame(&frame);
  // can_send(int id, char *data, int len, struct can_t *can);

  frame.ParamID = CTRL_PARAMID_TRMAX;
  frame.ParamVal = vest_data_out.tmax_rr;
  _send_frame(&frame);

  frame.ParamID = CTRL_PARAMID_UBAR;
  frame.ParamVal = vest_data_out.bar;
  _send_frame(&frame);
}

void _send_torque() {
  CTRL_PayloadTypeDef frame;
  frame.CRC16 = 0x0;

  frame.ParamID = CTRL_PARAMID_TLEFT;
  frame.ParamVal = model_output.tm_rl;
  _send_frame(&frame);

  frame.ParamID = CTRL_PARAMID_TRIGHT;
  frame.ParamVal = model_output.tm_rr;
  _send_frame(&frame);
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

  can_t can_primary;
  can_init("can1", &can_primary);
  can_t can_secondary;
  can_init("can0", &can_secondary);

  thread_data_1.can = can_primary;
  thread_data_1.can_id = NETWORK_PRIMARY;
  thread_data_2.can = can_secondary;
  thread_data_2.can_id = NETWORK_SECONDARY;
  pthread_t _thread_id_0;
  pthread_t _thread_id_1;
  pthread_create(&_thread_id_1, NULL, canread, &thread_data_1);
  pthread_create(&_thread_id_1, NULL, canread, &thread_data_1);

  while (1) {
    CTRL_PayloadTypeDef ctrl_frame;
    uint8_t UART_rx_buf[UART_MAX_BUF_LEN];
    uint8_t pkt_len;
    queue_element_t q_element;

    pthread_mutex_lock(&mtx);
    if(queue_first(&queue, &q_element)){
      dequeue(&queue);

    } else {

    }
    pthread_mutex_unlock(&mtx);

    if (q_element.can_network == NETWORK_PRIMARY) {

      switch (q_element.frame.can_id) {

      case primary_ID_INV_L_RESPONSE: {
        primary_message_INV_L_RESPONSE canlib_response;
        primary_deserialize_INV_L_RESPONSE(&canlib_response,
                                           &q_element.frame.data);
        inverter_message_INV_RESPONSE inv_response =
            *(inverter_message_INV_RESPONSE *)(&canlib_response);
        static inverter_data_t inverters_data[2];

        if (q_element.frame.data[0] == INV_REG_SPEED) {
          parse_inverter(&inv_response, INV_IDX_LEFT, inverters_data);
          vest_data_in.omega_rl = inverters_data[0].inverter_speed.speed * 4.5f;
          model_input.omega_rl = inverters_data[0].inverter_speed.speed * 4.5f;
        }
      } break;

      case primary_ID_INV_R_RESPONSE: {

        primary_message_INV_R_RESPONSE canlib_response;
        primary_deserialize_INV_R_RESPONSE(&canlib_response,
                                           &q_element.frame.data);
        inverter_message_INV_RESPONSE inv_response =
            *(inverter_message_INV_RESPONSE *)(&canlib_response);
        static inverter_data_t inverters_data[2];

        if (q_element.frame.data[0] == INV_REG_SPEED) {
          parse_inverter(&inv_response, INV_IDX_RIGHT, inverters_data);
          vest_data_in.omega_rr = inverters_data[1].inverter_speed.speed * 4.5f;
          model_input.omega_rr = inverters_data[1].inverter_speed.speed * 4.5f;
        }
      } break;

      case primary_ID_SPEED: {

        primary_message_SPEED message;
        primary_message_SPEED_conversion conversion;
        // deserialize
        primary_deserialize_SPEED(&message, &q_element.frame.data);
        // raw to conversion
        primary_raw_to_conversion_SPEED(&conversion, message.encoder_r,
                                        message.encoder_l, message.inverter_r,
                                        message.inverter_l);

        vest_data_in.omega_fr = conversion.encoder_r;
        vest_data_in.omega_fl = conversion.encoder_l;
      } break;

      case primary_ID_STEER_STATUS: {

        primary_message_STEER_STATUS message;
        primary_message_STEER_STATUS_conversion conversion;
        // deserialize
        primary_deserialize_STEER_STATUS(&message, &q_element.frame.data);
        // raw to conversion
        primary_raw_to_conversion_struct_STEER_STATUS(&conversion, &message);

        vest_data_in.torque_map = conversion.map_pw;
        model_input.map_sc = conversion.map_sc;
        model_input.map_tv = conversion.map_tv;
      } break;

      default:
        continue;
      }
    } else if (q_element.can_network == NETWORK_SECONDARY) {

      switch (q_element.frame.can_id) {
      case secondary_ID_STEERING_ANGLE: {

        secondary_message_STEERING_ANGLE message;
        // deserialize
        secondary_deserialize_STEERING_ANGLE(&message, &q_element.frame.data);

        model_input.delta = message.angle;
      } break;

      case secondary_ID_PEDALS_OUTPUT: {

        secondary_message_PEDALS_OUTPUT message;
        secondary_message_PEDALS_OUTPUT_conversion conversion;
        // deserialize
        secondary_deserialize_PEDALS_OUTPUT(&message, &q_element.frame.data);
        // raw to conversion
        secondary_raw_to_conversion_struct_PEDALS_OUTPUT(&conversion, &message);

        model_input.brake = conversion.bse_front / 100.0f;
        model_input.dreq = conversion.apps / 100.0f;
      } break;
      case secondary_ID_IMU_ANGULAR_RATE: {

        secondary_message_IMU_ANGULAR_RATE message;
        secondary_message_IMU_ANGULAR_RATE_conversion conversion;
        // deserialize
        secondary_deserialize_IMU_ANGULAR_RATE(&message, &q_element.frame.data);
        // raw to conversion
        secondary_raw_to_conversion_struct_IMU_ANGULAR_RATE(&conversion,
                                                            &message);

        model_input.omega = conversion.ang_rate_z * 0.017453f;
      } break;
      case secondary_ID_IMU_ACCELERATION: {

        secondary_message_IMU_ACCELERATION message;
        secondary_message_IMU_ACCELERATION_conversion conversion;
        // deserialize
        secondary_deserialize_IMU_ACCELERATION(&message, &q_element.frame.data);
        // raw to conversion
        secondary_raw_to_conversion_struct_IMU_ACCELERATION(&conversion,
                                                            &message);

        vest_data_in.ax_g = conversion.accel_x * 9.81f;
      } break;
      default:
        continue;
      }
    }

    pkt_len = UART_get_packet_sync(UART_rx_buf, UART_MAX_BUF_LEN);

    if (pkt_len != 0) {
      CLOG_log_raw_packet(UART_rx_buf,
                          pkt_len); // NOTE: riaddattare la funzione per accettare frame CAN

      // (timestamp) - idcan - id#data
      // (10.0000) primary FFF#01FF00           
      CTRL_read_frame(UART_rx_buf, pkt_len, &ctrl_frame);
      CLOG_log_ctrl_frame(&ctrl_frame);
    }

    if (is_response_timer_elapsed) {
      // timer
      _update_models();
      // salvarmi il timer
      _send_vest_out(); // NOTE: inviare questi messaggi in CAN
      _send_torque();   // NOTE: inviare questi messaggi in CAN
      CLOG_flush_file_buffers();
      is_response_timer_elapsed = false;
    }
  }
}

void _LOG_write_raw(char *txt) {
  printf("%llu - %s\n", CLOG_get_microseconds(), txt);
  CLOG_log_text((uint8_t *)txt);
}