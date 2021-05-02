/*
 * pulsing.c
 *
 *  Created on: 28.04.2021.
 *      Author: elena
 */

#include "pulsing.h"

void pinPulse(unsigned char port, unsigned char pin, unsigned long period)
{
	// Poluperioda u kojoj pin ima visoku vrednost
	pinSetValue(port, pin, HIGH);
	timer0DelayMs(calculateHalfPeriod(period));
	// Poluperioda u kojoj pin ima nisku vrednost
	pinSetValue(port, pin, LOW);
	timer0DelayMs(calculateHalfPeriod(period));
}
/******************************************************************************************/


void pinPulsing(unsigned char port, unsigned char pin, unsigned long period, unsigned char num_of_repetitions)
{
	unsigned char i;
	for(i=0; i<num_of_repetitions; i++)
		pinPulse(port, pin, period);
}
