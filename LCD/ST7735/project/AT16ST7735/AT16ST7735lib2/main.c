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
	//WriteChar8x11(40,40,'S',RED);
	TFTSingleColor(YELLOW);
	DrawRectangle(20,20,60,60,RED,1);
	WriteString8x11(10,10,mas,RED);
	
    while (1) 
    {
    }
}

