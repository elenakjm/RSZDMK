#include "../PLS7shield/PLS7shield.h"
#include "timer0.h"
#include<stdint.h>


uint8_t i=0;

const uint8_t cifre[]={0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04, 0x14
  };
  
uint8_t provera(uint8_t broj)
{
	for(i=2; i<broj; i++)
	{
		if(broj%i==0)
		{
			return 0; //nije prost
			break;
		}
	}
	return 1; //jeste prost
}

void stampaj(uint8_t x)
{
	PLS7writeDisplay(4, cifre[x%10]);
	if(x/10>0) //moze i bez if-a, ovo je tu samo da mi ne stampa nulu, npr 006 umesto 6
	{
		PLS7writeDisplay(3, cifre[(x/10)%10]);
		if(x/100>0)
		{
			PLS7writeDisplay(2, cifre[(x/100)%10]);
		}
	}
}

int main()
{
	PLS7init();
	timer0InteruptInit();
	PLS7writeDisplay(LEDS, 0xff); //prvo sve diode iskljucimo
	uint8_t br=1;
	uint8_t br_pre=0;
	
	enum state_t {UNOS, PROVERA, PROST, NIJE};
	enum state_t state = UNOS;
	
	while(1)
	{
		switch(state)
		{
			case UNOS:
				while(!PLS7buttonState(LEFT));
				//da se ne vrti sam od sebe, nije trazeno da ceka levi prekidac, ali je meni lakse ovako
				PLS7writeDisplay(LEDS, 0xff);
				br=~PLS7readSwitches();
				stampaj(br);
				state=PROVERA;
				break;
				
			case PROVERA:
				PLS7writeDisplay(LEDS, 0x00); //pali sve
				timer0DelayMs(1000); //ne trazi se, ali da se vide upaljene diode jer ce odmah preci dalje bez ovoga
				if (provera(br)==1)
					state=PROST;
				else
					state=NIJE;
				break;
				
			case PROST:
				PLS7writeDisplay(LEDS, 0x7e);
				state=UNOS;
				break;
				
			case NIJE:
				PLS7writeDisplay(LEDS, 0xe7);
				state=UNOS;
				break;
		}
	}
	
	return 0;
}