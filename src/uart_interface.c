#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "uart_interface.h"
#include "ctrl-nwk-utils.h"


int UART_fd = -1;
// char *uart_dev = "/dev/ttyAMA0";
char *uart_dev = "/dev/ttyUSB0";


/**
 * @brief Initialize the UART interface
 */
bool UART_init() {
	UART_fd = open(uart_dev, O_RDWR | O_NOCTTY | O_NDELAY);

	if (UART_fd == -1) {
		printf("Error opening serial port: %s\n", uart_dev);
        return false;
    }

	struct termios options;
	tcgetattr(UART_fd, &options);
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
	tcsetattr(UART_fd, TCSANOW, &options);

    return true;
}

/**
 * @brief Read from the UART until a whole valid packet is received
 */
int UART_get_packet_sync(uint8_t *buf, uint8_t max_len) {
	if (UART_fd == -1) {
		printf("Error: serial port is not open\n");
        return 0;
    }

    uint8_t idx = 0;
    bool is_escaping = false;
    bool pkt_complete = false;

    while (!pkt_complete) {
        int8_t bytes_read = read(UART_fd, buf+idx, 1);
        
        if (bytes_read <= 0) {
            printf("UART returned no bytes\n");
            return 0;
        }

        if (buf[idx] == CTRL_DLE && !is_escaping) {
            is_escaping = true;
        } else {
            if (is_escaping && buf[idx] == CTRL_ETX)
                pkt_complete = true;
            is_escaping = false;
        }

        idx += bytes_read;

        if (idx == max_len) {
            printf("Maximum buffer size was reached but no valid packet was detected\n");
            return 0;
        }
    }

    return idx;
}

/**
 * @brief Send a packet on the UART interface
 */
int UART_send_packet_sync(uint8_t *buf, uint8_t pkt_len) {
	if (UART_fd == -1) {
		printf("Error: serial port is not open\n");
        return 0;
    }

    return write(UART_fd, buf, pkt_len);
}

