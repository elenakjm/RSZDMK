/*
 * main.c
 *
 *  Created on: 03.05.2021.
 *      Author: elena
 */
#include "../usart/usart.h"
#include "adc_utils.h"
#include<stdio.h>

int main()
{
	//char string[128];

	InitADC(1, 64);
	unsigned int izlaz = ReadADC(0);
	//System.out.println(izlaz);

	return izlaz;
}
