/*
 * app__serial.c
 *
 *  Created on: 10 maj 2016
 *      Author: konrad
 */

#include "app__serial.h"
#include "app_events.h"
#include "app_mgr.h"
#include "lcd_font.h"
#include "lcd.h"
#include "btn.h"

// Application structure
App app__serial;
static App* app = &app__serial;

// Private (static) data storage
static const uint8_t total_cols = 18;
static const uint8_t total_lines = 7;
static uint8_t line = 0;
static uint8_t col = 0;

static char textdata[7][18];	// I wasn't able to use constants

static void serial_new_line() {
	if (line == total_lines-1) {
		// 1. Copy each line to the upper one
		for (int i=0; i<total_lines-1; i++)
			for (int j=0; j<total_cols; j++)
				textdata[i][j] = textdata[i+1][j];
		// 2. Clear last line
		for (int j=0; j<total_cols; j++) textdata[total_lines-1][j]=0x00;
	}
	else line++;
	col = 0;
}

static void serial_print_char(uint8_t c) {
	// 1. Draw character in right place
	textdata[line][col] = c;

	col++;
	if (col == total_cols) {
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
	switch(c){
//	case '\r':
//		col = 0;	// carriage return
//		break;
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

#define BUF(x,y) drawbuf[LCD_WIDTH*x+y]
static void serial_draw(uint8_t* drawbuf) {
	// draw rectangles
	for (int i=0; i<111; ++i) drawbuf[i]=0xFF;

	for (int i=0; i<LCD_PAGES; ++i)
		for (int j=112; j<LCD_WIDTH; ++j)
			drawbuf[i*LCD_WIDTH+j] = 0xFF;

	// draw content
	int textline = 0;
	int textcol = 0;
	int lcdline = 1;
	int lcdcol = 0;
	for (;textline<total_lines; textline++, lcdline++) {
		textcol = 0;
		lcdcol=0;
		for (; textcol<total_cols; textcol++) {
			int k;
			char c = textdata[textline][textcol];
			for (k=0; k<LCD_FONT_DEFAULT_WIDTH; k++)
				BUF(lcdline, lcdcol++) = lcd_font_default[LCD_FONT_DEFAULT_WIDTH*c+k];
			for (; k<LCD_FONT_DEFAULT_WIDTH_TOTAL; k++)
				BUF(lcdline, lcdcol++) = 0x00;
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
	serial_handle_string("bt> ");
	serial_handle_string(msg);
	serial_new_line();
}


static void serial_btn_pressed(uint32_t btn) {
	serial_handle_string("btn> ");
	serial_handle_string("pressed ");
	serial_handle_char('0'+btn);
	serial_new_line();
	if (btn & BTN_MASK_BACK) app_quit();
}

static void serialhandler(APP_ARGS) {
	switch(id) {
	case APP_EVENT_SPAWN:
		app->needs_redraw = 1;
		break;
	case APP_EVENT_BT_MSG:
		serial_handle_msg((char*)data);
		app->needs_redraw = 1;
		break;
	case APP_EVENT_DRAW:
		serial_draw((uint8_t*)data);
		break;
	case APP_EVENT_BTN_PRESSED:
		serial_btn_pressed((uint32_t)data);
		app->needs_redraw = 1;
		break;
	}
}


void app__serial_init() {
	app_init(app, APP__SERIAL_ID, &serialhandler,
			APP_EVENT_BTN_PRESSED | APP_EVENT_DRAW | APP_EVENT_BT_MSG,	// foreground
			APP_EVENT_BT_MSG
			);
}
