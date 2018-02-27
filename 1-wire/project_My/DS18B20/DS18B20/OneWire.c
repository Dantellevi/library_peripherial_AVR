#include "oneWire.h"

unsigned char w1_reset(void)
{
	unsigned char err;
	W1_OUT &= ~(1<<W1_PIN);
	W1_DDR |= 1<<W1_PIN;
	_delay_us(480);
	W1_DDR &= ~(1<<W1_PIN);
	_delay_us(66);
	err = W1_IN & (1<<W1_PIN);
	_delay_us(480-66);
	if( (W1_IN & (1<<W1_PIN)) == 0 )		// short circuit
	err = 1;
	return err;
}

unsigned char w1_bit_io( unsigned char b )
{
	
	W1_DDR |= 1<<W1_PIN;
	_delay_us(1);
	if( b )
	W1_DDR &= ~(1<<W1_PIN);
	_delay_us(14);
	if( (W1_IN & (1<<W1_PIN)) == 0 )
	b = 0;
	_delay_us(45);
	W1_DDR &= ~(1<<W1_PIN);
	
	return b;
}


unsigned int w1_byte_wr( unsigned char b )
{
	unsigned char i = 8, j;
	do{
		j = w1_bit_io( b & 1 );
		b >>= 1;
		if( j )
		b |= 0x80;
	}while( --i );
	return b;
}

unsigned int w1_byte_rd( void )
{
	return w1_byte_wr( 0xFF );
}


unsigned char w1_rom_search( unsigned char diff, unsigned char *id )
{
	unsigned char i, j, next_diff;
	unsigned char b;

	if( w1_reset() )
	return PRESENCE_ERR;			// error, no device found
	w1_byte_wr( SEARCH_ROM );			// ROM search command
	next_diff = LAST_DEVICE;			// unchanged on last device
	i = 8 * 8;					// 8 bytes
	do{
		j = 8;					// 8 bits
		do{
			b = w1_bit_io( 1 );			// read bit
			if( w1_bit_io( 1 ) ){			// read complement bit
				if( b )					// 11
				return DATA_ERR;			// data error
				}else{
				if( !b ){				// 00 = 2 devices
					if( diff > i ||
					((*id & 1) && diff != i) ){
						b = 1;				// now 1
						next_diff = i;			// next pass 0
					}
				}
			}
			w1_bit_io( b );     			// write bit
			*id >>= 1;
			if( b )					// store bit
			*id |= 0x80;
			i--;
		}while( --j );
		id++;					// next byte
	}while( i );
	return next_diff;				// to continue search
}




void w1_command( unsigned char command, unsigned char *id )
{
	unsigned char i;
	w1_reset();
	if( id ){
		w1_byte_wr( MATCH_ROM );			// to a single device
		i = 8;
		do{
			w1_byte_wr( *id );
			id++;
		}while( --i );
		}else{
		w1_byte_wr( SKIP_ROM );			// to all devices
	}
	w1_byte_wr( command );
}














