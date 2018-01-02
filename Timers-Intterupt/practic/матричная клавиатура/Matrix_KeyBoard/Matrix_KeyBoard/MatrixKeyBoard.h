
#ifndef MATRIXKEYBOARD_H_
#define MATRIXKEYBOARD_H_

#include "Main.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>


#define PASSWORD_OK 1
#define PASSWORD_ERROR 2



/*
		конфигурации по портам:
		PC4,PC5,PC6-столбцы
		PC0,PC1,PC2,PC3-строки

*/

unsigned char GetMatrixValue(void);		//функция возращает значение с матричной клавиатуры
void Password_Print_Confim(void);		//проверка пороля и вывод подтверждения

#endif /* MATRIXKEYBOARD_H_ */