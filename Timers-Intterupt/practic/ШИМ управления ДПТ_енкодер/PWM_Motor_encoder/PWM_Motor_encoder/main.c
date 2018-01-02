#include "Main.h"

#define IN1_ON PORTD|=(1<<PD7)
#define IN1_OFF PORTD&=~(1<<PD7)

#define IN2_ON PORTD|=(1<<PD6)
#define IN2_OFF PORTD&=~(1<<PD6)

void Port_Init(void)
{

	DDRB|=(1<<PB3);
	PORTB&=~(1<<PB3);

	DDRD|=(1<<PD7)|(1<<PD6);
	PORTD&=~((1<<PD7)|(1<<PD6));
	DDRD&=~(1<<PD0);
	PORTD&=~(1<<PD0);
	DDRD|=(1<<PD1);
	PORTD&=~(1<<PD1);


}

int main(void)
{
   Port_Init();
   PWM0_init(10,PWM_MODE_FIRST,FLAG_DEL_1024);
   Initilizer_Interrupt(FLAG_INT0,FLAG_LOW_LEVEL);
   IN1_ON;
   sei();
    while (1) 
    {
	
    }
}

