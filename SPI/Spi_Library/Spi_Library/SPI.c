#include "SPI.h"


void SPI_INICILIZER(void)
{
	DDR_SPI|=(1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	//DDR_SPI&=~(1<<MISO);
	//PORT_SPI=~(1<<MISO);
	PORT_SPI&=~((1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS));
	SPCR |=(1 <<SPE)|(1 <<MSTR)|(1<<SPR0);//������� ����, ������� �������, �������� 16
}

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


/*
========================================�������� 1-����� � ��������� �������========================
*/

void SPi_Transmit_data(uint8_t data)
{
	
	SPDR=data;//������� ������ � �������
	while(!(SPDR&(1<<SPIF)));//�������� �������� ������
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
	while(!(SPSR & (1<<SPIF)));//�������� ���� ������ ���������� (��������)
	return SPDR;
	

}




