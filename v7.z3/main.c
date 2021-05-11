/*
 * @file main.c
 * @brief Suma cifara
 * @author: elena
 */

#include"../usart/usart.h"
#include<avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include<stdio.h>
#include <avr/io.h>

int16_t saberi (int16_t num)
{
	int16_t sum = 0;
	int8_t broj = 0;

	while(num != 0)
	{
		broj = num % 10;
		sum += broj;
		num = num / 10;
	}
	return sum;
}

int main()
{
	usartInit(9600);
	char unos[20];
	int16_t suma = 0;
	int16_t broj = 0;
	char pom[60];

	while(1)
	{
		usartPutString_P(PSTR("Unesite ceo broj: \r\n"));
		while(!usartAvailable());
		_delay_ms(100);

		usartGetString(unos);
		broj = atoi(unos);
		sprintf(pom, "Konvertovano: %d\r\n", broj);
		usartPutString(pom);

		suma = saberi(broj);
		sprintf(pom, "Zbir cifara iznosi %d\r\n", suma);
		usartPutString(pom);


	}
	return 0;
}
