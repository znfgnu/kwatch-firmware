/*
 * icons8px.c
 *
 *  Created on: 17 lis 2016
 *      Author: konrad
 */

#include <stdint.h>
#include "icons8px.h"
#include "lcd.h"

icons8px_icon_t icon_exclamation = { 0x00, 0x7F, 0x7F, 0x7F, 0x51, 0x7F, 0x7F,
		0x7F };

void icons8px_draw_icon(icons8px_icon_t icon, int line, int col,
		lcd_buffer_t buf) {
	for (int i = 0; i < 8; i++) {
		buf[line][col++] = *(icon++);
	}
}
