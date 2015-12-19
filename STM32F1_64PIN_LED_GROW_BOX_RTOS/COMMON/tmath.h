/*
 * tmath.h
 *
 *  Created on: May 21, 2014
 *      Author: Almir
 */

#ifndef TMATH_H_
#define TMATH_H_

#include "ttypes.h"
#include "limits.h"

#define TMATH_UINT64_MAX		18446744073709551615llu
/* max uint32_t value: 42.949.672,95 */
#define TMATH_UINT32_MAX		UINT_MAX // 4294967295u
#define TMATH_INT32_MAX			INT_MAX // 2147483647
#define TMATH_INT32_MIN			INT_MIN // -2147483648

int32_t tmath_power(int32_t num, int8_t power);
int64_t tmath_round_int64(int64_t integer, uint8_t decimal, uint8_t round);
bool_t tmath_addition_overflow_uint32(uint32_t current_value,
									  uint32_t value_to_add);
bool_t tmath_int64_overflow_uint32(int64_t value);

uint8_t tmath_byte_reverse(uint8_t bData);

bool_t tmath_is_substraction_result_negative(uint32_t current_value,
		  	  	  	  	  	  	  	  	  	 uint32_t value_to_substract);

bool_t tmath_substraction_overflow_int32(int32_t current_value,
									 	 uint32_t value_to_substract);
bool_t tmath_addition_overflow_int32(int32_t current_value,
									 int32_t value_to_add);

#endif /* TMATH_H_ */
