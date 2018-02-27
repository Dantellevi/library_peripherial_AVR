

#include <avr/io.h>

#include <axlib/main_init.h>
#include <axlib/i2c.h>
#include <axlib/pcF8574.h>

#define ADD 0x4E // Адрес микросхемы

/*
	LCD		Микросхема
	RS		P0
	RW		P1
	EN		P2
	D4		P4
	D5		P5
	D6		P6
	D7		P7
	
На ножке P3 подключени подсветка. 1 вкл, 0 выкл.
*/

void com(BYTE com)
{
	com |= 0x08;				// Р3 в единицу, дабы горела подсветка
	pcf8574_byte_out(com, ADD);	// Вывод данных
	com |= 0x04;				// Е в единицу
	pcf8574_byte_out(com, ADD);	// Вывод данных
	com &= 0xFB;				// Е в ноль
	pcf8574_byte_out(com, ADD);	// Вывод данных
}

void init(void)
{	
	com(0x30);		// Переход в 4-х битный режим
	com(0x30);		// Переход в 4-х битный режим
	com(0x30);		// Переход в 4-х битный режим
	com(0x20);		// Переход в 4-х битный режим
	com(0x20);		// Установка параметров
	com(0x80);		// Установка параметров
	com(0x00);		// Выключаем дисплей
	com(0x80);		// Выключаем дисплей
	com(0x00);		// Очищаем дисплей
	com(0x10);		// Очищаем дисплей
	com(0x00);		// Устанавливаем режим ввода данных
	com(0x60);		// Устанавливаем режим ввода данных
	com(0x00);		// Включаем дисплей с выбранным курсором
	com(0xC0);		// Включаем дисплей с выбранным курсором
}

void char_out(BYTE data)
{	  
	BYTE data_h = ((data & 0xF0) + 0x09);
	BYTE data_l = ((data << 4) + 0x09);
	       					
	pcf8574_byte_out(data_h, ADD); // Передача старших 4 бит
	data_h |= 0x04;
	pcf8574_byte_out(data_h, ADD); // Передача старших 4 бит
	data_h &= 0xF9;
	pcf8574_byte_out(data_h, ADD); // Передача старших 4 бит
	
	pcf8574_byte_out(data_l, ADD); // Передача младших 4 бит
	data_l |= 0x04;
	pcf8574_byte_out(data_l, ADD); // Передача младших 4 бит
	data_l &= 0xF9;
	pcf8574_byte_out(data_l, ADD); // Передача младших 4 бит
}

void str_out(BYTE *str)
{
	while((*str) != '\0')
	{
		char_out(*str);
		str++;
	}
}

int main(void)
{
	
	init();
	str_out("ЁPҐBET MҐP!");
	
    while(1)
    {
		
    }
}