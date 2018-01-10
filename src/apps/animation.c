/*
 * dummy.c
 *
 *  Created on: 14 kwi 2017
 *      Author: konrad
 */
#include <app.h>
#include <app_event.h>
#include "apps/animation.h"
#include "lcd_font.h"
#include "lcd.h"
#include "btn.h"
#include "pseudo_rand.h"

// Application structure
App_t app__animation;

static int counter = 0;
static int fps = 0;

static int help_screen = 0;

#define APP__ANIMATION_MAX_ELEMENTS	500

static int active_elements = 3;
static unsigned char xx[APP__ANIMATION_MAX_ELEMENTS];
static unsigned char yy[APP__ANIMATION_MAX_ELEMENTS];
static char dx[APP__ANIMATION_MAX_ELEMENTS];
static char dy[APP__ANIMATION_MAX_ELEMENTS];

static void draw_handler(lcd_buffer_t buf) {
	if (help_screen) {
		lcd_font_print_string("Animation demo", 1, 10, buf);
		lcd_font_print_string("\x18 add particle", 2, 10, buf);
		lcd_font_print_string("\x19 remove particle", 3, 10, buf);
	} else {
		for (int i = 0; i < active_elements; i++) {
			if ((unsigned char)(xx[i] + dx[i]) >= LCD_WIDTH) {// || xx[i] + dx[i] < 0) {
				dx[i] = -dx[i];
			}
			if ((unsigned char)(yy[i] + dy[i]) >= LCD_PAGES * 8) {// || yy[i] + dy[i] < 0) {
				dy[i] = -dy[i];	// negative values are GREATER than LCD_WIDTH, because x and y are unsigned
			}
			xx[i] += dx[i];
			yy[i] += dy[i];

			buf[yy[i] / 8][xx[i]] = (1 << (yy[i] & 7));
		}
	}

	lcd_font_print_string("FPS:", 7, 128 - 35, buf);
	lcd_font_print_char('0' + fps / 10, 7, 128 - 10, buf);
	lcd_font_print_char('0' + fps % 10, 7, 128 - 5, buf);

	lcd_font_print_char('0' + active_elements / 100, 7, 0, buf);
	lcd_font_print_char('0' + active_elements / 10 % 10, 7, 5, buf);
	lcd_font_print_char('0' + active_elements % 10, 7, 10, buf);
	counter++;
}

static void btn_pressed_handler(uint32_t btn) {
	if (btn & BTN_MASK_UP) {
		active_elements++;
		if (active_elements > APP__ANIMATION_MAX_ELEMENTS) {
			active_elements = 0;
		}
	}
	if (btn & BTN_MASK_DOWN) {
		active_elements--;
		if (active_elements < 0) {
			active_elements = APP__ANIMATION_MAX_ELEMENTS;
		}
	}
	if (btn & BTN_MASK_BACK) {
		if (help_screen) {
			help_screen = 0;
		}
		else {
			app_quit();
		}
	}
	if (btn & BTN_MASK_OK) {
		help_screen ^= 1;
	}
}

static void handler(uint32_t id, void* data) {
	switch (id) {
	case APP_EVENT_SPAWN:
		app__animation.needs_redraw = 1;
		counter = 0;
		break;
	case APP_EVENT_DRAW:
		draw_handler(data);
		app__animation.needs_redraw = 1;
		break;
	case APP_EVENT_SECOND_ELAPSED:
		fps = counter;
		counter = 0;
		break;
	case APP_EVENT_BTN_PRESSED:
		btn_pressed_handler((uint32_t) data);
		break;
	}
}

void app__animation_init() {
	pseudo_rand_init(0xDEADBEEF);
	for (int i = 0; i < APP__ANIMATION_MAX_ELEMENTS; i++) {
		xx[i] = pseudo_rand_get() & 0x7F;	// [0; 127]
		yy[i] = pseudo_rand_get() & 0x3F;	// [0; 63]
		dx[i] = pseudo_rand_get() % 7 - 3;	// [-3; 3]
		dy[i] = pseudo_rand_get() % 7 - 3;	// [-3; 3]
	}
	app_init(&app__animation, APP__ANIMATION_ID, &handler,
			APP_EVENT_BTN_PRESSED | APP_EVENT_DRAW | APP_EVENT_SECOND_ELAPSED,	// foreground
			0);
}
