#include "delay.h"
#include "stm32f0xx_it.h"

#define DELAY_TIMERS		5
#define DELAY_MAX_VALUE		SysTick_LOAD_RELOAD_Msk

typedef struct
{
	volatile uint8_t timer_id;
	volatile uint32_t start;
	volatile uint32_t timeout;
} timer;



//static timer delay_find_free_timer(); unused
static void delay_start(uint32_t ticks, uint8_t irq_enable);
static void delay_ticks(uint32_t ticks, uint8_t stop);
static void delay_timeout(uint32_t timeout, uint32_t divider, uint8_t stop);


extern uint32_t SystemCoreClock;

static timer timers[DELAY_TIMERS];
static volatile uint32_t prescaler= 0;

// unused
//static timer delay_find_free_timer()
//{
//	uint8_t i;
//	for(i=0;i<DELAY_TIMERS;i++)
//	{
//		if (timers[i].timeout == 0)
//		{
//			return timers[i];
//		}
//	}
//}

static void delay_start(uint32_t ticks, uint8_t irq_enable)
{
	if (irq_enable)
	{
		SysTick->CTRL = SysTick_CTRL_TICKINT_Msk;
	} else {
		SysTick->CTRL  =  0;
	}
	SysTick->LOAD  = ticks-1;
	SysTick->VAL   = 0;
	SysTick->CTRL  |= SysTick_CTRL_ENABLE_Msk
					| SysTick_CTRL_CLKSOURCE_Msk;
}

static void delay_ticks(uint32_t ticks, uint8_t stop)
{
	uint32_t i;

	delay_start(ticks, !stop);

	if (stop)
	{
		i = 0;
		while(i == 0)
		{
			i = (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk);
		}

		delay_stop();
	}

}
static void delay_timeout(uint32_t timeout, uint32_t divider, uint8_t stop)
{
	uint32_t ticks;

	prescaler = 0;
	ticks = (timeout * (SystemCoreClock / divider)) / (prescaler + 1);

	while (ticks > DELAY_MAX_VALUE)
	{
		prescaler++;
		ticks = (timeout * (SystemCoreClock / divider)) / (prescaler + 1);
	}

	if (prescaler && stop)
	{
		do
		{
			delay_ticks(ticks,true);
		} while (prescaler--);
	} else if (stop)
	{
		delay_ticks(ticks,true);
	} else {
		delay_ticks(ticks,false);
	}
}

void delay_init()
{
	uint8_t i;
	for(i=0;i<DELAY_TIMERS;i++)
	{
		timers[i].timer_id = i;
		timers[i].start =0;
		timers[i].timeout = 0;
	}
}

void delay_us(uint32_t timeout)
{
	delay_timeout(timeout,1000000UL,true);
}

void delay_ms(uint32_t timeout)
{
	delay_timeout(timeout,1000UL,true);
}

uint8_t delay_start_us(uint32_t timeout)
{
	delay_timeout(timeout,1000000UL,false);
	return 1;
}
uint8_t delay_start_ms(uint32_t timeout)
{
	delay_timeout(timeout,1000UL,false);
	return 1;
}

uint8_t delay_is_elapsed(uint8_t timer)
{
	if(prescaler) return 0;

	if (SysTick->CTRL & SysTick_CTRL_ENABLE_Msk)
	{
		if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
		{
			SysTick->CTRL = 0;
			return 1;
		} else
		{
			return 0;
		}
	} else
	{
		return 1;
	}
}
void delay_stop()
{
	SysTick->CTRL  =  0;
}

//void SysTick_Handler(void)
//{
////	if (prescaler)
////	{
////		uint32_t dummy = SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk;
////		prescaler--;
////
////		(void)dummy; // suppress compiler warning: unused variable
////	}
////	else
////	{
////		SysTick->CTRL=0;
////	}
//}

void delay_start_only()
{
	SysTick->CTRL = 0;
	SysTick->LOAD = (SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
	SysTick->VAL = 0;                                          /* Load the SysTick Counter Value */
	SysTick->CTRL =	SysTick_CTRL_CLKSOURCE_Msk |
					SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
}
void delay_get_time_us(uint32_t * value)
{
	*value = (uint32_t)((SysTick_LOAD_RELOAD_Msk -SysTick->VAL) / (SystemCoreClock / 1000000UL));
	SysTick->CTRL =0;
}

