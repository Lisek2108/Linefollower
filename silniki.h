/*
 * silniki.h
 *
 *  Created on: 5 gru 2015
 *      Author: Lisek
 */

#ifndef HEADERS_SILNIKI_H_
#define HEADERS_SILNIKI_H_


//---------------------STA£E SILNIKA LEWEGO--------------------------

//Port konfiguracyjny dla wyboru kierunku obrotu silnika lewego
#define L_MOTOR_CONF DDRD
//Port dla wyboru kierunku obrotu silnika lewego
#define L_MOTOR_PORT PORTD

//Port konfiguracyjny dla kana³u PWM silnika lewego
#define L_MOTOR_PWM_CONF DDRD
//Port  dla kana³u PWM silnika lewego
#define L_MOTOR_PWM_PORT PORTD

//Numery pinów w portach

#define AIN1 (1 << PD7)
#define AIN2 (1 << PD6)
#define PWMA (1 << PD5)


//---------------------STA£E SILNIKA PRAWEGO--------------------------

//Port konfiguracyjny dla wyboru kierunku obrotu silnika prawego
#define R_MOTOR_CONF DDRD
//Port dla wyboru kierunku obrotu silnika lewego
#define R_MOTOR_PORT PORTD

//Port konfiguracyjny dla kana³u PWM silnika lewego
#define R_MOTOR_PWM_CONF DDRD
//Port  dla kana³u PWM silnika lewego
#define R_MOTOR_PWM_PORT PORTD

//Numery pinów w portach

#define BIN1 (1 << PD2)
#define BIN2 (1 << PD3)
#define PWMB (1 << PD4)

void init_motors();
void stop_motors();
void forward();

#endif /* HEADERS_SILNIKI_H_ */
