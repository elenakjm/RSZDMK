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


/**Funkcija nalazi na kojoj poziciji u unosu se nalazi operacija
 * @param str[] - string unosa
 * @param duz - duzina stringa
 * @return Poziciju operacije u nizu koji je unesen
 */
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

/**Funkcija nalazi na kojoj poziciji u tabeli se se nalazi operacija koja je u stringu
 * @param str[] - string unosa
 * @param duz - duzina stringa
 * @return Poziciju operacije u tabeli operacije[]
 */
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

/**Funkcija koja trazi vrednost izraza
 * @param br1 - prvi broj
 * @param br2 - drugi broj
 * @param op - pozicija na kojoj se nalazi operacija u operacije[] tabeli
 * @return Vrednost izraza
 */
int16_t izracunaj(int8_t op, int16_t br1, int16_t br2)
{
	switch(op)
	{
		case 0: return (br1 + br2); break;
		case 1: return (br1 - br2); break;
		case 2: return (br1 / br2); break;
		default: return (br1 * br2); break;
	}
}

int16_t nadji_brojeve (char str[], int8_t duz)
{
	int8_t i = nadji_gde_je_operacija(str, duz);
	char prvi[10];
	char drugi[10];
	int8_t pom;
	int8_t j = 0;
	int16_t broj1, broj2, racun = 0;
	//char ispis[20];

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

	/**
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
	*/

	//ovo iznad je deo koda za proveru

	racun = izracunaj(nadji_operaciju(str, duz), broj1, broj2);
	return racun;

}

int main()
{
	usartInit(9600);
	char unos[20];
	char ispis[40];
	int8_t duzina = 0;

	while(1)
	{
		usartPutString_P(PSTR("Unesite brojni izraz: \r\n"));
		while(!usartAvailable());
		_delay_ms(100);

		duzina = usartGetString(unos);
		nadji_brojeve(unos, duzina);

		sprintf(ispis, "Vresnost izraza %s je %d\r\n", unos, nadji_brojeve(unos, duzina));
		usartPutString(ispis);
	}

	return 0;
}

