#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "PWM_SW_demo.h"

volatile uint8_t cnt_pwm_0;
volatile uint8_t cnt_pwm_1;


void pwm_timer_init()
{
    /*
     * TIMER2 CONFIGURATION
     */
    /* Divide CPU frequency by 200 */
    OCR2A = 200;

    /* Timer2 CTC mode*/
    TCCR2A |= (1<<WGM21);

    /* Timer2 Preskaler 1*/
    TCCR2B |= (1<<CS20);

    /* Set Compare Match*/
    TIMSK2 |= (1<<OCIE2A);
}


void pwm_port_init()
{
    DDRPWM |= (1<<PWM0) | (1<<PWM1);
    PORTPWM |= (1<<PWM0) | (1<<PWM1);
}


ISR( TIMER2_COMPA_vect)
{
    static uint8_t cnt;

    if(cnt >= cnt_pwm_0) PORTPWM |= (1<<PWM0);
    else PORTPWM &= ~(1<<PWM0);

    if(cnt >= cnt_pwm_1) PORTPWM |= (1<<PWM1);
    else PORTPWM &= ~(1<<PWM1);
}


int PWM_SW_demo()
{
    pwm_timer_init();
    pwm_port_init();
    sei();

    while(1)
    {
        /*Main program loop*/
        for(uint8_t i = 0 ; i < 255 ; i++)
        {
            cnt_pwm_0 = i;
            cnt_pwm_1 = i % 30;
            _delay_ms(30);
        }

    }
    return 0;
}
