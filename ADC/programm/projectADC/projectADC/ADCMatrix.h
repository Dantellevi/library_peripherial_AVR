#ifndef ADCMATRIX_H_
#define ADCMATRIX_H_


#include "Main.h"
#include "ADClib.h"
#include "lcd.h"
#include <stdlib.h>
#include <stdio.h>

#define SIZE_PASSWORD 3		//размер вводимого пороля

#define FLAG_OK	1			//флаг  успешной проверки
#define FLAG_ERROR	0		//флаг ошибки ввода пороля

 uint8_t GetValueKey_Board(unsigned char channel);	//фунция получение символа с АЦП клавиатуры
 uint8_t password_confird(unsigned char channel);	//фунция проверки вводимого пороля

#endif /* ADCMATRIX_H_ */