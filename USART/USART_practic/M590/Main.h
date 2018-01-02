/*
 * Main.h
 *
 * Created: 20.12.2017 14:47:23
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



#include "lcd.h"
#include "usart.h"
#include "M590.h"




#define SPEED_BAUD 9600


//=======================ћоды дл€ статуса M590============

/*
0 Ц выключить уведомление о регистрации в сети
1 Ц  включить уведомление о регистрации в сети +CREG: <stat>
2 Ц включить уведомление о регистрации в сети и информацию о местоположении
*/
#define MODE_MESS_OFF '0'
#define MODE_MESS_ON '1'
#define MODE_MESS_ON_GPRS '2'
//=============================================================




#endif /* MAIN_H_ */