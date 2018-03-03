#include "SPI.h"

void SPI_MasterInit(void)
{
	// Set MOSI and SCK output, all others input
	DDR_SPI |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS);
	PORTB |= (1<<SPI_MISO); // pull-up?
	
	SPCR = ((0<<SPIE)|(1<<SPE)|(0<<DORD)|(1<<MSTR)|(1<<CPOL)|(1<<CPHA)|(0<<SPR1)|(0<<SPR0));
	
	SPSR = (1<<SPI2X); // SPI double speed. Total spi speed=Fosc/2=12MHz/2=6MHz
}

unsigned char SPI_MasterTransmit(unsigned char cData)
{

	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
//			c=SPI_MasterTransmit(b>>16);
//			c=SPI_MasterTransmit(b>>8);
//			c=SPI_MasterTransmit(b);


void spi_flush( void )
{
	volatile uint8_t dummy;
	dummy = SPSR;    // clear status flags
	dummy = SPDR;    // flush receiver buffer
}
