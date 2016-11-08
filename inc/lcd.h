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

// bytes sent at the beginning of transmission
#define LCD_I2C_DATA_TOKEN	0x40
#define LCD_I2C_CMD_TOKEN	0x00
// if only one byte is going to be sent, token has to be ORed with 0x80 (to set C0 bit)

// dimensions
#define LCD_WIDTH		128
#define LCD_HEIGHT		64
#define LCD_PAGES		(LCD_HEIGHT>>3)

// LCD fundamental commands
#define LCD_CMD_SETCONTRAST		0x81		// must be followed by byte with contrast value
#define LCD_CMD_INVERTED(x)		(0xA6|x)	// 0 - normal, 1 - inverted
#define LCD_CMD_DISPLAYON(x)	(0xAE|x)	// 0 - sleep mode, 1 - normal mode
#define LCD_CMD_FREEZERAM(x)	(0xA4|x)	// 0 - normal mode, LCD follows RAM content, 1 - RAM can change, LCD stays the same


extern uint8_t lcd_buffer[LCD_PAGES][LCD_WIDTH];

void lcd_init(void);
void lcd_scroll(uint8_t);
void lcd_invert(uint8_t);
void lcd_set_contrast(uint8_t);
void lcd_update();
void lcd_clearbuffer();

#endif /* LCD_H_ */
