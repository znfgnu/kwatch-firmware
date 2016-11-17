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

extern uint32_t btn_state[];
extern uint8_t btn_pushed;
extern uint8_t btn_held;
extern uint8_t btn_released;

#define BTN_BACK	0
#define BTN_UP		1
#define BTN_OK		2
#define BTN_DOWN	3

#define BTN_MASK_BACK	0x01
#define BTN_MASK_UP		0x02
#define BTN_MASK_OK		0x04
#define BTN_MASK_DOWN	0x08

// Buttons pulled UP

#define BTN_PUSHED		0x0E	// 2 last readings are "pushed", following 2 "released" bits, checking last 4 bits
#define BTN_HELD		0x80000000	// only earliest bit "released", checking 32 bits
#define BTN_RELEASED	0x01	// 2 last readings are "released", following 2 "pushed" bits, checking last 4 bits

#define BTN_PORT_OFFSET	12		// btns starting from pin 12

#endif /* BTN_H_ */
