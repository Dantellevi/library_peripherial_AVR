
#define F_CPU 8000000UL

#include "ili9341_i8080.h"
#include <avr/io.h>
#include <util/delay.h>

uint16_t MAX_X=0, MAX_Y = 0;

int main(void)
{	
	
	Init_ILI9341(3);
	
	TFT_Fill_Screen(0, MAX_X, 0, MAX_Y, BLACK);
	TFT_Draw_String(50,100,RED,BLACK,"hub",3);
	TFT_Draw_String(122,100,CYAN,BLACK,"stub.ru",3);
	
	TFT_Draw_String(98,150,CYAN,BLACK,"ILI9341",3);
	
	//TFT_Fill_Screen(0, MAX_X, 0, MAX_Y, 0x0ff0);
	//TFT_Fill_Rectangle(10, 10,1,0,YELLOW);
	//TFT_Draw_Char(15,15,GREEN,BLACK,'h',3);
	/*
	//на чёрном цвете хорошо видно как изменяется контрастность
 	TFT_Fill_Screen(0, MAX_X, 0, MAX_Y, BLACK);
 	//VCOM Control 1
	TFT_Send_Cmd(0xC5);		//(Contrast)
	TFT_Write_Data(0x00);	//3.825
	TFT_Write_Data(0x34);	//-1.375
	//VCOM Control 1
	TFT_Send_Cmd(0xC5);		//(Contrast)
	TFT_Write_Data(0xFF);	//3.825
	TFT_Write_Data(0x00);	//-1.375
	//VCOM Control 1
	TFT_Send_Cmd(0xC5);		//(Contrast)
	TFT_Write_Data(0x00);	//3.825
	TFT_Write_Data(0x34);	//-1.375
	*/
	

    while(1)
    {	
	
    }
}
