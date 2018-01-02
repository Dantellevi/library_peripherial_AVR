/*
 * hc05.h
 *
 * Created: 13.12.2017 15:21:06
 *  Author: Dante_L_Levi
 */ 


#ifndef HC05_H_
#define HC05_H_

#include "Main.h"
#include <string.h>
#include "USART.h"
#include "CicleBuffer.h"

#define AT_com		"AT\r\n"			//Проверочная команда если модуль возращает ОК то он готов к обмену  данными
#define AT_RES		"AT+RESET\r\n"	//Сброс модуля
#define AT_Version  "AT+VERSION?\r\n"	//Команда проверки прошивки модуля
#define AT_Origin	"AT+ORGL\r\n"			//Вернуть стандартные настройки модуля
#define AT_Name_Get "AT+NAME?\r\n"		//получить текущее имя модуля
#define AT_Name_Set "AT+NAME="		//установить имя модуля
#define AT_ROLE_Get "AT+ROLE?\r\n"		//получить текущую роль (Master,Slave)
#define AT_ROLE_Set "AT+ROLE="		//установить текущую роль
#define AT_PSWD_Get "AT+PSWD?\r\n"		//получить текущий пороль модуля
#define AT_PSWD_set	"AT+PSWD="	//установить текущий пороль
#define AT_STATE	"AT+STATE?\r\n"		//узнать статус работы модуля

#define OK 1
#define ERROR 0





char ckeckState(void);
void ResetHC05(void);
void SetOrigin(void);
char Version_Get(char *str);
char ROLE_Get(char *str);
char Role_Set(char *str,char *strResponse);
char Name_Get(char *str);
void Name_Set(char *str);
void Password_Set(char *str);
char Password_Get(char *str,int count);



#endif /* HC05_H_ */