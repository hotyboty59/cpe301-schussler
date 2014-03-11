// Daniel Schussler // CpE 301

#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>

int main(void) {

	char counter = 0x00; 
	PORTB = 0xFF;	 // Make port B an output	 
	PORTD = 0X00;	 // Make port D an input 
	TCNTn = 0x00;	 // timer and counter register
	while (1) {
		for (int i = 0; i < 10; i++) {
			if (i = 2
			 {
				sei(); 
				INT0_vect = 1;
			}	
			PORTD |= (1 << 0);				// make last bit one 
			delay_ms(250);					// .25 second delay, going up
			PORTD &= (1 << 0);				// make last bit zero
			counter++; delay_ms(250);		// .25 second delay
		
	}