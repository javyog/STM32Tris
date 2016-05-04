/*
 * game.c
 *
 *  Created on: Apr 24, 2016
 *      Author: Javier Oliver
 */
	/* Includes */
	#include "game.h"


	/*##### Variables #####*/
	/* Number of lines killed. If top ten score, we will save it*/
	uint32_t numLines;

	/* Counter to check if we are idle and we should go to sleep
	 * It will be refreshed inside the game engine if we press a button*/
	uint8_t sleepCountDown = COUNT_DOWN;

	/* This variable will hold the current screen status to show in the led matrix*/
	static TScreenMatrix gameMatrix = {{0}};



	/*##### Variables ENDS #####*/

	/* constants */
	TScreenMatrix gameIdle = {
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

	TScreenMatrix gameOver = {
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

	/* This function will rotate the current block */
	void GAME_rotateBlock(){

	}

	/* Function to move a block left -- eg. (*gameMatrix)[1][0] = 7;*/
	void GAME_moveLeft(){

	}

	/* Function to move a block right */
	void GAME_moveRight(){

	}

	/* Function to move a block to the bottom */
	void GAME_moveToBottom(){

	}

	/* Function to move the block 1 row down*/
	void GAME_moveDown(){

	}

	/* This function will check if a complete line has been filled.
	 * If a row is completed, it will return the line else -1*/
	int GAME_fullRow(TScreenMatrix currentMatrix){
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
	void GAME_copyScreen(TScreenMatrix screenToCopy){
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

	uint8_t GAME_buttonsPressed(void){
		uint8_t move = 0;

		/*This variables will be used to see if we have a long press so we move/rotate every X*/
		static uint32_t timeNow = 0;
		static uint32_t timePrev_LEFT = 0;
		static uint32_t timePrev_RIGHT = 0;
		static uint32_t timePrev_UP = 0;
		static uint32_t timePrev_DOWN = 0;

		static uint8_t firstLeft  = 1;
		static uint8_t firstRight = 1;
		static uint8_t firstUp	  = 1;
		static uint8_t firstDown  = 1;

		timeNow = HAL_GetTick();

		/* Move right, it will have first press and long presses */
		if (HAL_GPIO_ReadPin(BUTTON_RIGHT_GPIO_Port, BUTTON_RIGHT_Pin) == GPIO_PIN_SET){
			timePrev_RIGHT = timeNow;
			if(firstRight == 0)firstRight = 1;
		}else{
			if(firstRight == 1){
				firstRight = 0;
				move |= (RIGHT & (~(HAL_GPIO_ReadPin(BUTTON_RIGHT_GPIO_Port, BUTTON_RIGHT_Pin))));
			}else{
				if((timeNow - timePrev_RIGHT) > LONG_PRESS_MS){
					move |= (RIGHT & (~(HAL_GPIO_ReadPin(BUTTON_RIGHT_GPIO_Port, BUTTON_RIGHT_Pin))));
					timePrev_RIGHT = timeNow;
				}
			}
		}

		/* Move left, it will have first press and long presses */
		if (HAL_GPIO_ReadPin(BUTTON_LEFT_GPIO_Port, BUTTON_LEFT_Pin) == GPIO_PIN_SET){
			timePrev_LEFT = timeNow;
			if(firstLeft == 0)firstLeft = 1;
		}else{
			if(firstLeft == 1){
				firstLeft = 0;
				move |= (LEFT  & (~(HAL_GPIO_ReadPin(BUTTON_LEFT_GPIO_Port, BUTTON_LEFT_Pin)  << 1)));
			}else{
				if((timeNow - timePrev_LEFT) > LONG_PRESS_MS){
					move |= (LEFT & (~(HAL_GPIO_ReadPin(BUTTON_LEFT_GPIO_Port, BUTTON_LEFT_Pin)  << 1)));
					timePrev_LEFT = timeNow;
				}
			}
		}

		if (HAL_GPIO_ReadPin(BUTTON_UP_GPIO_Port, BUTTON_UP_Pin) == GPIO_PIN_SET){
			timePrev_UP = timeNow;
			if(firstUp == 0)firstUp = 1;
		}else{
			if(firstUp == 1){
				firstUp = 0;
				move |= (UP    & (~(HAL_GPIO_ReadPin(BUTTON_UP_GPIO_Port, BUTTON_UP_Pin)      << 3)));
			}else{
				if((timeNow - timePrev_UP) > LONG_PRESS_MS){
					move |= (UP & (~(HAL_GPIO_ReadPin(BUTTON_UP_GPIO_Port, BUTTON_UP_Pin)      << 3)));
					timePrev_UP = timeNow;
				}
			}
		}

		if (HAL_GPIO_ReadPin(BUTTON_DOWN_GPIO_Port, BUTTON_DOWN_Pin) == GPIO_PIN_SET){
			timePrev_DOWN = timeNow;
			if(firstDown == 0)firstDown = 1;
		}else{
			if(firstDown == 1){
				firstDown = 0;
				move |= (DOWN  & (~(HAL_GPIO_ReadPin(BUTTON_DOWN_GPIO_Port, BUTTON_DOWN_Pin)  << 2)));
			}else{
				if((timeNow - timePrev_DOWN) > LONG_PRESS_MS){
					move |= (DOWN  & (~(HAL_GPIO_ReadPin(BUTTON_DOWN_GPIO_Port, BUTTON_DOWN_Pin)  << 2)));
					timePrev_DOWN = timeNow;
				}
			}
		}

		/* The buttons have pull-ups, inverting the logic */
		/*
		buttons |= (UP    & (~(HAL_GPIO_ReadPin(BUTTON_UP_GPIO_Port, BUTTON_UP_Pin)      << 3)));
		buttons |= (DOWN  & (~(HAL_GPIO_ReadPin(BUTTON_DOWN_GPIO_Port, BUTTON_DOWN_Pin)  << 2)));
		buttons |= (LEFT  & (~(HAL_GPIO_ReadPin(BUTTON_LEFT_GPIO_Port, BUTTON_LEFT_Pin)  << 1)));
		buttons |= (RIGHT & (~(HAL_GPIO_ReadPin(BUTTON_RIGHT_GPIO_Port, BUTTON_RIGHT_Pin)))); */


		/* if every button is pressed or repeating buttons = 0x15   0x8 | 0x4 | 0x2 | 0x1 */

		return move;
	}

	/* This is the main game task where we will move, rotate, call sounds and control the whole game*/
	void GAME_EngineTask_20ms(void){
		uint8_t buttons;
		static uint32_t timeNow = 0;
		static uint32_t timePrev = 0;

		/* After 1000 ms time to move the block down */
		timeNow = HAL_GetTick();

		if (timeNow - timePrev > 1000){
			GAME_moveDown();
			timeNow = timePrev;
		}

		/*## BUTTON CONTROL SECTION ##*/
		buttons = GAME_buttonsPressed();

		/* If left and right pressed at the same time, don't move (Lighting led pin)*/
		switch (buttons){
			case LEFT:
				GAME_moveLeft();
				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			break;
			case RIGHT:
				GAME_moveRight();
				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			break;
			case UP:
				GAME_rotateBlock();
				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			break;
			case DOWN:
				GAME_moveToBottom();
				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			break;
			default:
				//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			break;
		}



		/*## BUTTON CONTROL SECTION ENDS ##*/
		MATRIX_matrixVariableUpdate(gameMatrix);
	}






