#include "SIM300.h"

#define ENTER 0x0D
#define CTRL_Z 0x1A

char sim300_buffer[128];		//буффер для считывания ответов от SIM300

int8_t SIM300Init(void)
{
	//Инициализация USART-интерфейса
	Usart_Init(Usart_baud);
	
	//Проверка линии связи с SIM300
	SIM300Cmd("AT");	//Тестовый запрос на SIM300
	
	//переменная таймер для ожидания ответа
	uint16_t i=0;
	
	//длинна ответа состовляет 6 байт
	//Ожидаем 6 байт
	//переносим их в буффер
	while(i<10)
	{
		if(UDataAvailable()<6)
		{
			i++;
			
			_delay_ms(10);
			
			continue;
		}
		else
		{
			//получаем ответ из 6 байт
			//проверка
			UReadBuffer(sim300_buffer,6);	//чтение данных из буффера
			
			return SIM300CheckResponse(sim300_buffer,"OK",6);
			
		}
	}
	
	//Ожидание без ответа
	//возращает время ожидание вышло
	
	return SIM300_TIMEOUT;
	
}


//=====================Функция отправки команды на модуль======================
/*
		Возращаемые значения  :
		int8_t- возращает флаг успешной передачи и приема команды либо ошибки передачи и приема
		Так же в буффер sim300_buffer  -записывается ответ от модуля при успешной передачи
*/

int8_t SIM300Cmd(char *cmd)
{
	USART_WriteString(cmd);	//Посылаем команду
	Usart_Transmit_SendChar(0x0D);	//Символ перевода строки
	
	uint8_t len=strlen(cmd);
	
	len++;	//Добавляем  1 для трейдинга CR, добавленного ко всем командам
	
	uint16_t i=0;
	
	//ожидаем ответа
	while(i<10*len)
	{
		if(UDataAvailable()<len)
		{
			i++;
			
			_delay_ms(10);
			
			continue;
		}
		else
		{
			//Получаем ответ
			//Проверка 
			UReadBuffer(sim300_buffer,len);	//Читаем данные из буффера
			
			return SIM300_OK;
			
		}
	}
	
	return SIM300_TIMEOUT;
	
}


/*
		=============Метод проверки модуля (ожидания ответа)=====================

*/
int8_t SIM300CheckResponse(const char *response,const char *check,uint8_t len)
{
	len-=2;
	
	//Проверка на начальне значения CR LF(если значение не равны 0x0D и 0x0A то значит мы получили ответ)
	if((response[0]!=0x0D)|(response[1]!=0x0A))
	return	SIM300_INVALID_RESPONSE;
	
	//проверка конца буффера CR LF(если значение не равны 0x0D и 0x0A то значит мы получили ответ)
	if((response[len]!=0x0D)|(response[len+1]!=0x0A))
	return	SIM300_INVALID_RESPONSE;
	
	
	//Сравниваем ответы
	for(uint8_t i=2;i<len;i++)
	{
		if(response[i]!=check[i-2])
		return SIM300_FAIL;
	}
	
	return SIM300_OK;
}

//=============Функция задания времении ожидания ответа от модуля================

int8_t SIM300WaitForResponse(uint16_t timeout)
{
	uint8_t i=0;
	uint16_t n=0;
	
	while(1)
	{
		while (UDataAvailable()==0 && n<timeout){n++; _delay_ms(1);}
		
		if(n==timeout)
		return 0;
		else
		{
			sim300_buffer[i]=USART_ReadData();
			
			if(sim300_buffer[i]==0x0D && i!=0)
			{
				UFlushBuffer();
				return i+1;
			}
			else
			i++;
		}
	}
}


//========================получить тип регистрации в сети=======================

int8_t SIM300GetNetStat(void)
{
	//Посылаем команду
	SIM300Cmd("AT+CREG?");//получить тип регистрации в сети
	
	//ожидаем ответа(переменная для таймера)
	uint16_t i=0;
	
	//получаем 20 байт данных
	//ожидаем получение 20 байт данных
	//в буффер
	while(i<10)
	{
		if(UDataAvailable()<20)
		{
			i++;
			
			_delay_ms(10);
			
			continue;
		}
		else
		{
			//Получили ответ из 20 байт данных
			//Проверяем буффер
			UReadBuffer(sim300_buffer,20);	//читаем данные из буффера
			
			if(sim300_buffer[11]=='1')
			return SIM300_NW_REGISTERED_HOME;
			else if(sim300_buffer[11]=='2')
			return SIM300_NW_SEARCHING;
			else if(sim300_buffer[11]=='5')
			return SIM300_NW_REGISTED_ROAMING;
			else
			return SIM300_NW_ERROR;
		}
	}
	
	//Если ответа нет
	//отправляет уведомление о истечении времени ожидания
	
	return SIM300_TIMEOUT;
	
}


//=======================Проверить инициализацию карточки можно командой=========

int8_t SIM300IsSIMInserted()
{
	UFlushBuffer();
	
	//Посылаем команду на модуль
	SIM300Cmd("AT+CSMINS?");
	
	//Ожидаем ответа
	uint16_t i=0;
	
	//Ответ должен состоять из 22 байт
	//Получаем ответ и помещаем его в буффер
	
	while(i<30)
	{
		if(UDataAvailable()<22)
		{
			i++;
			
			_delay_ms(10);
			
			continue;
		}
		else
		{
			//запись в буффер и проверка
			
			UReadBuffer(sim300_buffer,22);	//Запись в буффер
			
			if(sim300_buffer[13]=='1')
			return SIM300_SIM_PRESENT;		//SIM-карта присутствует
			else
			return SIM300_SIM_NOT_PRESENT;	//нет SIM-карты
		}
	}
	
	//Ошибка тайминга
	
	return SIM300_TIMEOUT;
}


/*
--------------------Функция проверки имени провайдера------------------------
*/
uint8_t SIM300GetProviderName(char *name)
{
	UFlushBuffer();
	
	//Отправляем команду на запрос провайдера
	SIM300Cmd("AT+CSPN?");
	
	uint8_t len=SIM300WaitForResponse(1000);		//устанавливаем время ожидания
	
	if(len==0)
	return SIM300_TIMEOUT;
	
	char *start,*end;
	start=strchr(sim300_buffer,'"');
	start++;
	end=strchr(start,'"');
	
	*end='\0';
	
	strcpy(name,start);
	
	return strlen(name);
}

/*
-------------------вернет IMEI модуля--------------------------
*/

int8_t SIM300GetIMEI(char *emei)
{
	UFlushBuffer();
	
	//Send Command
	SIM300Cmd("AT+GSN");
	
	uint8_t len=SIM300WaitForResponse(1000);
	
	if(len==0)
	return SIM300_TIMEOUT;
	
	sim300_buffer[len-1]='\0';
	
	strcpy(emei,sim300_buffer+2);
	
	return SIM300_OK;
}


/*
---------------------Получаем индификатор производителя-------------------------
*/
int8_t SIM300GetManufacturer(char *man_id)
{
	UFlushBuffer();
	
	//Команда на получение имени производителя
	SIM300Cmd("AT+GMI");
	
	uint8_t len=SIM300WaitForResponse(1000);
	
	if(len==0)
	return SIM300_TIMEOUT;
	
	sim300_buffer[len-1]='\0';
	
	strcpy(man_id,sim300_buffer+2);//исключаем \r\n
	
	return SIM300_OK;
}


/*
--------------------Функция запроса индификатора модуля------------------------
*/
int8_t	SIM300GetModel(char *model)
{
	UFlushBuffer();
	
	//идентификатор модуля
	SIM300Cmd("AT+GMM");
	
	uint8_t len=SIM300WaitForResponse(1000);
	
	if(len==0)
	return SIM300_TIMEOUT;
	
	sim300_buffer[len-1]='\0';
	
	strcpy(model,sim300_buffer+2);//исключаем \r\n
	
	return SIM300_OK;
}

void Clear_Usart_Buffer(void)
{
	
	memset(sim300_buffer,0,sizeof(sim300_buffer));
	

}


unsigned char Send_SMS(char* massage,char* NumberPhone)
{

//=====================Посылаем   команду на работу в текстовом режиме==========================
	Clear_Usart_Buffer();
	strcat(NumberPhone,"\n");
	
	
	//Проверка линии связи с SIM300
	SIM300Cmd("AT+CMGF=1\n");	//Команда на отправку сообщений в текстовом режиме

	char compFlag=strcmp(sim300_buffer,"AT+CMGF=1\n");
	if (compFlag==0)
	{
		//Модуль вернул ОК<Enter>
		//Можем передавать сообщение на указанный номер
		//Формат отправки(AT+CMGS=номер телефона+Enter)
		SIM300Cmd(strcat("AT+CMGS=",NumberPhone));
		//Формат отправки(message+0x1A)
		USART_WriteString(massage);Usart_Transmit_SendChar(CTRL_Z);

		return SIM300_SendMessage_OK;
	}
	else
	{
		return SIM300_SendMessage_ERROR;
	}


	
	

}

void Recieve_SMS(char* Buffer)
{
	UReadBuffer(sim300_buffer,10);
	char  flagcomp=strcmp(sim300_buffer,"+CMTI:'SM',1");
	if (flagcomp==0)
	{
	//начинаем читать непрочитанные сообщения
	SIM300Cmd("AT+CMGL='REC UNREAD'");	//Команда на отправку сообщений в текстовом режиме
	UReadBuffer(sim300_buffer,128);
	Buffer=(char*)sim300_buffer;

	}
}

