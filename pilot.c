/*
 * pilot.c
 *
 *  Created on: 30 lis 2015
 *      Author: Lisek
 */


#include "../headers/pilot.h"
#include <avr/io.h>

void init_pilot()
{
	// Ustawienie pinów portu odpowiedzialnego za pilota na wejœcia
	PILOT_PORT_CONF &= ~(PILOT_0 | PILOT_1 | PILOT_2 | PILOT_3);
	PILOT_PORT &= ~(PILOT_0 | PILOT_1 | PILOT_2 | PILOT_3);
}

// Funkcja sprawdzaj¹ca czy zost³ wciœniêty przycisk pilota
uint8_t button_pressed(uint8_t button)
{
	if(PILOT_PIN & button)return 1;
	else return 0 ;
}
