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
	static screenMatrix gameMatrix = {{0}};

	/* constants */
	screenMatrix gameIdle = {
							/*     (0,0) X ——►
							 *      Y
							 *      |
							 *      ▼
							 *      ..
							 *      ..
							 *      ..
							 *    				(15,7)
							 * */
									{0,0,0,0,0,0,0,0},
									{1,1,1,0,1,1,0,0},
									{0,1,0,0,1,0,1,0},
									{0,1,0,0,1,0,1,0},
									{0,1,0,0,1,0,1,0},
									{1,1,1,0,1,1,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{1,0,0,0,1,1,1,0},
									{1,0,0,0,1,0,0,0},
									{1,0,0,0,1,1,1,0},
									{1,0,0,0,1,0,0,0},
									{1,1,1,0,1,1,1,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0}
								   };

	screenMatrix gameOver = {
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0}
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

	/* This function will check if a complete line has been filled.
	 * If a row is completed, it will return the line else -1*/
	int GAME_fullRow(screenMatrix currentMatrix){
		int row = -1;

		return row;
	}

	/* this function will remove the row when completed.*/
	void GAME_removeRow(int row){

	}

	/* Show lines killed after GAME OVER */
	void GAME_showResults(){

	}

	/* Dumps the screenToCopy variable into the screen variable */
	void GAME_copyScreen(screenMatrix screenToCopy){
		uint8_t i;
		uint8_t j;

		/* Copy the gameOver screen to the current matrix */
		for(i = 0; i < ROW; i++){
			for (j = 0; j < COLUMN; j++)gameMatrix[i][j] = screenToCopy[i][j];
		}

	}

	/* Save the score to the flash for having a ranking*/
	void GAME_saveScore(uint32_t lines){

	}

	/* Game configuration */
	void GAME_Config(void){
		GAME_copyScreen(gameIdle);
	}

	/* Refreshes the screen */
	void GAME_refreshScreenTask_5ms(void){
		MATRIX_refreshMatrix(gameMatrix);
	}

	/* Move down block task*/
	void GAME_BlockDownTask_1000ms(void){
		//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);

	}







