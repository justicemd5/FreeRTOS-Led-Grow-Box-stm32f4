/*
 * rs232.c
 *
 *  Created on: Jan 22, 2014
 *      Author: nihad
 */

#include "rs232.h"
#include "peripheral.h"

ERROR_CODE rs232_open(UART_REG port, uint32_t baudrate)
{
	ERROR_CODE err;
	err = uart_open(port,baudrate);
	return err;
}
void rs232_close(UART_REG port)
{
	uart_close(port);
}

ERROR_CODE DO_NOT_OPTIMIZE rs232_buffer_write_read(UART_REG reg, uint8_t * buffer, uint16_t buffer_size, uint16_t * size, const uint8_t * pattern, uint32_t timeoutStart, uint32_t timeoutEnd)
{
	ERROR_CODE err = UART_NO_DATA;
	uint16_t i;
	uint8_t * j; //if pattern was found
	
	//if previous action returned this kind of error,
	//no need to send a new command until this flag is cleared
	if (SLEEP_OCCURED) return SLEEP_OCCURED_ERROR;

	uint32_t tmu = timeoutStart;

	uint8_t dummy;
	err = NO_ERROR;

	uart_flush(reg);

	//write
	for(i=0;i<*size;i++)
	{
		dummy = *(buffer+i);
		uart_byte_write(reg,dummy);
	}

	//wait end of write
	uart_wait_eow(reg);

	//TODO osloboditi
	memset(buffer,0,*size);	//clear buffer
	
	//read
	i=0;
	j=0;

	uart_handle_overrun(reg);

	while(uart_byte_timeout_read(reg,tmu,&dummy) == NO_ERROR)
	{
		*(buffer + i) = dummy;
		i++;
		if(i >= buffer_size)
		{
			i = buffer_size;
			buffer[buffer_size - 1] = '\0';
			break;
		}
		tmu = timeoutEnd;
		if (pattern && j == 0)
		{
			j = strstr(buffer,pattern);
			if(j == 0)
			{
				tmu =  timeoutStart;		//wait until find a match
			} else
			{
				memset(buffer,0,*size);	//clear buffer
				strcpy(buffer,pattern);
				i = strlen(pattern);
			}
		}
	}

	*size = 0;

	if (SLEEP_OCCURED)
	{
		err = SLEEP_OCCURED_ERROR;
	}
	else if (i > 0)
	{
		*size = i;
		err = NO_ERROR;
	}

	return err;
}

