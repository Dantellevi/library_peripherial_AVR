/*
 * HC-05.c
 *
 * Created: 13.12.2017 13:25:49
 * Author : Dante_L_Levi
 */ 

 #include "Main.h"

 void Port_init(void)
 {
	DDRA=0xFF;
	PORTA=0x00;
 }


int main(void)
{
	int s;
	char buf[20];

	Port_init();
	LCDinit();
	LCDstringXY("Hello Sania",0,1);
	Usart_Init(9600);
    
	sei();

    while (1) 
    {
		 //Usart_str_rn("Hello world!!!");
		 s=Usart_str_in(buf,10);
		 LCDputsIntGotoXY(s,1,2);
		 //
		 //
		 LCDstringXY(buf,1,3);
		 //
		 _delay_ms(500);
    }
}

