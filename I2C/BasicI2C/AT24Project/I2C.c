#include "I2C.h"


void I2CStart(void)
{

	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//вкл. бит старт(TWSTA),вкл. перырвани€(TWINT),разрешение работы(TWEN)
	while(!(TWCR&(1<<TWINT)));//подождем пока установитс€ TWIN

}


void I2CStop(void)
{
	TWCR=(1<<TWINT)|(TWSTO)|(1<<TWEN);	//вкл. прерывани€(TWINT) ,  выставл€ем флаг остановки- STOP(TWSTO),разрешение работы(TWEN)

}


void I2C_Init(void)
{

	TWBR=0x20;//100к√ц при F_CPU=8ћ√ц

}


void I2C_SendByte(uint8_t data)
{

	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);//вкл. передачу байта
	while(!(TWCR&(1<<TWINT)));//ждем установки флага

}


void I2C_SendByteByADDR(uint8_t c,uint8_t addr)
{
	I2CStart();//отправл€ем услови€ старта
	I2C_SendByte(addr);//отправим в шину адрес устройства + бит чтени€/записи
	I2C_SendByte(c);//ќтправим байт данных
	I2CStop();//отправим условие STOP

}


uint8_t I2C_ReadByte(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(TWEA);
	while (!(TWCR&(1<<TWINT)));
	return TWDR;
	
}

uint8_t I2C_ReadLastByte(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN);
	while (!(TWCR&(1<<TWINT)));
	return TWDR;
	
}