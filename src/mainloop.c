/*
 * mainloop.c
 *
 *  Created on: 7 lis 2016
 *      Author: konrad
 */

#include "mainloop.h"
#include "led.h"
#include "lcd.h"
#include "dma.h"
#include "app_mgr.h"
#include "app_events.h"
#include "app__serial.h"
#include "app__watchface.h"
#include "timers.h"
#include "btn.h"

void run() {


	lcd_clearbuffer();
	(foreground->handler)(APP_EVENT_DRAW, (void*)lcd_buffer);
	lcd_update();

	for(int i=0; ;) {
//		led_on(LED_VIBR);	// on means off when wibrating motor
//		uint8_t c = getDMAchar();//uart_getc(USART1);
//		led_off(LED_VIBR);  // similar

		__WFI();

		// TODO manage events

		// 1. second event
		while (timer_seconds > 0) {
			app__watchface.handler(APP_EVENT_SECOND_ELAPSED, (void*)0);
			timer_seconds--;
		}

		// 2. buttons event
		// TODO
		if (btn_pushed) {
			(foreground->handler)(APP_EVENT_BTN_PRESSED, (void*)btn_pushed);
			btn_pushed = 0;
		}
		if (btn_held) {
			(foreground->handler)(APP_EVENT_BTN_HELD, (void*)btn_held);
			btn_held = 0;
		}
		if (btn_released) {
			(foreground->handler)(APP_EVENT_BTN_RELEASED, (void*)btn_released);
			btn_released = 0;
		}


		if (foreground->needs_redraw) {
			lcd_clearbuffer();
			(foreground->handler)(APP_EVENT_DRAW, (void*)lcd_buffer);
			foreground->needs_redraw=0;
			lcd_update();
		}

//		(app__serial.handler)(APP_EVENT_BT_BYTE, (void*)c);

		i++;
//		if (i&1) led_on(LED_GREEN);
//		else led_off(LED_GREEN);
	}
}
