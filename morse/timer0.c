/*
 * timer0.c
 *
 *  Created on: 13.05.2021.
 *      Author: elena
 */


#include "timer0.h"

/// Sistemsko vreme
volatile uint32_t ms = 0;

/**
 * ISR - prekidna rutina tajmera 0 u modu CTC
 */
ISR(TIMER0_COMPA_vect)
{
	ms++;
}

/**
 * timer0InteruptInit - Funkcija koja inicijalizuje timer 0 tako da pravi prekide
 * svake milisekunde
 * @return Nema povratnu vrednost
 */
void timer0InteruptInit()
{
	TCCR0A = 0x02; // tajmer 0: CTC mod

	// Provera frekvencije takta prilikom kompilacije
	#if F_CPU > 20000000
	#error "Frekvencija takta mora biti manja od 20MHz!"
	#endif

	// Inicijalizacija promenljivih za preskaler i periodu tajmera 0
	uint32_t n = F_CPU / (1000/3); //treba nam 3 milisekunde
	uint8_t clksel = 1;
	// Odredjivanje vrednosti preskalera i periode tajmera 0
	while (n > 255){
		n /= 8;
		clksel++;
	}
	TCCR0B = clksel; // tajmer 0: Podesavanje preskalera
	OCR0A = (uint8_t)(n & 0xff) - 1; // tajmer 0: Podesavanje periode
	TIMSK0 = 0x02; // tajmer 0: Dozvola prekida
	sei(); // Globalna dozvola prekida
}

/**
 * timer0millis - Funkcija koja bezbedno vraca kao povratnu vrednost broj
milisekundi
 * proteklih od pocetka merenja vremena
 * @return Povratna vrednost je tipa uint32_t i ima vrednost broja
milisekundi
 * proteklih od pocetka merenja vremena
 */
uint32_t timer0millis()
{
	uint32_t tmp;
	cli(); // Zabrana prekida
	tmp = ms; // Ocitavanje vremena
	sei(); // Dozvola prekida
	return tmp;
}

/**
 * timer0DelayMs - Funkcija koja implementira pauzu u broju milisekundi koji
je prosledjen kao parametar
 * @param delay_length - ulaz tipa uint32_t - Duzina pauze u milisekundama
 * @return Povratna vrednost je tipa unsigned long i ima vrednost broja
milisekundi
 * proteklih od pocetka aplikacije do trenutka izlaska iz funkcije
 */
void timer0DelayMs(uint32_t delay_length)
{
	uint32_t t0 = timer0millis();
	while(timer0millis() - t0 < delay_length);
}
