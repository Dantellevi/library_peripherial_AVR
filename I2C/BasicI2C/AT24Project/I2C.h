
#ifndef I2C_H_
#define I2C_H_

#include "Main.h"


#define I2C_DDR		DDRC	// ���� ��� ������ �����������
#define I2C_PORT	PORTC	// ���� ��� ������ ������
#define I2C_PIN		PINC	// ���� ��� ����� ������

#define SCL			0		// ��� ����� SCL
#define SDA			1		// ��� ����� SDA

#define ONE_SCL()	{ I2C_DDR &= ~(1 << SCL); I2C_PORT |= (1 << SCL); }  // ��������� ������� �� ����� SCL
#define NULL_SCL()	{ I2C_DDR |= (1 << SCL);  I2C_PORT &= ~(1 << SCL); } // ��������� ���� �� ����� SCL
#define ONE_SDA()	{ I2C_DDR &= ~(1 << SDA); I2C_PORT |= (1 << SDA); }  // ��������� ������� �� ����� SDA
#define NULL_SDA()	{ I2C_DDR |= (1 << SDA);  I2C_PORT &= ~(1 << SDA); } // ��������� ���� �� ����� SDA


#define OK				0	// ����� � �����
#define SCL_FAIL		1	// ������ ����� SCL
#define SDA_FAIL		2	// ������ ����� SDA
#define SDA_SCL_FAIL	3	// ������ ����� SCL � SDA

#define WR				0   // ��� �� ������
#define RD				1	// ��� �� ������
#define NO				2	// ��� �� ���������

void I2CStart(void);
void I2CStop(void);
void I2C_Init(void);
void I2C_SendByte(uint8_t data);
void I2C_SendByteByADDR(uint8_t c,uint8_t addr);
uint8_t I2C_ReadByte(void);
uint8_t I2C_ReadLastByte(void);



#endif /* I2C_H_ */