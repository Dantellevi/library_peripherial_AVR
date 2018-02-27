#include "eepromext.h"

char err1=0;// сюда вернем ошибку

int EE_WriteByte(unsigned char c)
{
	TWDR=c;//запишем байт в регистр данных
	TWCR = (1<<TWINT)|(1<<TWEN);//включим передачу данных
	while(!(TWCR&(1<<TWINT)));//подождем пока установится TWIN
	if ((TWSR & 0xF8) != TW_MT_DATA_ASK)
	{
		return 1;
	}
	return 0;
}

unsigned char EE_ReadByte(void)
{
	err1=0;
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);//включим прием данных
	while(!(TWCR & (1<<TWINT)));//подождем пока установится TWIN
	if ((TWSR & 0xF8) != TW_MR_DATA_ASK)  err1=1;
	else err1=0;
	return TWDR;
}

unsigned char EE_ReadLastByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);//включим прием данных
	while(!(TWCR&(1<<TWINT)));//подождем пока установится TWIN
	if ((TWSR & 0xF8) != TW_MR_DATA_NASK)  err1=1;
	else err1=0;
	return TWDR;
}