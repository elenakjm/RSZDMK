/**
 * main.c
 *
 *  Created on: 17.05.2021.
 *      Author: elena
 */

#include <stdint.h>
#include "../usart/usart.h"
#include "../timer0_2/timer0_2.h"
#include "../pin_driver/pin.h"
int main()
{
	pinInit(PORT_B, 5, OUTPUT);
	timer0InteruptInit();
	usartInit(115200);

	int8_t c;
	int8_t key[] = "123"; //potrebna je duzina od 4 zbog null karaktera
	int16_t cnt = 0;
	pinSetValue(PORT_B, 5, LOW);
	while(1)
	{
		while(usartAvailable() == 0);
		c = usartGetChar();

		if (c == key[cnt])
		{
			pinSetValue(PORT_B, 5, HIGH);
			timer0DelayMs(1000);
			pinSetValue(PORT_B, 5, LOW);
			cnt++;
			if(cnt == 3)
			{
				for(int i = 0; i < 2; i++)
				{
					timer0DelayMs(1000);
					pinSetValue(PORT_B, 5, HIGH);
					timer0DelayMs(1000);
					pinSetValue(PORT_B, 5, LOW);
				}
				//akcija otkljucavanja...
				while(1);
			}
		} else
		{
			pinSetValue(PORT_B, 5, HIGH);
			while(1);
		}
	} return 0;
}
