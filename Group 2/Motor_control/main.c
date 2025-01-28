/*
 * Motor_control.c
 *
 * Created: 28/01/2025 13:20:25
 * Author : 220158118
 */ 


#define F_CPU 20E6
#include <avr/io.h>
#include <util/delay.h>

// Define motor control pins
#define MOTOR1_PIN1 PB0  // Motor 1, Control Pin 1 (IN1)
#define MOTOR1_PIN2 PB1  // Motor 1, Control Pin 2 (IN2)
#define MOTOR2_PIN1 PB2  // Motor 2, Control Pin 1 (IN3)
#define MOTOR2_PIN2 PB3  // Motor 2, Control Pin 2 (IN4)
#define MOTOR3_PIN1 PB4 // Motor 3, Control Pin 1 (IN5)
#define MOTOR3_PIN2 PB5 // Motor 3, Control Pin 2 (IN6)
#define MOTOR4_PIN1 PB6 // Motor 4, Control Pin 1 (IN7)
#define MOTOR4_PIN2 PB7 // Motor 4, Control Pin 2 (IN8)

// Function to move forward
void Move_Forward() {
	// Motor 1: IN1 = HIGH, IN2 = LOW
	PORTB |= (1 << MOTOR1_PIN1);
	PORTB &= ~(1 << MOTOR1_PIN2);

	// Motor 2: IN3 = HIGH, IN4 = LOW
	PORTB |= (1 << MOTOR2_PIN1);
	PORTB &= ~(1 << MOTOR2_PIN2);

	// Motor 3: IN5 = HIGH, IN6 = LOW
	PORTB |= (1 << MOTOR3_PIN1);
	PORTB &= ~(1 << MOTOR3_PIN2);

	// Motor 4: IN7 = HIGH, IN8 = LOW
	PORTB |= (1 << MOTOR4_PIN1);
	PORTB &= ~(1 << MOTOR4_PIN2);

}

// Function to move backward
void Move_Backward() {
	// Motor 1: IN1 = LOW, IN2 = HIGH
	PORTB &= ~(1 << MOTOR1_PIN1);
	PORTB |= (1 << MOTOR1_PIN2);

	// Motor 2: IN3 = LOW, IN4 = HIGH
	PORTB &= ~(1 << MOTOR2_PIN1);
	PORTB |= (1 << MOTOR2_PIN2);

	// Motor 3: IN5 = LOW, IN6 = HIGH
	PORTB &= ~(1 << MOTOR3_PIN1);
	PORTB |= (1 << MOTOR3_PIN2);

	// Motor 4: IN7 = LOW, IN8 = HIGH
	PORTB &= ~(1 << MOTOR4_PIN1);
	PORTB |= (1 << MOTOR4_PIN2);
}

// Function to turn left
void Turn_Left() {

	PORTB |= (1 << MOTOR1_PIN1);
	PORTB &= ~(1 << MOTOR1_PIN2);

	PORTB |= (1 << MOTOR3_PIN1);
	PORTB &= ~(1 << MOTOR3_PIN2);

	// Right motors (Motor 2 and Motor 4): Stop
	PORTB &= ~((1 << MOTOR2_PIN1) | (1 << MOTOR2_PIN2) | (1 << MOTOR4_PIN1) | (1 << MOTOR4_PIN2));

}

// Function to turn right
void Turn_Right() {
	// Right motors (Motor 2 and Motor 4): Move forward
	PORTB |= (1 << MOTOR2_PIN1);
	PORTB &= ~(1 << MOTOR2_PIN2);

	PORTB |= (1 << MOTOR4_PIN1);
	PORTB &= ~(1 << MOTOR4_PIN2);

	// Left motors (Motor 1 and Motor 3): Stop
	PORTB &= ~((1 << MOTOR1_PIN1) | (1 << MOTOR1_PIN2) | (1 << MOTOR3_PIN1) | (1 << MOTOR3_PIN2));
}

void Stop() {
	PORTB &= ~((1 << MOTOR1_PIN1) | (1 << MOTOR1_PIN2) | (1 << MOTOR2_PIN1) | (1 << MOTOR2_PIN2) | (1 << MOTOR3_PIN1) | (1 << MOTOR3_PIN2) | (1 << MOTOR4_PIN1) | (1 << MOTOR4_PIN2));
}

int main(void) {
	// Set motor control pins as output
	DDRB |= (1 << MOTOR1_PIN1) | (1 << MOTOR1_PIN2) | (1 << MOTOR2_PIN1) | (1 << MOTOR2_PIN2) | (1 << MOTOR3_PIN1) | (1 << MOTOR3_PIN2) | (1 << MOTOR4_PIN1) | (1 << MOTOR4_PIN2);
	// Stop all motors initially
	Stop();

	while (1) {
		// Move forward for 2 seconds
		Move_Forward();
		_delay_ms(2000);

		// Stop for 1 second
		Stop();
		_delay_ms(1000);

		// Move backward for 2 seconds
		Move_Backward();
		_delay_ms(2000);

		// Stop for 1 second
		Stop();
		_delay_ms(1000);

		// Turn left for 2 seconds
		Turn_Left();
		_delay_ms(2000);

		// Stop for 1 second
		Stop();
		_delay_ms(1000);

		// Turn right for 2 seconds
		Turn_Right();
		_delay_ms(2000);

		// Stop for 1 second
		Stop();
		_delay_ms(1000);
	}
}

