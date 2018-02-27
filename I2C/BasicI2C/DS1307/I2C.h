
#ifndef I2C_H_
#define I2C_H_


#include "Main.h"

void I2C_Init(void);
void Start_I2C(void);
void Stop_I2C(void);
void I2C_SendByte(unsigned char data);
void I2C_SendByteAddR(unsigned char data,unsigned char addr);
unsigned char I2C_ReadByte(void);
unsigned char I2C_ReadLastByte(void);




#endif /* I2C_H_ */