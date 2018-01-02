/*
 * usart.h
 *
 * Created: 15.12.2017 15:28:28
 *  Author: Dante_L_Levi
 */ 


#ifndef USART_H_
#define USART_H_

#include <inttypes.h>
#include "Main.h"

//Macros
#define RECEIVE_BUFF_SIZE 64
#define USART_RXC_VECT USART_RXC_vect

//Varriables
volatile char URBuff[RECEIVE_BUFF_SIZE];	//USART Receive Buffer
volatile int8_t UQFront;
volatile int8_t UQEnd;


void Usart_Init(long int baudrate);
void Usart_Transmit_SendChar(char data);
char USART_ReadData(void);
uint8_t UDataAvailable(void);
void Usart_int_Transmit(int data);
void UFlushBuffer(void);
void UReadBuffer(void *buff,uint16_t len);
void USART_WriteString(char *str);





#endif /* USART_H_ */