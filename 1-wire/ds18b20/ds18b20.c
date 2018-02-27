
#define F_CPU 8000000L							// Частота кварца нужна для точных временных задержек
#define PORT_W 5								// Порт для 1-wire A-1, B-2, C-3, D-4, E-5, F-6, G-7
#define PIN_W 6									// Номер пина для работы с шиной 1-wire

#include <avr/io.h>						
#include <mylib/dig.h>
#include <mylib/1ware.h>						// Подрубаем нашу библу

unsigned char s, d, znak;	
unsigned char temp[2];							// Массив для получения данных из датчика. Смешно, да. Вообще он должен быть на 9 ячеек, так как память датчика содержит 9 байт
int temper;										// Переменная для температуры

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
		owire_init();							// Сброс датчика
		owire_write(0xCC);						// Без РОМ кода. Широковещательная команда
		owire_write(0x44);						// Команда начать преобразование температуры
		while(!(PINE&0x40));					// Тупим пока датчик пыхтит с преобразованием и укладки данных к себе в память
		owire_init();							// Сброс датчика.
		owire_write(0xCC);						// Опять орем на всех сразу
		owire_write(0xBE);						// Команда передать данные от датчика к мастеру
		
		temp[0]=owire_read();					// Читаем младший байт температуры
		temp[1]=owire_read();					// Читаем старший байт температуры
		
		znak=0;									// Знак равен "+"
		if(temp[1]&0x80)						// Если температура минусовая
		{
			temp[0] = (~temp[0])+1;				// Побитное или + 1
			temp[1] = ~temp[1];					// Побитное или
			znak=1;								// Знак равен "-"
		}
		
		temper = ((temp[1]<<8)|(temp[0]*5));	// Эта абра-кадабра кладет в переменную temper значение температуры умноженной на 10. Например 23,5 градусов будут в виде 235
		
		
		
		s=0;									// Это уже пошло вывод на дисплейчик и к работе датчика не как не влияет. Значение температуры лежит в переменной temper
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