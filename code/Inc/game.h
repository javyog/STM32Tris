/*
 * game.h
 *
 *  Created on: Apr 24, 2016
 *      Author: Javier Oliver
 */

	#ifndef INC_GAME_H_
	#define INC_GAME_H_

	#include "stm32f1xx_hal.h"
	#include "ledMatrix_16x8.h"

	#define COLUMN		8
	#define ROW 		16
	#define COUNT_DOWN 	5

	/*Buttons -> nibble 1, 1, 1, 1*/
	#define RIGHT		0x1
	#define LEFT		0x2
	#define DOWN		0x4
	#define UP			0x8

	/* includes */
	#include <stdint.h>

	/* Functions */
	/* Game configuration */
	void GAME_Config(void);

	/* This is the main game task where we will move, rotate, call sounds and control the whole game*/
	void GAME_EngineTask_20ms(void);

	uint8_t GAME_buttonsPressed(void);

	/* Every second we will decrement the sleeCountDown. If we reach 0 we will go to sleep to save battery
	 * With every button interrupt we have to refresh the counter*/
	void GAME_goToSleepTask_1000ms(void);

	/* This function will rotate the current block */
	void GAME_rotateBlock();

	/* Function to move a block left */
	void GAME_moveLeft();

	/* Function to move a block right */
	void GAME_moveRight();

	/* Function to move a block to the bottom */
	void GAME_moveToBottom();

	/* Function to move the block 1 row down*/
	void GAME_moveDown();

	/* Show lines killed after GAME OVER */
	void GAME_showResults();

	/* This function will check if a complete line has been filled.
	 * If a row is completed, it will return the line else -1*/
	int GAME_fullRow(TScreenMatrix currentMatrix);

	/* this function will remove the row when completed.*/
	void GAME_removeRow(int row);

	/* Dumps the screenToCopy variable into the screen variable */
	void GAME_copyScreen(TScreenMatrix screenToCopy);

	/* Save the score to the flash for having a ranking.
	 * We could show it after the game over screen
	 * */
	void GAME_saveScore(uint32_t lines);

	#endif /* INC_GAME_H_ */

