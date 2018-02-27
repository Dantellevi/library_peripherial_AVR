#ifndef EEPROMEXT_H_
#define EEPROMEXT_H_

#include "main.h"

#define TW_MT_DATA_ASK 0x28 // Ведущий передал данные и ведомый подтвердил прием
#define TW_MR_DATA_ASK 0x50 // Ведущий принял данные и передал подтверждение
#define TW_MR_DATA_NASK 0x58 // Ведущий передал данные и ведомый подтвердил прием

int EE_WriteByte(unsigned char c);
unsigned char EE_ReadByte(void);
unsigned char EE_ReadLastByte(void);

#endif /* EEPROMEXT_H_ */