#ifndef BUZZER_H_
#define BUZZER_H_

#include "buzzer_config.h"

ERROR_CODE buzzer_Beep(uint32_t miliseconds, uint32_t frequency);
void buzzer_beep_warning();
void buzzer_beep_info();
void buzzer_beep_error();
void buzzer_beep_terminal();

#endif
