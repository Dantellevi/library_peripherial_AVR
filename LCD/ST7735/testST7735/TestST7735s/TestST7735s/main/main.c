
#include <avr/io.h>
#include <stdio.h>

#include "main_init.h"
#include "axlib/spi.h"
#include "axlib/st7735.h"

// ����� ������ ���������� ���� ������������ �����


// ����� ������ ���������� ���� ���������� ����������


int main(void)
{
// ����� ������ ���������� ���� ��������� ����������
DDRB|=(1<<PB3);
PORTB|=(1<<PB3);
// ������������� TFT ST7735
lcd_st7735_init();

// ��������� ���� ����� ������
lcd_st7735_screen(RGB16(0xFFFFFF));

// ����� ������
lcd_st7735_putstr_xy(0, 0, "Hello World!", RGB16(0x000000), RGB16(0xFFFFFF));

	while(1)
	{

		// ����� ������ ���������� ��� ��� 
	}
}
