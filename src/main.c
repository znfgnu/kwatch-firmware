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
	lcd_init();

	for(int i=0; ;) {
		lcd_set_contrast(((i>>1)&0x1F)<<3&0xFF);

		i++;
		led_on(LED_GREEN);
		lcd_update();
		Delay(LITTLE_DELAY);

		i++;
		led_off(LED_GREEN);
		lcd_update();
		Delay(LITTLE_DELAY);
	}
}
