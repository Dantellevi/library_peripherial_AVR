#include "TIMBASE.h"

unsigned char prescaler;
unsigned char volatile second;			// count seconds



void init_timer( void )
{
	TCCR1B = 1<<CS10;			// divide by 1
	OCR1A = 0;
	TCNT1 = -1;
	second = 0;
	prescaler = 0;

	TIMSK = 1<<OCIE1A;
}