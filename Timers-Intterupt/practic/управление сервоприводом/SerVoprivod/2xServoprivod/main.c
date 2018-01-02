/*
 * 2xServoprivod.c
 *
 * Created: 05.12.2017 19:34:45
 * Author : Dante_L_Levi
 */ 

#include "Main.h"
volatile unsigned int Danie_1Servo = 75,Danie_2Servo = 0,Sot = 0;  


ISR (TIMER1_COMPA_vect)  //формируем угол здвига 1 сервопривода
{
	PORTA &=~(1<<PA0); 	  // завершаем импульса дл¤  1 сервопривода
	OCR1A =  Danie_1Servo;

}

ISR (TIMER1_COMPB_vect)  // формируем угол здвига 2 сервопривода
{
	PORTA &=~(1<<PA1);      // завершаем импульса дл¤  2 сервопривода
	OCR1B =  Danie_2Servo;

}

ISR(TIMER1_OVF_vect)	//формеруем 20мс. 50гц
{
	PORTA |=(1<<PA0);       //нач¤ло импульса дл¤  1 сервопривода
	PORTA |=(1<<PA1);       //нач¤ло импульса дл¤  2 сервопривода
	Sot++;

}


void Port_init(void)
{
	
	DDRA|=(1<<PA0)|(1<<PA1);


}

/*
t=Fcpu/F/del=8000000/50/64=2500

длительность импульса 0.6ms(0 градусов)-2ms(180 градусов)
Цифровые значения:
8000000/64=125kHz
tp=1/125kHz=8us
значение для счетного регистра:
600us/8us=75-поворот на 0 градусов
2000us/8us=250-180 градусов




*/
void Timer_init(void)
{

	ICR1 = 2500;          //формеруем 20мс. дл¤ 8ћгц.
	OCR1A = 75;
	OCR1B = 75;
	TIMSK |=(1<<TOIE1)|(1<<OCIE1A)|(1<<OCIE1B);  // разрешаем работу прерывани¤м
	TCCR1A |=(1<<WGM11);                         // младшие бит режим FastPWM

	TCCR1B |= (1 << ICES1)|(1<<CS10)|(1<<CS11)|(1<<WGM12)|(1<<WGM13);   //пределитель 64,старший бит режим FastPWM (сброс при совпадении)
	
	

}

int main(void)
{
    Port_init();
	Timer_init();
	Initilizer_Interrupt(FLAG_INT0,FLAG_LOW_LEVEL);
	sei();
    while (1) 
    {
		//if ( Sot == 100)
		//{
			//Danie_1Servo = 300;  // данные дл¤ 1 сервопривода
		//}
		//if ( Sot == 200)
		//{
			//Danie_1Servo = 75;  // данные дл¤ 1 сервопривода
			//Sot = 0;
		//}

		asm("nop");

    }
}

