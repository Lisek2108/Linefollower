/*
 * sygnalizacja_pomocnicza.h
 *
 *  Created on: 18 lut 2016
 *      Author: Lisek
 */

#ifndef HEADERS_SYGNALIZACJA_POMOCNICZA_H_
#define HEADERS_SYGNALIZACJA_POMOCNICZA_H_

#include <avr/io.h>
//Plik nag³ówkowy gdzie zawarte s¹ deklaracje komponentów odpowiedzialnych za
//pomocnicz¹ sygnalizacjê i testowanie programu

#define LED_PORT_CONF DDRD // Port konfiguracyjny diod

#define LED_PORT PORTD // Port diod

// Piny diod
#define LED_1 (1 << PD0)
#define LED_2 (1 << PD1)


#define SWITCH_PORT_CONF DDRC // Port konfiguracyjny przycisków

#define SWITCH_PORT PORTC // Port przycisków

#define SWITCH_PIN PINC

// Piny przycisków
#define SWITCH_1 (1 << PC6)
#define SWITCH_2 (1 << PC7)

void init_signalizacja();


// Funkcje odpowiedzialne za manipulowanie stanem diod
void turn_on_diode_1();
void turn_on_diode_2();

void turn_off_diode_1();
void turn_off_diode_2();

void toggle_diode_1();
void toggle_diode_2();

// Funkcja sprawdzaj¹ca czy zostal wciœniêty przycisk

uint8_t switch_pressed(uint8_t button);

#endif /* HEADERS_SYGNALIZACJA_POMOCNICZA_H_ */
