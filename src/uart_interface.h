#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>

bool UART_init();
int UART_get_packet_sync(uint8_t*, uint8_t);
int UART_send_packet_sync(uint8_t*, uint8_t);

#endif