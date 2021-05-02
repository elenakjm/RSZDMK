/**
 * @file main.c
 * @brief Aplikacija koja implementira ogranicen broj treptanja diode
 * @author Ime Prezime
 * @date 14-03-2021
 * @version 1.0
 */

#include "../pin_driver/pin.h"
#include"../timer0_driver/timer0.h"
#include "pulsing.h"

int main()
{
	// Inicijalizacija
	pinInit(PORT_B, DIODE_PIN, OUTPUT);
	timer0InteruptInit();
	// Glavna petlja
	while (1)
	{
		pinPulsing(PORT_B, DIODE_PIN, FAST, FAST_REPETITIONS);
		pinPulsing(PORT_B, DIODE_PIN, SLOW, SLOW_REPETITIONS);
		while(1)
			;
	}
	return 0;
}
