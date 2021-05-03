#include "../usart/usart.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int main()
{
	char ime[64], string[128];
	usartInit(9600);

	while(1)
	{
		usartPutString("Unesite svoje ime i prezime:\r\n");
		while(!usartAvailable())
			;
		_delay_ms(50);

		usartGetString(ime);
		sprintf(string, "Zdravno, %s :)\r\n", ime);
		usartPutString(string);

	}

	return 0;
}
