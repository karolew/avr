#ifdef F_CPU
#undef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "d_led.h"
#include "d_button_led.h"


int led_7_segment_demo(void)
{
	button_led_init();
	d_led_init();

	cyfra_1 = 0;
	cyfra_2 = 0;
	cyfra_3 = 0;
	cyfra_4 = 0;

	sei();

	int counter = 0;

    while(1)
    {
    	if (BUTTON_ON)
    	{
    		LED_TOG;
    		_delay_ms(200);
    		LED_TOG;
    		counter++;
    		cyfra_4 = counter % 10;
    		cyfra_3 = ((counter - cyfra_4) % 100) / 10;
    		cyfra_2 = ((counter - cyfra_3) % 1000) / 100;
    		cyfra_1 = ((counter - cyfra_2) % 10000) / 1000;
    	}
    }
    return 0;
}

