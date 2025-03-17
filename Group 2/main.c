/*
 * bluetooth_testR.c
 *
 * Created: 25/02/2025 11:07:53
 * Author : 220158118
 */ 
#define F_CPU 20E6
#include <avr/io.h>
#include <avr/io.h>
#include <util/delay.h>


#define Baud_Rate 9600UL
#define Baud_Register_Value ((F_CPU/(16*Baud_Rate)) - 1)
#define Red_LED PB0
//#define Blue_LED PB1
//#define Green_LED PB2

char Receive_data()
{
	while((UCSR0A & 1<<RXC0)==0); // Waits for register to be empty
	return UDR0 ;
}

int main(void)
{
	 DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
	//UART intialisation
	UBRR0 = Baud_Register_Value;
	UCSR0B = 1<<RXEN0 ;
	UCSR0C = 1<<UCSZ01 | 1<< UCSZ00;
    /* Replace with your application code */
    while (1) 
    {
		char receivedChar = Receive_data();  // Receive character from RN42

		
		PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

		
		switch (receivedChar) {
			case 'r':
			PORTB |= (1 << PB0);  
			break;
			case 'b':
			PORTB |= (1 << PB1);  
			break;
			case 'g':
			PORTB |= (1 << PB2);  
			break;
			default:
			// If an unknown character is received, turn off all LEDs
			PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
			break;
		}
    }
}

