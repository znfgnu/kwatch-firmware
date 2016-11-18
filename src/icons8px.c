/*
 * icons8px.c
 *
 *  Created on: 17 lis 2016
 *      Author: konrad
 */

#include <stdint.h>
#include "icons8px.h"
#include "lcd.h"

uint8_t icon_exclamation[8] = { 0xFF, 0xFF, 0xFF, 0xA1,0xA1, 0xFF, 0xFF, 0xFF };

void draw_icon(uint8_t* icon, int line, int col) {
	for (int i=0; i<8; i++) {
		lcd_buffer[line][col++] = *(icon++);
	}
}
