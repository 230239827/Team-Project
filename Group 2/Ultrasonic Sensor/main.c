#define F_CPU 20000000UL  // 20 MHz
#include <avr/io.h>
#include <util/delay.h>

// Motor pins (adjust to your wiring)
#define MOTOR1_PIN1 PA0
#define MOTOR1_PIN2 PA1
#define MOTOR2_PIN1 PA2
#define MOTOR2_PIN2 PA3
#define MOTOR3_PIN1 PB0
#define MOTOR3_PIN2 PB1
#define MOTOR4_PIN1 PB2
#define MOTOR4_PIN2 PB3

// Ultrasonic sensor pins
#define TRIGGER_PIN PD4
#define ECHO_PIN PD5
#define BUZZER_PIN PD6

// UART Configuration
#define BAUD 9600
#define MYUBRR (F_CPU / 16 / BAUD - 1)

// Initialize UART
void UART_Init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN0);  // Enable receiver
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Receive UART data
char UART_Receive() {
	while (!(UCSR0A & (1 << RXC0)));  // Wait for data
	return UDR0;
}

// Motor control functions
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

void Stop() {
	PORTA &= ~(1 << MOTOR1_PIN1) & ~(1 << MOTOR1_PIN2);  // Stop Motor 1
	PORTA &= ~(1 << MOTOR2_PIN1) & ~(1 << MOTOR2_PIN2);  // Stop Motor 2
	PORTB &= ~(1 << MOTOR3_PIN1) & ~(1 << MOTOR3_PIN2);  // Stop Motor 3
	PORTB &= ~(1 << MOTOR4_PIN1) & ~(1 << MOTOR4_PIN2);  // Stop Motor 4
}

// Ultrasonic sensor functions
void Trigger() {
	PORTD |= (1 << TRIGGER_PIN);
	_delay_us(10);
	PORTD &= ~(1 << TRIGGER_PIN);
}

uint16_t MeasureDistance() {
	uint16_t duration = 0;

	// Send trigger pulse
	Trigger();

	// Wait for echo pulse to start
	while (!(PIND & (1 << ECHO_PIN)));

	// Measure echo pulse duration
	while (PIND & (1 << ECHO_PIN)) {
		_delay_us(1);
		duration++;
	}

	// Convert duration to distance (in cm)
	return duration / 58;
}

int main(void) {
	// Set motor pins as outputs
	DDRA |= (1 << MOTOR1_PIN1) | (1 << MOTOR1_PIN2) | (1 << MOTOR2_PIN1) | (1 << MOTOR2_PIN2);
	DDRB |= (1 << MOTOR3_PIN1) | (1 << MOTOR3_PIN2) | (1 << MOTOR4_PIN1) | (1 << MOTOR4_PIN2);

	// Set ultrasonic sensor pins
	DDRD |= (1 << TRIGGER_PIN) | (1 << BUZZER_PIN);  // TRIGGER and BUZZER as output
	DDRD &= ~(1 << ECHO_PIN);  // ECHO as input

	// Initialize UART
	UART_Init(MYUBRR);

	// Stop motors initially
	Stop();

	uint16_t duration = 0;
	uint16_t distance = 0;

	while (1) {

		trigger();
		_delay_us(10);
		// Read Bluetooth command
		//char command = UART_Receive();

		// Control motors based on command
		//switch (command) {
			//case 'F': Move_Forward(); break;
			//case 'B': Move_Backward(); break;
			//case 'L': Turn_Left(); break;
			//case 'R': Turn_Right(); break;
			//case 'S': Stop(); break;
			//default: Stop();  // Handle invalid commands
		//}

		// Measure distance using ultrasonic sensor
		// uint16_t distance = MeasureDistance();

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

		// Activate buzzer if obstacle is within 40 cm
		if (distance < 40) {
			PORTD |= (1 << BUZZER_PIN);  // Turn on buzzer
			_delay_ms(200);              // Beep for 200 ms
			PORTD &= ~(1 << BUZZER_PIN); // Turn off buzzer
			} 
			
		else if (distance < 15)
		{
			Stop();
		}
		
		else 
		{
			PORTD &= ~(1 << BUZZER_PIN); // Ensure buzzer is off]
			Move_Forward();
		}

		_delay_ms(100);  // Small delay for stability
	}
}
