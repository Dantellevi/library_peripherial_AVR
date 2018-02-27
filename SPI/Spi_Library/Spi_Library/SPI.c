#include "SPI.h"


void SPI_INICILIZER(void)
{
	DDR_SPI|=(1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	//DDR_SPI&=~(1<<MISO);
	//PORT_SPI=~(1<<MISO);
	PORT_SPI&=~((1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS));
	SPCR |=(1 <<SPE)|(1 <<MSTR)|(1<<SPR0);//включим шину, объ¤вим ведущим, делитель 16
}

void SPI_Master_Init(char flagMode,char del)
{
	if (flagMode==MASTER)
	{
		/*¬ыставим на выход ножки дл¤ SPI интерфейса*/
	DDR_SPI|=(1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	PORT_SPI&=~((1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS));


	/*¬ключим SPI-интерфейс , установим режим Master, установим тактовую частоту*/
	/*
	SPSR (SPI Status Register) Ч статусный регистр
	SPE (SPI Enable) Ч бит, включающий шину SPI.
	MSTR (Master/Slave Select) Ч бит, который назначает устройство ведущим либо ведомым. ѕри установке данного бита 1 устройство будет ведущим.

	*/
	/*(вкл. режим мастера)|(вкл.SPI)|(устанавливаем предделитель 16)*/
	//SPCR|=(1<<MSTR)|(1<<SPE);
	switch(del)
	{
		case DEL_16:
		{
			SPCR|=(1<<SPR0)|(1<<MSTR)|(1<<SPE);		
			break;
		}
		case  DEL_64:
		{
			SPCR|=(1<<SPR1)|(1<<MSTR)|(1<<SPE);
			break;
		}
		case DEL_128:
		{
			SPCR|=(1<<SPR1)|(1<<SPR0)|(1<<MSTR)|(1<<SPE);
			break;
		}
	}

	
	}
	
}


/*
========================================ѕередача 1-байта в сдвиговый регистр========================
*/

void SPi_Transmit_data(uint8_t data)
{
	
	SPDR=data;//заносим данные в регистр
	while(!(SPDR&(1<<SPIF)));//ожидание передачи данных
	PORT_SPI&=~(1<<DD_SS);
	_delay_ms(1);
	PORT_SPI|=(1<<DD_SS);
	

}

void SPI_SendByte(char byte)
{

	SPDR = byte;
	while (!(SPSR & (1 << SPIF)));
}


unsigned char SPI_CHangeByte(char byte)
{
	SPDR = byte;
	while(!(SPSR & (1<<SPIF)));//подождем пока данные передадутс¤ (обмен¤ютс¤)
	return SPDR;
	

}




