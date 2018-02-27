
#ifndef I2C_H_
#define I2C_H_

#include "Main.h"


#define I2C_DDR		DDRC	// Порт для выбора направления
#define I2C_PORT	PORTC	// Порт для вывода данных
#define I2C_PIN		PINC	// Порт для ввода данных

#define SCL			0		// Пин порта SCL
#define SDA			1		// Пин порта SDA

#define ONE_SCL()	{ I2C_DDR &= ~(1 << SCL); I2C_PORT |= (1 << SCL); }  // Установка единицы на линии SCL
#define NULL_SCL()	{ I2C_DDR |= (1 << SCL);  I2C_PORT &= ~(1 << SCL); } // Установка нуля на линии SCL
#define ONE_SDA()	{ I2C_DDR &= ~(1 << SDA); I2C_PORT |= (1 << SDA); }  // Установка единицы на линии SDA
#define NULL_SDA()	{ I2C_DDR |= (1 << SDA);  I2C_PORT &= ~(1 << SDA); } // Установка нуля на линии SDA


#define OK				0	// Линия в норме
#define SCL_FAIL		1	// Ошибка линии SCL
#define SDA_FAIL		2	// Ошибка линии SDA
#define SDA_SCL_FAIL	3	// Ошибка линий SCL и SDA

#define WR				0   // Бит на запись
#define RD				1	// Бит на чтение
#define NO				2	// Бит не требуется

void I2CStart(void);
void I2CStop(void);
void I2C_Init(void);
void I2C_SendByte(uint8_t data);
void I2C_SendByteByADDR(uint8_t c,uint8_t addr);
uint8_t I2C_ReadByte(void);
uint8_t I2C_ReadLastByte(void);



#endif /* I2C_H_ */