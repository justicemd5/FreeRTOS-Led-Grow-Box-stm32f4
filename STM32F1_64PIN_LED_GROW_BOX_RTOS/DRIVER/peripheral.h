#ifndef PERIPHERAL_H_
#define PERIPHERAL_H_

#include "settings.h"
#include "peripheral_config.h"
#include "gpio.h"
#include "touch.h"
#include "CONFIG/power_config.h"

//defined in settings.h
//extern volatile bool_t power_sleep_occured;

void (*peripheral_wakeup)(void);

void peripheral_init();
//void peripheral_deinit();
//void peripheral_sleep(power_schema_t schema);
//uint8_t peripheral_sleep_check(uint8_t reset_sleep_flag);
ERROR_CODE peripheral_device_on(uint16_t device);
//ERROR_CODE peripheral_device_off(uint16_t device, uint8_t deinit_hal);
//ERROR_CODE peripheral_device_test(uint16_t device);
//uint16_t peripheral_error_show_device();

#endif
