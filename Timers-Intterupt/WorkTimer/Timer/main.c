/*
 * Timer.c
 *
 * Created: 09.11.2017 11:19:12
 * Author : Dante_L_Levi
 */ 

#include "Main.h"



int main(void)
{
	DDRD|=(1<<PD0);
	PORTD&=~(1<<PD0);
	DDRD|=(1<<PD1);
	PORTD&=~(1<<PD1);
	DDRD|=(1<<PD2);
	PORTD&=~(1<<PD2);
	DDRD|=(1<<PD4);
	PORTD&=~(1<<PD4);
	DDRD|=(1<<PD5);
	PORTD&=~(1<<PD5);

	//===============Проверка===================================
	//Timer0_init(0,CTC_MODE,156,FLAG_DEL_1024);
	//Timer2_init_normalMode(21,NORMAL_MODE,0,FLAG_DEL_1024);
	//Timer2_init_normalMode(0,CTC_MODE,195,FLAG_DEL_1024);
	//Timer_init_16bit(57722,NORMAL_MODE,0,0,FLAG_DEL_1024);
	//Timer_init_16bit(0,CTC_MODE,CTC_OCR1A,7812,FLAG_DEL_1024);
	PWM1_init(900,FLAG_10BIT,PWM_MODE_FIRST,FLAG_DEL_1024,FLAG_CH_OCR1A);
	sei();
    /* Replace with your application code */
    while (1) 
    {
    }
}

