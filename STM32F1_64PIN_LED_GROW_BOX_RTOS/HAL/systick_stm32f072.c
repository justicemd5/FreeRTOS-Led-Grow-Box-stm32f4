#include "pit.h"

//ERROR_CODE pit_init(void);
void pit_start(uint8_t channel, uint32_t usTimeout, uint8_t isrEnable);
uint8_t pit_timeout(uint8_t channel);
void pit_stop(uint8_t channel);
