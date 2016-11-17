/*
 * app__watchface.c
 *
 *  Created on: 17 lis 2016
 *      Author: konrad
 */

#include "app__watchface.h"
#include "app_events.h"
#include "lcd_watchface_font.h"
#include "lcd_font.h"
#include "lcd.h"
#include "strings.h"
#include "icons8px.h"

// Application structure
App app__watchface;
static App* app = &app__watchface;

static uint8_t time[4] = {0, 0, 0, 0};
static uint16_t date[3] = {15, 1, 2017};
//		hours_tens = 0,
//		hours_units = 0,
//		minutes_tens = 0,
//		minutes_units = 0;

#define BUF2(x,y) drawbuf[LCD_WIDTH*(x)+(y)]
static void watchface_draw(uint8_t* drawbuf) {
	static int startcol = 8;
	static int startline = 1;

	for (int dig = 0; dig<4; dig++) {
		uint8_t digit = time[dig];
		uint8_t* font_dig = lcd_font_watchface[digit];

		for (int col = 0; col<24; col++) {
			for (int line = 0; line<4; line++) {
				BUF2(startline+line, startcol+col) = *(font_dig);
				font_dig++;
			}
		}
		startcol+= 24;
		if (dig == 1) startcol += 16;
	}

	// todo: colon


	startcol = 8;
	startline = 6;
	if (date[0] > 9) {
		print_char('0'+date[0]/10, startline, startcol);
		startcol += LCD_FONT_DEFAULT_WIDTH_TOTAL;
	}
	print_char('0'+date[0]%10, startline, startcol);
	startcol += (LCD_FONT_DEFAULT_WIDTH_TOTAL * 2);	// plus space

	print_string(months[date[1]-1], startline, startcol);


	// number of notifications
	startcol = 112;
	draw_icon(icon_exclamation, startline, startcol);


}

void watchfacehandler(APP_ARGS) {
	switch(id) {
//	case APP_EVENT_BT_BYTE:
//		watchface_handle_char((uint8_t)data);
//		break;
	case APP_EVENT_DRAW:
		watchface_draw((uint8_t*)data);
		break;
	}
}


void app__watchface_init() {
	app_init(app, APP__WATCHFACE_ID, &watchfacehandler);
}
