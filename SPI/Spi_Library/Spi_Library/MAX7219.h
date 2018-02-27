/*
 * MAX7219.h
 *
 * Created: 09.01.2018 15:33:26
 *  Author: Dante_L_Levi
 */ 


#ifndef MAX7219_H_
#define MAX7219_H_


#include "Main.h"


void Send_MAX7219(char reg,char data);
void Clear_7219(char dg);
void Number_MAX7219(volatile long n);

#endif /* MAX7219_H_ */