/*
 * _2_Servoprivoda.c
 * Created: 08.12.2014 7:52:03
 *  Author: Писанец А.Н.
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>           //подгружаем прерывание 
volatile unsigned int Danie_1Servo = 0,Danie_2Servo = 0,Sot = 0;   
 ISR (TIMER1_COMPA_vect)  //формируем угол здвига 1 сервопривода
  {
	PORTA &=~(1<<0); 	  // завершаем импульса для  1 сервопривода
  	OCR1A =  Danie_1Servo;				 		 			   		  		  			 			   	 
  }
 ISR (TIMER1_COMPB_vect)  // формируем угол здвига 2 сервопривода
  {
	PORTA &=~(1<<1);      // завершаем импульса для  2 сервопривода
	OCR1B =  Danie_2Servo; 			  		 			   		  		  			 			   	 
  } 
 ISR(TIMER1_OVF_vect)     //формеруем 20мс. 50гц
  {	 
	PORTA |=(1<<0);       //начяло импульса для  1 сервопривода 
	PORTA |=(1<<1);       //начяло импульса для  2 сервопривода 
	Sot++;
  }
//*******************//
//*******************//
int main(void)
{
	DDRA |=(1<<0)|(1<<1);           
	ICR1 = 5000;          //формеруем 20мс. для 16Мгц.	
	OCR1A = 150;   
	OCR1B = 150;			 
	TCCR1B |= (1 << ICES1)|(1<<CS10)|(1<<CS11)|(1<<WGM12)|(1<<WGM13);   //пределитель 64,старший бит режим FastPWM (сброс при совпадении)
	TCCR1A |=(1<<WGM11);                         // младшие бит режим FastPWM 	
	TIMSK |=(1<<TOIE1)|(1<<OCIE1A)|(1<<OCIE1B);  // разрешаем работу прерываниям 
	
	asm("sei");
  //===========//   
    while(1)
    {
		if ( Sot == 100)
		 {		
		   Danie_1Servo = 500;  // данные для 1 сервопривода
		 }		  
		if ( Sot == 200) 
		 {
		   Danie_1Servo = 150;  // данные для 1 сервопривода
		   Sot = 0;  			 
		 }
		asm("nop"); 			  				 		 
    }
}