/*
 * app__serial.c
 *
 *  Created on: 10 maj 2016
 *      Author: konrad
 */

#include "app__serial.h"
#include "app_events.h"
#include "lcd_font.h"

// Application structure
App app__serial;
static App* app = &app__serial;

// Private (static) data storage
static const uint8_t total_cols = 18;
static const uint8_t total_lines = 7;
static uint8_t line = 0;
static uint8_t col = 0;

static void serial_new_line() {
	if (line == total_lines-1) {
		// 1. Copy each line to the upper one
		for (int i=0; i<UI_APP_HEIGHT-1; i++)
			for (int j=0; j<UI_APP_WIDTH; j++)
				app->framebuffer[i][j] = app->framebuffer[i+1][j];
		// 2. Clear last line
		for (int j=0; j<UI_APP_WIDTH; j++) app->framebuffer[UI_APP_HEIGHT-1][j]=0x00;
	}
	else line++;
}

static void serial_print_char(uint8_t c) {

	// 1. Draw character in right place
	int i;
	for (i=0; i<LCD_FONT_DEFAULT_WIDTH; i++)
		app->framebuffer[line][col*(LCD_FONT_DEFAULT_WIDTH_TOTAL)+i] = lcd_font_default[LCD_FONT_DEFAULT_WIDTH*c+i];
	for (; i<LCD_FONT_DEFAULT_WIDTH_TOTAL; i++)
		app->framebuffer[line][col*(LCD_FONT_DEFAULT_WIDTH_TOTAL)+i] = 0x00;

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
	case '\r':
		col = 0;	// carriage return
		/* no break */
	case '\n':
		serial_new_line();
		break;
	case 0x7F:		// backspace
		serial_remove_last_char();
		break;
	default:
		serial_print_char(c);
		break;
	}
}

void serialhandler(APP_ARGS) {
	switch(id) {
	case APP_EVENT_BT_BYTE:
		serial_handle_char((uint8_t)data);
		app_updatescreen(app);
		break;
	}
}


void app__serial_init() {
	app_init(app, APP__SERIAL_ID, &serialhandler);
}
