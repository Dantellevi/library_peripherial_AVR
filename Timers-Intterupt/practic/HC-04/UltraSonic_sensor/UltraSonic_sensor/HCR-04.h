/*
 * HCR_04.h
 *
 * Created: 11.12.2017 12:34:16
 *  Author: Dante_L_Levi
 */ 


#ifndef HCR_04_H_
#define HCR_04_H_

#include "Main.h"


//Определение ножки Echo
#define Echo_PORT PORTD
#define Echo_DDR DDRD
#define Echo_PIN PIND
#define EchoNPin PD2


//Определение ножки Trig
#define Trig_PORT PORTD
#define Trig_DDR  DDRD
#define Trig_PIN  PIND
#define Trig_NPin PD0

//Конфигурация прерывания для датчика
#define  FLAG_INT0 0
#define  FLAG_INT1 1


#define flag_start 1
#define flag_stop 0



void HC_SRC04_Init(void);	//Инициализация ультразвукового датчика расстояния
void HC_SRC04_Strop(void);	//Запуск датчика(стробирующий сигнал)
void Init_Interruot_HC04(unsigned char flag);	//Инициализация  прерываний
unsigned int Convert_CM( int N_t);	//функция конвертации значени из импльсов в СМ
unsigned int GetValueHSR04(void);			//Возращаем значение 
void timer_Start_Stop(char flag);//запуск и остановка таймера(подсчет тактов)



#endif /* HCR_04_H_ */