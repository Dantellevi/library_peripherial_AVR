#include "MCP4921.h"

/*
======================================������� �������������� ������������ ��������� ���������� � ���=============
					����������� ���������:
					X-�������� ����������
					Vref-������� ����������

					����������� ��������:
					��� ����������� ��� ������ ��������� ����������
*/
unsigned int MCP_4921_Convert_Data(float X, float Vref)
{
	unsigned int u;
	X=X/Vref;
	u=(unsigned int)(X*4096);
	return u;
}

#define  A_B 7		//��� ���������� �� ����� ������
#define  BUF 6      //Input Buffer Control bit
#define  GA  5		//��� ������ ��������� �������� �������
#define  SHDN 4		//��� ���������� �������� ���������


//=================������� �������� ���� � ��� MCP4921========================

void MCP4921_Sent_Data(unsigned int h)
{
	
	unsigned int mask_inf=h>>8;
	mask_inf|=(1<<SHDN)|(1<<GA);
	PORT_SPI&=~(1<<DD_SS);
	SPI_SendByte(mask_inf);//���������� ������� ����
	SPI_SendByte(h);//���������� ������� ����
	PORT_SPI|=(1<<DD_SS);
} 