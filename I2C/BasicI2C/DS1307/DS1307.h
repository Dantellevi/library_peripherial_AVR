/*
 * DS1307.h
 *
 * Created: 07.02.2018 15:20:19
 *  Author: Dante_L_Levi
 */ 


#ifndef DS1307_H_
#define DS1307_H_


#include "I2C.h"



unsigned char RTC_ConvertFromBinDec(unsigned char c);
unsigned char RTC_ConvertFromDec(unsigned char c);


#endif /* DS1307_H_ */