/*
 * SIM300.h
 *
 * Created: 15.12.2017 16:06:47
 *  Author: Dante_L_Levi
 */ 


#ifndef SIM300_H_
#define SIM300_H_


#include <inttypes.h>
#include "Main.h"
#include "lcd.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



//Error List
#define SIM300_OK					 1
#define SIM300_INVALID_RESPONSE		-1
#define SIM300_FAIL					-2
#define SIM300_TIMEOUT				-3

//Status
#define SIM300_NW_REGISTERED_HOME	1
#define SIM300_NW_SEARCHING			2
#define SIM300_NW_REGISTED_ROAMING	5
#define SIM300_NW_ERROR				99

#define SIM300_SIM_PRESENT			1
#define SIM300_SIM_NOT_PRESENT		0


#define  SIM300_SendMessage_OK 1
#define  SIM300_SendMessage_ERROR 0



int8_t SIM300Init(void);	//������������� SIM300
int8_t SIM300Cmd(char *cmd);	//�������� ������� �� ������
int8_t SIM300CheckResponse(const char *response,const char *check,uint8_t len);
int8_t SIM300WaitForResponse(uint16_t timeout);
int8_t SIM300GetNetStat(void);
int8_t SIM300IsSIMInserted();
uint8_t SIM300GetProviderName(char *name);
int8_t SIM300GetIMEI(char *emei);
int8_t SIM300GetManufacturer(char *man_id);
int8_t	SIM300GetModel(char *model);
void Clear_Usart_Buffer(void);//������� �������
unsigned char Send_SMS(char* massage,char* NumberPhone);

void Recieve_SMS(char* Buffer);



#endif /* SIM300_H_ */