/*
 * main.c
 *
 *  Created on: 24.05.2021.
 *      Author: elena
 */

#include "../PLS7shield/PLS7shield.h"

int main()
{
	PLS7init();
	while(1)
	{
		PLS7writeDisplay(LEDS, PLS7readSwitches());
		if (PLS7buttonState(LEFT))
			PLS7writeDisplay(D1, 0x0c);
		else
			PLS7writeDisplay(D1, 0xfe);
		if (PLS7buttonState(DOWN))
			PLS7writeDisplay(D2, 0xa4);
		else
			PLS7writeDisplay(D2, 0xfe);
		if (PLS7buttonState(RIGHT))
			PLS7writeDisplay(D3, 0x27);
		else
			PLS7writeDisplay(D3, 0xfe);
		if (PLS7buttonState(UP))
			PLS7writeDisplay(D4, 0xc4);
		else
			PLS7writeDisplay(D4, 0xfe);
	}
	return 0;
}
