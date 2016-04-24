/*
 * osd.c
 *
 *  Created on: Apr 24, 2016
 *      Author: Javier Oliver
 */

	/* prototypes */
	#include "osd_api.h"
	#include "game.h"



/* ################## Defines ######################### */
	#define value1000ms	((1000u / OSD_SYSTEM_TICK_ms)-1u)
	#define value500ms	((500u / OSD_SYSTEM_TICK_ms)-1u)
	#define value200ms	((200u / OSD_SYSTEM_TICK_ms)-1u)
	#define value100ms	((100u / OSD_SYSTEM_TICK_ms)-1u)
	#define value40ms	((40u / OSD_SYSTEM_TICK_ms)-1u)

/* ################## Global variables ################## */
	#ifdef USE_BASIC_OSD
		T_OSD_counters OSD_counters;
	#endif

	#ifdef USE_BASIC_OSD
		void OSD_Scheduler(void) {

			/* ************** */

			if (OSD_counters.U16_until_1000ms < (uint16_t)value1000ms) {
				OSD_counters.U16_until_1000ms++;
			}
			else {
				OSD_counters.U16_until_1000ms = 0u;
				/* 1s tasks */
				/* Move block down task*/
				GAME_BlockDownTask_1000ms();


			}
			if (OSD_counters.U16_until_500ms < (uint16_t)value500ms) {
				OSD_counters.U16_until_500ms++;
			}
			else {
				OSD_counters.U16_until_500ms = 0u;
				/* 500ms tasks */


			}

			/* ************** */
			if (OSD_counters.U8_until_200ms < value200ms) {
				OSD_counters.U8_until_200ms++;
			}
			else {
				OSD_counters.U8_until_200ms = 0u;
				/* 200ms tasks */
			}
			/* ************** */
			if (OSD_counters.U8_until_100ms < value100ms) {
				OSD_counters.U8_until_100ms++;
			}
			else {
				OSD_counters.U8_until_100ms = 0u;
				/* 100ms tasks */
			}

			/* ************** */
			if (OSD_counters.U8_until_40ms < value40ms) {
				OSD_counters.U8_until_40ms++;
			}
			else {
				OSD_counters.U8_until_40ms = 0u;
				/* 40ms tasks */
			}
		}
	#endif
