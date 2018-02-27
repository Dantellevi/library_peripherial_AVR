#include "Main.h"


int main(void)
{
	char buffer[25];
	I2C_Init();
	Usart_Init(9600);

    
    while (1) 
    {
		ds3231_read_time(buffer);
		Usart_PrintString("Time= ");
		Usart_PrintString(buffer);
		Usart_PrintString("\r\n");
		_delay_ms(500);

    }
}

