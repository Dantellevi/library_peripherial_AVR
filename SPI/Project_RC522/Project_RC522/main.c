
#include "Main.h"

char buffer[BUFFER_SIZE];


int main(void)
{
	unsigned char card_num[5];
	unsigned char i;
   //lcd_init(0);
   Usart_Init(9600);
   sei();
   SPI_Master_Init(MASTER,DEL_16);
   
	MFCR522_Init();
	Usart_PrintString("RC522 started\r\n");

    while (1) 
    {
	//for (char i=0;i<255;i++)
	//{
		//SPI_SendByte(i);
		//SPI_PORT&=~(1<<SPI_CS_BIT);
//
		//SPI_PORT|=(1<<SPI_CS_BIT);
		//_delay_ms(500);
	//}
	
	
		//Usart_str_rn("hrllo");
		//Usart_PrintString("Transmit\r\n");
		_delay_ms(500);
		if ( MFRC522_Request( PICC_REQIDL, card_num ) == MI_OK )
		{
			if ( MFRC522_Anticoll( card_num ) == MI_OK )
			{
				Usart_PrintString("Card number:\r\n");
				for (i=0;i<5;i++)
				{
					sprintf(buffer,"%x",card_num[i]);
					Usart_PrintString(buffer);
				}
				Usart_PrintString("\r\n");

			}
		}
    }
}

