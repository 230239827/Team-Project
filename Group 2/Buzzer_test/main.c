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
//#define UTX PD2

void initial()
{
	DDRD |= 1<<buzzer; //| 1<<UTX;
	PORTD &= ~(1<<buzzer);
}

void buttonOn()
{
	PORTD |= (1<<buzzer);
	_delay_us(900);
}

void buttonOff()
{
	PORTD &= ~(1<<buzzer);
	_delay_us(900);
}

int main(void)
{
    /* Replace with your application code */
	
	initial();
	
    while (1) 
    {
		//PORTD |= 1<<UTX;
		//_delay_us(10);
		
		//PORTD &= ~(1<<UTX);
		//_delay_ms(10);
		
		buttonOn();
		
		buttonOff();
		

    }
	return 0;
}

//void buzzer_test()