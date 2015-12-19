#include "stdint.h"
#include "settings.h"

#define WATCHDOG_TIMEOUT_SECONDS	60

void watchdog_Reset();
uint8_t watchdog_IsReset();
