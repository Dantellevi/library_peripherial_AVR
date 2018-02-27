#include "lm75AD.h"


/*
======================Функция чтения температуры=========
		Принимамые параметры:
			adress-адрес микросхемы LM75AD(0-7)макс. 7 датчиков
		Возращаемые параметры:
			возращает 2-байтную переменную LSB  и MSB
*/
unsigned int LM75AD_GetTemp(unsigned char address)
{
	unsigned int b;
	unsigned int Temp;
	I2C_StartCondition();	//генерируем условие СТАРТ
	I2C_SendByte(LM75AD_ADRES|(address<<1));	//адрес плюс бит записи
	I2C_SendByte(TEMP);	//отправляем адрес регистра TEMP
	I2C_StartCondition();	//производим рестарт
	I2C_SendByte((LM75AD_ADRES|(address<<1))|1);	//адрес + бит чтения
	Temp=I2C_ReadByte();	//читаем 1-ый байт MSB
	b=I2C_ReadLastByte();	//читаем 2-ой байт LSB
	I2C_StopCondition();	//генерируем СТОП
	Temp=(Temp<<8)|b;		//комбинируем int переменную из 2-ух байт MSB и LSB
	return Temp;
}

//=========================================================

//Функция принимает значение регистра Temp и возвращает
//температуру от -55 до 127 шаг 1
char LM75AD_Convert(unsigned int TT)
{
	return (TT>>8);
}

//=====================================================









