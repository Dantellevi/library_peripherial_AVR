#include "ADCMatrix.h"
//=================================================================
//============================<Переменные>=========================
//=================================================================
uint8_t retval=0;		//переменная для считывания значений с АЦП клавиатуры	
uint8_t varpass=' ';	//переменная для считывания значений с АЦП клавиатуры
char bufferpassword[SIZE_PASSWORD];	//буффер для хранения вводимых цифр
char password[]={'1','2','3','4','\0'};	//пороль
unsigned char cnt=0;					//счетчик вводимых цифр
 
 
 
 
 /*
===================Название функции:GetValueKey_Board=============================
=================фунция получение символа с АЦП клавиатуры========================
			принимает unsigned char - канал считывания данных с АЦП
					возращает uint8_t- нажатый символ

 */
 uint8_t GetValueKey_Board(unsigned char channel)
{
	float value;
	
	value=adc_voltage(channel);

	if (value>2.2 && value<2.5)
	{
		retval='1';
		
	}
	else if (value>2 && value<2.2)
	{
		retval='2';
	}
	else if (value>1.5 && value<=1.69)
	{
		retval='3';
	}
	else if (value>1.3 && value<=1.50)
	{
		retval='4';
	}
	else if (value>1.1 && value<=1.15)
	{
		retval='5';
	}
	else if (value>0.9 && value<=0.95)
	{
		retval='6';
	}
	else if (value>0.75 && value<=0.82)
	{
		retval='7';
	}
	else if(value>0.5 && value<=0.57)
	{
		retval='8';

	}
	else if(value>0.3 && value<=0.40)
	{
		retval='9';
	}
	else if (value>0.05 && value<=0.12)
	{
		retval='O';
	}
	else if (value>0.1 && value<=0.17)
	{
		retval='0';
	}
	else if (value>0.15 && value<=0.21)
	{
		retval='C';
	}


	return retval;
}





/*
===================Название функции:password_confird=============================
====================фунция проверки вводимого пороля========================
			принимает unsigned char - канал считывания данных с АЦП
					возращает uint8_t- возращает флаг проверки пороля

 */
uint8_t password_confird(unsigned char channel)
{
	float value;
	
	value=adc_voltage(channel);
	if (value>2.2 && value<2.5)
	{
		varpass='1';
		
	}
	else if (value>2 && value<2.2)
	{
		varpass='2';
	}
	else if (value>1.5 && value<=1.69)
	{
		varpass='3';
	}
	else if (value>1.3 && value<=1.50)
	{
		varpass='4';
	}
	else if (value>1.1 && value<=1.15)
	{
		varpass='5';
	}
	else if (value>0.9 && value<=0.95)
	{
		varpass='6';
	}
	else if (value>0.75 && value<=0.82)
	{
		varpass='7';
	}
	else if(value>0.5 && value<=0.57)
	{
		varpass='8';

	}
	else if(value>0.3 && value<=0.40)
	{
		varpass='9';
	}
	else if (value>0.05 && value<=0.12)
	{
		varpass='O';
	}
	else if (value>0.1 && value<=0.17)
	{
		varpass='0';
	}
	else if (value>0.15 && value<=0.21)
	{
		varpass='C';
	}

	
	if (value>0 && value<=2.5 && varpass!='O' && varpass!='C' )
	{
		bufferpassword[cnt]=varpass;
		LCDdataXY('*',cnt,1);
		cnt++;
		_delay_ms(250);
		
	}
	
	if (cnt==4)
	{
		LCDstringXY(bufferpassword,2,2);
	}
	

	if (varpass=='C')
	{
		bufferpassword[SIZE_PASSWORD]=0;
		cnt=0;
		LCDclear();
	}

	uint8_t flag=0;
	while(varpass=='O')
	{
		if(bufferpassword[0]=='1')	flag++;
		if(bufferpassword[1]=='2')	flag++;
		if(bufferpassword[2]=='3')	flag++;
		if(bufferpassword[3]=='4')	flag++;
			if (flag>=4)
			{
				flag=0;
				return FLAG_OK;
			}
			else
			{
			
				return FLAG_ERROR;

			}
			
		
		
	}
		
	
	
}