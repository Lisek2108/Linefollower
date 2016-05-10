/*
 * adc.h
 *
 *  Created on: 18 lut 2016
 *      Author: Lisek
 */

#ifndef HEADERS_ADC_H_
#define HEADERS_ADC_H_

#include <avr/io.h>

void init_adc();
uint8_t pomiar(uint8_t kanal);

#endif /* HEADERS_ADC_H_ */
