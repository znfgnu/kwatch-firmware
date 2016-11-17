/*
 * app_mgr.c
 *
 *  Created on: 9 maj 2016
 *      Author: konrad
 */

#include "app_mgr.h"
#include "app_events.h"
#include "lcd.h"

App* foreground;

void app_init(App* app, uint32_t id, void (*handler)(APP_ARGS_PROTO)) {
	app->id = id;
	app->handler = handler;
	app->needs_redraw = 0;
}

void app_sleep(App* app) {
	// ?
}

void app_wakeup(App* app) {
	// 1. Copy framebuffer
	foreground = app;
	foreground->needs_redraw = 1;
}
