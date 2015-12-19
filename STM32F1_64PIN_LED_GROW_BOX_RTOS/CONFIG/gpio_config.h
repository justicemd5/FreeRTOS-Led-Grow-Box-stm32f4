#ifndef GPIO_CONFIG_H_
#define GPIO_CONFIG_H_

#include "settings.h"

#define GPIO_PORT_PIN_NUMBER	16

typedef GPIO_TypeDef*  GPIO_PORT;
typedef uint16_t  GPIO_PIN;


typedef enum
{
	GPIO_STATE_OUTPUT_ONLY,
	GPIO_STATE_FULL
} gpio_state_t;


#define GPIO_PORT_STRUCT 		GPIO_TypeDef*
#define GPIO_PIN_STRUCT			uint16_t
#define GPIO_AF_PIN_STRUCT		uint8_t
#define GPIO_AF_MODE			uint8_t

#define USE_GPIOA
#define USE_GPIOB
#define USE_GPIOC
#define USE_GPIOD


#endif
