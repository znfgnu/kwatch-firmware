/*
 * app__watchface.c
 *
 *  Created on: 17 lis 2016
 *      Author: konrad
 */

#include <app_event.h>
#include <apps/mainmenu.h>
#include <apps/serial.h>
#include <apps/watchface.h>
#include "lcd_watchface_font.h"
#include "lcd_font.h"
#include "lcd.h"
#include "strings.h"
#include "icons8px.h"
#include "btn.h"

// Application structure
App_t app__watchface;

static uint8_t time[6] = { 2, 3, 5, 9, 5, 5 };
static uint16_t date[3] = { 28, 2, 2017 };

#ifdef APP__WATCHFACE_DEBUG
char* lastev = "Hello!";
uint8_t btn_no = 0x0F;
#endif

static void watchface_draw(lcd_buffer_t drawbuf) {
	int startcol = 8;
	int startline = 1;

	for (int dig = 0; dig < 4; dig++) {
		uint8_t digit = time[dig];
		const uint8_t* font_dig = lcd_watchface_font[digit];

		for (int col = 0; col < 24; col++) {
			for (int line = 0; line < 4; line++) {
				drawbuf[startline + line][startcol + col] = *(font_dig);
				font_dig++;
			}
		}
		startcol += 24;
		if (dig == 1)
			startcol += 16;
	}

	// todo: colon
	if (time[5] & 1) {
		startcol = 8 + 2 * 24;
		drawbuf[2][startcol + 7] = 0x03;
		drawbuf[3][startcol + 7] = 0xC0;
		drawbuf[2][startcol + 8] = 0x03;
		drawbuf[3][startcol + 8] = 0xC0;
	}

	// date
	startcol = 8;
	startline = 6;

	if (date[0] > 9) {
		lcd_font_print_char('0' + date[0] / 10, startline, startcol, drawbuf);
		startcol += LCD_FONT_DEFAULT_WIDTH_TOTAL;
	}
	lcd_font_print_char('0' + date[0] % 10, startline, startcol, drawbuf);
	startcol += LCD_FONT_DEFAULT_WIDTH_TOTAL * 2;	// plus space

	lcd_font_print_string(strings_months_short[date[1] - 1], startline,
			startcol, drawbuf);

	// number of notifications
	startcol = 112;
	icons8px_draw_icon(icon_exclamation, startline, startcol, drawbuf);

#ifdef APP__WATCHFACE_DEBUG
	// seconds (debug)
	startcol = LCD_WIDTH - 2*LCD_FONT_DEFAULT_WIDTH_TOTAL;
	startline = 7;

	lcd_font_print_char('0'+time[4], startline, startcol, drawbuf);
	lcd_font_print_char('0'+time[5], startline, startcol+LCD_FONT_DEFAULT_WIDTH_TOTAL, drawbuf);

	startcol = 0;
	startline = 7;

	lcd_font_print_char('0'+btn_no, startline, startcol, drawbuf);
	startcol+=LCD_FONT_DEFAULT_WIDTH_TOTAL*2;
	lcd_font_print_string(lastev, startline, startcol, drawbuf);
#endif
}

#define APPS__WATCHFACE_IS_LEAP(x)	((x%4 == 0 && x%100!=0)||(x%400 == 0))

static int days_in_month(uint16_t month, uint16_t year) {
	static const uint8_t days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31,
			30, 31 };
	if (month == 2 && APPS__WATCHFACE_IS_LEAP(year)) {
		return 29;
	}
	return days[month - 1];
}

static void watchface_secondelapsed() {
	app__watchface.needs_redraw = 1;// TODO: change to each minute after debug
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
						date[0]++;
						if (date[0] == days_in_month(date[1], date[2]) + 1) {
							date[0] = 1;
							date[1]++;
							if (date[1] == 13) {
								date[1] = 1;
								date[2]++;
							}
						}
					} else if (time[1] == 10) {
						time[1] = 0;
						time[0]++;
					}
				}
			}
		}
	}
}

static void watchface_btn_pressed(uint32_t btn) {
#ifdef APP__WATCHFACE_DEBUG
	btn_no = btn;
	lastev = "pressed";
	app__watchface.needs_redraw = 1;
#endif

	if (btn & BTN_MASK_OK) {// on released, because on held debug will appear
		app_spawn(&app__mainmenu);
	}

	if (btn & BTN_MASK_BACK) {
		lcd_turnon(lcd_is_on ^ 1);
	} else if (!lcd_is_on) {
		lcd_turnon(1);
	}
}

static void watchface_btn_held(uint32_t btn) {
#ifdef APP__WATCHFACE_DEBUG
	btn_no = btn;
	lastev = "held";
	app__watchface.needs_redraw = 1;
#endif
}
static void watchface_btn_released(uint32_t btn) {
#ifdef APP__WATCHFACE_DEBUG
	btn_no = btn;
	lastev = "released";
	app__watchface.needs_redraw = 1;
#endif
}

static void watchface_msg(char* data) {
	date[2] = 0;
	for (int dig = 0; dig < 4; dig++) {
		date[2] *= 10;
		date[2] += data[dig] - '0';
	}
	date[1] = 0;
	for (int dig = 4; dig < 6; dig++) {
		date[1] *= 10;
		date[1] += data[dig] - '0';
	}
	date[0] = 0;
	for (int dig = 6; dig < 8; dig++) {
		date[0] *= 10;
		date[0] += data[dig] - '0';
	}
	for (int dig = 8; dig < 14; dig++) {
		time[dig-8] = data[dig] - '0';
	}
	app__watchface.needs_redraw = 1;
}

static void watchfacehandler(uint32_t id, void* data) {
	switch (id) {
	case APP_EVENT_SPAWN:
		app__watchface.needs_redraw = 1;
		break;
	case APP_EVENT_DRAW:
		watchface_draw(data);
		break;
	case APP_EVENT_SECOND_ELAPSED:
		watchface_secondelapsed();
		break;
	case APP_EVENT_BTN_PRESSED:
		watchface_btn_pressed((uint32_t) data);
		break;
	case APP_EVENT_BTN_HELD:
		watchface_btn_held((uint32_t) data);
		break;
	case APP_EVENT_BTN_RELEASED:
		watchface_btn_released((uint32_t) data);
		break;
	case APP_EVENT_BT_MSG:
		watchface_msg((char*) data);
		break;
	}
}

void app__watchface_init() {
	app_init(&app__watchface, APP__WATCHFACE_ID, &watchfacehandler,
			APP_EVENT_BTN_HELD | APP_EVENT_BTN_PRESSED | APP_EVENT_BTN_RELEASED
					| APP_EVENT_DRAW | APP_EVENT_SECOND_ELAPSED,// foreground
			APP_EVENT_SECOND_ELAPSED);
}
