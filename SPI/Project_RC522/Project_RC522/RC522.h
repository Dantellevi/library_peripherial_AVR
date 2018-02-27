#ifndef RC522_H_
#define RC522_H_

#include "Main.h"
#include "SPI.h"

//--------MF522 command bits--------------------
#define PCD_IDLE 0x00 //отключение модуля; команда отмены
#define PCD_AUTHENT 0x0E //команда проверки пороля 
#define PCD_RECEIVE 0x08 //команда приема данных
#define PCD_TRANSMIT 0x04 //команда передачи данных
#define PCD_TRANSCEIVE 0x0C //команда на прием и передачу
#define PCD_RESETPHASE 0x0F //перезагрузка модуля
#define PCD_CALCCRC 0x03 //Команда CRC-контролля

//Mifare_One card command bits
#define PICC_REQIDL 0x26 //Поиск инидфикатора
#define PICC_REQALL 0x52 //поиск всех устройст подключенных ответов
#define PICC_ANTICOLL 0x93 //конфликт
#define PICC_SElECTTAG 0x93 //выбрать карту 
#define PICC_AUTHENT1A 0x60 //verify A password key
#define PICC_AUTHENT1B 0x61 //verify B password key
#define PICC_READ 0x30 //чтение
#define PICC_WRITE 0xA0 //запись
#define PICC_DECREMENT 0xC0 //уменьшиение значения
#define PICC_INCREMENT 0xC1 //увеличение значения
#define PICC_RESTORE 0xC2 //перезапись данных в буффере
#define PICC_TRANSFER 0xB0 //Сохранение данных в буффере
#define PICC_HALT 0x50 //спящий режим

//THe mistake code that return when communicate with MF522
#define MI_OK 0
#define MI_NOTAGERR 1
#define MI_ERR 2

#define pinSlaveSelect_OUTPUT	DDRB |= (1<<PB4);
#define pinSlaveSelect_LOW		PORTB &= ~(1<<PA4);
#define pinSlaveSelect_HIGH		PORTB |= (1<<PA4);

#define pinReset_OUTPUT	DDRA |= (1<<PA1);
#define pinReset_LOW		PORTA &= ~(1<<PA1);
#define pinReset_HIGH		PORTA |= (1<<PA1);




void Write_MFRC522(unsigned char addr,unsigned char val);
unsigned char Read_MFRC522(unsigned char addr);
void MFRC522_Reset(void);
void MFRC522_SetBitMask(unsigned char reg, unsigned char mask);
void MFRC522_AntennaOn(void);
void MFRC522_AntennaOff(void);
void MFRC522_ClearBitMask(unsigned char reg, unsigned char mask);
void MFRC522_CalulateCRC(unsigned char *pIndata, unsigned char len, unsigned char *pOutData);
unsigned char MFRC522_Auth(unsigned char authMode, unsigned char BlockAddr, unsigned char *Sectorkey, unsigned char *serNum);
unsigned char MFRC522_ToCard(unsigned char command, unsigned char *sendData, unsigned char sendLen,unsigned char *backData, unsigned int *backLen);
unsigned char MFRC522_Anticoll(unsigned char *serNum);
unsigned char MFRC522_SelectTag(unsigned char *serNum);
unsigned char MFRC522_Write(unsigned char blockAddr, unsigned char *writeData);
void MFRC522_Halt(void);
void MFCR522_Init(void);
unsigned char MFRC522_Request(unsigned char reqMode, unsigned char *TagType);


#endif /* RC522_H_ */