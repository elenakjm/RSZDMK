/*
 * @file main.c
 * @brief Racunanje vrednosti izraza
 * @author: elena
 */

#include "../usart/usart.h"
#include<util/delay.h> //za delay
#include <stdlib.h> //za int8_t
#include<avr/pgmspace.h> //za PSTR
#include <avr/io.h> //za sprintf

char operacije[] = {
		'+', '-', '/', '*'
};

int8_t nadji_gde_je_operacija (char str[], int8_t duz)
{
	int8_t i, j;

	for(i = 0; i < duz; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(str[i] == operacije[j])
				return (duz - i - 1);
		}
	}
	return 0;
}

int8_t nadji_operaciju(char str[], int8_t duz)
{
	int8_t i, j;

	for(i = 0; i < duz; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(str[i] == operacije[j])
				return j;
		}
	}
	return 0;
}

void nadji_brojeve (char str[], int8_t duz)
{
	int8_t i = nadji_gde_je_operacija(str, duz);
	char prvi[10];
	char drugi[10];
	int8_t pom;
	int8_t j = 0;
	int16_t broj1, broj2 = 0;
	char ispis[20];

	for(pom = (duz - i); pom <= duz; pom++)
	{
		drugi[j] = str[pom];
		j++;
	}

	for(pom = 0; pom < (duz - i); pom++)
	{
		prvi[pom] = str[pom];
	}

	broj1 = atoi(prvi);
	broj2=atoi(drugi);

	sprintf(ispis, "Prvi %d", broj1);
	usartPutString(ispis);
	sprintf(ispis, ", drugi %d", broj2);
	usartPutString(ispis);
	usartPutString("\r\n");
	sprintf(ispis, "Operacija je na poziciji %d \r\n", i);
	usartPutString(ispis);
	usartPutString("Operacija je ");
	usartPutChar(operacije[nadji_operaciju(str, duz)]);
	usartPutString("\r\n");

}

int main()
{
	usartInit(9600);
	char unos[20];
	int8_t duzina = 0;

	while(1)
	{
		usartPutString_P(PSTR("Unesite brojni izraz: \r\n"));
		while(!usartAvailable());
		_delay_ms(100);

		duzina = usartGetString(unos);
		nadji_brojeve(unos, duzina);
	}

	return 0;
}

