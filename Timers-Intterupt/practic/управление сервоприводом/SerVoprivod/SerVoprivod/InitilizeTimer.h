/*
 * InitilizeTimer.h
 *
 * Created: 09.11.2017 11:41:50
 *  Author: Dante_L_Levi
 */ 


#ifndef INITILIZETIMER_H_
#define INITILIZETIMER_H_


#include "Main.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>


#define NORMAL_MODE 1
#define CTC_MODE 2

#define CTC_OCR1A 1
#define CTC_ICR1A 2


#define PWM_MODE_FIRST 1
#define  PWM_MODE_PHASECORRECT 2
#define  PWM_MODE_PHASEFREQCORRECT 3


#define  FLAG_8BIT 8
#define  FLAG_9BIT 9
#define  FLAG_10BIT 10

#define FLAG_DEL_NONE 0
#define FLAG_DEL_0 1
#define FLAG_DEL_8 2
#define FLAG_DEL_64 3
#define FLAG_DEL_256 4
#define FLAG_DEL_1024 5
#define FLAG_DEL_extern 6
#define FLAG_DEL_128 7
#define FLAG_DEL_32 8


#define FLAG_CH_OCR1A 0
#define FLAG_CH_OCR1B 1
#define FLAG_CH_ICR1 2




void Timer0_init(char starVal,char flagMode, char freq,char flagDel );		//функция инициализации таймера Timer/counter0
void Timer2_init_normalMode(int starVal,char flagMode,char freq,char flagDel);	//функция инициализации таймера Timer/counter2
void Timer_init_16bit(unsigned int starVal,char flagMode,char flagCTC, unsigned int freq,char flagDel);	//функция инициализации Timer/Counter1
//------------------------------------------------------------------------------------------------------------------------
void PWM0_init(char starVal,char Mode,char flagdel);						//Функция инициализации ШИМ Timer/Counter0
void SetPWM0_Value(char value);												//Функция установки значений в ШИМ Timer/Counter0
//-------------------------------------------------------------------------------------------------------------------------
void PWM2_init(char starVal,char Mode,char flagdel);						//Функция инициализации ШИМ Timer/Counter2
void SetPWM2_Value(char value);												//Функция установки значений в ШИМ Timer/Counter2
//--------------------------------------------------------------------------------------------------------------------------

void PWM1_init(int starVal,char flagBits,char Mode,char flagdel,char channel);


#endif /* INITILIZETIMER_H_ */