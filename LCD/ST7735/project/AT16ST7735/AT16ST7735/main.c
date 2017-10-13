/*
 * Работа с  дисплеем ST7735
 *
 * Created: 11.10.2017 14:36:17
 * Author : Лепотенко А.С.
 */ 

 #include "Main.h"

 unsigned char mas[70]="Привет парни";

int main(void)
{
    TFTInit();
	TFTSingleColor(WHITE);
	lcd_st7735_putchar(20,22,'F',RED,GREEN);
	//TFTSingleColor(YELLOW);
	//DrawRectangle(20,20,60,60,RED,2);
	//WriteString8x11(10,10,mas,RED);
	//DrawTriangle(20,20,60,70,80,20,RED,2);

	
    while (1) 
    {
    }
}

