/*
 * tstring.h
 *
 *  Created on: Apr 23, 2014
 *      Author: Almir
 */

#ifndef TSTRING_H_
#define TSTRING_H_

#include "ttypes.h"
#include <string.h>

#define TSTRING_INT16_LEN				6  /* 65535\0 */
#define TSTRING_INT32_LEN				11 /* 4294967295\0 */
#define TSTRING_INT32_DECIMAL_LEN		13 /* -4294967,295\0
 	 	 	 	 	 	 	 	 	 	 	  -42949672,95\0*/
#define TSTRING_INT32_FORMATTED_LEN		15 /* -4.294.967.295\0
											  +429.496.729,5\0
											  -42.949.672,95\0
											  +4.294.967,295\0
											  -429.496,7295\0 */

#define TSTRING_INT64_FORMATTED_LEN		26 /* 9.223.372.036.854.775.807\0
											  92.233.720.368.547.758,07\0 */

extern const char_t * const TSTRING_EMPTY;

void tstring_pad_left(char_t * string, uint8_t total_width);
void tstring_pad_left_char(char_t * string, uint8_t total_width, char_t padding_char);
void tstring_pad_right(char_t * string, uint8_t total_width);
void tstring_pad_right_char(char_t * string, uint8_t total_width, char_t padding_char);
void tstring_insert(char_t * string, uint16_t index, const char_t * value);
void tstring_insert_char(char_t * string, uint16_t index, char_t value);
void tstring_remove_length(char_t * string, uint16_t index, uint8_t length);
void tstring_remove(char_t * string, uint16_t index);

void tstring_replace(char_t * string, const char_t * old, const char_t * new);

int8_t tstring_index_of(const char_t * string, const char_t * value);
int16_t tstring_index_of_char(const char_t * string, const char_t value);
int8_t tstring_last_index_of(const char_t * string, char_t value);
bool_t tstring_contains_char(const char_t * string, char_t value);
bool_t tstring_contains(const char_t * string, const char_t * value);
bool_t tstring_ends_with(const char_t * string, const char_t * value);
bool_t tstring_ends_with_char(const char_t * string, char_t value);
bool_t tstring_starts_with_char(const char_t * string, char_t value);
void tstring_int_to_hex(int32_t data, char_t * hex_string);
void tstring_int_to_decimal_string(
		char_t * string, const int32_t number, const uint8_t decimal_places);
void tstring_uint_to_decimal_string(
		char_t * string, const uint32_t number, const uint8_t decimal_places);
void tstring_digit_group(char_t * string);
uint32_t tstring_decimal_string_to_uint(const char_t * string,
									    const uint8_t decimal_places);
bool_t tstring_try_decimal_string_to_uint(uint32_t * number,
										  const char_t * string,
	    								  const uint8_t decimal_places);
int32_t tstring_string_to_int(const char_t * string);

void tstring_int_to_string(char_t * string, int32_t integer);
void tstring_concat(uint8_t argc, ...);
bool_t tstring_is_null_or_empty(const char_t * string);
void tstring_copy(char_t * to, const char_t * from);
bool_t tstring_try_copy(char_t * const to, uint16_t to_length,
						const char_t * const from);

void tstring_to_upper(char_t * string);
void tstring_to_lower(char_t * string);
void tstring_ascii_get_bytes(const char_t * string, uint8_t * bytes);
void tstring_split(char_t * string, char_t split_char, char_t * array[]);

void tstring_substring_length(
		char_t * to, const char_t * from, const uint16_t index, const uint8_t length);
void tstring_substring(char_t * to, const char_t * from, const uint16_t index);

void tstring_trim(char_t * string);
void tstring_trim_end(char_t * string);
void tstring_trim_start(char_t * string);
void tstring_int64_to_decimal_string(
		char_t * string, const int64_t number, const uint8_t decimal_places);
void tstring_uint_to_string(char_t * string, uint32_t integer);
void tstring_int64_to_string(char_t * string, int64_t integer);

#endif /* TSTRING_H_ */
