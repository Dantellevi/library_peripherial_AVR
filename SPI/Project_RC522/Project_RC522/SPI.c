#include "SPI.h"

void SPI_Master_Init(char flagMode,char del)
{
	if (flagMode==MASTER)
	{
		/*�������� �� ����� ����� �� SPI ����������*/
	DDR_SPI|=(1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	PORT_SPI&=~((1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS));


	/*������� SPI-��������� , ��������� ����� Master, ��������� �������� �������*/
	/*
	SPSR (SPI Status Register) � ��������� �������
	SPE (SPI Enable) � ���, ���������� ���� SPI.
	MSTR (Master/Slave Select) � ���, ������� ��������� ���������� ������� ���� �������. ��� ��������� ������� ���� 1 ���������� ����� �������.

	*/
	/*(���. ����� �������)|(���.SPI)|(������������� ������������ 16)*/
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

void SPI_SendByte(char byte)
{

	SPDR = byte;
	while (!(SPSR & (1 << SPIF)));
}

uint8_t spi_read_byte(void){
	SPDR = 0x00;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}