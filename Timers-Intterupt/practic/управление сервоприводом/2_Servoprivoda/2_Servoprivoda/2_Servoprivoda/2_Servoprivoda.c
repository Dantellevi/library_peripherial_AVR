/*
 * _2_Servoprivoda.c
 * Created: 08.12.2014 7:52:03
 *  Author: ������� �.�.
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>           //���������� ���������� 
volatile unsigned int Danie_1Servo = 0,Danie_2Servo = 0,Sot = 0;   
 ISR (TIMER1_COMPA_vect)  //��������� ���� ������ 1 ������������
  {
	PORTA &=~(1<<0); 	  // ��������� �������� ���  1 ������������
  	OCR1A =  Danie_1Servo;				 		 			   		  		  			 			   	 
  }
 ISR (TIMER1_COMPB_vect)  // ��������� ���� ������ 2 ������������
  {
	PORTA &=~(1<<1);      // ��������� �������� ���  2 ������������
	OCR1B =  Danie_2Servo; 			  		 			   		  		  			 			   	 
  } 
 ISR(TIMER1_OVF_vect)     //��������� 20��. 50��
  {	 
	PORTA |=(1<<0);       //������ �������� ���  1 ������������ 
	PORTA |=(1<<1);       //������ �������� ���  2 ������������ 
	Sot++;
  }
//*******************//
//*******************//
int main(void)
{
	DDRA |=(1<<0)|(1<<1);           
	ICR1 = 5000;          //��������� 20��. ��� 16���.	
	OCR1A = 150;   
	OCR1B = 150;			 
	TCCR1B |= (1 << ICES1)|(1<<CS10)|(1<<CS11)|(1<<WGM12)|(1<<WGM13);   //����������� 64,������� ��� ����� FastPWM (����� ��� ����������)
	TCCR1A |=(1<<WGM11);                         // ������� ��� ����� FastPWM 	
	TIMSK |=(1<<TOIE1)|(1<<OCIE1A)|(1<<OCIE1B);  // ��������� ������ ����������� 
	
	asm("sei");
  //===========//   
    while(1)
    {
		if ( Sot == 100)
		 {		
		   Danie_1Servo = 500;  // ������ ��� 1 ������������
		 }		  
		if ( Sot == 200) 
		 {
		   Danie_1Servo = 150;  // ������ ��� 1 ������������
		   Sot = 0;  			 
		 }
		asm("nop"); 			  				 		 
    }
}