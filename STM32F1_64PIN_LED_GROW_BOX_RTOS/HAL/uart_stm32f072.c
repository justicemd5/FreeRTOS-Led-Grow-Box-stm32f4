///*
// * uart.c
// *
// *  Created on: Doc 30, 2013
// *      Author: nihad
// */
//#include "uart.h"
//#include "timeout.h"
//#include "peripheral.h"
//#include "uart_config.h"
//
////static ERROR_CODE uart_check_flag(UART_REG reg, uint32_t flag, uint32_t timeout);
//
//void uart_deinit()
//{
//	uart_close(USART1);
//	uart_close(USART2);
//	uart_close(USART3);
//	uart_close(USART4);
//}
//
//ERROR_CODE uart_open(UART_REG reg, uint32_t baudrate)
//{
//	USART_InitTypeDef USART_InitStructure;
//
//	ERROR_CODE error = uart_close(reg);
//
//	if (NO_ERROR == error)
//	{
//		//enable clock
//		if(reg == USART1)
//		{
//			RCC_APB2PeriphClockCmd(RCC_APB2ENR_USART1EN,ENABLE);
//		}
//		else if(reg == USART2)
//		{
//			RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART2EN, ENABLE);
//		}
//		else if(reg == USART3)
//		{
//			RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART3EN, ENABLE);
//		}
//		else if(reg == USART4)
//		{
//			RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART4EN, ENABLE);
//		}
//		else
//		{
//			error = GLOBAL_ERROR;
//		}
//	}
//
//	if (NO_ERROR == error)
//	{
//		USART_InitStructure.USART_BaudRate = baudrate;
//		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//		USART_InitStructure.USART_StopBits = USART_StopBits_1;
//		USART_InitStructure.USART_Parity = USART_Parity_No;
//		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//
//		USART_Init(reg, &USART_InitStructure);
//
//	//	USART_ITConfig(reg, USART_IT_TXE, ENABLE);
//	//	USART_ITConfig(reg, USART_IT_RXNE, ENABLE);
//
//		USART_Cmd(reg,ENABLE);
//	}
//
//	return error;
//}
//
//ERROR_CODE uart_close(UART_REG reg)
//{
//	USART_Cmd(reg,DISABLE);
//
//    //enable clock
//	if(reg == USART1)
//	{
//		RCC_APB2PeriphClockCmd(RCC_APB2ENR_USART1EN,DISABLE);
//	}
//	else if(reg == USART2)
//	{
//		RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART2EN, DISABLE);
//	}
//	else if(reg == USART3)
//	{
//		RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART3EN, DISABLE);
//	}
//	else if(reg == USART4)
//	{
//		RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART4EN, DISABLE);
//	}
//	else
//	{
//		return GLOBAL_ERROR;
//	}
//
//	return NO_ERROR;
//}
//
//ERROR_CODE uart_byte_write(UART_REG reg, uint8_t data)
//{
//	uint32_t timeout;
//
//	WAIT_FOR_FLAG_CHANGE_OR_TIMEOUT((reg->ISR & USART_FLAG_TXE) == RESET,timeout,UART_WRITE_TIMEOUT_US,UART_MODEM_WRITE_FAILED);
//
//	// Transmit Data
//	reg->TDR = (uint16_t)data & (uint16_t)0x01FF;
//
//	return NO_ERROR;
//
//}
//
//ERROR_CODE uart_wait_eow(UART_REG reg)
//{
//	/* Loop until the end of transmission */
//	/* The software must wait until TC=1. The TC flag remains cleared during all data
//	 transfers and it is set by hardware at the last frame’s end of transmission */
//	uint32_t timeout;
//
//	WAIT_FOR_FLAG_CHANGE_OR_TIMEOUT((reg->ISR & USART_FLAG_TC) == RESET,timeout,UART_WRITE_TIMEOUT_US,UART_MODEM_WRITE_FAILED);
//
//	reg->ICR |= USART_ICR_TCCF;
//
//	return NO_ERROR;
//
//}
//
//ERROR_CODE uart_byte_read(UART_REG reg, uint8_t * data)
//{
//	uint32_t timeout;
//
//	WAIT_FOR_FLAG_CHANGE_OR_TIMEOUT((reg->ISR & USART_FLAG_RXNE) == RESET,timeout,UART_WRITE_TIMEOUT_US,UART_NO_DATA);
//
//	if ((reg->ISR & USART_FLAG_RXNE) != RESET)
//	{
//		*data = (uint8_t)((uint16_t)(reg->RDR & (uint16_t)0x01FF));
//		return NO_ERROR;
//	} else {
//		return UART_NO_DATA;
//	}
//}
//
//ERROR_CODE uart_byte_timeout_read(UART_REG reg, uint32_t timeout_ms, uint8_t * data)
//{
//	if(timeout_ms)
//	{
//		timeout_AsyncWaitms(UART_TIMER_CHANNEL,timeout_ms);
//
//		while((reg->ISR & USART_FLAG_RXNE)== RESET && !timeout_AsyncIsElapsed(UART_TIMER_CHANNEL))
//		{
//			if (SLEEP_OCCURED) break;
//		}
//		timeout_AsyncStop(UART_TIMER_CHANNEL);
//	}
//
//	if(reg->ISR & USART_FLAG_RXNE)
//	{
//		*data = (uint8_t)((uint16_t)(reg->RDR & (uint16_t)0x01FF));
//
//		return NO_ERROR;
//	}
//	else
//	{
//		return UART_NO_DATA;
//	}
//
////	if (reg->ISR & USART_FLAG_RXNE == RESET)
////	{
////		timeout_AsyncWaitus(0, timeout_us);
////
////		while (!timeout_AsyncIsElapsed(0) && (reg->ISR & USART_FLAG_RXNE == RESET))
////		{
////			if (SLEEP_OCCURED) break;
////		}
////
////		timeout_AsyncStop(0);
////	}
////
////
////	//if (SLEEP_OCCURED) return SLEEP_OCCURED_ERROR;
////
////	if (reg->ISR & USART_FLAG_RXNE)
////	{
////		*data = (uint8_t)((uint16_t)(reg->RDR & (uint16_t)0x01FF));
////		return NO_ERROR;
////	}
////	return UART_NO_DATA;
//}
//void uart_toggle_irq(UART_REG reg, uint32_t interupt, uint8_t enable)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//
//	if(USART1 == reg)
//	{
//		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPriority = 0x02;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = enable;
//		NVIC_Init(&NVIC_InitStructure);
//
//		USART_ITConfig(reg, interupt, enable);
//	}
//}
//
//void uart_handle_overrun(UART_REG reg)
//{
//	reg->ICR = USART_FLAG_ORE;
//}
//
//void uart_flush(UART_REG reg)
//{
//	reg->RQR |= USART_RQR_RXFRQ;	//emtpy read register
//}
//
////static ERROR_CODE uart_check_flag(UART_REG reg, uint32_t flag, uint32_t timeout)
////{
////	timeout_AsyncWaitus(UART_TIMER_CHANNEL, timeout);
////
////	while((RESET == USART_GetFlagStatus(reg, flag)) && !timeout_AsyncIsElapsed(UART_TIMER_CHANNEL));
////
////	timeout_AsyncStop(UART_TIMER_CHANNEL);
////
//////	if (SLEEP_OCCURED)
//////	{
//////		return SLEEP_ERROR;
//////	}
////	if(RESET == USART_GetFlagStatus(reg, flag))
////	{
////		return UART_NO_DATA;
////	}
////	return NO_ERROR;
////}
//void uart_dma_deinit()
//{
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, DISABLE);
//}
//
//void uart_dma_init()
//{
//	uart_dma_deinit();
//
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//}
//
//ERROR_CODE
//uart_dma_write
//(
//	const UART_REG reg,
//
//	const uint8_t *const data,
//
//	const uint16_t data_size
//)
//{
//	uart_dma_stop(reg);
//
//	DMA_InitTypeDef DMA_InitStructure;
//
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//	DMA_InitStructure.DMA_MemoryDataSize =  DMA_MemoryDataSize_Byte;
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//	DMA_InitStructure.DMA_BufferSize = data_size;
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(reg->TDR));
//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)data;
//	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
//
//	USART_DMACmd(reg, USART_DMAReq_Tx, ENABLE);
//
//#if(defined(USE_UART1))
//	if(USART1 == reg)
//	{
//		if(!USART1_MAPPED)
//		{
//			DMA_ClearITPendingBit(DMA1_FLAG_GL4);
//
//			DMA_Init(DMA1_Channel4, &DMA_InitStructure);
//
//			DMA_Cmd(DMA1_Channel4, ENABLE);
//		}
//		else
//		{
//			DMA_ClearITPendingBit(DMA1_FLAG_GL2);
//
//			DMA_Init(DMA1_Channel2, &DMA_InitStructure);
//
//			DMA_Cmd(DMA1_Channel2, ENABLE);
//		}
//	}
//	else
//#endif
//	{
//		return UART_INVALID_UART_REGISTER;
//	}
//
//	return NO_ERROR;
//}
//
//
//
//ERROR_CODE
//uart_dma_stop
//(
//	const UART_REG reg
//)
//{
//
//#if(defined(USE_UART1))
//	if(USART1 == reg)
//	{
//		if(!USART1_MAPPED)
//		{
//			DMA_ClearITPendingBit(DMA1_FLAG_GL4);
//
//			DMA_Cmd(DMA1_Channel4, DISABLE);
//		}
//		else
//		{
//			DMA_ClearITPendingBit(DMA1_FLAG_GL2);
//
//			DMA_Cmd(DMA1_Channel2, DISABLE);
//		}
//	}
//	else
//#endif
//	{
//		return UART_INVALID_UART_REGISTER;
//	}
//
//	USART_DMACmd(reg, USART_DMAReq_Tx, DISABLE);
//
//	return NO_ERROR;
//}
//
//
//
//ERROR_CODE
//uart_dma_completed
//(
//	const UART_REG reg,
//
//	bool_t *const flag_ptr
//)
//{
//	*flag_ptr = false;
//
//	//uint8_t x = 0;
//
//#if(defined(USE_UART1))
//	if(USART1 == reg)
//	{
//		if(!USART1_MAPPED)
//		{
//			if(!(DMA1_Channel4->CCR & 0x01))
//			{
//				*flag_ptr = true;
//			}
//			else if(SET == DMA_GetFlagStatus(DMA1_FLAG_TC4))
//			{
//				*flag_ptr = true;
//			}
//		}
//		else
//		{
//			if(!(DMA1_Channel2->CCR & 0x01))
//			{
//				*flag_ptr = true;
//			}
//			else if(SET == DMA_GetFlagStatus(DMA1_FLAG_TC2))
//			{
//				*flag_ptr = true;
//			}
//		}
//	}
//	else
//#endif
//	{
//		return UART_INVALID_UART_REGISTER;
//	}
//
//	return NO_ERROR;
//}
//
//
//
//ERROR_CODE
//uart_dma_error
//(
//	const UART_REG reg
//)
//{
//	ERROR_CODE err = NO_ERROR;
//
//#if(defined(USE_UART1))
//	if(USART1 == reg)
//	{
//		if(!USART1_MAPPED)
//		{
//			if(SET == DMA_GetFlagStatus(DMA1_FLAG_TE4))
//			{
//				err = UART_DMA_ERROR;
//			}
//		}
//		else
//		{
//			if(SET == DMA_GetFlagStatus(DMA1_FLAG_TE2))
//			{
//				err = UART_DMA_ERROR;
//			}
//		}
//	}
//	else
//#endif
//	{
//		return UART_INVALID_UART_REGISTER;
//	}
//
//	return err;
//}
