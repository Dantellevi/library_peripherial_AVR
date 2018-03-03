#ifndef spi_h 
#define spi_h 

#include <avr/io.h> 
#define DDR_SPI	DDRB




// create alias for the different SPI chip pins - code assumes all on port B 
#if (defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__)) 
#define SPI_SS PORTB0 
#define SPI_SCK PORTB1 
#define SPI_MOSI PORTB2 
#define SPI_MISO PORTB3 
#elif (defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)) 
#define SPI_SS PORTB2 
#define SPI_SCK PORTB5 
#define SPI_MOSI PORTB3 
#define SPI_MISO PORTB4
#elif (defined(__AVR_ATmega16__))

#define SPI_SS PORTB4
#define SPI_SCK	PORTB7
#define SPI_MOSI	PORTB5
#define SPI_MISO PORTB6


#elif defined(__AVR_ATmega324PA__)
#define SPI_SS		PORTB4
#define SPI_SCK		PORTB7
#define SPI_MOSI	PORTB5
#define SPI_MISO	PORTB6

#define SPCR _SFR_IO8(0x2C)
#define SPR0 0
#define SPR1 1
#define CPHA 2
#define CPOL 3
#define MSTR 4
#define DORD 5
#define SPE 6
#define SPIE 7

#define SPSR _SFR_IO8(0x2D)
#define SPI2X 0
#define WCOL 6
#define SPIF 7


#define SPDR _SFR_IO8(0x2E)
#define SPDR0 0
#define SPDR1 1
#define SPDR2 2
#define SPDR3 3
#define SPDR4 4
#define SPDR5 5
#define SPDR6 6
#define SPDR7 7










#else 
//unknown processor - add to spi.h 

#error stopas-nezinau


#endif 




#define SS_LO PORTB &= ~_BV(SPI_SS)
#define SS_HI PORTB |= _BV(SPI_SS)






// SPI clock modes 
#define SPI_MODE_0 0x00 /* Sample (Rising) Setup (Falling) CPOL=0, CPHA=0 */ 
#define SPI_MODE_1 0x01 /* Setup (Rising) Sample (Falling) CPOL=0, CPHA=1 */ 
#define SPI_MODE_2 0x02 /* Sample (Falling) Setup (Rising) CPOL=1, CPHA=0 */ 
#define SPI_MODE_3 0x03 /* Setup (Falling) Sample (Rising) CPOL=1, CPHA=1 */ 

// data direction 
#define SPI_LSB 1 /* send least significant bit (bit 0) first */ 
#define SPI_MSB 0 /* send most significant bit (bit 7) first */ 

// whether to raise interrupt when data received (SPIF bit received) 
#define SPI_NO_INTERRUPT 0 
#define SPI_INTERRUPT 1 

// slave or master with clock diviser 
#define SPI_SLAVE 0xF0 
#define SPI_MSTR_CLK4 0x00 /* chip clock/4 */ 
#define SPI_MSTR_CLK16 0x01 /* chip clock/16 */ 
#define SPI_MSTR_CLK64 0x02 /* chip clock/64 */ 
#define SPI_MSTR_CLK128 0x03 /* chip clock/128 */ 
#define SPI_MSTR_CLK2 0x04 /* chip clock/2 */ 
#define SPI_MSTR_CLK8 0x05 /* chip clock/8 */ 
#define SPI_MSTR_CLK32 0x06 /* chip clock/32 */ 

#endif