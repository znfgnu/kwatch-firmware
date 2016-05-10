/*
 * ui.c
 *
 *  Created on: 9 maj 2016
 *      Author: konrad
 */

#include "ui.h"
#include "lcd.h"
#include "lcd_font.h"

void ui_drawRectangles(uint8_t* drawbuf) {
	for (int i=0; i<111; ++i) drawbuf[i]=0xFF;

	for (int i=0; i<LCD_PAGES; ++i)
		for (int j=112; j<LCD_WIDTH; ++j)
			drawbuf[i*LCD_WIDTH+j] = 0xFF;
}

void ui_print_text(uint8_t* drawbuf, uint8_t page, char* string, uint8_t inverted) {
	drawbuf += page*LCD_WIDTH;
	uint8_t mask = 0x00;
	if (inverted) mask = 0xFF;
	while(*string) {
		drawbuf++;	// 1px offset each character
		for(int i=0; i<5; ++i) *(drawbuf++) = mask ^ LETTER(*string, i);
		string++;
	}
}

void ui_init() {
	ui_drawRectangles(lcd_buffer);
	ui_print_text(lcd_buffer, 0, "10:57 | KwatchOS", 1);

	ui_print_text(lcd_buffer, 1, "123456789012345678", 0);
	ui_print_text(lcd_buffer, 2, "12345678901234", 0);
	ui_print_text(lcd_buffer, 3, "12345678901234", 0);
	ui_print_text(lcd_buffer, 4, "12345678901234", 0);
	ui_print_text(lcd_buffer, 5, "123456789012345678", 0);
	ui_print_text(lcd_buffer, 6, "12345678901234", 0);
	ui_print_text(lcd_buffer, 7, "12345678901234", 0);
}
