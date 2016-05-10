/*
 * silniki.c
 *
 *  Created on: 18 lut 2016
 *      Author: Lisek
 */

#include "../headers/silniki.h"
#include <avr/io.h>

void init_motors()
{
	L_MOTOR_CONF |= (AIN1 | AIN2 | PWMA); // Ustawienie odpowiednich pinów portu D na wyjœcie
	R_MOTOR_CONF |= (BIN1 | BIN2 | PWMB); // Ustawienie odpowiednich pinów portu D na wyjœcie

	L_MOTOR_PORT &= ~(AIN1 | AIN2); // Zatrzymanie silników
	R_MOTOR_PORT &= ~(BIN1 | BIN2); // Zatrzymanie silników

}

void stop_motors()
{
	L_MOTOR_PORT &= ~(AIN1 | AIN2);
	R_MOTOR_PORT &= ~(BIN1 | BIN2);
}

void forward()
{
	L_MOTOR_PORT &= ~AIN1;
	R_MOTOR_PORT &= ~BIN2;

	L_MOTOR_PORT |= AIN2 | BIN1;
}
