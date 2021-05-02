#include <avr/io.h>
#include <avr/interrupt.h>

int main()
{
	DDRB |= 1 << 5; //PB5 je izlaz
	return 0;
}

void branch_a()
{
	while (1)
	{
		PORTB |= 1 << 5; //LED ON
		_delay_ms(500); //pauza 1s
		PORTB &= ~(1 << 5); //LED OFF
		_delay_ms(500); //pauza 1s
	}
}

void branch_b()
{
	TCCR0A
}
