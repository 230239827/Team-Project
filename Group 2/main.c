/*
 * Buzzer_test.c
 *
 * Created: 28/01/2025 15:16:07
 * Author : 230239827
 */ 

#define F_CPU 20E6
#include <avr/io.h>
#include <util/delay.h>

#define buzzer PD3

int main(void)
{
    /* Replace with your application code */
	
	DDRD |= (1<<buzzer);
	PORTD &= ~(1<<buzzer);
	
    while (1) 
    {
		PORTD |= (1<<buzzer); 
		_delay_us(900);
		
		PORTD &= ~(1<<buzzer);
		_delay_us(900);

    }
	return 0;
}

//void buzzer_test()