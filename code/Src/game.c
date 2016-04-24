/*
 * game.c
 *
 *  Created on: Apr 24, 2016
 *      Author: javy
 */
	/* Includes */
	#include "stm32f1xx_hal.h"
	#include "game.h"

	/* Variables */
	const screenMatrix gameOver = {
									{0,0,0,0,0,0,0,0},
								    {0,0,0,0,0,0,0,0},
								    {0,0,0,0,0,0,0,0},
								    {0,0,0,0,0,0,0,0},
								    {0,0,0,0,0,0,0,0},
								    {0,0,0,0,0,0,0,0},
								    {0,0,0,0,0,0,0,0},
								    {0,0,0,0,0,0,0,0},
								    {0,0,0,0,0,0,0,0},
								    {0,0,0,0,0,0,1,0},
								    {0,0,0,0,1,1,0,0},
								    {0,1,0,0,1,0,1,0},
								    {0,1,0,0,1,0,1,0},
								    {0,1,0,0,0,0,1,0},
								    {0,0,1,1,1,1,0,0},
								    {0,0,0,0,0,0,0,0}
								   };
	screenMatrix gameMatrix = {{0}};


	 /* With every button interrupt we have to refresh the counter*/
	void GAME_goToSleepTask_1000ms(void);

	/* Function to move a block left -- eg. (*gameMatrix)[1][0] = 7;*/
	void GAME_moveLeft(screenMatrix *gameMatrix){
			}

	/* Function to move a block right */
	void GAME_moveRight(screenMatrix *gameMatrix){

	}

	/* Function to move a block to the bottom */
	void GAME_moveBottom(screenMatrix *gameMatrix){

	}

	/* Show lines killed after GAME OVER */
	void GAME_showResults(screenMatrix *gameMatrix){

	}

	/* Show GAME OVER screen */
	void GAME_showGameOver(screenMatrix *gameMatrix){
		uint8_t i;
		uint8_t j;
		for(i = 0; i < ROW; i++){
			for (j = 0; j < COLUMN; j++) (*gameMatrix)[ROW][COLUMN] = gameOver[ROW][COLUMN];
		}

	}

	/* Save the score to the flash for having a ranking*/
	void GAME_saveScore(uint32_t lines){

	}

	/* Game configuration */
	void GAME_Config(void){
		SystemClock_Config();
	}

	/* Move down block task*/
	void GAME_BlockDownTask_1000ms(void){
		HAL_GPIO_TogglePin(STATUS_LED_GPIO_Port, STATUS_LED_Pin);
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

	  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	  /* SysTick_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
	}



