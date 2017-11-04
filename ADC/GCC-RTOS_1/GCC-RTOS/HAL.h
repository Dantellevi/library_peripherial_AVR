#ifndef HAL_H
#define HAL_H


//Clock Config
#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avrlibtypes.h>
#include <avrlibdefs.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdlib.h>

#define INLINE __attribute__((always_inline))




//System Timer Config
#define Prescaler	  		64
#define	TimerDivider  		(F_CPU/Prescaler/1000)		// 1 mS


//USART Config
#define baudrate 9600L
#define bauddivider (F_CPU/(16*baudrate)-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)


//PORT Defines
#define LED1 		4
#define LED2		5
#define	LED3		7

#define I_C			3
#define I_L			6
#define LED_PORT 	PORTD
#define LED_DDR		DDRD

#define SEND(X) do{buffer_index = 1; UDR = X; UCSRB|=(1<<UDRIE); }while(0)

extern void InitAll(void);



#endif
