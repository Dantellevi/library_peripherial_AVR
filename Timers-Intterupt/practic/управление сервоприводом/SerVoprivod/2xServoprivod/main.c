/*
 * 2xServoprivod.c
 *
 * Created: 05.12.2017 19:34:45
 * Author : Dante_L_Levi
 */ 

#include "Main.h"
volatile unsigned int Danie_1Servo = 75,Danie_2Servo = 0,Sot = 0;  


ISR (TIMER1_COMPA_vect)  //��������� ���� ������ 1 ������������
{
	PORTA &=~(1<<PA0); 	  // ��������� �������� ��  1 ������������
	OCR1A =  Danie_1Servo;

}

ISR (TIMER1_COMPB_vect)  // ��������� ���� ������ 2 ������������
{
	PORTA &=~(1<<PA1);      // ��������� �������� ��  2 ������������
	OCR1B =  Danie_2Servo;

}

ISR(TIMER1_OVF_vect)	//��������� 20��. 50��
{
	PORTA |=(1<<PA0);       //������ �������� ��  1 ������������
	PORTA |=(1<<PA1);       //������ �������� ��  2 ������������
	Sot++;

}


void Port_init(void)
{
	
	DDRA|=(1<<PA0)|(1<<PA1);


}

/*
t=Fcpu/F/del=8000000/50/64=2500

������������ �������� 0.6ms(0 ��������)-2ms(180 ��������)
�������� ��������:
8000000/64=125kHz
tp=1/125kHz=8us
�������� ��� �������� ��������:
600us/8us=75-������� �� 0 ��������
2000us/8us=250-180 ��������




*/
void Timer_init(void)
{

	ICR1 = 2500;          //��������� 20��. �� 8���.
	OCR1A = 75;
	OCR1B = 75;
	TIMSK |=(1<<TOIE1)|(1<<OCIE1A)|(1<<OCIE1B);  // ��������� ������ ����������
	TCCR1A |=(1<<WGM11);                         // ������� ��� ����� FastPWM

	TCCR1B |= (1 << ICES1)|(1<<CS10)|(1<<CS11)|(1<<WGM12)|(1<<WGM13);   //����������� 64,������� ��� ����� FastPWM (����� ��� ����������)
	
	

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
			//Danie_1Servo = 300;  // ������ �� 1 ������������
		//}
		//if ( Sot == 200)
		//{
			//Danie_1Servo = 75;  // ������ �� 1 ������������
			//Sot = 0;
		//}

		asm("nop");

    }
}

