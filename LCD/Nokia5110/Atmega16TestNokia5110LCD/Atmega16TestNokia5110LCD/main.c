/*
 *
 *
 * Created: 02.10.2017 13:47:10
 * Author :Лепотенко А.С.
 */ 

#include "Main.h"

void Port_ini(void)
{


}



int main(void)
{
Port_ini();
Lcd_init();
Lcd_clear();




    while (1) 
    {
	
	Lcd_prints(0,0,FONT_1X,(unsigned char *)PSTR("Привет"));
	Lcd_prints(0,3,FONT_1X,(unsigned char *)PSTR("Hello"));
	Lcd_update();
    }
}

