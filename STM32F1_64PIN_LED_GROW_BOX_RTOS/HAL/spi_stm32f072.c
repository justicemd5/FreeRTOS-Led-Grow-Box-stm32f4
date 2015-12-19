///*
// * hal_spi.c
// *
// *  Created on: Dec 26, 2013
// *      Author: nihad
// */
//
//#include "spi.h"
//#include "ttypes.h"
//#include "timeout.h"
//
//static void spi_empty(SPIREG reg);
//static void spi_clear_flags(SPIREG reg, uint8_t force_clear_flag);
////static ERROR_CODE spi_check_flag(SPIREG reg, uint32_t flag, uint32_t timeout, uint8_t state); unused
//
//ERROR_CODE spi_init()
//{
//	SPI_InitTypeDef SPI_InitStructure;
//
//	spi_deinit();
//
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//
//	/* Enable the SPI periph */
//#ifdef USE_SPI1
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	//spi1
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//	SPI_Init(SPI1, &SPI_InitStructure);
//	SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);	//1 bayt RX Buffer RXNE flag change
//	SPI_Cmd(SPI1,ENABLE);
//
//	spi_clear_flags(SPI1, true);
//
//#endif
//#ifdef USE_SPI2_OUTPUT_ONLY
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);	//spi2
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
//	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
//	SPI_Init(SPI2,&SPI_InitStructure);
//	SPI_RxFIFOThresholdConfig(SPI2, SPI_RxFIFOThreshold_QF);
//	SPI_Cmd(SPI2,ENABLE);
//
//	spi_clear_flags(SPI2, true);
//#endif
//
//	return NO_ERROR;
//}
//
//ERROR_CODE spi_deinit()
//{
//
//	spi_deactivate();
//
//#ifdef USE_SPI1
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	//spi1
//	spi_clear_flags(SPI1, false);
//	SPI_Cmd(SPI1,DISABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, DISABLE);	//spi1
//#endif
//#ifdef USE_SPI2_OUTPUT_ONLY
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);	//spi2
//	spi_clear_flags(SPI2, false);
//	SPI_Cmd(SPI2,DISABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, DISABLE);	//spi2
//#endif
//
//	return NO_ERROR;
//}
//
//ERROR_CODE spi_set_speed(SPIREG reg, uint8_t speed)
//{
//	return NO_ERROR;
//}
//
//void spi_activate(uint8_t device)
//{
//	//make sure all CS are disabled first
//	SPI_CS_1_ON;
//	SPI_CS_2_ON;
//	SPI_CS_3_ON;
//
//	if (device == 1)
//	{
//		SPI_CS_1_OFF;
//	}
//	else if (device == 2)
//	{
//		SPI_CS_2_OFF;
//	}
//	else if (device == 3)
//	{
//		SPI_CS_3_OFF;
//	}
//	//TODO
//	timeout_Waitus(10);
//}
//void spi_deactivate()
//{
//	SPI_CS_1_ON;
//	SPI_CS_2_ON;
//	SPI_CS_3_ON;
//	timeout_Waitus(10);
//}
//
//ERROR_CODE DO_NOT_OPTIMIZE spi_byte_write(SPIREG reg, uint8_t byte)
//{
//
//	uint32_t timeout;
//
//	WAIT_FOR_FLAG_CHANGE_OR_TIMEOUT((reg->SR & SPI_I2S_FLAG_BSY),timeout,SPI_TIMEOUT_US,SPI_WRITE_FAILED);
//
//	*(volatile uint8_t *)((uint32_t)reg + 0x0C) = byte;
//
//	return NO_ERROR;
//
//}
//
//ERROR_CODE DO_NOT_OPTIMIZE spi_byte_read(SPIREG reg, uint8_t * read)
//{
//
//	uint32_t timeout = SPI_TIMEOUT_US; //~19ms
//
//	while((reg->SR & SPI_I2S_FLAG_RXNE) && timeout) //empty any remaining unread chars from RX buffer
//	{
//		uint8_t dummy = *(volatile uint8_t *)((uint32_t)reg + 0x0C);
//		timeout--;
//
//		(void)dummy; // suppress compiler warning: unused variable
//	}
//	//HANDLE_TIMEOUT_ERROR(timeout,SPI_ERROR);
//
//	ERROR_CODE err = spi_byte_write(reg, 0xFF); //Send DUMMY Byte through the SPI peripheral
//
//	HANDLE_ERROR(err);
//
//	WAIT_FOR_FLAG_CHANGE_OR_TIMEOUT(reg->SR & (SPI_I2S_FLAG_RXNE == RESET),timeout,SPI_TIMEOUT_US,SPI_WRITE_FAILED);
//
//	*read = *(volatile uint8_t *)((uint32_t)reg + 0x0C);
//
//	return NO_ERROR;
//}
//
//void spi_buffer_write(SPIREG reg, uint8_t * data, uint8_t dataLength, uint8_t fromByte, uint8_t length)
//{
//	uint8_t i, j, k;
//
//	spi_empty(reg);
//
//	k = length;
//
//	for(i=0; i < dataLength; i++)
//	{
//
//		if(i >= fromByte && k)
//		{
//			j = *(data+i);
//			k--;
//		}
//		else
//		{
//			j=0;
//		}
//
//		while((reg->SR & SPI_I2S_FLAG_BSY))
//		{
//		}
//		/* Send a Byte through the SPI peripheral */
//		*(uint8_t *)((uint32_t)reg + 0x0C) = j;
//
//	}
//}
//
//static void spi_empty(SPIREG reg)
//{
//	//empty any remaining unread chars from RX buffer
//	while((reg->SR & SPI_I2S_FLAG_RXNE))
//	{
//		uint8_t i = *(uint8_t *)((uint32_t)reg + 0x0C);
//		//timeout--;
//
//		(void)i; // suppress compiler warning: unused variable
//	}
//}
//
//// unused
////static ERROR_CODE spi_check_flag(SPIREG reg, uint32_t flag, uint32_t timeout, uint8_t state)
////{
////	timeout_AsyncWaitus(SPI_TIMER_CHANNEL, timeout);
////
////	while((state == SPI_I2S_GetFlagStatus(reg, flag)) && !timeout_AsyncIsElapsed(SPI_TIMER_CHANNEL));
////
////	timeout_AsyncStop(SPI_TIMER_CHANNEL);
////
////	if(state == SPI_I2S_GetFlagStatus(reg, flag))
////	{
////		return SPI_ERROR;
////	}
////	return NO_ERROR;
////}
//
//static void spi_clear_flags(SPIREG reg, uint8_t force_clear_flag)
//{
//	if (reg->SR & SPI_FLAG_CRCERR || force_clear_flag)
//	{
//		SPI_I2S_ClearFlag(reg,SPI_FLAG_CRCERR);
//	}
//
//	//	  @note   OVR (OverRun error) flag is cleared by software sequence: a read
//	//	          operation to SPI_DR register (SPI_I2S_ReceiveData()) followed by
//	//	          a read operation to SPI_SR register (SPI_I2S_GetFlagStatus()).
//	if (reg->SR & SPI_I2S_FLAG_OVR || force_clear_flag)
//	{
//		uint8_t i = SPI_ReceiveData8(reg);
//		i = SPI_I2S_GetFlagStatus(reg, SPI_I2S_FLAG_OVR);
//
//		(void)i; // suppress compiler warning: unused variable
//	}
//
//	//	  @note   MODF (Mode Fault) flag is cleared by software sequence: a read/write
//	//	          operation to SPI_SR register (SPI_I2S_GetFlagStatus()) followed by
//	//	          a write operation to SPI_CR1 register (SPI_Cmd() to enable the SPI).
//	if (reg->SR & SPI_FLAG_MODF || force_clear_flag)
//	{
//		uint8_t i = SPI_I2S_GetFlagStatus(reg, SPI_FLAG_MODF);
//		SPI_Cmd(reg,ENABLE);
//
//		(void)i; // suppress compiler warning: unused variable
//	}
//}
