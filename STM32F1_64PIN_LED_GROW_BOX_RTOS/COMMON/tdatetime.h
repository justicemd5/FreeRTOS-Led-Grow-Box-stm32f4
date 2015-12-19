/*
 * tdatetime.h
 *
 *  Created on: 12.09.2013
 *      Author: Almir
 */

#ifndef TDATETIME_H_
#define TDATETIME_H_

#include "ttypes.h"

typedef struct
{                       /* Structure used for time operation */
	uint8_t Second;                     /* seconds (0 - 59) */
	uint8_t Minute;                     /* minutes (0 - 59) */
	uint8_t Hour;                       /* hours (0 - 23) */
	uint8_t DayOfWeek;                  /* day of week (0-Sunday, .. 6-Saturday)  */
	uint8_t Day;                        /* day (1 - 31) */
	uint8_t Month;                      /* month (1 - 12) */
	uint8_t Year;                       /* year */

} RTC_DateTime;

//extern const char_t * const DATETIME_FORMAT;

bool_t tdatetime_str_to_dt_exact(RTC_DateTime * datetime, const char_t * string, const char_t * format);
bool_t tdatetime_dt_to_str_exact(char_t * string, const RTC_DateTime * datetime, const char_t * format);
bool_t tdatetime_dt_to_str(char_t * string, const RTC_DateTime * datetime, char_t * datetime_format);
void tdatetime_new(RTC_DateTime * datetime, const uint8_t year,
											const uint8_t month,
											const uint8_t day,
											const uint8_t hour,
											const uint8_t minute,
											const uint8_t second);
int8_t tdatetime_compare(const RTC_DateTime * date1, const RTC_DateTime * date2);
void tdatetime_copy(RTC_DateTime * to, const RTC_DateTime * from);
void tdatetime_date_copy(RTC_DateTime * to, const RTC_DateTime * from);
void tdatetime_add_seconds(RTC_DateTime * dt, uint16_t seconds);
void tdatetime_add_minutes(RTC_DateTime * dt, uint16_t minutes);
void tdatetime_add_hours(RTC_DateTime * dt, uint16_t hours);
void tdatetime_add_days(RTC_DateTime * dt, uint16_t days);
void tdatetime_substract_hours(RTC_DateTime * dt, uint16_t hours);
void tdatetime_substract_minutes(RTC_DateTime * dt, uint16_t minutes);
bool_t tdatetime_validate(RTC_DateTime * datetime);
void tdatetime_get_max(RTC_DateTime * datetime);
void tdatetime_get_min(RTC_DateTime * datetime);
void tdatetime_difference(RTC_DateTime * difference,
						  RTC_DateTime * dt1,
						  RTC_DateTime * dt2);

#endif /* TDATETIME_H_ */
