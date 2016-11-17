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

static uint8_t time[6] = {2, 3, 5, 8, 0, 0};
static uint16_t date[3] = {15, 1, 2017};
//		hours_tens = 0,
//		hours_units = 0,
//		minutes_tens = 0,
//		minutes_units = 0;


//debug

char* lastev = "Brak";
uint8_t btn_no = 8;

//-debug

#define BUF2(x,y) drawbuf[LCD_WIDTH*(x)+(y)]
static void watchface_draw(uint8_t* drawbuf) {
	int startcol = 8;
	int startline = 1;

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
	startcol += LCD_FONT_DEFAULT_WIDTH_TOTAL * 2;	// plus space

	print_string(months[date[1]-1], startline, startcol);


	// number of notifications
	startcol = 112;
	draw_icon(icon_exclamation, startline, startcol);

	// seconds (debug)
	startcol = LCD_WIDTH - 2*LCD_FONT_DEFAULT_WIDTH_TOTAL;
	startline = 7;

	print_char('0'+time[4], startline, startcol);
	print_char('0'+time[5], startline, startcol+LCD_FONT_DEFAULT_WIDTH_TOTAL);

	startcol = 0;
	startline = 7;

	print_char('0'+btn_no, startline, startcol);
	startcol+=LCD_FONT_DEFAULT_WIDTH_TOTAL*2;
	print_string(lastev, startline, startcol);
}

static void watchface_secondelapsed() {
	app->needs_redraw = 1;	// TODO: change to each minute after debug
	time[5]++;
	if (time[5] == 10) {
		time[5] = 0;
		time[4]++;
		if (time[4] == 6) {
			time[4] = 0;
			time[3]++;
			if (time[3] == 10) {
				time[3] = 0;
				time[2]++;
				if (time[2] == 6) {
					time[2] = 0;
					time[1]++;
					if (time[1] == 4 && time[0] == 2) {
						time[1] = 0;
						time[0] = 0;
					}
					else if (time[1] == 10) {
						time[1] = 0;
						time[0]++;
					}
				}
			}
		}
	}
}

static void watchface_btn_pressed(uint32_t btn) {
	btn_no = btn;
	lastev = "pressed";
	app->needs_redraw = 1;
}
static void watchface_btn_held(uint32_t btn) {
	btn_no = btn;
	lastev = "held";
	app->needs_redraw = 1;
}
static void watchface_btn_released(uint32_t btn) {
	btn_no = btn;
	lastev = "released";
	app->needs_redraw = 1;
}

void watchfacehandler(APP_ARGS) {
	switch(id) {
//	case APP_EVENT_BT_BYTE:
//		watchface_handle_char((uint8_t)data);
//		break;
	case APP_EVENT_DRAW:
		watchface_draw((uint8_t*)data);
		break;
	case APP_EVENT_SECOND_ELAPSED:
		watchface_secondelapsed();
		break;
	case APP_EVENT_BTN_PRESSED:
		watchface_btn_pressed((uint32_t)data);
		break;
	case APP_EVENT_BTN_HELD:
		watchface_btn_held((uint32_t)data);
		break;
	case APP_EVENT_BTN_RELEASED:
		watchface_btn_released((uint32_t)data);
		break;
	}
}


void app__watchface_init() {
	app_init(app, APP__WATCHFACE_ID, &watchfacehandler);
}
