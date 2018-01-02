  ISR (TIMER1_COMPA_vect)  //формируем углы здвига
  {
	volatile static unsigned char Danie;
    register unsigned char Temp ;	
	TCCR1A &=~(1<<WGM11);	 	
    PORTA &=  Servo_W[ Danie].Servo_portA_;      // сброс портов относящиеся к данному времени 
	PORTB &=  Servo_W[  Danie].Servo_portB_;   
	PORTC &=  Servo_W[ Danie].Servo_portC_;
	PORTD &=  Servo_W[ Danie].Servo_portD_;
	Danie++;  
	Temp = Servo_W[Danie].Servo_Position_;	     //считуем следующее врема		 		  		  
	if ((Temp == 0xFF) | (Danie == MaxServo))    // проверяем на конец данных 0xFF или передача всех данных закончена
	 { 
	   Danie = 0;
	   Servo_Dan &=~ (1<<0);
	 }	   
	else
	 {	   
	   OCR1A  = Servo_W[Danie].Servo_Position_;  //первые данные по времени	        
	 }		 	 	 
	TIFR |=(1<<OCIE1A);               //сброс флагов	
     TCCR1A |=(1<<WGM11); 			 			 		 			   		  		  			 			   	 
  }
  
 ISR(TIMER1_OVF_vect)                 //формеруем 20мс. 
  {	 
	PORTA |= Servo_Uctanovka[0];      //устанавливаем высокое состояние на порт(в зависимости с определением серводвигателей)
	PORTB |= Servo_Uctanovka[1];      //устанавливаем высокое состояние на порт(в зависимости с определением серводвигателей)
	PORTC |= Servo_Uctanovka[2];      //устанавливаем высокое состояние на порт(в зависимости с определением серводвигателей)
	PORTD |= Servo_Uctanovka[3];      //устанавливаем высокое состояние на порт(в зависимости с определением серводвигателей)
	TCCR1A &=~(1<<WGM11);
	OCR1A  =Servo_W[0].Servo_Position_;  //первые данные по времени	        
	TIFR |=(1<<OCIE1A);                  //сброс флагов
	TCCR1A |=(1<<WGM11);
  }
  //*******************************//
  //*******************************// 
void DanieServo_Port(void)
 {	  	
   register unsigned char i,DD,Temp,S = (MaxServo - 1);
   unsigned char *F;  
   if ( Servo_Dan & (1<<0))
    return;
	asm("cli"); 
  //  ** сортируем данные угла по возрастанию от меншего к болшему ** //	    
   do
    {
     i = 0;
	 DD = 0;		
	 while ( DD < S )   
       {
		 DD++;		  	     		
	     if ( Servo_[i]->Position > Servo_[DD]->Position ) //определяем больше или нет первые данные прием вторые
	      {
		    Temp =Servo_[i];                               //сохраняем первые данные
		    Servo_[i] = Servo_[DD];                        //презаписываем первые данные 
		    Servo_[DD]= Temp;                              //перезаписываем вторые данные      
	      }	
		 i++;     	   	   
       }  
      S--;  	   		    	   	   	   
    } while (S > 0);                                       //сортируем массив в зависимости от значения MaxServo
  // ** устанавливаем порты и данные по здвигу ** //
	DD = 0; 
	i = 0; 
	Servo_W[0].Servo_portA_ = 255;    
	Servo_W[0].Servo_portB_ = 255;
	Servo_W[0].Servo_portC_ = 255;
	Servo_W[0].Servo_portD_ = 255;		
	while (1)         
	 {			   					
	  Temp = Servo_[S]->BitPorta;	 //считываем данные по порту и пина		
	  switch ( Temp & 0b11110000)   //налажуем маску и узнаем имя порта 
		{
		case 0xA0: Servo_W[DD].Servo_portA_ ^= (1<<(Temp & 0b00001111)); break;	//устанавливаем бит в ноль на портуA		          			         			           
		case 0xB0: Servo_W[DD].Servo_portB_ ^= (1<<(Temp & 0b00001111)); break;	//устанавливаем бит в ноль на портуB		           			          
		case 0xC0: Servo_W[DD].Servo_portC_ ^= (1<<(Temp & 0b00001111)); break;	//устанавливаем бит в ноль на портуC
		case 0xD0: Servo_W[DD].Servo_portD_ ^= (1<<(Temp & 0b00001111)); break;	//устанавливаем бит в ноль на портуD
		}
	 i++;
	 if ( i == MaxServo )
		break;				
	 if (!(Servo_[S]->Position == Servo_[i]->Position))     //проверяем следующие данные такиеже или нет
	  {
		Servo_W[DD].Servo_Position_ = Servo_[S]->Position; //сохраняем угол сдвига	к выставленым портам	
		DD++;						
		Servo_W[DD].Servo_portA_ = 255;  
		Servo_W[DD].Servo_portB_ = 255;
		Servo_W[DD].Servo_portC_ = 255;
		Servo_W[DD].Servo_portD_ = 255;	 				 				 												 
	  }		 			 			  				  		
	 S++; 	   		   		   		 				    				    	     			      		  
    } 	 	 
	   if ( DD < MaxServo ) 
		{
		Servo_W[DD].Servo_Position_ = Servo_[S]->Position; //сохраняем угол сдвига	к выставленым портам 
		DD++; 
		Servo_W[DD].Servo_Position_ = 0xFF;
		}
	Servo_Dan |=(1<<0);
	asm("sei"); 	 	 	  	 		   	  	
 }
 //********************************//      
void Servo_Port_Ustanovki(void)
  {
	register uint8_t Temp,i = 0;		
	//=================// 	 	 
   while ( i < MaxServo )      
	 {
        Servo_[i]= &Servo[i];	   	
		Temp = Servo[i].BitPorta;      //узнаем привязку даного сервопривода (какой порт и бит )		 	
		switch ( Temp )                //определяем с каким портом будем работать 
		 {
			case 0xA0 ... 0xA7:  
				Temp = (1<<(Temp & 0b00001111)); //определяем какой бит выставить на порту 
				PORTA &=~ Temp;                  //сброс порта в ноль
				DDRA |= Temp;                    //переопределяем порт на выход
				Servo_Uctanovka[0] |=Temp;    	 //устанавливаем какие биты портаА нужно вкл. каждые 20милесикунд 						 
			    break;			          			         			           
			case 0xB0 ... 0xB7:  
				Temp = (1<<(Temp & 0b00001111)); //определяем какой бит выставить на порту 
				PORTB &=~ Temp;                  //сброс порта в ноль
				DDRB |= Temp;                    //переопределяем порт на выход
				Servo_Uctanovka[1] |=Temp;	     //устанавливаем какие биты портаВ нужно вкл. каждые 20милесикунд 
			    break;			           			          
			case 0xC0 ... 0xC7: 
				Temp = (1<<(Temp & 0b00001111)); //определяем какой бит выставить на порту 
				PORTC &=~ Temp;                  //сброс порта в ноль                   
				DDRC |= Temp;                    //переопределяем порт на выход
				Servo_Uctanovka[2] |=Temp;	     //устанавливаем какие биты портаC нужно вкл. каждые 20милесикунд 
			    break;	
			case 0xD0 ... 0xD7:  
				Temp = (1<<(Temp & 0b00001111)); //определяем какой бит выставить на порту 
				PORTD &=~ Temp;                  //сброс порта в ноль 
				DDRD |= Temp;                    //переопределяем порт на выход
				Servo_Uctanovka[3] |=Temp;	     //устанавливаем какие биты портаD нужно вкл. каждые 20милесикунд 
			    break;	
		}
	   i++;			
	 }	
	ICR1 = 2500;//5000 формеруем 20мс. для 16Мгц. //2500 формеруем 20мс. для 8Мгц.		 
	TCCR1B |= (1 << ICES1)|(1<<CS10)|(1<<CS11)|(1<<WGM12)|(1<<WGM13);
	TIMSK |=(1<<TOIE1)|(1<<OCIE1A);
	TCCR1A |=(1<<WGM11);  				 	  	  	  
  }   