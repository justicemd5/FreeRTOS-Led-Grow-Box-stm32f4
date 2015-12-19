/*
 * uart.h
 *
 *  Created on: Dec 30, 2013
 *      Author: nihad
 */

#ifndef UART_H_
#define UART_H_

#include "uart_config.h"
#include "error_codes.h"

ERROR_CODE uart_init();
void uart_deinit();

ERROR_CODE uart_open(UART_REG reg, uint32_t baudrate);
ERROR_CODE uart_close(UART_REG reg);

ERROR_CODE uart_byte_write(UART_REG reg, uint8_t data);
ERROR_CODE uart_wait_eow(UART_REG reg);
ERROR_CODE uart_byte_read(UART_REG reg, uint8_t * data);
ERROR_CODE uart_byte_timeout_read(UART_REG reg, uint32_t timeout_us, uint8_t * data);
void uart_handle_overrun(UART_REG reg);
void uart_flush(UART_REG reg);
void uart_toggle_irq(UART_REG reg, uint32_t interupt, uint8_t enable);

void uart_dma_init();
ERROR_CODE uart_dma_write(const UART_REG reg, const uint8_t *const data,
						const uint16_t data_size);
ERROR_CODE uart_dma_stop(const UART_REG reg);
ERROR_CODE uart_dma_completed(const UART_REG reg, bool_t *const flag_ptr);
ERROR_CODE uart_dma_error(const UART_REG reg);

#endif /* uart_H_ */
