/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "apps/mainmenu.h"
#include "apps/serial.h"
#include "apps/watchface.h"
#include "apps/dummy.h"
#include "apps/tetris.h"
#include "apps/animation.h"
#include "stm32f10x.h"
#include "lcd.h"
#include "uart.h"
#include "mainloop.h"
#include "timers.h"
#include "btn.h"
#include "config.h"

int main(void) {
	uart_init();
	lcd_init();
	btn_init();
	timers_init();

	// initialize your apps here:
	app__watchface_init();
	app__serial_init();
	app__mainmenu_init();
	app__dummy_init();
	app__tetris_init();
	app__animation_init();

	mainloop_run();
	// shouldn't reach here.
}
