/*
 * app_mgr.h
 *
 *  Created on: 9 maj 2016
 *      Author: konrad
 */

#ifndef APP_H_
#define APP_H_

#include <stdint.h>

#define APP_MAX_APPS	20

typedef void (*app_handler_t)(uint32_t, void*);

// Application structure. Stores data needed to communicate with firmware
typedef struct {
	uint32_t id;				// unique application ID
	int needs_redraw;
	app_handler_t handler;	// handler for events

	uint32_t events_when_background;
	uint32_t events_when_foreground;
} App_t;

extern App_t* foreground;

void app_init(App_t*, uint32_t, app_handler_t, uint32_t, uint32_t);
void app_spawn(App_t*);
void app_quit();
App_t* app_get_active_app();
void app_notify_event(uint32_t, void*);

#endif /* APP_H_ */
