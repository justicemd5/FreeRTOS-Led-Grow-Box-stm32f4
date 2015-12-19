/*
 * timeout.c
 *
 *  Created on: Jan 6, 2014
 *      Author: nihad
 */

#include "timeout.h"
#include "pit.h"

void timeout_Waitms(uint32_t waitms)
{
	timeout_Waitus(waitms*1000U);
}

void timeout_Waitus(uint32_t waitus)
{
	pit_start(0,waitus,0);
	while(!pit_timeout(0));
	pit_stop(0);
}

void timeout_AsyncWaitms(uint8_t timer, uint32_t waitms)
{
	timeout_AsyncWaitus(timer, waitms*1000U);
}
void timeout_AsyncWaitus(uint8_t timer, uint32_t waitus)
{
	pit_start(timer,waitus,0);
}
uint8_t timeout_AsyncIsElapsed(uint8_t timer)
{
	volatile uint8_t ret;
	ret = pit_timeout(timer);
	if(ret)
	{
		pit_stop(timer);
	}
	
	return ret;
}
void timeout_AsyncStop(uint8_t timer)
{
	pit_stop(timer);
}
uint8_t timeout_WaitOrExpire_ms(uint32_t * reg, uint32_t flag, uint32_t waitms)
{
	return timeout_WaitOrExpire_us(reg,flag,waitms*1000U);
}

uint8_t timeout_WaitOrExpire_us(uint32_t * reg, uint32_t flag, uint32_t waitus)
{
	pit_start(0,waitus,0);
	while(!pit_timeout(0) && !( *reg & flag));
	pit_stop(0);
	return ((*reg) & flag);	
}

void timeout_AsyncISRWaitms(uint8_t timer, uint32_t waitms)
{
	timeout_AsyncISRWaitus(timer, waitms*1000U);
}

void timeout_AsyncISRWaitus(uint8_t timer, uint32_t waitus)
{
	pit_start(timer,waitus,1);
}
