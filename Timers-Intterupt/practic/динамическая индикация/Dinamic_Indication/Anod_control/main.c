
#include "Main.h"

void Port_init(void)
{
	DDRD=0xFF;
	PORTD=0x00;

	DDRC=0xFF;
	PORTC=0x00;


}


int main(void)
{
   Port_init();
   Timer_init();
   sei();

   ledprint(1234);

    while (1) 
    {
    }
}

