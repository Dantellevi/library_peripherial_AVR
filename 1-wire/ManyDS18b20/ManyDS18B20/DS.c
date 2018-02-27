#include "DS.h"



//-------------------------------------------------------------------------
//	������� ��������� ROM ���� �� �������.
//	��� ������� ������� ������ ������ ������� �� �����.
//  ROM ��� ������������ � ������������ ������. ����� ������� 8 ����.
//
//  ������� ���������� 0 ���� �� ����� ���� ������, 1 ���� ����� ������.
//
//	����������� ��������:
//
//		BYTE *str - ��������� �� ������ ������� �������
//-------------------------------------------------------------------------
uint8_t ds18b20_rom_code(uint8_t *str)
{
	uint8_t i=0;
	uint8_t exist=OneWire_Init();
	OWire_Write(0x33);
	while(i < 8)
	{
		*str = OWire_read();
		str++;
		i++;
	}
	return exist;
}

//-------------------------------------------------------------------------
//	������� ������� ���������� ���������.
//	��� ������� ������� ������ ������ ������� �� �����.
//
// ������������ ��������:	RESOL_9
//							RESOL_10
//							RESOL_11
//							RESOL_12
//
//-------------------------------------------------------------------------
void ds18b20_resol(uint8_t resol)
{
	OneWire_Init();
	OWire_Write(0xCC);
	OWire_Write(0x4E);
	OWire_Write(0x7D);
	OWire_Write(0xC9);
	OWire_Write(resol);
	
	_delay_ms(10);
	
	OneWire_Init();
	OWire_Write(0xCC);
	OWire_Write(0x48);
}


//-------------------------------------------------------------------------
//	������� ��������� ����������� �� �������.
//	��� ������� ������� ������ ������ ������� �� �����.
//
//-------------------------------------------------------------------------

int ds1820_all(void)
{
	uint8_t temp[2];
	int temper = 0x00;
	uint8_t exist = OneWire_Init();
	OWire_Write(0xCC);
	OWire_Write(0x44);
	
	_delay_ms(10);

	OneWire_Init();
	OWire_Write(0xCC);
	OWire_Write(0xBE);
	
	temp[0] = OWire_read();
	temp[1] = OWire_read();
	
	if(temp[1] & 0x80)
	{
		temp[0] = (~temp[0])+1;
		temp[1] = ~temp[1];
		ZNAKK = MINUST;
	}
	else
	{
		ZNAKK = PLUST;
	}
	
	OneWire_Init();
	
	temper = (((int)temp[1] << 8) | (int)(temp[0] * 5));
	if(exist) return 	temper;
	else return 0x8000;

}




//-------------------------------------------------------------------------
//	������� ��������� ����������� �� ������� �� ��� ROM ����.
//	����� �������� ��� ������� ���������� �������� �� �����.
//
//  ������������ ���������
//
//		BYTE *rom - ��������� �� 8-� ������� ������ � ROM �����
//
//-------------------------------------------------------------------------
int ds1820_read_t(uint8_t *rom)
{
	uint8_t i = 0;
	uint8_t temp[2];
	int temper = 0x00;
	uint8_t rm = 0;
	
	uint8_t exist = OneWire_Init();
	OWire_Write(0xCC);
	OWire_Write(0x44);
	
	_delay_ms(10);

	i = 0;
	
	OneWire_Init();
	OWire_Write(0x55);
	
	rm = *rom;
	
	while(i < 8)
	{
		OWire_Write(*rom);
		rom++;
		i++;
	}
	OWire_Write(0xBE);

	temp[0] = OWire_read();
	temp[1] = OWire_read();
	
	if(temp[1] & 0x80)
	{
		temp[0] = ~temp[0] + 1;
		temp[1] = ~temp[1];
		ZNAKK = MINUST;
	}
	else
	{
		ZNAKK = PLUST;
	}
	
	if(rm == 0x10)
	{
		temper = (temp[1] << 8) | (temp[0] * 5);
	}
	else
	{
		temper = ((temp[1] << 5) | (temp[0] >> 3)) * 5;
		//temper = temp[0];
	}
	
	OneWire_Init();
	
	if(exist) return 	temper;
	else return 0x8000;

}