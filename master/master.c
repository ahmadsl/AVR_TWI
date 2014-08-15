/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Advanced
Automatic Program Generator
� Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 8/13/2014
Author  : www.Eca.ir *** www.Webkade.ir
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega16.h>
#include <stdio.h>
// Alphanumeric LCD Module functions
#include <alcd.h>

char rx[32];
char tx[32];
char SLA_W,SLA_R;
char DATA;
char a[16];
// Two Wire bus interrupt service routine
interrupt [TWI] void twi_isr(void)
{
// Place your code here
lcd_clear();
lcd_puts("TWINT");
}

// Declare your global variables here

void main(void)
{
// Declare your local variables here
int flag = 1;

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=Out Func1=Out Func0=Out 
// State7=T State6=T State5=T State4=T State3=T State2=0 State1=0 State0=0 
PORTB=0x00;
DDRB=0x07;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// Bit Rate: 400.000 kHz
TWBR=0x02;
// Two Wire Bus Slave Address: 0x1
// General Call Recognition: On
TWAR=0x03;
// Generate Acknowledge Pulse: On
// TWI Interrupt: On
TWCR=0x45;
TWSR=0x00;

// Alphanumeric LCD initialization
// Connections specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTA Bit 0
// RD - PORTA Bit 1
// EN - PORTA Bit 2
// D4 - PORTA Bit 4
// D5 - PORTA Bit 5
// D6 - PORTA Bit 6
// D7 - PORTA Bit 7
// Characters/line: 8
lcd_init(16);

// Global enable interrupts
#asm("sei")

SLA_W = 0x05;
DATA = 'A';

while (1)
      {  
      if(flag){                  
        //start transmite
        TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
        //TWCR = 1<<7   , 5   2  
        //TWCR = 0b00100100;
        lcd_clear();        
        sprintf(a,"%d",TWCR);
        lcd_puts("start");
        lcd_puts(a);
        //
        while(!(TWCR & (1<<TWINT)));
        //start transmition check
        if(TWSR & 0x08){        
            //SLA transmite
            TWDR = SLA_W;
            TWCR = (1<<TWINT) | (1<<TWEN);
            lcd_clear();
            lcd_puts("SLA_W");
            //
            while(!(TWCR & (1<<TWINT)));
            //ack receive check
            if(TWSR & 0x18){
                //data transmite
                TWDR = DATA;
                TWCR = (1<<TWINT) | (1<<TWEN);  
                lcd_clear();
                lcd_puts("DATA");
                //
                while(!(TWCR & (1<<TWINT)));
                //ack receive check
                if(TWSR & 0x28){
                    //stop transmite
                    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);      \
                    lcd_clear();
                    lcd_puts("STOP");
                    flag = 0;
                }else{
                    lcd_puts("DATA ACK r error");
                }  
            }else{
                lcd_puts("SLA ACK r error");
            }            
        }else{
            lcd_puts("st t error");
        }
      }
              
    }
}
