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

#define MOTOR1_PIN1 PA0  // Motor 1, Control Pin 1 (IN1)
#define MOTOR1_PIN2 PA1  // Motor 1, Control Pin 2 (IN2)
#define MOTOR2_PIN1 PA2  // Motor 2, Control Pin 1 (IN3)
#define MOTOR2_PIN2 PA3  // Motor 2, Control Pin 2 (IN4)
#define MOTOR3_PIN1 PB0  // Motor 3, Control Pin 1 (IN5)
#define MOTOR3_PIN2 PB1  // Motor 3, Control Pin 2 (IN6)
#define MOTOR4_PIN1 PB2  // Motor 4, Control Pin 1 (IN7)
#define MOTOR4_PIN2 PB3  // Motor 4, Control Pin 2 (IN8)


char Receive_data()
{
	while((UCSR0A & 1<<RXC0)==0); // Waits for register to be empty
	return UDR0 ;
}


// Function to move forward
void Move_Forward() {
	PORTA |= (1 << MOTOR1_PIN1);
	PORTA &= ~(1 << MOTOR1_PIN2);

	PORTA |= (1 << MOTOR2_PIN1);
	PORTA &= ~(1 << MOTOR2_PIN2);

	PORTB |= (1 << MOTOR3_PIN1);
	PORTB &= ~(1 << MOTOR3_PIN2);

	PORTB |= (1 << MOTOR4_PIN1);
	PORTB &= ~(1 << MOTOR4_PIN2);
}

// Function to move backward
void Move_Backward() {
	PORTA &= ~(1 << MOTOR1_PIN1);
	PORTA |= (1 << MOTOR1_PIN2);

	PORTA &= ~(1 << MOTOR2_PIN1);
	PORTA |= (1 << MOTOR2_PIN2);

	PORTB &= ~(1 << MOTOR3_PIN1);
	PORTB |= (1 << MOTOR3_PIN2);

	PORTB &= ~(1 << MOTOR4_PIN1);
	PORTB |= (1 << MOTOR4_PIN2);
}

// Function to turn left
void Turn_Left() {
	// Left motors (Motor 1 and Motor 2): Move forward
	PORTA |= (1 << MOTOR1_PIN1);
	PORTA &= ~(1 << MOTOR1_PIN2);

	PORTA |= (1 << MOTOR2_PIN1);
	PORTA &= ~(1 << MOTOR2_PIN2);

	// Right motors (Motor 3 and Motor 4): Stop
	PORTB &= ~(1 << MOTOR3_PIN1);
	PORTB &= ~(1 << MOTOR3_PIN2);

	PORTB &= ~(1 << MOTOR4_PIN1);
	PORTB &= ~(1 << MOTOR4_PIN2);
}

// Function to turn right
void Turn_Right() {
	// Right motors (Motor 3 and Motor 4): Move forward
	PORTB |= (1 << MOTOR3_PIN1);
	PORTB &= ~(1 << MOTOR3_PIN2);

	PORTB |= (1 << MOTOR4_PIN1);
	PORTB &= ~(1 << MOTOR4_PIN2);

	// Left motors (Motor 1 and Motor 2): Stop
	PORTA &= ~(1 << MOTOR1_PIN1);
	PORTA &= ~(1 << MOTOR1_PIN2);

	PORTA &= ~(1 << MOTOR2_PIN1);
	PORTA &= ~(1 << MOTOR2_PIN2);
}

// Function to stop all motors
void Stop() {
	PORTA &= ~(1 << MOTOR1_PIN1) & ~(1 << MOTOR1_PIN2);  // Stop Motor 1
	PORTA &= ~(1 << MOTOR2_PIN1) & ~(1 << MOTOR2_PIN2);  // Stop Motor 2
	PORTB &= ~(1 << MOTOR3_PIN1) & ~(1 << MOTOR3_PIN2);  // Stop Motor 3
	PORTB &= ~(1 << MOTOR4_PIN1) & ~(1 << MOTOR4_PIN2);  // Stop Motor 4
}


int main(void)
{
	//UART intialisation
	UBRR0 = Baud_Register_Value;
	UCSR0B = 1<<RXEN0 ;
	UCSR0C = 1<<UCSZ01 | 1<< UCSZ00;
	
	DDRA |= (1 << MOTOR1_PIN1) | (1 << MOTOR1_PIN2) | (1 << MOTOR2_PIN1) | (1 << MOTOR2_PIN2);
	DDRB |= (1 << MOTOR3_PIN1) | (1 << MOTOR3_PIN2) | (1 << MOTOR4_PIN1) | (1 << MOTOR4_PIN2);

	Stop();
	
	
    /* Replace with your application code */
    while (1) 
    {
		char command = Receive_data();
		
		switch (command) {
			case 'F': Move_Backward();
			break;
			case 'B': Move_Backward(); 
			break;
			case 'L': Turn_Left();
			break;
			case 'R': Turn_Right();
			break;
			default: Stop();
		}
    }
}

