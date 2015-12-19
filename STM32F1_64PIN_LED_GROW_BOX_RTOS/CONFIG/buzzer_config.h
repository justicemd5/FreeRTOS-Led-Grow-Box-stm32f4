#ifndef BUZZER_CONFIG_H_
#define BUZZER_CONFIG_H_

#include "settings.h"

#define BUZZER_PORT					GPIOA
#define BUZZER_PIN					GPIO_Pin_2
#define BUZZER_PIN_ON  				gpio_set_pin(BUZZER_PORT, BUZZER_PIN)
#define BUZZER_PIN_OFF  			gpio_reset_pin(BUZZER_PORT, BUZZER_PIN)

#define BUZZER_TIMER_CHANNEL		(uint8_t)14


#endif /* END OF BUZZER */
