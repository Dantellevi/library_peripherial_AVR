/*
 * Main.h
 *
 * Created: 30.11.2017 15:34:41
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
#include "InitilizeTimer.h"
#include "Interrupt.h"
#include "MatrixKeyBoard.h"
#include "lcd.h"
void pause(unsigned int a);


#endif /* MAIN_H_ */