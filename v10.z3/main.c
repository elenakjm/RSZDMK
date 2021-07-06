/*
 * main.c
 *
 *  Created on: 05.07.2021.
 *      Author: elena
 */

#include <stdlib.h>
#include<avr/pgmspace.h>
#include<math.h>
#include "../usart/usart.h"
#include <avr/io.h>

#define ITERATIVE 1
#define FORMULA 2

int8_t SumGeo(int16_t first_element, int16_t ratio, int16_t n, int8_t mode)
{
	int16_t i=first_element;
	int16_t suma=0;
	if(mode==ITERATIVE)
	{
		enum pomocna {case1, case2};
		enum pomocna p=case1;

		switch(p)
		{
		case case1:
			if (i<n)
			{
				suma+=i;
				i++;
				usartPutString("A\r\n");
			}
			else
				p=case2;
			break;

		case case2:
			break;
		}
	}

	else if(mode==FORMULA)
	{
		suma=first_element*(1-pow(ratio, n))/(1-ratio);
	}

	return suma;
}

int main()
{
	usartInit(9600);
	int16_t s=SumGeo(1, 2, 3, ITERATIVE);
	for(int i=0; i<s; i++)
	{
		usartPutString("A\r\n");
	}
}

