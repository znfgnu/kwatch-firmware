/*
 * dummy.h
 *
 *  Created on: 14 kwi 2017
 *      Author: konrad
 */

#ifndef APPS_DUMMY_H_
#define APPS_DUMMY_H_

#include "app_mgr.h"

#define APP__DUMMY_ID	((uint8_t)'?')
extern App app__dummy;
void app__dummy_init();

#endif /* APPS_DUMMY_H_ */
