/**
 * @file morse.h
 * @brief Biblioteka koja realizuje morzeov kod
 * @date 13-05-2021
 * @author elena
 */

#ifndef MORSE_H_
#define MORSE_H_

#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/io.h>
#include <stdlib.h> //int8_t
#include<avr/pgmspace.h> //PSTR
#include <avr/io.h> //sprintf
#include<string.h> //za strlen
#include "timer0.h"

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

/**
 * pinSetValue - Funkcija koja postavlja vrednost na pinu
 * @param port - ulaz tipa unsigned char - Port na kojem je pin ciju vrednost potrebno postaviti
 * @param pin - ulaz tipa unsigned char - Pin ciju je vrednost potrebno postaviti
 * @param value - ulaz tipa unsigned char - Vrednost koju je potrebno postaviti na pin
 * @return Nema povratnu vrednost
 */
void pinSetValue(unsigned char port, unsigned char pin, unsigned char value);

/**
 * pinInit - Funkcija koja implementiran inicijalizaciju pina
 * @param port - ulaz tipa unsigned char - Port na kojem je pin koji je potrebno inicijalizovati
 * @param pin - ulaz tipa unsigned char - Pin koji je potrebno inicijalizovati
 * @param direction - ulaz tipa unsigned char - Smer prema kojem je potrebno inicijalizovati pin
 * @return Nema povratnu vrednost
 */
void pinInit(unsigned char port, unsigned char pin, unsigned char direction);

/**
 * letter_num - funkcija koja trazi na kojoj poziciji u tabeli se nalazi slovo
 * @param x - slovo ciju poziciju trazimo
 * @return vraca poziciju slova u tabeli
 */
int8_t letter_num(char x);

/**
 * glavni - Glavna funkcija programa koja spaja sve sporedne
 * @param port - ulaz tipa unsigned char - Port na kojem je pin koji je potrebno inicijalizovati
 * @param pin - ulaz tipa unsigned char - Pin koji je potrebno inicijalizovati
 * @param unos - string koji se koristi
 * @return Nema povratnu vrednost
 */
void glavni(unsigned char port, unsigned char pin, char unos[]);

/**
 * blink - pali ili gasi diodu na 0.3ms
 * @param port - ulaz tipa unsigned char - Port na kojem je pin koji je potrebno inicijalizovati
 * @param pin - ulaz tipa unsigned char - Pin koji je potrebno inicijalizovati
 * @value - vrednost 0 ili 1
 */
void blink(unsigned char port, unsigned char pin, int8_t value);

/**
 * get_bit - trazi bit u slovu na odredjenoj poziciji
 * @param letter - slovo koje nam treba
 * @param pozicija - na kojoj poziciji u slovu se nalazi bit
 * @return vraca int8_t vrednost bita
 */
int8_t get_bit(int64_t letter, int8_t pozicija);

/**
 * pulsing - Funkcija koja odredjeni period drzi diodu ugasenom
 * koristi se kod pauze izmedju dva slova i dve reci
 * @param port - ulaz tipa unsigned char - Port na kojem je pin koji je potrebno inicijalizovati
 * @param pin - ulaz tipa unsigned char - Pin koji je potrebno inicijalizovati
 * @return nema povratnu vrednost
 */
void pulsing(unsigned char port, unsigned char pin, unsigned char value, int8_t repetition);

#endif /* MORSE_H_ */
