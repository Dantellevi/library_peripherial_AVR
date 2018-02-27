/*
 * EEPROMAT24.h
 *
 * Created: 01.02.2018 15:27:39
 *  Author: Dante_L_Levi
 */ 


#ifndef EEPROMAT24_H_
#define EEPROMAT24_H_


#include "Main.h"

#define TW_MT_DATA_ASK 0x28	//ведущий передал данные и ведомый подтвердил прием
#define TW_MR_DATA_ASK 0x50 //Ведущий приял данные и передал подтверждение
#define  TW_MR_DATA_NASK 0x58	//Ведущий передал данные и ведомый подтвердил прием




int EE_WriteByte(unsigned char c);
unsigned char EE_ReadByte(void);
unsigned char EE_ReadLastByte(void);


#endif /* EEPROMAT24_H_ */