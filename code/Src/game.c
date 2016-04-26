/*
 * game.c
 *
 *  Created on: Apr 24, 2016
 *      Author: Javier Oliver
 */
	/* Includes */
	#include "stm32f1xx_hal.h"
	#include "game.h"
	#include "ledMatrix_16x8.h"

	/* Variables */

	/*variables*/
	/* number of lines killed. If top ten score, we will save it*/
	uint32_t numLines;

	/* counter to check if we are idle and we should go to sleep */
	uint8_t sleepCountDown;

	/* This variable will hold the current screen status to show */
	screenMatrix gameMatrix = {{0}};

	/* constants */

	const screenMatrix gameOver = {
									{0,0,1,1,1,1,0,0},
								    {0,1,1,0,0,1,1,0},
								    {1,1,0,0,0,0,1,1},
								    {1,0,0,0,0,0,0,1},
								    {1,0,0,0,0,0,0,1},
								    {1,1,0,0,0,0,1,1},
								    {0,1,1,0,0,1,1,0},
								    {0,0,1,1,1,1,0,0},
									{0,0,1,1,1,1,0,0},
								    {0,1,1,0,0,1,1,0},
								    {1,1,0,0,0,0,1,1},
								    {1,0,0,0,0,0,0,1},
								    {1,0,0,0,0,0,0,1},
								    {1,1,0,0,0,0,1,1},
								    {0,1,1,0,0,1,1,0},
								    {0,0,1,1,1,1,0,0}
								   };



	 /* With every button interrupt we have to refresh the counter*/
	void GAME_goToSleepTask_1000ms(void){

	}

	/* Function to move a block left -- eg. (*gameMatrix)[1][0] = 7;*/
	void GAME_moveLeft(){

	}

	/* Function to move a block right */
	void GAME_moveRight(){

	}

	/* Function to move a block to the bottom */
	void GAME_moveBottom(){

	}

	/* Show lines killed after GAME OVER */
	void GAME_showResults(){

	}

	/* Show GAME OVER screen */
	void GAME_showGameOver(){
		uint8_t i;
		uint8_t j;

		/* Copy the gameOver screen to the current matrix */
		for(i = 0; i < ROW; i++){
			for (j = 0; j < COLUMN; j++)gameMatrix[i][j] = gameOver[i][j];
		}

	}

	/* Save the score to the flash for having a ranking*/
	void GAME_saveScore(uint32_t lines){

	}

	/* Game configuration */
	void GAME_Config(void){

	}

	/* Refreshes the screen */
	void GAME_refreshScreenTask_20ms(void){
		GAME_showGameOver();
		MATRIX_refreshMatrix(gameMatrix);
	}

	/* Move down block task*/
	void GAME_BlockDownTask_1000ms(void){
		HAL_GPIO_TogglePin(STATUS_LED_GPIO_Port, STATUS_LED_Pin);

	}







