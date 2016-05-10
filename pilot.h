/*
 * pilot.h
 *
 *  Created on: 30 lis 2015
 *      Author: Lisek
 */

#ifndef HEADERS_PILOT_H_
#define HEADERS_PILOT_H_

#include <avr/io.h>

#define PILOT_PORT_CONF DDRC // Port konfiguracyjny pilota

#define PILOT_PORT PORTC // Port pilota

#define PILOT_PIN PINC

// Definicje "wyjœc" pilota
#define PILOT_0 (1 << PC2)
#define PILOT_1 (1 << PC3)
#define PILOT_2 (1 << PC4)
#define PILOT_3 (1 << PC5)

void init_pilot(); // Funkcja inicjalizuj¹ca pilot

uint8_t button_pressed(uint8_t button); // Funkcja sprawdzaj¹ca czy wciœniêto przycisk

#endif /* HEADERS_PILOT_H_ */
