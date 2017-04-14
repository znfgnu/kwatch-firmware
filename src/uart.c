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

char input_buffer[INPUT_BUFFER_SIZE];
char* input_cursor = input_buffer;
uint8_t buffer_ready = 0;	// 0 -> filling in progress, 1 -> reading in progress
// TODO: more buffers!

int uart_open (USART_TypeDef* USARTx, uint32_t baud)
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructureTx;
  GPIO_InitTypeDef GPIO_InitStructureRx;

  assert_param(IS_USART_123_PERIPH(USARTx));

  if (USARTx == USART1) {

    // Turn on clocks

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  |
			   RCC_APB2Periph_AFIO,
			   ENABLE);

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

    // Configure the UART

    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_Mode  = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1,&USART_InitStructure);
    USART_Cmd(USART1, ENABLE);

    return 0;
  }
  return 1;
}

void uart_interrupt_init() {
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_ITConfig(BT_USART_PORT, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = BT_USART_IRQN;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void uart_init() {
	uart_open(BT_USART_PORT, BT_USART_BAUD);
	uart_interrupt_init();
}

void USART1_IRQHandler() {
	if( USART_GetITStatus(BT_USART_PORT, USART_IT_RXNE)) {
		if (buffer_ready == 0) {
			*input_cursor = BT_USART_PORT->DR;
			if (*input_cursor == '\0') {
				// go to next buffer
				input_cursor = input_buffer;
				buffer_ready = 1;
			} else {
				input_cursor++;
			}
		}
		else {
			// error, no space for more bytes
			USART_ClearITPendingBit(BT_USART_PORT, USART_IT_RXNE);	// reading data register clears flag
		}

	}
}

