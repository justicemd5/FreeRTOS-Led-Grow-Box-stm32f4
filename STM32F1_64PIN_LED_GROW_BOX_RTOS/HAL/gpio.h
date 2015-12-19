#ifndef GPIO_H_
#define GPIO_H_

#include "settings.h"
#include "error_codes.h"
#include "gpio_config.h"

void gpio_init();

//only input output mode
void gpio_set_mode(GPIO_PORT_STRUCT port, GPIO_PIN_STRUCT pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, bool_t defaultvalue);
void gpio_set_alternate(GPIO_PORT_STRUCT port, GPIO_AF_PIN_STRUCT pin, GPIO_AF_MODE af);
void gpio_exti_config(GPIO_PORT_STRUCT port, GPIO_PIN_STRUCT pin);
void gpio_nvic_config(GPIO_PORT_STRUCT port, GPIO_PIN_STRUCT pin);
void gpio_ports_reset();
void gpio_all_inactive();
void gpio_state_backup(gpio_state_t state);
void gpio_state_restore(gpio_state_t state);

#endif //GPIO_H
