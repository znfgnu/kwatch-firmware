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

void run() {


	lcd_clearbuffer();
	(foreground->handler)(APP_EVENT_DRAW, (void*)lcd_buffer);
	lcd_update();

	for(int i=0; ;) {
//		led_on(LED_VIBR);	// on means off when wibrating motor
//		uint8_t c = getDMAchar();//uart_getc(USART1);
//		led_off(LED_VIBR);  // similar

		__WFI();

//		(app__serial.handler)(APP_EVENT_BT_BYTE, (void*)c);

		// nierozlaczne
//		lcd_clearbuffer();
//		(app__serial.handler)(APP_EVENT_DRAW, (void*)lcd_buffer);
//		lcd_update();

		i++;
		if (i&1) led_on(LED_GREEN);
		else led_off(LED_GREEN);
	}
}
