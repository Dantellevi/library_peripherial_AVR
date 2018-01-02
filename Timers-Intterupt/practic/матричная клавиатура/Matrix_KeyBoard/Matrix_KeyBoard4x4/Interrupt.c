#include "Interrupt.h"

char valInterupt=0;

//==========================���������� ����������=====================
ISR(INT0_vect)
{
	
	if (((PIND&(1<<PD0)))&&(valInterupt<255))
	{
		PORTD^=(1<<PD1);
		valInterupt++;
		
		SetPWM0_Value(valInterupt);
	}
	else if (!(PIND&(1<<PD0))&&(valInterupt>0))
	{
		valInterupt--;
		SetPWM0_Value(valInterupt);
	}

}


ISR(INT1_vect)
{


}

//====================================================================


/*
==========================������� ������������� ������� ����������=============================

char flagInter-����� ���������� INT0,INT1
char flagcontrol- ��������� ���������� , �� ������ , ������ ��� ��������� ������

*/

void Initilizer_Interrupt(char flagInter,char flagcontrol)
{
	if (flagInter==FLAG_INT0)
	{
		switch(flagcontrol)
		{

			case FLAG_FALLING_EDGE:{	//�� ���������� ������

			MCUCR|=(1<<ISC01);
			GICR|=(1<<INT0);
			break;
			}
			case FLAG_LOW_LEVEL:{	//�� ������� ������
			

			MCUCR&=~((1<<ISC01)|(1<<ISC00));
			GICR|=(1<<INT0);

			break;
			}

			case FLAG_ANY_LEVEL:{	//�� ������ �������� �������
			MCUCR|=(1<<ISC00);
			GICR|=(1<<INT0);
			break;
			}

			case FLAG_RISING_EDGE:{	//�� ������������� ������

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

			case FLAG_FALLING_EDGE:{	//�� ���������� ������

				MCUCR|=(1<<ISC11);
				GICR|=(1<<INT1);
				break;
			}
			case FLAG_LOW_LEVEL:{		//�� ������� ������
				

				MCUCR&=~((1<<ISC11)|(1<<ISC10));
				GICR|=(1<<INT1);

				break;
			}

			case FLAG_ANY_LEVEL:{		//�� ������ �������� �������
				MCUCR|=(1<<ISC10);
				GICR|=(1<<INT1);
				break;
			}

			case FLAG_RISING_EDGE:{		//�� ������������� ������

				MCUCR|=(1<<ISC11)|(1<<ISC10);
				GICR|=(1<<INT1);
				break;
			}


		}
	}

}


