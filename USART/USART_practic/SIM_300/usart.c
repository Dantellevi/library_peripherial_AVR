#include "usart.h"



//-------------------------------------------------------------------------
//	Функция инициализации USART.
//
//	Принимает аргументы:
//
//		long int baudrate - Передает функции значение скорости передачи в БОД.
//-------------------------------------------------------------------------

void Usart_Init(long int baudrate)
{

	UBRRH=((F_CPU/16/baudrate-1)>>8);
	UBRRL = (F_CPU/16/baudrate-1);

	UCSRA = 0x00;
	UCSRB |= (3 << TXEN) | (1 << RXCIE);
	UCSRC = (1 << URSEL) | (3 << UCSZ0);

}


//-------------------------------------------------------------------------
//	Функция передачи байта в USART.
//	Принимает аргументы:
//
//		char data - Передает функции байт, который необходимо послать в порт.
//						  Данная функция не использует прерывания USART.
//-------------------------------------------------------------------------

void Usart_Transmit_SendChar(char data)
{

	while (!( UCSRA & (1 << UDRE)));
	UDR = data;
}

//=============================================================================================
//The USART ISR
ISR(USART_RXC_VECT)
{
	//Read the data
	char data=UDR;

	//Now add it to q

	if(((UQEnd==RECEIVE_BUFF_SIZE-1) && UQFront==0) || ((UQEnd+1)==UQFront))
	{
		//Q Full
		UQFront++;
		if(UQFront==RECEIVE_BUFF_SIZE) UQFront=0;
	}
	

	if(UQEnd==RECEIVE_BUFF_SIZE-1)
	UQEnd=0;
	else
	UQEnd++;


	URBuff[UQEnd]=data;

	if(UQFront==-1) UQFront=0;

}

//==========================================================================
//-------------------------------------------------------------------------
//	Функция приема байта в USART.
//	Возращаемые аргументы:
//
//		Возращает символ из регистра данных USART интерфейса
//						  
//-------------------------------------------------------------------------
char USART_ReadData(void)
{
	char data;
	
	//Check if q is empty
	if(UQFront==-1)
	return 0;
	
	data=URBuff[UQFront];
	
	if(UQFront==UQEnd)
	{
		//If single data is left
		//So empty q
		UQFront=UQEnd=-1;
	}
	else
	{
		UQFront++;

		if(UQFront==RECEIVE_BUFF_SIZE)
		UQFront=0;
	}

	return data;
}

/*
		Сообщает количество данных в очереди FIFO.
		Возращаемое значение:
		uint8_t -возращает количество данных в очереди FIFO

*/
uint8_t UDataAvailable(void)
{
	if(UQFront==-1) return 0;
	if(UQFront<UQEnd)
	return(UQEnd-UQFront+1);
	else if(UQFront>UQEnd)
	return (RECEIVE_BUFF_SIZE-UQFront+UQEnd+1);
	else
	return 1;
}


/*
		======================Функция передает по USART строку===========
		Принимаемые значения:
		str- массив символов(строка) для передачи
*/

void USART_WriteString(char *str)
{
	while((*str)!='\0')
	{
		Usart_Transmit_SendChar(*str);
		str++;
	}
}

/*
Копирует содержимое FIFO буфера в память, 
определенную buff, количество 
скопированных данных определяется параметром len. 
Если по UART в FIFO буфер пришло меньше данных, 
чем надо (в соответствии с параметром len), 
то оставшееся место будет заполнено нулями.
		
		Принимаемые данные:
			buff-массив типа char для приема данных из буфера
			len-количество данных
*/

void UReadBuffer(void *buff,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++)
	{
		((char*)buff)[i]=USART_ReadData();
	}
}

/*
	Отменяет ожидание данных FIFO буфером. 
	Прежде чем отправлять новую команду GSM 
	модулю, сначала отмените ожидание 
	данных FIFO буфером.
*/
void UFlushBuffer(void)
{
	while(UDataAvailable()>0)
	{
		USART_ReadData();
	}
}



//--------------------------------------------------------------------------
//Функция отправляет в порт значение целочисленной переменной
//Принимаемые значения:

//				int -целочисленное значение,которое преобразуется в строку

//--------------------------------------------------------------------------
void Usart_int_Transmit(int data)
{
	char str[40];
	itoa(data,str,10);
	USART_WriteString(str);


}