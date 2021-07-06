/*
 * PLS7shield.h
 *
 *  Created on: 24.05.2021.
 *      Author: elena
 */

#ifndef PLS7SHIELD_H_
#define PLS7SHIELD_H_

#include <avr/io.h>

void PLS7init();
#define LEDS 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4

void PLS7writeDisplay(uint8_t display, uint8_t value);
uint8_t PLS7readDisplay(uint8_t display);

#define LEFT 0
#define DOWN 1
#define RIGHT 2
#define UP 3

uint8_t PLS7buttonState(uint8_t button);

#define S1 7
#define S2 6
#define S3 5
#define S4 4
#define S5 3
#define S6 2
#define S7 1
#define S8 0

uint8_t PLS7readSwitches();
uint8_t PLS7switchState(uint8_t sw);


#endif /* PLS7SHIELD_H_ */
