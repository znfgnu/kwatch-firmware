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
#include "dma.h"
#include "mainloop.h"
#include "timers.h"
#include "btn.h"
#include "app__watchface.h"
#include "app__serial.h"
#include "config.h"

int main(void)
{
	led_init();
	led_on(LED_VIBR);
	uart_init();
	lcd_init();
//	dma_init();
	btn_init();
	timers_init();

	// initialize your apps here:
	app__watchface_init();
	app__serial_init();

	run();
	// shouldn't reach here.
}
