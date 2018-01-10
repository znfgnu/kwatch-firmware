/*
 * app_mgr.c
 *
 *  Created on: 9 maj 2016
 *      Author: konrad
 */

#include <app_event.h>
#include "app.h"
#include "lcd.h"

App_t* foreground;
static App_t* apps[APP_MAX_APPS];	// process table (?)
static uint8_t number_of_apps = 0;

static App_t* stack[APP_MAX_APPS];
static uint8_t stack_size = 0;

void app_init(App_t* app, uint32_t id, app_handler_t handler,
		uint32_t events_foreground, uint32_t events_background) {
	app->id = id;
	app->handler = handler;
	app->needs_redraw = 0;
	app->events_when_background = events_background;
	app->events_when_foreground = events_foreground;
	apps[number_of_apps++] = app;
}

void app_notify_event(uint32_t id, void* data) {
	// bt messages sniffing protection
	if (id == APP_EVENT_BT_MSG) {
		for (int i = 0; i < number_of_apps; i++) {
			App_t* app = apps[i];
			if (*((uint8_t*) data) == app->id) {
				app->handler(id, data + 1);
				break;
			}
		}
	}

	else {
		for (int i = 0; i < number_of_apps; i++) {
			App_t* app = apps[i];
			if (app == foreground) {
				if (app->events_when_foreground & id) {
					app->handler(id, data);
				}
			} else if (app->events_when_background & id) {
				app->handler(id, data);
			}
		}
	}
}

void app_spawn(App_t* new_app) {
	stack[stack_size++] = new_app;
}

void app_quit() {
	stack[--stack_size] = (App_t*) 0;
}

App_t* app_get_active_app() {
	return stack[stack_size - 1];
}
