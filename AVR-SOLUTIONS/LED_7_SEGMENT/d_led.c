#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "d_led.h"

volatile uint8_t cyfra_1;
volatile uint8_t cyfra_2;
volatile uint8_t cyfra_3;
volatile uint8_t cyfra_4;

/*
 * Zachowanie tablicy kodów w pamięci FLASH
 * Odczyt za pomocą funkcji pgm_read_byte z biblioteki pgmspace.h
 */
uint8_t KOD_SSD[] PROGMEM =
		{
		0b00111111,		// 0
		0b00000110,		// 1
		0b01011011,		// 2
		0b01001111,		// 3
		0b01100110,		// 4
		0b01101101,		// 5
		0b01111101,		// 6
		0b00100111,		// 7
		0b01111111,		// 8
		0b01101111,		// 9
		0b10000000,		// dot
		0b00000000		// clear
		};

void d_led_init()
{
    /*
     * KONFIGURACJA LED
     */
    /*Wszystkie port jako wyjścia*/
    LED_DATA_DIR = 0xFF;

    /*Ustawiamy na wszystkich portach 0 (wygaszenie)*/
    LED_DATA = 0x00;

    /*4 porty jako wyjścia do multipleksowania wyświetlaczy LED*/
    KATODY_DIR |= (K_LED1 | K_LED2 | K_LED3 | K_LED4);

    /* Ustawiamy porty do sterowani akatodami na 0*/
    KATODY_PORT &= ~(K_LED1 | K_LED2 | K_LED3 | K_LED4);

    /*
     * KONFIGURACJA TIMER0
     */
    /*16e6 / 1024 / 200 = 78,125*/
    OCR0A = 78;

    /* Konfiguracja Timer0 w tryb CTC*/
    TCCR0A |= (1<<WGM01);

    /* Preskaler Timer0 na 1024*/
    TCCR0B |= ((1<<CS02) | (1<<CS00));

    /* Ustawienie przerwania od CTC*/
    TIMSK0 |= (1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
	static uint8_t licznik = 1;

	KATODY_PORT |= 0x0F;
	KATODY_PORT &= ~licznik;

	if (licznik == 1)
	{
		LED_DATA = pgm_read_byte( &KOD_SSD[cyfra_1] );
	}
	else if (licznik == 2)
	{
		LED_DATA = pgm_read_byte( &KOD_SSD[cyfra_2] );
	}
	else if (licznik == 4)
	{
		LED_DATA = pgm_read_byte( &KOD_SSD[cyfra_3] );
	}
	else if (licznik == 8)
	{
		LED_DATA = pgm_read_byte( &KOD_SSD[cyfra_4] );
	}

	licznik <<= 1;
	if (licznik > 8) licznik = 1;
}
