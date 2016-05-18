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
#include "ui.h"
#include "app_mgr.h"
#include "app_events.h"
#include "app__serial.h"
#include "dma.h"

void Delay(uint32_t count){
	while(count--);
}

#define LITTLE_DELAY	3000000

int counter = 0;

int main(void)
{
	ui_init();
	led_init();
	uart_open(USART1, 115200);
	dma_init();
	lcd_init();

	app__serial_init();
	app_wakeup(&app__serial);

	for(int i=0; ;) {
		uint8_t c = getDMAchar();//uart_getc(USART1);
		(app__serial.handler)(APP_EVENT_BT_BYTE, (void*)c);

		i++;
		if (i&1) led_on(LED_GREEN);
		else led_off(LED_GREEN);
	}
}
