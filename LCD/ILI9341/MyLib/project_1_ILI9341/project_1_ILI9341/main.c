/*
 * 
 *
 * Created: 24.10.2017 10:29:21
 * Author : лепотенко А.С.
 */ 

#include "Main.h"


int main(void)
{
    TFT9341_init();
	TFT9341_FillScreen(YELLOW);
	TFT9341_DrawCircle(100,100,25,RED);
	//TFT9341_DrawRect(RED,0,0,120,120);
	//TFT9341_String(0,0,RED,YELLOW,"Hello World",1);

    while (1) 
    {
    }
}

