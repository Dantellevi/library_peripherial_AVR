/*
 * Project_Ds18b20_ILI9341.c
 *
 * Created: 26.02.2018 15:18:19
 * Author : Dante_L_Levi
 */ 

#include "Main.h"


uint16_t MAX_X=0, MAX_Y = 0;
uint32_t SysTimer;

int main(void)
{
	uint32_t x, y;
	Usart_Init(9600);
	Usart_PrintString("1-Wire\r\n");
	InitTFT();
	TFTPoint p[13];
    //Init_ILI9341(3);
	//TFT_Fill_Screen(0, MAX_X, 0, MAX_Y, BLACK);
	//TFT_Fill_Screen(0, MAX_X, 0, MAX_Y, YELLOW);
	x = 0;
    while (1) 
    {
		TFTSetOrientation(x);


		 p[0].x = 10;  p[0].y = 10;
		 p[1].x = 40;  p[1].y = 17;
		 p[2].x = 100;  p[2].y = 60;
		 p[3].x = 60;  p[3].y = 120;
		 p[4].x = 200;  p[4].y = 90;
		 p[5].x = 150;  p[5].y = 170;
		 p[6].x = 80;  p[6].y = 40;
		 TFTFillPoly((TFTPointPtr)&p, 7, 0, Cyan);
		_delay_ms(500);
		//start_meas();
		//_delay_ms(1000);
		//read_meas();
		//_delay_ms(1000);
		//TFT_Read_Id();
		//TFT_Fill_Screen(0, MAX_X, 0, MAX_Y, YELLOW);
		//_delay_ms(1000);
		
		//_delay_ms(1000);
		//TFT_Read_Id();
		//_delay_ms(1000);
    }
}

