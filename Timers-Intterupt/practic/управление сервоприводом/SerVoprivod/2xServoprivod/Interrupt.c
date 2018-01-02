#include "Interrupt.h"
extern volatile unsigned int Danie_1Servo;

//==========================Обработчик прерываний=====================

ISR(INT0_vect)
{
	if (!(PIND&(1<<PD0))&&(Danie_1Servo>74))
	{
	_delay_ms(100);
	if (Danie_1Servo<300)
	{
	Danie_1Servo+=10;
	}
	
	}
	else if ((PIND&(1<<PD0))&&(Danie_1Servo<=300)&&(Danie_1Servo>74))
	{
		_delay_ms(100);
		Danie_1Servo-=10;

	}
	else if (Danie_1Servo>300)
	{
	Danie_1Servo-=10;
	}
	else if (Danie_1Servo<75)
	{
		Danie_1Servo+=10;
	}

}


ISR(INT1_vect)
{


}

//====================================================================


/*
==========================Функция инициализации внешних прерываний=============================

char flagInter-канал прерывания INT0,INT1
char flagcontrol- настройка прерывания , по фронту , уровню или изменению уровня

*/

void Initilizer_Interrupt(char flagInter,char flagcontrol)
{
	if (flagInter==FLAG_INT0)
	{
		switch(flagcontrol)
		{

			case FLAG_FALLING_EDGE:{	//по спадающему фронту

			MCUCR|=(1<<ISC01);
			GICR|=(1<<INT0);
			break;
			}
			case FLAG_LOW_LEVEL:{	//по низкому уровню
			

			MCUCR&=~((1<<ISC01)|(1<<ISC00));
			GICR|=(1<<INT0);

			break;
			}

			case FLAG_ANY_LEVEL:{	//по любому перепаду уровней
			MCUCR|=(1<<ISC00);
			GICR|=(1<<INT0);
			break;
			}

			case FLAG_RISING_EDGE:{	//по возрастающему фронту

			MCUCR|=(1<<ISC01)|(1<<ISC00);
			GICR|=(1<<INT0);
			break;
			}


		}
	}
	else if (flagInter==FLAG_INT1)
	{
		switch(flagcontrol)
		{

			case FLAG_FALLING_EDGE:{	//по спадающему фронту

				MCUCR|=(1<<ISC11);
				GICR|=(1<<INT1);
				break;
			}
			case FLAG_LOW_LEVEL:{		//по низкому уровню
				

				MCUCR&=~((1<<ISC11)|(1<<ISC10));
				GICR|=(1<<INT1);

				break;
			}

			case FLAG_ANY_LEVEL:{		//по любому перепаду уровней
				MCUCR|=(1<<ISC10);
				GICR|=(1<<INT1);
				break;
			}

			case FLAG_RISING_EDGE:{		//по возрастающему фронту

				MCUCR|=(1<<ISC11)|(1<<ISC10);
				GICR|=(1<<INT1);
				break;
			}


		}
	}

}


