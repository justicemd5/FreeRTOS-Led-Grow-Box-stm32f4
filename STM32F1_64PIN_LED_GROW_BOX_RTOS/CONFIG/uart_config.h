#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#include "settings.h"

#define USE_UART1
#define USE_UART3

#define UART_TIMER_CHANNEL			0
#define UART_WRITE_TIMEOUT_US		10000
#define UART_READ_TIMEOUT_US		10000

#define USART1_MAPPED 				(true)

typedef USART_TypeDef* UART_REG;
typedef struct
{
	uint32_t 	Baudrate;
	uint8_t 	StopBits;
	uint8_t		Parity;
} UART_PARAMETERS;

#endif
