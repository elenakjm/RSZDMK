/**
 * @file main.c
 * @brief Zadatak koji implementira logovanje
 * @author elena
 */

#include "../usart/usart.h"
#include <stdlib.h> //int8_t
#include<util/delay.h>
#include<avr/pgmspace.h> //PSTR
#include <avr/io.h> //sprintf
#include<string.h> //za strlen

///Makro za max velicinu stringa
#define max_name 32
///Makro za max duzinu sifre
#define max_pass 3
///Makro za max broj korisnika
#define br_korisnika 5

///Baza podataka sa korisnicima
char korisnici[br_korisnika][32]=
{
		"Hocu da umrem",
		"Zasto upisah ovo",
		"Cao kako si",
		"Ime Prezime",
		"Nisam Kreativna",
};

///Baza podataka sa siframa
char pin[br_korisnika][4] = {"1234", "6666", "4545", "0101", "7531"};

/**
 * Funkcija koja uporedjuje da li su imena korisnika ista
 * @param str1 - Ime prvog korisnika
 * @param str2 - Ime koje se prosledjuje iz baze
 * @param duz1 - Duzina imena prvog
 * @param duz2 - Duzina imena drugog
 * @return Vraca 1 ako su isti ili 0 ako nisu
 */
int8_t uporedi_korisnike(char str1[], char str2[], int8_t duz1, int8_t duz2)
{
	int8_t i;
	int8_t tacno = 1;

	if(duz1 != duz2)
		tacno = 0;
	for(i = 0; i < duz1; i++)
	{
		if(str1[i] != str2[i])
			tacno = 0;
	}
	return tacno;
}

/**
 * Funkcija koja proverava da li se korisnik nalazi u bazi
 * @param str - Uneseno ime korisnika
 * @param duz - Duzina unesenog imena
 * @return Vraca na kojoj poziciji se nalazi korisnik, ili vraca broj 6 ako nije u bazi
 */
int8_t proveri_ime(char str[], int8_t duz)
{
	int8_t i;
	for(i = 0; i < br_korisnika; i++)
	{
		if(uporedi_korisnike(str, korisnici[i], duz, strlen(korisnici[i]))==1)
		{
			return i;
		}
	}
	return 6;
}

/**
 * Funkcija koja proverava da li je korisnik uneo ispravnu sifru
 * @param sifra - Unesena sifra
 * @param br - Pozicija na kojoj se u bazi nalazi sifra trazenog korisnika
 * @return Vraca 1 ako je dobro uneta sifra, 0 ako nije
 */
int8_t proveri_sifru(char sifra[], int8_t br)
{
	int8_t i;

	for(i = 0; i < 4; i++)
	{
		if(sifra[i] != pin[br][i])
			return 0;
	}
	return 1;
}

/**
 * Funkcija u kojoj se unosi sifra i javlja da li je ispravna
 * @param ime - Ime korisnika
 * @param br - Pozicija na kojoj se u bazi nalazi sifra trazenog korisnika
 * @return Vraca 1 ako je dobro uneta sifra, 0 ako nije
 */
int8_t unos_sifre(char ime[], int8_t br)
{
	char string[128];
	int8_t i = 0;
	char pass[4];

	sprintf(string, "%s, unesite pin: \r\n", ime);
	usartPutString(string);

	while(i < 4)
	{
		while(!usartAvailable());
		_delay_ms(100);

		pass[i] = usartGetChar();
		sprintf(string, "*");
		usartPutString(string);
		i++;
	}

	usartPutString("\r\n");
	//sprintf(string, "Unesen je pin %s", pass);
	//usartPutString(string);

	i = proveri_sifru(pass, br);
	return i;
}

/**
 * Funkcija koja implementira glavni deo programa
 * @return Nema povratnu vrednost
 */
int main()
{
	usartInit(9600);
	char username[max_name];
	int8_t duz_ime = 0;
	int8_t tacno = 1;
	int8_t tacno2 = 1;
	char ispis[45];
	char pass[4];

	while(1)
	{
		usartPutString_P(PSTR("Unesite username: \r\n"));
		while(!usartAvailable());
		_delay_ms(100);

		duz_ime = usartGetString(username);
		tacno = proveri_ime(username, duz_ime);

		if(tacno == 6)
			usartPutString_P(PSTR("Korisnik se ne nalazi u bazi\r\n"));
		else
		{
			tacno2 = unos_sifre(username, tacno);
			if(tacno2 == 1)
			{
				sprintf(ispis, "Korisnik %s uspesno ulogovan \r\n", korisnici[tacno]);
				usartPutString(ispis);
			}

			else
			{
				sprintf(ispis, "Netacna sifra \r\n");
				usartPutString(ispis);
			}
		}

	}

	return 0;
}


