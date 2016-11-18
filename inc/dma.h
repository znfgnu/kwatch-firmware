/*
 * dma.h
 *
 *  Created on: 18 maj 2016
 *      Author: konrad
 */

#ifndef DMA_H_
#define DMA_H_

#include "stm32f10x_dma.h"

#define DMA_BUFFER_SIZE		100

void dma_init();
char getDMAchar();

#endif /* DMA_H_ */
