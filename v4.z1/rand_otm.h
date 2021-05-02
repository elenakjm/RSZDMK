/*
 * rand_otm.h
 *
 *  Created on: 02.05.2021.
 *      Author: elena
 */

#ifndef RAND_OTM_H_
#define RAND_OTM_H_

void InitRand2(unsigned int seed);
void SetDirection(unsigned char dir);
unsigned int Rand2();
unsigned int RandRange2(unsigned int min, unsigned int max);
unsigned char GetLSB(unsigned int state);
unsigned char GetMSB(unsigned int state);
unsigned int ShiftAndToggle(unsigned int state, unsigned char bit);
void pomocna(unsigned int rez, unsigned int state, unsigned char bit_num);

#endif /* RAND_OTM_H_ */
