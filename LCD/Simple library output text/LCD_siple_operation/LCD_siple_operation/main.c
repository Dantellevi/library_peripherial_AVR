/*
 * LCD_siple_operation.c
 *
 * Created: 26.09.2017 16:58:33
 * Author : Dante_L_Levi
 */ 


 #include "Main.h"

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
    
    while (1) 
    {

    }
}

