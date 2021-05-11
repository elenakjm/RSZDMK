/*
 * @file main.c
 * @brief Konvertor decimalnog u heksa
 * @author: elena
 */

#include "../usart/usart.h"
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include<avr/pgmspace.h>
#include<stdio.h>
#define max_hex 16

void konvertuj(int16_t broj)
{
	char hex[max_hex];
	int16_t pomocna = 0;
	int8_t i = 0;

	while(broj != 0)
	{
		pomocna = broj % 16; //ostatak pri deljenju sa 16

		if(pomocna < 10)
			hex[i] = pomocna + '0'; //da predje u char
		else
			hex[i]= pomocna + 55; //da dobijemo A u ascii

		i += 1;
		broj = broj / 16;
	}

	usartPutString_P(PSTR("Uneli ste broj 0x"));
	for(int j = i - 1; j >= 0; j--) //stampamo od nazad
	{
		usartPutChar(hex[j]);
	}
	usartPutString_P(PSTR("\r\n"));
}

int main()
{
	usartInit(9600);
	char unos[20];
	int16_t broj_d = 0;
	//char broj_h[max_hex];
	char pom[60];

	while(1)
	{
		usartPutString_P(PSTR("Unesite decimalan broj: \r\n"));
		while(!usartAvailable());
		_delay_ms(100);

		usartGetString(unos);
		sscanf(unos, "%d", &broj_d);
		sprintf(pom, "Unesen je broj %d\r\n", broj_d);
		usartPutString(unos);

		konvertuj(broj_d);

	}

	return 0;
}
