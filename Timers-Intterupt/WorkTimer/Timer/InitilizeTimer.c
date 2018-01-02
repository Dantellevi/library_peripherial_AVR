#include "InitilizeTimer.h"
unsigned char valInter=0;
unsigned char valInter2=0;
unsigned int valInter1=0;
char valcomp=0;
unsigned int valcomp1=0;
char valcomp2=0;



 //long int Fcpu=8000000;


 void SelectFreqDel(char flag);
//==========================Прерывания================================

//--------------------------------TIMER0------------------------------------
ISR(TIMER0_OVF_vect)
{

//=========Операции=============
	//PORTD^=(1<<PD0);
	//TCNT0=valInter;

//=============================


}


ISR(TIMER0_COMP_vect)
{

//=========Операции=============

	PORTD^=(1<<PD0);
//=============================

}

//---------------------------------------TIMER2--------------------------------------

ISR(TIMER2_OVF_vect)
{
	//=========Операции=============
	PORTD^=(1<<PD1);
	TCNT2=valInter2;

	//=============================

}

ISR(TIMER2_COMP_vect)
{
	
	PORTD^=(1<<PD1);

}
//------------------------------TIMER1-----------------------------------
ISR(TIMER1_OVF_vect)
{
	PORTD^=(1<<PD2);
	TCNT1=valInter1;

}

ISR(TIMER1_CAPT_vect)
{
	
	PORTD^=(1<<PD2);

}

ISR(TIMER1_COMPA_vect)
{
	PORTD^=(1<<PD2);

}

//====================================================================
/*
NORMAL-Mode:
Тактовая частота : 8000000Гц
отсчитывать 30мс
период одного такта :1/Fcpu/kdel=1024/8000000=0.128мс
количество тактов для времени 30мс: n=30mc/0.128mc=234,375=235
-----------------------------------------------------------------------


CTC-mode:
тактовая частота 8000000
изменение с частотой :40Гц
значение для регистра сравнения:Fcpu/Fzn/Kdel=8000000/40/1024=195,3125=195

==========================================================================

char startVal-начальное значение таймера в режиме Normal
char flagMode-режим работы таймера:Normal,CTC
char freq- значение для сравнения в регистр сравнения в режиме CTC
char flagDel- делитель частоты для работы в обоих режимах
*/

//функция инициализации таймера/счетчика timer0/8-bit
void Timer0_init(char starVal,char flagMode, char freq,char flagDel )
{
	
	valInter=starVal;
	cli();
	if (flagMode==NORMAL_MODE)
	{
		TCCR0|=(0<<WGM00)|(0<<WGM01);
		TIMSK|=(1<<TOIE0);

		
		switch(flagDel)
		{

			case 0:
			{
				TCCR0|=(0<<CS00)|(0<<CS01)|(0<<CS02);
				break;
			}

			case 1:
			{
				TCCR0|=(1<<CS00)|(0<<CS01)|(0<<CS02);
				break;
			}
			case 2:
			{
				TCCR0|=(0<<CS00)|(1<<CS01)|(0<<CS02);
				break;
			}

			case 3:
			{
				TCCR0|=(1<<CS00)|(1<<CS01)|(0<<CS02);
				break;
			}
			case 4:
			{
				TCCR0|=(0<<CS00)|(0<<CS01)|(1<<CS02);
				break;
			}

			case 5:
			{
				TCCR0|=(1<<CS00)|(0<<CS01)|(1<<CS02);
				break;
			}
			case 6:
			{
				TCCR0|=(0<<CS00)|(1<<CS01)|(1<<CS02);
				break;
			}

		}

		TCNT0=starVal;
	}
	else if (flagMode==CTC_MODE)
	{
		TCCR0|=(0<<WGM00)|(1<<WGM01);
		TIMSK|=(0<<TOIE0)|(1<<OCIE0);
		
		
		
		switch(flagDel)
		{

			case 0:
			{
				TCCR0|=(0<<CS00)|(0<<CS01)|(0<<CS02);
				
				break;
			}

			case 1:
			{
				TCCR0|=(1<<CS00)|(0<<CS01)|(0<<CS02);
				
				break;
			}
			case 2:
			{
				TCCR0|=(0<<CS00)|(1<<CS01)|(0<<CS02);
				
				break;
			}

			case 3:
			{
				TCCR0|=(1<<CS00)|(1<<CS01)|(0<<CS02);
				
				break;
			}
			case 4:
			{
				TCCR0|=(0<<CS00)|(0<<CS01)|(1<<CS02);
				
				break;
			}

			case 5:
			{
				TCCR0|=(1<<CS00)|(0<<CS01)|(1<<CS02);
				
				break;
			}
			case 6:
			{
				TCCR0|=(0<<CS00)|(1<<CS01)|(1<<CS02);
				
				break;
			}

		}
		 valcomp=freq;
		 OCR0=valcomp;
	}

	sei();

}




//====================================================================
/*
=====================функция инициализации таймера/счетчика timer2/8-bit=======================
NORMAL-Mode:
Тактовая частота : 8000000Гц
отсчитывать 30мс
период одного такта :1/Fcpu/kdel=1024/8000000=0.128мс
количество тактов для времени 30мс: n=30mc/0.128mc=234,375=235
-----------------------------------------------------------------------


CTC-mode:
тактовая частота 8000000
изменение с частотой :40Гц
значение для регистра сравнения:Fcpu/Fzn/Kdel=8000000/40/1024=195,3125=195

==========================================================================

char startVal-начальное значение таймера в режиме Normal
char flagMode-режим работы таймера:Normal,CTC
char freq- значение для сравнения в регистр сравнения в режиме CTC
char flagDel- делитель частоты для работы в обоих режимах
*/

void Timer2_init_normalMode(int starVal,char flagMode,char freq,char flagDel)
{
	valInter2=starVal;
	cli();
	if (flagMode==NORMAL_MODE)
	{
		TCCR2|=(0<<WGM20)|(0<<WGM21);
		TIMSK|=(1<<TOIE2);

		switch(flagDel)
		{

			case 0:
			{
				TCCR2|=(0<<CS20)|(0<<CS21)|(0<<CS22);
				break;
			}

			case 1:
			{
				TCCR2|=(1<<CS20)|(0<<CS21)|(0<<CS22);
				break;
			}
			case 2:
			{
				TCCR2|=(0<<CS20)|(1<<CS21)|(0<<CS22);
				break;
			}

			case 3://64
			{
				TCCR2|=(0<<CS20)|(0<<CS21)|(1<<CS22);
				break;
			}
			case 4://256
			{
				TCCR2|=(0<<CS00)|(1<<CS21)|(1<<CS22);
				break;
			}

			case 5://1024
			{
				TCCR2|=(1<<CS20)|(1<<CS21)|(1<<CS22);
				break;
			}
			
			case 7://128
			{
				TCCR2|=(1<<CS20)|(0<<CS01)|(1<<CS22);
				break;
			}

			case 8://32
			{
				TCCR2|=(1<<CS21)|(1<<CS21)|(0<<CS22);
				break;
			}


		}

		TCNT2=starVal;
	}
	else if (flagMode==CTC_MODE)
	{
		TCCR2|=(0<<WGM20)|(1<<WGM21);
		TIMSK|=(0<<TOIE2)|(1<<OCIE2);
		
		
		
		switch(flagDel)
		{

			case 0:
			{
				TCCR2|=(0<<CS20)|(0<<CS21)|(0<<CS22);
				break;
			}

			case 1:
			{
				TCCR2|=(1<<CS20)|(0<<CS21)|(0<<CS22);
				break;
			}
			case 2:
			{
				TCCR2|=(0<<CS20)|(1<<CS21)|(0<<CS22);
				break;
			}

			case 3://64
			{
				TCCR2|=(0<<CS20)|(0<<CS21)|(1<<CS22);
				break;
			}
			case 4://256
			{
				TCCR2|=(0<<CS00)|(1<<CS21)|(1<<CS22);
				break;
			}

			case 5://1024
			{
				TCCR2|=(1<<CS20)|(1<<CS21)|(1<<CS22);
				break;
			}
			
			case 7://128
			{
				TCCR2|=(1<<CS20)|(0<<CS01)|(1<<CS22);
				break;
			}

			case 8://32
			{
				TCCR2|=(1<<CS21)|(1<<CS21)|(0<<CS22);
				break;
			}

		}
		valcomp2=freq;
		OCR2=valcomp2;
	}

	sei();

}

/*
===========================функция инициализации таймера/счетчика timer1/16-bit===========================
NORMAL-Mode:
Тактовая частота : 8000000Гц
отсчитывать 1с
период одного такта :1/Fcpu/kdel=1024/8000000=0.128мс
количество тактов для времени 1с: n=1/0.128mc=7812.5=7813
65535-7813=57722
-----------------------------------------------------------------------


CTC-mode:
тактовая частота 8000000
изменение с частотой :1Гц
значение для регистра сравнения:Fcpu/Fzn/Kdel=8000000/1/1024=7812
==========================================================================

char startVal-начальное значение таймера в режиме Normal
char flagMode-режим работы таймера:Normal,CTC
char freq- значение для сравнения в регистр сравнения в режиме CTC
char flagDel- делитель частоты для работы в обоих режимах
char flagCTC-флаг выбора режима сравнения:OCR1A,ICR1
*/
//
void Timer_init_16bit(unsigned int starVal,char flagMode,char flagCTC, unsigned int freq,char flagDel)
{
	valInter1=starVal;
	cli();
	if (flagMode==NORMAL_MODE)
	{

		


		TCCR1A|=(0<<WGM11)|(0<<WGM10);
		TCCR1B|=(0<<WGM12)|(0<<WGM13);
		TIMSK|=(1<<TOIE1);

		switch(flagDel)
		{

			case 0:
			{
				TCCR1B|=(0<<CS10)|(0<<CS11)|(0<<CS12);
				break;
			}

			case 1://1
			{
				TCCR1B|=(1<<CS10)|(0<<CS11)|(0<<CS12);
				break;
			}
			case 2://8
			{
				TCCR1B|=(0<<CS10)|(1<<CS11)|(0<<CS12);
				break;
			}

			case 3://64
			{
				TCCR1B|=(1<<CS10)|(1<<CS11)|(0<<CS12);
				break;
			}
			case 4://256
			{
				TCCR1B|=(0<<CS10)|(0<<CS11)|(1<<CS12);
				break;
			}

			case 5://1024
			{
				TCCR1B|=(1<<CS10)|(0<<CS11)|(1<<CS12);
				break;
			}
			
			


		}

		TCNT1=starVal;
	}
	else if (flagMode==CTC_MODE)
	{

		if (flagCTC==CTC_OCR1A)
		{
			TCCR1A|=(0<<WGM11)|(0<<WGM10);
			TCCR1B|=(1<<WGM12)|(0<<WGM13);
			TIMSK|=(0<<TOIE1)|(1<<OCIE1A);
			switch(flagDel)
			{

				case 0:
				{
					TCCR1B|=(0<<CS10)|(0<<CS11)|(0<<CS12);
					break;
				}

				case 1://1
				{
					TCCR1B|=(1<<CS10)|(0<<CS11)|(0<<CS12);
					break;
				}
				case 2://8
				{
					TCCR1B|=(0<<CS10)|(1<<CS11)|(0<<CS12);
					break;
				}

				case 3://64
				{
					TCCR1B|=(1<<CS10)|(1<<CS11)|(0<<CS12);
					break;
				}
				case 4://256
				{
					TCCR1B|=(0<<CS10)|(0<<CS11)|(1<<CS12);
					break;
				}

				case 5://1024
				{
					TCCR1B|=(1<<CS10)|(0<<CS11)|(1<<CS12);
					break;
				}
				
				


			}
			valcomp1=freq;
			OCR1AH=(freq>>8);
			OCR1AL=freq;


		}
		else if (flagCTC==CTC_ICR1A)
		{
			TCCR1A|=(0<<WGM11)|(0<<WGM10);
			TCCR1B|=(1<<WGM12)|(1<<WGM13);
			TIMSK|=(1<<TICIE1)|(0<<OCIE1A);
			switch(flagDel)
			{

				case 0:
				{
					TCCR1B|=(0<<CS10)|(0<<CS11)|(0<<CS12);
					break;
				}

				case 1://1
				{
					TCCR1B|=(1<<CS10)|(0<<CS11)|(0<<CS12);
					break;
				}
				case 2://8
				{
					TCCR1B|=(0<<CS10)|(1<<CS11)|(0<<CS12);
					break;
				}

				case 3://64
				{
					TCCR1B|=(1<<CS10)|(1<<CS11)|(0<<CS12);
					break;
				}
				case 4://256
				{
					TCCR1B|=(0<<CS10)|(0<<CS11)|(1<<CS12);
					break;
				}

				case 5://1024
				{
					TCCR1B|=(1<<CS10)|(0<<CS11)|(1<<CS12);
					break;
				}
				
				


			}
			valcomp1=freq;
			ICR1H=(freq>>8);
			ICR1L=freq;

		}
	
	}

	sei();

}


/*

===============================функция инициализации ШИМ timer0/8-bit======================================
	Подсчет частоты ШИМ:

	Fcpu/del=Fpwm

	Пример:
	8000000/1024=7812.5=7813Гц=7.8125 кГц
	==========================================================
	char starval-начальное значение ШИМ
	Mode- режим работы ШИМ:First,PhaseCorrect
	char flagdel-делитель частоты для работы
*/
//
void PWM0_init(char starVal,char Mode,char flagdel)
{
	if (Mode==PWM_MODE_FIRST)
	{
		TCCR0|=(1<<WGM01)|(1<<WGM00);
		TCCR0|=(1<<COM01);
		switch(flagdel)
		{

			case 0:
			{
				TCCR0|=(0<<CS00)|(0<<CS01)|(0<<CS02);
				break;
			}

			case 1:
			{
				TCCR0|=(1<<CS00)|(0<<CS01)|(0<<CS02);
				break;
			}
			case 2:
			{
				TCCR0|=(0<<CS00)|(1<<CS01)|(0<<CS02);
				break;
			}

			case 3:
			{
				TCCR0|=(1<<CS00)|(1<<CS01)|(0<<CS02);
				break;
			}
			case 4:
			{
				TCCR0|=(0<<CS00)|(0<<CS01)|(1<<CS02);
				break;
			}

			case 5:
			{
				TCCR0|=(1<<CS00)|(0<<CS01)|(1<<CS02);
				break;
			}
			case 6:
			{
				TCCR0|=(0<<CS00)|(1<<CS01)|(1<<CS02);
				break;
			}

		}

		OCR0=starVal;

	}
	else if (Mode==PWM_MODE_PHASECORRECT)
	{
		TCCR0|=(0<<WGM01)|(1<<WGM00);
		TCCR0|=(1<<COM01);
		switch(flagdel)
		{

			case 0:
			{
				TCCR0|=(0<<CS00)|(0<<CS01)|(0<<CS02);
				break;
			}

			case 1:
			{
				TCCR0|=(1<<CS00)|(0<<CS01)|(0<<CS02);
				break;
			}
			case 2:
			{
				TCCR0|=(0<<CS00)|(1<<CS01)|(0<<CS02);
				break;
			}

			case 3:
			{
				TCCR0|=(1<<CS00)|(1<<CS01)|(0<<CS02);
				break;
			}
			case 4:
			{
				TCCR0|=(0<<CS00)|(0<<CS01)|(1<<CS02);
				break;
			}

			case 5:
			{
				TCCR0|=(1<<CS00)|(0<<CS01)|(1<<CS02);
				break;
			}
			case 6:
			{
				TCCR0|=(0<<CS00)|(1<<CS01)|(1<<CS02);
				break;
			}

		}

		OCR0=starVal;
	}


	

}

//Функция установки значения ШИМ для 0 таймера
void SetPWM0_Value(char value)
{
	
	OCR0=value;

}

//==================================функция инициализации ШИМ timer2/8-bit=============================
/*
Подсчет частоты ШИМ:

Fcpu/del=Fpwm

Пример:
8000000/1024=7812.5=7813Гц=7.8125 кГц
==========================================================
char starval-начальное значение ШИМ
Mode- режим работы ШИМ:First,PhaseCorrect
char flagdel-делитель частоты для работы
*/
void PWM2_init(char starVal,char Mode,char flagdel)
{

	if (Mode==PWM_MODE_FIRST)
	{
		TCCR2|=(1<<WGM21)|(1<<WGM20);
		TCCR2|=(1<<COM21);

		switch(flagdel)
		{

			case 0:
			{
				TCCR2|=(0<<CS20)|(0<<CS21)|(0<<CS22);
				break;
			}

			case 1:
			{
				TCCR2|=(1<<CS20)|(0<<CS21)|(0<<CS22);
				break;
			}
			case 2:
			{
				TCCR2|=(0<<CS20)|(1<<CS21)|(0<<CS22);
				break;
			}

			case 3://64
			{
				TCCR2|=(0<<CS20)|(0<<CS21)|(1<<CS22);
				break;
			}
			case 4://256
			{
				TCCR2|=(0<<CS00)|(1<<CS21)|(1<<CS22);
				break;
			}

			case 5://1024
			{
				TCCR2|=(1<<CS20)|(1<<CS21)|(1<<CS22);
				break;
			}
			
			case 7://128
			{
				TCCR2|=(1<<CS20)|(0<<CS01)|(1<<CS22);
				break;
			}

			case 8://32
			{
				TCCR2|=(1<<CS21)|(1<<CS21)|(0<<CS22);
				break;
			}


		}

		OCR2=starVal;


	}
	else if (Mode==PWM_MODE_PHASECORRECT)
	{
		TCCR2|=(1<<WGM21)|(0<<WGM20);
		TCCR2|=(1<<COM21);

		switch(flagdel)
		{

			case 0:
			{
				TCCR2|=(0<<CS20)|(0<<CS21)|(0<<CS22);
				break;
			}

			case 1:
			{
				TCCR2|=(1<<CS20)|(0<<CS21)|(0<<CS22);
				break;
			}
			case 2:
			{
				TCCR2|=(0<<CS20)|(1<<CS21)|(0<<CS22);
				break;
			}

			case 3://64
			{
				TCCR2|=(0<<CS20)|(0<<CS21)|(1<<CS22);
				break;
			}
			case 4://256
			{
				TCCR2|=(0<<CS00)|(1<<CS21)|(1<<CS22);
				break;
			}

			case 5://1024
			{
				TCCR2|=(1<<CS20)|(1<<CS21)|(1<<CS22);
				break;
			}
			
			case 7://128
			{
				TCCR2|=(1<<CS20)|(0<<CS01)|(1<<CS22);
				break;
			}

			case 8://32
			{
				TCCR2|=(1<<CS21)|(1<<CS21)|(0<<CS22);
				break;
			}


		}

		OCR2=starVal;
	}

}
void SetPWM2_Value(char value)
{

	OCR2=value;

}


//функция инициализации ШИМ timer1
/*
Подсчет частоты ШИМ:

Fcpu/del=Fpwm

Пример:
8000000/1024=7812.5=7813Гц=7.8125 кГц
==========================================================
char starval-начальное значение ШИМ
Mode- режим работы ШИМ:First,PhaseCorrect
char flagdel-делитель частоты для работы
char channel-канал работы ШИМ :OCR1A,OCR1B
char flagBits-разрядность ШИМ:8,9,10 бит
*/
void PWM1_init(int starVal,char flagBits,char Mode,char flagdel,char channel)
{
	if(Mode==PWM_MODE_FIRST)
	{
		switch(flagBits)
		{

			case 8:{
				TCCR1A|=(1<<WGM10)|(0<<WGM11);
				TCCR1B|=(1<<WGM12)|(0<<WGM13);
				SelectFreqDel(flagdel);

				if (channel==FLAG_CH_OCR1A)
				{
					TCCR1A|=(1<<COM1A1);
					OCR1AH=(char)(starVal>>8);
					OCR1AL=(char)starVal;
				}
				else if (channel==FLAG_CH_OCR1B)
				{
					TCCR1A|=(1<<COM1B1);
					OCR1BH=(char)(starVal>>8);
					OCR1BL=(char)starVal;
				}
				
				break;
			}
			case 9:{
				TCCR1A|=(0<<WGM10)|(1<<WGM11);
				TCCR1B|=(1<<WGM12)|(0<<WGM13);
				SelectFreqDel(flagdel);

				if (channel==FLAG_CH_OCR1A)
				{
					TCCR1A|=(1<<COM1A1);
					OCR1AH=(char)(starVal>>8);
					OCR1AL=(char)starVal;
				}
				else if (channel==FLAG_CH_OCR1B)
				{
					TCCR1A|=(1<<COM1B1);
					OCR1BH=(char)(starVal>>8);
					OCR1BL=(char)starVal;
				}
				break;
			}

			case 10:{
				TCCR1A|=(1<<WGM10)|(1<<WGM11);
				TCCR1B|=(1<<WGM12)|(0<<WGM13);
				SelectFreqDel(flagdel);

				if (channel==FLAG_CH_OCR1A)
				{
					TCCR1A|=(1<<COM1A1);
					OCR1AH=(char)(starVal>>8);
					OCR1AL=(char)starVal;
				}
				else if (channel==FLAG_CH_OCR1B)
				{
					TCCR1A|=(1<<COM1B1);
					OCR1BH=(char)(starVal>>8);
					OCR1BL=(char)starVal;
				}
				break;
			}

		}
		


	}

	//====================
	else if (Mode==PWM_MODE_PHASECORRECT)
	{
		switch(flagBits)
		{

			case 8:{
				TCCR1A|=(1<<WGM10)|(0<<WGM11);
				TCCR1B|=(0<<WGM12)|(0<<WGM13);
				SelectFreqDel(flagdel);

				if (channel==FLAG_CH_OCR1A)
				{
					TCCR1A|=(1<<COM1A1);
					OCR1AH=(char)(starVal>>8);
					OCR1AL=(char)starVal;
				}
				else if (channel==FLAG_CH_OCR1B)
				{
					TCCR1A|=(1<<COM1B1);
					OCR1BH=(char)(starVal>>8);
					OCR1BL=(char)starVal;
				}
				break;
			}
			case 9:{
				TCCR1A|=(0<<WGM10)|(1<<WGM11);
				TCCR1B|=(0<<WGM12)|(0<<WGM13);
				SelectFreqDel(flagdel);

				if (channel==FLAG_CH_OCR1A)
				{
					TCCR1A|=(1<<COM1A1);
					OCR1AH=(char)(starVal>>8);
					OCR1AL=(char)starVal;
				}
				else if (channel==FLAG_CH_OCR1B)
				{
					TCCR1A|=(1<<COM1B1);
					OCR1BH=(char)(starVal>>8);
					OCR1BL=(char)starVal;
				}
				break;
			}

			case 10:{
				TCCR1A|=(1<<WGM10)|(1<<WGM11);
				TCCR1B|=(0<<WGM12)|(0<<WGM13);
				SelectFreqDel(flagdel);

				if (channel==FLAG_CH_OCR1A)
				{
					TCCR1A|=(1<<COM1A1);
					OCR1AH=(char)(starVal>>8);
					OCR1AL=(char)starVal;
				}
				else if (channel==FLAG_CH_OCR1B)
				{
					TCCR1A|=(1<<COM1B1);
					OCR1BH=(char)(starVal>>8);
					OCR1BL=(char)starVal;
				}
				break;
			}

		}
	}

}


//===========================функция выбора частоты для ШИМ===================================================
void SelectFreqDel(char flag)
{
	switch(flag)
	{

		case 0:
		{
			TCCR1B|=(0<<CS10)|(0<<CS11)|(0<<CS12);
			break;
		}

		case 1://1
		{
			TCCR1B|=(1<<CS10)|(0<<CS11)|(0<<CS12);
			break;
		}
		case 2://8
		{
			TCCR1B|=(0<<CS10)|(1<<CS11)|(0<<CS12);
			break;
		}

		case 3://64
		{
			TCCR1B|=(1<<CS10)|(1<<CS11)|(0<<CS12);
			break;
		}
		case 4://256
		{
			TCCR1B|=(0<<CS10)|(0<<CS11)|(1<<CS12);
			break;
		}

		case 5://1024
		{
			TCCR1B|=(1<<CS10)|(0<<CS11)|(1<<CS12);
			break;
		}
		
		


	}


}

//======================================функция установки значения в ШИМ таймера 1=========================================
void SetPWM1_Value(int val,char channel,char flgbits)
{

	if (flgbits==FLAG_8BIT)
	{
		if (channel==FLAG_CH_OCR1A)
		{
			OCR1AH=(char)(val>>8);
			OCR1AL=(char)val;
		}
		else if (channel==FLAG_CH_OCR1B)
		{
			OCR1BH=(char)(val>>8);
			OCR1BL=(char)val;
		}
		else if (channel==FLAG_CH_ICR1)
		{
			ICR1H=(char)(val>>8);
			ICR1L=(char)val;
		}
		
	}
	else if (flgbits==FLAG_9BIT)
	{
		if (channel==FLAG_CH_OCR1A)
		{
			OCR1AH=(char)(val>>8);
			OCR1AL=(char)val;
		}
		else if (channel==FLAG_CH_OCR1B)
		{
			OCR1BH=(char)(val>>8);
			OCR1BL=(char)val;
		}
		else if (channel==FLAG_CH_ICR1)
		{
			ICR1H=(char)(val>>8);
			ICR1L=(char)val;
		}
	}
	else if(flgbits==FLAG_10BIT)
	{

	if (channel==FLAG_CH_OCR1A)
	{
		OCR1AH=(char)(val>>8);
		OCR1AL=(char)val;
	}
	else if (channel==FLAG_CH_OCR1B)
	{
		OCR1BH=(char)(val>>8);
		OCR1BL=(char)val;
	}
	else if (channel==FLAG_CH_ICR1)
	{
		ICR1H=(char)(val>>8);
		ICR1L=(char)val;
	}
	}
}

void Timer_close(char flagTimers)
{


}





