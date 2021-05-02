/*
 * rand_otm.c
 *
 *  Created on: 02.05.2021.
 *      Author: elena
 */

#include"logic_utils.h"
#include "rand_otm.h"

#define levo 1
#define desno 2

unsigned char direction;
unsigned int broj;
unsigned int exili1, exili2, exili3, pom;

/** Opis: vrši inicijalizaciju poèetnog stanja generatora na osnovu parametra seed.
 * Povratna vrednost: nema povratnu vrednost
*/
void InitRand2(unsigned int seed)
{
	broj = seed;
}

/** Opis: vrši postavljanje orijentacije – leve ili desne (na ulazu se oèekuje 0 ili 1 za
desnu, odnosno levu orijentaciju, respektivno)
* Povratna vrednost: nema povratnu vrednost
*/
void SetDirection(unsigned char dir)
{
	direction = dir;
}

/** Opis: vrši generisanje 16-bitnog pseduosluèajnog broja.
* Povratna vrednost: generisana 16-bitna vrednost
*/
unsigned int Rand2()
{
	ShiftAndToggle(broj, direction);

	return broj;
}

/** Opis: vrši generisanje 16-bitnog pseduosluèajnog broja iz intervala min-max
 * Povratna vrednost: generisana 16-bitna vrednost
 */
unsigned int RandRange2(unsigned int min, unsigned int max)
{
	while(Rand2() < min || Rand2() > max)
	{
		Rand2();
	}
	return broj;
}

/** Opis: vrši izdvajanje vrednosti LSB trenutnog stanja registra.
* Povratna vrednost: izdvojena vrednost LSB
*/
unsigned char GetLSB(unsigned int state)
{
	return CheckBit (state, 0);
}

/** Opis: vrši izdvajanje vrednosti MSB trenutnog stanja registra.
* Povratna vrednost: izdvojena vrednost MSB
*/
unsigned char GetMSB(unsigned int state)
{
	return CheckBit (state, 15);
}

/** Opis: vrši generisanje novog stanja na osnovu trenutnog stanja registra i nove
vrednosti LSB(u sluèaju desne orijentacije) i MSB(u sluèaju leve orijentacije).
* Povratna vrednost: nema povratnu vrednost
*/
unsigned int ShiftAndToggle(unsigned int state, unsigned char bit)
{
	if(bit == levo) //nisam sigurna sta je bit, pa sam stavila da je direction
	{
		pom = GetMSB(state);
		exili1 = Xor(CheckBit(state, 1), pom);
		exili2 = Xor(CheckBit(state, 2), pom);
		exili3 = Xor(CheckBit(state, 4), pom);

		ShiftLeft(state, 1);
		pomocna(exili1, state, 2);
		pomocna(exili2, state, 3);
		pomocna(exili3, state, 5);
		pomocna(pom, state, 0);
	}

	else
	{
		pom = GetLSB(state);
		exili1 = Xor(CheckBit(state, 14), pom);
		exili2 = Xor(CheckBit(state, 13), pom);
		exili3 = Xor(CheckBit(state, 11), pom);

		ShiftRight(state, 1);
		pomocna(exili1, state, 13);
		pomocna(exili2, state, 12);
		pomocna(exili3, state, 10);
		pomocna(pom, state, 15);
	}
	return state; //pise da nema povratnu, ali je funkcija tipa unsigned int, valjda vraca ovo?
}

void pomocna(unsigned int rez, unsigned int state, unsigned char bit_num)
{
	if(rez == 1)
		SetBit(state, bit_num);
	else
		ClearBit(state, bit_num);
}
