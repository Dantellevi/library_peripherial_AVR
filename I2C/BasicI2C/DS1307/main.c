/*
 * DS1307.c
 *
 * Created: 07.02.2018 15:17:48
 * Author : Dante_L_Levi
 */ 

 #include "Main.h"

 unsigned char sec,min,hour,day,date,month,year;




 /*
 ============================������� ������ ������ � ���������� ds1307=============
 */
 void Read_RTCTime(void)
 {
	//������ �����
	I2C_SendByteAddR(0,0b11010000); //��������� �� ����� 0
	_delay_ms(300);
	Start_I2C();
	I2C_SendByte(0b11010001); //�������� � ���������� ��� ������
	sec = I2C_ReadByte();
	min = I2C_ReadByte();
	hour = I2C_ReadByte();
    day = I2C_ReadByte();
	date = I2C_ReadByte();
	month = I2C_ReadByte();
	year = I2C_ReadLastByte();
	Stop_I2C();
	sec = RTC_ConvertFromDec(sec); //����������� � ���������� ������
	min = RTC_ConvertFromDec(min); //����������� � ���������� ������
	hour = RTC_ConvertFromDec(hour); //����������� � ���������� ������
	day = RTC_ConvertFromDec(day); //����������� � ���������� ������
	year = RTC_ConvertFromDec(year); //����������� � ���������� ������
	month = RTC_ConvertFromDec(month); //����������� � ���������� ������
	date = RTC_ConvertFromDec(date); //����������� � ���������� ������
	//-------------------------------------------
	Usart_char_out(date/10+0x30);//����������� ����� � ��� �����
	Usart_char_out(date%10+0x30);//����������� ����� � ��� �����
	Usart_char_out('.');
	Usart_char_out(month/10+0x30);//����������� ����� � ��� �����
	Usart_char_out(month%10+0x30);//����������� ����� � ��� �����
	Usart_char_out('.');
	Usart_char_out(year/10+0x30);//����������� ����� � ��� �����
	Usart_char_out(year%10+0x30);//����������� ����� � ��� �����
	Usart_char_out(' ');
	Usart_char_out('-');
	Usart_char_out(day+0x30);//����������� ����� � ��� �����
	Usart_char_out('-');
	Usart_char_out(' ');
	Usart_char_out(' ');
	Usart_char_out(hour/10+0x30);//����������� ����� � ��� �����
	Usart_char_out(hour%10+0x30);//����������� ����� � ��� �����
	Usart_char_out(':');
	Usart_char_out(min/10+0x30);//����������� ����� � ��� �����
	Usart_char_out(min%10+0x30);//����������� ����� � ��� �����
	Usart_char_out(':');
	Usart_char_out(sec/10+0x30);//����������� ����� � ��� �����
	Usart_char_out(sec%10+0x30);//����������� ����� � ��� �����
	Usart_char_out(0x0d);//������� � ������ ������
	Usart_char_out(0x0a);//������� �������
 
 }


int main(void)
{
	I2C_Init();
	Usart_Init(9600);

	//=============================��������� �������=============
	Start_I2C();
	I2C_SendByte(0b11010000);
	I2C_SendByte(0);//��������� �� ������� 0�00(�������)
	I2C_SendByte(RTC_ConvertFromBinDec(0)); //�������
	I2C_SendByte(RTC_ConvertFromBinDec(44)); //������
	I2C_SendByte(RTC_ConvertFromBinDec(15)); //����
	I2C_SendByte(RTC_ConvertFromBinDec(3)); //���� ������
	I2C_SendByte(RTC_ConvertFromBinDec(7)); //����
	I2C_SendByte(RTC_ConvertFromBinDec(2)); //�����
	I2C_SendByte(RTC_ConvertFromBinDec(18)); //���
	Stop_I2C();
	//===========================================================





    while (1) 
    {
		Read_RTCTime();
		_delay_ms(500);

    }
}

