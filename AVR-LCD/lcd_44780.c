#include <avr/io.h>
#include <avr/delay.h>

#include "lcd_44780.h"


void set_data_port_out(void)
{
	DDR(LCD_D4_PORT) |= (1<<LCD_D4_PIN);
	DDR(LCD_D5_PORT) |= (1<<LCD_D5_PIN);
	DDR(LCD_D6_PORT) |= (1<<LCD_D6_PIN);
	DDR(LCD_D7_PORT) |= (1<<LCD_D7_PIN);
}


void set_data_port_in(void)
{
	DDR(LCD_D4_PORT) &= ~(1<<LCD_D4_PIN);
	DDR(LCD_D5_PORT) &= ~(1<<LCD_D5_PIN);
	DDR(LCD_D6_PORT) &= ~(1<<LCD_D6_PIN);
	DDR(LCD_D7_PORT) &= ~(1<<LCD_D7_PIN);
}


void set_control_port_out(void)
{
	DDR(LCD_E_PORT) |= (1<<LCD_E_PIN);
	DDR(LCD_RS_PORT) |= (1<<LCD_RS_PIN);
	#if LCD_RW
		DDR(LCD_RW_PORT) |= (1<<LCD_RW_PIN);
	#endif
}


void set_control_port_in(void)
{
	DDR(LCD_E_PORT) &= ~(1<<LCD_E_PIN);
	DDR(LCD_RS_PORT) &= ~(1<<LCD_RS_PIN);
	#if LCD_RW
		DDR(LCD_RW_PORT) &= ~(1<<LCD_RW_PIN);
	#endif
}


#if LCD_RW
	static inline uint8_t lcd_read_half_byte(void)
	{
		uint8_t data = 0;
		SET_E;
		if (PIN(LCD_D4_PORT) & (1<<LCD_D4_PIN)) data |= (1<<0);
		if (PIN(LCD_D5_PORT) & (1<<LCD_D5_PIN)) data |= (1<<1);
		if (PIN(LCD_D6_PORT) & (1<<LCD_D6_PIN)) data |= (1<<2);
		if (PIN(LCD_D7_PORT) & (1<<LCD_D7_PIN)) data |= (1<<3);
		CLR_E;
		return data;
	}

	uint8_t lcd_read_byte(void)
	{
		set_data_port_in();
		SET_RW;
		uint8_t data = 0;
		data = (lcd_read_half_byte()<<4);
		data |= lcd_read_half_byte();
		return data;
	}

	uint8_t lcd_read_flag(void)
	{
		CLR_RS;
		return lcd_read_byte();
	}

	void lcd_check_busy(void)
	{
		while(lcd_read_flag() & 0x80);
	}
#endif


static inline void lcd_write_half_byte(uint8_t data)
{
	SET_E;
	if (data & (1<<0)) PORT(LCD_D4_PORT) |= (1<<LCD_D4_PIN);
	else PORT(LCD_D4_PORT) &= ~(1<<LCD_D4_PIN);
	if (data & (1<<1)) PORT(LCD_D5_PORT) |= (1<<LCD_D5_PIN);
	else PORT(LCD_D5_PORT) &= ~(1<<LCD_D5_PIN);
	if (data & (1<<2)) PORT(LCD_D6_PORT) |= (1<<LCD_D6_PIN);
	else PORT(LCD_D6_PORT) &= ~(1<<LCD_D6_PIN);
	if (data & (1<<3)) PORT(LCD_D7_PORT) |= (1<<LCD_D7_PIN);
	else PORT(LCD_D7_PORT) &= ~(1<<LCD_D7_PIN);
	CLR_E;
}


void lcd_write_byte(uint8_t data)
{
	#if LCD_RW
		CLR_RW;
	#endif

	set_data_port_out();
	lcd_write_half_byte(data>>4);
	lcd_write_half_byte(data);

	#if LCD_RW
		lcd_check_busy();
	#else
		_delay_us(120);
	#endif
}


void lcd_write_cmd(uint8_t cmd)
{
	CLR_RS;
	lcd_write_byte(cmd);
}


void lcd_write_char(char data)
{
	SET_RS;
	lcd_write_byte(data);
}

void lcd_write_text(char* text, uint8_t row, uint8_t col)
{
	lcd_cursor(col, row);
	while(*text && row < LCD_ROW)
	{
		lcd_write_char(*text++);
		if(++col % LCD_COL == 0)
			lcd_cursor(0, ++row);
	}
}

void lcd_cursor(uint8_t x, uint8_t y)
{
	switch(y)
	{
		case 0:
			lcd_write_cmd( LCDC_SET_DDRAM | (LCD_DDRAM_LINE_1 + x) );
			break;
	#if LCD_ROW > 1
		case 1:
			lcd_write_cmd( LCDC_SET_DDRAM | (LCD_DDRAM_LINE_2 + x) );
			break;
	#endif
	#if LCD_ROW > 2
		case 2:
			lcd_write_cmd( LCDC_SET_DDRAM | (LCD_DDRAM_LINE_3 + x) );
			break;
		case 3:
			lcd_write_cmd( LCDC_SET_DDRAM | (LCD_DDRAM_LINE_4 + x) );
			break;
	#endif
	}
}

void lcd_cursor_on(void)
{
	lcd_write_cmd( LCD_ONOFF | LCD_DISP_ON | LCD_CURSOR_ON );
	#if LCD_RW == 0
		_delay_ms(4.1);
	#endif
}

void lcd_cursor_off(void)
{
	lcd_write_cmd( LCD_ONOFF | LCD_DISP_ON | LCDC_CURSOR_OFF );
	#if LCD_RW == 0
		_delay_ms(4.1);
	#endif
}

void lcd_cls(void)
{
	lcd_write_cmd( LCD_CLEAR );
	#if LCD_RW == 0
		_delay_ms(4.1);
	#endif
}

void lcd_init(void)
{
	set_data_port_out();
	set_control_port_out();

	_delay_ms(15);

	CLR_E;
	CLR_RS;
	#if LCD_RW
		CLR_RW;
	#endif

	lcd_write_half_byte(0x03);
	_delay_ms(4.1);
	lcd_write_half_byte(0x03);
	_delay_us(100);
	lcd_write_half_byte(0x03);
	_delay_us(100);
	lcd_write_half_byte(0x02);
	_delay_us(100);

	lcd_write_cmd( LCD_FUNC | LCD_4_BIT | LCDC_TWO_LINE | LCDC_FONT_5x10 );
	lcd_write_cmd( LCD_ONOFF | LCD_DISP_ON );
	_delay_ms(4.1);
	lcd_write_cmd( LCDC_ENTRY_MODE | LCD_EM_SHIFT_CURSOR | LCD_EM_RIGHT );
	lcd_cls();
}
