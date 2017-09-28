/*
 * LCD_siple_operation.c
 *
 * Created: 26.09.2017 16:58:33
 * Author : Dante_L_Levi
 */ 


 #include "Main.h"
 #include <avr/pgmspace.h>

 const uint8_t PROGMEM text_1[]="Люби Родину!!!";

 void Port_init(void)
 {
 DDRD=0xFF;
 PORTD=0x00;

 }
 

int main(void)
{
	Port_init();
	LCDinit();
	LCDstringXY("Hello World",0,1);
	LCDstring_of_flashXY(text_1,1,0);

    
    while (1) 
    {

    }
}

