/*
 * Cathod_Control.c
 *
 * Created: 08.12.2017 11:39:21
 * Author : Dante_L_Levi
 */ 

#include "Main.h"

void Port_init(void)
{
	DDRD=0xFF;
	PORTD=0x00;

	DDRC=0xFF;
	PORTC=0x00;


}

int main(void)
{
    Port_init();
	Timer_init();
	sei();
	ledprint(2679);
    while (1) 
    {
    }
}

