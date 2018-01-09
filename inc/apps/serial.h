/*
 * app__serial.h
 *
 *  Created on: 10 maj 2016
 *      Author: konrad
 */

#ifndef APPS_SERIAL_H_
#define APPS_SERIAL_H_

#include "app.h"

#define APP__SERIAL_ID	((uint8_t)'T')
extern App_t app__serial;
void app__serial_init();

#endif /* APPS_SERIAL_H_ */
