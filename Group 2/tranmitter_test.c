/*
 * bluetooth_test.c
 *
 * Created: 25/02/2025 11:01:51
 * Author : 220158118
 */ 

#define F_CPU 20E6
#include <avr/io.h>
#include <util/delay.h>


#define Baud_Rate 9600UL
#define Baud_Register_Value ((F_CPU/(16*Baud_Rate)) - 1)


void Transmit_Character(char data)
{
	while((UCSR0A & 1<<UDRE0)==0); // Waits for register to be empty
	UDR0 = data;
}

int main(void) {
	//UART intialisation
	UBRR0 = Baud_Register_Value;
	UCSR0B = 1<<TXEN0 ;
	UCSR0C = 1<<UCSZ01 | 1<< UCSZ00;

	while (1) {
		// Send 'r', 'b', or 'g' every second
		Transmit_Character('r');
		_delay_ms(1000);
		Transmit_Character('b');
		_delay_ms(1000);
		Transmit_Character('g');
		_delay_ms(1000);
	}
}