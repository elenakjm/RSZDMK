/*
 * main.c
 *
 *  Created on: 14.05.2021.
 *      Author: elena
 */

#include "../morse/morse.h"

int main()
{
	pinInit(PORT_B, DIODE_PIN, OUTPUT);
	timer0InteruptInit();
	char unos[64] = "ae";

		glavni(PORT_B, DIODE_PIN, unos);

	return 0;
}
