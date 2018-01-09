/*
 * uart.c
 *
 *  Created on: 8 maj 2016
 *      Author: konrad
 */

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>
#include "uart.h"
#include "config.h"

char uart_input_buffer[INPUT_BUFFER_SIZE];
static char* uart_input_cursor = uart_input_buffer;
uint8_t uart_buffer_ready = 0;	// 0 -> filling in progress, 1 -> reading in progress
// TODO: more buffers!

void uart_init() {
	/*
	 * UART is configured on pins PA9 and PA10 of USART1 peripheral
	 */
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructureTx;
	GPIO_InitTypeDef GPIO_InitStructureRx;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// Configure TX pin
	GPIO_InitStructureTx.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructureTx.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructureTx.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructureTx);

	// Configure RX pin
	GPIO_InitStructureRx.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructureRx.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructureRx);

	// Configure UART peripheral
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = BT_USART_BAUD;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);

	// Configure interrupt
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

// Interrupt handlers

void USART1_IRQHandler() {
	if (USART_GetITStatus(USART1, USART_IT_RXNE)) {
		if (uart_buffer_ready == 0) {
			*uart_input_cursor = USART1->DR;
			if (*uart_input_cursor == '\0') {
				// go to next buffer
				uart_input_cursor = uart_input_buffer;
				uart_buffer_ready = 1;
			} else {
				uart_input_cursor++;
			}
		} else {
			// error, no space for more bytes
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);	// reading data register clears flag
		}

	}
}

