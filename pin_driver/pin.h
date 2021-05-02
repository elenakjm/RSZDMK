/*
 * pin.h
 *
 *  Created on: 29.03.2021.
 *      Author: elena
 */

#include <avr/io.h>
#ifndef PIN_H_
#define PIN_H_

/// Makro za podesavanje visoke vrednosti signala na pinu
#define HIGH 1
/// Makro za podesavanje niske vrednosti signala na pinu
#define LOW 0
/// Makro za podesavanje izlaznog smera pina
#define OUTPUT 1
/// Makro za podesavanje ulaznog smera pina
#define INPUT 0
/// Makro za selektovanje porta B
#define PORT_B 0
/// Makro za selektovanje porta C
#define PORT_C 1
/// Makro za selektovanje porta D
#define PORT_D 2
/// Makro za selektovanje pina na koji je povezana dioda
#define DIODE_PIN 5

void pinSetValue(unsigned char port, unsigned char pin, unsigned char value);
void pinInit(unsigned char port, unsigned char pin, unsigned char direction);



#endif /* PIN_H_ */
