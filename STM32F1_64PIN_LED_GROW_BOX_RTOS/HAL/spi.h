/*
 * hal_spi.h
 *
 *  Created on: Dec 26, 2013
 *      Author: nihad
 */


#ifndef SPI_H_
#define SPI_H_

#include "spi_config.h"
#include "error_codes.h"

ERROR_CODE spi_init();
ERROR_CODE spi_deinit();

ERROR_CODE spi_set_speed(SPIREG reg, uint8_t speed);

void spi_activate(uint8_t device);
void spi_deactivate();

ERROR_CODE spi_byte_write(SPIREG reg, uint8_t byte);
ERROR_CODE spi_byte_read(SPIREG reg, uint8_t * read);
void spi_buffer_write(SPIREG reg, uint8_t * data, uint8_t dataLength, uint8_t fromByte, uint8_t length);

ERROR_CODE spi_dma_enable(SPIREG reg);
ERROR_CODE spi_dma_disable(SPIREG reg);
ERROR_CODE spi_dma_write_bytes(uint8_t * data, uint8_t length);

#endif /* HAL_spi_H_ */
