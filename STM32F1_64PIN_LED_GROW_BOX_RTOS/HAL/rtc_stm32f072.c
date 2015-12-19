#include "rtc.h"
#include "timeout.h"
//
//// unused function
////static void rtc_reset_backup_registers()
////{
////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
////    PWR_BackupAccessCmd(ENABLE);
////	RCC_BackupResetCmd(ENABLE);
////	RCC_BackupResetCmd(DISABLE);
////}
//
//static uint8_t rtc_backup_register_flag_check(uint32_t backup_register, uint32_t flag)
//{
//	if(flag & RTC_ReadBackupRegister(backup_register))
//	{
//		return true;
//	}
//
//	return false;
//}
//
//static void rtc_set_backup_register_value(uint32_t backup_register, uint32_t new_value)
//{
//	RTC_WriteBackupRegister(backup_register, new_value);
//}
//
//
//static ERROR_CODE rtc_enable_oscillator()
//{
//	uint32_t timeout = 0x00FFFFFF;
//
//#if defined (RTC_CLOCK_SOURCE_LSI)  //LSI used as RTC source clock
//
//	RCC_LSICmd(ENABLE); // Enable the LSI OSC
//	while(RESET == RCC_GetFlagStatus(RCC_FLAG_LSIRDY) && timeout) //Wait till LSI is ready
//	{
//		timeout--;
//	}
//	if(0 == timeout)
//	{
//		return INIT_RTC_LSI_FAILED;
//	}
//#elif defined (RTC_CLOCK_SOURCE_LSE) //LSE used as RTC source clock
//
//	RCC_LSEConfig(RCC_LSE_ON); //Enable the LSE OSC
//	while(RESET == RCC_GetFlagStatus(RCC_FLAG_LSERDY) && timeout) //Wait till LSE is ready
//	{
//		timeout--;
//	}
//	if(0 == timeout)
//	{
//		return INIT_RTC_LSE_FAILED;
//	}
//#else
//#error Please select the RTC Clock source inside the rtc.h file
//#endif
//
//	return NO_ERROR;
//}
//
//ERROR_CODE rtc_init()
//{
//	ERROR_CODE err;
//	RTC_InitTypeDef  RTC_InitStructure;
//	RTC_TimeTypeDef  RTC_TimeStruct;
//	RTC_DateTypeDef  RTC_DateStruct;
//	ErrorStatus es = SUCCESS;
////	uint32_t clock_source; unused variable
//
//	//TODO
//	// provjeriti ovaj clock zbog sleepa
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); //Enable the PWR clock
//	PWR_BackupAccessCmd(ENABLE); //Allow access to RTC
//
//	err = rtc_enable_oscillator();
//	if(err)
//	{
//		return err;
//	}
//
//	if(rtc_backup_register_flag_check(RTC_INITIALIZATION_BACKUP_REGISTER, RTC_INITIALIZED_FLAG))
//	{
//		es = RTC_WaitForSynchro();
//		if(ERROR == es)
//		{
//			return INIT_RTC_SYNC_FAILED;
//		}
//
//		return NO_ERROR;
//	}
//
//	rtc_set_backup_register_value(RTC_INITIALIZATION_BACKUP_REGISTER, RTC_INITIALIZED_FLAG);
//
//#if defined (RTC_CLOCK_SOURCE_LSI)
//	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI); //Select the RTC Clock Source
//#elif defined (RTC_CLOCK_SOURCE_LSE)
//	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); //Select the RTC Clock Source
//#else
//#error Please select the RTC Clock source inside the rtc.h file
//#endif
//
//	RCC_RTCCLKCmd(ENABLE);
//	es = RTC_WaitForSynchro();
//	if(ERROR == es)
//	{
//		return INIT_RTC_SYNC_FAILED;
//	}
//
//#if defined (RTC_CLOCK_SOURCE_LSI)  //LSI used as RTC source clock
//	//Configure the RTC data register and RTC prescaler
//	//ck_spre(1Hz) = RTCCLK(LSI) /(AsynchPrediv + 1)*(SynchPrediv + 1)
//	RTC_InitStructure.RTC_AsynchPrediv = 0x63;
//	RTC_InitStructure.RTC_SynchPrediv  = 0x18F;
//	RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
//#elif defined (RTC_CLOCK_SOURCE_LSE) //LSE used as RTC source clock
//	//Configure the RTC data register and RTC prescaler
//	//ck_spre(1Hz) = RTCCLK(LSI) /(AsynchPrediv + 1)*(SynchPrediv + 1)
//	RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
//	RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
//	RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
//#else
//#error Please select the RTC Clock source inside the rtc.h file
//#endif
//
//	es = RTC_Init(&RTC_InitStructure);
//	if(ERROR == es)
//	{
//		return INIT_RTC_FAILED;
//	}
//
//	//PAZNJA PRI MIJENJANU INICIJALNOG VREMENA I DATUMA, IZ RAZLOGA #####
//	RTC_TimeStruct.RTC_H12     = RTC_H12_AM;
//	RTC_TimeStruct.RTC_Hours   = 0;
//	RTC_TimeStruct.RTC_Minutes = 0;
//	RTC_TimeStruct.RTC_Seconds = 0;
//	es = RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
//	if(ERROR == es)
//	{
//		return INIT_RTC_SET_TIME_FAILED;
//	}
//
//	//PAZNJA PRI MIJENJANU INICIJALNOG VREMENA I DATUMA, IZ RAZLOGA #####
//	RTC_DateStruct.RTC_Year = 14;
//	RTC_DateStruct.RTC_Month = 1;
//	RTC_DateStruct.RTC_Date = 1;
//	RTC_DateStruct.RTC_WeekDay = 0;
//	es = RTC_SetDate(RTC_Format_BIN,&RTC_DateStruct);
//	if(ERROR == es)
//	{
//		return INIT_RTC_SET_DATE_FAILED;
//	}
//
//
//	//RTC_DayLightSavingConfig(RTC_DayLightSaving_SUB1H, RTC_StoreOperation_Reset); //RAZLOG #####
//
//	es = RTC_WaitForSynchro(); //Wait for RTC APB registers synchronisation
//	if(ERROR == es)
//	{
//		return INIT_RTC_SYNC_FAILED;
//	}
//
//	return NO_ERROR;
//}
//
//ERROR_CODE rtc_DeInit()
//{
//	return NO_ERROR;
//}
//
//ERROR_CODE rtc_set_alarm(RTC_DateTime * TimePtr, uint32_t alarm_mask)
//{
//	EXTI_InitTypeDef EXTI_InitStructure;
//	RTC_AlarmTypeDef RTC_AlarmStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//
//	RTC_AlarmStructInit(&RTC_AlarmStructure);
//	RTC_ITConfig(RTC_IT_ALRA, DISABLE);
//	RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
//
//	//EXTI configuration
//	EXTI_ClearITPendingBit(EXTI_Line17);
//	EXTI_InitStructure.EXTI_Line = EXTI_Line17;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);
//
//	//Enable the RTC Alarm Interrupt
//	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x01;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//
//	//Set the alarm
//	RTC_AlarmStructure.RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
//	RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = TimePtr->Hour;
//	RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = TimePtr->Minute;
//	RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = TimePtr->Second;
//	RTC_AlarmStructure.RTC_AlarmDateWeekDay = TimePtr->Day;
//	RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
//	RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_None;
//	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure);
//
//	RTC_ITConfig(RTC_IT_ALRA, ENABLE);
//
//	if(ERROR == RTC_AlarmCmd(RTC_Alarm_A, ENABLE)) 	//nable the alarm
//	{
//		return RTC_SET_ALARM_FAILED;
//	}
//
//	RTC_ClearFlag(RTC_FLAG_ALRAF);
//	RTC_ClearITPendingBit(RTC_IT_ALRA);
//	EXTI_ClearITPendingBit(EXTI_Line17);
//
//	return NO_ERROR;
//}
//
//
//ERROR_CODE rtc_set_time(RTC_DateTime * TimePtr)
//{
//	ErrorStatus es;
//	RTC_TimeTypeDef  RTC_TimeStruct;
//	RTC_DateTypeDef  RTC_DateStruct;
//
//	RTC_TimeStruct.RTC_H12     = RTC_H12_AM;
//	RTC_TimeStruct.RTC_Hours   = TimePtr->Hour;
//	RTC_TimeStruct.RTC_Minutes = TimePtr->Minute;
//	RTC_TimeStruct.RTC_Seconds = TimePtr->Second;
//	es = RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
//	if(ERROR == es)
//	{
//		return RTC_SET_TIME_FAILED;
//	}
//
//	RTC_DateStruct.RTC_Year = TimePtr->Year;
//	RTC_DateStruct.RTC_Month = TimePtr->Month;
//	RTC_DateStruct.RTC_Date = TimePtr->Day;
//	RTC_DateStruct.RTC_WeekDay = 0;
//	es = RTC_SetDate(RTC_Format_BIN,&RTC_DateStruct);
//	if(ERROR == es)
//	{
//		return RTC_SET_DATE_FAILED;
//	}
//
//	return NO_ERROR;
//}
//
//ERROR_CODE rtc_get_time(RTC_DateTime * TimePtr)
//{
//	RTC_TimeTypeDef  RTC_TimeStruct;
//	RTC_DateTypeDef  RTC_DateStruct;
//
//	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
//	RTC_GetDate(RTC_Format_BIN,&RTC_DateStruct);
//
//	TimePtr->Hour = RTC_TimeStruct.RTC_Hours;
//	TimePtr->Minute = RTC_TimeStruct.RTC_Minutes;
//	TimePtr->Second = RTC_TimeStruct.RTC_Seconds;
//	TimePtr->Year = RTC_DateStruct.RTC_Year;
//	TimePtr->Month = RTC_DateStruct.RTC_Month;
//	TimePtr->Day = RTC_DateStruct.RTC_Date;
//
//	return NO_ERROR;
//}
//
//ERROR_CODE rtc_peripheral_test()
//{
//	RTC_DateTime date_time_1, date_time_2;
//
//	rtc_get_time(&date_time_1);
//
//	timeout_AsyncWaitms(0,1500);
//	while(!timeout_AsyncIsElapsed(0))
//	{
//		rtc_get_time(&date_time_2);
//		if(date_time_1.Second != date_time_2.Second) break;
//	}
//
//	timeout_AsyncStop(0);
//
//	if(date_time_1.Second == date_time_2.Second)
//	{
//		return TEST_RTC_FAILED;
//	}
//
//	return NO_ERROR;
//}
