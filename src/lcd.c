/*
 * lcd.c
 *
 *  Created on: 5 kwi 2016
 *      Author: konrad
 */

#include "lcd.h"
#include "stm32f10x_i2c.h"

// private functions
void lcdI2CWrite(uint8_t);
void lcdI2CStart(uint8_t);
void lcdI2CStop();
void lcdI2CInit();

void lcdInit() {
	lcdI2CInit();

	lcdI2CStart(LCD_I2C_ADDR);

	// -- start copy-paste --
	lcdI2CWrite(0x00);	// register

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



	// -- draw sth --

	lcdI2CWrite(0xB0 + 1);
	lcdI2CWrite(0x00);
	lcdI2CWrite(0x10);

	lcdI2CStop();
	lcdI2CStart(LCD_I2C_ADDR);
	lcdI2CWrite(0x40);		// register (GDDRAM register?)

	for(int i=0; i<LCD_WIDTH; i++) {
		lcdI2CWrite(0xFF);
	}

	// -- end copy-paste --

	lcdI2CStop();

}

void lcdScroll(uint8_t lines) {
	lcdI2CStart(LCD_I2C_ADDR);
	lcdI2CWrite(0x00);	// register

	lcdI2CWrite(0xD3);

	lcdI2CWrite(lines);	// register
	lcdI2CStop();
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
	I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);	// works when debugger stops here

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));	// doesn't work when debugger stops here

	I2C1->SR1;	// read value (what debugger does)
}

void lcdI2CStop() {
	I2C_GenerateSTOP(I2C1, ENABLE);
}

void lcdI2CInit() {
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);		// PB6-7 -> I2C1 pins pack 1
//	RCC_AHB1PeriphClockCmd(RCC_AHB, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;			// alternate function (I2C here)
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;			// open drain - why?
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);

	// connects pins to alternate function
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C1);
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C1);

	I2C_InitStruct.I2C_ClockSpeed = 400000;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;				// don't care when master
	I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &I2C_InitStruct);

	I2C_Cmd(I2C1, ENABLE);
}
