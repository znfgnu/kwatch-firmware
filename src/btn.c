/*
 * btn.c
 *
 *  Created on: 10 kwi 2016
 *      Author: konrad
 */
#include "btn.h"
#include "stm32f10x_gpio.h"

uint32_t btn_state[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
int btn_pushed;
int btn_held;
int btn_released;

void btn_init() {
	// Just input configuration, debouncing in timers.c
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
			| GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}
