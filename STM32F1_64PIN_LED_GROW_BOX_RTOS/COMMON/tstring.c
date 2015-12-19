/*
 * tstring.c
 *
 *  Created on: Apr 23, 2014
 *      Author: Almir
 */

#include "tstring.h"
#include "mini-printf.h"
#include "tmath.h"
#include <ctype.h>
#include <stdarg.h> /* va_arg */

/* TODO ovo izmjestiti u regional_settings.h */
static const char_t DECIMAL_SYMBOL = ',';
static const char_t DIGIT_GROUPING_SYMBOL = '.';

/* dvije decimale	42.949.672,95\0 */
/* tri decimale		4.294.967,295\0 */
#define INT32_LEN	14

const char_t * const TSTRING_EMPTY = "";

/* pass total_width without null */
static void padding(char_t * string, uint8_t total_width, char_t padding_char,
					bool_t right_padding)
{
	const uint8_t str_len = strlen(string);
	const uint8_t white_space_len = total_width - str_len;

	/* ovako radi .net padding, ako ne može paddovat samo ga vrati kakav jest */
	if (str_len < total_width)
	{
		if (right_padding)
		{
			memset(string + str_len, padding_char, white_space_len);
		}
		else
		{
			/* pomakni tekst i null udesno za širinu whitespace-a */
			memmove(string + white_space_len, string, str_len + 1);
			/* u lijevu stranu ubaci whitespace */
			memset(string, padding_char, white_space_len);
		}
	}
	else
	{
		/* TODO greška */
	}

	string[total_width] = 0;
}

void tstring_pad_left_char(char_t * string, uint8_t total_width, char_t padding_char)
{
	padding(string, total_width, padding_char, false);
}

void tstring_pad_left(char_t * string, uint8_t total_width)
{
	tstring_pad_left_char(string, total_width, ' ');
}

void tstring_pad_right_char(char_t * string, uint8_t total_width, char_t padding_char)
{
	padding(string, total_width, padding_char, true);
}

void tstring_pad_right(char_t * string, uint8_t total_width)
{
	tstring_pad_right_char(string, total_width, ' ');
}

void tstring_insert(char_t * string, uint16_t index, const char_t * value)
{
	const uint16_t value_len = strlen(value);
	const uint16_t string_len = strlen(string);

	if (string_len >= index)
	{
		memmove(string + index + value_len, string + index, string_len - index);
		memmove(string + index, value, value_len);
	}
	else
	{
		/* TODO greška */
	}

	/* final string length will be the length of both strings combined */
	string[value_len + string_len] = 0;
}

void tstring_insert_char(char_t * string, uint16_t index, char_t value)
{
	char_t character[2];
	character[0] = value;
	character[1] = '\0';

	tstring_insert(string, index, character);
}

void tstring_remove_length(char_t * string, uint16_t index, uint8_t length)
{
	const uint16_t str_len = strlen(string);

	if ((str_len > index) && (0 < length) && (str_len >= index + length))
	{
		memmove(string + index, string + index + length,
				str_len - (index + length));

		string[str_len - length] = 0;
	}
	else
	{
		/* TODO greška */
	}
}

void tstring_remove(char_t * string, uint16_t index)
{
	tstring_remove_length(string, index, strlen(string) - index);
}

void tstring_replace_char(char_t * string, char_t old, char_t new)
{
	uint8_t str_len = strlen(string);

	uint8_t i;
	for (i = 0; i < str_len; i++)
	{
		if (string[i] == old)
		{
			string[i] = new;
		}
	}
}

void tstring_replace(char_t * string, const char_t * old, const char_t * new)
{
	int8_t index_of_old = 0;
	uint8_t old_len = strlen(old);

	do
	{
		index_of_old = tstring_index_of(string, old);
		if (-1 != index_of_old)
		{
			tstring_remove_length(string, index_of_old, old_len);
			tstring_insert(string, index_of_old, new);
		}

	} while (-1 != index_of_old);
}

int16_t tstring_index_of_char(const char_t * string, const char_t value)
{
	char_t * character = strchr(string, value);
	return (character == 0) ? -1 : character - string;
}

int8_t tstring_index_of(const char_t * string, const char_t * value)
{
	char_t * strPtr = strstr(string, value);
	return (strPtr == 0) ? -1 : strPtr - string;
}

int8_t tstring_last_index_of(const char_t * string, char_t value)
{
	char_t * character = strrchr(string, value);
	return (character == 0) ? -1 : character - string;
}

bool_t tstring_contains(const char_t * string, const char_t * value)
{
	int8_t index = tstring_index_of(string, value);

	if (-1 == index)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool_t tstring_contains_char(const char_t * string, char_t value)
{
	int16_t index = tstring_index_of_char(string, value);

	if (-1 == index)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool_t tstring_ends_with_char(const char_t * string, char_t value)
{
	return (0 != string[0] && string[strlen(string) - 1] == value);
}

bool_t tstring_ends_with(const char_t * string, const char_t * value)
{
	uint8_t value_len = strlen(value);
	uint8_t start = strlen(string) - value_len;

#if 0 /* stari kod */
	int i;
	for (i = 0; i < valueLen; i++)
	{
		if (string[i + start] != value[i]) return 0;
	}
	return 1;
#endif

	if (strcmp(string + start, value) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool_t tstring_starts_with_char(const char_t * string, char_t value)
{
	return (string[0] == value);
}

void tstring_digit_group(char_t * string)
{
	/* u slučaju da već postoji separator npr. 1[]225.554,2236 */
	tstring_replace(string, &DIGIT_GROUPING_SYMBOL, "");

	int16_t dec_symbol_index = tstring_index_of_char(string, DECIMAL_SYMBOL);
	if (dec_symbol_index == -1)
	{
		dec_symbol_index = strlen(string);
	}

	int8_t i = dec_symbol_index;
	for (; i > 0 && i - 3 > 0;)
	{
		i -= 3;
		if (isdigit(string[i - 1])) /* da se izbjegne -.887 */
		{
			tstring_insert_char(string, i, DIGIT_GROUPING_SYMBOL);
		}
	}
}

int32_t tstring_string_to_int(const char_t * string)
{
	int32_t result = 0;

	bool_t is_negative = false;
	if ('-' == string[0])
	{
		//string[0] = '0'; /* TODO prepraviti ovo */
		is_negative = true;
	}

	uint8_t i = strlen(string);
	int8_t j = 0;
	for (; i > 0; i--, j++)
	{
		uint8_t ascii_number = string[i - 1];
		if (48 <= ascii_number && 57 >= ascii_number)
		{
			result += (ascii_number - 48) * tmath_power(10, j);
		}
		else
		{
			break;
			/* TODO error */
		}
	}

	if (is_negative)
	{
		result *= -1;
	}

	return result;
}

static void remove_digit_grouping(char_t * const string)
{
	char_t symbol[2] = { DIGIT_GROUPING_SYMBOL, 0 };
	tstring_replace(string, symbol, "");
}

static void remove_comma(char_t * const string)
{
	char_t symbol[2] = { DECIMAL_SYMBOL, 0 };
	tstring_replace(string, symbol, "");
}

uint32_t tstring_decimal_string_to_uint(const char_t * string,
									    const uint8_t decimal_places)
{
	char_t string_copy[INT32_LEN] = { 0 };
	memcpy(string_copy, string, strlen(string));

	remove_digit_grouping(string_copy);

	int16_t dec = tstring_index_of_char(string_copy, DECIMAL_SYMBOL) + 1;

	if (0 != dec)
	{
		int8_t len = strlen(string_copy);
		if (len - dec > decimal_places)
		{
			tstring_remove(string_copy, (dec + decimal_places));
			len = strlen(string_copy);
		}

		dec = decimal_places - (len - dec);
	}
	else
	{
		dec = decimal_places;
	}

	remove_comma(string_copy);

	uint32_t integer = tstring_string_to_int(string_copy);

	/* ne koristi se funkcija pow(10, decimal_places) zbog toga sto bi se
	 * morao ukljuciti novi header math.h */
	integer *= tmath_power(10, dec);

	return integer;
}

static void fill_decimal_string_with_zeros(char_t * const string,
										   uint8_t dec_places)
{
	uint8_t str_len = strlen(string);
	if (!tstring_contains_char(string, DECIMAL_SYMBOL))
	{
		tstring_insert_char(string, str_len, DECIMAL_SYMBOL);
		str_len++;
	}

	int16_t decimals_index = tstring_index_of_char(string, DECIMAL_SYMBOL) + 1;
	const uint8_t decimals_count = str_len - (uint8_t)decimals_index;

	if (decimals_count < dec_places)
	{
		uint8_t decimals_to_add = dec_places - decimals_count;

		memset(string + str_len, '0', decimals_to_add);
	}
}

/* String "287,5" representing decimal number 287,500 to "287500" */
static void decimal_string_to_uint_string(char_t * const string,
										  uint8_t dec_places)
{
	if (0 != dec_places)
	{
		fill_decimal_string_with_zeros(string, dec_places);
	}

	int16_t comma_index = tstring_index_of_char(string, DECIMAL_SYMBOL);
	if (-1 != comma_index)
	{
		tstring_remove_length(string, comma_index, 1);
	}
}

static bool_t is_string_uint32_overflow(const char_t * const string,
										uint8_t dec_places)
{
	// TODO prevent memory leaks when modifying number_str
	char_t number_str[TSTRING_INT32_DECIMAL_LEN + 10] = { 0 };

	tstring_copy(number_str, string);

	decimal_string_to_uint_string(number_str, dec_places);

	uint8_t number_text_len = strlen(number_str);

	bool_t is_overflow = false;

	if (number_text_len > 10)
	{
		is_overflow = true;
	}
	else if (number_text_len == 10)
	{
		char_t bilion_number[2] = { number_str[0], 0 };
		uint8_t bilion = tstring_string_to_int(bilion_number);

		if (bilion > 4)
		{
			is_overflow = true;
		}
		else if (bilion == 4)
		{
			uint32_t input_value = tstring_string_to_int(number_str + 1);

			if (input_value > 294967295)
			{
				is_overflow = true;
			}
		}
	}

	return is_overflow;
}

bool_t tstring_try_decimal_string_to_uint(uint32_t * number,
										  const char_t * string,
	    								  const uint8_t decimal_places)
{
	bool_t successful = false;
	if (!is_string_uint32_overflow(string, decimal_places))
	{
		if (0 != number)
		{
			*number = tstring_decimal_string_to_uint(string, decimal_places);
		}

		successful = true;
	}

	return successful;
}

static void int_to_decimal_string(
		char_t * string, const int64_t number, const uint8_t decimal_places,
		bool_t int64, bool_t is_unsigned)
{
	int64_t non_const_num = number;
	bool_t is_negative = false;
	if (number < 0)
	{
		is_negative = true;
		non_const_num *= -1;
	}

	if (int64)
	{
		tstring_int64_to_string(string, non_const_num);
	}
	else
	{
		if (is_unsigned)
		{
			tstring_uint_to_string(string, (uint32_t)non_const_num);
		}
		else
		{
			tstring_int_to_string(string, (int32_t)non_const_num);
		}
	}

	uint8_t str_len = strlen(string);
	if (str_len - 1 < decimal_places) /* for number like 0,0225*/
	{
		tstring_pad_left_char(string, decimal_places + 1, '0');
		str_len = strlen(string);
	}

	uint8_t decimal_index = str_len - decimal_places;

	if (str_len != decimal_index) /* za cijele brojeve da se ne desava 85, */
	{
		tstring_insert_char(string, decimal_index, DECIMAL_SYMBOL);
	}
	if (is_negative)
	{
		tstring_insert_char(string, 0, '-');
	}
}

void tstring_int_to_decimal_string(
		char_t * string, const int32_t number, const uint8_t decimal_places)
{
	int_to_decimal_string(string, number, decimal_places, false, false);
}

void tstring_uint_to_decimal_string(
		char_t * string, const uint32_t number, const uint8_t decimal_places)
{
	int_to_decimal_string(string, number, decimal_places, false, true);
}

void tstring_int64_to_decimal_string(
		char_t * string, const int64_t number, const uint8_t decimal_places)
{
	int_to_decimal_string(string, number, decimal_places, true, false);
}

void tstring_int_to_string(char_t * string, int32_t integer)
{
	mini_snprintf(string, INT32_LEN, "%d", integer);
}

void tstring_uint_to_string(char_t * string, uint32_t integer)
{
	tstring_int64_to_string(string, (int64_t)integer);
}

void tstring_int64_to_string(char_t * string, int64_t integer)
{
	uint8_t base = 10;

	uint64_t tmp_integer;
	char_t * ptr = string;

	do
	{
		tmp_integer = integer;
		integer /= base;
		*ptr++ = "0123456789"[tmp_integer - (integer * base)];

	} while (integer);

	// Apply negative sign
	if (tmp_integer < 0)
	{
		*ptr++ = '-';
	}

	*ptr-- = '\0';

	char_t * ptr1 = string;
	while (ptr1 < ptr)
	{
		char_t tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
}

void tstring_int_to_hex(int32_t data, char_t * hex_string)
{
	const char_t * hex_chars = "0123456789abcdef";
	uint8_t i;
	for (i = 0; 0 != data; i++)
	{
		tstring_insert_char(hex_string, 0, hex_chars[data % 16]);
		data /= 16;
	}

	hex_string[i] = '\0';
}

void tstring_concat(uint8_t argc, ...)
{
	va_list arguments;
	va_start(arguments, argc);

	char_t * firstArg = va_arg(arguments, char_t *);
	int i;
	for (i = 0; i < argc - 1; ++i)
	{
		char_t * arg = va_arg(arguments, char_t *);
		strcat(firstArg, arg);
	}

	va_end(arguments);
}

bool_t tstring_is_null_or_empty(const char_t * string)
{
	if (string == 0)
	{
		return 1; /* null */
	}
	else
	{
		return string[0] == '\0'; /* empty */
	}
}

void tstring_copy(char_t * to, const char_t * from)
{
	if (from != 0)
	{
		memmove(to, from, strlen(from) + 1);
	}
}

bool_t tstring_try_copy(char_t * const to, uint16_t to_length,
						const char_t * const from)
{
	const uint8_t from_len = strlen(from);

	bool_t sucessful = false;
	if (from_len <= to_length)
	{
		if (from != 0)
		{
			memmove(to, from, strlen(from) + 1);
			sucessful = true;
		}
	}

	return sucessful;
}

void tstring_substring_length(
		char_t * to, const char_t * from, const uint16_t index, const uint8_t length)
{
	/* TODO check is "to" big enough to store "from" */
	if (from != 0)
	{
		memmove(to, from + index, length);
		to[length] = 0;
	}
}

void tstring_substring(char_t * to, const char_t * from, const uint16_t index)
{
	tstring_substring_length(to, from, index, strlen(from) - index);
}

static void to_upper_to_lower(char_t * string, char_t first_char, char_t last_char)
{
	uint8_t strLen = strlen(string);

	uint8_t i;
	for (i = 0; i < strLen; ++i)
	{
		if (string[i] >= first_char && string[i] <= last_char)
		{
			if (first_char == 'a') /* from small to capital */
			{
				string[i] -= 32;
			}
			else /* from capital to small */
			{
				string[i] += 32;
			}
		}

//		else if (string[i] == 134) string[i] = 143; //
//		else if (string[i] == 159) string[i] = 172; //
//		else if (string[i] == 231) string[i] = 230; //
//		else if (string[i] == 208) string[i] = 209; //
//		else if (string[i] == 167) string[i] = 166; //
//		ili else if (string[i] = BOSNIAN_cj) string[i] = BOSNIAN_CJ;
	}
}

void tstring_to_upper(char_t * string)
{
	to_upper_to_lower(string, 'a', 'z');
}

void tstring_to_lower(char_t * string)
{
	to_upper_to_lower(string, 'A', 'Z');
}

void tstring_split(char_t * string, char_t split_char, char_t * array[])
{
	/* ovaj kod se vi�e ne koristi zbog problema sa code page 852
	char_t * pch;
	pch = strtok(string, &split_char);
	uint8_t count = 0;

	while (0 != pch)
	{
		array[count] = pch;
		pch = strtok(0, &split_char);
		count++;
	}
	*/

	int16_t index = 0;

	uint8_t i;
	for (i = 0; -1 != index; ++i)
	{
		index = tstring_index_of_char(string, split_char);
		if (-1 != index)
		{
			string[index] = 0;
		}

		array[i] = string;
		string += index + 1;
	}
}

void tstring_trim(char_t * string)
{
	tstring_trim_end(string);
	tstring_trim_start(string);
}

void tstring_trim_end(char_t * string)
{
	uint8_t last_char_index = strlen(string) - 1;
	while(tstring_ends_with_char(string, ' '))
	{
		tstring_remove(string, last_char_index);
		last_char_index--;
	}
}

void tstring_trim_start(char_t * string)
{
	while(tstring_starts_with_char(string, ' '))
	{
		tstring_remove_length(string, 0, 1);
	}
}

