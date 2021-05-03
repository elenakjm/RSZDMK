#define DIODE_PIN 5
#include "../pin_driver/pin.h"
#include "../timer0_driver/timer0.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

void pinPulse(unsigned char port, unsigned char pin, unsigned long period);
void pinPulsing(unsigned char port, unsigned char pin, unsigned long period, unsigned char num_of_repetitions);

int main()
{
	// Inicijalizacija
	pinInit(PORT_B, DIODE_PIN, OUTPUT);
	timer0InteruptInit();
	// Glavna petlja
	while (1)
	{
		pinPulsing(PORT_B, DIODE_PIN, 300, 5);
		pinPulsing(PORT_B, DIODE_PIN, 2000, 5);
		while(1)
			;
	}
	return 0;
}


void pinPulse(unsigned char port, unsigned char pin, unsigned long period)
{
		for (int i = 0; i <= 255; i++)
		{
			analogWrite(DIODE_PIN, i);
				    _delay_ms(10);
		}
		//pinSetValue(port, pin, HIGH);
		timer0DelayMs(period/2);
		pinSetValue(port, pin, LOW);
		timer0DelayMs(period/2);
}

void pinPulsing(unsigned char port, unsigned char pin, unsigned long period, unsigned char num_of_repetitions)
{
	unsigned char i;
	for(i=0; i<num_of_repetitions; i++)
		pinPulse(port, pin, period);
}
