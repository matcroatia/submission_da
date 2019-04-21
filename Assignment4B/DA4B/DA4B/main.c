/*
 * DA4B.c
 *
 * Created: 4/17/2019 5:02:52 PM
 * Author : Mat Tomljenovic
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void adc_funct(void);
int motor_speed;
int motor_stop = 0;



int main()
{
	DDRD = 0xFB;		//make port D as output
	EIMSK = 0x01;		//enable INT0
	EIFR = 0x01;		//enable interrupt flag 
	EICRA = 0x03;		//set interrupt on rising edge
	TCCR0A= 0x83;		//set timer 0 for fast PWM and clear OCR0A on clear and compare match
	TCCR0B= 0x05;		//set pre-scaler to 1024
	sei();				//enable global interrupts
	adc_funct();			//function declaration
	
	while (1)
	{
		while((ADCSRA &( 1<<ADIF )) == 0);
		motor_speed = ADC*190/800;			//controls speed of the motor
		OCR0A = motor_speed;				//speed is set to change on clear and compare match
		if(motor_stop == 0)
		{
			PORTD = 0x01;					//motor will rotate clockwise
		}
		else
		{
			PORTD = 0x00;					//motor will rotate counter clockwise
		}
		
	}
}
ISR(INT0_vect)
{
	motor_stop ^= 1;			           //toggles motor to stop
}

void adc_funct(void)
{
	ADMUX = 0x40;					//used to enable ADC
	ADCSRA = 0xE7;					//used to start the ADC conversion process
}

