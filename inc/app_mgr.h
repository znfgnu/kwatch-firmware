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
#define APP_ARGS_PROTO	uint32_t, void*
#define APP_ARGS		uint32_t id, void* data

#define APPMGR_MAX_APPS	20

// Application structure. Stores data needed to communicate with firmware
typedef struct App{
	uint32_t id;										// unique application ID
//	uint8_t framebuffer[UI_APP_HEIGHT][UI_APP_WIDTH];	// private framebuffer
	void (*handler)(APP_ARGS_PROTO);					// handler for events
	uint8_t needs_redraw;

	uint32_t events_when_background;
	uint32_t events_when_foreground;
} App;

extern App* foreground;
//extern App* installed_apps[];
#define ISFOREGROUND(x)	(foreground==x)

void app_init(App*, uint32_t, void(*)(APP_ARGS), uint32_t, uint32_t);
void app_sleep(App*);	// to background
void app_wakeup(App*);	// to foreground
//void app_updatescreen(App*);

void app_notify_event(APP_ARGS_PROTO);

#endif /* APP_MGR_H_ */
