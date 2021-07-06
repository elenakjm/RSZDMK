/*
 * main.c
 *
 *  Created on: 05.07.2021.
 *      Author: elena
 */

#include "../PLS7shield/PLS7shield.h"
#include<util/delay.h>
#include<math.h>
#include"../usart/usart.h"

const uint8_t cifre[]={
    0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04, 0x14
  };

int main()
{
	PLS7init();
	PLS7writeDisplay(LEDS, PLS7readSwitches());
	_delay_ms(50);

	for(int i = 1; i < 5; i++)
	{
		PLS7writeDisplay(i, 0xff);
	}

	while(1)
	{

			uint8_t p1, p2, p3=0;
			uint8_t s=0;

			if(PLS7switchState(7)==0)
				s+=pow(2, 7);
			if(PLS7switchState(6)==0)
				s+=pow(2, 6);
			if(PLS7switchState(5)==0)
				s+=pow(2, 5);
			if(PLS7switchState(4)==0)
				s+=pow(2, 4);
			if(PLS7switchState(3)==0)
				s+=pow(2, 3);
			if(PLS7switchState(2)==0)
				s+=pow(2, 2);
			if(PLS7switchState(1)==0)
				s+=pow(2, 1);
			if(PLS7switchState(0)==0)
				s+=pow(2, 0);

			p1=s%10; //ispisi poslednju cifru na displej 4
			PLS7writeDisplay(4, cifre[p1]);

			s=s/10;
			if(s>0)
			{
				p2=(s)%10;
				PLS7writeDisplay(3, cifre[p2]); //ispisi drugu cifru na displej 3
			}
			else
				PLS7writeDisplay(3, 0xff); //ispisi nista

			s=s/10;
			if(s>0)
			{
				p3=(s)%10;
				PLS7writeDisplay(2, cifre[p3]);
			}
			else
				PLS7writeDisplay(2, 0xff);

			//brojevi nikad nece ici do 1000+ pa nam prvi disp ne treba

	}

	return 0;
}

