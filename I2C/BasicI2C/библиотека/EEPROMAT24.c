#include "EEPROMAT24.h"
char err1=0;// сюда вернем ошибку

unsigned char EE_ReadByte(void)
{
	err1=0;
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//вкл. прием
	while (!(TWCR&(1<<TWINT)));
	if ((TWCR&0xF8)!=TW_MR_DATA_ASK)
	{
		err1=1;
	}
	else
	{
		err1=0;
	}
	return TWDR;
	
}


int EE_WriteByte(unsigned char c)
{
	
	TWDR=c;
	TWCR=(1<<TWINT)|(1<<TWEN);//вкл. передачу байта
	while(!(TWCR&(1<<TWINT)));//ждем установки флага
	if ((TWSR&0xF8)!=TW_MT_DATA_ASK)
	{
		return 1;
	}
	else
	{

		return	0;
	}

}




unsigned char EE_ReadLastByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);//включим прием данных
	while(!(TWCR&(1<<TWINT)));//подождем пока установится TWIN
	if ((TWSR & 0xF8) != TW_MR_DATA_NASK)  err1=1;
	else err1=0;
	return TWDR;
}