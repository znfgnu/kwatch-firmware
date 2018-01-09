/*
 * app__watchface.h
 *
 *  Created on: 17 lis 2016
 *      Author: konrad
 */

#ifndef APPS_WATCHFACE_H_
#define APPS_WATCHFACE_H_

#include "app.h"

#define APP__WATCHFACE_ID	((uint8_t)'t')
extern App_t app__watchface;
void app__watchface_init();

//#define APP__WATCHFACE_DEBUG

#endif /* APPS_WATCHFACE_H_ */
