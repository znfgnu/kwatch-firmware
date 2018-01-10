/*
 * app_mainmenu.c
 *
 *  Created on: 14 kwi 2017
 *      Author: konrad
 */
#include <app.h>
#include <app_event.h>
#include "apps/mainmenu.h"
#include "lcd_font.h"
#include "lcd.h"
#include "btn.h"

#include "apps/dummy.h"
#include "apps/serial.h"
#include "apps/tetris.h"
#include "apps/animation.h"

// Application structure
App_t app__mainmenu;

static uint8_t top_app_idx = 0;
static uint8_t chosen_app_idx = 0;

static char* menuentries_names[] = {
		"Debug",
		"Animation demo",
		"Tetris",
		"Pong",
		"Space invaders",
		"Timer",
		"Stopwatch",
		"---",
		"Hello, world",
		"Settings",
		"About",
};

static App_t* menuentries_pointers[] = {
		&app__serial,
		&app__animation,
		&app__tetris,
		&app__dummy,
		&app__dummy,
		&app__dummy,
		&app__dummy,
		(App_t*) 0,
		&app__dummy,
		&app__dummy,
		&app__dummy,
};

static uint8_t appsno = sizeof(menuentries_names)
		/ sizeof(menuentries_names[0]);

static void draw_handler(lcd_buffer_t buf) {
	for (int i = 0; i + top_app_idx < appsno && i < LCD_PAGES; ++i) {
		lcd_font_print_string(menuentries_names[i + top_app_idx], i, 3, buf);
	}
	buf[chosen_app_idx - top_app_idx][1] = 0xFF;
	lcd_font_print_char((char) 16, chosen_app_idx - top_app_idx, 120, buf);
}

static void btn_pressed_handler(uint32_t btn) {
	if (btn & BTN_MASK_UP) {
		// if already chosen app is at the top of the screen, we need to move view
		if (chosen_app_idx == top_app_idx) {
			// if it's first app from menu, choose the last one
			if (chosen_app_idx == 0) {
				chosen_app_idx = appsno - 1;
				top_app_idx = appsno - 8;
			}
			// else move view one line up
			else {
				chosen_app_idx--;
				top_app_idx--;
			}
		}
		// no need to move view
		else {
			chosen_app_idx--;
		}
	}

	if (btn & BTN_MASK_DOWN) {
		// if already chosen app is at the bottom of the screen, we need to move view
		if (chosen_app_idx == top_app_idx + 7) {
			// if it's last app from menu, choose the first one
			if (chosen_app_idx == appsno - 1) {
				chosen_app_idx = 0;
				top_app_idx = 0;
			}
			// else move view one line down
			else {
				chosen_app_idx++;
				top_app_idx++;
			}
		}
		// no need to move view
		else {
			chosen_app_idx++;
		}
	}

	if (btn & BTN_MASK_BACK) {
		app_quit();
	}

	if (btn & BTN_MASK_OK) {
		if (menuentries_pointers[chosen_app_idx]) {
			app_spawn(menuentries_pointers[chosen_app_idx]);
		}
	}
}

static void handler(uint32_t id, void* data) {
	switch (id) {
	case APP_EVENT_SPAWN:
		app__mainmenu.needs_redraw = 1;
		break;
	case APP_EVENT_DRAW:
		draw_handler(data);
		break;
	case APP_EVENT_BTN_PRESSED:
		btn_pressed_handler((uint32_t) data);
		app__mainmenu.needs_redraw = 1;
		break;
	}
}

void app__mainmenu_init() {
	app_init(&app__mainmenu, APP__MAINMENU_ID, &handler,
			APP_EVENT_BTN_PRESSED | APP_EVENT_DRAW,	// foreground
			0);
}
