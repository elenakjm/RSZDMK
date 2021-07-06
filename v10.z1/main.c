/*
 * main.c
 *
 *  Created on: 05.07.2021.
 *      Author: elena
 */


#include <stdint.h>
#include "../usart/usart.h"
#include "../timer0_2/timer0_2.h"
#include "../pin_driver/pin.h"

int main()
{
	usartInit(9600);
	timer0InteruptInit();
	pinInit(PORT_B, 5, OUTPUT);

	enum state_t {LOCKED, NUM1, NUM2, UNLOCKED, BROKEN, REC1, REC2};
	enum state_t state=LOCKED;
	pinSetValue(PORT_B, 5, LOW);
	int8_t c;

	while(1)
	{
		while(usartAvailable()==0);
		c=usartGetChar();

		switch(state)
		{

		case LOCKED:
			if(c=='1')
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(2000);
				pinSetValue(PORT_B, 5, LOW);
				state=NUM1;
			}
			else
			{
				pinSetValue(PORT_B, 5, HIGH);
				state=BROKEN;
			}
			break;

		case NUM1:
			if(c=='2')
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(2000);
				pinSetValue(PORT_B, 5, LOW);
				state=NUM2;
			}
			else
			{
				pinSetValue(PORT_B, 5, HIGH);
				state=BROKEN;
			}
			break;

		case NUM2:
			if(c=='3')
			{
				for(int8_t i=0; i<3; i++)
				{
					pinSetValue(PORT_B, 5, HIGH);
					timer0DelayMs(2000);
					pinSetValue(PORT_B, 5, LOW);
					timer0DelayMs(2000);
				}
				state=UNLOCKED;
			}
			else
			{
				pinSetValue(PORT_B, 5, HIGH);
				state=BROKEN;
			}
			break;

		case UNLOCKED:
			break;

		case BROKEN:
		{
			if(c=='7')
			{
				pinSetValue(PORT_B, 5, LOW);
				timer0DelayMs(2000);
				pinSetValue(PORT_B, 5, HIGH);
				state=REC1;
			}

			else
			{
				for(int8_t i=0; i<2; i++)
				{
					pinSetValue(PORT_B, 5, LOW);
					timer0DelayMs(2000);
					pinSetValue(PORT_B, 5, HIGH);
					timer0DelayMs(2000);
				}
				state=BROKEN;
			}
			break;
		}

		case REC1:
		{
			if(c=='8')
			{
				pinSetValue(PORT_B, 5, LOW);
				timer0DelayMs(2000);
				pinSetValue(PORT_B, 5, HIGH);
				state=REC2;
			}

			else
			{
				for(int8_t i=0; i<2; i++)
				{
					pinSetValue(PORT_B, 5, LOW);
					timer0DelayMs(2000);
					pinSetValue(PORT_B, 5, HIGH);
					timer0DelayMs(2000);
				}
				state=BROKEN;
			}
			break;
		}

		case REC2:
		{
			if(c=='9')
			{
				pinSetValue(PORT_B, 5, LOW);
				timer0DelayMs(2000);
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(2000);
				pinSetValue(PORT_B, 5, LOW);
				state=LOCKED;
			}

			else
			{
				for(int8_t i=0; i<2; i++)
				{
					pinSetValue(PORT_B, 5, LOW);
					timer0DelayMs(2000);
					pinSetValue(PORT_B, 5, HIGH);
					timer0DelayMs(2000);
				}
				state=BROKEN;
			}
			break;
		}

		}
	}
}
