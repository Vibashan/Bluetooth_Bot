#include<avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//USART Initialisation
void usart_int(void) 
{
  UCSR0A=0x00;
  UCSR0B=(1<< RXEN0)|(1<< TXEN0);// TRANSMIT AND RECEIVE ENABLE
  UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);// ASYNCHRONOUS, 8 BIT TRANSFER
  UBRR0L= 103 ; // BAUD RATE 9600 
}

void usart_send(int ch )
{
  while(UCSR0A!=(UCSR0A|(1<<UDRE0)));// Waiting for UDRE to become high
  UDR0= ch;
}

int main(void)
{
  DDRB=0xFF;
  DDRD=0b11110000; // Setting all motor connections as Output
  float  Time;
  int D;
  usart_int();
  unsigned int ch;
  while(1)
  {
    //Waits for until it recivie data
    while(UCSR0A!= (UCSR0A|(1<<RXC0)));
    
    ch=UDR0;
 
    if(ch==0)  //Stop
    {
      PORTD=0x00;
    }
    if(ch==1) //Backward
    {
      PORTD=0b10100000;
      PORTB=0b00000110;
    }
    else if(ch==2) //Forward
    {
      PORTD=0b01010000;
      PORTB=0b00000110;
    }
    else if(ch==3)  //Right
    {
      PORTD=0b10010000;
      PORTB=0b00000110;
    }
    else if(ch==4) //Left
    {
      PORTD=0b01100000;
      PORTB=0b00000110;
    }

    }
      
  }
  
  

