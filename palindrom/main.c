/**
 * @file	main.c
 * @brief	Palindrom
 * @author	Hocu da umrem
 */

#include <string.h>
#include "../usart/usart.h"
#include<util/delay.h>
#include<avr/pgmspace.h>
#include <stdint.h>

int main ()
{
	char rec [64];
	int duzina;
	usartInit(9600);
	char jeste = 1;

	while(1)
	{
		usartPutString("Unesite rec: \r\n");
		while(!usartAvailable());
		_delay_ms(100);

		usartGetString(rec);
		usartPutString_P(PSTR("Unesena rec "));
		usartPutString(rec);

		for (duzina = 0; rec[duzina] != '\0'; duzina ++);
		for(int i = 0; i < (duzina / 2); i ++)
		{
			if(rec[i] != rec[duzina-1-i])
				jeste = 0;
		}

		if(jeste == 1)
			usartPutString_P(PSTR(" jeste palindrom\r\n"));
		else
			usartPutString_P(PSTR(" nije palindrom\r\n"));
	}

	return 0;

}
