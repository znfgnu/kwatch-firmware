/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "lcd.h"
#include "led.h"
#include "uart.h"

void Delay(uint32_t count){
	while(count--);
}

#define LITTLE_DELAY	3000000

int counter = 0;

int main(void)
{
	ledInit();
	lcdInit();
	uart_open(USART1, 115200);
//	btnInit();

	for(int i=0; ;) {
		for (int j=0; j<26; j++) uart_putc('A'+(j), USART1);
		uart_putc('\n', USART1);
		uart_putc('\r', USART1);
		i++;
		lcdScroll(i&0x3F);
		ledOn(LED_GREEN);
		Delay(LITTLE_DELAY);

		i++;
		lcdScroll(i&0x3F);
		ledOff(LED_GREEN);
		Delay(LITTLE_DELAY);
	}
}

//int main(void)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//
//	GPIO_InitTypeDef gpioInitStruct;
//	gpioInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	gpioInitStruct.GPIO_Pin = GPIO_Pin_1;
//	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//
//	GPIO_Init(GPIOA, &gpioInitStruct);
//	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
//
//
//	for(;;) {
//
//		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
//		GPIO_SetBits(GPIOA, GPIO_Pin_1);
//	}
//}



/*
#include "lcd.h"
#include "led.h"

void Delay(uint32_t count){
	while(count--);
}

#define LITTLE_DELAY	3000000

int counter = 0;

int main(void)
{
	ledInit();
	lcdInit();
	btnInit();

	for(int i=0; ;) {
		i++;
//		lcdScroll(i&0x3F);
		ledOn(LED_BLUE);
		ledOff(LED_GREEN);
		Delay(LITTLE_DELAY);

		i++;
//		lcdScroll(i&0x3F);
		ledOn(LED_RED);
		ledOff(LED_BLUE);
		Delay(LITTLE_DELAY);

		i++;
//		lcdScroll(i&0x3F);
		ledOn(LED_ORANGE);
		ledOff(LED_RED);
		Delay(LITTLE_DELAY);

		i++;
//		lcdScroll(i&0x3F);
		ledOn(LED_GREEN);
		ledOff(LED_ORANGE);
		Delay(LITTLE_DELAY);
	}
}
 */
