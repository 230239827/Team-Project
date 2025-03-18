/*
 * UPDATEDHCSR04.c
 *
 * Created: 18/03/2025 00:39:41
 * Author : 230091007
 */ 

#define F_CPU 20E6
#include <avr/io.h>
#include <util/delay.h>

#define TRIGGER_PIN PD2
#define ECHO_PIN PD3
#define BUZZER_PIN PD4

void trigger()
{
	PORTD |= (1 << TRIGGER_PIN);
	_delay_us(10);
	PORTD &= ~(1 << TRIGGER_PIN);
}

int main(void)
{
    DDRD &= ~(1 << ECHO_PIN);
	DDRD |= (1 << TRIGGER_PIN) | (1 << BUZZER_PIN);
	
	uint16_t duration = 0;
	uint16_t distance = 0;
	
    while (1) 
    {
		trigger();
		_delay_us(10);
		
		duration = 0;
		while (!(PIND & (1 << ECHO_PIN)))
		{
		}
		
		while (PIND & (1 << ECHO_PIN))
		{
			_delay_us(1);
			duration++;
		}
		
		distance = (duration/58);
		
		if (distance < 40)
		{
			PORTD |= (1 << BUZZER_PIN);
			_delay_ms(200);
			
			PORTD &= ~(1 << BUZZER_PIN);
		}
		
		else
		{
			PORTD &= ~(1 << BUZZER_PIN);
		}
		_delay_ms(100);
    }
}

