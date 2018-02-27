
#ifndef SPI_H_
#define SPI_H_

#include "Main.h"


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






void SPI_Master_Init(char flagMode,char del);
void SPi_Transmit_data(uint8_t data);
void SPI_SendByte(char byte);
void SPI_INICILIZER(void);
unsigned char SPI_CHangeByte(char byte);


#endif /* SPI_H_ */