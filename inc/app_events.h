/*
 * app_events.h
 *
 *  Created on: 10 maj 2016
 *      Author: konrad
 */

#ifndef APP_EVENTS_H_
#define APP_EVENTS_H_

#define APP_EVENT_BT_BYTE			0x01		// received one byte via bluetooth
#define APP_EVENT_SECOND_ELAPSED	0x02		// one second elapsed

#define APP_EVENT_DRAW				0x10

#define APP_EVENT_BTN_UP_PRESSED	0x20
#define APP_EVENT_BTN_UP_RELEASED	0x21
#define APP_EVENT_BTN_UP_HOLD		0x22

#define APP_EVENT_BTN_DN_PRESSED	0x30
#define APP_EVENT_BTN_DN_RELEASED	0x31
#define APP_EVENT_BTN_DN_HOLD		0x32

#define APP_EVENT_BTN_OK_PRESSED	0x40
#define APP_EVENT_BTN_OK_RELEASED	0x41
#define APP_EVENT_BTN_OK_HOLD		0x42

#define APP_EVENT_BTN_BK_PRESSED	0x50
#define APP_EVENT_BTN_BK_RELEASED	0x51
#define APP_EVENT_BTN_BK_HOLD		0x52


#endif /* APP_EVENTS_H_ */
