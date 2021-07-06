/*
 * main.c
 *
 *  Created on: 06.07.2021.
 *      Author: elena
 */

#include "../timer0_driver/timer0.h"
#include "../PLS7shield/PLS7shield.h"

void door_open(uint8_t sprat)
{
	PLS7writeDisplay(sprat, 0x1f);
	for(int i=1; i<5; i++)
	{
		if(i!=sprat)
			PLS7writeDisplay(i, 0xff);
	}
}

void door_close(uint8_t sprat)
{
	PLS7writeDisplay(sprat, 0x1e);
	for(int i=1; i<5; i++)
	{
		if(i!=sprat)
			PLS7writeDisplay(i, 0xff);
	}
}

void leds_on()
{
	PLS7writeDisplay(LEDS, 0x00);
}

void leds_off()
{
	PLS7writeDisplay(LEDS, 0x55);
}

uint8_t switch_low()
{
	if(PLS7switchState(0)==1 && PLS7switchState(1)==1) //oba neaktivna
		return 1;
	else if(PLS7switchState(0)==0 && PLS7switchState(1)==1) //prvi aktivan
		return 2;
	else if(PLS7switchState(0)==1 && PLS7switchState(1)==0) //drugi aktivan
		return 3;
	else
		return 4;
}

int main()
{
	timer0InteruptInit();
	PLS7init();
	PLS7writeDisplay(LEDS, 0xff);

	enum state_t {F4O, F4C, F3O, F3C, F2O, F2C, F1O, F1C, FM};
	enum state_t state = F1O;
	door_open(1);
	leds_on();

	uint8_t current_floor = 0;
	uint8_t target_floor = 0;
	uint8_t pom=0; //pomocna za preskoke

	while(1)
	{
		switch(state)
		{
		case F1O:
			current_floor = 1;
			target_floor = 1;
			if(pom==0 && PLS7buttonState(LEFT))
			{
				pom=1;
				state=F1C;
				leds_off();
				door_close(1);
			}

			else
				state=F1O;
			if(!PLS7buttonState(LEFT) && !PLS7buttonState(RIGHT) && !PLS7buttonState(UP) && !PLS7buttonState(DOWN))
			{
				pom=0;
			}
			break;


		case F1C:
			if(pom==0 && PLS7buttonState(RIGHT))
			{
				pom=1;

				if(switch_low()==1)
				{
					leds_on();
					door_open(1);
					state=F1O;
				}

				else
				{
					target_floor=switch_low();
					state=FM;
				}
			}

			else
				state=F1C;

			if(!PLS7buttonState(LEFT) && !PLS7buttonState(RIGHT) && !PLS7buttonState(UP) && !PLS7buttonState(DOWN))
			{
				pom=0;
			}
			break;


		case FM:
			//ne pise da treba da se penje sprat po sprat sa zatvorenim vratima
			//po njihovom crtezu se samo popne na sprat i otvori vrata
			//ali ovo je logicnije
			//tako da mozda ne treba da se pisu sve ove funkcije
			if(current_floor<target_floor)
			{
				while(current_floor!=target_floor)
				{
					leds_on();
					current_floor++;
					timer0DelayMs(1000);
					door_close(current_floor);
				}
			}

			else
			{
				while(current_floor!=target_floor)
				{
					leds_on();
					current_floor--;
					timer0DelayMs(1000);
					door_close(current_floor);
				}
			}

			door_open(current_floor);

			if(target_floor == 1)
				state=F1O;
			if(target_floor == 2)
				state=F2O;
			if(target_floor == 3)
				state=F3O;
			if(target_floor == 4)
				state=F4O;
			break;


		case F2O:
			current_floor = 2;
			target_floor = 2;
			if(pom==0 && PLS7buttonState(LEFT))
			{
				pom=1;
				state=F2C;
				leds_off();
				door_close(2);
			}

			else
				state=F2O;
			if(!PLS7buttonState(LEFT) && !PLS7buttonState(RIGHT) && !PLS7buttonState(UP) && !PLS7buttonState(DOWN))
			{
				pom=0;
			}
			break;


		case F2C:
			if(pom==0 && PLS7buttonState(RIGHT))
			{
				pom=1;

				if(switch_low()==2)
				{
					leds_on();
					door_open(2);
					state=F2O;
				}

				else
				{
					target_floor=switch_low();
					state=FM;
				}
			}

			else
				state=F2C;

			if(!PLS7buttonState(LEFT) && !PLS7buttonState(RIGHT) && !PLS7buttonState(UP) && !PLS7buttonState(DOWN))
			{
				pom=0;
			}
			break;


		case F3O:
			current_floor = 3;
			target_floor = 3;
			if(pom==0 && PLS7buttonState(LEFT))
			{
				pom=1;
				state=F3C;
				leds_off();
				door_close(3);
			}

			else
				state=F3O;
			if(!PLS7buttonState(LEFT) && !PLS7buttonState(RIGHT) && !PLS7buttonState(UP) && !PLS7buttonState(DOWN))
			{
				pom=0;
			}
			break;


		case F3C:
			if(pom==0 && PLS7buttonState(RIGHT))
			{
				pom=1;

				if(switch_low()==3)
				{
					leds_on();
					door_open(3);
					state=F3O;
				}

				else
				{
					target_floor=switch_low();
					state=FM;
				}
			}

			else
				state=F3C;

			if(!PLS7buttonState(LEFT) && !PLS7buttonState(RIGHT) && !PLS7buttonState(UP) && !PLS7buttonState(DOWN))
			{
				pom=0;
			}
			break;


		case F4O:
			current_floor = 4;
			target_floor = 4;
			if(pom==0 && PLS7buttonState(LEFT))
			{
				pom=1;
				state=F4C;
				leds_off();
				door_close(4);
			}

			else
				state=F4O;
			if(!PLS7buttonState(LEFT) && !PLS7buttonState(RIGHT) && !PLS7buttonState(UP) && !PLS7buttonState(DOWN))
			{
				pom=0;
			}
			break;


		case F4C:
			if(pom==0 && PLS7buttonState(RIGHT))
			{
				pom=1;

				if(switch_low()==4)
				{
					leds_on();
					door_open(4);
					state=F4O;
				}

				else
				{
					target_floor=switch_low();
					state=FM;
				}
			}

			else
				state=F4C;

			if(!PLS7buttonState(LEFT) && !PLS7buttonState(RIGHT) && !PLS7buttonState(UP) && !PLS7buttonState(DOWN))
			{
				pom=0;
			}
			break;
		}
	}

	return 0;
}
