/*
 * adc.c
 *
 *  Created on: 18 lut 2016
 *      Author: Lisek
 */

#include "../headers/adc.h"
#include <util/delay.h>

void init_adc()
{

	ADMUX = (1 << REFS0) | (1 << ADLAR);
	ADCSRA = (1 << ADPS2) | (1 << ADPS0) | (1 << ADEN); // Prescaler 32 dla zapewnienia odpowiedniego czasu konwersji

}

uint8_t pomiar(uint8_t kanal)
{


	ADMUX = (ADMUX & 0xF8) | kanal;//Wybranie konkretnego kanalu
	_delay_us(1);
	ADCSRA |= (1 << ADSC);//Rozpoczêcie pomiaru

	while(ADCSRA & (1 << ADSC));

	return ADCH;//Zwrócenie wartoœci zmierzonego napiêcia w 10-biowej postaci
}
