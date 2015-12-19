#include "gpio.h"
#include "gpio_config.h"
#include "uart_config.h"
#include "spi_config.h"
#include "i2c_config.h"
#include "usb_config.h"
#include "peripheral_config.h"

static void uart_gpio_init();
static void lcd_gpio_init();
static void touch_gpio_init();
static void usb_gpio_init();
static void i2c_gpio_init();
static void spi_gpio_init();
static void power_pins_skip(GPIO_PORT_STRUCT port, GPIO_PIN_STRUCT * pins);

#ifdef USE_GPIOA
	uint16_t backup_gpioA;
#endif
#ifdef USE_GPIOB
	uint16_t backup_gpioB;
#endif
#ifdef USE_GPIOC
	uint16_t backup_gpioC;
#endif
#ifdef USE_GPIOD
	uint16_t backup_gpioD;
#endif

void gpio_init()
{
	uint32_t clocks = 0;

#ifdef USE_GPIOA
	clocks |= RCC_APB2Periph_GPIOA;
#endif
#ifdef USE_GPIOB
	clocks |= RCC_APB2Periph_GPIOB;
#endif
#ifdef USE_GPIOC
	clocks |= RCC_APB2Periph_GPIOC;
#endif
#ifdef USE_GPIOD
	clocks |= RCC_APB2Periph_GPIOD;
#endif

	/* GPIOD Periph clock enable */
	RCC_APB2PeriphClockCmd(clocks, ENABLE);

//	i2c_gpio_init();
//	uart_gpio_init();
//	spi_gpio_init();
//	usb_gpio_init();

	lcd_gpio_init();
	touch_gpio_init();

}

static void lcd_gpio_init()
{
	gpio_set_mode(GPIOB, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11
					| GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,
						GPIO_Mode_Out_PP, GPIO_Speed_50MHz, false);

	gpio_set_mode(GPIOC, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
					| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7
					| GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11,
						GPIO_Mode_Out_PP, GPIO_Speed_50MHz, false);


}

static void touch_gpio_init()
{

	gpio_set_mode(GPIOA, GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_4, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, false);

	gpio_set_mode(GPIOA, GPIO_Pin_6, GPIO_Mode_IPU, GPIO_Speed_50MHz, false);

	gpio_set_mode(GPIOC, GPIO_Pin_13, GPIO_Mode_IPU, GPIO_Speed_50MHz, false);

	//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //Busy Pin
	//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	//    GPIO_Init(GPIOC, &GPIO_InitStructure);
	//
	//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //Dout
	//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//    GPIO_Init(GPIOA, &GPIO_InitStructure);
	//
	//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //IRQ
	//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//    GPIO_Init(GPIOC, &GPIO_InitStructure);
	//
	//
	//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_4; //CLK, Din, cs
	//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//    GPIO_Init(GPIOA, &GPIO_InitStructure);


}
//
//static void power_pins_skip(GPIO_PORT_STRUCT port, GPIO_PIN_STRUCT * pins)
//{
//	//excluding power pins from configuration
//#ifdef POWER_ADAPTOR_SUPPLY_PORT
//	if (POWER_ADAPTOR_SUPPLY_PORT == port)
//	{
//		*pins &= ~(POWER_ADAPTOR_SUPPLY_PIN);
//	}
//#endif
//#ifdef POWER_BATTERY_SUPPLY_PORT
//	if (POWER_BATTERY_SUPPLY_PORT == port)
//	{
//		*pins &= ~(POWER_BATTERY_SUPPLY_PIN);
//	}
//#endif
//#ifdef POWER_MCU_SUPPLY_PORT
//	if (POWER_MCU_SUPPLY_PORT == port)
//	{
//		*pins &= ~(POWER_MCU_SUPPLY_PIN);
//	}
//#endif
//#ifdef POWER_KEYBOARD_WAKE_PORT
//	if (POWER_KEYBOARD_WAKE_PORT == port)
//	{
//		*pins &= ~(POWER_KEYBOARD_WAKE_PIN);
//	}
//#endif
//#ifdef PERIPHERAL_POWER_PORT
//	if (PERIPHERAL_POWER_PORT == port)
//	{
//		*pins &= ~(PERIPHERAL_POWER_PIN);
//	}
//#endif
////#ifdef PERIPHERAL_LED_RED_PORT
////	if (PERIPHERAL_LED_RED_PORT == port)
////	{
////		*pins &= ~(PERIPHERAL_LED_RED_PIN);
////	}
////#endif
//}
//
//void gpio_ports_reset()
//{
//	GPIO_DeInit(GPIOA);
//	GPIO_DeInit(GPIOB);
//	GPIO_DeInit(GPIOC);
//	GPIO_DeInit(GPIOD);
//	GPIO_DeInit(GPIOE);
//	GPIO_DeInit(GPIOF);
//}
//
//void gpio_all_inactive()
//{
//	uint32_t clocks;
//
//	clocks = 	RCC_AHBPeriph_GPIOA |
//				RCC_AHBPeriph_GPIOB |
//				RCC_AHBPeriph_GPIOC |
//				RCC_AHBPeriph_GPIOD |
//				RCC_AHBPeriph_GPIOE |
//				RCC_AHBPeriph_GPIOF |
//				RCC_AHBPeriph_CRC   |
//				RCC_AHBPeriph_DMA1  |
//				RCC_AHBPeriph_FLITF |
//				RCC_AHBPeriph_TS;
//
//	//reset all clocks
//	RCC_AHBPeriphResetCmd(clocks & ~(RCC_AHBPeriph_SRAM),ENABLE);			//preserve SRAM CLOCK running
//	RCC_AHBPeriphResetCmd(clocks & ~(RCC_AHBPeriph_SRAM),DISABLE);
//
//	clocks = 	RCC_APB1Periph_CAN		|
//				RCC_APB1Periph_CEC		|
//				RCC_APB1Periph_CRS		|
//				RCC_APB1Periph_DAC		|
//				RCC_APB1Periph_I2C1		|
//				RCC_APB1Periph_I2C2		|
//				RCC_APB1Periph_SPI2		|
//				RCC_APB1Periph_TIM14	|
//				RCC_APB1Periph_TIM2		|
//				RCC_APB1Periph_TIM3		|
//				RCC_APB1Periph_TIM6		|
//				RCC_APB1Periph_TIM7		|
//				RCC_APB1Periph_USART2	|
//				RCC_APB1Periph_USART3	|
//				RCC_APB1Periph_USART4	|
//				RCC_APB1Periph_USB		|
//				RCC_APB1Periph_WWDG;
//
//	RCC_APB1PeriphResetCmd(clocks & ~(RCC_APB1Periph_PWR),ENABLE);		//rtc clock must run
//	RCC_APB1PeriphResetCmd(clocks & ~(RCC_APB1Periph_PWR),DISABLE);
//
//
//	clocks =	RCC_APB2Periph_ADC1		|
//				RCC_APB2Periph_SPI1		|
//				RCC_APB2Periph_TIM1		|
//				RCC_APB2Periph_TIM15	|
//				RCC_APB2Periph_TIM16	|
//				RCC_APB2Periph_TIM17	|
//#ifndef DEBUG
//				RCC_APB2Periph_DBGMCU	|
//#endif
//				RCC_APB2Periph_USART1;
//
//#ifdef DEBUG
//	RCC_APB2PeriphResetCmd(clocks & ~(RCC_APB2Periph_SYSCFG) & ~(RCC_APB2Periph_DBGMCU),ENABLE);		//exti clock must run
//	RCC_APB2PeriphResetCmd(clocks & ~(RCC_APB2Periph_SYSCFG) & ~(RCC_APB2Periph_DBGMCU),DISABLE);
//#else
//	RCC_APB2PeriphResetCmd(clocks & ~(RCC_APB2Periph_SYSCFG),ENABLE);		//exti clock must run
//	RCC_APB2PeriphResetCmd(clocks & ~(RCC_APB2Periph_SYSCFG),DISABLE);
//#endif
//
//	//gpio inactive
//	clocks = 	RCC_AHBPeriph_GPIOA |
//				RCC_AHBPeriph_GPIOB |
//				RCC_AHBPeriph_GPIOC |
//				RCC_AHBPeriph_GPIOD |
//				RCC_AHBPeriph_GPIOE |
//				RCC_AHBPeriph_GPIOF;
//
//
//	/* GPIOD Periph clock enable */
//	RCC_AHBPeriphClockCmd(clocks, ENABLE);
//
//	GPIO_PIN_STRUCT pins;
//
//	pins = GPIO_Pin_All & ~(GPIO_Pin_13) & ~(GPIO_Pin_14);		//SWD pins A13 and A14
//	power_pins_skip(GPIOA,&pins);
//	gpio_set_mode(	GPIOA,
//					pins,
//					GPIO_INPUT_ANALOG,
//					GPIO_SPEED_LOW,
//					0);
//
//	pins = GPIO_Pin_All;
//	power_pins_skip(GPIOB,&pins);
//	gpio_set_mode(	GPIOB,
//					pins,
//					GPIO_INPUT_ANALOG,
//					GPIO_SPEED_LOW,
//					0);
//
//	pins = GPIO_Pin_All;
//	power_pins_skip(GPIOC,&pins);
//	gpio_set_mode(	GPIOC,
//					pins,
//					GPIO_INPUT_ANALOG,
//					GPIO_SPEED_LOW,
//					0);
//
//	pins = GPIO_Pin_All;
//	power_pins_skip(GPIOD,&pins);
//	gpio_set_mode(	GPIOD,
//					pins,
//					GPIO_INPUT_ANALOG,
//					GPIO_SPEED_LOW,
//					0);
//
//	gpio_set_mode(	GPIOE,
//					GPIO_Pin_All,
//					GPIO_INPUT_ANALOG,
//					GPIO_SPEED_LOW,
//					0);
//
//	gpio_set_mode(	GPIOF,
//					GPIO_Pin_All,
//					GPIO_INPUT_ANALOG,
//					GPIO_SPEED_LOW,
//					0);
//
//	RCC_AHBPeriphClockCmd(clocks, DISABLE);
//
//}
//
//void gpio_state_backup(gpio_state_t state)
//{
//	if (state == GPIO_STATE_OUTPUT_ONLY)
//	{
//#ifdef USE_GPIOA
//		backup_gpioA = GPIO_ReadOutputData(GPIOA);
//#endif
//#ifdef USE_GPIOB
//		backup_gpioB = GPIO_ReadOutputData(GPIOB);
//#endif
//#ifdef USE_GPIOC
//		backup_gpioC = GPIO_ReadOutputData(GPIOC);
//#endif
//#ifdef USE_GPIOD
//		backup_gpioD = GPIO_ReadOutputData(GPIOD);
//#endif
//	}
//}
//
//void gpio_state_restore(gpio_state_t state)
//{
//	if (state == GPIO_STATE_OUTPUT_ONLY)
//	{
//#ifdef USE_GPIOA
//		GPIO_Write(GPIOA, backup_gpioA);
//#endif
//#ifdef USE_GPIOB
//		GPIO_Write(GPIOB, backup_gpioB);
//#endif
//#ifdef USE_GPIOC
//		GPIO_Write(GPIOC, backup_gpioC);
//#endif
//#ifdef USE_GPIOD
//		GPIO_Write(GPIOD, backup_gpioD);
//#endif
//	}
//}
//
void gpio_set_mode(GPIO_PORT_STRUCT port, GPIO_PIN_STRUCT pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, bool_t defaultvalue)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

	/*Configure GPIO pin : PA */
	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_InitStructure.GPIO_Mode = mode;
	GPIO_InitStructure.GPIO_Speed = speed;

	GPIO_Init(port, &GPIO_InitStructure);


	if (mode == GPIO_Mode_Out_PP && defaultvalue)
	{
		gpio_set_pin(port,pin);
	}

	else if (mode == GPIO_Mode_Out_PP && defaultvalue == 0)
	{
		gpio_reset_pin(port,pin);
	}

}
//

//
//
//
//static void uart_gpio_init()
//{
////	GPIO_InitTypeDef   GPIO_InitStructure; unused variable
//
//#ifdef USE_UART1
//	/** USART1 GPIO Configuration
//	PB6   ------> USART1_TX
//	PB7   ------> USART1_RX
//	*/
//
//	/*Configure GPIO pin : PA */
//	gpio_set_mode(	GPIOB,
//					GPIO_Pin_6 | GPIO_Pin_7,
//					GPIO_AF_OUTPUT_PP,
//					GPIO_SPEED_MEDIUM,
//					0);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_0);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_0);
//#endif
//
//#ifdef USE_UART3
//	/** USART1 GPIO Configuration
//	PC10   ------> USART3_TX
//	PC11   ------> USART3_RX
//	*/
//
//	gpio_set_mode(	GPIOC,
//					GPIO_Pin_10|GPIO_Pin_11,
//					GPIO_AF_OUTPUT_PP,
//					GPIO_SPEED_MEDIUM,
//					0);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_1);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_1);
//#endif
//}
//
//
//static void usb_gpio_init()
//{
//
//#ifdef USE_USB
//	gpio_set_mode(	GPIOA,
//					GPIO_Pin_11|GPIO_Pin_12,
//					GPIO_OUTPUT_PP,
//					GPIO_SPEED_FAST,
//					0);
//#endif
//}
//
//
//
//static void i2c_gpio_init()
//{
//
//#ifdef USE_I2C1
//
//	/** I2C1 GPIO Configuration
//	PB6   ------> I2C1_SCL
//	PB7   ------> I2C1_SDA
//	*/
//
//	gpio_set_mode(	GPIOB,
//					GPIO_Pin_8|GPIO_Pin_9,
//					GPIO_AF_OUTPUT_OD,
//					GPIO_SPEED_LOW,
//					0);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_1);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_1);
//#endif
//
//#ifdef USE_I2C2
//	/** I2C2 GPIO Configuration
//	PB10   ------> I2C2_SCL
//	PB11   ------> I2C2_SDA
//	*/
//
//	gpio_set_mode(	GPIOB,
//					GPIO_Pin_10|GPIO_Pin_11,
//					GPIO_AF_OUTPUT_OD,
//					GPIO_SPEED_LOW,
//					0);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_1);
//#endif
//}
//
//
//
//static void spi_gpio_init()
//{
////	GPIO_InitTypeDef   GPIO_InitStructure; unused variable
//
//#ifdef USE_SPI1
//	/** SPI1 GPIO Configuration
//	PB3   ------> SPI1_SCK
//	PB4   ------> SPI1_MISO
//	PB5   ------> SPI1_MOSI
//	*/
//
//	gpio_set_mode(	GPIOB,
//					GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5,
//					GPIO_AF_OUTPUT_PP,
//					GPIO_SPEED_FAST,
//					0);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_0);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_0);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_0);
//#endif
//
//#ifdef USE_SPI2_OUTPUT_ONLY
//	/** SPI2 GPIO Configuration
//	PC3   ------> SPI2_MOSI
//	PB13   ------> SPI2_SCK
//	*/
//
//	gpio_set_mode(	GPIOB,
//					GPIO_Pin_13 | GPIO_Pin_15,
//					GPIO_AF_OUTPUT_PP,
//					GPIO_SPEED_FAST,
//					0);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_0);
//
//	/*Configure GPIO pin alternate function */
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_0);
//#endif
//}
