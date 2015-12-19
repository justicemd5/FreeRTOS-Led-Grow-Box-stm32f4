#ifndef FM_H_
#define FM_H_

#include "fm_config.h"
#include "error_codes.h"

//public prototypes
ERROR_CODE fm_Write(uint32_t address, uint8_t * data, uint8_t length, uint8_t* successful_written_bytes);
ERROR_CODE fm_Read(uint32_t address, uint8_t * data, uint8_t length);
ERROR_CODE fm_Erase(void);
ERROR_CODE fm_peripheral_Test();

#ifdef TEST
	ERROR_CODE fm_Test(void);
#endif

#endif /* FM_H_ */
