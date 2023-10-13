#ifndef lcd_cfg_44780
#define lcd_cfg_44780

/* Define LCD type
 *          LCD_COL 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
 * LCD_ROW          __________________________________________________________
 *        1        |____________________1x16______________________|           |
 *        2        |____________________2x16______________________|           |
 *        3        |                                                          |
 *        4        |____________________________4x20__________________________|
 */
#define LCD_ROW                 4
#define LCD_COL                 20

/* Define uC ports and pins for LCD control
 * RS	Register Select
 * E	Enable
 * RW	Read / Write*/
#define LCD_E_PORT              B
#define LCD_E_PIN               0
#define LCD_RS_PORT             B
#define LCD_RS_PIN              1
/* RW 1 - Read Option enabled. LCD RW pin must be connected to defined uC port.
 * RW 0 - Read Option disabled. LCD RW pin must be connected to 0V.*/
#define LCD_RW                  1
#if LCD_RW
  #define LCD_RW_PORT           B
  #define LCD_RW_PIN            2
#endif

/* Define uC ports and pins for LCD data*/
#define LCD_D4_PORT             D
#define LCD_D4_PIN              2
#define LCD_D5_PORT             D
#define LCD_D5_PIN              3
#define LCD_D6_PORT             D
#define LCD_D6_PIN              4
#define LCD_D7_PORT             D
#define LCD_D7_PIN              5

/* Enables/disables functions, control lighter version of library. */
/* lcd_cursor_on */
#define CFG_CURSOR_OFF              1
/* lcd_cursor_off */
#define CFG_CURSOR_ON               1
/* lcd_write_text_center */
#define CFG_WRITE_TEXT_CENTER       1
/* lcd_shift_right */
#define CFG_SHIFT_RIGHT             1
/* lcd_shift_left */
#define CFG_SHIFT_LEFT              1

#endif
