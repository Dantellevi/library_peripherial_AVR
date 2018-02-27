#include "SPI.h"

void port_ini(void)
{

	PORTD=0x00;
	DDRD=0xFF;
	PORTB|=(1<<SS)|(1<<MISO)|(1<<MOSI);
	DDRB|=(1<<SS)|(1<<MOSI)|(1<<SCK);

}




void SPI_SendByte (unsigned char byte)
{

	unsigned char i;
	for (i=0;i<8;i++) //�������� �� ����� �����
	{
		if ((byte&0x80)==0x00)//��������� ����� ���
		PORTB&=~(1<<MOSI); //���� 0, �� ���������� 0 �� ����
		else PORTB|=(1<<MOSI); //���� 1, �� ���������� 1

		byte<<=1; //�������� �����, � ������� �������� ��� �������� ���������� ����
		PORTB|=(1<<SCK); //����� �� ����� SCK
		asm("nop"); //1 ���� �������
		PORTB&=~(1<<SCK); //���� �� ����� SCK
	}

}


unsigned char SPI_ReceiveByte(void)
{
	unsigned char i, result=0;
	for(i=0;i<8;i++)
	{
		PORTB|=(1<<SCK);//����� �� ����� SCK
		result<<=1;//�������� ����� ����, ����� �������� ��������� ���
		if((PINB&(1<<MISO))!=0x00)//������� ����� ��� � ������� ������
		result=result|0x01;//������� ��������� � ����� ����� MISO ���
		PORTB&=~(1<<SCK);//���� �� ����� SCK
		asm("nop");//1 ���� �������
	}
	 return result;//������ ���������
}


//������ ��� ����� �������� ������� �������� ������ � SD.

/*
� ������ ������� ���� ������. � ������ ������� ������ 8, ��� ��� ��� ��������� CMD8. 
����� ���������� �������� � ����� ������. �� �� ���� �����, ��� ���� ���������� ������ ����� ���, 
������ ������ ��� ������� ��� ����� ����� �������� ����������.

�� ����� ��� �������� ������� ������� �� 48 ���, �� ���� �� 6 ������. ������ ������ ���������� ������� ���� � �������, 
������ � �������� ��������� � �����, ������ � ��������, � �������� � ����������� ���������.

��������� ��� � ������ 0.
��� �������� � 1.
������ ������� � � ������ ������ ������� ����� 8.
����� ���� ����������������� ���� � ����� 20 ����, ��� ������ ����.
����� ���� ���������, 7 ��� ����������� ����� � �������� ��� � ������ 1.
������� ��� ����� ����� �������� ������� �������� �������
������� � ����� ����� ������� �������� � ����� ������, ��� ��� ����� ������� ����� ��������� ����� ������������
*/

unsigned char SD_cmd(char dt0,char dt1,char dt2,char dt3,char dt4,char dt5)
{
	unsigned char result;
	long int cnt;
	SPI_SendByte(dt0); //������
	SPI_SendByte(dt1); //��������
	SPI_SendByte(dt2);
	SPI_SendByte(dt3);
	SPI_SendByte(dt4);
	SPI_SendByte(dt5); //����������� �����
	cnt=0;
	do
	{ //��� ����� � ������� R1 (������� ��� 109)
		result=SPI_ReceiveByte();
		cnt++;
	} while (((result&0x80)!=0x00)&&cnt<0xFFFF);
	return result;

}




/*
=======================������� � ������������� ����� �����===================

*/

unsigned char SD_Init(void)
{
	unsigned char i,temp;
	long int cnt;
	for(i=0;i<10;i++) //80 ��������� (�� ����� 74) ������� ��� 91
	SPI_SendByte(0xFF);
	/*
	�� ���� �� �������� 10 ������ FF, ��� ����� ��������� 80 ��������. 
	������ ���� SS �� ����� ��������� �� ��������. ������ ��������� �� 
	MOSI � ����� �� �������, ����� 80 ��������� �� ����� SCK ��� �������� MOSI. 
	�� ������� ��������. ��������� �������. ������ �� ��� �������� ����� ��� ����, 
	����� ����� ��� ������� ����� ������, ��� �������� �� � ��� ���������� ������ �� 
	SPI � ������������� � ��������������� �����.
	*/

	PORTB&=~(1<<SS);//�������� SS
	temp=SD_cmd(0x40,0x00,0x00,0x00,0x00,0x95); //CMD0 ������� ��� 102 � 96
	if(temp!=0x01) return 1; //����� ���� ����� �� 0x01
	SPI_SendByte(0xFF);
	cnt=0;
	do
	{
		temp=SD_cmd(0x41,0x00,0x00,0x00,0x00,0x95); //CMD1 �������� �����, �������� ������ ������
		SPI_SendByte(0xFF);
		cnt++;
	} while ((temp!=0x00)&&cnt<0xFFFF); //��� ������ R1
	if(cnt>=0xFFFF) return 2;
	return 0;

}

/*
�������� ������� ��� ������ ����� � ����� SD ���� ������� main(). ������ ����� ������, �� ������, ��� ������ ��� ��� ������, 
��� ��� ������� ���� ���-�� ��������, ����� ����� ��������� � ���������, ��� ��� ������ ��, ��� �� ��������
*/

unsigned char SD_Write_Block (char* bf, unsigned char dt1, unsigned char dt2, unsigned char dt3, unsigned char dt4)
{
	unsigned char result;
	long int cnt;
	//����� ������� �������� �������
	result=SD_cmd(0x58,dt1,dt2,dt3,dt4,0x95); //CMD24 ������� ��� 51 � 97-98
	if (result!=0x00) return 6; //�����, ���� ��������� �� 0x00
	SPI_SendByte (0xFF);
	SPI_SendByte (0xFE); //������ ������
	//������ ������ � ��� ������ ���� �����, ��� ������ � ����� �������� ������, ��������� �� ����� ������ � ���������� ����� ������
	for (cnt=0;cnt<512;cnt++) SPI_SendByte(bf[cnt]); //������
	SPI_SendByte (0xFF); //���������� �����
	SPI_SendByte (0xFF);
	result=SPI_ReceiveByte();
	if ((result&0x05)!=0x05) return 6; //�����, ���� ��������� �� 0x05 (������� ��� 111)
	cnt=0;
	do { //���� ��������� ��������� BUSY
		result=SPI_ReceiveByte();
		cnt++;
    	} while ( (result!=0xFF)&&(cnt<0xFFFF) );

	if (cnt>=0xFFFF) return 6;

	return 0;
}



unsigned char SD_Read_Block (char* bf, unsigned char dt1, unsigned char dt2, unsigned char dt3, unsigned char dt4)
{
	unsigned char result;
	long int cnt;
	result=SD_cmd (0x51,dt1,dt2,dt3,dt4,0x95); //CMD17 ������� ��� 50 � 96
	if (result!=0x00) return 5; //�����, ���� ��������� �� 0x00
	SPI_SendByte (0xFF);
	cnt=0;
	do{ //���� ������ �����
		result=SPI_ReceiveByte();
		cnt++;
	} while ( (result!=0xFE)&&(cnt<0xFFFF) );
	if (cnt>=0xFFFF) return 5;
	for (cnt=0;cnt<512;cnt++) bf[cnt]=SPI_ReceiveByte(); //�������� ����� ����� �� ���� � �����

	SPI_ReceiveByte(); //�������� ����������� �����
	SPI_ReceiveByte();
	return 0;
}

