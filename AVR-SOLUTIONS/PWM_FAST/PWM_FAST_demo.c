#ifdef F_CPU
#undef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include <avr/io.h>

#include "PWM_FAST_demo.h"

void _CFG_FAST_PWM(uint8_t port_PWM)
{
    /*Set port as output*/
    DDRD |= port_PWM;

    /*Configure Timer0 FAST PWM mode*/
    TCCR0A |= (1<<WGM00) | (1<<WGM01);

    /*Configure PWM output behavior - OCR0A On/Off or Off/On*/
    TCCR0A |= (1<<COM0A0) | (1<<COM0A1);
    //TCCR0A |= (1<<COM0A1);

    /*Prescaler x1*/
    TCCR0B |= (1<<CS00);
}

int PWM_FAST_demo(void)
{
    _CFG_FAST_PWM(LED_RED);
    while(1)
    {
        for(uint8_t i = 0 ; i< 255 ; i++)
        {
            OCR0A = i;
            _delay_ms(10);
        }
        _delay_ms(500);
    }
    return 0;
}

