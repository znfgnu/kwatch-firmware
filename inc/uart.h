/*
 * uart.h
 *
 *  Created on: 8 maj 2016
 *      Author: konrad
 */

#ifndef UART_H_
#define UART_H_

#define INPUT_BUFFER_SIZE	200

extern char input_buffer[];
extern uint8_t buffer_ready;	// 0 -> filling in progress, 1 -> reading in progress

void uart_init();

#endif /* UART_H_ */
