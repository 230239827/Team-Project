/*
 * HCSR04code.c
 *
 * Created: 04/02/2025 11:04:04
 * Author : 230091007
 */ 

#include <avr/io.h>
#include < util/delay.h>
#include <avr/interrupt.h>

#define TRIGGER_PIN PD1
#define ECHO_PIN PD2
#define BUZZER_PIN PD3


void init_ports() {
	// Set TRIG_PIN as output
	DDRD |= (1 << TRIGGER_PIN);
	
	// Set ECHO_PIN as input
	DDRD &= ~(1 << ECHO_PIN);
}

void send_trigger() { //10us pulse
	PORTD |= (1 << TRIGGER_PIN);
	_delay_us(10);
	PORTD &= ~(1 << TRIGGER_PIN);
}

uint16_t get_distance() {
	send_trigger();

    // Wait for the ECHO signal to go high
    while (!(PIND & (1 << ECHO_PIN)));

    // Measure the pulse width
    uint32_t duration = 0;
    while (PIND & (1 << ECHO_PIN)) { //checking if echo pin is high
	    duration++; //counts the number of us the pin stays high. (Measuring pulse width)
	    _delay_us(1); // Each loop takes 1 microsecond
	    if (duration > 30000) break; // prevents loop from running indefinitely
    }

    
    // Calculate distance in cm
    return duration / (1/(0.0343/2)); // Speed of sound is 343m/s 
    }


int main(void)
{
	
    DDRD |= (1<<buzzer);
    PORTD &= ~(1<<buzzer);
	
    init_ports();
    while (1) 
    {        
		uint16_t distance = get_distance(); //measures the duration of the echo pulse and calculates the distance in centimetres
	    
	    if (distance < 50) { // If obstacle is closer than 50 cm, send a signal to buzzer 

		PORTD |= (1<<buzzer); 
		_delay_us(900);
		
		PORTD &= ~(1<<buzzer);
		_delay_us(900);
		
	
		}	
		}
		
		else{ //do nothing, allow sensor to continue as normal
			
		}
	   
    }
	
}


