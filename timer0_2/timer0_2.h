/*
 * timer0_2.h
 *
 *  Created on: 13.05.2021.
 *      Author: elena
 */

#ifndef TIMER0_2_H_
#define TIMER0_2_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void timer0InteruptInit();

uint32_t timer0millis();

void timer0DelayMs(uint32_t delay_length);




#endif /* TIMER0_2_H_ */
