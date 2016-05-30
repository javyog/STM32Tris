/*
 * game.h
 *
 *  Created on: Apr 24, 2016
 *      Author: Javier Oliver
 */

	#ifndef INC_GAME_H_
	#define INC_GAME_H_

	/* includes */
	#include "stdint.h"
    #include "stdlib.h"
	#include "stm32f1xx_hal.h"
	#include "ledMatrix_16x8.h"

    /* Matrix rows and columns*/
	#define COLUMN		8
	#define ROW 		16
    /* Count down define before going to sleep*/
	#define COUNT_DOWN 	5
	/* Time to move the current block one position down in ms */
	#define TIME_ONE_DOWN 1000
	/* This is the time to see a long press and repeat the buttons pressed*/
	#define LONG_PRESS_MS 700

	/* after long press is detected, this will be the time to repeat the button action*/
	#define REPEAT_PRESS_MS 200

	/* Long press and repeat press for down actions */
	#define LONG_DOWN_MS 300
	#define REPEAT_DOWN_MS 75


	/*Buttons -> nibble 1, 1, 1, 1*/
	#define RIGHT		0x1
	#define LEFT		0x2
	#define DOWN		0x4
	#define UP			0x8


	/* Functions */
	/* Game configuration */
	void GAME_Config(void);

	/* This is the main game task where we will move, rotate, call sounds and control the whole game*/
	void GAME_EngineTask_20ms(void);

	/* nextMove will decide what next move is going to be done by checking the input buttons */
	uint8_t GAME_nextMove(void);

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

	/* This function will create a block if there is none */
	void GAME_CreateBlock();

	/* Show lines killed after GAME OVER */
	void GAME_showResults();

	/* This function will check for a complete rows after a block is placed in its place */
	void GAME_checkFullRows();

	/* this function will remove the row when completed.*/
	void GAME_removeRow(int rowFull);

	/* Dumps the screenToCopy variable into the screen variable */
	void GAME_copyScreen(TScreenMatrix screenToCopy);

	/* Save the score to the flash for having a ranking.
	 * We could show it after the game over screen
	 * */
	void GAME_saveScore(uint32_t lines);


	#endif /* INC_GAME_H_ */

