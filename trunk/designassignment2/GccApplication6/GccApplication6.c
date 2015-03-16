/*
 * GccApplication6.c
 *
 * Created: 3/15/2015 10:10:30 PM
 *  Author: Daniel schussler
 */ 


#define F_CPU 2000000UL   		// 2 mega hertz
#include <avr/io.h>
#include <util/delay.h>

int main ()
{

	int  x = 0;			// counter for rising edge of waveform
	int i = 0;			// interrupt counter
	DDRB 1 << 4;		// PB4 is output
	DDRB 1 << 5;		// PB5 is output
	PORTB &= ~ (1<<5);
	MCUCSR = $40;		// setting int2 to activate on the rising edge
	sei (); 			// enable interrupts

	while (1)
	{
		TNCT0 = 206
		TCCR0 = 0x01;

		while (TIFR & 0x01) == 0)
		{
			x++;
		}

		TCCR0 = 0;				// stop timer0

		TIFR = 1<< TOV0;			// clear the tov0 flag
		PORTB = PORTB ^ (1<<5);	// clear portb 5

	}

	ISR (INT2_vect) 		// isr for external interrupt 2
	{
		PORTB ^= (1<<4);		// toggle portb 4
	}