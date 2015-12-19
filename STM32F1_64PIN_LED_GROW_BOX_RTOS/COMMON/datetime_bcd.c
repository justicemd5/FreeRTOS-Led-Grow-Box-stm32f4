//#include "fiscal_math.h"
#include "array.h"

void RTC_datetime_value_to_bcd(RTC_DateTime * datetime, uint8_t *bcd_date)
{
	bcd_date[0] = fiscal_math_int_to_BCD(datetime->Year);
	bcd_date[1] = 0;
	bcd_date[2] = fiscal_math_int_to_BCD(datetime->Day);
	bcd_date[3] = fiscal_math_int_to_BCD(datetime->Month);
	bcd_date[4] = fiscal_math_int_to_BCD(datetime->Hour);
	bcd_date[5] = 0;
	bcd_date[6] = fiscal_math_int_to_BCD(datetime->Second);
	bcd_date[7] = fiscal_math_int_to_BCD(datetime->Minute);
}
void RTC_datetime_value_to_short_bcd(RTC_DateTime * datetime, uint8_t *bcd_date)
{
	bcd_date[0] = fiscal_math_int_to_BCD(datetime->Hour);
 	bcd_date[1] = fiscal_math_int_to_BCD(datetime->Minute);
	bcd_date[2] = fiscal_math_int_to_BCD(datetime->Day);
	bcd_date[3] = fiscal_math_int_to_BCD(datetime->Month);
 	bcd_date[4] = fiscal_math_int_to_BCD(datetime->Year);
}
void bcd_value_to_RTC_datetime(uint8_t * datetime, RTC_DateTime * output)
{
	output->Year = fiscal_math_BCD_to_int(datetime[0]);
	output->Month = fiscal_math_BCD_to_int(datetime[3]);
	output->Day = fiscal_math_BCD_to_int(datetime[2]);
	output->Hour = fiscal_math_BCD_to_int(datetime[4]);
	output->Second = fiscal_math_BCD_to_int(datetime[6]);
	output->Minute = fiscal_math_BCD_to_int(datetime[7]);
}
