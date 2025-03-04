#define F_CPU 20000000UL  // 20 MHz clock
#include <avr/io.h>
#include <util/delay.h>

// Define motor control pins
#define MOTOR1_PIN1 PA0  // Motor 1, Control Pin 1 (IN1)
#define MOTOR1_PIN2 PA1  // Motor 1, Control Pin 2 (IN2)
#define MOTOR2_PIN1 PA2  // Motor 2, Control Pin 1 (IN3)
#define MOTOR2_PIN2 PA3  // Motor 2, Control Pin 2 (IN4)
#define MOTOR3_PIN1 PB0  // Motor 3, Control Pin 1 (IN5)
#define MOTOR3_PIN2 PB1  // Motor 3, Control Pin 2 (IN6)
#define MOTOR4_PIN1 PB2  // Motor 4, Control Pin 1 (IN7)
#define MOTOR4_PIN2 PB3  // Motor 4, Control Pin 2 (IN8)

// Define ADC channels for joysticks
#define JOYSTICK_X 5  // Joystick X-axis connected to ADC5 (PA5)
#define JOYSTICK_Y 6  // Joystick Y-axis connected to ADC6 (PA6)

// Define thresholds for joystick control
#define JOYSTICK_NEUTRAL_LOW 450  // Lower threshold for neutral position
#define JOYSTICK_NEUTRAL_HIGH 550  // Upper threshold for neutral position

// Function to initialize ADC
void ADC_Init() {
	ADMUX |= (1 << REFS0);  // Use AVCC as reference voltage
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Enable ADC and set prescaler to 128
}

// Function to read ADC value
uint16_t ADC_Read(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);  // Select ADC channel
	ADCSRA |= (1 << ADSC);  // Start conversion
	while (ADCSRA & (1 << ADSC));  // Wait for conversion to complete
	return ADC;  // Return ADC value
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

int main(void) {
	// Set motor control pins as output
	DDRA |= (1 << MOTOR1_PIN1) | (1 << MOTOR1_PIN2) | (1 << MOTOR2_PIN1) | (1 << MOTOR2_PIN2);
	DDRB |= (1 << MOTOR3_PIN1) | (1 << MOTOR3_PIN2) | (1 << MOTOR4_PIN1) | (1 << MOTOR4_PIN2);

	// Initialize ADC
	ADC_Init();

	// Stop all motors initially
	Stop();

	while (1) {
		// Read joystick values
		uint16_t joystickX = ADC_Read(JOYSTICK_X);
		uint16_t joystickY = ADC_Read(JOYSTICK_Y);

		// Determine movement based on joystick values
		if (joystickX > JOYSTICK_NEUTRAL_HIGH) {
			Move_Forward();
			} else if (joystickX < JOYSTICK_NEUTRAL_LOW) {
			Move_Backward();
			} else if (joystickY > JOYSTICK_NEUTRAL_HIGH) {
			Turn_Right();
			} else if (joystickY < JOYSTICK_NEUTRAL_LOW) {
			Turn_Left();
			} else {
			Stop();  // Stop if joystick is in neutral position
		}

		_delay_ms(100);  // Small delay to debounce
	}
}