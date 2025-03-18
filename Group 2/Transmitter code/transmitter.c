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
#define JOYSTICK_X 5  
#define JOYSTICK_Y 6  

#define JOYSTICK_NEUTRAL_LOW 450
#define JOYSTICK_NEUTRAL_HIGH 550

void Transmit_Character(char data)
{
	while((UCSR0A & 1<<UDRE0)==0); // Waits for register to be empty
	UDR0 = data;
}

uint16_t ADC_Read(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);  // Select ADC channel
	ADCSRA |= (1 << ADSC);  // Start conversion
	while (ADCSRA & (1 << ADSC));  // Wait for conversion to complete
	return ADC;  // Return ADC value
}

int main(void)
{
	//UART intialisation
	UBRR0 = Baud_Register_Value;
	UCSR0B = 1<<TXEN0 ;
	UCSR0C = 1<<UCSZ01 | 1<< UCSZ00
	
	//ADC initialisation
	ADMUX |= (1<<REFS0)
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	
	
	
	
	
    /* Replace with your application code */
    while (1) 
    {
		uint16_t joystickX = ADC_Read(JOYSTICK_X);
		uint16_t joystickY = ADC_Read(JOYSTICK_Y);
		
		char command = 'S';
		
		if (joystickX > JOYSTICK_NEUTRAL_HIGH) 
		command = 'F';
		else if (joystickX > JOYSTICK_NEUTRAL_LOW)
		 command = 'B';
		else if (joystickY > JOYSTICK_NEUTRAL_HIGH)
		command = 'R';
		else if (joystickY < JOYSTICK_NEUTRAL_LOW)
		command = 'L';
		
		Transmit_Character(command);
		

    }
}

