/*
 * main.c
 *
 *  Created on: 30.05.2021.
 *      Author: elena
 */

#include "../PLS7shield/PLS7shield.h"
#include<util/delay.h>

const uint8_t cifre[]={
    0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04
  };

int main()
{
	PLS7init();
	PLS7writeDisplay(LEDS, PLS7readSwitches());
	_delay_ms(50);
	uint8_t pozicija = 1;
	uint8_t br = 1;
	uint8_t pls;
	uint8_t pom = 0;

	while(1)
	{
		if (PLS7buttonState(LEFT) && pom == 0)
		{
			pom = 1;
			pozicija = 1;
		}

		if (PLS7buttonState(DOWN) && pom == 0)
		{
			pom = 1;
			pozicija = 4;
		}

		if (PLS7buttonState(RIGHT) && pom == 0)
		{
			pom = 1;
			pozicija = 3;
		}

		if (PLS7buttonState(UP) && pom == 0)
		{
			pom = 1;
			pozicija = 2;
		}


		pls = PLS7readSwitches();
		switch(pls)
		{
			case 0xfe:
				br = 8;
				break;
			case 0xfd:
				br = 7;
				break;
			case 0xfb:
				br = 6;
				break;
			case 0xf7:
				br = 5;
				break;
			case 0xef:
				br = 4;
				break;
			case 0xdf:
				br = 3;
				break;
			case 0xbf:
				br = 2;
				break;
			case 0x7f:
				br = 1;
				break;
			default:
				br = 0;
				break;
		}



		if(!PLS7buttonState(UP) && !PLS7buttonState(RIGHT) && !PLS7buttonState(DOWN) && !PLS7buttonState(LEFT))
		{
			if(pom == 1)
			{
				//PLS7writeDisplay(LEDS, PLS7readSwitches());
				PLS7writeDisplay(pozicija, cifre[br]);
				_delay_ms(50);
				PLS7writeDisplay(LEDS, PLS7readSwitches());
			}
			pom = 0;
		}



	}

	return 0;
}
