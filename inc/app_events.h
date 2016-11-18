/*
 * app_events.h
 *
 *  Created on: 10 maj 2016
 *      Author: konrad
 */

#ifndef APP_EVENTS_H_
#define APP_EVENTS_H_

#define APP_EVENT_BT_BYTE			0x00000001		// received one byte via bluetooth
#define APP_EVENT_SECOND_ELAPSED	0x00000002		// one second elapsed

#define APP_EVENT_DRAW				0x00000004
#define APP_EVENT_SPAWN				0x00000008		// unmaskable

#define APP_EVENT_BTN_PRESSED		0x00000010
#define APP_EVENT_BTN_HELD			0x00000020
#define APP_EVENT_BTN_RELEASED		0x00000040


#endif /* APP_EVENTS_H_ */
