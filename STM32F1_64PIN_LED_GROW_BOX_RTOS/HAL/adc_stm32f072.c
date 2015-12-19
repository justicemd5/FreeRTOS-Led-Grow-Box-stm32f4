//
//#include "adc.h"
//#include "timeout.h"
//
//static ERROR_CODE adc_check_flag(ADC_REG * reg, uint32_t flag, uint32_t timeout, uint8_t state);
//
//void adc_init(ADC_REG * reg, ADC_INIT_STRUCT * data)
//{
//	ADC_DeInit(reg);
//
//    if (reg == ADC1)
//    {
//    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
//    }
//
//    if (data == 0)
//    {
//    	ADC_INIT_STRUCT new_data;
//    	new_data.ADC_Resolution = ADC_Resolution_12b;
//    	new_data.ADC_ContinuousConvMode = DISABLE;
//    	new_data.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
//    	new_data.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;
//    	new_data.ADC_DataAlign = ADC_DataAlign_Right;
//    	new_data.ADC_ScanDirection = ADC_ScanDirection_Upward;
//    	ADC_Init(reg, &new_data);
//    	ADC_ChannelConfig(reg, ADC_Channel_13 , ADC_SampleTime_41_5Cycles);
//    	ADC_GetCalibrationFactor(reg);
//    }
//
//    ADC_AutoPowerOffCmd(reg, ENABLE);
//    ADC_Cmd(reg, ENABLE);
//}
//
//ERROR_CODE adc_deinit(ADC_REG * reg)
//{
//	ADC_DeInit(reg);
//
//    if (reg == ADC1)
//    {
//    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, DISABLE);
//    }
//
//    return NO_ERROR;
//}
//
//ERROR_CODE adc_measure(ADC_REG * reg, ADC_VALUE_STRUCT * value)
//{
//	ERROR_CODE err;
//
//	reg->CR |= (uint32_t)ADC_CR_ADSTART;
//	while(RESET == ADC_GetFlagStatus(reg, ADC_FLAG_EOC))
//	{
//		err = 1;
//	}
//	err = adc_check_flag(reg, ADC_FLAG_EOC, ADC_TIMEOUT_us, RESET);
//
//	ADC_StopOfConversion(reg);
//
//	HANDLE_ERROR(err);
//
//	*value = (ADC_VALUE_STRUCT)ADC_GetConversionValue(reg);
//
//	return NO_ERROR;
//}
//
//static ERROR_CODE adc_check_flag(ADC_REG * reg, uint32_t flag, uint32_t timeout, uint8_t state)
//{
//	timeout_AsyncWaitus(0,timeout);
//
//	while((state == ADC_GetFlagStatus(reg, flag)) && !timeout_AsyncIsElapsed(0));
//
//	timeout_AsyncStop(0);
//
//	if(state == ADC_GetFlagStatus(reg, flag))
//	{
//		return PRINTER_ADC_MEASUREMENT_FAILED;
//	}
//	return NO_ERROR;
//}
//
