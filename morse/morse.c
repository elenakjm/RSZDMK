/*
 * @file morse.c
 * @brief biblioteka za morzeov kod
 * @date 13.05.2021.
 * @author elena
 */


#include "morse.h"

///Broj slova
#define broj_slova 26

///Look up tabela sa slovima
const int64_t slova[broj_slova] PROGMEM ={
		0000000000011101, 0000000101010111, 0000010111010111,
		0000000001010111, 0000000000000001, 0000000101110101, 0000000101110111,
		0000000001010101, 0000000000000101, 0001110111011101, 0000000111010111,
		0000000101011101, 0000000001110111, 0000000000010111, 0000011101110111,
		0000010111011101, 0001110101110111, 0000000001011101, 0000000000010101,
		000000000000111, 0000000001110101, 0000000111010101, 0000000111011101,
		0000011101010111, 0001110111010111, 0000010101110111};

///Look up tabela koja govori koliko bitova citamo iz svakog slova
const int8_t num_bits[broj_slova] PROGMEM = {
		5, 9, 11, 7, 1, 9, 9, 7, 3, 13, 9, 9, 7, 5, 11, 11, 13, 7, 5, 3, 7, 9, 9, 11, 13, 11
};


/***********************************************************************************/
void pinSetValue(unsigned char port, unsigned char pin, unsigned char value)
{
	// Postavljanje vrednosti pina
	switch(port)
	{ case PORT_B:
		if (value == HIGH)
			PORTB |= 1 << pin;
		else
			PORTB &= ~(1 << pin);
		break;
	case PORT_C:
		if (value == HIGH)
			PORTC |= 1 << pin;
		else
			PORTC &= ~(1 << pin);
		break;
	case PORT_D:
		if (value == HIGH)
			PORTD |= 1 << pin;
		else
			PORTD &= ~(1 << pin);
		break;
	default:
		break;
	}
}

/******************************************************************************************/
void pinInit(unsigned char port, unsigned char pin, unsigned char direction)
{
	// Inicijalizacija smera pina
	switch(port)
	{ case PORT_B:
		if (direction == OUTPUT)
			DDRB |= 1 << pin;
		else
			DDRB &= ~(1 << pin);
		break;
	case PORT_C:
		if (direction == OUTPUT)
			DDRC |= 1 << pin;
		else
			DDRC &= ~(1 << pin);
		break;
	case PORT_D:
		if (direction == OUTPUT)
			DDRD |= 1 << pin;
		else
			DDRD &= ~(1 << pin);
		break;
	default:
		break;
	}
}

/***********************************************************************************/
/**
 * letter_num - funkcija koja trazi na kojoj poziciji u tabeli se nalazi slovo
 * @return vraca poziciju slova u tabeli
 */
int8_t letter_num(char x)
{
	int8_t i = 0; //promenljiva koja govori na kojoj poziciji u tabeli je slovo
	char slovo;
	slovo = 'A';

	if(x >= 'a' && x <= 'z') //petlja za mala slova
	{
		x += 'A' - 'a'; //prebacujemo sve u velika slova
		while(x != slovo)
		{
			slovo++; //uzimamo sledece slovo
			i++;
		}
	}

	else if(x >= 'A' && x <= 'Z') //petlja za velika slova
		{
			while(x != slovo)
			{
				slovo++;
				i++;
			}
		}

	else if(x == ' ')
		i = 30; //vraca 30 ako je razmak

	else
		i = 31; //vraca 31 ako nije nasao karakter

	return i;
}


/***********************************************************************************/
void glavni(unsigned char port, unsigned char pin, char unos[])
{
	int8_t duzina = strlen(unos); //duzina unosa
	int8_t i, j, pom1, pom2 = 0;

	for(i = 0; i < duzina; i++) //ocitava slovo po slovo
	{
		pom1 = letter_num(unos[i]);

		if(pom1 == 31) //ako je razmak
		{
			pulsing(port, pin, LOW, 4); //4 a ne 7 kao sto je trazeno jer na kraju imamo jos 3 pauze
		}

		else if(pom1 == 31) //ako nije ni razmak ni slovo
		{
			pinSetValue(port, pin, LOW); //ne znam sta drugo da stavim
		}

		else //ako je slovo
		{
			for(j = 0; j < num_bits[pom1]; j++) //ocitava bit po bit slova
			{
				pom2 = get_bit(slova[pom1], j); //trazi vrednost bita
				blink(port, pin, pom2); //pali ili gasi diodu
			}
		}

		pulsing(port, pin, LOW, 3); //pauza izmedju 2 slova
	}
}

/***********************************************************************************/
/**
 * get_bit - trazi bit u slovu na odredjenoj poziciji
 * @return vraca int8_t vrednost bita
 */
int8_t get_bit(int64_t letter, int8_t pozicija)
{
	if (letter == (letter | (1 << pozicija)))
		return 1;
	else
		return 0;
}

/***********************************************************************************/
/**
 * blink - pali ili gasi diodu na 0.3ms
 * @param port - ulaz tipa unsigned char - Port na kojem je pin koji je potrebno inicijalizovati
 * @param pin - ulaz tipa unsigned char - Pin koji je potrebno inicijalizovati
 * @value - vrednost 0 ili 1
 */
void blink(unsigned char port, unsigned char pin, int8_t value)
{
	pinSetValue(port, pin, value);

	timer0DelayMs(300); //trajanje 0.3ms

}

/***********************************************************************************/
/**
 * pulsing - Funkcija koja odredjeni period drzi diodu ugasenom
 * koristi se kod pauze izmedju dva slova i dve reci
 * @return nema povratnu vrednost
 */
void pulsing(unsigned char port, unsigned char pin, unsigned char value, int8_t repetition)
{
	int8_t i;
	for(i = 0; i < repetition; i++)
	{
		pinSetValue(port, pin, value);
		timer0DelayMs(300);
	}
}
