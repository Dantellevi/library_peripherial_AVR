/*************************************************************************
Title:    AVR-USB, ATMEGA16 @ 12MHz + universal PCB V2.0
Author:   Levas Vabolis
File:     main.c
Software: AVR-GCC x.x
Hardware: 
* FUSE _LOW = 0xCE, _HIGH = 0xD9 (2F, D1 irgi veikia)
*
**************************************************************************/

//#define togle	PORTB ^= _BV(2)
//#define high		PORTB |= _BV(2)
//#define low		PORTB &= ~_BV(2)


#include <stdlib.h>
#include <avr/io.h>
#include	<avr/pgmspace.h>  
#include <util\delay.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>
#include <string.h>
#include "spi.c"
#include "lcd.c"
#include "ili9341.c"




char tbuffer[17];




int main(void)
{
unsigned int x,y,c;


/* TAI TESTINIS grafinio "blob" masyvas */
unsigned char buffer[4*4*3]={

0xFF,3,3, 0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, 3,0xFF,3,
0xFF,3,3, 3,3,3, 3,3,3, 3,0xFF,3,
0xFF,3,3, 3,3,3, 3,3,3, 3,0xFF,3,
0xFF,3,3, 3,3,0xFF, 3,3,0xFF, 3,0xFF,3

};



ili9341_init();	

/* tekstinio LCD debugas */
    lcd_init(LCD_DISP_ON);
	lcd_command(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("C:");
/* tekstinio LCD */

lcdFillRGB(BLACK);


c=0;
for(;;){

lcdDrawVLine(120,100, 50, CYAN);
lcdDrawHLine(120,100, 50, YELLOW);
lcdFillCircle(50,50,10,CYAN);
lcdDrawRectangle(20,20,30,30,MAGENTA);

lcdDrawBMP(100,160,4,4,buffer);
lcdDrawString("http://www.vabolis.lt",5,120,1,WHITE);
lcdDrawString("http://www.vabolis.lt",5,180,2,WHITE);


c++;
		itoa( c, tbuffer, 10);
		lcd_gotoxy(3,0);
		lcd_puts(tbuffer); lcd_puts("  ");

while(1){
	for(x=200;x < 240; x=x+5)
	{
		for(y=280;y<320;y=y+5)
			{
				//lcdDrawPixel(x,y,x*y+c);
				lcdFilledRec(x,y,3,3,x*y+c);
				c++;
			}
	}
	}

}		

return 0;
}