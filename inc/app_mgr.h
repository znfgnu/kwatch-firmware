/*
 * app_mgr.h
 *
 *  Created on: 9 maj 2016
 *      Author: konrad
 */

#ifndef APP_MGR_H_
#define APP_MGR_H_

#include "ui.h"

// Handler arguments
#define APP_ARGS_PROTO	uint8_t, void*
#define APP_ARGS		uint8_t id, void* data

// Application structure. Stores data needed to communicate with firmware
typedef struct App{
	uint32_t id;										// unique application ID
	uint8_t framebuffer[UI_APP_HEIGHT][UI_APP_WIDTH];	// private framebuffer
	void (*handler)(APP_ARGS_PROTO);					// handler for events
} App;

extern App* foreground;
#define ISFOREGROUND(x)	(foreground==x)

void app_init(App*, uint32_t, void(*)(APP_ARGS));
void app_sleep(App*);
void app_wakeup(App*);
void app_updatescreen(App*);

#endif /* APP_MGR_H_ */
