#ifndef RTC_H_
#define RTC_H_

#include "settings.h"
#include "tdatetime.h"
#include "rtc_config.h"
#include "error_codes.h"

ERROR_CODE rtc_init();
ERROR_CODE rtc_set_time(RTC_DateTime * TimePtr);
ERROR_CODE rtc_get_time(RTC_DateTime * TimePtr);
ERROR_CODE rtc_set_alarm(RTC_DateTime * TimePtr, uint32_t alarm_mask);
ERROR_CODE rtc_peripheral_test();

#endif
