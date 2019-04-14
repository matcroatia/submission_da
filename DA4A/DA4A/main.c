/*
 * DA4A.c
 *
 * Created: 4/13/2019 7:35:14 PM
 * Author : Mat Tomljenovic
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void adc_func(void);				  // initializing void function
int motor_spin;							  // constant for controlling motor spin
int	motor = 0;							  // const for motor on/off
int main(void)
{
	DDRD = 0x40;							// enable port D as output
	DDRC = 0x02;						    // enable port C as output
	PORTC |= (1 << PINC4) | (1 << PINC0);	// enable pin 4 and pin 0 as inputs
	TCCR0A= 0x03;							// set fast PWM and clear overflow flag register on match
	TCCR0B= 0x05;						    // set pre-scaler to 1024
	PCICR = 0x02;							// enable PCIE1 
	PCMSK1 = 0x02;							// enable pin changes
	sei();									// enable global interrupts
	adc_func();						// initializes the ADC
	
	while (1)
	{																	
	}
}
ISR(PCINT1_vect)
{
	if(!(PINC & (1<<PINC1)))				// if button is pressed then activate motor for spin selection
	{
		if(motor == 0)						// if button is pressed the motor will stop
		{
			OCR0A = 0;						// register used to stop motor
			_delay_ms(1000);				// delay used to prevent debouncing
		}
		if (motor == 1)						// if button is pressed motor will turn on
		{
			while((ADCSRA&(1<<ADIF))==0);	// loop used to convert ADC
			motor_spin = ADC;				// set motor_spint to ADC value
			OCR0A = motor_spin;				// the motor vale is loaded into ORR0A register
			_delay_ms(1000);				// mdelay used to prevent debouncing
		}
			motor ^= 1;							// used to toggle motor 
	}
}

void adc_func(void) 					// function used for ADC
{
	ADMUX = ( 0 << REFS1);				    // used to enable ADC
	ADCSRA = 0xE7;						    // used to start conversion process
}


