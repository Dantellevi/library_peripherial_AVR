/*
 * Main.h
 *
 * Created: 27.11.2017 15:01:08
 *  Author: Dante_L_Levi
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>


#include "lcd.h"
#include "InitilizeTimer.h"

void pause(unsigned int a);


#endif /* MAIN_H_ */