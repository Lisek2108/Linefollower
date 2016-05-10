/*
 * main.c
 *
 *  Created on: 30 lis 2015
 *      Author: Lisek
 */

#include "../headers/pilot.h"
#include "../headers/silniki.h"
#include "../headers/sygnalizacja_pomocnicza.h"
#include "../headers/adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#define EEMEM __attribute__((section(".eeprom")))
#define F_CPU 16000000UL

EEMEM unsigned char P;
EEMEM unsigned char D;
EEMEM uint16_t V;

unsigned char kp;
unsigned char td;
uint16_t v;
uint8_t tryb = 0;
uint8_t v1,v2;

int stan_robota = 0; // B³¹d regulacji
int16_t poprzedni_stan_robota = 0; // Poprzedni b³¹d regulacji
volatile long sterowanie = 0; // Sterowanie
uint8_t wagi[8] = {2,2,4,4,8,8,32,32}; // Wagi poszczególnych czujników
uint8_t prog = 161; // Próg dzia³ania czujników
int p_stan_robota = 0;
volatile uint8_t petla = 0;
int8_t polozenie_robota()
{
	uint8_t i = 0;
	char stan = 0;
	int czujniki_pod_linia = 0; // Liczba czujników pod lini¹

	if(pomiar(3) > prog) czujniki_pod_linia ++; // Sprawdzenie czy œrodkowy czujnik jest pod lini¹

	for(i = 0 ; i < 8 ; i ++)
	{
		PORTA &= 0xF8;
		PORTA |= i;// Zmiana kana³u analogowego multipleksera
		_delay_us(1);
		if(pomiar(4) > prog) // Sprawdzenie czy kolejny czujnik jest pod lini¹
		{
			czujniki_pod_linia++;

			if(i % 2 == 0) stan += wagi[i];

			else stan -= wagi[i];
		}


	}

 	if(stan!=0)p_stan_robota = stan;
	if(czujniki_pod_linia > 0) return stan;
	else return p_stan_robota; // Koñcowy b³¹d regulacji

}

int16_t saturacja(int16_t ll,int16_t hl,int16_t sygnal)
{
	if(sygnal > hl)
		return hl;
	else if(sygnal < ll)
		return ll;
	else
		return sygnal;
}

void timer1_init()
{
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10) | (1 << WGM11); //Zmiana stanu przy zrównaniu siê OCR1A/B z TCNT1
	TCCR1B = (1 << WGM12) | (1 << CS10); //Prescaler 8
	OCR1A = 50;
	OCR1B = 50;

}
void timer0_init()//Inicjalizacja timera wywo³uj¹cego przerwanie
{
	TCCR0 = (1 << WGM01) | (1 << CS02) | (1 << CS00); //Tryb CTC, prescaler 1024
	OCR0 = 30; //125Hz czêstotliwoœc wystepowania przerwania
	TIMSK |= (1 << OCIE0);

}

void spiSlaveInit()
{
	DDRB = (1 << 6); // Ustawienie MOSI na wyjœcie
	SPCR = (1<<SPE) | (1 << SPR1); // Inicjalizacja SPI
}

unsigned char spi_tranceiver (unsigned char data)
{
    // Load data into the buffer
    SPDR = data;

    //Wait until transmission complete
    while(!(SPSR & (1<<SPIF) ));

    // Return received data
    return(SPDR);
}

void trybKonfiguracyjny()
{
	while(tryb != 99)
	{

		tryb = spi_tranceiver(0);

		switch(tryb)
		{
			case 1:
			{
				spi_tranceiver(kp);
				spi_tranceiver(td);
				v1 = (v >> 8);
				v2 = (v & 0xFF);
				spi_tranceiver(v1);
				spi_tranceiver(v2);
				break;

			}
			case 5:
			{
				eeprom_write_byte(&P,spi_tranceiver(0));
				kp = eeprom_read_byte(&P);
				eeprom_write_byte(&D,spi_tranceiver(0));
				td = eeprom_read_byte(&D);
				break;
			}
			case 7:
			{
				v1 = spi_tranceiver(0);
				v2 = spi_tranceiver(0);
				v = (v1 << 8) + v2;
				eeprom_write_word(&V,v);
				break;

			}
			default:
				break;
		}


		if(switch_pressed(SWITCH_2)) break;
		toggle_diode_2();
	}
}


int main()
{

	kp = eeprom_read_byte(&P);
	td = eeprom_read_byte(&D);
	v = eeprom_read_word(&V);

	sei();
	init_signalizacja();
	init_adc();
	DDRA = 0x07;
	init_pilot();
	init_motors();
	timer0_init();
	timer1_init();
	spiSlaveInit();

	toggle_diode_1();
	_delay_ms(1000);
	toggle_diode_1();
	_delay_ms(1000);
	toggle_diode_1();
	_delay_ms(1000);

	stop_motors();

	while(1)
	{

		/*if(switch_pressed(SWITCH_1))
		{
			stop_motors();
		}*/
		if(switch_pressed(SWITCH_2))
			forward();

		if(button_pressed(PILOT_0))
		{
			forward();
		}

		if(switch_pressed(SWITCH_1)) // Tryb konfiguracyjny
		{
			stop_motors();
			trybKonfiguracyjny();

			turn_off_diode_2();
			_delay_ms(500);
			toggle_diode_2();
			_delay_ms(500);
			toggle_diode_2();

		}
		if(button_pressed(PILOT_1))
		{
			stop_motors();
		}

		if(petla == 1)
		{
			petla = 0;
			stan_robota = polozenie_robota();
			sterowanie = kp * stan_robota + td*(stan_robota - poprzedni_stan_robota);
			poprzedni_stan_robota = stan_robota;

			if(sterowanie >= - (kp*2) && sterowanie <= (kp*2) )
			{
				OCR1A = v + 300;
				OCR1B = v + 300;
			}
			else
			{
				OCR1A = v - saturacja(v-900,v,(int)sterowanie);
				OCR1B = v + saturacja(-v,900-v,(int)sterowanie);
			}
		}

	}

}

ISR(TIMER0_COMP_vect)
{
	petla = 1;
}
