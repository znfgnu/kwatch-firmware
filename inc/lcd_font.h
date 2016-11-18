/*
 * lcd_font.h
 *
 *  Created on: 9 maj 2016
 *      Author: konrad
 */

#ifndef LCD_FONT_H_
#define LCD_FONT_H_

#define LCD_FONT_DEFAULT_WIDTH			5
#define LCD_FONT_DEFAULT_SPACING		1
#define LCD_FONT_DEFAULT_WIDTH_TOTAL	(LCD_FONT_DEFAULT_WIDTH+LCD_FONT_DEFAULT_SPACING)
extern const uint8_t lcd_font_default[255*5];


#define LETTER(c, seg)	(lcd_font_default[LCD_FONT_DEFAULT_WIDTH*(c)+(seg)])

void print_char(const char, int, int);
void print_string(const char*, int, int);

#endif /* LCD_FONT_H_ */
