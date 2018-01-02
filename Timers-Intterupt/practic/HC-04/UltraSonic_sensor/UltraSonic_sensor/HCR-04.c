#include "HCR-04.h"

//==============================���������� ����������==========================
ISR(INT0_vect)
{
	if (Echo_PIN&(1<<EchoNPin))
	{
		timer_Start_Stop(flag_start);
	}
	else if(!(Echo_PIN&(1<<EchoNPin))){
		timer_Start_Stop(flag_stop);
	}

}


//==============================================================================




//=====================������������� ��������������� ������� ����������==========
void HC_SRC04_Init(void)
{
	
	//=================������������� �����==============
	
	//----------------------����� Trig-----------------
	Trig_DDR|=(1<<Trig_NPin);
	Trig_PORT&=~(1<<Trig_NPin);
	//-------------------------------------------------
	
	//----------------------����� Echo-----------------
	Echo_DDR&=~(1<<EchoNPin);
	Echo_PORT&=~(1<<EchoNPin);
	//-------------------------------------------------

	//================================================== 
}


//������ ������ ������� ������������� �������� 20���
void HC_SRC04_Strop(void)
{
	Trig_PORT|=(1<<Trig_NPin);
	_delay_us(20);
	Trig_PORT&=~(1<<Trig_NPin);
}

//======================������� ������������� ����������===============
/*
	����������:
	unsigned char flag -��� ���������� �� INT0  ��� INT1
*/
void Init_Interruot_HC04(unsigned char flag)
{
	if (flag==FLAG_INT0)
	{
		MCUCR|=(1<<ISC00);
		GICR|=(1<<INT0);
	}
	else if (flag==FLAG_INT1)
	{
		MCUCR|=(1<<ISC10);
		GICR|=(1<<INT1);
	}

}

//������ � ��������� ������� ��������
void timer_Start_Stop(char flag)
{
	
	if (flag)
	{
		TCCR1A|=(0<<WGM11)|(0<<WGM10);
		TCCR1B|=(0<<WGM12)|(0<<WGM13);
		TCNT1=0;
		
		TIMSK|=(1<<TOIE1);
		TCCR1B|=(1<<CS11)|(1<<CS10);
	}
	else
	{
		TCCR1B&=~((1<<CS11)|(1<<CS10));
		TIMSK&=~(1<<TOIE1);
		
	}
	
	//return tact;
}

//����������� ������������ �������� � ����������
/*
����������:
unsigned int N_t-���������� ������������ ��������
*/
unsigned int Convert_CM( int N_t)
{
	 long int C;
	
	C=N_t*8;	//���������� ����� ��������
	C/=58;		//��������� ���������� � �����������
	//C+=1;		//����������� ������ 
	
	return ( int)C;

}

//�������� ��������
unsigned int GetValueHSR04(void)
{

	HC_SRC04_Strop();
	_delay_ms(100);
	return Convert_CM(TCNT1);

}













