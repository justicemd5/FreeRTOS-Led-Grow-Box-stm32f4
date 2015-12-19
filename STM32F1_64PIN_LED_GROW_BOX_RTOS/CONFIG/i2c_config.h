#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

#include "settings.h"

//needed for gpio init in HAL
#define USE_I2C1
#define USE_I2C2

typedef I2C_TypeDef* 				I2C_REG;
#define I2C_TIMING 					0x60201B26
#define I2C_READ_TIMEOUT_US			6000
#define I2C_WRITE_TIMEOUT_US		10000
#define I2C_TIMEOUT_TIMER			0

#endif


