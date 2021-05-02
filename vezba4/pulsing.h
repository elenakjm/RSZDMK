/*
 * pulsing.h
 *
 *  Created on: 28.04.2021.
 *      Author: elena
 */

#ifndef PULSING_H_
#define PULSING_H_

#include "../pin_driver/pin.h"
#include"timer0.h"
#include "utils.h"

#define DIODE_PIN 5

#define FAST 200
#define SLOW 1000

#define FAST_REPETITIONS 15
#define SLOW_REPETITIONS 3

void pinPulse(unsigned char port, unsigned char pin, unsigned long period);
void pinPulsing(unsigned char port, unsigned char pin, unsigned long period, unsigned char num_of_repetitions);



#endif /* PULSING_H_ */
