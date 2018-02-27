#include "I2C.h"


void I2CStart(void)
{

	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//���. ��� �����(TWSTA),���. ����������(TWINT),���������� ������(TWEN)
	while(!(TWCR&(1<<TWINT)));//�������� ���� ����������� TWIN

}


void I2CStop(void)
{
	TWCR=(1<<TWINT)|(TWSTO)|(1<<TWEN);	//���. ����������(TWINT) ,  ���������� ���� ���������- STOP(TWSTO),���������� ������(TWEN)

}


void I2C_Init(void)
{

	TWBR=0x20;//100��� ��� F_CPU=8���

}


void I2C_SendByte(uint8_t data)
{

	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);//���. �������� �����
	while(!(TWCR&(1<<TWINT)));//���� ��������� �����

}


void I2C_SendByteByADDR(uint8_t c,uint8_t addr)
{
	I2CStart();//���������� ������� ������
	I2C_SendByte(addr);//�������� � ���� ����� ���������� + ��� ������/������
	I2C_SendByte(c);//�������� ���� ������
	I2CStop();//�������� ������� STOP

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