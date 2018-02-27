/*
 * SPI.h
 *
 * Created: 16.01.2018 15:58:23
 *  Author: Dante_L_Levi
 */ 


#ifndef SPI_H_
#define SPI_H_


#include "Main.h"


#define MOSI 5
#define MISO 6
#define SCK  7
#define SS   4


void port_ini(void);
void SPI_SendByte (unsigned char byte);
unsigned char SPI_ReceiveByte(void);
unsigned char SD_cmd(char dt0,char dt1,char dt2,char dt3,char dt4,char dt5);
unsigned char SD_Init(void);
unsigned char SD_Write_Block (char* bf, unsigned char dt1, unsigned char dt2, unsigned char dt3, unsigned char dt4);
unsigned char SD_Read_Block (char* bf, unsigned char dt1, unsigned char dt2, unsigned char dt3, unsigned char dt4);




#endif /* SPI_H_ */