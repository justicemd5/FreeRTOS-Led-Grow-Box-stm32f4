/*
 * tmath.c
 *
 *  Created on: May 21, 2014
 *      Author: Almir
 */

#include "tmath.h"

int32_t tmath_power(int32_t num, int8_t power)
{
	if (0 == power)
	{
		return 1;
	}
	else
	{
		int32_t number = num;
		int8_t i;
		for (i = 1; i < power; num *= number, i++) { /* empty block */ }

		return num;
	}
}

int64_t tmath_round_int64(int64_t integer, uint8_t decimal, uint8_t round)
{
	int32_t co = tmath_power(10, (decimal - round));
	int64_t rounded =  integer / co;

	if (1 != co)
	{
		co /= 10;
		int64_t temp = integer / co;
		temp %= 10;
		if (temp >= 5)
		{
			rounded++;
		}
	}

	return rounded;
}

static bool_t is_addition_overflow_int32(uint32_t current_value,
								  uint32_t value_to_add, uint32_t max)
{
	uint32_t max_value_to_add = max - current_value;

	return (value_to_add > max_value_to_add);
}

bool_t tmath_addition_overflow_uint32(uint32_t current_value,
									  uint32_t value_to_add)
{
	return is_addition_overflow_int32(current_value, value_to_add, TMATH_UINT32_MAX);
}

bool_t tmath_addition_overflow_int32(int32_t current_value,
									 int32_t value_to_add)
{
	return is_addition_overflow_int32(current_value, value_to_add, TMATH_INT32_MAX);
}

bool_t tmath_substraction_overflow_int32(int32_t current_value,
									 	 uint32_t value_to_substract)
{
	int32_t min = TMATH_INT32_MIN + value_to_substract;

	return current_value < min;
}

bool_t tmath_int64_overflow_uint32(int64_t value)
{
	return (value > TMATH_UINT32_MAX);
}

bool_t tmath_is_substraction_result_negative(uint32_t current_value,
		  	  	  	  	  	  	  	  	  	 uint32_t value_to_substract)
{
	return (value_to_substract > current_value);
}

uint8_t tmath_byte_reverse(uint8_t bData)
{
	uint8_t lookup[] = { 0, 8,  4, 12,
					  2, 10, 6, 14 ,
					  1, 9,  5, 13,
					  3, 11, 7, 15 };
	uint8_t ret_val = (uint8_t)(((lookup[(bData & 0x0F)]) << 4) + lookup[((bData & 0xF0) >> 4)]);
	return ret_val;
}
/* ne koristi se
uint32_t tmath_safe_add_uint32_t(uint32_t current_value, uint32_t value_to_add)
{
	if (!tmath_is_overflow_uint32(value_to_add, current_value))
	{
		current_value += value_to_add;
	}
	else
	{

	}

	return current_value;
}
*/
