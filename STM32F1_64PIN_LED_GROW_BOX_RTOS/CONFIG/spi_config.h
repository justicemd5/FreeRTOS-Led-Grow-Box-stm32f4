#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include "settings.h"


/* SPI SETTINGS */
typedef SPI_TypeDef* SPIREG;

#define USE_SPI1
#define USE_SPI2_OUTPUT_ONLY


#define SPI_TIMER_CHANNEL			(uint8_t)0
#define SPI_TIMEOUT_US				(uint32_t)200000


//CHIP SELECTS
//FM
#define SPI_CS_1_PORT			GPIOC
#define SPI_CS_1_PIN			GPIO_Pin_12
#define SPI_CS_1_ON				gpio_set_pin(SPI_CS_1_PORT, SPI_CS_1_PIN)
#define SPI_CS_1_OFF			gpio_reset_pin(SPI_CS_1_PORT, SPI_CS_1_PIN)
//SD CARD
#define SPI_CS_2_PORT			GPIOD
#define SPI_CS_2_PIN			GPIO_Pin_2
#define SPI_CS_2_ON				gpio_set_pin(SPI_CS_2_PORT, SPI_CS_2_PIN)
#define SPI_CS_2_OFF			gpio_reset_pin(SPI_CS_2_PORT, SPI_CS_2_PIN)
//SRAM
#define SPI_CS_3_PORT			GPIOC
#define SPI_CS_3_PIN			GPIO_Pin_2
#define SPI_CS_3_ON				gpio_set_pin(SPI_CS_3_PORT, SPI_CS_3_PIN)
#define SPI_CS_3_OFF			gpio_reset_pin(SPI_CS_3_PORT, SPI_CS_3_PIN)

#endif /* END OF SPI SETTINGS */
