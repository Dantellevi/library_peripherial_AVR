#include "lm75AD.h"


/*
======================������� ������ �����������=========
		���������� ���������:
			adress-����� ���������� LM75AD(0-7)����. 7 ��������
		����������� ���������:
			��������� 2-������� ���������� LSB  � MSB
*/
unsigned int LM75AD_GetTemp(unsigned char address)
{
	unsigned int b;
	unsigned int Temp;
	I2C_StartCondition();	//���������� ������� �����
	I2C_SendByte(LM75AD_ADRES|(address<<1));	//����� ���� ��� ������
	I2C_SendByte(TEMP);	//���������� ����� �������� TEMP
	I2C_StartCondition();	//���������� �������
	I2C_SendByte((LM75AD_ADRES|(address<<1))|1);	//����� + ��� ������
	Temp=I2C_ReadByte();	//������ 1-�� ���� MSB
	b=I2C_ReadLastByte();	//������ 2-�� ���� LSB
	I2C_StopCondition();	//���������� ����
	Temp=(Temp<<8)|b;		//����������� int ���������� �� 2-�� ���� MSB � LSB
	return Temp;
}

//=========================================================

//������� ��������� �������� �������� Temp � ����������
//����������� �� -55 �� 127 ��� 1
char LM75AD_Convert(unsigned int TT)
{
	return (TT>>8);
}

//=====================================================









