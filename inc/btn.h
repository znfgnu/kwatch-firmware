/*
 * btn.h
 *
 *  Created on: 10 kwi 2016
 *      Author: konrad
 */

#ifndef BTN_H_
#define BTN_H_

#include <stdint.h>

void btn_init();

extern uint32_t btn_state[];	// Array that stores last 32 state readings of each button
extern int btn_pushed;	// Bitmask telling which button is pushed
extern int btn_held;	// Bitmask telling which button is held
extern int btn_released;	// Bitmask telling which button is released

#define BTN_OK_PORT  GPIOB
#define BTN_OK_PIN   GPIO_Pin_12
#define BTN_UP_PORT  GPIOC
#define BTN_UP_PIN   GPIO_Pin_13
#define BTN_DOWN_PORT  GPIOC
#define BTN_DOWN_PIN   GPIO_Pin_2
#define BTN_BACK_PORT  GPIOB
#define BTN_BACK_PIN   GPIO_Pin_2

#define BTN_NUM_OK		0
#define BTN_NUM_UP		1
#define BTN_NUM_DOWN		2
#define BTN_NUM_BACK		3

#define BTN_MASK_OK		0x01
#define BTN_MASK_UP		0x02
#define BTN_MASK_DOWN	0x04
#define BTN_MASK_BACK	0x08

// Buttons pulled UP
#define BTN_PUSHED		0x06	// 2 last readings are "released", following 1 "pushed" bit, checking last 3 bits
#define BTN_HELD		0x80000000	// only earliest bit "released", checking 32 bits
#define BTN_RELEASED	0x01	// 2 last readings are "pushed", following 1 "released" bit, checking last 3 bits

#define BTN_PORT_OFFSET	12	// Buttons starting from pin 12

#endif /* BTN_H_ */
