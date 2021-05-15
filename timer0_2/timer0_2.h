/**
 * @file timer0_2.h
 * @author elena
 */

#ifndef TIMER0_2_H_
#define TIMER0_2_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

/**
 * timer0InteruptInit - Funkcija koja inicijalizuje timer 0 tako da pravi prekide
 * svake milisekunde
 * @return Nema povratnu vrednost
 */
void timer0InteruptInit();

/**
 * timer0millis - Funkcija koja bezbedno vraca kao povratnu vrednost broj
milisekundi
 * proteklih od pocetka merenja vremena
 * @return Povratna vrednost je tipa uint32_t i ima vrednost broja
milisekundi
 * proteklih od pocetka merenja vremena
 */
uint32_t timer0millis();

/**
 * timer0DelayMs - Funkcija koja implementira pauzu u broju milisekundi koji je prosledjen
 * kao parametar
 * @param delay_length - ulaz tipa unsigned long - Duzina pauze u milisekundama
 * @return Povratna vrednost je tipa unsigned long i ima vrednost broja milisekundi
 * proteklih od pocetka aplikacije do trenutka izlaska iz funkcije
 */
void timer0DelayMs(uint32_t delay_length);




#endif /* TIMER0_2_H_ */
