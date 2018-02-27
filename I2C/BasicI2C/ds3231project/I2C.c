#include "I2C.h"



void I2C_Init(void)
{
	TWBR=0x20;//�������� �������� (��� 8 ��� ���������� 100 ���, ��� � ���������� ��� ������� � ds1307)

}



void Start_I2C(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//�������� ���� ����������� TWIN
}


void Stop_I2C(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}



void I2C_SendByte(unsigned char data)
{
	TWDR=data;//������� ���� � ������� ������
	TWCR = (1<<TWINT)|(1<<TWEN);//������� �������� �����
	while (!(TWCR & (1<<TWINT)));//�������� ���� ����������� TWIN
}


void I2C_SendByteAddR(unsigned char data,unsigned char addr)
{
	Start_I2C();
	I2C_SendByte(addr); // �������� � ���� ����� ���������� + ��� ������-������
	I2C_SendByte(data);// �������� ���� ������
	Stop_I2C();

}

unsigned char I2C_ReadByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR & (1<<TWINT)));//�������� ��������� ���� TWIN
	return TWDR;//������ ������� ������
}


unsigned char I2C_ReadLastByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//�������� ��������� ���� TWIN
	return TWDR;//������ ������� ������
}