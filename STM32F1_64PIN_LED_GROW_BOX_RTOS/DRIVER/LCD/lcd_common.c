#include <stdio.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "lcd.h"
#include "lcd_common.h"
#include "stm32f10x.h"

unsigned short deviceid=0;

// we use this sempaphore to ensure multiple threads do not try to use the LCD at the same time
xSemaphoreHandle xLcdSemaphore;

#define rw_data_prepare()               write_cmd(34)

#define LCD_REG              (*((volatile unsigned short *) 0x60000000)) /* RS = 0 */
#define LCD_RAM              (*((volatile unsigned short *) 0x60020000)) /* RS = 1 */


void write_reg(unsigned char reg_addr,unsigned short reg_val);
unsigned short read_reg(unsigned char reg_addr);
unsigned short lcd_read_gram(unsigned int x,unsigned int y);

//
// Note that we call init BEFORE the main OS scheduler is running so we
// cannot use the os delay routines.
//
void Delay(unsigned i)
{
    unsigned n;
    for(;i;i--)
    {
	for(n=0;n<3100;n++)
	{
	    asm("nop");
	}
    }
}



unsigned short BGR2RGB(unsigned short c)
{
    u16  r, g, b, rgb;

    b = (c>>0)  & 0x1f;
    g = (c>>5)  & 0x3f;
    r = (c>>11) & 0x1f;

    rgb =  (b<<11) + (g<<5) + (r<<0);

    return( rgb );
}

void write_cmd(unsigned short cmd)
{
    LCD_REG = cmd;
}

unsigned short read_data(void)
{
    return LCD_RAM;
}

void write_data(unsigned short data_code )
{
    LCD_RAM = data_code;
}

void write_reg(unsigned char reg_addr,unsigned short reg_val)
{
    write_cmd(reg_addr);
    write_data(reg_val);
}

unsigned short read_reg(unsigned char reg_addr)
{
    unsigned short val=0;
    write_cmd(reg_addr);
    val = read_data();
    return (val);
}

unsigned int lcd_getdeviceid(void)
{
    return deviceid;
}

unsigned short lcd_read_gram(unsigned int x,unsigned int y)
{
    unsigned short temp;
    lcd_SetCursor(x,y);
    rw_data_prepare();
    /* dummy read */
    temp = read_data();
    temp = read_data();
    return temp;
}


#define MAX_X 319
#define MAX_Y 239




static __inline void lcd_write_ram_prepare(void)
{
    write_cmd(0x22);
}

static void lcd_set_cursor(uint16_t Xpos,uint16_t Ypos)
{
	lcd_SetCursor(Ypos, MAX_X - Xpos);
}

static void lcd_char_xy(unsigned short Xpos,unsigned short Ypos,unsigned char c,unsigned short charColor,unsigned short bkColor)
{
    unsigned short i=0;
    unsigned short j=0;
    const unsigned char *buffer = AsciiLib[(c - 32)] ;
    unsigned char tmp_char=0;
    for (i=0;i<16;i++)
    {

	tmp_char=buffer[i];
	for (j=0;j<8;j++)
	{
	    if ( (tmp_char >> 7-j) & 0x01)
	    {
		lcd_set_cursor(Xpos + j,Ypos+i);
		lcd_write_ram_prepare();
		write_data(charColor);
	    }


	    //uint16_t col = ( (tmp_char >> 7-j) & 0x01) ? charColor : bkColor;
	    //write_data(col);
	}
    }
}

 void lcd_DrawHLine(int x1, int x2, int col, int y )
{
    uint16_t ptr;
    //Set up registers for horizontal scanning
//    write_reg(0x0003,(1<<12)|(1<<5)|(1<<4) | (0<<3) );

    lcd_SetCursor(x1, y); //start position
    rw_data_prepare(); /* Prepare to write GRAM */
    while (x1 <= x2)
    {
        write_data(col);
        x1 ++;

    }
}

 void lcd_DrawVLine(int y1, int y2, int col, int x)
{
    unsigned short p;

    //Set up registers for vertical scanning
//    write_reg(0x0003,(1<<12)|(1<<5)|(0<<4) | (1<<3) );

    lcd_SetCursor(x, y1); //start position
    rw_data_prepare(); /* Prepare to write GRAM */
    while (y1 <= y2)
    {
        write_data(col);
        y1++;
    }
}

static uint16_t bg_col;

//////////////////////////////////////////////////////////////////////////////////////////////////
// LOCKING code
//////////////////////////////////////////////////////////////////////////////////////////////////
static volatile xTaskHandle lcdUsingTask = NULL;

void lcd_lock()
{
    while( xSemaphoreTake( xLcdSemaphore, ( portTickType ) 100 ) != pdTRUE )
    {
	printf("Waiting a long time for LCD\r\n");
    }
    lcdUsingTask = xTaskGetCurrentTaskHandle();
}

void lcd_release()
{
    xSemaphoreGive(xLcdSemaphore);
    lcdUsingTask = NULL;
}

#define LCD_LOCK char auto_lock = 0;if (lcdUsingTask != xTaskGetCurrentTaskHandle()){ lcd_lock(); auto_lock = 1; }
#define LCD_UNLOCK if (auto_lock) lcd_release()


/////////////////////////////////////////////////////////////////////////////////////////////////
// THREADSAFE INTERFACE - uses semaphores to unsure only one thread is drawing at a time
/////////////////////////////////////////////////////////////////////////////////////////////////

void lcd_text_xy(uint16_t Xpos, uint16_t Ypos, const char *str,uint16_t Color, uint16_t bkColor)
{
    LCD_LOCK;
    uint8_t TempChar;

//	printf("lcd text %d,%d %s\r\n", Xpos, Ypos, str);

    while ((TempChar=*str++))
    {
	lcd_char_xy(Xpos,Ypos,TempChar,Color,bkColor);
	if (Xpos < MAX_X - 8)
	{
	    Xpos+=8;
	}
	else if (Ypos < MAX_Y - 16)
	{
	    Xpos=0;
	    Ypos+=16;
	}
	else
	{
	    Xpos=0;
	    Ypos=0;
	}
    }
    LCD_UNLOCK;
}

void lcd_text(uint8_t col, uint8_t row, const char *text)
{
    lcd_text_xy(col * 8, row * 16, text, 0xFFFF, bg_col);
}

void lcd_fill(uint16_t xx, uint16_t yy, uint16_t ww, uint16_t hh, uint16_t color)
{
	int ii, jj;
    LCD_LOCK;
    for ( ii = 0; ii < hh; ii++)
    {
	lcd_set_cursor(xx, yy + ii);
	lcd_write_ram_prepare();
	for ( jj = 0; jj < ww; jj++)
	{
	    write_data(color);
	}
    }
    LCD_UNLOCK;
}

#include <stdarg.h>
void lcd_printf(uint8_t col, uint8_t row, uint8_t ww, const char *fmt, ...)
{
    LCD_LOCK;
    char message[31];
    va_list ap;
    va_start(ap, fmt);
    int len = vsnprintf(message, sizeof(message) - 1, fmt, ap);
    va_end(ap);

    while (len < ww && len < sizeof(message) - 2)
    {
    	message[len++] = ' ';
    }
    message[len] = 0;

    lcd_text(col, row, message);

    LCD_UNLOCK;
}

void lcd_clear(uint16_t Color)
{
    LCD_LOCK;
    uint32_t index=0;
    lcd_set_cursor(0,0);
    lcd_write_ram_prepare(); /* Prepare to write GRAM */
    for(index = 0; index < LCD_W * LCD_H; index++)
    {
	write_data(Color);
    }
    LCD_UNLOCK;
}

void lcd_background(uint16_t color)
{
    bg_col = color;
}

void lcd_DrawRect(int x1, int y1, int x2, int y2, int col)
{
    LCD_LOCK;
    lcd_DrawVLine(y1, y2, col, x1);
    lcd_DrawVLine(y1, y2, col, x2);
    lcd_DrawHLine(x1, x2, col, y1);
    lcd_DrawHLine(x1, x2, col, y2);
    LCD_UNLOCK;
}

void display_on()
{
    write_reg(0x000C,0x1003);
}

void display_off()
{
    write_reg(0x000F,0x0010);

    write_reg(0x000C,0x1023);
}
