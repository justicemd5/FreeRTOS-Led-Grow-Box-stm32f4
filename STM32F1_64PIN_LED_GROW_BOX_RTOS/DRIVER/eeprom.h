/**
  * @}
  */
#ifndef EEPROM_H_
#define EEPROM_H_
#include "eeprom_config.h"
#include "error_codes.h"

ERROR_CODE eeprom_read(uint8_t address, uint8_t * data, uint8_t length);
ERROR_CODE eeprom_write(uint8_t address, uint8_t * data, uint8_t length);
ERROR_CODE eeprom_peripheral_test();

#ifdef TEST
	ERROR_CODE eeprom_Test(void);
#endif

#endif
