/*
 * dummy.c
 *
 *  Created on: 14 kwi 2017
 *      Author: konrad
 */
#include <app.h>
#include <app_event.h>
#include "apps/dummy.h"
#include "lcd_font.h"
#include "lcd.h"
#include "btn.h"

// Application structure
App_t app__dummy;

static void draw_handler(lcd_buffer_t buf) {
	lcd_font_print_string("Nothing to do here! \x02", 3, 1, buf);
}

static void btn_pressed_handler(uint32_t btn) {
	if (btn & BTN_MASK_BACK) {
		app_quit();
	}
}

static void handler(uint32_t id, void* data) {
	switch (id) {
	case APP_EVENT_SPAWN:
		app__dummy.needs_redraw = 1;
		break;
	case APP_EVENT_DRAW:
		draw_handler(data);
		break;
	case APP_EVENT_BTN_PRESSED:
		btn_pressed_handler((uint32_t) data);
		break;
	}
}

void app__dummy_init() {
	app_init(&app__dummy, APP__DUMMY_ID, &handler,
			APP_EVENT_BTN_PRESSED | APP_EVENT_DRAW,	// foreground
			0);
}
