/*
 * main.c
 *
 *  Created on: 24.05.2021.
 *      Author: elena
 */

#include "../PLS7shield/PLS7shield.h"
#include <util/delay.h>

const uint8_t cifre[]={
    0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04, 0x14
  };

int main()
{
	PLS7init();
	PLS7writeDisplay(LEDS, PLS7readSwitches());
	_delay_ms(50);
	uint8_t pozicija = 1; //D ide od 1 do 4
	uint8_t broj = 0;
	uint8_t pom = 0;

	for(int i = 1; i < 5; i++)
	{
		PLS7writeDisplay(i, cifre[0]);
	}

	while(1)
	{

		if (PLS7buttonState(LEFT) && pom == 0)
		{
			pom = 1;

			if (pozicija == 1)
				pozicija = 4;
			else
				pozicija --;
		}

		if (PLS7buttonState(DOWN) && pom == 0)
		{
			pom = 1;

			if (broj == 0)
				broj = 9;
			else
				broj --;
		}

		if (PLS7buttonState(RIGHT) && pom == 0)
		{
			pom = 1;

			if (pozicija == 4)
				pozicija = 1;
			else
				pozicija ++;
		}

		if (PLS7buttonState(UP) && pom == 0)
		{
			pom = 1;

			if (broj == 9)
				broj = 0;
			else
				broj ++;
		}

		if(!PLS7buttonState(UP) && !PLS7buttonState(RIGHT) && !PLS7buttonState(DOWN) && !PLS7buttonState(LEFT))
		{
			pom = 0;
		}


		PLS7writeDisplay(pozicija, cifre[broj]);
		_delay_ms(50);
	}

	return 0;
}
