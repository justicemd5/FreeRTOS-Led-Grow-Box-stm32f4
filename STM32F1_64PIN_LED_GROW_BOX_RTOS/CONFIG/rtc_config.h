#ifndef RTC_CONFIG_H_
#define RTC_CONFIG_H_

#include "settings.h"

//#define RTC_ALARM_MASK	RTC_AlarmMask_None

typedef enum
{
	DAYLIGHT_CHANGE = 0,
	INVERVAL_15_MINUTES_ELAPSED,
	TRANSFER_FILES,
	KEYBOARD_TIMEOUT
} datetime_event_e;

#define RTC_EVENTS_COUNT		4
#define RTC_EVENT_ENUM_STRUCT	datetime_event_e

/* RTC SETTINGS */
#define RTC_CLOCK_SOURCE_LSE
#ifndef RTC_CLOCK_SOURCE_LSE
#define RTC_CLOCK_SOURCE_LSI
#endif

#define RTC_INITIALIZATION_BACKUP_REGISTER 		RTC_BKP_DR0
#define RTC_INITIALIZED_FLAG					0xA3
/* END OF RTC SETTINGS */

#endif
