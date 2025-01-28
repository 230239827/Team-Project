/*
 * Reciever_code.c
 *
 * Created: 27/01/2025 20:26:38
 * Author : 220158118
 */ 

#define F_CPU 20E6
#include <avr/io.h>
#include <avr/interrupt.h>

#define Baud_Rate 9600UL
#define Baud_Register_Value ((F_CPU/(16*Baud_Rate)) - 1)

char Receive_data()
{
	while((UCSR0A & 1<<RXC0)==0); // Waits for register to be empty
	return UDR0 ;
}

int main(void)
{
	//UART intialisation
	UBRR0 = Baud_Register_Value;
	UCSR0B = 1<<RXEN0 ;
	UCSR0C = 1<<UCSZ01 | 1<< UCSZ00
	
	
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

