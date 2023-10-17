#ifndef _d_led_h
#define _d_led_h

#define LED_DATA        PORTD
#define LED_DATA_DIR    DDRD
#define KATODY_PORT     PORTB
#define KATODY_DIR      DDRB

#define K_LED1  (1<<PB0)
#define K_LED2  (1<<PB1)
#define K_LED3  (1<<PB2)
#define K_LED4  (1<<PB3)

extern volatile uint8_t cyfra_1;
extern volatile uint8_t cyfra_2;
extern volatile uint8_t cyfra_3;
extern volatile uint8_t cyfra_4;

void d_led_init(void);

#endif
