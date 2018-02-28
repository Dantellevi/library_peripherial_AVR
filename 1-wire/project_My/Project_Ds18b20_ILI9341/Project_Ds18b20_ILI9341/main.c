/*
 * Project_Ds18b20_ILI9341.c
 *
 * Created: 26.02.2018 15:18:19
 * Author : Dante_L_Levi
 */ 

#include "Main.h"


uint16_t MAX_X=0, MAX_Y = 0;

int main(void)
{
	Usart_Init(9600);
	Usart_PrintString("1-Wire\r\n");
    Init_ILI9341(3);
	//TFT_Fill_Screen(0, MAX_X, 0, MAX_Y, BLACK);
	//TFT_Fill_Screen(0, MAX_X, 0, MAX_Y, YELLOW);
    while (1) 
    {
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

