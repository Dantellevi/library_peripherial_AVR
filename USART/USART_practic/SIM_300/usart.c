#include "usart.h"



//-------------------------------------------------------------------------
//	������� ������������� USART.
//
//	��������� ���������:
//
//		long int baudrate - �������� ������� �������� �������� �������� � ���.
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
//	������� �������� ����� � USART.
//	��������� ���������:
//
//		char data - �������� ������� ����, ������� ���������� ������� � ����.
//						  ������ ������� �� ���������� ���������� USART.
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
//	������� ������ ����� � USART.
//	����������� ���������:
//
//		��������� ������ �� �������� ������ USART ����������
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
		�������� ���������� ������ � ������� FIFO.
		����������� ��������:
		uint8_t -��������� ���������� ������ � ������� FIFO

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
		======================������� �������� �� USART ������===========
		����������� ��������:
		str- ������ ��������(������) ��� ��������
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
�������� ���������� FIFO ������ � ������, 
������������ buff, ���������� 
������������� ������ ������������ ���������� len. 
���� �� UART � FIFO ����� ������ ������ ������, 
��� ���� (� ������������ � ���������� len), 
�� ���������� ����� ����� ��������� ������.
		
		����������� ������:
			buff-������ ���� char ��� ������ ������ �� ������
			len-���������� ������
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
	�������� �������� ������ FIFO �������. 
	������ ��� ���������� ����� ������� GSM 
	������, ������� �������� �������� 
	������ FIFO �������.
*/
void UFlushBuffer(void)
{
	while(UDataAvailable()>0)
	{
		USART_ReadData();
	}
}



//--------------------------------------------------------------------------
//������� ���������� � ���� �������� ������������� ����������
//����������� ��������:

//				int -������������� ��������,������� ������������� � ������

//--------------------------------------------------------------------------
void Usart_int_Transmit(int data)
{
	char str[40];
	itoa(data,str,10);
	USART_WriteString(str);


}