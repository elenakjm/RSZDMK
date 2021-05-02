/*
 * timer0.h
 *
 *  Created on: 29.03.2021.
 *      Author: elena
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * timer0DelayMs - Funkcija koja implementira pauzu u broju milisekundi koji je prosledjen
 * kao parametar
 * @param delay_length - ulaz tipa unsigned long - Duzina pauze u milisekundama
 * @return Povratna vrednost je tipa unsigned long i ima vrednost broja milisekundi
 * proteklih od pocetka aplikacije do trenutka izlaska iz funkcije
 */

unsigned long timer0DelayMs(unsigned long delay_length);
/**
 * timer0InteruptInit - Funkcija koja inicijalizuje timer 0 tako da pravi prekide
 * svake milisekunde
 * @return Nema povratnu vrednost
 */
void timer0InteruptInit();
/**
 * main - funkcija koja implementiran glavni deo aplikacije
 * @return Nema povratnu vrednost
 */



#endif /* TIMER0_H_ */
