/*
 * led.h
 *
 *  Drives LEDs on Discovery board
 *
 *  Created on: 5 kwi 2016
 *      Author: konrad
 */

#ifndef LED_H_
#define LED_H_

#include <stdint.h>
#include "stm32f10x_gpio.h"

#define LED_GREEN	GPIO_Pin_1
#define LED_VIBR	GPIO_Pin_2
#define LED_ORANGE	0x2000
#define LED_RED		0x4000
#define LED_BLUE	0x8000

void led_init(void);
void led_on(uint32_t);
void led_off(uint32_t);

#endif /* LED_H_ */
