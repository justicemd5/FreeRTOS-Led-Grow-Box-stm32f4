/*
 * pit.h
 *
 *  Created on: Jan 6, 2014
 *      Author: nihad
 */

#ifndef PIT_H_
#define PIT_H_

#include "pit_config.h"

void pit_init(uint8_t enable);
void pit_start(uint8_t channel, uint32_t usTimeout, uint8_t isrEnable);
uint8_t pit_timeout(uint8_t channel);
void pit_stop(uint8_t channel);

#endif /* PIT_H_ */
