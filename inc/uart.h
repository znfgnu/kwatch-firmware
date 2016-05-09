/*
 * uart.h
 *
 *  Created on: 8 maj 2016
 *      Author: konrad
 */

#ifndef UART_H_
#define UART_H_

int uart_open(USART_TypeDef* USARTx, uint32_t baud);
void uart_close(USART_TypeDef* USARTx);
int uart_putc(int c, USART_TypeDef* USARTx);
int uart_getc(USART_TypeDef* USARTx);

#endif /* UART_H_ */
