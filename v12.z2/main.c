/*
 * main.c
 *
 *  Created on: 06.07.2021.
 *      Author: elena
 */

//NAPOMENA: radi ovo, ali izgleda da usart zdere neke pinove pa se na 7seg ne ispisuje ceo broj
#include "timer0.h"
#include<math.h>
#include "../PLS7shield/PLS7shield.h"
#include "../usart/usart.h"
#include<avr/io.h>
#include<avr/pgmspace.h>
#include <stdlib.h> //za int8_t
#include "timer0.h"

const uint8_t cifre[]={
    0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04, 0x14
  };

uint8_t izracunaj()
{
	uint8_t d=0;
	if(PLS7switchState(7)==0)
		d+=pow(2, 7);
	if(PLS7switchState(6)==0)
		d+=pow(2, 6);
	if(PLS7switchState(5)==0)
		d+=pow(2, 5);
	if(PLS7switchState(4)==0)
		d+=pow(2, 4);
	if(PLS7switchState(3)==0)
		d+=pow(2, 3);
	if(PLS7switchState(2)==0)
		d+=pow(2, 2);
	if(PLS7switchState(1)==0)
		d+=pow(2, 1);
	if(PLS7switchState(0)==0)
		d+=pow(2, 0);
	return d;

}

int main()
{
	usartInit(9600);
	PLS7init();
	PLS7writeDisplay(LEDS, 0xff);

	timer0InteruptInit();
	typedef enum state_t {LENGTH_INIT, ELEMENTS, PRINT, ITER_I, ITER_J} state_t;
	state_t state = LENGTH_INIT;
	uint8_t d;
	uint8_t niz[256];
	char ispis[50];
	uint8_t s;
	uint8_t i;
	uint8_t j;
	uint8_t pom=0;

	while(1)
	{

		switch(state)
		{
		case LENGTH_INIT:
			d=0;
			while(!PLS7buttonState(LEFT)); //ceka levi taster

			d=izracunaj();
			sprintf(ispis, "Duzina: %d", d);
			usartPutString(ispis);

			i=0;
			state=ELEMENTS;
		break;

		case ELEMENTS:
			usartPutString("Elementi: ");
			for(i=0; i<d; i++)
			{
				while(!PLS7buttonState(RIGHT));
				s=0;
				s=izracunaj();
				niz[i]=s;
				sprintf(ispis, "%d", s);
				usartPutString(ispis);
				usartPutString("\r\n");
				timer0DelayMs(1000); //sprecava dzampere
			}

			i=0;
			j=0;
			while(!PLS7buttonState(LEFT));
			timer0DelayMs(1000);
			state=ITER_I;
			break;

		case ITER_I:
			PLS7writeDisplay(LEDS, 0x00); //usart koristi deo pinova pa zato ne svetle sve diode?
			if(i<d)
			{
				state=ITER_J;
			}

			else
			{
				PLS7writeDisplay(LEDS, 0xff);
				i=0;
				state=PRINT;
			}
		break;


		case ITER_J:
			for(j=i+1; j<d; j++)
			{
				if(niz[j]>niz[i])
				{
					pom=niz[i];
					niz[i]=niz[j];
					niz[j]=pom;
				}
			}
			i++;
			state=ITER_I;
		break;

		case PRINT:
			while(i<d)
			{
				PLS7writeDisplay(1, 0xff);
				PLS7writeDisplay(2, 0xff);
				PLS7writeDisplay(3, 0xff);
				pom=niz[i];
				PLS7writeDisplay(4, cifre[pom%10]);

				pom=pom/10;
				if(pom>0)
				{
					PLS7writeDisplay(3, cifre[pom%10]);
					pom=pom/10;

					if(pom>0)
						PLS7writeDisplay(2, cifre[pom%10]);

				}

				i++;
				timer0DelayMs(1000);
			}
			state=LENGTH_INIT;
		break;

		}
	}

	return 0;
}
