/*
 * dummy.c
 *
 *  Created on: 14 kwi 2017
 *      Author: konrad
 */
#include "apps/dummy.h"
#include "app_events.h"
#include "app_mgr.h"
#include "lcd_font.h"
#include "lcd.h"
#include "btn.h"

// Application structure
App app__dummy;
static App* app = &app__dummy;

#define BUF(l,c) buf[LCD_WIDTH*(l)+(c)]
static void draw_handler(uint8_t* buf) {
	print_string("Nothing to do here! \x02", 3, 1, buf);
}

static void btn_pressed_handler(uint32_t btn) {
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
		break;
	}
}

void app__dummy_init() {
	app_init(app, APP__DUMMY_ID, &handler,
			APP_EVENT_BTN_PRESSED | APP_EVENT_DRAW,	// foreground
			0
			);
}
