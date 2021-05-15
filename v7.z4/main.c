/**
 * @filem main.c
 * @author: elena
 */

#include "../usart/usart.h"
#include<avr/pgmspace.h> //za PSTR
#include<stdlib.h>
#include<util/delay.h>


/**
 * Funkcija koja proverava da li su naredni karakteri iznad trenutnog
 * @param str - String koji gledamo
 * @param duz - Duzina stringa
 * @return Vraca 1 ako je dobro, 0 ako nije
 */
int8_t check(char str[], int8_t duz)
{
	int8_t i, j;

	for(i = 0; i < duz; i++) //i je pozicija trenutnog karaktera koji uporedjujemo
	{
		for(j = i; j < duz; j++) //j je pozicija ostalih karaktera sa kojima uporedjujemo
		{
			if(str[i] < str[j]) //ako je neki naredni karakter veci od trenutnog
				return 0;
		}
	}
	return 1;
}

/**
 * Funkcija koja uklanja razmake
 * @param str - String koji gledamo
 * @param duz - Duzina stringa
 * @return Vraca string bez razmaka
 */
void removeBlank(char str[], int8_t duz)
{
	int8_t i, j;
	for(i = 0; i < duz; i++)
	{
		if(str[i] == ' ')
		{
			for(j = i; j < duz; j++)
			{
				str[j] = str[j+1];
			}
			duz--;
		}
	}
}

/**
* Funkcija koja kapitalizuje sva slova
* @param str - String koji gledamo
* @param duz - Duzina stringa
* @return Vraca kapitalizovan string
*/
void capitalise(char str[], int8_t duz)
{
	int8_t i;
	for(i = 0; i < duz; i++)
	{
		if(str[i] >= 'a' && str[i] <= 'z')
			str[i] += 'A' - 'a';
	}
}

int main()
{
	usartInit(9600);
	char unos[64];
	int8_t duzina = 0;

	while(1)
	{
		usartPutString_P(PSTR("Unesite string: \r\n"));
		while(!usartAvailable());
		_delay_ms(100);

		duzina = usartGetString(unos);

		capitalise(unos, duzina);
		removeBlank(unos, duzina);

		//usartPutString("Obradjen string: \r\n");
		//usartPutString(unos);

		if(check(unos, duzina))
			usartPutString_P(PSTR("String jeste sortiran leksikografski\r\n"));
		else
			usartPutString_P(PSTR("String nije sortiran leksikografski\r\n"));

	}
	return 0;
}
