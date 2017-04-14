/*
 * app_mainmenu.c
 *
 *  Created on: 14 kwi 2017
 *      Author: konrad
 */
#include <apps/mainmenu.h>
#include "app_events.h"
#include "app_mgr.h"
#include "lcd_font.h"
#include "lcd.h"
#include "btn.h"

// Application structure
App app__mainmenu;
static App* app = &app__mainmenu;

static uint8_t chosenline = 0;

#define BUF(l,c) buf[LCD_WIDTH*l+c]
static void draw_handler(uint8_t* buf) {
	BUF(chosenline,1) = 0xFF;
}

static void btn_pressed_handler(uint32_t btn) {
	if (btn & BTN_MASK_UP) {
		if (chosenline != 0) {
			--chosenline;
			app->needs_redraw = 1;
		}
	}
	if (btn & BTN_MASK_DOWN) {
		if (chosenline != 7) {
			++chosenline;
			app->needs_redraw = 1;
		}
	}
	if (btn & BTN_MASK_BACK) {
		app_quit();
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
