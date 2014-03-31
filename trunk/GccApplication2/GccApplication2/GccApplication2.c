// Daniel Schussler
// CpE 301
// mid term


#include <avr/io.h>
#include <avr/interrupt.h>

#define MOSI 3
#define SCK 5
#define SS 2

void usart_init ();
void tcnt_init ();
void display_seg ();
void calculate (unsigned char command_int, unsigned char info);

int f;	// temperature in Fahrenheit
char diget_one;
char diget_two;

int main(void)
{
	DDRB = (1<<MOSI) | (1<<SCK) | (1<<SS);	// outputs for max7221 converter
	DDRD = 1;			// output PD0 to test
	DDRC = 0;			// PC0 for analog
	int temp;			// for combining high and low converted values
	
	ADCSRA = 0x87;			// ADC enable with select prescaler of 64
	ADMUX = 0xC0;			// 1.1 V reference and ADC0 left justified
	
	usart_init();			// initialize USART for serial output
	tcnt_init();			// initialize tcnt1 timer
	
	while (1)
	{
		ADCSRA |= (1 << ADSC);				// starting conversion
		while ((ADCSRA & (1 << ADIF)) == 0);		// wait for finish
		temp = ADCL + (ADCH * 256);			// put together for one integer
		f = ((temp * 1.1) / 1024) * 180 + 32;		// convert into Fahrenheit
	}
}

void display_seg()
{
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);	// enable SPI as master
	
	calculate (0x09, 0b00000011);	// decoding for digits 0 and 1
	
	calculate (0x0B, 0x02);		// display the digits 0 and 1
	calculate (0x0C, 0x01);		// flip on chip
	calculate (0x01, diget_one);	// display first digit (0)
	calculate (0x02, diget_two);	// display second digit (1)
}

void calculate (unsigned char command_int, unsigned char info)
{
	PORTB &= ~(1<<SS); 			// initialize packet
	
	SPDR = command_int;			// start command transmission
	while (!(SPSR & (1<<SPIF)));		// wait for finish
	
	SPDR = info;				// start info transmission
	while (!(SPSR & (1<<SPIF)));		// wait for finish
	
	PORTB |= (1<<SS);			// end packet
}


void usart_init ()
{
	UCSR0B = 0x08;				// enable transmitter
	UCSR0C = 0x06;				// enable 8-bit character size
	UBRR0L = 0x33;				// set baud rate
}


void usart_send (unsigned char ch)
{
	while (!(UCSR0A & (1<<UDRE0)));		// wait until ready to send
	UDR0 = ch;				// send value over serial
}

ISR (TIMER1_OVF_vect)
{
	char output[3];
	PORTD = PORTD ^ 1;		// toggle test PD0 led
	itoa (f,output,10);		// convert temperature to string for USART output
	switch(output[0])
	{
		case '0':	diget_one = 0x00;
		break;
		case '1':	diget_one = 0x01;
		break;
		case '2':	diget_one = 0x02;
		break;
		case '3':	diget_one = 0x03;
		break;
		case '4':	diget_one = 0x04;
		break;
		case '5':	diget_one = 0x05;
		break;
		case '6':	diget_one = 0x06;
		break;
		case '7':	diget_one = 0x07;
		break;
		case '8':	diget_one = 0x08;
		break;
		case '9':	diget_one = 0x09;
		break;
		default:	diget_one = 0x00;
		break;
	}
	switch(output[1])
	{
		case '0':	diget_two = 0x00;
		break;
		case '1':	diget_two = 0x01;
		break;
		case '2':	diget_two = 0x02;
		break;
		case '3':	diget_two = 0x03;
		break;
		case '4':	diget_two = 0x04;
		break;
		case '5':	diget_two = 0x05;
		break;
		case '6':	diget_two = 0x06;
		break;
		case '7':	diget_two = 0x07;
		break;
		case '8':	diget_two = 0x08;
		break;
		case '9':	diget_two = 0x09;
		break;
		default:	diget_two = 0x00;
		break;
	}

	display_seg();			// output Fahrenheit temperature to seven segment displays
	usart_send (output[0]);		// send first digit of Fahrenheit temperature to serial
	usart_send (output[1]);		// send second digit of Fahrenheit temperature to serial
	usart_send ('\n');		// send new line to serial
	TCNT1=0x85EE;			// reset TCNT to one second delay
}

void tcnt_init()
{
	// TIMER1 Delays
	// 1       second  = 0x85EE
	// 500 mil seconds = 0xC2F7
	// 250 mil seconds = 0xE17C
	// 125 mil seconds = 0xF0BE
	// 63  mil seconds = 0xF85F

	TCNT1 = 0x85EE;			// one second delay
	TCCR1A = 0x00;			// normal mode
	TCCR1B = 0x04;			// Normal mode with a prescaler of 256
	TIMSK1 = 0x01;			// enable interrupt on timer1 for overflow
	sei();					// enable global interrupts
}