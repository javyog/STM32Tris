/*
 * game.h
 *
 *  Created on: Apr 24, 2016
 *      Author: Javier Oliver
 */

	#ifndef INC_GAME_H_
	#define INC_GAME_H_

	#define COLUMN	8
	#define ROW 	16

	/* includes */
	#include <stdint.h>

	/* typedefs */
	typedef uint8_t screenMatrix[16][8];


	/* Functions */
	/* Game configuration */
	void GAME_Config(void);

	/* Task to move down the current block*/
	void GAME_BlockDownTask_1000ms(void);

	/* Every second we will decrement the sleeCountDown. If we reach 0 we will go to sleep to save battery
	 * With every button interrupt we have to refresh the counter*/
	void GAME_goToSleepTask_1000ms(void);

	/* Function to move a block left */
	void GAME_moveLeft();

	/* Function to move a block right */
	void GAME_moveRight();

	/* Function to move a block to the bottom */
	void GAME_moveBottom();

	/* Show lines killed after GAME OVER */
	void GAME_showResults();

	/* Show GAME OVER screen */
	void GAME_showGameOver();

	/* Refreshes the screen */
	void GAME_refreshScreenTask_20ms(void);

	/* Save the score to the flash for having a ranking*/
	void GAME_saveScore(uint32_t lines);

	#endif /* INC_GAME_H_ */

