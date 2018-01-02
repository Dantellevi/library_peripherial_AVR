#include "MatrixKeyBoard.h"

unsigned char valueKeyboard=' ';

unsigned char cnt=0;
 char passconfim[4];

 //получаем значение с матричной клавиатуры
unsigned char GetMatrixValue(void)
{
		return valueKeyboard;
	
}

//Функция проверки пороля и вывод результата
void Password_Print_Confim(void)
{
	unsigned char flag_compare=0;
	if (GetMatrixValue()!=' ' && GetMatrixValue()!='*'&& GetMatrixValue()!='#')
	{
		passconfim[cnt]=GetMatrixValue();
		LCDdataXY('*',cnt,1);
		cnt++;
		_delay_ms(250);
		valueKeyboard=' ';
	}
	else if (GetMatrixValue()=='*')
	{
		if (cnt==4)
		{
			if (passconfim[0]=='1')	//первая цифра пороля
			{
				flag_compare++;
			}
			if (passconfim[1]=='2')//вторая  цифра пороля
			{
				flag_compare++;
			}
			if (passconfim[2]=='3')//третья цифра пороля
			{
				flag_compare++;
			}
			if (passconfim[3]=='4')//четвертая цифра пороля
			{
				flag_compare++;
			}
			

			if (flag_compare==4)
			{
				LCDstringXY("Password OK   ",1,2);
				
				//--------------------Дополнительный код если пороль верен------------------------------

				//-------------------------------------------------------------------------------------------
				
			}
			else{

				LCDstringXY("Password Error",1,2);
				cnt=0;
				valueKeyboard=' ';
				flag_compare=0;
				for(int i=0;i<4;i++)
				{
					passconfim[i]=0;
				}
				_delay_ms(1000);
				LCDclear();
			}
			
			
		}
		else
		{
			LCDstringXY("Error !!password!!!",1,3);
			//--------------------Дополнительный код если произошла ошибка------------------------------

			//-------------------------------------------------------------------------------------------
		}
	}
	else if (GetMatrixValue()=='#')
	{
		cnt=0;
		valueKeyboard=' ';
		flag_compare=0;
		for(int i=0;i<4;i++)
		{
			passconfim[i]=0;
		}

		LCDclear();
		LCDstringXY("reset !!",1,3);
		_delay_ms(1000);
		LCDclear();
		
	}
	
	


}