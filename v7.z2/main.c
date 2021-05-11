/*
 * @file main.c
 * @brief broj samoglasnika
 * @author: elena
 */

#include "../usart/usart.h"
#include<util/delay.h>
#include<avr/pgmspace.h>
#include <stdlib.h>
#include <avr/io.h>

const char samoglasnici[] = {
		'a', 'e', 'i', 'o', 'u'
};

int8_t proveri(char string[], int8_t duzina)
{
	int8_t broj = 0;
	int8_t i, j;

	for(i = 0; i < duzina; i++)
	{
		for(j = 0; j < 5; j++)
		{
			if(string[i] == samoglasnici[j])
				broj++;
		}
	}
	return broj;
}

int main()
{
	usartInit(9600);
	char tmp[60];
	char unos[20];
	int8_t duzina = 0;
	int8_t broj = 0;

	while(1)
	{
		usartPutString_P(PSTR("Unesite rec: \r\n"));
		while(!usartAvailable());
		_delay_ms(100);

		duzina = usartGetString(unos);
		broj = proveri(unos, duzina);

		sprintf(tmp, "Rec ima %d samoglasnika\r\n", broj);
		usartPutString(tmp);
	}

	return 0;
}


