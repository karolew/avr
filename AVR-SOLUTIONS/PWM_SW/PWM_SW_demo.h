#ifndef PWM_SW_PWM_SW_DEMO_H_
#define PWM_SW_PWM_SW_DEMO_H_

#define PWM0    PD6
#define PWM1    PD7

#define DDRPWM  DDRD
#define PORTPWM PORTD

/*Veriables to control SW PWM channels*/
//extern volatile uint8_t cnt_pwm_0;
//extern volatile uint8_t cnt_pwm_1;

void pwm_timer_init();
void pwm_port_init();

#endif /* PWM_SW_PWM_SW_DEMO_H_ */
