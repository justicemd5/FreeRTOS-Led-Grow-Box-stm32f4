/*
 * display.h
 *
 *  Created on: Jan 20, 2014
 *      Author: nihad
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "display_config.h"
#include "error_codes.h"

#define	DISPLAY_TILE	0x04
#define CURSOR_ON		0x02
#define BLINK_ON		0x01

ERROR_CODE display_IsAttached(DISPLAY display);

ERROR_CODE display_Clear(DISPLAY display);
void display_save_text(DISPLAY display, uint8_t enable);
ERROR_CODE display_Control(DISPLAY display, uint8_t control);
ERROR_CODE display_SetCursorPosition(DISPLAY display, uint8_t row, uint8_t column);
void display_Data(DISPLAY display, uint8_t data);
ERROR_CODE display_Show(DISPLAY display, uint8_t control, uint8_t * line1, uint8_t * line2);
void display_ShowLogo(void);
void display_restore_lines(DISPLAY display);
ERROR_CODE display_peripheral_Test(uint8_t display);

#ifdef TEST
	ERROR_CODE display_Test(void);
#endif
#endif /* DISPLAY_H_ */
