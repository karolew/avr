#ifndef _d_lcd
#define _d_lcd

#include "lcd_cfg_44780.h"


/*LCD type*/
#if ( ( LCD_ROW == 4 ) && ( LCD_COL == 20 ) )
	#define LCD_DDRAM_LINE_1	0x00
	#define LCD_DDRAM_LINE_2	0x40
	#define LCD_DDRAM_LINE_3	0x14
	#define LCD_DDRAM_LINE_4	0x54
#else
	#define LCD_DDRAM_LINE_1	0x00
	#define LCD_DDRAM_LINE_2	0x40
	#define LCD_DDRAM_LINE_3	0x10
	#define LCD_DDRAM_LINE_4	0x50
#endif


/*Port macros*/
#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)


/*Control macros*/
#define SET_E PORT(LCD_E_PORT) |= (1<<LCD_E_PIN)
#define CLR_E PORT(LCD_E_PORT) &= ~(1<<LCD_E_PIN)
#define SET_RS PORT(LCD_RS_PORT) |= (1<<LCD_RS_PIN)
#define CLR_RS PORT(LCD_RS_PORT) &= ~(1<<LCD_RS_PIN)
#if LCD_RW
	#define SET_RW PORT(LCD_RW_PORT) |= (1<<LCD_RW_PIN)
	#define CLR_RW PORT(LCD_RW_PORT) &= ~(1<<LCD_RW_PIN)
#endif


/*44780 instructions*/
#define LCD_CLEAR                   0x01
#define LCD_HOME                    0x02
#define LCDC_ENTRY_MODE             0x04
    #define LCD_EM_SHIFT_CURSOR     0x00
    #define LCD_EM_SHIFT_DISPLAY    0x01
    #define LCD_EM_LEFT             0x00
    #define LCD_EM_RIGHT            0x02
#define LCD_ONOFF                   0x08
    #define LCD_DISP_ON             0x04
    #define LCD_CURSOR_ON           0x02
    #define LCDC_CURSOR_OFF         0x00
    #define LCDC_BLINK_ON           0x01
    #define LCDC_BLINK_OFF          0x00
#define LCD_SHIFT                   0x10
    #define LCDC_SHIFT_DISP         0x08
    #define LCDC_SHIFT_CURSOR       0x00
    #define LCDC_SHIFT_RIGHT        0x04
    #define LCDC_SHIFT_LEFT         0x00
#define LCD_FUNC                    0x20
    #define LCD_8_BIT               0x10
    #define LCD_4_BIT               0x00
    #define LCDC_TWO_LINE           0x08
    #define LCDC_FONT_5x10          0x04
    #define LCDC_FONT_5x7           0x00
#define LCDC_SET_CGRAM              0x40
#define LCDC_SET_DDRAM              0x80


/* Special char control
 * 0x80 - 0x87 CGRAM addresses used to map 0 - 7 ASCII codes */
#define SPECIAL_CHAR_ADDR_START     0x80
#define SPECIAL_CHAR_ADDR_STOP      0x87
#define SPECIAL_CHAR_ADDR_MASK      0x07


/* Public LCD functions */
void lcd_init(void);
void lcd_cursor(uint8_t x, uint8_t y);
void lcd_write_char(char data);
void lcd_cls(void);
void lcd_write_text(char* text, uint8_t row, uint8_t col);
#if CFG_WRITE_TEXT_P
    void lcd_write_text_P(char* text, uint8_t row, uint8_t col);
#endif
#if CFG_WRITE_TEXT_E
    void lcd_write_text_E(char* text, uint8_t row, uint8_t col);
#endif
#if CFG_DEF_SPECIAL_CHAR
    void lcd_def_special_char(uint8_t addr, uint8_t *znak);
#endif
#if CFG_DEF_SPECIAL_CHAR_P
    void lcd_def_special_char_P(uint8_t addr, uint8_t *znak);
#endif
#if CFG_DEF_SPECIAL_CHAR_E
    void lcd_def_special_char_E(uint8_t addr, uint8_t *znak);
#endif
#if CFG_CURSOR_ON
    void lcd_cursor_on(void);
#endif
#if CFG_CURSOR_OFF
    void lcd_cursor_off(void);
#endif
#if CFG_SHIFT_RIGHT
    void lcd_shift_right(uint8_t col);
#endif
#if CFG_SHIFT_RIGHT
    void lcd_shift_left(uint8_t col);
#endif
#if CFG_WRITE_TEXT_CENTER
    void lcd_write_text_center(char* text, uint8_t row);
#endif

#endif
