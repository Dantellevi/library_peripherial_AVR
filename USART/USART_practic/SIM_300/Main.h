/*
 * Main.h
 *
 * Created: 15.12.2017 9:54:44
 *  Author: Dante_L_Levi
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usart.h"
#include "lcd.h"
#include "SIM300.h"


#define Usart_baud 9600


#endif /* MAIN_H_ */