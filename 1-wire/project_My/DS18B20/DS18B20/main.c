/*
 * DS18B20.c
 *
 * Created: 27.02.2018 12:38:55
 * Author : Dante_L_Levi
 */ 

#include "Main.h"



int main(void)
{
  Usart_Init(9600);
  Usart_PrintString("1-Wire\r\n");
    while (1) 
    {
	 start_meas();
	 _delay_ms(1000);
	 read_meas();
	 _delay_ms(1000);
    }
}

