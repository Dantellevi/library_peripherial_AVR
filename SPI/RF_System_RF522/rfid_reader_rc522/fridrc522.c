#include <stdio.h>
#include <util/delay.h>
#include "uart.h"

#include "MFRC522.h"

#define RXUBRR (F_CPU/16/9600)-1

#define BUFFER_SIZE 2
char buffer[BUFFER_SIZE];

int main( void )
{
	uchar card_num[5];
	uchar i;

	sei();

	uart_init(RXUBRR);
	MFRC522_Init();
	
	uart_puts("RC522 started\r\n");


	while(1) {
		_delay_ms(500);
		if ( MFRC522_Request( PICC_REQIDL, card_num ) == MI_OK ) {
			if ( MFRC522_Anticoll( card_num ) == MI_OK ) {
				uart_puts("Card number:\r\n");
				for (i = 0; i < 5; i++ ) {
					sprintf(buffer, "%x ", card_num[i]);
					uart_puts(buffer);
				}
				uart_puts("\r\n");
			}
		}
	}
}
