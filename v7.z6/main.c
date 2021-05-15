/**
 * @file main.c
 * @brief Eratostenovo sito
 *  Created on: 15.05.2021.
 *      Author: elena
 */

#include"../usart/usart.h"
#include"../timer0_driver/timer0.h"
#include<stdlib.h>
#include<avr/pgmspace.h>
#include<util/delay.h>


int8_t prost(int8_t num)
{
	for(int8_t i = 2; i < num; i++)
	{
		if(num % i == 0)
			return 0;
	}
	return 1;
}

void nums(int8_t num)
{
	int8_t i;
	char pom[15];

	sprintf(pom, "Prosti brojevi do %d su: ", num);
	usartPutString(pom);

	for(i = 2; i <= num; i++)
	{
		if(prost(i))
		{
			sprintf(pom, "Broj %d\r\n", i);
			usartPutString(pom);
		}
	}
}



int main()
{
	usartInit(9600);
	int8_t br = 0;
	timer0InteruptInit();

	while (1)
	{
		usartPutString_P(PSTR("Unesite broj: "));
		while(!usartAvailable());
		timer0DelayMs(100);

		br = usartParseInt();

		nums(br);

	}

	return 0;
}
