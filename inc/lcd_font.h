/*
 * lcd_font.h
 *
 *  Created on: 9 maj 2016
 *      Author: konrad
 */

#ifndef LCD_FONT_H_
#define LCD_FONT_H_

extern const uint8_t ASCII[255*5];
#define LETTER(c, seg)	(ASCII[5*(c)+seg])

#endif /* LCD_FONT_H_ */
