#ifdef F_CPU
#undef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "PWM_SW_demo.h"

#if SW_PWM_CHANNELS >= 1
    volatile uint8_t cnt_pwm_0;
#endif
#if SW_PWM_CHANNELS >= 2
    volatile uint8_t cnt_pwm_1;
#endif
#if SW_PWM_CHANNELS >= 3
    volatile uint8_t cnt_pwm_2;
#endif
#if SW_PWM_CHANNELS >= 4
    volatile uint8_t cnt_pwm3;
#endif

void pwm_timer_init(uint8_t timer_ocr)
{
    /*
     * TIMER2 CONFIGURATION
     */
    /* Divide CPU frequency by 200 */
    OCR2A = timer_ocr;

    /* Timer2 CTC mode*/
    TCCR2A |= (1<<WGM21);

    /* Timer2 Preskaler 1*/
    TCCR2B |= (1<<CS20);

    /* Set Compare Match*/
    TIMSK2 |= (1<<OCIE2A);
}


void pwm_port_init()
{
    #if SW_PWM_CHANNELS >= 1
        DDRPWM |= PWM0;
        PORTPWM |= PWM0;
    #endif
    #if SW_PWM_CHANNELS >= 2
        DDRPWM |= PWM1;
        PORTPWM |= PWM1;
    #endif
    #if SW_PWM_CHANNELS >= 3
        DDRPWM |= PWM2;
        PORTPWM |= PWM2;
    #endif
    #if SW_PWM_CHANNELS >= 4
        DDRPWM |= PWM3;
        PORTPWM |= PWM3;
    #endif
}


ISR( TIMER2_COMPA_vect)
{
    static uint8_t cnt;
    #if SW_PWM_CHANNELS >= 1
        if(cnt >= cnt_pwm_0) PORTPWM |= PWM0;
        else PORTPWM &= ~PWM0;
    #endif
    #if SW_PWM_CHANNELS >= 2
        if(cnt >= cnt_pwm_1) PORTPWM |= PWM1;
        else PORTPWM &= ~PWM1;
    #endif
    #if SW_PWM_CHANNELS >= 3
        if(cnt >= cnt_pwm_2) PORTPWM |= PWM2;
        else PORTPWM &= ~PWM2;
    #endif
    #if SW_PWM_CHANNELS >= 4
        if(cnt >= cnt_pwm_3) PORTPWM |= PWM3;
        else PORTPWM &= ~PWM3;
    #endif
}


int PWM_SW_demo()
{
    pwm_timer_init(200);
    pwm_port_init();
    sei();

    while(1)
    {
        /*Main program loop*/
        for(uint8_t i = 0 ; i < 255 ; i++)
        {
            cnt_pwm_0 = i;
            cnt_pwm_1 = i % 4;
            _delay_ms(12);
        }

    }
    return 0;
}
