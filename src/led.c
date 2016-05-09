/*
 * led.c
 *
 *  Created on: 5 kwi 2016
 *      Author: konrad
 */

#include "led.h"
#include "stm32f10x_gpio.h"

void led_init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void led_on(uint32_t led) {
	GPIO_ResetBits(GPIOA, led);
}

void led_off(uint32_t led) {
	GPIO_SetBits(GPIOA, led);
}
