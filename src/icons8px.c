/*
 * icons8px.c
 *
 *  Created on: 17 lis 2016
 *      Author: konrad
 */

#include <stdint.h>
#include "icons8px.h"
#include "lcd.h"

icons8px_icon_t icon_exclamation = { 0xFF, 0xFF, 0xFF, 0xA1, 0xA1, 0xFF, 0xFF,
		0xFF };

void icons8px_draw_icon(icons8px_icon_t icon, int line, int col,
		lcd_buffer_t buf) {
	for (int i = 0; i < 8; i++) {
		buf[line][col++] = *(icon++);
	}
}
