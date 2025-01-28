/*
 * Bluetooth_connection.c
 *
 * Created: 26/01/2025 15:50:12
 * Author : 220158118
 */ 


#define F_CPU 20E6
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

#define Baud_Rate 9600UL
#define Baud_Register_Value ((F_CPU/(16*Baud_Rate)) - 1)

void UART_Init() {
	UBRR0 = Baud_Register_Value; // Set UART's baud to 9600 with F_CPU = 20MHz
	UCSR0B = 1 << TXEN0;//| 1<<RXEN0 ; // Enable transmitter and receiver
	//UCSR0C = 1 << UCSZ01 | 1 << UCSZ00; // 8-bit data, 1 stop bit, no parity
}

void Transmit_Character(char data) {
	while ((UCSR0A & (1 << UDRE0)) == 0); // Wait for the transmit buffer to be empty
	UDR0 = data; // Send the character
}

void Transmit_String(const char* String) {
	uint8_t String_Length = strlen(String); // Get the length of the string
	for (uint8_t Index = 0; Index < String_Length; Index++) { // Loop through the string
		Transmit_Character(String[Index]); // Transmit each character
	}
}

int main(void) {
	UART_Init(); // Initialize UART

		// Send commands to the RN41/RN42 module
		Transmit_String("$$$");
		_delay_ms(1000); // Wait for the module to respond with "CMD"

		Transmit_String("SM,1\r\n"); // Set module as master
		_delay_ms(1000);

		Transmit_String("WR\r\n"); // Save settings
		_delay_ms(1000);

		Transmit_String("R,1\r\n"); // Reboot the module
		_delay_ms(1000);

	while (1) {
		
	
		// Main loop
	}
}