#include <HAL.h>

inline void InitAll(void)
{

//InitUSART
UBRRL = LO(bauddivider);
UBRRH = HI(bauddivider);
UCSRA = 0;
UCSRB = 1<<RXEN|1<<TXEN|0<<RXCIE|0<<TXCIE|0<<UDRIE;
UCSRC = 1<<URSEL|1<<UCSZ0|1<<UCSZ1;

//InitPort
//LED_DDR |= 1<<LED1|1<<LED2|1<<LED3;
//DDRB |= 1<<PB3;

//Init ADC
//ADMUX = 1<<REFS0|1<<ADLAR|0<<MUX0;



//Init PWM
//TCCR0 = 1<<WGM00|3<<COM00|1<<WGM01|1<<CS00;

//Init Interrupts
MCUCR |= 1<<ISC00|1<<ISC01;
GICR |= 1<<INT0;
}
