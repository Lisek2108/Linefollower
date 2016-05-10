/*
 * sygnalizacja_pomocnicza.c
 *
 *  Created on: 18 lut 2016
 *      Author: Lisek
 */

#include <avr/io.h>
#include <util/delay.h>
#include "../headers/sygnalizacja_pomocnicza.h"

uint8_t switch_pressed(uint8_t button)
{

	if(!(SWITCH_PIN & button))return 1;
	else return 0 ;
}

void init_signalizacja()
{
	LED_PORT_CONF |= LED_1 | LED_2; // Ustawienie pinów diod na wyjœcie
	SWITCH_PORT_CONF &= ~(SWITCH_1 | SWITCH_2); // Ustawienie pinów przycisków na wejœcie
	SWITCH_PORT |= (SWITCH_1 | SWITCH_2); // Podci¹gniêcie pinów przycisków do vcc

}

void turn_on_diode_1()
{
	LED_PORT |= LED_1;
}

void turn_on_diode_2()
{
	LED_PORT |= LED_2;
}

void turn_off_diode_1()
{
	LED_PORT &= ~(LED_1);
}

void turn_off_diode_2()
{
	LED_PORT &= ~(LED_2);
}

void toggle_diode_1()
{
	LED_PORT ^= LED_1;
}

void toggle_diode_2()
{
	LED_PORT ^= LED_2;
}

