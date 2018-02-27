#include "MCP4921.h"

/*
======================================Функция преобразования необходимого выходного напряжения в код=============
					Принимаемые параметры:
					X-выходное напряжение
					Vref-опорное напряжение

					Возращаемое значение:
					код необходимый для вывода выходного напряжения
*/
unsigned int MCP_4921_Convert_Data(float X, float Vref)
{
	unsigned int u;
	X=X/Vref;
	u=(unsigned int)(X*4096);
	return u;
}

#define  A_B 7		//Бит отвечающий за выбор канала
#define  BUF 6      //Input Buffer Control bit
#define  GA  5		//Бит выбора выходного усиления сигнала
#define  SHDN 4		//Бит управления выходной мощностью


//=================Функция передачи кода в ЦАП MCP4921========================

void MCP4921_Sent_Data(unsigned int h)
{
	
	unsigned int mask_inf=h>>8;
	mask_inf|=(1<<SHDN)|(1<<GA);
	PORT_SPI&=~(1<<DD_SS);
	SPI_SendByte(mask_inf);//отправляем старший байт
	SPI_SendByte(h);//отправляем младший байт
	PORT_SPI|=(1<<DD_SS);
} 