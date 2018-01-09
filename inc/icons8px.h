/*
 * icons8px.h
 *
 *  Created on: 17 lis 2016
 *      Author: konrad
 */

#ifndef ICONS8PX_H_
#define ICONS8PX_H_

#include "lcd.h"

typedef uint8_t icons8px_icon_t[8];

extern icons8px_icon_t icon_exclamation;
void icons8px_draw_icon(icons8px_icon_t, int, int, lcd_buffer_t);

#endif /* ICONS8PX_H_ */
