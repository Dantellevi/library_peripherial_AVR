  ISR (TIMER1_COMPA_vect)  //��������� ���� ������
  {
	volatile static unsigned char Danie;
    register unsigned char Temp ;	
	TCCR1A &=~(1<<WGM11);	 	
    PORTA &=  Servo_W[ Danie].Servo_portA_;      // ����� ������ ����������� � ������� ������� 
	PORTB &=  Servo_W[  Danie].Servo_portB_;   
	PORTC &=  Servo_W[ Danie].Servo_portC_;
	PORTD &=  Servo_W[ Danie].Servo_portD_;
	Danie++;  
	Temp = Servo_W[Danie].Servo_Position_;	     //������� ��������� �����		 		  		  
	if ((Temp == 0xFF) | (Danie == MaxServo))    // ��������� �� ����� ������ 0xFF ��� �������� ���� ������ ���������
	 { 
	   Danie = 0;
	   Servo_Dan &=~ (1<<0);
	 }	   
	else
	 {	   
	   OCR1A  = Servo_W[Danie].Servo_Position_;  //������ ������ �� �������	        
	 }		 	 	 
	TIFR |=(1<<OCIE1A);               //����� ������	
     TCCR1A |=(1<<WGM11); 			 			 		 			   		  		  			 			   	 
  }
  
 ISR(TIMER1_OVF_vect)                 //��������� 20��. 
  {	 
	PORTA |= Servo_Uctanovka[0];      //������������� ������� ��������� �� ����(� ����������� � ������������ ���������������)
	PORTB |= Servo_Uctanovka[1];      //������������� ������� ��������� �� ����(� ����������� � ������������ ���������������)
	PORTC |= Servo_Uctanovka[2];      //������������� ������� ��������� �� ����(� ����������� � ������������ ���������������)
	PORTD |= Servo_Uctanovka[3];      //������������� ������� ��������� �� ����(� ����������� � ������������ ���������������)
	TCCR1A &=~(1<<WGM11);
	OCR1A  =Servo_W[0].Servo_Position_;  //������ ������ �� �������	        
	TIFR |=(1<<OCIE1A);                  //����� ������
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
  //  ** ��������� ������ ���� �� ����������� �� ������� � ������� ** //	    
   do
    {
     i = 0;
	 DD = 0;		
	 while ( DD < S )   
       {
		 DD++;		  	     		
	     if ( Servo_[i]->Position > Servo_[DD]->Position ) //���������� ������ ��� ��� ������ ������ ����� ������
	      {
		    Temp =Servo_[i];                               //��������� ������ ������
		    Servo_[i] = Servo_[DD];                        //������������� ������ ������ 
		    Servo_[DD]= Temp;                              //�������������� ������ ������      
	      }	
		 i++;     	   	   
       }  
      S--;  	   		    	   	   	   
    } while (S > 0);                                       //��������� ������ � ����������� �� �������� MaxServo
  // ** ������������� ����� � ������ �� ������ ** //
	DD = 0; 
	i = 0; 
	Servo_W[0].Servo_portA_ = 255;    
	Servo_W[0].Servo_portB_ = 255;
	Servo_W[0].Servo_portC_ = 255;
	Servo_W[0].Servo_portD_ = 255;		
	while (1)         
	 {			   					
	  Temp = Servo_[S]->BitPorta;	 //��������� ������ �� ����� � ����		
	  switch ( Temp & 0b11110000)   //�������� ����� � ������ ��� ����� 
		{
		case 0xA0: Servo_W[DD].Servo_portA_ ^= (1<<(Temp & 0b00001111)); break;	//������������� ��� � ���� �� �����A		          			         			           
		case 0xB0: Servo_W[DD].Servo_portB_ ^= (1<<(Temp & 0b00001111)); break;	//������������� ��� � ���� �� �����B		           			          
		case 0xC0: Servo_W[DD].Servo_portC_ ^= (1<<(Temp & 0b00001111)); break;	//������������� ��� � ���� �� �����C
		case 0xD0: Servo_W[DD].Servo_portD_ ^= (1<<(Temp & 0b00001111)); break;	//������������� ��� � ���� �� �����D
		}
	 i++;
	 if ( i == MaxServo )
		break;				
	 if (!(Servo_[S]->Position == Servo_[i]->Position))     //��������� ��������� ������ ������� ��� ���
	  {
		Servo_W[DD].Servo_Position_ = Servo_[S]->Position; //��������� ���� ������	� ����������� ������	
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
		Servo_W[DD].Servo_Position_ = Servo_[S]->Position; //��������� ���� ������	� ����������� ������ 
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
		Temp = Servo[i].BitPorta;      //������ �������� ������ ������������ (����� ���� � ��� )		 	
		switch ( Temp )                //���������� � ����� ������ ����� �������� 
		 {
			case 0xA0 ... 0xA7:  
				Temp = (1<<(Temp & 0b00001111)); //���������� ����� ��� ��������� �� ����� 
				PORTA &=~ Temp;                  //����� ����� � ����
				DDRA |= Temp;                    //�������������� ���� �� �����
				Servo_Uctanovka[0] |=Temp;    	 //������������� ����� ���� ������ ����� ���. ������ 20���������� 						 
			    break;			          			         			           
			case 0xB0 ... 0xB7:  
				Temp = (1<<(Temp & 0b00001111)); //���������� ����� ��� ��������� �� ����� 
				PORTB &=~ Temp;                  //����� ����� � ����
				DDRB |= Temp;                    //�������������� ���� �� �����
				Servo_Uctanovka[1] |=Temp;	     //������������� ����� ���� ������ ����� ���. ������ 20���������� 
			    break;			           			          
			case 0xC0 ... 0xC7: 
				Temp = (1<<(Temp & 0b00001111)); //���������� ����� ��� ��������� �� ����� 
				PORTC &=~ Temp;                  //����� ����� � ����                   
				DDRC |= Temp;                    //�������������� ���� �� �����
				Servo_Uctanovka[2] |=Temp;	     //������������� ����� ���� �����C ����� ���. ������ 20���������� 
			    break;	
			case 0xD0 ... 0xD7:  
				Temp = (1<<(Temp & 0b00001111)); //���������� ����� ��� ��������� �� ����� 
				PORTD &=~ Temp;                  //����� ����� � ���� 
				DDRD |= Temp;                    //�������������� ���� �� �����
				Servo_Uctanovka[3] |=Temp;	     //������������� ����� ���� �����D ����� ���. ������ 20���������� 
			    break;	
		}
	   i++;			
	 }	
	ICR1 = 2500;//5000 ��������� 20��. ��� 16���. //2500 ��������� 20��. ��� 8���.		 
	TCCR1B |= (1 << ICES1)|(1<<CS10)|(1<<CS11)|(1<<WGM12)|(1<<WGM13);
	TIMSK |=(1<<TOIE1)|(1<<OCIE1A);
	TCCR1A |=(1<<WGM11);  				 	  	  	  
  }   