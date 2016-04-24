/*
 * osd_api.h
 *
 *  Created on: Apr 24, 2016
 *      Author: Javier Oliver
 */    
    #ifndef __OSD_API_H
    #define __OSD_API_H

    
    #include <stdint.h> 

 /* Public Defines ------------------------------------------------------------*/
 
     #define USE_BASIC_OSD
     #define OSD_SYSTEM_TICK_ms (1u) /* SysTick = 1ms */     
     
     #ifdef USE_BASIC_OSD
        #ifndef OSD_COUNTERS
            #define OSD_COUNTERS
            typedef struct {
                uint16_t U16_until_1000ms;
                uint16_t U16_until_500ms;
                uint8_t  U8_until_200ms;
                uint8_t  U8_until_100ms;
                uint8_t  U8_until_40ms;
                uint8_t  U8_until_20ms;
            }T_OSD_counters;
        #endif
    #endif
    
 /* Public functions ----------------------------------------------------------*/

    /* OS Scheduler function */
    void OSD_Scheduler(void);
    
    #endif