/*
 * timeout.h
 *
 *  Created on: Jan 6, 2014
 *      Author: nihad
 */

#ifndef TIMEOUT_H_
#define TIMEOUT_H_

#include "stdint.h"

void timeout_Waitms(uint32_t waitms);
void timeout_Waitus(uint32_t waitus);

void timeout_AsyncWaitms(uint8_t timer, uint32_t waitms);
void timeout_AsyncWaitus(uint8_t timer, uint32_t waitus);
uint8_t timeout_AsyncIsElapsed(uint8_t timer);
void timeout_AsyncStop(uint8_t timer);

uint8_t timeout_WaitOrExpire_ms(uint32_t * reg, uint32_t flag, uint32_t waitms);
uint8_t timeout_WaitOrExpire_us(uint32_t * reg, uint32_t flag, uint32_t waitus);

void timeout_AsyncISRWaitms(uint8_t timer, uint32_t waitms);
void timeout_AsyncISRWaitus(uint8_t timer, uint32_t waitus);

#endif /* TIMEOUT_H_ */
