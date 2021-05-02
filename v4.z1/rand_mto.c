/*
 * rand_mto.c
 *
 *  Created on: 01.05.2021.
 *      Author: elena
 */

#include"logic_utils.h"
#include <avr/io.h>
#include "rand_mto.h"

unsigned char exili1, exili2, exili3, n;
unsigned int broj;

/** Opis: vrši inicijalizaciju poèetnog stanja generatora na osnovu parametra seed.
 * Povratna vrednost: nema povratnu vrednost
 */
void InitRand1(unsigned int seed)
{
	broj = seed;
}

/**Opis: vrši generisanje 16-bitnog pseduosluèajnog broja.
 * Povratna vrednost: generisana 16-bitna vrednost
 */
unsigned int Rand1()
{
	n = GenerateNextBit(broj);
	UpdateState(broj, n);

	return broj;
}

/** Opis: vrši generisanje 16-bitnog pseduosluèajnog broja iz intervala min-max.
 *Povratna vrednost: generisana 16-bitna vrednost
 */
unsigned int RandRange1(unsigned int min, unsigned int max)
{
	while(Rand1() < min || Rand1() > max)
	{
		Rand1();
	}
	return broj;
}

/** Opis: vrši generisanje naredne vrednost MSB, na osnovu trenutnog stanja registra.
 * Povratna vrednost: generisana vrednost MSB
*/
unsigned char GenerateNextBit(unsigned int current_state)
{
	exili1 = Xor(CheckBit(current_state, 0), CheckBit(current_state, 2));
	exili2 = Xor(CheckBit(current_state, 3), exili1);
	exili3 = Xor(CheckBit(current_state, 5), exili2);
	return exili3;
}

/**Opis: vrši generisanje novog stanja registra na osnovu trenutnog stanja registra i
nove vrednosti MSB.
 * Povratna vrednost: generisano novo 16-bitno stanje registra
*/
unsigned int UpdateState(unsigned int state, unsigned char bit)
{
	ShiftRight(state, 1);

	if(bit == 1)
		SetBit(state, 15);
	else
		ClearBit(state, 15);
	return state;
}
