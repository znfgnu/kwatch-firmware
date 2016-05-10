/*
 * app__serial.h
 *
 *  Created on: 10 maj 2016
 *      Author: konrad
 */

#ifndef APP__SERIAL_H_
#define APP__SERIAL_H_

#include "app_mgr.h"

#define APP__SERIAL_ID	0x77

extern App app__serial;
void serialhandler(APP_ARGS_PROTO);

void app__serial_init();

#endif /* APP__SERIAL_H_ */
