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
#include "lcd.h"
#include "led.h"
#include "uart.h"
#include "ui.h"
#include "dma.h"
#include "mainloop.h"
#include "app__watchface.h"

void Delay(uint32_t count){
	while(count--);
}

#define LITTLE_DELAY	3000000

int counter = 0;

int main(void)
{
	ui_init();
	led_init();
	led_on(LED_VIBR);
	uart_open(USART1, 115200);
	lcd_init();
	dma_init();

	app__watchface_init();
	app_wakeup(&app__watchface);

	run();

}
