#ifndef EEPROM_CONFIG_H_
#define EEPROM_CONFIG_H_

#include "settings.h"
/* EEPROM SETTINGS */
#define EEPROM_SIZE_IN_BYTES 		0x100

/* EEPROM hardware address and page size */
#define EEPROM_HW_ADDRESS 			0xA0


   /* The I2C Timing is calculated respecting the following conditions:
      - I2C clock source frequency is the system clock: 48MHz
      - I2C speed frequency: 100KHz
      - Rise time: 122ns
      - Fall time: 4ns
   */
#define EEPROM_I2C_TIMING            0x10A15E87

#define EEPROM_I2C 							I2C1
#define CPU_EEPROM_RESET_FLAG				0xAE
#define EEPROM_TEST_BYTE_ADDRESS			0

#endif /* ENDOF EEPROM SETTINGS */
