//#ifndef POWER_CONFIG_H_
//#define POWER_CONFIG_H_
//
//#include "settings.h"
//
//typedef enum
//{
//	POWER_RUN,
//	POWER_DEEP_SLEEP,
//	POWER_DISPAY_MEMORIES_OFF_WAKE_FROM_KEYBOARD,
//	POWER_MEMORIES_OFF
//} power_schema_t;
//
//
//#define POWER_ADAPTOR_SUPPLY_CLOCK				RCC_AHBPeriph_GPIOA
//#define POWER_ADAPTOR_SUPPLY_PORT				GPIOA
//#define POWER_ADAPTOR_SUPPLY_PIN				GPIO_Pin_4
//#define POWER_ADAPTOR_SUPPLY_IS_ON				gpio_read_pin(POWER_ADAPTOR_SUPPLY_PORT, POWER_ADAPTOR_SUPPLY_PIN)
//#define POWER_ADAPTOR_SUPPLY_EXTI_PORT			EXTI_PortSourceGPIOA
//#define POWER_ADAPTOR_SUPPLY_EXTI_PIN			EXTI_PinSource4
//#define POWER_ADAPTOR_SUPPLY_EXTI_LINE			EXTI_Line4
//#define POWER_ADAPTOR_SUPPLY_NVIC_CHANNEL		EXTI4_15_IRQn
//
//#define POWER_BATTERY_SUPPLY_CLOCK				RCC_AHBPeriph_GPIOA
//#define POWER_BATTERY_SUPPLY_PORT				GPIOA
//#define POWER_BATTERY_SUPPLY_PIN				GPIO_Pin_10
//#define POWER_BATTERY_SUPPLY_IS_ON				gpio_read_pin(POWER_BATTERY_SUPPLY_PORT, POWER_BATTERY_SUPPLY_PIN)
//#define POWER_BATTERY_SUPPLY_EXTI_PORT			EXTI_PortSourceGPIOA
//#define POWER_BATTERY_SUPPLY_EXTI_PIN			EXTI_PinSource10
//#define POWER_BATTERY_SUPPLY_EXTI_LINE			EXTI_Line10
//#define POWER_BATTERY_SUPPLY_NVIC_CHANNEL		EXTI4_15_IRQn
//
//#define POWER_MCU_SUPPLY_CLOCK					RCC_AHBPeriph_GPIOC
//#define POWER_MCU_SUPPLY_PORT					GPIOC
//#define POWER_MCU_SUPPLY_PIN					GPIO_Pin_13
//#define POWER_MCU_SUPPLY_IS_ON					gpio_read_pin(POWER_MCU_SUPPLY_PORT, POWER_MCU_SUPPLY_PIN)
//#define POWER_MCU_SUPPLY_EXTI_PORT				EXTI_PortSourceGPIOC
//#define POWER_MCU_SUPPLY_EXTI_PIN				EXTI_PinSource13
//#define POWER_MCU_SUPPLY_EXTI_LINE				EXTI_Line13
//#define POWER_MCU_SUPPLY_EXTI_FLAG				EXTI_Line13
//#define POWER_MCU_SUPPLY_NVIC_CHANNEL			EXTI4_15_IRQn
//
//#define POWER_KEYBOARD_WAKE_CLOCK				RCC_AHBPeriph_GPIOC
//#define POWER_KEYBOARD_WAKE_PORT				GPIOC
//#define POWER_KEYBOARD_WAKE_PIN					GPIO_Pin_5
//#define POWER_KEYBOARD_WAKE_IS_ON				gpio_read_pin(POWER_KEYBOARD_WAKE_PORT, POWER_KEYBOARD_WAKE_PIN)
//#define POWER_KEYBOARD_WAKE_EXTI_PORT			EXTI_PortSourceGPIOC
//#define POWER_KEYBOARD_WAKE_EXTI_PIN			EXTI_PinSource5
//#define POWER_KEYBOARD_WAKE_EXTI_LINE			EXTI_Line5
//#define POWER_KEYBOARD_WAKE_EXTI_FLAG			EXTI_Line5
//#define POWER_KEYBOARD_WAKE_NVIC_CHANNEL		EXTI4_15_IRQn
//
//#endif
