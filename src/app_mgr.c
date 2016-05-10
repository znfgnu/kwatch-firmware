/*
 * app_mgr.c
 *
 *  Created on: 9 maj 2016
 *      Author: konrad
 */

#include "app_mgr.h"
#include "lcd.h"

App* foreground;

void app_init(App* app, uint32_t id, void (*handler)(APP_ARGS_PROTO)) {
	app->id = id;
	app->handler = handler;
}

void app_sleep(App* app) {
	// 1. Copy framebuffer
	for (int i=0; i<UI_APP_HEIGHT; ++i)
		for (int j=0; j<UI_APP_WIDTH; ++j)
			app->framebuffer[i][j] = lcd_buffer[i+1][j];

}

void app_wakeup(App* app) {
	// 1. Copy framebuffer
	foreground = app;
	app_updatescreen(app);
}

void app_updatescreen(App* app) {
	if (foreground != app) return;
	for (int i=0; i<UI_APP_HEIGHT; ++i)
		for (int j=0; j<UI_APP_WIDTH; ++j)
			lcd_buffer[i+1][j] = app->framebuffer[i][j];
	lcd_update();
}
