#include "settings.h"
#include "peripheral.h"
#include "peripheral_config.h"

#include "display.h"

#ifdef CONSOLE_DEBUG
#include "stdio.h"
#endif


//#define SLEEP_CHECK_PIN				POWER_MCU_SUPPLY_IS_ON				//production code
//#define SLEEP_CHECK_PIN			!power_sleep_occured		//for debug

extern uint32_t SystemCoreClock;

void peripheral_deinit()
{
//	uart_deinit();
//	i2c_deinit();
//	pit_init(DISABLE);
//	gpio_all_inactive();
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, DISABLE);
//	SystemInit();				//set internal HSI clock
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
}

void peripheral_init()
{
	//never should fail
	//so we avoid err

	/* MUST Enable SYSCFG clock */
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	//rtc_init();							//rtc should be running in sleep also
	//datetime_enable_dst(false);			//enable dst alarm interupt

	//power_gpio_init();					//prepare power pins

//	if (!SLEEP_CHECK_PIN)	return;		//sleep

	SystemInit();
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, DISABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	//pit_init(ENABLE);
	delay_init();
	gpio_init();	// gpio clocks, i2c,spi,uart, usb gpio init
	//buzzer_gpio_init();

//	i2c_init();
//	EXTI_init();
//	nvic_init();

//#ifdef CONSOLE_DEBUG
//	(void)rs232_open(CONSOLE_USART,CONSOLE_BAUD);
//	setvbuf(stdout, 0, _IONBF, 0);
//#endif
}

//uint8_t peripheral_sleep(power_schema_t schema, uint8_t reset_sleep_flag)
//{
//	ERROR_CODE err;
//
//	gpio_state_backup(GPIO_STATE_OUTPUT_ONLY);			//backup gpio states
//
//	//only exit the sleep when power is on
//	//deep sleep
//	if (!SLEEP_CHECK_PIN)
//	{
//		peripheral_deinit();
//		power_gpio_init();									//reinialize power pins	Periperal memory OFF
//
//		power_prepare_to_schema(POWER_DEEP_SLEEP);
//		while (!SLEEP_CHECK_PIN)
//		{
//			power_activate_schema(POWER_DEEP_SLEEP);		//due to rtc alarm
//		}
//	}
//
//	peripheral_deinit();
//	peripheral_init();
//
//	//test all peripherals after sleep except SD card since it is initialized in memory
//	err = peripheral_device_on(	PERIPHERAL_DEVICE_ALL);
//
//	if(err)
//	{
//		peripheral_ShowError(err,true);
//	}
//
//	display_restore_lines(DISPLAY_OPERATOR);
//	//display_Show(DISPLAY_CUSTOMER,DISPLAY_TILE,DISPLAY_CUSTOMER_WELCOME_MESSAGE,0);
//
//	gpio_state_restore(GPIO_STATE_OUTPUT_ONLY);			//restore gpio states
//
//	power_sleep_occured = !reset_sleep_flag;
//
//	return power_sleep_occured;
//}
//
//uint8_t peripheral_sleep_check(uint8_t reset_sleep_flag)
//{
//
//	if (!SLEEP_CHECK_PIN)
//	{
//		return peripheral_sleep(POWER_DEEP_SLEEP, reset_sleep_flag);
//	} else
//	{
//		uint8_t tmp = power_sleep_occured;
//		if(reset_sleep_flag) power_sleep_occured = 0;
//		return tmp;
//	}
//}
//
//void peripheral_ShowError(ERROR_CODE error, uint8_t block)
//{
//	uint16_t device = peripheral_error_show_device();
//
//	//TODO
//	// Format Error message to display/print
//	//uint8_t message[];
//
//	if (device & PERIPHERAL_DEVICE_DISPLAY_OPERATOR)
//	{
//		//TODO Display Print
//	}
////	else if (device & PERIPHERAL_DEVICE_PRINTER)
////	{
////		//TODO Printer Print
////	}
////	else if (device & PERIPHERAL_DEVICE_DISPLAY_OPERATOR)
////	{
////		//TODO Display Print
////	}
//
//	if(block)
//	{
//		while(1);
//	}
//}


uint16_t peripheral_error_show_device()
{
	ERROR_CODE err = peripheral_device_on(PERIPHERAL_ERROR_DEVICE_NOTIFICATION_1);
	if (err == NO_ERROR) return PERIPHERAL_ERROR_DEVICE_NOTIFICATION_1;

	err = peripheral_device_on(PERIPHERAL_ERROR_DEVICE_NOTIFICATION_2);
	if (err == NO_ERROR) return PERIPHERAL_ERROR_DEVICE_NOTIFICATION_2;

	err = peripheral_device_on(PERIPHERAL_ERROR_DEVICE_NOTIFICATION_3);
	if (err == NO_ERROR) return PERIPHERAL_ERROR_DEVICE_NOTIFICATION_3;

	return NO_ERROR;	//NO DEVICE
}
static void show_error(ERROR_CODE err, uint8_t * text);
static void show_error(ERROR_CODE err, uint8_t * text)
{
	uint8_t dtext[16];

	if (err == NO_ERROR)
	{
		mini_snprintf(dtext, 16, "%s-OK", text);
	} else
	{
		mini_snprintf(dtext, 16, "%s-GRESKA", text);
	}
	display_Show(DISPLAY_CUSTOMER,0,dtext,0);
	timeout_Waitms(1000);
}
ERROR_CODE peripheral_device_on(uint16_t device)
{
	uint8_t display_reset = 0;
	ERROR_CODE err = NO_ERROR;


	if(PERIPHERAL_DEVICE_LCD & device)
	{
		err = LCD_Init();
		HANDLE_ERROR(err);

		//LCD_Clear(WHITE);
	}

	if(PERIPHERAL_DEVICE_TOUCH & device)
	{
		err = Touch_Init();
		HANDLE_ERROR(err);
	}

	//	if(PERIPHERAL_DEVICE_RTC & device)
//	{
//		err = rtc_peripheral_test();
//		HANDLE_ERROR(err);
//	}

	return err;
}



//static void power_gpio_init()
//{
//
//	RCC_AHBPeriphClockCmd(POWER_MCU_SUPPLY_CLOCK, ENABLE);
//	gpio_set_mode(	POWER_MCU_SUPPLY_PORT,
//					POWER_MCU_SUPPLY_PIN,
//					GPIO_INPUT_PD,
//					GPIO_SPEED_FAST,
//					0);
//}



