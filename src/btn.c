/*
 * btn.c
 *
 *  Created on: 10 kwi 2016
 *      Author: konrad
 */
#include "btn.h"
#include "stm32f10x_gpio.h"
#include "led.h"
//
//void btnInit() {
//	GPIO_InitTypeDef GPIO_InitStruct;
//	EXTI_InitTypeDef EXTI_InitStruct;
//	NVIC_InitTypeDef NVIC_InitStruct;
//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
//
//	// A0 btn
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//	// setting external interrupt
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);
//
//	EXTI_InitStruct.EXTI_Line = EXTI_Line0 | EXTI_Line1;
//	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//	EXTI_Init(&EXTI_InitStruct);
//
//	// setting NVIC
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
//
//	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
//	NVIC_Init(&NVIC_InitStruct);
//	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
//	NVIC_Init(&NVIC_InitStruct);
//}
//
//extern int counter;
//
//void EXTI0_IRQHandler() {
//	counter++;
//	lcdScroll(counter&0x3F);
//	EXTI_ClearITPendingBit(EXTI_Line0);
//}
//
//void EXTI1_IRQHandler() {
//	counter--;
//	lcdScroll(counter&0x3F);
//	EXTI_ClearITPendingBit(EXTI_Line1);
//}
