/*
 * adc_utils.c
 *
 *  Created on: 29.03.2021.
 *      Author: elena
 */

#include"logic_utils.h"
#include "adc_utils.h"
#include <avr/io.h>

#define SINGLE 6 //sesti bit ADCSRA
#define FREE_RUNNING 5 //peti bit ADCSRA

unsigned char n;

/**- Opis: vrši inicijalizaciju AD konvertora na osnovu prosleðenih parametara
(referentni napon i faktor skaliranja).
- Povratna vrednost: nema povratnu vrednost
*/
void InitADC(unsigned char reference, unsigned char division_factor)
{
	SetVref(reference);
	SetPrescaler(division_factor);
	n = SINGLE;
/** Nisam razumela ovaj deo sa biranjem konverzije, zato sam u f-ju RunConversation
 * dodala parametar n koji se prosledjuje i od kojeg zavisi vrsta konverzije
 */
	SetEnable(1);

}


/**- Opis: vrši inicijalizaciju AD konvertora na osnovu prosleðenih parametara
(referentni napon i faktor skaliranja).
- Povratna vrednost: oèitana vrednost sa izlaza AD konvertora*/
unsigned int ReadADC(unsigned char channel)
{
	SetChannel(channel);
	RunConversion(n);
	while(CheckBit(ADCSRA, 4)!=1)
		;
	if(CheckBit(ADMUX, 5) == 0) //check za ADLAR bit
		return (ShiftLeft(ADCH, 8)) | ADCL; // mozda return (ADCW) umesto cele if petlje?
	else
		return (ShiftLeft(ADCH, 2)) | ADCL;
}


/**- Opis: vrši postavljanje referentnog napona (u okviru ADMUX registra) na osnovu
parametra reference.
- Povratna vrednost: nema povratnu vrednost*/
void SetVref(unsigned char reference)
{
	switch(reference)
	{
		case 0x00: //AREF
			BitmaskClear(ADMUX, 0xC0); //Bit 7:6, tj REFS1:0=00
			break;
		case 0x01: //AVCC
			SetBit(ADMUX, 6); //REFS1:0=01
			ClearBit(ADMUX, 7);
			break;
		default: //0x02 je reserved, ostaje samo 0x03 - internal
			BitmaskSet(ADMUX, 0xC0); //REFS1:0=11
			break;
	}
}


/**- Opis: vrši postavljanje faktora skaliranja (u okviru ADCSRA registra) na osnovu
parametra division_factor.
- Povratna vrednost: nema povratnu vrednost*/
void SetPrescaler(unsigned char division_factor)
{
	switch(division_factor)
	{
		case 2:
			BitmaskClear(ADCSRA, 0x06);
			SetBit(ADCSRA, 0);
			break;
		case 4:
			BitmaskClear(ADCSRA, 0x05);
			SetBit(ADCSRA, 1);
			break;
		case 8:
			BitmaskSet(ADCSRA, 0x03);
			ClearBit(ADCSRA, 3);
			break;
		case 16:
			BitmaskClear(ADCSRA, 0x03);
			SetBit(ADCSRA, 3);
			break;
		case 32:
			BitmaskSet(ADCSRA, 0x05);
			ClearBit(ADCSRA, 1);
			break;
		case 64:
			BitmaskSet(ADCSRA, 0x06);
			ClearBit(ADCSRA, 0);
			break;
		case 128:
			BitmaskSet(ADCSRA, 0x07);
			break;
	}
}


/**- Opis: vrši postavljanje dozvole rada AD konvertora (u okviru ADCSRA registra) na
osnovu parametra enable.
- Povratna vrednost: nema povratnu vrednost*/
void SetEnable(unsigned char enable)
{
	if(enable == 1)
		SetBit(ADCSRA, 7); //ADEN bit
	else
		ClearBit(ADCSRA, 7);
}


/**- Opis: vrši izbor analognog ulaznog kanala AD konvertora (u okviru ADMUX
registra) na osnovu parametra channel.
- Povratna vrednost: nema povratnu vrednost*/
void SetChannel(unsigned char channel)
{
	BitmaskClear(ADMUX, 0x1F); //bit 5 i 4 su uvek na nuli, ostale menjam po potrebi
	switch(channel)
	{
		case 0: //ostaju sve nule
			break;
		case 1: //00001
			SetBit(ADMUX, 0);
			break;
		case 2: //00010
			SetBit(ADMUX, 1);
			break;
		case 3: //00011
			BitmaskSet(ADMUX, 0x03);
			break;
		case 4: //00100
			SetBit(ADMUX, 2);
			break;
		case 5: //00101
			BitmaskSet(ADMUX, 0x05);
			break;
	}
}


/**- Opis: implementira izvršavanje AD konverzije, odnosno njeno pokretanje i èekanje
na njen završetak.
- Povratna vrednost: nema povratnu vrednost*/
void RunConversion(unsigned char n) //u f-ji InitADC stoji objasnjenje za dodatni parametar
{
	SetBit(ADCSRA, n); //ako je 6, bice single conv, ako je 5 bice free running
}

