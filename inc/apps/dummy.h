/*
 * dummy.h
 *
 *  Created on: 14 kwi 2017
 *      Author: konrad
 */

#ifndef APPS_DUMMY_H_
#define APPS_DUMMY_H_

#include "app.h"

#define APP__DUMMY_ID	((uint8_t)'?')
extern App_t app__dummy;
void app__dummy_init();

#endif /* APPS_DUMMY_H_ */
