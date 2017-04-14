/*
 * mainloop.c
 *
 *  Created on: 7 lis 2016
 *      Author: konrad
 */

#include <apps/serial.h>
#include <apps/watchface.h>
#include "mainloop.h"
#include "led.h"
#include "lcd.h"
#include "app_mgr.h"
#include "app_events.h"
#include "timers.h"
#include "btn.h"
#include "uart.h"

void run() {
	app_spawn(&app__watchface);	// root app

	lcd_clearbuffer();
	app_notify_event(APP_EVENT_DRAW, (void*)lcd_buffer);
	lcd_update();

	for(;;) {
		App* top_app = app_get_active_app();
		if (top_app == foreground) __WFI();
		else {
			foreground = top_app;
			foreground->handler(APP_EVENT_SPAWN, (void*)0);
		}

		// TODO manage events

		// 1. second event
		while (timer_seconds > 0) {
			app_notify_event(APP_EVENT_SECOND_ELAPSED, (void*)0);
			timer_seconds--;
		}

		// 2. buttons event
		if (btn_pushed) {
			app_notify_event(APP_EVENT_BTN_PRESSED, (void*)btn_pushed);
			btn_pushed = 0;
		}
		if (btn_held) {
			app_notify_event(APP_EVENT_BTN_HELD, (void*)btn_held);
			btn_held = 0;
		}
		if (btn_released) {
			app_notify_event(APP_EVENT_BTN_RELEASED, (void*)btn_released);
			btn_released = 0;
		}

		// 3. bluetooth message
		if (buffer_ready) {
			app_notify_event(APP_EVENT_BT_MSG, (void*)input_buffer);
			buffer_ready = 0;
		}

		// if needs redraw, do it now.
		if (foreground->needs_redraw && lcd_is_on) {
			foreground->needs_redraw=0;
			lcd_clearbuffer();
			app_notify_event(APP_EVENT_DRAW, (void*)lcd_buffer);
			lcd_update();
		}
	}
}
