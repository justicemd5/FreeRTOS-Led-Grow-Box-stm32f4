/*
 * array.h
 *
 *  Created on: May 7, 2014
 *      Author: Almir
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include "stdint.h"
#include "ttypes.h"
//#include "datetime.h"
#include "tdatetime.h"
#include "error_codes.h"

//void array_insert_char(uint8_t * array, uint32_t index, char_t character);
//void array_insert_uint8(uint8_t * array, uint32_t index, uint8_t value);
void array_insert_int16(uint8_t * array, uint32_t index, int16_t value);
void array_insert_uint16(uint8_t * array, uint32_t index, uint16_t value);
void array_insert_uint32(uint8_t * array, uint32_t index, uint32_t value);
void array_insert_int32(uint8_t * array, int32_t index, int32_t value);
void array_insert_datetime(uint8_t * array, uint32_t index, const RTC_DateTime * dateTime);
void array_insert_datetime_full(uint8_t * array, uint32_t index, RTC_DateTime * dateTime);
void array_insert_uint24(uint8_t * array, uint32_t index, uint32_t value);
void array_insert_string(uint8_t * array, uint32_t index, const char_t * string);
void array_insert_error_code(uint8_t  *array, uint32_t index, ERROR_CODE error, uint8_t size);

char_t array_get_char(uint8_t * array, uint32_t index);
uint8_t array_get_uint8(uint8_t * array, uint32_t index);
int16_t array_get_int16(uint8_t * array, uint32_t index);
uint16_t array_get_uint16(uint8_t * array, uint32_t index);
uint32_t array_get_uint32(uint8_t * array, uint32_t index);
int32_t array_get_int32(uint8_t * array, uint32_t index);
void array_get_datetime(uint8_t * array, uint32_t index, RTC_DateTime * dateTime);
void array_get_datetime_full(uint8_t * array, uint32_t index, RTC_DateTime * dateTime);
uint32_t array_get_uint24(uint8_t * array, uint32_t index);
void array_get_string(uint8_t * array, uint32_t index, uint8_t length, char_t * string);
ERROR_CODE array_get_error_code(uint8_t * array, uint32_t index, uint8_t size);

#endif /* ARRAY_H_ */
