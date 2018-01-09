/*
 * tetris.c
 *
 *  Created on: 14 kwi 2017
 *      Author: konrad
 */
#include <app.h>
#include <app_event.h>
#include "apps/tetris.h"
#include "lcd_font.h"
#include "lcd.h"
#include "btn.h"

// Application structure
App_t app__tetris;

static uint16_t board[20];
static uint8_t block[4][4] = {
		{0x00, 0x00, 0x00, 0x00},
		{0x0F, 0x09, 0x09, 0x0F},
		{0xF0, 0x90, 0x90, 0xF0},
		{0xFF, 0x99, 0x99, 0xFF},
};

static void spawn_handler(void) {
	// generate sample board
	for (int i=0; i<10; ++i) {
		board[i] = (1<<(10-i))-1;
	}
}

static void draw_handler(lcd_buffer_t buf) {
	uint8_t l_offset = 1;
	uint8_t c_offset = 10;

	// draw frame
	for (int i=0; i<82; ++i) {
		buf[l_offset-1][c_offset-1+i] = 0x80;
		buf[l_offset+5][c_offset-1+i] = 0x01;
	}
	for (int i=0; i<5; ++i) {
		buf[l_offset+i][c_offset-1] = 0xFF;
		buf[l_offset+i][c_offset+80] = 0xFF;
	}

	// draw blocks
	for (int i=0; i<20; ++i) {
		if (board[i]) {
			for (int j=0; j<5; j++) {
				uint8_t wtd = (board[i]>>(j*2))&3;
				for (int k=0; k<4; ++k) {
					buf[l_offset+j][c_offset+4*i+k] = block[wtd][k];
				}
			}
		}
	}
}

static void btn_pressed_handler(uint32_t btn) {
	if (btn & BTN_MASK_BACK) {
		app_quit();
	}
}

static void handler(uint32_t id, void* data) {
	switch(id) {
	case APP_EVENT_SPAWN:
		spawn_handler();
		app__tetris.needs_redraw = 1;
		break;
	case APP_EVENT_DRAW:
		draw_handler(data);
		break;
	case APP_EVENT_BTN_PRESSED:
		btn_pressed_handler((uint32_t)data);
		break;
	}
}

void app__tetris_init() {
	app_init(&app__tetris, APP__TETRIS_ID, &handler,
			APP_EVENT_BTN_PRESSED | APP_EVENT_SECOND_ELAPSED | APP_EVENT_DRAW,	// foreground
			0);
}
