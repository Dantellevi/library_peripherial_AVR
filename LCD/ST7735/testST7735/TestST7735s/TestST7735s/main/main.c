
#include <avr/io.h>
#include <stdio.h>

#include "main_init.h"
#include "axlib/spi.h"
#include "axlib/st7735.h"

// Здесь должны находиться ваши подключаемые файлы


// Здесь должны находиться ваши глобальные переменные


int main(void)
{
// Здесь должны находиться ваши локальные переменные
DDRB|=(1<<PB3);
PORTB|=(1<<PB3);
// Инициализация TFT ST7735
lcd_st7735_init();

// Закрасить весь экран цветом
lcd_st7735_screen(RGB16(0xFFFFFF));

// Вывод строки
lcd_st7735_putstr_xy(0, 0, "Hello World!", RGB16(0x000000), RGB16(0xFFFFFF));

	while(1)
	{

		// Здесь должен находиться ваш код 
	}
}
