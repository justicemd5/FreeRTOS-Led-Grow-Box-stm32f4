#ifndef I2C_H_
#define I2C_H_

#include "i2c_config.h"
#include "error_codes.h"

ERROR_CODE i2c_init();
ERROR_CODE i2c_deinit();
ERROR_CODE i2c_write_read(I2C_REG reg, uint8_t address, uint8_t * writeData, uint8_t writeSize, uint8_t * readData, uint8_t readSize);
ERROR_CODE i2c_get_status(I2C_REG reg, uint8_t address);

#endif
