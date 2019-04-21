/*
 * DA4B2.c
 *
 * Created: 4/18/2019 5:40:39 PM
 * Author : Mat Tomljenovic
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void adc_funct(void);
int motor_rotate;

int main(void)
{
	DDRD = 0xFF;			//enable port D as output
	TCCR0A = 0x83;			//set timer 0 for fast PWM and clear OCR0A on clear and compare match
	TCCR0B = 0x05;			//set pre-scaler to 1024
	adc_funct();			//function declaration
	while (1)
	{
		while((ADCSRA & ( 1<<ADIF )) == 0); //while motor is on
		motor_rotate = (ADC /33 +1);		//rotate motor 180 degrees
		OCR0A = motor_rotate;				//set rotate on clear and match register
		
	}
}

void adc_funct(void)
{
	ADMUX = ADMUX = 0x40;					//used to enable ADC;

	ADCSRA = 0xEF;
}

