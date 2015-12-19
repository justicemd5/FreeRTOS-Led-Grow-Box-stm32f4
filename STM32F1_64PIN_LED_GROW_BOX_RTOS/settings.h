
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SETTINGS_H_
#define SETTINGS_H_

#ifndef STM32F1XX_HD
#define STM32F1XX_HD
#endif

#ifndef STM32F103
#define STM32F103
#endif

/* Includes ------------------------------------------------------------------*/
/* Uncomment the line below to enable peripheral header file inclusion */
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"

// #include "stm32f10x_can.h"
// #include "stm32f10x_cec.h"
// #include "stm32f10x_crc.h"
// #include "stm32f10x_dac.h"
// #include "stm32f10x_dbgmcu.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_flash.h"
// #include "stm32f10x_fsmc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"
//#include "stm32f10x_iwdg.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_rtc.h"
// #include "stm32f10x_sdio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
//#include "stm32f10x_wwdg.h"
#include "stm32f10x_fsmc.h"
#include "misc.h"  /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

#include "error_codes.h"
#include "array.h"

extern volatile bool_t power_sleep_occured;

#define CONSOLE_DEBUG

#ifdef CONSOLE_DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x)
#endif

#define CODE_TIME(x) x = ((SysTick_LOAD_RELOAD_Msk -SysTick->VAL) / (SystemCoreClock / 1000000UL));
#define WAIT_FOR_FLAG_CHANGE_OR_TIMEOUT(e,t,tm,err) 		t = tm*3; while((e) && --t);if(t==0) return err;

#define mcu_gpio_clock_enable(x)			RCC_AHBPeriphClockCmd(x, ENABLE)
#define mcu_gpio_clock_disable(x)			RCC_AHBPeriphClockCmd(x, DISABLE)

#define gpio_set_pin(x,y)					GPIO_SetBits(x, y)
#define gpio_reset_pin(x,y)					GPIO_ResetBits(x, y)
#define gpio_read_pin(x,y)					GPIO_ReadInputDataBit(x, y)

#define HANDLE_ERROR(x)						if(NO_ERROR != x) return x;
#define HANDLE_ERROR_WITH_GOTO(x)			if(NO_ERROR != x) goto error;
#define HANDLE_ERROR_CHANGE(x,y)			if(NO_ERROR != x) return y;

#define DO_NOT_OPTIMIZE				__attribute__((optimize("O0")))
#define __WEAK						__attribute__((weak))

#define SLEEP_TEST
#define SLEEP_CHECK					peripheral_sleep_check(0)
#define SLEEP_OCCURED				power_sleep_occured
#define SLEEP_FLAG_CLEAR			power_sleep_occured = 0
//#define SAFE_FUNCTION(x) 			SLEEP_CHECK; x; if(SLEEP_OCCURED) x;

#define USE_EXCEPTION_ON_ERRORS
#define TRING_KASA_ONE

#ifdef TRING_KASA_ONE
#define USE_KEYBOARD

#endif

#define PRODUCTION_CODE

#ifdef PRODUCTION_CODE
#undef DEBUG
#else
#ifndef DEBUG
#define DEBUG
#endif
#endif
/* Exported macro ------------------------------------------------------------*/
//#ifdef  USE_FULL_ASSERT
//
///**
// * @brief  The assert_param macro is used for function's parameters check.
// * @param  expr: If expr is false, it calls assert_failed function which reports
// *         the name of the source file and the source line number of the call
// *         that failed. If expr is true, it returns no value.
// * @retval None
// */
//#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
///* Exported functions ------------------------------------------------------- */
//void assert_failed(uint8_t* file, uint32_t line);
//#else
//#define assert_param(expr) ((void)0)
//#endif /* USE_FULL_ASSERT */

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
