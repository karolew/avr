#include <avr/io.h>
#include <util/delay.h>

#include "d_button_led.h"

void button_led_init(void)
{
    /* Ustawienie LED na porcie B jako wyjścia */
    DDRB |= LED_PIN;

    /* Wyłączenie LED */
    PORTB &= ~LED_PIN;

    /* Ustawienie BUTTON jako wejście */
    DDRB &= ~BUTTON;

    /* Podciągnięcie BUTTON do VCC wewnętrzym rezystorem */
    PORTB |= BUTTON;
}
