#ifndef _PWM_FAST_demo
#define _PWM_FAST_demo

#include <avr/io.h>

/* For Atmega328 it must be Port D Pin 6 as it is PWM OC0A output */
#define LED_RED  (1<<PD6)

void _CFG_FAST_PWM(uint8_t port_PWM);
int PWM_FAST_demo(void);

#endif
