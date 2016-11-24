/*
 * app_mgr.h
 *
 *  Created on: 9 maj 2016
 *      Author: konrad
 */

#ifndef APP_MGR_H_
#define APP_MGR_H_

#include <stdint.h>

// Handler arguments
#define APP_ARGS_PROTO	uint32_t, void*
#define APP_ARGS		uint32_t id, void* data

#define APPMGR_MAX_APPS	20

// Application structure. Stores data needed to communicate with firmware
typedef struct App{
	uint8_t id;										// unique application ID
	void (*handler)(APP_ARGS_PROTO);					// handler for events
	uint8_t needs_redraw;

	uint32_t events_when_background;
	uint32_t events_when_foreground;
} App;

extern App* foreground;

#define ISFOREGROUND(x)	(foreground==x)

void app_init(App*, uint8_t, void(*)(APP_ARGS), uint32_t, uint32_t);
void app_spawn(App*);
void app_quit();
App* app_get_active_app();

void app_notify_event(APP_ARGS_PROTO);

#endif /* APP_MGR_H_ */
