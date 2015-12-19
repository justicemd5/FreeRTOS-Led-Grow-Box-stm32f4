//#include "i2c.h"
//#include "timeout.h"
//
//static ERROR_CODE i2c_check_flag(I2C_REG reg, uint32_t flag, uint32_t timeout, uint8_t state);
//static void i2c_software_reset(I2C_REG reg);
//
//ERROR_CODE i2c_init()
//{
//
//	i2c_deinit();
//
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1 | RCC_APB1Periph_I2C2,ENABLE);
//
//	RCC_I2CCLKConfig(RCC_I2C1CLK_SYSCLK); //Configure the I2C clock source. The clock is derived from the SYSCLK
//
//	I2C_InitTypeDef I2C_InitStructure;
//	//I2C configuration
//	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
//	I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Disable;
//	I2C_InitStructure.I2C_DigitalFilter = 0x00;
//	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
//	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
//	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//	I2C_InitStructure.I2C_Timing = I2C_TIMING;
//
//	I2C_Init(I2C1, &I2C_InitStructure); //Apply I2C configuration after enabling it
//
//	I2C_InitStructure.I2C_Timing = I2C_TIMING;
//
//	I2C_Init(I2C2, &I2C_InitStructure);
//
//	I2C_Cmd(I2C1, ENABLE); // Enable I2C Peripheral
//	I2C_Cmd(I2C2, ENABLE);
//
//	return NO_ERROR;
//}
//
//ERROR_CODE i2c_deinit()
//{
//	I2C_Cmd(I2C1, DISABLE);
//	I2C_Cmd(I2C2, DISABLE);
//
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1 | RCC_APB1Periph_I2C2, DISABLE);
//
//	return NO_ERROR;
//}
//
//ERROR_CODE i2c_write_read(I2C_REG reg, uint8_t address, uint8_t * writeData, uint8_t writeSize, uint8_t * readData, uint8_t readSize)
//{
//	ERROR_CODE err;	// = i2c_get_status(reg,address);
//
//	I2C_ClearFlag(reg, ((uint32_t)0xFFFFFFFF));
//	I2C_ClearITPendingBit(reg, ((uint32_t)0xFFFFFFFF));
//
//	if(writeSize)
//	{
//		if(readSize)
//		{
//			I2C_TransferHandling(reg, address, writeSize, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
//		}
//		else
//		{
//			I2C_TransferHandling(reg, address, writeSize, I2C_AutoEnd_Mode, I2C_Generate_Start_Write);
//		}
//
//		uint8_t i = 0;
//
//		for (i=0;i<writeSize;i++)
//		{
//			err = i2c_check_flag(reg,I2C_FLAG_TXIS, I2C_WRITE_TIMEOUT_US, RESET);
//
//			HANDLE_ERROR(err);
//
//			I2C_SendData(reg, *(writeData + i)); // Send Register address
//		}
//
//		if(readSize)
//		{
//			err = i2c_check_flag(reg,I2C_FLAG_TC,I2C_WRITE_TIMEOUT_US, RESET);
//			HANDLE_ERROR(err);
//		}
//	}
//
//	if(readSize)
//	{
//		I2C_TransferHandling(reg, address, readSize, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
//
//		uint8_t i = 0;
//
//		while(readSize)
//		{
//			readSize--;
//			err = i2c_check_flag(reg,I2C_FLAG_RXNE,I2C_READ_TIMEOUT_US,RESET);
//			HANDLE_ERROR(err);
//
//		    *(readData+i)= I2C_ReceiveData(reg); //Read data from RXDR
//		    i++;
//
//		}
//	}
//
//	//wait stop flag
//	err = i2c_check_flag(reg,I2C_FLAG_STOPF,I2C_READ_TIMEOUT_US, RESET);
//
//	return err;
//}
//
//ERROR_CODE i2c_get_status(I2C_REG reg, uint8_t address)
//{
//
//	uint8_t test;
//	test = 0;
//
//	i2c_software_reset(reg);
//
//	return i2c_write_read(reg,address,&test,1,0,0);
//
//}
//
//static ERROR_CODE i2c_check_flag(I2C_REG reg, uint32_t flag, uint32_t timeout, uint8_t state)
//{
//	timeout_AsyncWaitus(I2C_TIMEOUT_TIMER, timeout);
//
//	while((state == I2C_GetFlagStatus(reg, flag)) && !timeout_AsyncIsElapsed(I2C_TIMEOUT_TIMER));
//
//	timeout_AsyncStop(I2C_TIMEOUT_TIMER);
//
//	if(state == I2C_GetFlagStatus(reg, flag))
//	{
//		I2C_GenerateSTOP(reg,ENABLE);
//		i2c_software_reset(reg);
//		return I2C_COMMUNICATION_ERROR;
//	}
//	return NO_ERROR;
//}
//
//static void i2c_software_reset(I2C_REG reg)
//{
//	//software reset pg.615 doc: RM0091
//	reg->CR1 &= ~(I2C_CR1_PE);
//	while(reg->CR1 & I2C_CR1_PE);
//	reg->CR1 |= I2C_CR1_PE;
//}
