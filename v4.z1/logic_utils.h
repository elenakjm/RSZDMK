/*
 * logic_utils.h
 *
 *  Created on: 29.03.2021.
 *      Author: elena
 */

#ifndef LOGIC_UTILS_H_
#define LOGIC_UTILS_H_

/**
* Opis: vr�i postavljanje bita na vrednost 1, na poziciji bit_num, u okviru 16-bitne promenljive reg
* Povratna vrednost: modifikovana vrednost promenljive reg
*/
unsigned int SetBit(unsigned int reg, unsigned char bit_num);

/**
 * Opis: vr�i postavljanje bita na vrednost 0, na poziciji bit_num, u okviru 16-bitne promenljive reg
 * Povratna vrednost: modifikovana vrednost promenljive reg
 */
unsigned int ClearBit(unsigned int reg, unsigned char bit_num);


/**
 * Opis: vr�i postavljanje bita na suprotnu vrednost od postoje�e, na poziciji bit_num, u
okviru 16-bitne promenljive reg
 * Povratna vrednost: modifikovana vrednost promenljive reg
 */
unsigned int ToggleBit(unsigned int reg, unsigned char bit_num);


/**
 * Opis: vr�i proveru vrednosti bita, na poziciji bit_num, u okviru 16-bitne promenljive
reg
 * Povratna vrednost: vrednost bita na datoj poziciji (0 ili 1)
 */
unsigned int CheckBit(unsigned int reg, unsigned char bit_num);


/**
 * Opis: vr�i postavljanje grupe bita na vrednost 1, specificiranih u promenljivoj mask,
u okviru 16-bitne promenljive reg
 * Povratna vrednost: modifikovana vrednost promenljive reg
 */
unsigned char BitmaskSet(unsigned char reg, unsigned char mask);

/**
 * Opis: vr�i postavljanje grupe bita na vrednost 0, specificiranih u promenljivoj mask,
u okviru 16-bitne promenljive reg
 * Povratna vrednost: modifikovana vrednost promenljive reg
 */
unsigned char BitmaskClear(unsigned char reg, unsigned char mask);


/**
 * Opis: vr�i bitsku negaciju 16-bitne promenljive input
 * - Povratna vrednost: rezultat operacije
 */
unsigned int Not(unsigned int input);


/**
 * Opis: vr�i bitsku i operaciju nad 16-bitnim promenljivima input1 i input2
 * Povratna vrednost: rezultat operacije
 */
unsigned int And(unsigned int input1, unsigned int input2);


/**
 * Opis: vr�i bitsku ili operaciju nad 16-bitnim promenljivima input1 i input2
 *  Povratna vrednost: rezultat operacije
 */
unsigned int Or(unsigned int input1, unsigned int input2);


/**
 * Opis: vr�i bitsku eks-ili operaciju nad 16-bitnim promenljivima input1 i input2
 * Povratna vrednost: rezultat operacije
 */
unsigned int Xor(unsigned int input1, unsigned int input2);


/**
 * Opis: vr�i pomeranje (eng. shift) ulazne promenljive input u levo za
num_of_shifts mesta.
 * Povratna vrednost: rezultat operacije
 */
unsigned int ShiftLeft(unsigned int input, unsigned int num_of_shifts);


/**
 * Opis: vr�i pomeranje (eng. shift) ulazne promenljive input u desno za num_of_shifts mesta.
 * Povratna vrednost: rezultat operacije
 */
unsigned int ShiftRight(unsigned int input, unsigned int num_of_shifts);


#endif /* LOGIC_UTILS_H_ */
