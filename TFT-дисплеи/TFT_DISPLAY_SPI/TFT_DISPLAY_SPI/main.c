#include "Main.h"



int main(void)
{
	Usart_Init(9600);
	ili9341_init();	
	lcdFillRGB(RED);
	//lcdDrawRectangle(20,20,30,30,MAGENTA);
	lcdDrawVLine(120,100, 50, CYAN);
	lcdDrawHLine(120,100, 50, YELLOW);
	lcdFillCircle(200,200,20,GREEN);
	TFT9341_String(10,17,RED,GREEN,"hello world!!!!",1);
    while (1) 
    {
		

		//for (uint8_t i=0;i<254;i++)
		//{
			//
			//spi_send_byte(i);
			//SPI_PORT&=~(1<<SPI_CS_BIT);
			//_delay_ms(1);
			//SPI_PORT|=(1<<SPI_CS_BIT);
			//
			//
			//_delay_ms(100);
		//}
    }
}

