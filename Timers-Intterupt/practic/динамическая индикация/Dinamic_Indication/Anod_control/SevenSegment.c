#include "SevenSegment.h"

unsigned int i;
//под цифры каждого разряда потребуются также переменные
unsigned R1=0,R2=0,R3=0,R4=0;

unsigned char n_count=0;	//счетчик для прохода по порядкам числа и зажигания соответствующего порядка

ISR(TIMER1_COMPA_vect)
{
	
	if (n_count==0)
	{
		PORTC&=~(1<<PC0);
		PORTC|=(1<<PC1);
		PORTC|=(1<<PC2);
		PORTC|=(1<<PC3);
		segchar(R1);

	}
	else if (n_count==1)
	{
		PORTC|=(1<<PC0);
		PORTC&=~(1<<PC1);
		PORTC|=(1<<PC2);
		PORTC|=(1<<PC3);
		segchar(R2);
	}
	else if (n_count==2)
	{
		PORTC|=(1<<PC0);
		PORTC|=(1<<PC1);
		PORTC&=~(1<<PC2);
		PORTC|=(1<<PC3);
		segchar(R3);
	}
	else if (n_count==3)
	{
		PORTC|=(1<<PC0);
		PORTC|=(1<<PC1);
		PORTC|=(1<<PC2);
		PORTC&=~(1<<PC3);
		segchar(R4);
	}
	n_count++;
	if (n_count>3)
	{
		n_count=0;
	}

}

void segchar (unsigned char seg)
{
	switch(seg)
	{
		case 1: PORTD = 0b11111001; break;
		case 2: PORTD = 0b10100100; break;
		case 3: PORTD = 0b10110000; break;
		case 4: PORTD = 0b10011001; break;
		case 5: PORTD = 0b10010010; break;
		case 6: PORTD = 0b10000010; break;
		case 7: PORTD = 0b11111000; break;
		case 8: PORTD = 0b10000000; break;
		case 9: PORTD = 0b10010000; break;
		case 0: PORTD = 0b11000000; break;
	}
}

void ledprint(unsigned int number)
{
//разбиваем число на разряды пример: 1234
	 R1 = number%10;		//4
	 R2 = number%100/10;	//3
	 R3 = number%1000/100;	//2
	 R4 = number/1000;		//1
 }



void Timer_init(void)
{	
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK |= (1<<OCIE1A);	//устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	OCR1AH = 0b00100000; //записываем в регистр число для сравнения
	OCR1AL = 0b11101101;
	TCCR1B |= (1<<CS11);//установим делитель.
	
}





