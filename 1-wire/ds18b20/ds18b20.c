
#define F_CPU 8000000L							// ������� ������ ����� ��� ������ ��������� ��������
#define PORT_W 5								// ���� ��� 1-wire A-1, B-2, C-3, D-4, E-5, F-6, G-7
#define PIN_W 6									// ����� ���� ��� ������ � ����� 1-wire

#include <avr/io.h>						
#include <mylib/dig.h>
#include <mylib/1ware.h>						// ��������� ���� �����

unsigned char s, d, znak;	
unsigned char temp[2];							// ������ ��� ��������� ������ �� �������. ������, ��. ������ �� ������ ���� �� 9 �����, ��� ��� ������ ������� �������� 9 ����
int temper;										// ���������� ��� �����������

int main(void)							
{
	DDRA=0xFF;
	DDRC=0xFF;
	DDRF=0x0E;
	PORTA=0xFF;
	PORTF=0x0E;
	PORTF=0x06;
	PORTC=0x00;
	PORTA=0x01;
	
	
    while(1)
    {
		owire_init();							// ����� �������
		owire_write(0xCC);						// ��� ��� ����. ����������������� �������
		owire_write(0x44);						// ������� ������ �������������� �����������
		while(!(PINE&0x40));					// ����� ���� ������ ������ � ��������������� � ������� ������ � ���� � ������
		owire_init();							// ����� �������.
		owire_write(0xCC);						// ����� ���� �� ���� �����
		owire_write(0xBE);						// ������� �������� ������ �� ������� � �������
		
		temp[0]=owire_read();					// ������ ������� ���� �����������
		temp[1]=owire_read();					// ������ ������� ���� �����������
		
		znak=0;									// ���� ����� "+"
		if(temp[1]&0x80)						// ���� ����������� ���������
		{
			temp[0] = (~temp[0])+1;				// �������� ��� + 1
			temp[1] = ~temp[1];					// �������� ���
			znak=1;								// ���� ����� "-"
		}
		
		temper = ((temp[1]<<8)|(temp[0]*5));	// ��� ����-������� ������ � ���������� temper �������� ����������� ���������� �� 10. �������� 23,5 �������� ����� � ���� 235
		
		
		
		s=0;									// ��� ��� ����� ����� �� ���������� � � ������ ������� �� ��� �� ������. �������� ����������� ����� � ���������� temper
		d=0;
		while(temper>99)
		{
			temper-=100;
			s++;
		}
		while(temper>9)
		{
			temper-=10;
			d++;
		}
		
		if(znak) led_out_char(13,0,0);
		led_out_char(s,1,0);
		led_out_char(d,2,1);
		led_out_char((char)temper,3,0);
		led_out_char(11,4,0);
		led_out_char(12,5,0);
		led_out_char(14,5,0);
		
    }
}