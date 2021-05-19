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


void removeNum(int8_t pozicija, int8_t duz, int8_t nums[])
{
	for(int8_t i = pozicija; i < duz; i++)
	{
		nums[i] = nums[i+1];
	}
}

int8_t proveri(int8_t num, int8_t nums[])
{
	int8_t i, j;
	for(i = 0; i <= (num - 1); i++)
	{
		for(j = i + 1; j <= (num - 1); j++)
		{
			if(nums[j] % i == 0)
			{
				removeNum(j, num, nums);
				num--;
			}
		}
	}
	return num;
}

void unesi(int8_t num, int8_t nums[])
{
	int8_t i;
	for(i = 2; i <= num; i++)
	{
		nums[i-2] = i;
	}
}


int main()
{
	usartInit(9600);
	int8_t br = 0;
	timer0InteruptInit();
	int8_t nova_duz = 0;
	char pom[20];

	while (1)
	{
		usartPutString_P(PSTR("Unesite broj: "));
		while(!usartAvailable());
		timer0DelayMs(100);

		br = usartParseInt();

		int8_t brojevi[br];
		unesi(br, brojevi);
		nova_duz = proveri(br, brojevi);

		usartPutString_P(PSTR("Prosti su: \r\n"));
		for(int8_t i = 0; i < nova_duz; i++)
		{
			sprintf(pom, "%d ", brojevi[i]);
			usartPutString(pom);
		}

	}

	return 0;
}
