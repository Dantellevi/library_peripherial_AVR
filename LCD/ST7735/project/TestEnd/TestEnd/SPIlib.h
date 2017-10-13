/*
 * SPIlib.h
 *
 * Created: 13.10.2017 11:22:46
 *  Author: Dante_L_Levi
 */ 


#ifndef SPILIB_H_
#define SPILIB_H_
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned int SPI_DATA = 0;
volatile unsigned int SPI_FLAG = 0;


#define FULL	0xFF

#ifdef SPDR

#if !defined (NULL)
#define NULL 0
#endif

// Включить SPI
#define SPI_ON			0x40

// Выключить SPI
#define SPI_OFF			0

// Режим Мастер
#define SPI_MASTER		0x10

// Режим Слейв
#define SPI_SLAVE		0

// Направление передачи (Младший разряд вперед)
#define SPI_DIRECT_LSB	0x20

// Направление передачи (Старший разряд вперед)
#define SPI_DIRECT_MSB	0

// Разрешить прерывание
#define SPI_INT_ON		0x80

// Запретить прерывание
#define SPI_INT_OFF		0

// Положительный тактовый сигнал
#define SPI_CPOL_LOW	0

// Отрицательный тактовый сигнал
#define SPI_CPOL_HIGHT	0x08

// Наростающий фронт сигнала
#define SPI_CPHA_1EDGE	0
// Спадающий фронт сигнала
#define SPI_CPHA_2EDGE	0x04

// Предделитель частоты (настройка скорости передачи для мастера)
#define SPI_PRESCALER_2		0
#define SPI_PRESCALER_4		1
#define SPI_PRESCALER_8		2
#define SPI_PRESCALER_16	3
#define SPI_PRESCALER_32	4
#define SPI_PRESCALER_64	5
#define SPI_PRESCALER_128	6
#define SPI_PRESCALER_NO	7





#define SPI_M_PORT		(DDRB |= (1 << 5) | (1 << 7) | (1 << 4))
#define SPI_M_SS_ON		(PORTB &= ~(1 << 4))
#define SPI_M_SS_OFF	(PORTB |= (1 << 4))

#define SPI_S_PORT		(DDRB |= (1 << 6))
#define SPI_S_SS_PIN	4



// Флаг наличия данных в режиме Slave
#define FLAG_DATA	0
#define FLAG_OUT	1

#if defined(SPI_SLAVE_MODE)
// Преывания по окончанию передачи для ведущего
ISR(SPI_STC_vect)
{
	SPI_DATA = SPDR;
	SPI_FLAG = 1;
}
#endif

// Объявление структур
typedef struct
{
	char SPI_set;			// Включить/выключить SPI
	char SPI_Mode;			// Выбор Мастер или Слейв
	char SPI_Direct;		// Выбор направления передачи байта
	char SPI_Prescaler;		// Выбор претделителя
	char SPI_Polaric;		// Выбор полярности тактового сигнала
	char SPI_Phase;			// Выбор фазы тактового сигнала
	
}SPI_InitTypeDef;

// Объявление функций

// Инициализация SPI
void SPI_init(SPI_InitTypeDef *spi);

// Чтение байта и передача по шине для мастер устройства
unsigned char SPI_M_byte_io(char data);

// Чтение байта из шины для слейв устройства
unsigned char SPI_S_byte_io(char data, char timeout);




// Функции

//-------------------------------------------------------------------------------------------------------

// Функция инициализации SPI принимает в качестве аргумента указатель на структуру

void SPI_init(SPI_InitTypeDef *spi)
{
	if(spi == NULL)
	{
		return;
	}
	if(spi->SPI_Mode == SPI_MASTER)
	{
		SPI_M_PORT;
		SPI_M_SS_OFF;
		SPCR = (spi->SPI_set | spi->SPI_Mode | spi->SPI_Direct | spi->SPI_Polaric | spi->SPI_Phase);
	}
	else
	{
		SPI_S_PORT;
		SPCR = (spi->SPI_set | spi->SPI_Mode | spi->SPI_Direct | spi->SPI_Polaric | spi->SPI_Phase | (1 << SPIE));
		sei();
	}

	switch (spi->SPI_Prescaler)
	{
		case 0: // 2
		SPSR |= (1 << SPI2X);
		SPCR &= ~(1 << SPR0) | ~(1 << SPR1);
		break;
		
		case 1: // 4
		SPCR &= ~(1 << SPR0) | ~(1 << SPR1);
		break;
		
		case 2: // 8
		SPSR |= (1 << SPI2X);
		SPCR |= (1 << SPR0);
		SPCR &= ~(1 << SPR1);
		break;
		
		case 3: // 16
		SPCR |= (1 << SPR0);
		SPCR &= ~(1 << SPR1);
		break;
		
		case 4: // 32
		SPSR |= (1 << SPI2X);
		SPCR &= ~(1 << SPR0);
		SPCR |= (1 << SPR1);
		break;
		
		case 5: // 64
		SPCR &= ~(1 << SPR0);
		SPCR |= (1 << SPR1);
		break;
		
		case 6: //128
		SPCR |= 0x03;
		break;
		
		case 7: //SLAVE
		SPCR &= 0xFC;
		break;
	}
}

//-------------------------------------------------------------------------------------------------------

// Чтение байта и передача по шине для мастер устройства
unsigned char SPI_M_byte_io(char data)
{
	unsigned char answer = 0;
	SPI_M_SS_ON;
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	answer = SPDR;
	SPI_M_SS_OFF;
	return answer;
}

//-------------------------------------------------------------------------------------------------------

// Чтение/запись байта из шины для слейв устройства
unsigned char SPI_S_byte_io(char data, char timeout)
{
	// Ожидания единицы на входе SS
	while(!(PINB & (1 << SPI_S_SS_PIN)));
	// Загрузка байта для передачи Мастеру
	SPDR = data;
	// Ожидания завершения обмена
	while(SPI_FLAG == 0)
	{
		if(!timeout)
		{
			// Выход с записью в регистр данных 0xFF по таймауту
			SPDR = 0xFF;
			return FULL;
		}
		_delay_ms(1);
		timeout--;
	}
	// Сброс флага обмена
	SPI_FLAG = 0;
	// Возврат значения принятого от Мастера
	return SPI_DATA;
}





#endif // SPDR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




#endif /* SPILIB_H_ */