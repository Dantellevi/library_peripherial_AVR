

#define BUT_PORT PINC
//LED PORT config
#define LED_PORT PORTD
#define RDY 4
#define SND 5
#define ERR 7

//LED config - '0' - off '1' - on
#define RDY_OFF (LED_PORT &= ~ (1<<RDY))
#define RDY_ON (LED_PORT |= (1<<RDY))

#define SND_OFF (LED_PORT &= ~ (1<<SND))
#define SND_ON (LED_PORT |= (1<<SND))


#define ERR_OFF (LED_PORT &= ~ (1<<ERR))
#define ERR_ON (LED_PORT |= (1<<ERR))

#define LED_LGT (LED_PORT = (1<<RDY) | (1<<SND) | (1<<ERR))
#define LED_CLR (LED_PORT = (0<<RDY) | (0<<SND) | (0<<ERR))

#define LONG_DELAY _delay_ms (2100)


//------Message sended-----------------
// #define REG_MESS "Parts or kits recently ordered from store already in passthrough room"
#define REG_MESS "Hello. Button 1\n"
#define STR_MESS "Device ready to work\n"
//-------------------------------------


//-------------------------------------
//NUMBERS OF TELEPHONES
//-------------------------------------

#define NUM0 "+1234567899\n"

//-------------------------------------

//LCD_config
#define RS 0    //ATmega8 for Tower - 2, Pinboard - 0
#define E 2   //Alwais PB - 2
#define LCD_PORT PORTB   //pinboard - PORTB, ATmega8 for Tower PORTD
#define LCD_DELAY _delay_us (780)

void init_all (void)
	{
	MCUCSR |= (1<<JTD); //Cancel JTAG
	MCUCSR |= (1<<JTD);
	//Timers
	TCCR0 = 0;
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR2 = 0;
	DDRA = 0xFF;  //Comment on ATmega8
	DDRB = 0xFF;   //Config out port LCD PORT
	DDRD = 0xFF;   //
	DDRC = 0x00;   //Button port
	PORTA = 0;    //Comment on ATmega8
	PORTC = 0xFF;
	PORTD = 0;
	PORTB = 0;
	//InitUSART

	#define baudrate 9600L
	#define bauddivider (F_CPU/(16*baudrate)-1)
	#define HI(x) ((x)>>8)
	#define LO(x) ((x)& 0xFF)
 
	UBRRL = LO(bauddivider);
	UBRRH = HI(bauddivider);
	UCSRA = 0;
	UCSRB = 1<<RXEN|1<<TXEN|1<<RXCIE|0<<TXCIE;
	UCSRC = 1<<URSEL|1<<UCSZ0|1<<UCSZ1;
	UCSRA &= ~(1<< UDRE);
	sei(); 		//Enable inerupts
	}
