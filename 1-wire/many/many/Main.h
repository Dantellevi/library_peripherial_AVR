/*
 * Main.h
 *
 * Created: 26.02.2018 17:15:46
 *  Author: Dante_L_Levi
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "DS.h"
#include "USART.h"
#include "OneWire.h"
#include "delay.h"


#define TASCII(numb) (numb+48)

#define true 1
#define false 0

#define vuchar volatile unsigned char
#define vuint volatile unsigned int

#define sbi(reg,bit) reg |= (1<<bit)
#define cbi(reg,bit) reg &= ~(1<<bit)
#define ibi(reg,bit) reg ^= (1<<bit)
#define CheckBit(reg,bit) (reg&(1<<bit))

void RunTasks(void);



#endif /* MAIN_H_ */