/*
 * mainloop.c
 *
 *  Created on: 7 lis 2016
 *      Author: konrad
 */

#include <stm32f10x.h>
#include <app.h>
#include <app_event.h>
#include <apps/serial.h>
#include <apps/watchface.h>
#include "mainloop.h"
#include "lcd.h"
#include "timers.h"
#include "btn.h"
#include "uart.h"

void mainloop_run() {
	app_spawn(&app__watchface);	// root app

	lcd_clearbuffer();
	app_notify_event(APP_EVENT_DRAW, (void*) lcd_buffer);
	lcd_update();

	for (;;) {
		App_t* top_app = app_get_active_app();
		if (top_app == foreground) {
			__WFI();
		} else {
			foreground = top_app;
			foreground->handler(APP_EVENT_SPAWN, (void*) 0);
		}

		// 1. "Second elapsed" event
		while (timer_seconds > 0) {
			app_notify_event(APP_EVENT_SECOND_ELAPSED, (void*) 0);
			timer_seconds--;
		}

		// 2. Buttons' events
		if (btn_pushed) {
			app_notify_event(APP_EVENT_BTN_PRESSED, (void*) btn_pushed);
			btn_pushed = 0;
		}
		if (btn_held) {
			app_notify_event(APP_EVENT_BTN_HELD, (void*) btn_held);
			btn_held = 0;
		}
		if (btn_released) {
			app_notify_event(APP_EVENT_BTN_RELEASED, (void*) btn_released);
			btn_released = 0;
		}

		// 3. Incoming bluetooth message event
		if (uart_buffer_ready) {
			app_notify_event(APP_EVENT_BT_MSG, (void*) uart_input_buffer);
			uart_buffer_ready = 0;
		}

		// If needs redrawing, do it now.
		if (foreground->needs_redraw && lcd_is_on) {
			foreground->needs_redraw = 0;
			lcd_clearbuffer();
			app_notify_event(APP_EVENT_DRAW, (void*) lcd_buffer);
			lcd_update();
		}
	}
}
