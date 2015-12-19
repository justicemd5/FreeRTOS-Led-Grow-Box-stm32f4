#ifndef __IFM_H
#define __IFM_H

#include "ifm_config.h"

ERROR_CODE ifm_memorypage_clear(uint32_t address);
ERROR_CODE ifm_string_write(uint32_t address, const uint8_t * dataBuffer, uint32_t dataSize);
void ifm_string_read(uint32_t address, uint8_t * dataBuffer, uint32_t dataSize);

ERROR_CODE ifm_uint32_write(uint32_t address, uint32_t value);
uint32_t ifm_uint32_read(uint32_t address);

#endif
