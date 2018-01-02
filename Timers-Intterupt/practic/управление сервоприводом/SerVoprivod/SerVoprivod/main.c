
 #include "Main.h"

 extern unsigned char i;
 void Port_init(void)
 {
	DDRD&=~((1<<PD0)|(1<<PD2));
	PORTD|=(1<<PD0)|(1<<PD2);
	DDRB=0xFF;
	PORTB=0x00;
 }


int main(void)
{
	Port_init();
	Initilizer_Interrupt(FLAG_INT0,FLAG_LOW_LEVEL);
	PWM0_init(0,PWM_MODE_FIRST,FLAG_DEL_64);
	sei();
    /* Replace with your application code */
    while (1) 
    {
		SetPWM0_Value(i);

    }
}

