
# AVR LCD 44780 

Library for LCD displays based on a HD44780 compatible controller.

## Usage
* Copy *.c and *.h files to your project.
* Update lcd_cfg_44780.h according to your HW setup and preferences.
* Include lcd_44780.h and call lcd_init().

## Notes
* When LCD_RW is set to 0, additional delays may be required after lcd_cls() calls.
* Special char definition must contain 9 bytes, and last byte must be SPECIAL_CHAR_END_BYTE_9