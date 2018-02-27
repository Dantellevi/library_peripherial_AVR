

#include "Main.h"



int main(void)
{
    Usart_Init(9600);
	Usart_str_rn("Hello World");

    while (1) 
    {
	Usart_str_rn("Hello World");
	_delay_ms(600);
    }
}

