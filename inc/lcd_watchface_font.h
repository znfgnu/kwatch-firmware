/*
 * lcd_watchface_font.h
 *
 *  Created on: 17 lis 2016
 *      Author: konrad
 */

#ifndef LCD_WATCHFACE_FONT_H_
#define LCD_WATCHFACE_FONT_H_

#include <stdint.h>

typedef uint8_t lcd_watchface_font_digit_t[96];
typedef lcd_watchface_font_digit_t lcd_watchface_font_t[10];

extern const lcd_watchface_font_t lcd_watchface_font;

#endif /* LCD_WATCHFACE_FONT_H_ */
