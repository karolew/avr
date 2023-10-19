#ifndef PWM_SW_PWM_SW_DEMO_H_
#define PWM_SW_PWM_SW_DEMO_H_

#include <avr/io.h>

/*Configurable from 1 - 4*/
#define SW_PWM_CHANNELS 2

/*Configure Ports and Pins for PWM. This version support only one Port*/
#if SW_PWM_CHANNELS >= 1
    #define PPWM0    PD4
    #define PWM0    (1<<PPWM0)
    extern volatile uint8_t cnt_pwm_0;
#endif
#if SW_PWM_CHANNELS >= 2
    #define PPWM1    PD5
    #define PWM1    (1<<PPWM1)
    extern volatile uint8_t cnt_pwm_1;
#endif
#if SW_PWM_CHANNELS >= 3
    #define PPWM2    PD6
    #define PWM2    (1<<PPWM2)
    extern volatile uint8_t cnt_pwm_2;
#endif
#if SW_PWM_CHANNELS >= 4
    #define PPWM3    PD7
    #define PWM3    (1<<PPWM3)
    extern volatile uint8_t cnt_pwm3;
#endif

#define DDRPWM  DDRD
#define PORTPWM PORTD

void pwm_timer_init(uint8_t timer_ocr);
void pwm_port_init();
int PWM_SW_demo();

#endif /* PWM_SW_PWM_SW_DEMO_H_ */
