/*
 * osd.c
 *
 *  Created on: Apr 24, 2016
 *      Author: Javier Oliver
 */

	/* prototypes */
	#include "osd.h"
	#include "stm32f1xx_hal.h"
	#include "game.h"
	#include "ledMatrix_16x8.h"



/* ################## Defines ######################### */
	#define value1000ms	((1000u / OSD_SYSTEM_TICK_ms)-1u)
	#define value500ms	((500u  / OSD_SYSTEM_TICK_ms)-1u)
	#define value200ms	((200u  / OSD_SYSTEM_TICK_ms)-1u)
	#define value100ms	((100u  / OSD_SYSTEM_TICK_ms)-1u)
	#define value40ms	((40u   / OSD_SYSTEM_TICK_ms)-1u)
	#define value20ms	((20u   / OSD_SYSTEM_TICK_ms)-1u)
	#define value2ms	((2u    / OSD_SYSTEM_TICK_ms)-1u)

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
			if (OSD_counters.U8_until_200ms < (uint8_t)value200ms) {
				OSD_counters.U8_until_200ms++;
			}
			else {
				OSD_counters.U8_until_200ms = 0u;
				/* 200ms tasks */
			}
			/* ************** */
			if (OSD_counters.U8_until_100ms < (uint8_t)value100ms) {
				OSD_counters.U8_until_100ms++;
			}
			else {
				OSD_counters.U8_until_100ms = 0u;
				/* 100ms tasks */
			}

			/* ************** */
			if (OSD_counters.U8_until_40ms < (uint8_t)value40ms) {
				OSD_counters.U8_until_40ms++;
			}
			else {
				OSD_counters.U8_until_40ms = 0u;
				/* 40ms tasks */
			}
			/* ************** */
			if (OSD_counters.U8_until_20ms < (uint8_t)value20ms) {
				OSD_counters.U8_until_20ms++;
			}
			else {
				OSD_counters.U8_until_20ms = 0u;
				/* 20ms tasks */
				GAME_refreshScreenTask_20ms();
			}
			/* ************** */
			if (OSD_counters.U8_until_2ms < (uint8_t)value2ms) {
				OSD_counters.U8_until_2ms++;
			}
			else {
				OSD_counters.U8_until_2ms = 0u;
				/* 2ms tasks */
				MATRIX_refreshColumn_task2ms();

			}


		}

		/* System Clock Configuration */
		void SystemClock_Config(void)
		{
		  RCC_OscInitTypeDef RCC_OscInitStruct;
		  RCC_ClkInitTypeDef RCC_ClkInitStruct;

		  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
		  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
		  RCC_OscInitStruct.HSICalibrationValue = 16;
		  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
		  HAL_RCC_OscConfig(&RCC_OscInitStruct);

		  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
									  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
		  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
		  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
		  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
		  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

		  //HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
		  /* Configuring Sys tick to 5ms */
		  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/(1000 / OSD_SYSTEM_TICK_ms));

		  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

		  /* SysTick_IRQn interrupt configuration */
		  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
		}
	#endif
