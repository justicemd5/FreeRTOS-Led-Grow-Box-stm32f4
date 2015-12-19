/*
 * cash.h
 *
 *  Created on: Sep 02, 2014
 *      Author: Suvad
 */
#ifndef DATETIME_BCD_H_
#define DATETIME_BCD_H_

#include "tdatetime.h"

void RTC_datetime_value_to_bcd(RTC_DateTime * datetime, uint8_t * bcd_date);
void bcd_value_to_RTC_datetime(uint8_t * datetime, RTC_DateTime * output);
void RTC_datetime_value_to_short_bcd(RTC_DateTime * datetime, uint8_t *bcd_date);

#endif /* DATETIME_BCD_H_ */

