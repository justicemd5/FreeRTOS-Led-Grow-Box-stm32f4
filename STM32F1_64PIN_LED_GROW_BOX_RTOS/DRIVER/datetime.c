///*
// * datetime.c
// *
// *  Created on: Nov 27, 2013
// *      Author: Administrator
// */
//
//#include "datetime.h"
//#include "tdatetime.h"
//#include "rtc_config.h"
//
////static uint8_t forceHour;
//
//typedef struct
//{
//	RTC_DateTime 	datetime;
//	uint8_t			a_type;
//} alarm_list_struct;
//
//static alarm_list_struct alarm_list[RTC_EVENTS_COUNT];
//
//static alarm_list_struct next_alarm;
//
//static uint8_t CompareDates(RTC_DateTime * dt, uint8_t month, uint8_t day, uint8_t hour);
//static void datetime_reset(RTC_DateTime * dt);
//
//static uint8_t CompareDates(RTC_DateTime * dt, uint8_t month, uint8_t day, uint8_t hour)
//{
//	if (dt->Month == month)
//	{
//		if (dt->Day == day)
//		{
//			return (dt->Hour < hour);
//		}
//		else
//		{
//			return (dt->Day < day);
//		}
//	}
//	else
//	{
//		return (dt->Month < month);
//	}
//	return 0;
//}
//
//static void datetime_reset(RTC_DateTime * dt)
//{
//	dt->Year = 0;
//	dt->Month = 1;
//	dt->Day = 1;
//	dt->Hour = 0;
//	dt->Minute = 0;
//	dt->Second = 0;
//}
//
//ERROR_CODE datetime_get(RTC_DateTime * dateTime)
//{
//	return rtc_get_time(dateTime);
//}
//
//ERROR_CODE datetime_set(RTC_DateTime * dateTime)
//{
//	ERROR_CODE err = ERROR_FISCAL_INVALID_DATETIME;
//
//	if (tdatetime_validate(dateTime))
//	{
//		err = rtc_set_time(dateTime);
//	}
//
//	datetime_alarmlist_clear();
//
//	return err;
//}
//
//ERROR_CODE datetime_enable_dst(uint8_t forceHour)
//{
//	uint16_t day, year;
//
//	RTC_DateTime dst, currentDateTime;
//
//	rtc_get_time(&currentDateTime);
//
//	if (forceHour) currentDateTime.Hour++;
//	//find the last Sunday in March
//	//month = 3;
//	year = 2000 + currentDateTime.Year;
//	day = 31 - ((((5 * year) / 4) + 4) % 7);	//zadnja nedjelja u martu
//
//	//da li je dt prije ili poslije dst
//	if(CompareDates(&currentDateTime,3,(uint8_t)day,2))
//	{
//		//to je datum prije dst
//		dst.Year = currentDateTime.Year;
//		dst.Month = 3;
//		dst.Day =  (uint8_t)day;
//		dst.Hour = 2;
//		dst.Minute = 0;
//		dst.Second = 0;
//		dst.DayOfWeek = 0;
//	}
//	else
//	{
//		//sljede�i slu�aj izme�u 3 i 10 mjeseca
//		day = 31 - ((((5 * year) / 4) + 1) % 7);	//zadnja nedjelja u oktobru
//
//		if(CompareDates(&currentDateTime,10,(uint8_t)day,3))
//		{
//			//to je datum prije dst
//			dst.Year = currentDateTime.Year;
//			dst.Month = 10;
//			dst.Day =  (uint8_t)day;
//			dst.Hour = 3;
//			dst.Minute = 0;
//			dst.Second=0;
//			dst.DayOfWeek = 0;
//		} else
//		{
//			//sljede�i slu�aj izme�u 10 i 12 mjeseca godine
//			year++;
//			day = 31 - ((((5 * year) / 4) + 4) % 7);	//zadnja nedjelja u martu
//			//to je datum prije dst
//			dst.Year = (uint8_t)(year-2000);
//			dst.Month = 3;
//			dst.Day =  (int8_t)day;
//			dst.Hour = 2;
//			dst.Minute = 0;
//			dst.Second=0;
//			dst.DayOfWeek = 0;
//		}
//	}
//	//write alarm
////	rtc_set_alarm(&dst, RTC_ALARM_MASK);
////	tdatetime_copy(&next_alarm, &dst);
//
//	datetime_alarmlist_add(&dst,0);
//
//	return NO_ERROR;
//}
//
//ERROR_CODE datetime_change_dst(RTC_DateTime * dst)
//{
//	uint8_t forceHour = 0;
//
//	if (dst->Month == 3)
//	{
//		dst->Hour++;
//	}
//	else if (dst->Month == 10)
//	{
//		dst->Hour--;
//		forceHour = 1;			//fix problem with returning from 3 to 2 am
//	}
//	datetime_set(dst);
//	datetime_enable_dst(forceHour);
//	return NO_ERROR;
//}
//
//ERROR_CODE datetime_enable_alarm(RTC_DateTime* dateTime)
//{
//	return rtc_set_alarm(dateTime, RTC_ALARM_MASK);
//}
//
//RTC_DateTime * datetime_alarm_get(void)
//{
//	return &next_alarm.datetime;
//}
//
//void datetime_alarmlist_add(RTC_DateTime* dateTime, uint8_t alarmtype)
//{
////	uint8_t i;
////	RTC_DateTime current;
////	rtc_get_time(&current);
////
////	for (i=0;i<RTC_EVENTS_COUNT;++i)
////	{
////		//dst always use index 0
////		if (alarmtype == 0)
////		{
////			alarm_list[0].a_type = alarmtype;
////			tdatetime_copy(&alarm_list[0].datetime,dateTime);
////			break;
////		}
////		else
////		{
////			if (i > 0)
////			{
////				if (alarm_list[i].datetime.Year == 0 || tdatetime_compare(&current, &alarm_list[i].datetime) == 1)
////				{
////					alarm_list[i].a_type = alarmtype;
////					tdatetime_copy(&alarm_list[i].datetime,dateTime);
////					break;
////				}
////			}
////		}
////
////	}
//
//	if(alarmtype < RTC_EVENTS_COUNT)
//	{
//		alarm_list[alarmtype].a_type = alarmtype;
//		tdatetime_copy(&alarm_list[alarmtype].datetime,dateTime);
//	}
//
//
//	datetime_alarmlist_set_next();
//
//}
//
//void datetime_alarmlist_remove(uint8_t alarmtype)
//{
//	alarm_list[alarmtype].a_type = 0;
//	datetime_reset(&alarm_list[alarmtype].datetime);
//
//	datetime_alarmlist_set_next();
//}
//
//void datetime_alarmlist_clear()
//{
//	uint8_t i;
//	for (i=0;i<RTC_EVENTS_COUNT;++i)
//	{
//		alarm_list[i].a_type = 0;
//		datetime_reset(&alarm_list[i].datetime);
//	}
//}
//
//void datetime_alarmlist_set_next(void)
//{
//	uint8_t i;
//	RTC_DateTime current;
//
//	next_alarm.datetime.Year = 0;
//	rtc_get_time(&current);
//
//	for (i=0;i<RTC_EVENTS_COUNT;++i)
//	{
//		if (tdatetime_compare(&alarm_list[i].datetime, &current) == 1)
//		{
//			if (next_alarm.datetime.Year == 0 || tdatetime_compare(&next_alarm.datetime, &alarm_list[i].datetime) == 1)
//			{
//				tdatetime_copy(&next_alarm.datetime,&alarm_list[i].datetime);
//				next_alarm.a_type = alarm_list[i].a_type;
//			}
//		}
//		else
//		{
//			//elapsed timer so remove it from the list
//			alarm_list[i].a_type = 0;
//			datetime_reset(&alarm_list[i].datetime);
//		}
//	}
//
//	if (next_alarm.datetime.Year > 0)
//	{
//		rtc_set_alarm(&next_alarm.datetime, RTC_ALARM_MASK);
//	} else {
//		//should never been here
//		i=0;
//	}
//
//}
//
//void datetime_alarmlist_occured()
//{
//	alarm_list_struct alarmOccured;
//
//	alarmOccured.a_type = next_alarm.a_type;
//	tdatetime_copy(&alarmOccured.datetime,&next_alarm.datetime);
//
//	if (next_alarm.a_type == 0)
//	{
//		RTC_DateTime current;
//		datetime_get(&current);
//		//fixing st problem with not updating rtc structure after sleep
//		uint8_t seconds = current.Second;
//		while(seconds == current.Second)
//		{
//			datetime_get(&current);
//		}
//		datetime_change_dst(&current);
//		return;		//prevent recursion
//	}
//
//	datetime_alarmlist_set_next();
//
//	if (alarmOccured.datetime.Year > 0)
//	{
//		datetime_alarm_handler(&alarmOccured.datetime, alarmOccured.a_type);
//	}
//}
//
//__WEAK void datetime_alarm_handler(RTC_DateTime* dateTime, uint8_t alarmtype){}
