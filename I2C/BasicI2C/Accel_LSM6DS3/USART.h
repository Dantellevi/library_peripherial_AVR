//---------------------------------------------<                                           >---------------------------
//---------------------------------------------<       Библиотека для работы с USART       >---------------------------
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
char Usart_str_in(char *str, char count);
void Usart_str_rn(char *str);
char usart_data(void);
void USart_Print(char *str);
void Usart_PrintString(char *str);
void Usart_int_out(int data);
void USART_TX(uint8_t *str1, uint8_t cnt);

//==============================================================

#endif /* USART_H_ */