///*
// * pit.c
// *
// *  Created on: Jan 6, 2014
// *      Author: nihad
// */
//
//	/* -----------------------------------------------------------------------
//	In this example TIM7 counter clock (TIM7CLK) is set to APB1 clock (PCLK1), since
//	APB1 prescaler is set to 1 and TIM7 prescaler is set to 0.
//
//	In this example TIM7 input clock (TIM7CLK) is set to APB1 clock (PCLK1),
//	since APB1 prescaler is set to 1.
//	TIM7CLK = PCLK1 = HCLK = SystemCoreClock
//
//	With Prescaler set to 479 and Period to 24999, the TIM7 counter is updated each 250 ms
//	(i.e. and interrupt is generated each 250 ms)
//	 TIM7 counter clock = TIM7CLK /((Prescaler + 1)*(Period + 1))
//						= 48 MHz / ((25000)*(480))
//						= 4 Hz
//	 ==> TIM7 counter period = 250 ms
//
//	Note:
//	SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
//	Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
//	function to update SystemCoreClock variable value. Otherwise, any configuration
//	based on this variable will be incorrect.
//	----------------------------------------------------------------------- */
//
//#include "pit.h"
//
//static TIM_TypeDef* GetChannel(uint8_t channel);
//static void channel_clock_enable(TIM_TypeDef* channel);
//
//static TIM_TypeDef* GetChannel(uint8_t channel)
//{
//	if(channel == 0)
//	{
//		return TIM6;
//	}
//	else if(channel == 1)
//	{
//		return TIM7;
//	}
//	else if(channel == 2)
//	{
//		return TIM16;
//	}
//	else if(channel == 3)
//	{
//		return TIM1;
//	}
//	else if(channel == 14)
//	{
//		return TIM14;
//	}
//	else if(channel == 15)
//	{
//		return TIM15;
//	}
//	else if(channel == 23)
//	{
//		return TIM2;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//static void channel_clock_enable(TIM_TypeDef* channel)
//{
//	if (channel == TIM1)
//	{
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
//	}
//	else if (channel == TIM2)
//	{
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//	}
//	else if (channel == TIM6)
//	{
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
//	}
//	else if (channel == TIM7)
//	{
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
//	}
//	else if (channel == TIM14)
//	{
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
//	}
//	else if (channel == TIM15)
//	{
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);
//	}
//	else if (channel == TIM16)
//	{
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);
//	}
//}
//
//void pit_init(uint8_t enable)
//{
//
//
//}
//
//void DO_NOT_OPTIMIZE pit_start(uint8_t channel, uint32_t usTimeout, uint8_t isrEnable)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_TypeDef* TimCh;
//	uint32_t period, prescaler;
//
//	TimCh = GetChannel(channel);
//
//	TIM_DeInit(TimCh);
//	channel_clock_enable(TimCh);
//
//	//usTimeout -= 19;	//it takes 19 us at 48MHz to complete this function
//
//	if(TimCh != TIM2)
//	{
//		prescaler = usTimeout / 1365;
//		period = (48 * usTimeout) / (prescaler + 1);
//	}
//	else
//	{
//		prescaler = 47;
//		period = usTimeout;
//	}
//
//	/* Time base configuration */
//	TIM_TimeBaseStructure.TIM_Period = (uint32_t)period;
//	TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t)prescaler;
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInit(TimCh, &TIM_TimeBaseStructure);
//
//
//	TIM_ClearFlag(TimCh,TIM_FLAG_Update);
//	/* TIM Clear IT Pending Bit */
//	TIM_ClearITPendingBit(TimCh,TIM_IT_Update);
//	/* TIM Interrupts enable */
//	TIM_ITConfig(TimCh, TIM_IT_Update, ENABLE);
//
//
//	if (isrEnable)
//	{
//		if (channel == 0)
//		{
//			/* Enable the TIM6 gloabal Interrupt */
//			NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
//		} else
//		{
//			/* Enable the TIM7 gloabal Interrupt */
//			NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
//		}
//
//		NVIC_InitStructure.NVIC_IRQChannelPriority = 0x02;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
//	}
//
//	/* TIM enable counter */
//	TIM_Cmd(TimCh, ENABLE);
//
//
//}
//
//uint8_t DO_NOT_OPTIMIZE pit_timeout(uint8_t channel)
//{
//	TIM_TypeDef* TimCh = GetChannel(channel);
//
//	if (TimCh->CR1 & TIM_CR1_CEN)
//	{
//		return TIM_GetITStatus(TimCh,TIM_IT_Update);
//	} else
//	{
//		return 1;
//	}
//}
//
//void DO_NOT_OPTIMIZE pit_stop(uint8_t channel)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	TIM_TypeDef* TimCh = GetChannel(channel);
//
//	TIM_Cmd(TimCh,DISABLE);
//
//	TIM_ClearFlag(TimCh,TIM_FLAG_Update);
//	/* TIM Clear IT Pending Bit */
//	TIM_ClearITPendingBit(TimCh,TIM_IT_Update);
//	/* TIM Interrupts enable */
//	TIM_ITConfig(TimCh, TIM_IT_Update, DISABLE);
//
//	if(channel == 0)
//	{
//		/* Enable the TIM6 gloabal Interrupt */
//		NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
//	}
//	else if(channel == 1)
//	{
//		/* Enable the TIM7 gloabal Interrupt */
//		NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
//	}
//	else if(channel == 2)
//	{
//		NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;
//	}
//
//	else if(channel == 3)
//	{
//		NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
//	}
//	else if(channel == 14)
//	{
//		NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
//	}
//	else if(channel == 15)
//	{
//		NVIC_InitStructure.NVIC_IRQChannel = TIM15_IRQn;
//	}
//	else if(channel == 23)
//	{
//		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//	}
//
//	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x02;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
//
//	NVIC_Init(&NVIC_InitStructure);
//}
//
