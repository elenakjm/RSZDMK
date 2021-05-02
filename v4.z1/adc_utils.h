/*
 * adc_utils.h
 *
 *  Created on: 29.03.2021.
 *      Author: elena
 */

#ifndef ADC_UTILS_H_
#define ADC_UTILS_H_


/**- Opis: vr�i inicijalizaciju AD konvertora na osnovu prosle�enih parametara
(referentni napon i faktor skaliranja).
- Povratna vrednost: nema povratnu vrednost*/
void InitADC(unsigned char reference, unsigned char division_factor);


/**- Opis: vr�i inicijalizaciju AD konvertora na osnovu prosle�enih parametara
(referentni napon i faktor skaliranja).
- Povratna vrednost: o�itana vrednost sa izlaza AD konvertora*/
unsigned int ReadADC(unsigned char channel);


/**- Opis: vr�i postavljanje referentnog napona (u okviru ADMUX registra) na osnovu
parametra reference.
- Povratna vrednost: nema povratnu vrednost*/
void SetVref(unsigned char reference);


/**- Opis: vr�i postavljanje faktora skaliranja (u okviru ADCSRA registra) na osnovu
parametra division_factor.
- Povratna vrednost: nema povratnu vrednost*/
void SetPrescaler(unsigned char division_factor);


/**- Opis: vr�i postavljanje dozvole rada AD konvertora (u okviru ADCSRA registra) na
osnovu parametra enable.
- Povratna vrednost: nema povratnu vrednost*/
void SetEnable(unsigned char enable);


/**- Opis: vr�i izbor analognog ulaznog kanala AD konvertora (u okviru ADMUX
registra) na osnovu parametra channel.
- Povratna vrednost: nema povratnu vrednost*/
void SetChannel(unsigned char channel);


/**- Opis: implementira izvr�avanje AD konverzije, odnosno njeno pokretanje i �ekanje
na njen zavr�etak.
- Povratna vrednost: nema povratnu vrednost*/
void RunConversion(unsigned char n);


#endif /* ADC_UTILS_H_ */
