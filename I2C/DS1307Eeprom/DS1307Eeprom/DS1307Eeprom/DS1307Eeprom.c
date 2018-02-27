#include "main.h"

unsigned char bt[32];

int main(void)
{
	int i=0;
	USART_Init (8);
	I2C_Init();
	
	//Чтение
	I2C_StartCondition(); //Отправим условие START
	USART_Transmit(TWSR);//читаем статусный регистр
	I2C_SendByte(0b10100000);//передаем адрес устройства и бит записи (0)
	USART_Transmit(TWSR);//читаем статусный регистр
	I2C_SendByte(0);//передаем старшую часть адреса ячейки памяти
	USART_Transmit(TWSR);//читаем статусный регистр
	I2C_SendByte(0);//передаем младшую часть адреса ячейки памяти
	USART_Transmit(TWSR);//читаем статусный регистр
 	I2C_StartCondition(); //Отправим условие START
 	USART_Transmit(TWSR);//читаем статусный регистр
 	I2C_SendByte(0b10100001);//передаем адрес устройства и бит чтения (1)
 	USART_Transmit(TWSR);//читаем статусный регистр
 	for(i=0;i<=30;i++)
 	{
 		bt[i] = EE_ReadByte(); //прочитаем байт из микросхемы
 		//USART_Transmit(TWSR);//читаем статусный регистр
 	}
 	bt[31] = EE_ReadLastByte(); //прочитаем байт из микросхемы
	//USART_Transmit(TWSR);//читаем статусный регистр
	I2C_StopCondition(); //Отправим условие STOP
	USART_Transmit(TWSR);//читаем статусный регистр
 	for(i=0;i<=31;i++)
 	{
 		USART_Transmit(bt[i]); //отправим считанные байты в ПК
 	}

	//Запись
// 	I2C_StartCondition(); //Отправим условие START
// 	USART_Transmit(TWSR);//читаем статусный регистр
// 	I2C_SendByte(0b10100000);//передаем адрес устройства и бит записи (0)
// 	USART_Transmit(TWSR);//читаем статусный регистр
// 	I2C_SendByte(0);//передаем старшую часть адреса ячейки памяти 
// 	USART_Transmit(TWSR);//читаем статусный регистр
// 	I2C_SendByte(0);//передаем младшую часть адреса ячейки памяти
// 	USART_Transmit(TWSR);//читаем статусный регистр
// 	bt[0]=0x30;	 bt[1]=0x31;  bt[2]=0x32;  bt[3]=0x33;	bt[4]=0x34;	 bt[5]=0x35;  bt[6]=0x36;	bt[7]=0x37;
// 	bt[8]=0x38;	 bt[9]=0x39;  bt[10]=0x3A; bt[11]=0x3B; bt[12]=0x3C; bt[14]=0x3D; bt[14]=0x3E; bt[15]=0x3F;
// 	bt[16]=0x40; bt[17]=0x41; bt[18]=0x42; bt[19]=0x43;	bt[20]=0x44; bt[21]=0x45; bt[22]=0x46; bt[23]=0x47;
// 	bt[24]=0x48; bt[25]=0x49; bt[26]=0x4A; bt[27]=0x4B; bt[28]=0x4C; bt[29]=0x4D; bt[30]=0x4E; bt[31]=0x4F;
// 	for(i=0;i<=31;i++)
// 	{
// 		EE_WriteByte(bt[i]);
// 		USART_Transmit(TWSR);//читаем статусный регистр
// 	}
//  	I2C_StopCondition(); //Отправим условие STOP
//  	USART_Transmit(TWSR);//читаем статусный регистр
	
    while(1)
    {
    }
}