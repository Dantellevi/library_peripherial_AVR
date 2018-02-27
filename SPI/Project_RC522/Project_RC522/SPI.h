/*
 * SPI.h
 *
 * Created: 23.01.2018 16:33:53
 *  Author: Dante_L_Levi
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "Main.h"


#define SPI_DDR DDRB
#define SPI_MOSI_BIT PB5
#define SPI_SCK_BIT PB7
#define SPI_CS_BIT PB4
#define SPI_PORT PORTB




#define DDR_SPI DDRB
#define PORT_SPI PORTB

#define DD_MOSI PB5
#define DD_SCK	PB7
#define DD_SS	PB4
#define MISO    PB6
//------------------------------------------


#define MASTER	1
#define SLAVE	0


#define DEL_16		0
#define DEL_128		1
#define DEL_64		2

//void spi_init(uint8_t setup);
void SPI_Master_Init(char flagMode,char del);
void spi_send_byte(uint8_t data);
void SPI_SendByte(char byte);
uint8_t spi_read_byte(void);


#endif /* SPI_H_ */