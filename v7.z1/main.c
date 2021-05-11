/**
 * @file	main.h
 * @brief	Aplikacija za logovanje
 * @author	Stojkovski Elena
 */

#include "../usart/usart.h"
#include <util/delay.h>
#include <stdlib.h>
#include<avr/pgmspace.h>
#define duz_ime 7
#define pass 9

int8_t tacno (char str1[], char str2[], int8_t duz1, int8_t duz2)
{
	int8_t i;

	if (duz1 != duz2)
		return 0;

	for(i = 0; i < duz1; i++)
	{
		if(str1[i] != str2[i])
		{
			return 0;
		}
	}

	return 1;
}

int main()
{
	usartInit(9600);
	char pom [60];
	char ime [duz_ime]="MyName";
	char sifra [pass]="P@ssw0rd";
	int8_t provera = 0;
	int8_t duzina = 0;

	while(1)
	{
		usartPutString_P(PSTR("Unesite korisnicko ime: \r\n"));
		while (usartAvailable() == 0);
		_delay_ms(100);

		duzina = usartGetString(pom);
		pom[duzina] = '\0';

		provera = tacno(ime, pom, duzina+1, duz_ime);

		if(provera == 1)
		{
			usartPutString_P(PSTR("Unesite lozinku: \r\n"));
			while (usartAvailable() == 0);
			_delay_ms(100);

			duzina = usartGetString(pom);
			pom[duzina] = '\0';

			provera = tacno (sifra, pom, duzina+1, pass);

			if(provera == 1)
			{
				usartPutString_P(PSTR("Dobrodosao/la "));
				usartPutString(ime);
				usartPutString_P(PSTR("\r\n"));
			}

			else
				usartPutString_P(PSTR("Logovanje neuspesno \r\n"));
		}

		else
		{
			usartPutString_P(PSTR("Logovanje neuspesno \r\n"));
		}

	}

	return 0;
}


