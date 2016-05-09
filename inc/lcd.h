/*
 * lcd.h
 *
 *  Created on: 5 kwi 2016
 *      Author: konrad
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

#define LCD_I2C_ADDR	0x78

#define LCD_WIDTH		128
#define LCD_HEIGHT		64

void lcdInit(void);
void lcdScroll(uint8_t);


uint8_t a();

#endif /* LCD_H_ */
