/*
 * array.c
 *
 *  Created on: May 7, 2014
 *      Author: Almir
 */

#include "array.h"
#include "string.h"

// TODO parametri const
static void insert_uint(uint8_t * array, uint32_t index, uint32_t num, uint8_t length)
{
	int i, j;
	for (i = 0, j = 0; i < length; i++, j += 8)
	{
		array[index + i] = (num >> j) & 0xFF;
	}
}
//// TODO ovo prepraviti, mora biti jedna funkcija
//static void insert_int(uint8_t * array, uint32_t index, int32_t num, uint8_t length)
//{
//	int i, j;
//	for (i = 0, j = 0; i < length; i++, j += 8)
//	{
//		array[index + i] = (num >> j) & 0xFF;
//	}
//}

void array_insert_int16(uint8_t * array, uint32_t index, int16_t value)
{
	insert_uint(array, index, (int32_t)value, 2);
}

void array_insert_uint16(uint8_t * array, uint32_t index, uint16_t value)
{
	insert_uint(array, index, (uint32_t)value, 2);
}

void array_insert_uint32(uint8_t * array, uint32_t index, uint32_t value)
{
	insert_uint(array, index, (uint32_t)value, 4);
}

void array_insert_int32(uint8_t * array, int32_t index, int32_t value)
{
	insert_uint(array, index, (uint32_t)value, 4);
}

void array_insert_uint24(uint8_t * array, uint32_t index, uint32_t value)
{
	insert_uint(array, index, (uint32_t)value, 3);
}

void array_insert_datetime(uint8_t * array, uint32_t index, const RTC_DateTime * dateTime)
{
	array[index] = dateTime->Hour;
	array[index + 1] = dateTime->Minute;
	array[index + 2] = dateTime->Day;
	array[index + 3] = dateTime->Month;
	array[index + 4] = dateTime->Year;
}

//all datetime parameters
void array_insert_datetime_full(uint8_t * array, uint32_t index, RTC_DateTime * dateTime)
{
	array[index] = dateTime->Hour;
	array[index + 1] = dateTime->Minute;
	array[index + 2] = dateTime->Day;
	array[index + 3] = dateTime->Month;
	array[index + 4] = dateTime->Year;
	array[index + 5] = dateTime->Second;
	array[index + 6] = dateTime->DayOfWeek;
}

void array_insert_string(uint8_t * array, uint32_t index, const char_t * string)
{
	memmove(array + index, string, strlen(string));
}

void array_insert_error_code(uint8_t *array, uint32_t index, ERROR_CODE error, uint8_t size)
{
	insert_uint(array, index, (uint32_t)error, size);
}

/* TODO ove funkcije zamijeniti sa jednostavnijim pomoæu kastanja kao macro */
/* find integer in array by index, cast it to pointer to integer then get it's value */
//#define ARRAY_GET_INT32(array, index) *((uint32_t*)(array + index))
static uint32_t get_int(uint8_t * array, uint32_t address, uint8_t length)
{
	uint32_t num = 0;

	int i, j;
	for (i = 0, j = 0; i < length; i++, j += 8)
	{
		num += array[address + i] << j;
	}

	return num;
}

int16_t array_get_int16(uint8_t * array, uint32_t index)
{
	return *((int16_t*)(array + index));
}

// TODO ovo nije potrebno
char_t array_get_char(uint8_t * array, uint32_t index)
{
	return get_int(array, index, 1);
}

// TODO ovo nije potrebno
uint8_t array_get_uint8(uint8_t * array, uint32_t index)
{
	return get_int(array, index, 1);
}

uint16_t array_get_uint16(uint8_t * array, uint32_t index)
{
	return get_int(array, index, 2);
}

uint32_t array_get_uint32(uint8_t * array, uint32_t index)
{
	return get_int(array, index, 4);
}

int32_t array_get_int32(uint8_t * array, uint32_t index)
{
	return (int32_t)get_int(array, index, 4);
}

uint32_t array_get_uint24(uint8_t * array, uint32_t index)
{
	return get_int(array, index, 3);
}

void array_get_datetime(uint8_t * array, uint32_t index, RTC_DateTime * dateTime)
{
	dateTime->Hour = array[index];
	dateTime->Minute = array[index + 1];
	dateTime->Day = array[index + 2];
	dateTime->Month = array[index + 3];
	dateTime->Year = array[index + 4];
}

void array_get_datetime_full(uint8_t * array, uint32_t index, RTC_DateTime * dateTime)
{
	dateTime->Hour = array[index];
	dateTime->Minute = array[index + 1];
	dateTime->Day = array[index + 2];
	dateTime->Month = array[index + 3];
	dateTime->Year = array[index + 4];
	dateTime->Second = array[index + 5];
	dateTime->DayOfWeek = array[index + 6];
}

void array_get_string(uint8_t * array, uint32_t index, uint8_t length, char_t * string)
{
	memmove(string, array + index, length);
	string[length] = 0;
}

ERROR_CODE array_get_error_code(uint8_t * array, uint32_t index, uint8_t size)
{
	return get_int(array, index, size);
}
