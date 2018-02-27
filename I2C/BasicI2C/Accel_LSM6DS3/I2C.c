#include "I2C.h"



void I2C_Init(void)
{
	TWBR=0x20;//скорость передачи (при 8 мгц получается 100 кгц, что и необходимо для общения с ds1307)

}



void Start_I2C(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//подождем пока установится TWIN
}


void Stop_I2C(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}



void I2C_SendByte(unsigned char data)
{
	TWDR=data;//запишем байт в регистр данных
	TWCR = (1<<TWINT)|(1<<TWEN);//включим передачу байта
	while (!(TWCR & (1<<TWINT)));//подождем пока установится TWIN
}


void I2C_SendByteAddR(unsigned char data,unsigned char addr)
{
	Start_I2C();
	I2C_SendByte(addr); // Отправим в шину адрес устройства + бит чтения-записи
	I2C_SendByte(data);// Отправим байт данных
	Stop_I2C();

}

unsigned char I2C_ReadByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	return TWDR;//читаем регистр данных
}


unsigned char I2C_ReadLastByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	return TWDR;//читаем регистр данных
}