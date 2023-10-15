#ifdef F_CPU
#undef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdlib.h>
#include <util/delay.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "../lcd_44780.h"


int main(void)
{
	lcd_init();
	lcd_cls();

	const uint8_t pl_au[] = {
	        0b00000,
	        0b00000,
	        0b01110,
	        0b00001,
	        0b01111,
	        0b10001,
	        0b01111,
	        0b00010};
	const uint8_t pl_ci[] = {
	        0b00010,
	        0b00100,
	        0b01110,
	        0b10000,
	        0b10000,
	        0b10001,
	        0b01110,
	        0b00000};
	const uint8_t pl_eu[] = {
	        0b00000,
	        0b00000,
	        0b01110,
	        0b10001,
	        0b11111,
	        0b10000,
	        0b01110,
	        0b00010};
	const uint8_t pl_el[] = {
	        0b01100,
	        0b00100,
	        0b00110,
	        0b00100,
	        0b01100,
	        0b00100,
	        0b01110,
	        0b00000};
	const uint8_t pl_en[] = {
	        0b00010,
	        0b00100,
	        0b10110,
	        0b11001,
	        0b10001,
	        0b10001,
	        0b10001,
	        0b00000};
	const uint8_t pl_uo[] = {
	        0b00010,
	        0b00100,
	        0b01110,
	        0b10001,
	        0b10001,
	        0b10001,
	        0b01110,
	        0b00000};
	const uint8_t pl_es[] = {
	        0b00010,
	        0b00100,
	        0b01110,
	        0b10000,
	        0b01110,
	        0b00001,
	        0b11110,
	        0b00000};
	const uint8_t pl_zi[] = {
	        0b00010,
	        0b00100,
	        0b11111,
	        0b00010,
	        0b00100,
	        0b01000,
	        0b11111,
	        0b00000};
	const uint8_t pl_zy[] = {
	        0b00000,
	        0b00100,
	        0b11111,
	        0b00010,
	        0b00100,
	        0b01000,
	        0b11111,
	        0b00000};

	lcd_def_special_char(0x80, (uint8_t *)pl_au);
	lcd_def_special_char(0x81, (uint8_t *)pl_ci);
	lcd_def_special_char(0x82, (uint8_t *)pl_el);
	lcd_def_special_char(0x83, (uint8_t *)pl_en);
	lcd_def_special_char(0x84, (uint8_t *)pl_uo);
	lcd_def_special_char(0x85, (uint8_t *)pl_es);
	lcd_def_special_char(0x86, (uint8_t *)pl_zi);
	lcd_def_special_char(0x87, (uint8_t *)pl_zy);

    #define STR_IMPL_(x) #x
    #define STR(x) STR_IMPL_(x)

    #define au  STR(\x80)       // ą
    #define ci  STR(\x81)       // ć
    #define el  STR(\x82)       // ę
    #define en  STR(\x83)       // ń
    #define uo  STR(\x84)       // ó
    #define es  STR(\x85)       // ś
    #define zi  STR(\x86)       // ź
    #define zy  STR(\x87)       // ż

    while(1)
    {
        _delay_ms(100);
        char data[] = "-"zy"y"ci" "el"o"es" b"au"ki-";
        lcd_write_text_center(data, 0);
    	_delay_ms(1000);


    	for(uint8_t i = 0 ; i< 2 ; i++)
    	{
            lcd_shift_right(1);
            _delay_ms(300);
    	}
        for(uint8_t i = 0 ; i< 4 ; i++)
        {
            lcd_shift_left(1);
            _delay_ms(300);
        }
        for(uint8_t i = 0 ; i< 2 ; i++)
        {
            lcd_shift_right(1);
            _delay_ms(300);
        }

    	char var_buf[5] = {0};
    	lcd_write_text("TMP: ", 1, 0);
    	for(int i = -20 ; i <= 20 ; i++)
    	{
    	    lcd_write_text("     ", 1, 5);
    		lcd_write_text(strcat(itoa(i, var_buf, 10), " C"), 1, 5);
    		_delay_ms(50);
    	}

    	lcd_write_text_P(PSTR("FLASH OK"), 3, 10);
    	_delay_ms(1000);

    	lcd_write_text("Very long text should be displayed on successive lines "
    	        "until the last character.", 0, 0);
    	_delay_ms(3000);

    	lcd_cls();
    	_delay_ms(20);
    }
    return 0;
}

