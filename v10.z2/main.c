/*
 * main.c
 *
 *  Created on: 05.07.2021.
 *      Author: elena
 */

#include <stdint.h>
#include <stdlib.h>
#include "../usart/usart.h"
#include "../timer0_2/timer0_2.h"
#include "../pin_driver/pin.h"
#include <util/delay.h>


int main()
{
	usartInit(9600);
	timer0InteruptInit();
	pinInit(PORT_B, 5, OUTPUT);
	char c;
	enum state_t {CF0U, CF1, CF2D, OF2, CF2, CF1U, OF1, CF1D, CF0, OF0};
	enum state_t state=OF0;
	usartPutString("Stanje: OF0\r\n");

	while(1)
	{
		switch(state)
		{
		case OF0:
			while(usartAvailable()==0);
			c=usartGetChar();
			if(c=='U')
			{
				pinSetValue(PORT_B, 5, LOW);
				_delay_ms(1000);
				pinSetValue(PORT_B, 5, HIGH);
				_delay_ms(1000);
				state = CF0U;
				usartPutString("Stanje: CF0U\r\n");
			}
			else
			{
				state=OF0;
				usartPutString("Stanje: OF0\r\n");
			}
			break;

		case CF0U:
			pinSetValue(PORT_B, 5, HIGH);
			state = CF1;
			usartPutString("Stanje: CF1\r\n");
			break;

		case CF1:
			for(int8_t i=0; i<4; i++)
			{
				pinSetValue(PORT_B, 5, LOW);
				_delay_ms(1000);
				pinSetValue(PORT_B, 5, HIGH);
				_delay_ms(1000);
			}
			state = OF1;
			usartPutString("Stanje: OF1\r\n");
			break;

		case OF1:
			while(usartAvailable()==0);
			c=usartGetChar();
			if(c=='U')
			{
				pinSetValue(PORT_B, 5, LOW);
				_delay_ms(1000);
				pinSetValue(PORT_B, 5, HIGH);
				_delay_ms(1000);
				state = CF1U;
				usartPutString("Stanje: CF1U\r\n");
			}
			else if(c=='D')
			{
				pinSetValue(PORT_B, 5, LOW);
				_delay_ms(1000);
				pinSetValue(PORT_B, 5, HIGH);
				_delay_ms(1000);
				state=CF1D;
				usartPutString("Stanje: CF1D\r\n");
			}
			else
				state=OF1;
				usartPutString("Stanje: OF1\r\n");
			break;

		case CF1D:
			pinSetValue(PORT_B, 5, HIGH);
			state = CF0;
			usartPutString("Stanje: CF0\r\n");
			break;

		case CF0:
			for(int8_t i=0; i<4; i++)
			{
				pinSetValue(PORT_B, 5, LOW);
				_delay_ms(1000);
				pinSetValue(PORT_B, 5, HIGH);
				_delay_ms(1000);
			}
			state = OF0;
			usartPutString("Stanje: OF0\r\n");
			break;

		case CF1U:
			pinSetValue(PORT_B, 5, HIGH);
			state = CF2;
			usartPutString("Stanje: CF2\r\n");
			break;

		case CF2:
			for(int8_t i=0; i<4; i++)
			{
				pinSetValue(PORT_B, 5, LOW);
				_delay_ms(1000);
				pinSetValue(PORT_B, 5, HIGH);
				_delay_ms(1000);
			}
			state = OF2;
			usartPutString("Stanje: OF2\r\n");
			break;

		case OF2:
			while(usartAvailable()==0);
			c=usartGetChar();
			if(c=='D')
			{
				pinSetValue(PORT_B, 5, LOW);
				_delay_ms(1000);
				pinSetValue(PORT_B, 5, HIGH);
				_delay_ms(1000);
				state = CF2D;
				usartPutString("Stanje: CF2D\r\n");
			}
			else
			{
				state=OF2;
				usartPutString("Stanje: OF2\r\n");
			}
			break;

		case CF2D:
			pinSetValue(PORT_B, 5, HIGH);
			state = CF1;
			usartPutString("Stanje: CF1\r\n");
			break;

		}

	}
}
