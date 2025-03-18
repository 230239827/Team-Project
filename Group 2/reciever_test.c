#define F_CPU 20E6
#include <avr/io.h>
#include <avr/io.h>
#include <util/delay.h>

char UART_Buffer[30];
int ADC_Result = 0;

#define Baud_Rate 115200UL
#define Baud_Register_Value ((F_CPU/(16*Baud_Rate)) - 1)
char Receive_data()
{
	while((UCSR0A & 1<<RXC0)==0); // Waits for register to be empty
	return UDR0 ;
}

void Receive_string(char String[])
{
	uint8_t String_Length = strlen(String); // obtain String's length
	for (uint8_t Index = 0; Index < String_Length; Index++) // Loop through the string
	{
		Receive_data(String[Index]); // Transmits a chararcter
	}

}

int main(void)
{
	
	UBRR0 = Baud_Register_Value;
	UCSR0B = 1<<RXEN0 ;
	UCSR0C = 1<<UCSZ01 | 1<< UCSZ00;
	/* Replace with your application code */
	while (1)
	{
		
		sprintf(UART_Buffer, "ADC Result =%d\r" ,ADC_Result );
		ADC_Result++;
		if (ADC_Result > 15)
		{
			ADC_Result = 0;
		}
		else { ADC_Result = ADC_Result;}
		_delay_ms(500);
		
		}
	}
}

