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
static App* apps[APPMGR_MAX_APPS];	// process table (?)
static uint8_t number_of_apps = 0;

void app_init(App* app, uint32_t id, void (*handler)(APP_ARGS_PROTO), uint32_t events_foreground, uint32_t events_background) {
	app->id = id;
	app->handler = handler;
	app->needs_redraw = 0;
	app->events_when_background = events_background;
	app->events_when_foreground = events_foreground;
	apps[number_of_apps++] = app;
}

void app_sleep(App* app) {
	// ?
}

void app_wakeup(App* app) {
	foreground = app;
	foreground->needs_redraw = 1;
}

void app_notify_event(APP_ARGS) {
	for (int i=0; i<number_of_apps; i++) {
		App* app = apps[i];
		if (ISFOREGROUND(app)) {
			if (app->events_when_foreground & id) app->handler(id, data);
		}
		else if (app->events_when_background & id) app->handler(id, data);
	}
}
