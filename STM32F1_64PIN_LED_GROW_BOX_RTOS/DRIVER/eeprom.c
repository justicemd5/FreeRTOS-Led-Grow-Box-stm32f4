

#include "eeprom.h"

#ifdef EEPROM
ERROR_CODE eeprom_GetStatus()
{
	  uint32_t I2C_TimeOut = EEPROM_LONG_TIMEOUT;

	  /* Configure slave address, nbytes, reload, end mode and start or stop generation */
	  I2C_TransferHandling(EEPROM_I2C, EEPROM_HW_ADDRESS, 0, I2C_AutoEnd_Mode, I2C_No_StartStop);

	  /* Clear NACKF and STOPF */
	  I2C_ClearFlag(EEPROM_I2C, I2C_ICR_NACKCF | I2C_ICR_STOPCF);

	  /* Generate start */
	  I2C_GenerateSTART(EEPROM_I2C, ENABLE);

	  /* Wait until timeout elapsed */
	  while ((I2C_GetFlagStatus(EEPROM_I2C, I2C_ISR_STOPF) == RESET) && (I2C_TimeOut-- != 0));

	  /* Check if Temp sensor is ready for use */
	  if ((I2C_GetFlagStatus(EEPROM_I2C, I2C_ISR_NACKF) != RESET) || (I2C_TimeOut == 0))
	  {
	    /* Clear NACKF and STOPF */
	    I2C_ClearFlag(EEPROM_I2C, I2C_ICR_NACKCF | I2C_ICR_STOPCF);

	    return ERROR;
	  }
	  else
	  {
	    /* Clear STOPF */
	    I2C_ClearFlag(EEPROM_I2C, I2C_ICR_STOPCF);

	    return SUCCESS;
	  }
}
ERROR_CODE eeprom_Read(uint8_t address, uint8_t * data, uint8_t length)
{
	uint8_t i;
	uint32_t eepromTimeout;

	for (i = 0; i < length; ++i) {

		/* Test on BUSY Flag */
		eepromTimeout = EEPROM_LONG_TIMEOUT;
		while(I2C_GetFlagStatus(EEPROM_I2C, I2C_ISR_BUSY) != RESET)
		{
		if((eepromTimeout--) == 0) return GLOBAL_ERROR;
		}

		/* Configure slave address, nbytes, reload, end mode and start or stop generation */
		I2C_TransferHandling(EEPROM_I2C, EEPROM_HW_ADDRESS, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

		/* Wait until TXIS flag is set */
		eepromTimeout = EEPROM_LONG_TIMEOUT;
		while(I2C_GetFlagStatus(EEPROM_I2C, I2C_ISR_TXIS) == RESET)
		{
		if((eepromTimeout--) == 0) return GLOBAL_ERROR;
		}

		/* Send Register address */
		I2C_SendData(EEPROM_I2C, (uint8_t)(address+i));

		/* Wait until TC flag is set */
		eepromTimeout = EEPROM_LONG_TIMEOUT;
		while(I2C_GetFlagStatus(EEPROM_I2C, I2C_ISR_TC) == RESET)
		{
		if((eepromTimeout--) == 0) return GLOBAL_ERROR;
		}

		/* Configure slave address, nbytes, reload, end mode and start or stop generation */
		I2C_TransferHandling(EEPROM_I2C, EEPROM_HW_ADDRESS, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

		//while (DataNum != 2)
		//{
		/* Wait until TXIS flag is set */
		eepromTimeout = EEPROM_LONG_TIMEOUT;
		while(I2C_GetFlagStatus(EEPROM_I2C, I2C_ISR_RXNE) == RESET)
		{
		  if((eepromTimeout--) == 0) return GLOBAL_ERROR;
		}

	    /* Read data from RXDR */
	    *(data+i)= I2C_ReceiveData(EEPROM_I2C);

		/* Update number of transmitted data */
		//DataNum++;
		//}

		/* Wait until STOPF flag is set */
		eepromTimeout = EEPROM_LONG_TIMEOUT;
		while(I2C_GetFlagStatus(EEPROM_I2C, I2C_ISR_STOPF) == RESET)
		{
		if((eepromTimeout--) == 0) return GLOBAL_ERROR;
		}

		/* Clear STOPF flag */
		I2C_ClearFlag(EEPROM_I2C, I2C_ICR_STOPCF);
	}

    return NO_ERROR;
}
ERROR_CODE eeprom_Write(uint8_t address, uint8_t * data, uint8_t length)
{
	uint8_t i;
	uint32_t eepromTimeout;

	for (i = 0; i < length; ++i) {

		/* Test on BUSY Flag */
		eepromTimeout = EEPROM_LONG_TIMEOUT;
		while(I2C_GetFlagStatus(EEPROM_I2C, I2C_ISR_BUSY) != RESET)
		{
		if((eepromTimeout--) == 0) return GLOBAL_ERROR;
		}

		/* Configure slave address, nbytes, reload, end mode and start or stop generation */
		I2C_TransferHandling(EEPROM_I2C, EEPROM_HW_ADDRESS, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);

		/* Wait until TXIS flag is set */
		eepromTimeout = EEPROM_LONG_TIMEOUT;
		while(I2C_GetFlagStatus(EEPROM_I2C, I2C_ISR_TXIS) == RESET)
		{
		if((eepromTimeout--) == 0) return GLOBAL_ERROR;
		}

		/* Send Register address */
		I2C_SendData(EEPROM_I2C, (uint8_t)(address+i));

		/* Wait until TCR flag is set */
		eepromTimeout = EEPROM_LONG_TIMEOUT;
		while(I2C_GetFlagStatus(EEPROM_I2C, I2C_ISR_TCR) == RESET)
		{
		if((eepromTimeout--) == 0) return GLOBAL_ERROR;
		}

		/* Configure slave address, nbytes, reload, end mode and start or stop generation */
		I2C_TransferHandling(EEPROM_I2C, EEPROM_HW_ADDRESS, 1, I2C_AutoEnd_Mode, I2C_No_StartStop);

		//while (DataNum != 2)
		//{
		/* Wait until TXIS flag is set */
		eepromTimeout = EEPROM_LONG_TIMEOUT;
		while(I2C_GetFlagStatus(EEPROM_I2C, I2C_ISR_TXIS) == RESET)
		{
		  if((eepromTimeout--) == 0) return GLOBAL_ERROR;
		}

		/* Write data to TXDR */
		I2C_SendData(EEPROM_I2C, *(data+i));

		/* Update number of transmitted data */
		//DataNum++;
		//}

		/* Wait until STOPF flag is set */
		eepromTimeout = EEPROM_LONG_TIMEOUT;
		while(I2C_GetFlagStatus(EEPROM_I2C, I2C_ISR_STOPF) == RESET)
		{
		if((eepromTimeout--) == 0) return GLOBAL_ERROR;
		}

		/* Clear STOPF flag */
		I2C_ClearFlag(EEPROM_I2C, I2C_ICR_STOPCF);
	}
	
    return NO_ERROR;
}

#ifdef TEST
	ERROR_CODE eeprom_Test(void)
	{
		uint8_t result;
		uint8_t source[] = "Test";
		uint8_t ret[] = {0,0,0,0};
		eeprom_Init();
		result = eeprom_GetStatus();
		result = eeprom_Write(0,&source,4);
		result = eeprom_Read(0,&ret,4);
		eeprom_DeInit();
		return strncmp(&source,&ret,4); 
	}
#endif



#endif
