/*
 * tdatetime.c
 *
 *  Created on: 12.09.2013
 *      Author: Almir
 */

#include "tdatetime.h"
#include "tstring.h"
//#include "fiscal_formats.h" /* za izmjenu default formata */

static bool_t is_leap_year(uint8_t year)
{
	if (year % 4 == 0) /* leap */
	{
		if (year % 100 != 0) /* leap */
		{
			return true;
		}
		else
		{
			return (year % 400 == 0);
		}
	}
	else /* NOT leap */
	{
		return false;
	}
}

static uint8_t get_days_in_month(uint8_t month, uint8_t year)
{
	uint8_t days = 31;

	if (4 == month || 6 == month || 9 == month || 11 == month)
	{
		days = 30;
	}
	else if (2 == month)
	{
		days = (is_leap_year(year) ? 29 : 28);
	}

	return days;
}

bool_t tdatetime_validate(RTC_DateTime * datetime)
{
	uint8_t max_days = get_days_in_month(datetime->Month, datetime->Year);

	if (datetime->Minute > 59
		|| datetime->Hour > 23
		|| datetime->Day < 1 || datetime->Day > max_days
		|| datetime->Month < 1 || datetime->Month > 12
		|| datetime->Year > 99 )
	{
		return false;
	}
	else
	{
		return true;
	}
}

void tdatetime_new(RTC_DateTime * datetime, const uint8_t year, const uint8_t month,
		const uint8_t day, const uint8_t hour, const uint8_t minute, const uint8_t second)
{
	datetime->Year = year;
	datetime->Month = month;
	datetime->Day = day;
	datetime->Hour = hour;
	datetime->Minute = minute;
	datetime->Second = second;
}

void tdatetime_get_max(RTC_DateTime * datetime)
{
	tdatetime_new(datetime, 99, 12, 31, 23, 59, 59);
}

void tdatetime_get_min(RTC_DateTime * datetime)
{
	tdatetime_new(datetime, 0, 1, 1, 0, 0, 0);
}

static void datetime_value_to_string(char_t * string, RTC_DateTime * datetime,
		const char_t * format, const char_t specifier, char_t * data_string,
		uint8_t data_index, uint8_t data_length)
{
	if (tstring_index_of_char("dMyHms", specifier) != -1)
	{
		uint16_t data_value = 0;

		switch (specifier)
		{
			case 'd':
				data_value = datetime->Day;
				break;
			case 'M':
				data_value = datetime->Month;
				break;
			case 'y':
				data_value = datetime->Year;
				if (4 == data_length)
				{
					data_value += 2000;
				}
				break;
			case 'H':
				data_value = datetime->Hour;
				break;
			case 'm':
				data_value = datetime->Minute;
				break;
			case 's':
				data_value = datetime->Second;
				break;
			default:
				break;
		}

		/* TODO kada je format vremena H:mm, ako je sat veci od 9 nastaje problem jer uzima samo desetice
		testirati i m, s i ostale specifiere kad su samo jedno slovo a vrijednost veæa od 9 */
//		if (9 < data_value && 2 > data_length)
//		{
//			data_length = 2;
//		}

		tstring_int_to_string(data_string, data_value);

		tstring_pad_left_char(data_string, data_length, '0');
	}
	else
	{
		memmove(data_string, format + data_index, data_length);
		data_string[data_length] = 0;
	}

	tstring_insert(string, strlen(string), data_string);
}

static void string_value_to_datetime(char_t * string, RTC_DateTime * datetime,
		const char_t specifier, char_t * data_string, uint8_t data_index, uint8_t data_length)
{
	memmove(data_string, string + data_index, data_length);
	//data_string[data_length + 1] = 0; /* ovo nije potrebno jer je data_string inicijalizovan na 0 */
	uint16_t data_value = tstring_string_to_int(data_string);

	switch (specifier)
	{
		case 'd':
			datetime->Day = data_value;
			break;
		case 'M':
			datetime->Month = data_value;
			break;
		case 'y':
			if (data_length == 4)
			{
				data_value -= 2000;
			}
			datetime->Year = data_value;
			break;
		case 'H':
			datetime->Hour = data_value;
			break;
		case 'm':
			datetime->Minute = data_value;
			break;
		case 's':
			datetime->Second = data_value;
			break;
		default:
			break;
	}
}

static bool_t datetime_string_convert(char_t * string, RTC_DateTime * datetime,
									  const char_t * format, bool_t to_string)
{
	if (to_string)
	{
		/* invalid datetime cannot be converted to string */
		if (!tdatetime_validate(datetime))
		{
			return false;
		}

		/* clear string */
		string[0] = 0;
	}
	else
	{
		/* clear datetime */
		tdatetime_new(datetime, 0, 1, 1, 0, 0, 0);
	}

	uint8_t format_len = strlen(format);

	uint8_t i;
	for (i = 0; i < format_len; ++i)
	{
		const char_t specifier = format[i];

		/* skip invalid specifiers when converting to datetime */
		if (!to_string && tstring_index_of_char("dMyHms", specifier) == -1)
		{
			/* input string and format do not match */
			if (string[i] != format[i])
			{
				return false;
			}

			continue;
		}

		uint8_t data_index = i;
		uint8_t data_length = 1;
		while (format[i] == format[i + 1])
		{
			i++;
			data_length++;
		}

		/* specifier može biti 1 ili 2 osim za godinu (y) */
		if ((tstring_index_of_char("dMHms", specifier) != -1 && 2 < data_length) ||
			(tstring_index_of_char("y", specifier) != -1 && !(2 == data_length || 4 == data_length)))
		{
			string[0] = 0;
			return false;
		}

		char_t data_string[5] = { 0 }; /* yyyy0 */

		if (to_string)
		{
			datetime_value_to_string(string, datetime, format, specifier,
					data_string, data_index, data_length);
		}
		else
		{
			string_value_to_datetime(string, datetime, specifier,
					data_string, data_index, data_length);
		}
	}

	if (!to_string)
	{
		/* return false if datetime is invalid after conversion from string */
		if (!tdatetime_validate(datetime))
		{
			return false;
		}
	}

	return true;
}

// TODO provjeriti uspjesnost konverzije gdje god se koriste ove tri funkcije ispod
bool_t tdatetime_dt_to_str_exact(char_t * string, const RTC_DateTime * datetime,
								 const char_t * format)
{
	return datetime_string_convert(string, (RTC_DateTime *)datetime, format, true);
}

bool_t tdatetime_str_to_dt_exact(RTC_DateTime * datetime, const char_t * string,
								 const char_t * format)
{
	return datetime_string_convert((char_t *)string, datetime, format, false);
}

bool_t tdatetime_dt_to_str(char_t * string, const RTC_DateTime * datetime, char_t * datetime_format)
{
	return tdatetime_dt_to_str_exact(string, datetime, datetime_format);
}

void tdatetime_date_copy(RTC_DateTime * to, const RTC_DateTime * from)
{
	to->Day = from->Day;
	to->Month = from->Month;
	to->Year = from->Year;
}

void tdatetime_copy(RTC_DateTime * to, const RTC_DateTime * from)
{
	to->DayOfWeek = from->DayOfWeek;
	to->Second = from->Second;
	to->Minute = from->Minute;
	to->Hour = from->Hour;
	to->Day = from->Day;
	to->Month = from->Month;
	to->Year = from->Year;
}

int8_t tdatetime_compare(const RTC_DateTime * date1, const RTC_DateTime * date2)
{
	/* ova funkcija treba da vrati:
	 * -1 ako je prvi datum manji od drugog,
	 *  1 ako je prvi datum veæi od drugog i
	 *  0 ako su identièni*/

	if (date1->Year > date2->Year) return 1;
	else if (date1->Year < date2->Year) return -1;
	else
	{
		if (date1->Month > date2->Month) return 1;
		else if (date1->Month < date2->Month) return -1;
		else
		{
			if (date1->Day > date2->Day) return 1;
			else if (date1->Day < date2->Day) return -1;
			else
			{
				if (date1->Hour > date2->Hour) return 1;
				else if (date1->Hour < date2->Hour) return -1;
				else
				{
					if (date1->Minute > date2->Minute) return 1;
					else if (date1->Minute < date2->Minute) return -1;
					else
					{
						if (date1->Second > date2->Second) return 1;
						else if (date1->Second < date2->Second) return -1;
						else
						{
							return 0;
						}
					}
				}
			}
		}
	}
}

static void datetime_to_sec(RTC_DateTime * dt, uint32_t * p_seconds)
{
	uint16_t MONTH_DAYS[] = { 0U, 0U, 31U, 59U, 90U, 120U, 151U,
							  181U, 212U, 243U, 273U, 304U, 334U }; /* Leap-year */

	uint32_t seconds; /* Number of seconds till 1.1.2000 */
	if (tdatetime_validate(dt))
	{
		/* Compute number of days from 2000 till given year */
		seconds = (dt->Year * 365U) + ((dt->Year + 3U) / 4U);
		/* Add number of days till given month */
		seconds += MONTH_DAYS[dt->Month];
		/* Add days in given month */
		seconds += dt->Day;
		 /* For un-leap year or month <= 2, decrement day counter */
		if ((dt->Year & 3U) || (dt->Month <= 2U))
		{
			seconds--;
		}

		seconds = (seconds * 86400U) + (dt->Hour * 3600U)
				+ (dt->Minute * 60U) + dt->Second;

		*p_seconds = seconds;
	}
}

static void sec_to_datetime(RTC_DateTime * dt, uint32_t seconds)
{
	const uint8_t ULY[] = {0U,31U,28U,31U,30U,31U,30U,31U,31U,30U,31U,30U,31U}; /* Un-leap-year */
	//const uint8_t  LY[] = {0U,31U,29U,31U,30U,31U,30U,31U,31U,30U,31U,30U,31U}; /* Leap-year */

	uint32_t days;

	days = seconds / 86400U;
	seconds = seconds % 86400U; /* Seconds left */
	dt->Hour = seconds / 3600U; /* Hours */
	seconds = seconds % 3600u; /* Seconds left */
	dt->Minute = seconds / 60U; /* Minutes */
	dt->Second = seconds % 60U; /* Seconds */
	dt->DayOfWeek = (days + 6U) % 7U; /* Day of week */
	dt->Year = (4U * (days / ((4U * 365U) + 1U))); /* Year */
	days = days % ((4U * 365U) + 1U);

	if (days == ((0U * 365U) + 59U))
	{ /* 59 */
		dt->Day = 29U;
		dt->Month = 2U;
		return;
	}
	else if (days > ((0U * 365U) + 59U))
	{
		days--;
	}

	uint32_t x = days / 365U;
	dt->Year += x;
	days -= x * 365U;
	for (x = 1U; x <= 12U; x++)
	{
		if (days < ULY[x])
		{
			dt->Month = x;
			break;
		}
		else
		{
			days -= ULY[x];
		}
	}

	dt->Day = days + 1U;
}

static uint32_t add_operation(uint32_t dt_sec, uint32_t seconds)
{
	dt_sec += seconds;

	return dt_sec;
}

static uint32_t substract_operation(uint32_t dt_sec, uint32_t seconds)
{
	dt_sec -= seconds;

	return dt_sec;
}

static void add_substract_seconds(RTC_DateTime * dt, uint32_t seconds,
								  uint32_t (*operation)(uint32_t, uint32_t))
{
	uint32_t dt_sec = 0;
	datetime_to_sec(dt, &dt_sec);

	dt_sec = operation(dt_sec, seconds);

	sec_to_datetime(dt, dt_sec);
}

static void add_seconds(RTC_DateTime * dt, uint32_t seconds)
{
	add_substract_seconds(dt, seconds, add_operation);
}

void tdatetime_add_days(RTC_DateTime * dt, uint16_t days)
{
	add_seconds(dt, (uint32_t)(days * 86400));
}

void tdatetime_add_hours(RTC_DateTime * dt, uint16_t hours)
{
	add_seconds(dt, (uint32_t)(hours * 3600));
}

void tdatetime_add_minutes(RTC_DateTime * dt, uint16_t minutes)
{
	add_seconds(dt, (uint32_t)(minutes * 60));
}

void tdatetime_add_seconds(RTC_DateTime * dt, uint16_t seconds)
{
	add_seconds(dt, seconds);
}

static void substract_seconds(RTC_DateTime * dt, uint32_t seconds)
{
	add_substract_seconds(dt, seconds, substract_operation);
}

void tdatetime_substract_hours(RTC_DateTime * dt, uint16_t hours)
{
	substract_seconds(dt, (uint32_t)(hours * 3600));
}

void tdatetime_substract_minutes(RTC_DateTime * dt, uint16_t minutes)
{
	substract_seconds(dt, (uint32_t)(minutes * 60));
}

void tdatetime_difference(RTC_DateTime * difference,
						  RTC_DateTime * dt1,
						  RTC_DateTime * dt2)
{
	uint32_t dt1_sec = 0;
	uint32_t dt2_sec = 0;

	datetime_to_sec(dt1, &dt1_sec);
	datetime_to_sec(dt2, &dt2_sec);

	uint32_t difference_sec = 0;
	if (dt1_sec > dt2_sec)
	{
		difference_sec = dt1_sec - dt2_sec;
	}
	else
	{
		difference_sec = dt2_sec - dt1_sec;
	}

	sec_to_datetime(difference, difference_sec);
}
