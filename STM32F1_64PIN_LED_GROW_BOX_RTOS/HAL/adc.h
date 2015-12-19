#ifndef ADC_H_
#define ADC_H_

#include "adc_config.h"
#include "error_codes.h"

void adc_init(ADC_REG * reg, ADC_INIT_STRUCT * data);
ERROR_CODE adc_deinit(ADC_REG * reg);
ERROR_CODE adc_measure(ADC_REG * reg, ADC_VALUE_STRUCT * value);

#endif
