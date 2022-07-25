#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include "uart_interface.h"
#include "ctrl-nwk-utils.h"


int UART_fd = -1;
char *uart_dev = "/dev/ttyAMA0";
// char *uart_dev = "/dev/ttyUSB0";


/**
 * @brief Initialize the UART interface
 */
bool UART_init() {
	UART_fd = open(uart_dev, O_RDWR | O_NOCTTY);

	if (UART_fd == -1) {
		printf("Error opening serial port: %s\n", uart_dev);
        return false;
    }

	struct termios options;
	tcgetattr(UART_fd, &options);
    
    /* Disable all I/O processing */
    options.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
    options.c_oflag = 0; //&= ~(OCRNL | ONLCR | ONLRET | ONOCR | ONOEOT| OFILL | OLCUC | OPOST);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
    options.c_cflag &= ~(CSIZE | PARENB);
    options.c_cflag |= CS8;
    // One input byte is enough to return from read()
    options.c_cc[VMIN]  = 1;
    options.c_cc[VTIME] = 0;
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

    while (!CTRL_is_frame_wellformed(buf, idx)) {
        int8_t bytes_read = read(UART_fd, buf+idx, 1);

        if (bytes_read == -1) {
            printf("Error: %s\n", strerror(errno));
            return 0;
        } else {
            idx += bytes_read;
        }

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

