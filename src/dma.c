/*
 * dma.c
 *
 *  Created on: 18 maj 2016
 *      Author: konrad
 */

#include "dma.h"

char* dmaBuffer = "Hello!";

#define BUFSIZE 300
char buffer[BUFSIZE];
char* next=buffer;

void dma_init() {
	DMA_InitTypeDef dmaInitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);




	dmaInitStruct.DMA_BufferSize = strlen(dmaBuffer);
	dmaInitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	dmaInitStruct.DMA_M2M = DMA_M2M_Disable;
	dmaInitStruct.DMA_MemoryBaseAddr = dmaBuffer;
	dmaInitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dmaInitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dmaInitStruct.DMA_Mode = DMA_Mode_Normal;
	dmaInitStruct.DMA_PeripheralBaseAddr = &(USART1->DR);
	dmaInitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dmaInitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmaInitStruct.DMA_Priority = DMA_Priority_VeryHigh;

	DMA_DeInit(DMA1_Channel4);
	DMA_Init(DMA1_Channel4, &dmaInitStruct);
	DMA_Cmd(DMA1_Channel4, ENABLE);
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

	while(!DMA_GetFlagStatus(DMA1_FLAG_TC4));

	dmaInitStruct.DMA_BufferSize = BUFSIZE;
	dmaInitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	dmaInitStruct.DMA_M2M = DMA_M2M_Disable;
	dmaInitStruct.DMA_MemoryBaseAddr = buffer;
	dmaInitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dmaInitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dmaInitStruct.DMA_Mode = DMA_Mode_Circular;
	dmaInitStruct.DMA_PeripheralBaseAddr = &(USART1->DR);
	dmaInitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dmaInitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmaInitStruct.DMA_Priority = DMA_Priority_VeryHigh;

	for (int i=0; i<BUFSIZE; i++) buffer[i]=0xff;

	DMA_DeInit(DMA1_Channel5);
	DMA_Init(DMA1_Channel5, &dmaInitStruct);
	DMA_Cmd(DMA1_Channel5, ENABLE);
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

//	while(!DMA_GetFlagStatus(DMA1_FLAG_TC5));

}

char getDMAchar() {
	static char c;
	while((*next)==0xff);
	c = *next;
	*next = 0xff;
	next++;
	if (next == buffer+BUFSIZE) next=buffer;
	return c;
}
