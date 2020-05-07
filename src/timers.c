/*
 * timers.c
 *
 *  Created on: 17 lis 2016
 *      Author: konrad
 */

#include "timers.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"	// nvic
#include "btn.h"

int timer_seconds = 0;

static void timer_persecond_init() {
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN, ENABLE);

	// for 24 MHz:
	// timer ticks each 1ms
	// timer overflows each 1000ms (1sec)

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 12000;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 1000 - 1;	// [0, 999] -> 1000 steps
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_Cmd(TIM2, ENABLE);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 1;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);
}

static void timer_btndebounce_init() {
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN, ENABLE);

	// for 24 MHz:
	// timer ticks each 20us
	// timer overflows each 20ms

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 480;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 1000 - 1;	// [0, 999] -> 1000 steps
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &timerInitStructure);
	TIM_Cmd(TIM3, ENABLE);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = TIM3_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 1;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);
}

void timers_init() {
	timer_persecond_init();
	timer_btndebounce_init();
}

// Interrupt handlers

void TIM2_IRQHandler() {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		timer_seconds++;
	}
}

void TIM3_IRQHandler() {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

		// get buttons state
		uint16_t stateB = (GPIOB->IDR);
		uint16_t stateC = (GPIOC->IDR);

		for (int i = 0; i < 4; i++) {
			uint8_t state;

			switch (i) {
			case BTN_NUM_OK:
				state = stateB & BTN_OK_PIN ? 1 : 0;
				break;
			
			case BTN_NUM_UP:
				state = stateC & BTN_UP_PIN ? 1 : 0;
				break;
			
			case BTN_NUM_DOWN:
				state = stateC & BTN_DOWN_PIN ? 1 : 0;
				break;
			
			case BTN_NUM_BACK:
				state = stateB & BTN_BACK_PIN ? 1 : 0;
				break;
			
			default:
				state = 0;
				break;
			}

			btn_state[i] = (btn_state[i] << 1) | state; // push one bit

			if ((btn_state[i] & 0x07) == BTN_PUSHED) {
				btn_pushed |= (1 << i);
			} else if ((btn_state[i] & 0x07) == BTN_RELEASED) {
				btn_released |= (1 << i);
			} else if (btn_state[i] == BTN_HELD) {
				btn_held |= (1 << i);
			}
		}
	}
}
