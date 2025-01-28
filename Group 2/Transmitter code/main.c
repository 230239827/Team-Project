/*
 * Transmitter code.c
 *
 * Created: 20/01/2025 20:08:07
 * Author : 220158118
 */ 

#define F_CPU 20E6                                
#include <avr/io.h> 
#include <avr/interrupt.h>   

#define Baud_Rate 9600UL
#define Baud_Register_Value ((F_CPU/(16*Baud_Rate)) - 1)                                                                                                                                                                                                                                       


void Transmit_Character(char data)
{
	while((UCSR0A & 1<<UDRE0)==0); // Waits for register to be empty
	UDR0 = data;
}


int main(void)
{
	//UART intialisation
	UBRR0 = Baud_Register_Value;
	UCSR0B = 1<<TXEN0 ;
	UCSR0C = 1<<UCSZ01 | 1<< UCSZ00
	
	
	
	sei();
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

