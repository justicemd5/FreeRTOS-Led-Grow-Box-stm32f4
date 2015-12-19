
#include "buzzer.h"
#include "timeout.h"

ERROR_CODE DO_NOT_OPTIMIZE buzzer_Beep(uint32_t miliseconds, uint32_t frequency)
{
	ERROR_CODE err = NO_ERROR;

	if (0 != miliseconds && 0 != frequency)
	{
		uint32_t period;
		period = 1000000/frequency;

		timeout_AsyncWaitms(BUZZER_TIMER_CHANNEL,miliseconds);

		while(!timeout_AsyncIsElapsed(BUZZER_TIMER_CHANNEL))
		{
			timeout_Waitus(period/2);
			BUZZER_PIN_ON;
			timeout_Waitus(period/2);
			BUZZER_PIN_OFF;
		}
		BUZZER_PIN_OFF;
	}

	return err;
}

void buzzer_beep_warning()
{
	buzzer_Beep(400, 700);
}

void buzzer_beep_info()
{
	buzzer_Beep(100, 700);
}

void buzzer_beep_error()
{
	buzzer_Beep(400, 5000);
}

void buzzer_beep_terminal()
{
	buzzer_Beep(80, 4000);
	timeout_Waitms(50);
	buzzer_Beep(80, 4000);
}
