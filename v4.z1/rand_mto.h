/*
 * rand_mto.h
 *
 *  Created on: 01.05.2021.
 *      Author: elena
 */

#ifndef RAND_MTO_H_
#define RAND_MTO_H_

void InitRand1(unsigned int seed);
unsigned int Rand1();
unsigned int RandRange1(unsigned int min, unsigned int max);
unsigned char GenerateNextBit(unsigned int current_state);
unsigned int UpdateState(unsigned int state, unsigned char bit);

#endif /* RAND_MTO_H_ */
