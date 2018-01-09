/*
 * lcd_font.h
 *
 *  Created on: 9 maj 2016
 *      Author: konrad
 */

#ifndef LCD_FONT_H_
#define LCD_FONT_H_

#include "lcd.h"

#define LCD_FONT_DEFAULT_WIDTH			5
#define LCD_FONT_DEFAULT_SPACING		1
#define LCD_FONT_DEFAULT_WIDTH_TOTAL	(LCD_FONT_DEFAULT_WIDTH+LCD_FONT_DEFAULT_SPACING)
#define LCD_FONT_NO_CHARACTERS			255

typedef uint8_t lcd_font_character_t[LCD_FONT_DEFAULT_WIDTH];

extern const lcd_font_character_t lcd_font_default[LCD_FONT_NO_CHARACTERS];

#define LCD_FONT_CHR_BT	1

void lcd_font_print_char(int, int, int, lcd_buffer_t);
void lcd_font_print_string(const char*, int, int, lcd_buffer_t);

#endif /* LCD_FONT_H_ */
