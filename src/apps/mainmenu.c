/*
 * app_mainmenu.c
 *
 *  Created on: 14 kwi 2017
 *      Author: konrad
 */
#include "apps/mainmenu.h"
#include "app_events.h"
#include "app_mgr.h"
#include "lcd_font.h"
#include "lcd.h"
#include "btn.h"

#include "apps/dummy.h"
#include "apps/serial.h"
#include "apps/tetris.h"

// Application structure
App app__mainmenu;
static App* app = &app__mainmenu;

static uint8_t top_app = 0;
static uint8_t chosen_app = 0;

static char* appnames[] = {
		"Debug",
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

static App* apppointers[] = {
		&app__serial,
		&app__tetris,
		&app__dummy,
		&app__dummy,
		&app__dummy,
		&app__dummy,
		(App*) 0,
		&app__dummy,
		&app__dummy,
		&app__dummy,
};

static uint8_t appsno = sizeof(appnames) / sizeof(appnames[0]);

//#define BUF(l,c) buf[LCD_WIDTH*(l)+(c)]
static void draw_handler(uint8_t* buf) {
	for (int i=0; i+top_app<appsno && i<LCD_PAGES; ++i) {
		print_string(appnames[i+top_app], i, 3, buf);
	}
	BUF(chosen_app-top_app,1) = 0xFF;
	print_char((char)16, chosen_app-top_app, 120, buf);
}

static void btn_pressed_handler(uint32_t btn) {
	if (btn & BTN_MASK_UP) {
		if (chosen_app == top_app) {	// pierwsza wybrana opcja
			if (chosen_app == 0) {	// pierwsza ever -> zawin
				chosen_app = appsno-1;
				top_app = appsno-8;
			}
			else {
				chosen_app--;
				top_app--;
			}
		}
		else {
			chosen_app--;
		}
	}


	if (btn & BTN_MASK_DOWN) {
		if (chosen_app - top_app == 7) {	// ostatnia wybrana opcja
			if (chosen_app == appsno - 1) {	// ostatnia ever -> zawin
				chosen_app = 0;
				top_app = 0;
			}
			else {
				chosen_app++;
				top_app++;
			}
		}
		else {
			chosen_app++;
		}
	}

	if (btn & BTN_MASK_BACK) {
		app_quit();
	}

	if (btn & BTN_MASK_OK) {
		if (apppointers[chosen_app]) app_spawn(apppointers[chosen_app]);
	}
}

static void handler(APP_ARGS) {
	switch(id) {
	case APP_EVENT_SPAWN:
		app->needs_redraw = 1;
		break;
	case APP_EVENT_DRAW:
		draw_handler((uint8_t*)data);
		break;
	case APP_EVENT_BTN_PRESSED:
		btn_pressed_handler((uint32_t)data);
		app->needs_redraw = 1;
		break;
	}
}

void app__mainmenu_init() {
	app_init(app, APP__MAINMENU_ID, &handler,
			APP_EVENT_BTN_PRESSED | APP_EVENT_DRAW,	// foreground
			0
			);
}
