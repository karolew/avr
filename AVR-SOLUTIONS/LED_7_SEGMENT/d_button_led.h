#ifndef _d_button_led
#define _d_button_led

#define LED_PIN     (1<<PB5)
#define LED_TOG     PORTB ^= LED_PIN
#define BUTTON      (1<<PB4)
#define BUTTON_ON   !(PINB & BUTTON)

void button_led_init(void);

#endif
