/*
 * rs232.h
 *
 *  Created on: Jan 22, 2014
 *      Author: nihad
 */

#ifndef RS232_H_
#define RS232_H_

#include <stdint.h>
#include <stdlib.h>
#include "string.h"
#include "settings.h"
#include "uart.h"
#include "error_codes.h"

ERROR_CODE rs232_open(UART_REG port, uint32_t baudrate);
void rs232_close(UART_REG port);

ERROR_CODE rs232_buffer_write_read(UART_REG reg, uint8_t * buffer, uint16_t buffer_size, uint16_t * size, const uint8_t * pattern, uint32_t timeoutStart, uint32_t timeoutEnd);


#ifdef TEST
	ERROR_CODE rs232_Test();
#endif

#endif /* RS232_H_ */
