//#include "ifm.h"
//
//// funkcija koja èisti cijelu stranicu u memoriji
//ERROR_CODE ifm_memorypage_clear(uint32_t address)
//{
//	FLASH_Status	result;
//
//	FLASH_Unlock();
//	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
//
//	result = FLASH_ErasePage(address);
//	if (result != FLASH_COMPLETE)
//	{
//		FLASH_Lock();
//		return INTERNAL_FLASH_CLEAR_PAGE_ERROR;
//	}
//
//	FLASH_Lock();
//	return NO_ERROR;
//}
//
//// upis stringa na relativnu lokaciju definisanu offset-om
//ERROR_CODE ifm_string_write(uint32_t address, const uint8_t * dataBuffer, uint32_t dataSize)
//{
//	uint32_t 		tempAddress;
//	uint32_t 		tempData;
//	FLASH_Status	result;
//
//	tempAddress = address;
//
//	FLASH_Unlock();
//	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
//
//	uint32_t i = 0;
//	for(i=0; i<dataSize; i+=4)  {
//
//		// ukoliko je osigurano da je velicina ulaznog bafera djeljiva sa 4, upotreba ovog control-a nije potrebna
//		// najmanja jedinica koja se upisuje u memoriju su 24 bita (FLASH_ProgramWord), i ukoliko je duzina k, potrebno je osigurati da u ulaznom podatku ima 24-k nula
//		// zato se koristi ovaj control, takodjer vazno je da se koristi Little Endian nacin redanja bajta u memoriji
//		uint8_t control = 0;
//		if ( (i+5) > dataSize ) control = dataSize % 4;
//		tempData = 0x00000000;
//
//		if (control == 0) {
//			tempData = dataBuffer[i+3];
//			tempData = tempData << 8;
//			tempData+=dataBuffer[i+2];
//			tempData = tempData << 8;
//			tempData+=dataBuffer[i+1];
//			tempData = tempData << 8;
//			tempData+=dataBuffer[i];
//		} else if (control == 3) {
//			tempData = tempData << 8;
//			tempData+=dataBuffer[i+2];
//			tempData = tempData << 8;
//			tempData+=dataBuffer[i+1];
//			tempData = tempData << 8;
//			tempData+=dataBuffer[i];
//		} else if (control == 2) {
//			tempData = tempData << 8;
//			tempData = tempData << 8;
//			tempData+=dataBuffer[i+1];
//			tempData = tempData << 8;
//			tempData+=dataBuffer[i];
//		} else if (control == 1) {
//			tempData = tempData << 8;
//			tempData = tempData << 8;
//			tempData = tempData << 8;
//			tempData+=dataBuffer[i];
//		}
//
//		result = FLASH_ProgramWord(tempAddress, tempData);
//		if (result != FLASH_COMPLETE)
//		{
//			FLASH_Lock();
//			return INTERNAL_FLASH_WRITE_ERROR;
//		}
//		tempAddress+=4;
//	}
//
//	FLASH_Lock();
//	return NO_ERROR;
//}
//
//// data size, mora biti djeljivo sa 4 !
//// citanje stringa sa relativne lokacije definisane offset-om
//void ifm_string_read(uint32_t address, uint8_t * dataBuffer, uint32_t dataSize)
//{
//	uint32_t 	*pointer_to_adress;
//	uint32_t 	tempData;
//
//	pointer_to_adress = address;
//	tempData = *pointer_to_adress;
//
//	uint8_t i = 0;
//	for(i=0; i<dataSize; i+=4) {
//		dataBuffer[i] = tempData;
//
//		tempData = tempData >> 8;
//		dataBuffer[i+1] = tempData;
//
//		tempData = tempData >> 8;
//		dataBuffer[i+2] = tempData;
//
//		tempData = tempData >> 8;
//		dataBuffer[i+3] = tempData;
//
//		pointer_to_adress += 1;
//		tempData = *pointer_to_adress;
//	}
//
//}
//
//// upis int-a na relativnu lokaciju definisanu offset-om
//ERROR_CODE ifm_uint32_write(uint32_t address, uint32_t value)
//{
//	uint32_t 		tempAddress;
//	FLASH_Status	result;
//
//	tempAddress = address;
//
//	FLASH_Unlock();
//	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
//
//	result = FLASH_ProgramWord(tempAddress, value);
//	if (result != FLASH_COMPLETE)
//	{
//		FLASH_Lock();
//		return INTERNAL_FLASH_WRITE_ERROR;
//	}
//
//	FLASH_Lock();
//	return NO_ERROR;
//}
//
//// citanje int-a sa relativne lokacije definisane offset-om
//uint32_t ifm_uint32_read(uint32_t address)
//{
//	uint32_t 	*pointer_to_adress;
//	uint32_t 	tempData;
//
//	pointer_to_adress = address;
//	tempData = *pointer_to_adress;
//
//	return tempData;
//}
