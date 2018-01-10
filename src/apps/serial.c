/*
 * app__serial.c
 *
 *  Created on: 10 maj 2016
 *      Author: konrad
 */

#include <app_event.h>
#include <apps/serial.h>
#include "app.h"
#include "lcd_font.h"
#include "lcd.h"
#include "btn.h"

// Application structure
App_t app__serial;

// Private (static) data storage
#define APP__SERIAL_TOTAL_COLS 18
#define APP__SERIAL_TOTAL_LINES 7
static uint8_t line = 0;
static uint8_t col = 0;

static char testchar = '\0';

static char textdata[APP__SERIAL_TOTAL_LINES][APP__SERIAL_TOTAL_COLS];	// I wasn't able to use constants

static void serial_new_line() {
	if (line == APP__SERIAL_TOTAL_LINES - 1) {
		// 1. Copy each line to the upper one
		for (int i = 0; i < APP__SERIAL_TOTAL_LINES - 1; i++) {
			for (int j = 0; j < APP__SERIAL_TOTAL_COLS; j++) {
				textdata[i][j] = textdata[i + 1][j];
			}
		}
		// 2. Clear last line
		for (int j = 0; j < APP__SERIAL_TOTAL_COLS; j++) {
			textdata[APP__SERIAL_TOTAL_LINES - 1][j] = 0x00;
		}
	} else {
		line++;
	}
	col = 0;
}

static void serial_print_char(uint8_t c) {
	// 1. Draw character in right place
	textdata[line][col] = c;

	col++;
	if (col == APP__SERIAL_TOTAL_COLS) {
		serial_new_line();
		col = 0;
	}
}

static void serial_remove_last_char() {
	if (col != 0) {
		col--;
		serial_print_char(' ');
		col--;
	}
}

static void serial_handle_char(uint8_t c) {
	switch (c) {
	case '\n':
		serial_new_line();
		break;
	case 0x7F:		// backspace
		serial_remove_last_char();
		break;
	case '\r':
	case '\0':
		break;
	default:
		serial_print_char(c);
		break;
	}
}

static void serial_draw(lcd_buffer_t buf) {
	// draw rectangles
	for (int i = 0; i < 111; ++i) {
		buf[0][i] = 0xFF;
	}

	for (int i = 0; i < LCD_PAGES; ++i) {
		for (int j = 112; j < LCD_WIDTH; ++j) {
			buf[i][j] = 0xFF;
		}
	}

	// draw content
	int textline = 0;
	int textcol = 0;
	int lcdline = 1;
	int lcdcol = 0;
	for (; textline < APP__SERIAL_TOTAL_LINES; textline++, lcdline++) {
		textcol = 0;
		lcdcol = 0;
		for (; textcol < APP__SERIAL_TOTAL_COLS; textcol++) {
			int k;
			int c = textdata[textline][textcol];
			for (k = 0; k < LCD_FONT_DEFAULT_WIDTH; k++) {
				buf[lcdline][lcdcol++] = lcd_font_default[c][k];
			}
			for (; k < LCD_FONT_DEFAULT_WIDTH_TOTAL; k++) {
				buf[lcdline][lcdcol++] = 0x00;
			}
		}
	}
}

static void serial_handle_string(char* s) {
	while (*s) {
		serial_handle_char(*s);
		s++;
	}
}

static void serial_handle_msg(char* msg) {
	serial_handle_char(LCD_FONT_CHR_BT);
	serial_handle_char(' ');
	serial_handle_string(msg);
	serial_new_line();
}

static void serial_btn_pressed(uint32_t btn) {
	if (btn & BTN_MASK_BACK) {
		app_quit();
		return;
	}

	if (btn & BTN_MASK_UP) {
		testchar++;
	}
	if (btn & BTN_MASK_DOWN) {
		testchar--;
	}

	serial_handle_string("\x07 ");
	serial_handle_char('0' + (testchar / 100));
	serial_handle_char('0' + ((testchar / 10) % 10));
	serial_handle_char('0' + (testchar % 10));
	serial_handle_string(": '");
	serial_handle_char(testchar);
	serial_handle_string("'\n");
}

static void serialhandler(uint32_t id, void* data) {
	switch (id) {
	case APP_EVENT_SPAWN:
		app__serial.needs_redraw = 1;
		break;
	case APP_EVENT_BT_MSG:
		serial_handle_msg((char*) data);
		app__serial.needs_redraw = 1;
		break;
	case APP_EVENT_DRAW:
		serial_draw(data);
		break;
	case APP_EVENT_BTN_PRESSED:
		serial_btn_pressed((uint32_t) data);
		app__serial.needs_redraw = 1;
		break;
	}
}

void app__serial_init() {
	app_init(&app__serial, APP__SERIAL_ID, &serialhandler,
			APP_EVENT_BTN_PRESSED | APP_EVENT_DRAW | APP_EVENT_BT_MSG,	// foreground
			APP_EVENT_BT_MSG);
}
