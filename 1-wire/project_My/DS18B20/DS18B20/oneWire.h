/*
 * oneWire.h
 *
 * Created: 27.02.2018 12:41:51
 *  Author: Dante_L_Levi
 */ 


#ifndef ONEWIRE_H_
#define ONEWIRE_H_


#include "Main.h"

#define MATCH_ROM	0x55
#define SKIP_ROM	0xCC
#define	SEARCH_ROM	0xF0

#define CONVERT_T	0x44		// DS1820 commands
#define READ		0xBE
#define WRITE		0x4E
#define EE_WRITE	0x48
#define EE_RECALL	0xB8

#define	SEARCH_FIRST	0xFF		// start new search
#define	PRESENCE_ERR	0xFF
#define	DATA_ERR	0xFE
#define LAST_DEVICE	0x00		// last device found
//			0x01 ... 0x40: continue searching

#ifndef W1_PIN
#define W1_PIN	PB0
#define W1_IN	PINB
#define W1_OUT	PORTB
#define W1_DDR	DDRB
#endif


unsigned char w1_reset(void);

unsigned int w1_byte_wr( unsigned char b );
unsigned int w1_byte_rd( void );

unsigned char w1_rom_search( unsigned char diff, unsigned char *id );

void w1_command(  unsigned char command, unsigned char *id );


#endif /* ONEWIRE_H_ */