#include "DS18b20.h"

unsigned int temp;


#define PLUS 1
#define  MINUS 0
unsigned char ZNAK=PLUS;





void start_meas( void ){
	if( W1_IN & 1<< W1_PIN ){
		w1_command( CONVERT_T, NULL );
		W1_OUT |= 1<< W1_PIN;
		W1_DDR |= 1<< W1_PIN;			// parasite power on

		}else{
		Usart_PrintString( "Short Circuit !\r\n" );
	}
}



void read_meas( void )
{
	unsigned char id[8], diff;
	char s[30];
	unsigned char byte[2];
	unsigned char i;
	

	for( diff = SEARCH_FIRST; diff != LAST_DEVICE; ){
		diff = w1_rom_search( diff, id );

		if( diff == PRESENCE_ERR ){
			Usart_PrintString( "No Sensor found\r\n" );
			break;
		}
		if( diff == DATA_ERR ){
			Usart_PrintString( "Bus Error\r\n" );
			break;
		}
		if( id[0] == 0x28 || id[0] == 0x10 ){	// temperature sensor
			Usart_PrintString( "ID: " );
			for( i = 0; i < 8; i++ ){
				sprintf(s, "%02X ", id[i] );
				Usart_PrintString(s);
			}
			w1_byte_wr( READ );			// read command
			
			
			temp = w1_byte_rd();			// low byte
			temp |= (unsigned int)w1_byte_rd() << 8;		// high byte
			byte[0]=temp>>8;		//старшая часть
			if (byte[0]&0x80)
			{
				temp=~temp;
				temp+=1;
				ZNAK=MINUS;
			}
			else
			{
				ZNAK=PLUS;
			}
			switch(ZNAK)
			{
				case PLUS:
				{
					if( id[0] == 0x10 )			// 9 -> 12 bit
					temp <<= 3;
					sprintf( s, "  T: %04X = ", temp );	// hex value
					Usart_PrintString(s);
					sprintf( s, "Tcels=%4d.%01dшC\r\n", temp >> 4, (temp << 12) / 6553 ); // 0.1шC
					Usart_PrintString(s );
					break;
				}
				case MINUS:
				{
					if( id[0] == 0x10 )			// 9 -> 12 bit
					temp <<= 3;
					sprintf( s, "  T: %04X = ", temp );	// hex value
					Usart_PrintString(s);
					sprintf( s, "Tcels=-%4d.%01dшC\r\n", temp >> 4, (temp << 12) / 6553 ); // 0.1шC
					Usart_PrintString(s );
					break;
				}
			}
			
			
			
			
			
			
			
			
		}
	}
	Usart_PrintString( "" );
}

