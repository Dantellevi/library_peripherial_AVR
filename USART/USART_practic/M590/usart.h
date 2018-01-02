/*
 * usart.h
 *
 * Created: 15.12.2017 15:28:28
 *  Author: Dante_L_Levi
 */ 


#ifndef USART_H_
#define USART_H_

#include "Main.h"
#include "CicleBuffer.h"
//-------------------------------------------------------------------------
//						Объявление служебных псевдонимов
//-------------------------------------------------------------------------

#define RXCIE_ON	(UCSRB |= (1 << RXCIE))
#define RXCIE_OFF	(UCSRB &= ~(1 << RXCIE))
#define TXCIE_ON	(UCSRB |= (1 << TXCIE))
#define TXCIE_OFF	(UCSRB |= ~(1 << TXCIE))

//-------------------------------------------------------------------------
//							Подключаемые библиотеки
//-------------------------------------------------------------------------
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



//======================<Прототипы функций>=====================

void Usart_Init(long int baudrate);
void Usart_char_out(char data);
void Usart_str_out(char *str,char count);
void Usart_MutBUS_out(char *str);
int Usart_str_in(char *str, char count);
void Usart_str_transmit(char *str);
char usart_data(void);
char Usart_char_in(void);
void Usart_int_out(int data);

//==============================================================





#endif /* USART_H_ */