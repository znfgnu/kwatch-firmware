/*
 * lcd.c
 *
 *  Created on: 5 kwi 2016
 *      Author: konrad
 */

#include "lcd.h"
#include "lcd_font.h"
#include "stm32f10x_i2c.h"


// private functions
void lcdI2CWrite(uint8_t);
void lcdI2CStart(uint8_t);
void lcdI2CStop();
void lcdI2CInit();
void lcdI2CUpdatePage(uint8_t, uint8_t*);
void lcdI2CUpdateScreen(uint8_t*);

uint8_t lcd_buffer[LCD_PAGES][LCD_WIDTH];

void lcd_init() {
	lcdI2CInit();

	lcdI2CStart(LCD_I2C_ADDR);
	lcdI2CWrite(LCD_I2C_CMD_TOKEN);

	lcdI2CWrite(0xAE); //display off
	lcdI2CWrite(0x20); //Set Memory Addressing Mode
	lcdI2CWrite(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	lcdI2CWrite(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	lcdI2CWrite(0xC8); //Set COM Output Scan Direction
	lcdI2CWrite(0x00); //---set low column address
	lcdI2CWrite(0x10); //---set high column address
	lcdI2CWrite(0x40); //--set start line address
	lcdI2CWrite(0x81); //--set contrast control register
	lcdI2CWrite(0xFF);
	lcdI2CWrite(0xA1); //--set segment re-map 0 to 127
	lcdI2CWrite(0xA6); //--set normal display
	lcdI2CWrite(0xA8); //--set multiplex ratio(1 to 64)
	lcdI2CWrite(0x3F); //
	lcdI2CWrite(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	lcdI2CWrite(0xD3); //-set display offset
	lcdI2CWrite(0x00); //-not offset
	lcdI2CWrite(0xD5); //--set display clock divide ratio/oscillator frequency
	lcdI2CWrite(0xF0); //--set divide ratio
	lcdI2CWrite(0xD9); //--set pre-charge period
	lcdI2CWrite(0x22); //
	lcdI2CWrite(0xDA); //--set com pins hardware configuration
	lcdI2CWrite(0x12);
	lcdI2CWrite(0xDB); //--set vcomh
	lcdI2CWrite(0x20); //0x20,0.77xVcc
	lcdI2CWrite(0x8D); //--set DC-DC enable
	lcdI2CWrite(0x14); //
	lcdI2CWrite(0xAF); //--turn on SSD1306 panel

	lcdI2CWrite(0xB0);
	lcdI2CWrite(0x00);
	lcdI2CWrite(0x10);
	lcdI2CStop();

	lcdI2CUpdateScreen((uint8_t*)lcd_buffer);
}

void lcd_scroll(uint8_t lines) {
	lcdI2CStart(LCD_I2C_ADDR);
	lcdI2CWrite(LCD_I2C_CMD_TOKEN);	// register
	lcdI2CWrite(0xD3);
	lcdI2CWrite(lines);	// register
	lcdI2CStop();
}

void lcd_invert(uint8_t inverted) {
	lcdI2CStart(LCD_I2C_ADDR);
	lcdI2CWrite(LCD_I2C_CMD_TOKEN);
	lcdI2CWrite(LCD_CMD_INVERTED(inverted));
	lcdI2CStop();
}

void lcd_set_contrast(uint8_t contrast) {
	lcdI2CStart(LCD_I2C_ADDR);
	lcdI2CWrite(LCD_I2C_CMD_TOKEN);
	lcdI2CWrite(0x81); //--set contrast control register
	lcdI2CWrite(contrast);
	lcdI2CStop();
}

void lcd_update() {
	lcdI2CUpdateScreen((uint8_t*)lcd_buffer);
}

void lcd_clearbuffer() {
	for (int i=0; i<LCD_PAGES; ++i) {
		for (int j=0; j<LCD_HEIGHT; ++j) {
			lcd_buffer[i][j] = 0x00;
		}
	}
}

// --- begin private functions


// stupid. wasting CPU time for displaying data
void lcdI2CWrite(uint8_t data) {
	I2C_SendData(I2C1, data);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

void lcdI2CStart(uint8_t addr) {
	// wait until not busy
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	// generate start
	I2C_GenerateSTART(I2C1, ENABLE);

	// wait until slave acknowledged start condition
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// stm is transmitter
	I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
}

void lcdI2CStop() {
	I2C_GenerateSTOP(I2C1, ENABLE);
}

void lcdI2CInit() {
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);		// PB6-7 -> I2C1 pins pack 1

//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;			// alternate function (I2C here)
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);

	I2C_InitStruct.I2C_ClockSpeed = 400000;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;				// don't care when master
	I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &I2C_InitStruct);

	I2C_Cmd(I2C1, ENABLE);
}

void lcdI2CUpdatePage(uint8_t page_number, uint8_t* buffer) {
	lcdI2CStart(LCD_I2C_ADDR);
	lcdI2CWrite(LCD_I2C_CMD_TOKEN);
	lcdI2CWrite(0xB0 + page_number);
	lcdI2CWrite(0x00);
	lcdI2CWrite(0x10);
	lcdI2CStop();

	lcdI2CStart(LCD_I2C_ADDR);
	lcdI2CWrite(LCD_I2C_DATA_TOKEN);		// register (GDDRAM register?)

	for(int i=0; i<LCD_WIDTH; i++)
		lcdI2CWrite(buffer[i]);

	lcdI2CStop();
}

void lcdI2CUpdateScreen(uint8_t* buffer) {
	for (int i=0; i<LCD_PAGES; ++i)
		lcdI2CUpdatePage(i, buffer+LCD_WIDTH*i);
}
