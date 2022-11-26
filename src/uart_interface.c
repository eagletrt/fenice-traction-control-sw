#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include "uart_interface.h"
#include "ctrl-nwk-utils.h"
#include "logger.h"


int UART_fd = -1;
char *uart_dev = "/dev/ttyAMA0";
// char *uart_dev = "/dev/ttyUSB0";
// char *uart_dev = "/dev/random";


/**
 * @brief Initialize the UART interface
 */
bool UART_init() {
	UART_fd = open(uart_dev, O_RDWR | O_NOCTTY);

	if (UART_fd == -1) {
		LOG_write(LOGLEVEL_ERR, "[UART] Error opening serial port: %s", uart_dev);
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
	cfsetispeed(&options, B1000000);
	cfsetospeed(&options, B1000000);
	tcsetattr(UART_fd, TCSANOW, &options);

    return true;
}

/**
 * @brief Read from the UART until a whole valid packet is received
 */
int UART_get_packet_sync(uint8_t *buf, uint8_t max_len) {
	if (UART_fd == -1) {
		LOG_write(LOGLEVEL_ERR, "[UART] Error: serial port is not open");
        return 0;
    }

    uint8_t idx = 0;

    while (!CTRL_is_frame_wellformed(buf, idx)) {
        /* Read one byte */
        if (read(UART_fd, buf+idx, 1) != -1) {
            idx++;
        } else {
            LOG_write(LOGLEVEL_ERR, "[UART] Read error: %s", strerror(errno));
            return 0;
        }

        /* Reset idx to 0 if: */
        /*   1) The beginning of the buffer is not a valid header */
        if (idx == 2 && (buf[0] != CTRL_DLE || buf[1] != CTRL_STX)) {
            idx = 0;
        }
        /*   2) The maximum frame size was read but it makes no sense */
        if (idx == CTRL_MAX_FRAME_LEN) {
            LOG_write(LOGLEVEL_INFO, "[UART] Max frame size was read but no ending sequence was received");
            idx = 0;
        }
        /*   3) Despite not reading a valid packet the buffer filled up */
        if (idx >= (max_len - 1)) {
            LOG_write(LOGLEVEL_WARN, "[UART] Buffer overrun");
            idx = 0;
        }
    }

    return idx;
}

/**
 * @brief Send a packet on the UART interface
 */
int UART_send_packet_sync(uint8_t *buf, uint8_t pkt_len) {
	if (UART_fd == -1) {
		LOG_write(LOGLEVEL_ERR, "[UART] Error: serial port is not open");
        return 0;
    }

    return write(UART_fd, buf, pkt_len);
}

