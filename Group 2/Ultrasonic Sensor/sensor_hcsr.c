/*
 * sensor_hcsr.c
 *
 * Created: 18/02/2025 15:01:37
 * Author : 230091007
 */ 

#define F_CPU 20E6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define TRIGGER_PIN PD2
#define ECHO_PIN PD3
#define BUZZER_PIN PD4

void trigger()
{														// Sending 10us trigger pulse
	PORTD |= (1 << TRIGGER_PIN);
	_delay_us(10);
	PORTD &=~ (1 << TRIGGER_PIN);
	_delay_us(10);
}


int main(void)
{
	DDRD &= ~(1 << ECHO_PIN);
	DDRD |= (1 << TRIGGER_PIN) | (1 << BUZZER_PIN);
	
	
	while (1)
	{
		trigger();
		_delay_ms(1000);								// Delay for 1s
	

 		uint16_t duration = 0;
	 
 		while (PIND & (1 << ECHO_PIN))					// When echo is high, time it
		{
			_delay_us(1);								// Counts in us
			duration++;									// Times how long the pin stays high (Measuring the pulse width)
		}
			
			
		uint16_t distance = (duration/148);				// cm = us/148
		
		
		if (distance < 50)							// If obstacle is closer than 50cm, send signal to buzzer
			
		{
			PORTD |= (1 << BUZZER_PIN);
			_delay_ms(200);
				
			PORTD &= ~(1 << BUZZER_PIN);
			_delay_ms(200);
		}
			
		else
		{
			PORTD &= ~(1 << BUZZER_PIN);
		}
			
		
		
		

	}
}



