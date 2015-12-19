/*
 * datetime.h
 *
 *  Created on: Oct 23, 2013
 *      Author: Nihad
 */

#ifndef DATETIME_H_
#define DATETIME_H_

#include "tdatetime.h"
#include "settings.h"
#include "rtc.h"
#include "rtc_config.h"

//typedef struct
//{                       /* Structure used for time event operation */
//	RTC_DateTime			datetime;
//	RTC_EVENT_ENUM_STRUCT	event_type;
//} RTC_Events;


ERROR_CODE datetime_set(RTC_DateTime* dateTime);
ERROR_CODE datetime_get(RTC_DateTime* dateTime);
ERROR_CODE datetime_enable_dst(uint8_t forceHour);
ERROR_CODE datetime_change_dst(RTC_DateTime * dst);
ERROR_CODE datetime_enable_alarm(RTC_DateTime* dateTime);

RTC_DateTime * datetime_alarm_get(void);
void datetime_alarmlist_add(RTC_DateTime* dateTime, uint8_t alarmtype);
void datetime_alarmlist_remove(uint8_t alarmtype);
void datetime_alarmlist_clear();
void datetime_alarmlist_set_next(void);
void datetime_alarm_handler(RTC_DateTime* dateTime, uint8_t alarmtype);
void datetime_alarmlist_occured();

#endif /* DATETIME_H_ */
