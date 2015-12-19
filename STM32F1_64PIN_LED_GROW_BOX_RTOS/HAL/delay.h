#ifndef DELAY_H_
#define DELAY_H_

#include "settings.h"

void delay_init();
void delay_us(uint32_t timeout);
void delay_ms(uint32_t timeout);

uint8_t delay_start_us(uint32_t timeout);
uint8_t delay_start_ms(uint32_t timeout);
uint8_t delay_is_elapsed(uint8_t timer);
void delay_stop();

void delay_start_only();
void delay_get_time_us(uint32_t * value);

#endif
