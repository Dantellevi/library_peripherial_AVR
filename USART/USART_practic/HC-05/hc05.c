#include "hc05.h"

unsigned char flag_work=0;		//флаг проверки роботоспособности

char ckeckState(void)
{
//Посылаем команду AT и если возращается OK то то возращаем ОК для передачи
	unsigned char i=0;
	char buf[10];
	char count_byte=0;
	char str[]=AT_com;
	while (str[i])
	{
		Usart_char_out(str[i]);
		i++;
	}
	_delay_ms(10);
	//Получаем ответ от HC-05
	count_byte=Usart_str_in(buf,4);
	int compVal=strcmp(buf,"OK\r\n");
	if (compVal==0)
	{
		flag_work=1;
		return OK;
	}
	else
	{
	flag_work=0;
	return ERROR;
	}


}

//=====================Функция сброса модуля=======================

void ResetHC05(void)
{
if (flag_work==OK)
{
	unsigned char i=0;
	char str[]=AT_RES;
	while (str[i])
	{
		Usart_char_out(str[i]);
		i++;
	}
	_delay_ms(10);
}
else
{
	return;
}

}


void SetOrigin(void)
{
if (flag_work==OK)
{
	unsigned char i=0;
	char str[]=AT_Origin;
	while (str[i])
	{
		Usart_char_out(str[i]);
		i++;
	}
	_delay_ms(10);
}
else
{
	return;
}

}

//===============Получение версии прошивки============
//str-буффер куда будет сохраняться ответ
//count-размер ответа
//возращает количество байт в ответе


char Version_Get(char *str)
{
if (flag_work==OK)
{
	unsigned char i=0;
	char buf[]=AT_Version;
	while (buf[i])
	{
		Usart_char_out(buf[i]);
		i++;
	}
	_delay_ms(10);
//-----------------Получаем ответ--------------------------
	char out = 0;
	char data = 0;
	char timeout = 0;
	
	while(27 > data)
	{
		data = GetData();
		
		// Если в течении пол секунды данные не пришли
		// то выйти из функции и вернуть 0
		if(timeout >= 500)
		{
			ClearBuffer();
			return out;
		}
		
		timeout++;
		_delay_ms(1);
	}
	
	out = OutBufferStr(str, 27);
	return out;
	}
	else return 0;
}



//=====================Получить роль модуля===============================
//str-буффер для хранения роли
//count-размер роли
//возращает : количество байт в ответе

char ROLE_Get(char *str)
{
if (flag_work==OK)
{
	unsigned char i=0;
	char buf[]=AT_ROLE_Get;
	while (buf[i])
	{
		Usart_char_out(buf[i]);
		i++;
	}
	_delay_ms(10);
	//-----------------Получаем ответ--------------------------
	char out = 0;
	char data = 0;
	char timeout = 0;
	
	while(9 > data)
	{
		data = GetData();
		
		// Если в течении пол секунды данные не пришли
		// то выйти из функции и вернуть 0
		if(timeout >= 500)
		{
			ClearBuffer();
			return out;
		}
		
		timeout++;
		_delay_ms(1);
	}
	
	out = OutBufferStr(str, 12);
	return out;
	}
	else return 0;
}



//=====================Функция установки роли(мастер, слайв,ведомый в цикле*)========================
//========str-массив для имени--------------
//strResponse----массив для получения ответа
char Role_Set(char *str,char *strResponse)
{
	if (flag_work==OK)
	{
		strcat(str,"\r\n");
		char buf[100]={0};
		strcpy(buf,AT_ROLE_Set); 
		
		strcat(buf,str);
		Usart_str_rn(buf);
		//=====================Получаем ответ====================
		_delay_ms(10);
		//Получаем ответ от HC-05
		int count_byte=Usart_str_in(strResponse,4);
		int compVal=strcmp(strResponse,"OK\r\n");
		if (compVal==0)
		{
			
			return OK;
		}
		else
		{
			
			return ERROR;
		}

	}
	else
	{
		return ERROR;
	}

}


//=======================Функция получения имени модуля====================
/*
		Переменные:
		str-хранит полученное имени

*/
char Name_Get(char *str)
{
	if (flag_work==OK)
	{
		unsigned char i=0;
		char buf[]=AT_Name_Get;
		while (buf[i])
		{
			Usart_char_out(buf[i]);
			i++;
		}
		_delay_ms(10);
		//-----------------Получаем ответ--------------------------
		char out = 0;
		char data = 0;
		char timeout = 0;
		
		while(3 > data)
		{
			data = GetData();
			
			// Если в течении пол секунды данные не пришли
			// то выйти из функции и вернуть 0
			if(timeout >= 500)
			{
				ClearBuffer();
				return out;
			}
			
			timeout++;
			_delay_ms(1);
		}
		
		out = OutBufferStr(str,20);
		return out;
	}
	else return 0;
}

//==========================Функция установки имени===============
void Name_Set(char *str)
{
	if (flag_work==OK)
	{

		char buf[100]={0};
		strcpy(buf,AT_Name_Set); 
		
		strcat(buf,str);
		Usart_str_rn(buf);

	}
	else
	{
		return;
	}

}



void Password_Set(char *str)
{
	if (flag_work==OK)
	{
		strcat(str,"\r\n");
		char buf[100]={0};
		strcpy(buf,AT_PSWD_set); 
		
		strcat(buf,str);
		Usart_str_rn(buf);

	}
	else
	{
		return;
	}

}


char Password_Get(char *str,int count)
{
	if (flag_work==OK)
	{
		unsigned char i=0;
		char buf[]=AT_PSWD_Get;
		while (buf[i])
		{
			Usart_char_out(buf[i]);
			i++;
		}
		_delay_ms(10);
		//-----------------Получаем ответ--------------------------
		char out = 0;
		char data = 0;
		char timeout = 0;
		
		while(count > data)
		{
			data = GetData();
			
			// Если в течении пол секунды данные не пришли
			// то выйти из функции и вернуть 0
			if(timeout >= 500)
			{
				ClearBuffer();
				return out;
			}
			
			timeout++;
			_delay_ms(1);
		}
		
		out = OutBufferStr(str, count);
		return out;
	}
	else return 0;
}



