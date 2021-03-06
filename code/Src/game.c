/*
 * game.c
 *
 *  Created on: Apr 24, 2016
 *      Author: Javier Oliver
 */

    /*
     * ToDO:  * When moving right or moving down, it would be interesting to do some spaceDown, spaceLeft,
     * 			spaceRight and only then move the block
     * 		  * Add sound
     * 		  * Change block creation method. Atm I create another blank screen array which has the block and I have to iterate
     * 		 	every time the user press a button. I add the block array to a pile array and then display.
     * 		 	I could have a type block with coordinate to speed up the thing
     * 		  * Add a true random generator. The sequence is always the same as it is now by using rand()
     * */

	/* Includes */
	#include <game.h>
	#include <mxconstants.h>
	#include <stm32f1xx_hal_gpio.h>
	#include <sys/_stdint.h>



	/*##### Variables #####*/
	/* Number of lines killed. If top ten score, we will save it*/
	uint32_t numLines;

	/* Counter to check if we are idle and we should go to sleep
	 * It will be refreshed inside the game engine if we press a button*/
	uint8_t sleepCountDown = COUNT_DOWN;


	/* After thinking how to represent the block,
	 * i thought to have a matrix with 4 dots in it and the OR function to display */
	TScreenMatrix blockMatrix = {{0}};
	/* This variable will the blocks that are not moving */
	TScreenMatrix pileMatrix = {{0}};
	/* This variable will hold the current screen status to show in the led matrix*/
	TScreenMatrix displayMatrix = {{0}};

	/* Current game state */
	currentStatus gameState = IDLE;
	/* The type of block being played*/
	typeBlock currentBlock = NONE;
	/* Current rotation state */
	uint8_t rotation = 0;

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
									{1,1,1,0,1,1,1,0},
									{0,1,0,0,1,0,0,0},
									{0,1,0,0,1,1,1,0},
									{0,1,0,0,1,0,0,0},
									{0,1,0,0,1,1,1,0},
									{0,0,0,0,0,0,0,0},
									{1,1,1,0,1,1,0,0},
									{0,1,0,0,1,0,1,0},
									{0,1,0,0,1,1,0,0},
									{0,1,0,0,1,0,1,0},
									{0,0,0,0,0,0,0,0},
									{1,1,1,0,0,1,1,0},
									{0,1,0,0,1,0,0,0},
									{0,1,0,0,0,1,0,0},
									{0,1,0,0,0,0,1,0},
									{1,1,1,0,1,1,0,0}
								   };

	TScreenMatrix gameBlank = {
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

	TScreenMatrix gameOver = {
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,1,0,1,1,0,1,0},
									{0,0,1,0,0,1,0,0},
									{0,1,0,1,1,0,1,0},
									{0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0},
									{0,0,1,1,1,1,0,0},
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
		uint8_t row;
		uint8_t column;
		uint8_t found = 0;

		/* o o
		 * o o
		 * */
		if (currentBlock == O) return;

		/*     .
		 * o o o o
		 * */
		if (currentBlock == I){
			for (row = (ROW - 1); ((row >= 0)&& (found == 0)); row--){
				for (column = 0; (column <= (COLUMN - 1) && (found == 0)); column++){
					/* This will be the most left down dot*/
					if (blockMatrix[row][column] == 1){
						found = 1;
						/* o o o o */
						if (rotation == 0){
							/* limits with the screen*/
							if ((row == 0)|| (row >= 14)){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row - 1][column + 2]) == 1) ||
									((pileMatrix[row + 1][column + 2]) == 1) ||
									((pileMatrix[row + 2][column + 2]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row - 1][column + 2] = 1;
									blockMatrix[row + 1][column + 2] = 1;
									blockMatrix[row + 2][column + 2] = 1;
									blockMatrix[row][column] = 0;
									blockMatrix[row][column + 1] = 0;
									blockMatrix[row][column + 3] = 0;
									rotation = 1;

								}
							}
						}
						else{
							 /* o
							  .	o
								o
								o
							 */

							/* limits with the screen*/
							if ((column == (COLUMN - 1))|| (column < 2)){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row - 2][column - 2]) == 1) ||
									((pileMatrix[row - 2][column - 1]) == 1) ||
									((pileMatrix[row - 2][column + 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row - 2][column - 2] = 1;
									blockMatrix[row - 2][column - 1] = 1;
									blockMatrix[row - 2][column + 1] = 1;
									blockMatrix[row][column] = 0;
									blockMatrix[row - 1][column] = 0;
									blockMatrix[row - 3][column] = 0;
									rotation = 1;
								}
							}

							rotation = 0;
						}
					}
				}
			}
		}


		if (currentBlock == S){
			for (row = (ROW - 1); ((row >= 0)&& (found == 0)); row--){
				for (column = 0; (column <= (COLUMN - 1) && (found == 0)); column++){
					/* This will be the most left down dot*/
					if (blockMatrix[row][column] == 1){
						found = 1;
						/*   .
						 *   o o
						 * o o
						 * */
						if (rotation == 0){
							/* limits with the screen*/
							if (row <= 1){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row][column + 2]) == 1) ||
									((pileMatrix[row - 2][column + 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row][column + 2] = 1;
									blockMatrix[row - 2][column + 1] = 1;
									blockMatrix[row][column] = 0;
									blockMatrix[row][column + 1] = 0;
									rotation = 1;

								}
							}
						}
						else{
							/*   o
							 * . o o
							 *     o
							 * */

							/* limits with the screen*/
							if (column <= 1){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row][column - 2]) == 1) ||
									((pileMatrix[row][column - 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row][column - 2] = 1;
									blockMatrix[row][column - 1] = 1;
									blockMatrix[row - 2][column - 1] = 0;
									blockMatrix[row][column] = 0;
									rotation = 1;

								}
							}

							rotation = 0;
						}
					}
				}

			}
		}

		if (currentBlock == Z){
			for (row = (ROW - 1); ((row >= 0)&& (found == 0)); row--){
				for (column = 0; (column <= (COLUMN - 1) && (found == 0)); column++){
					/* This will be the most left down dot*/
					if (blockMatrix[row][column] == 1){
						found = 1;
						/*   .
						 * o o
						 *   o o
						 * */
						if (rotation == 0){
							/* limits with the screen*/
							if (row <= 1){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row][column - 1]) == 1) ||
									((pileMatrix[row - 2][column]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row][column - 1] = 1;
									blockMatrix[row - 2][column] = 1;
									blockMatrix[row][column] = 0;
									blockMatrix[row][column + 1] = 0;
									rotation = 1;

								}
							}
						}
						else{
							/*     o
							 * . o o
							 *   o
							 * */

							/* limits with the screen*/
							if (column >= 6){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row][column + 1]) == 1) ||
									((pileMatrix[row][column + 2]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row][column + 1] = 1;
									blockMatrix[row][column + 2] = 1;
									blockMatrix[row][column] = 0;
									blockMatrix[row - 2][column + 1] = 0;
									rotation = 1;

								}
							}

							rotation = 0;
						}
					}
				}

			}
		}

		if (currentBlock == T){
			for (row = (ROW - 1); ((row >= 0)&& (found == 0)); row--){
				for (column = 0; (column <= (COLUMN - 1) && (found == 0)); column++){
					/* This will be the most left down dot*/
					if (blockMatrix[row][column] == 1){
						found = 1;
						/*   .
						 * o o o
						 *   o
						 * */
						if (rotation == 0){
							/* limits with the screen*/
							if (row <= 1){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row - 2][column]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row - 2][column] = 1;
									blockMatrix[row - 1][column - 1] = 0;
									rotation = 1;

								}
							}
						}
						else if(rotation == 1){
							/*   o
							 * . o o
							 *   o
							 * */

							/* limits with the screen*/
							if (column == 0){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row - 1][column - 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row - 1][column - 1] = 1;
									blockMatrix[row][column] = 0;
									rotation = 2;
								}
							}
						}
						else if(rotation == 2){
							/*   o
							 * o o o
							 *   .
							 * */

							/* limits with the screen*/
							if (row >= 15){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row + 1][column + 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row + 1][column + 1] = 1;
									blockMatrix[row][column + 2] = 0;
									rotation = 3;
								}
							}
						}
						else if(rotation == 3){
							/*   o
							 * o o .
							 *   o
							 * */

							/* limits with the screen*/
							if (column >= 7){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row - 1][column + 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row - 1][column + 1] = 1;
									blockMatrix[row - 2][column] = 0;
									rotation = 0;
								}
							}
						}
					}
				}

			}
		}


		if (currentBlock == L){
			for (row = (ROW - 1); ((row >= 0)&& (found == 0)); row--){
				for (column = 0; (column <= (COLUMN - 1) && (found == 0)); column++){
					/* This will be the most left down dot*/
					if (blockMatrix[row][column] == 1){
						found = 1;
						/*   .
						 * o o o
						 * o
						 * */
						if (rotation == 0){
							/* limits with the screen*/
							if (row <= 1){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row][column + 1]) == 1) ||
									((pileMatrix[row][column + 2]) == 1) ||
									((pileMatrix[row - 2][column + 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row][column + 1] = 1;
									blockMatrix[row][column + 2] = 1;
									blockMatrix[row - 2][column + 1] = 1;

									blockMatrix[row][column] = 0;
									blockMatrix[row - 1][column] = 0;
									blockMatrix[row - 1][column + 2] = 0;
									rotation = 1;
								}
							}
						}
						else if(rotation == 1){
							/*   o
							 * . o
							 *   o o
							 * */

							/* limits with the screen*/
							if (column == 0){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row - 1][column + 1]) == 1) ||
									((pileMatrix[row - 2][column + 1]) == 1) ||
									((pileMatrix[row - 1][column - 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row - 1][column + 1] = 1;
									blockMatrix[row - 2][column + 1] = 1;
									blockMatrix[row - 1][column - 1] = 1;

									blockMatrix[row][column] = 0;
									blockMatrix[row][column + 1] = 0;
									blockMatrix[row - 2][column] = 0;
									rotation = 2;
								}
							}
						}
						else if(rotation == 2){
							/*     o
							 * o o o
							 *   .
							 * */

							/* limits with the screen*/
							if (row >= 15){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row - 1][column]) == 1) ||
									((pileMatrix[row - 1][column + 1]) == 1) ||
									((pileMatrix[row + 1][column + 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row - 1][column] = 1;
									blockMatrix[row - 1][column + 1] = 1;
									blockMatrix[row + 1][column + 1] = 1;

									blockMatrix[row][column] = 0;
									blockMatrix[row][column + 2] = 0;
									blockMatrix[row - 1][column + 2] = 0;
									rotation = 3;
								}
							}
						}
						else if(rotation == 3){
							/* o o
							 *   o .
							 *   o
							 * */

							/* limits with the screen*/
							if (column >= 7){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row][column - 1]) == 1) ||
									((pileMatrix[row - 1][column - 1]) == 1) ||
									((pileMatrix[row - 1][column + 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row][column - 1] = 1;
									blockMatrix[row - 1][column - 1] = 1;
									blockMatrix[row - 1][column + 1]= 1;

									blockMatrix[row][column] = 0;
									blockMatrix[row - 2][column] = 0;
									blockMatrix[row - 2][column - 1] = 0;
									rotation = 0;
								}
							}
						}
					}
				}

			}
		}

		if (currentBlock == J){
			for (row = (ROW - 1); ((row >= 0)&& (found == 0)); row--){
				for (column = 0; (column <= (COLUMN - 1) && (found == 0)); column++){
					/* This will be the most left down dot*/
					if (blockMatrix[row][column] == 1){
						found = 1;
						/*   .
						 * o o o
						 *     o
						 * */
						if (rotation == 0){
							/* limits with the screen*/
							if (row <= 1){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row][column - 1]) == 1) ||
									((pileMatrix[row - 2][column]) == 1) ||
									((pileMatrix[row - 2][column - 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row][column - 1] = 1;
									blockMatrix[row - 2][column] = 1;
									blockMatrix[row - 2][column - 1] = 1;

									blockMatrix[row][column] = 0;
									blockMatrix[row - 1][column] = 0;
									blockMatrix[row - 1][column - 2] = 0;
									rotation = 1;
								}
							}
						}
						else if(rotation == 1){
							/*   o o
							 * . o
							 *   o
							 * */

							/* limits with the screen*/
							if (column == 0){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row - 1][column + 1]) == 1) ||
									((pileMatrix[row - 2][column - 1]) == 1) ||
									((pileMatrix[row - 1][column - 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row - 1][column + 1] = 1;
									blockMatrix[row - 2][column - 1] = 1;
									blockMatrix[row - 1][column - 1] = 1;

									blockMatrix[row][column] = 0;
									blockMatrix[row - 2][column] = 0;
									blockMatrix[row - 2][column + 1] = 0;
									rotation = 2;
								}
							}
						}
						else if(rotation == 2){
							/* o
							 * o o o
							 *   .
							 * */

							/* limits with the screen*/
							if (row >= 15){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row + 1][column + 1]) == 1) ||
									((pileMatrix[row + 1][column]) == 1) ||
									((pileMatrix[row - 1][column + 1]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row + 1][column + 1] = 1;
									blockMatrix[row + 1][column] = 1;
									blockMatrix[row - 1][column + 1] = 1;

									blockMatrix[row][column] = 0;
									blockMatrix[row - 1][column] = 0;
									blockMatrix[row][column + 2] = 0;
									rotation = 3;
								}
							}
						}
						else if(rotation == 3){
							/*   o
							 *   o .
							 * o o
							 * */

							/* limits with the screen*/
							if (column >= 7){
								return;
							}else{
								/* space with the pile for rotation */
								if (((pileMatrix[row][column + 2]) == 1) ||
									((pileMatrix[row - 1][column + 2]) == 1) ||
									((pileMatrix[row - 1][column]) == 1)){
										/* no space, return*/
										return;
								}else{
									blockMatrix[row][column + 2] = 1;
									blockMatrix[row - 1][column + 2] = 1;
									blockMatrix[row - 1][column]= 1;

									blockMatrix[row][column] = 0;
									blockMatrix[row][column + 1] = 0;
									blockMatrix[row - 2][column + 1] = 0;
									rotation = 0;
								}
							}
						}
					}
				}
			}
		}
		/* Updating screen */
		for(row = 0; row < ROW; row++){
			/* Updating the current block */
			for (column = 0; column < COLUMN; column++) {
				displayMatrix[row][column] = (pileMatrix[row][column] | blockMatrix[row][column]);
			}
		}

	}

	/* Function to move a block left -- eg. (*displayMatrix)[1][0] = 7;*/
	void GAME_moveLeft(){

		/* Variable to hold the updated block. It will be used to detect collisions*/
		TScreenMatrix movedBlock = {{0}};
		int row;
		int column;
		uint8_t stop = 0;


		/* From right to left */
		for (row = (ROW - 1); (row >= 0) && (stop == 0); row--){
			for (column = 0; column <= (COLUMN - 1); column++){
				if (blockMatrix[row][column] == 1){
					/* If we are in the most right */
					if(column == 0) stop = 1;
					/* Below we have an obstacle*/
					if(column > 0){
						if(pileMatrix[row][column - 1] == 1)stop = 1;
					}
					movedBlock[row][column] = 0;
					movedBlock[row][column - 1] = 1;
				}
			}
		}

		/* After checking the block against the display matrix we take actions*/
		if (stop == 0){

			for(row = 0; row < ROW; row++){
				/* Updating the current block */
				for (column = 0; column < COLUMN; column++) {
					blockMatrix[row][column] = movedBlock[row][column];
					displayMatrix[row][column] = (pileMatrix[row][column] | blockMatrix[row][column]);
				}
			}

		}else
		{
			/* If we reach this means that we have an obstacle and thus we should not move the block */
		}

	}


	/* Function to move a block right */
	void GAME_moveRight(){
		/* Variable to hold the updated block. It will be used to detect collisions*/
		TScreenMatrix movedBlock = {{0}};
		int row;
		int column;
		uint8_t stop = 0;


		/* From right to left */
		for (row = (ROW - 1); (row >= 0) && (stop == 0); row--){
			for (column = (COLUMN - 1); column >= 0; column--){
				if (blockMatrix[row][column] == 1){
					/* If we are in the most right */
					if(column == (COLUMN - 1)) stop = 1;
					/* Below we have an obstacle*/
					if(column < (COLUMN - 1)){
						if(pileMatrix[row][column + 1] == 1)stop = 1;
					}
					movedBlock[row][column] = 0;
					movedBlock[row][column + 1] = 1;
				}
			}
		}

		/* After checking the block against the display matrix we take actions*/
		if (stop == 0){

			for(row = 0; row < ROW; row++){
				/* Updating the current block */
				for (column = 0; column < COLUMN; column++) {
					blockMatrix[row][column] = movedBlock[row][column];
					displayMatrix[row][column] = (pileMatrix[row][column] | blockMatrix[row][column]);
				}
			}

		}else
		{
			/* If we reach this means that we have an obstacle and thus we should not move the block */
		}

	}




	/* Function to move a block to the bottom until down is not pressed */
	void GAME_moveToBottom(){
		GAME_moveDown();
	}

	/* Function to move the block 1 row down*/
	void GAME_moveDown(){
		/* Variable to hold the updated block. It will be used to detect collisions*/
		TScreenMatrix movedBlock = {{0}};
		int row;
		int column;
		int dots = 0;


		/* We need to find 4 dots and they need to be not blocked in order to move down*/


		/* From bottom to top we check the pile */
		for (row = (ROW - 1); (row >= 0); row--){

			for (column = 0; column < COLUMN; column++){
				if (blockMatrix[row][column] == 1){
					/* Row 15 reached */
					if(row == (ROW - 1)) break;
					/* Below we have an obstacle*/
					if (row < (ROW-1)){
						if(pileMatrix[row + 1][column] == 1)break;
					}
					movedBlock[row][column] = 0;
					movedBlock[row + 1][column] = 1;
					dots++;
				}
			}
		}

		/* After checking the block against the display matrix we take actions*/
		if (dots == 4){

			for(row = 0; row < ROW; row++){
				/* Updating the current block */
				for (column = 0; column < COLUMN; column++) {
					blockMatrix[row][column] = movedBlock[row][column];
					displayMatrix[row][column] = (pileMatrix[row][column] | blockMatrix[row][column]);
				}
			}

		}else{
			for(row = 0; row < ROW; row++){
				/* Updating the current pile with the block which was used to call this function */
				for (column = 0; column < COLUMN; column++) {
					pileMatrix[row][column] |= blockMatrix[row][column];
					displayMatrix[row][column] = pileMatrix[row][column];
				}
			}
			/* No block to move, flag to generate a new one in the engine */
			currentBlock = NONE;
		}

	}


	/*
	 * This function will check if a complete line has been filled.
	 */
	void GAME_checkFullRows(){
		uint8_t row;
		uint8_t column;
		uint8_t dots = 0;


		/* From bottom to top we check the pile */
		for (row = 0; row < ROW; row++){
			dots = 0;
			for (column = 0; column < COLUMN; column++){
				if (pileMatrix[row][column] == 1) dots ++;
				if (dots == 8){
					GAME_removeRow (row);
				}
			}
		}
	}

	/* this function will remove the row when completed.*/
	void GAME_removeRow(int rowFull){
		int row;
		uint8_t column;

		/* From bottom to top we check the pile */
		for (row = rowFull; row >= 0; row--){
			for (column = 0; column < COLUMN; column++){
				if (row == 0){
					pileMatrix[row][column] = 0;
					displayMatrix[row][column] = 0;
				}else {
					pileMatrix[row][column] = pileMatrix[row - 1][column];
					displayMatrix[row][column] = displayMatrix[row - 1][column];
				}
			}
		}
		numLines++;

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
			for (j = 0; j < COLUMN; j++)displayMatrix[i][j] = screenToCopy[i][j];
		}

	}

	/* Save the score to the flash for having a ranking*/
	void GAME_saveScore(uint32_t lines){

	}

	/* Game configuration */
	void GAME_Config(void){
		numLines = 0;
		GAME_copyScreen(gameIdle);
	}

	/* This function will create a block if there is NONE */
	void GAME_CreateBlock(){
		uint8_t row;
		uint8_t column;
		uint8_t gameFinished = 0;


		for(row = 0; row < ROW; row++){
			/* Updating the current Screen */
			for (column = 0; column < COLUMN; column++) {
				blockMatrix[row][column] = 0;
			}
		}

		/* To DO: Implement a true random generator*/
		switch(rand() % 7){
		    /*  o o
		     *  o o
		     * */
			case 0:
					/* Checking if we can place a new block */
					if ((displayMatrix[0][3] == 1) || (displayMatrix[0][4] == 1)||
						(displayMatrix[1][3] == 1) || (displayMatrix[1][4] == 1)) gameFinished = 1;

					currentBlock = O;
					blockMatrix[0][3] = 1;
					blockMatrix[0][4] = 1;
					blockMatrix[1][3] = 1;
					blockMatrix[1][4] = 1;
					displayMatrix[0][3] = 1;
					displayMatrix[0][4] = 1;
					displayMatrix[1][3] = 1;
					displayMatrix[1][4] = 1;
				break;
			case 1:
			    /*
			     *  o o o o
			     * */
					/* Checking if we can place a new block */
					if ((displayMatrix[0][2] == 1) || (displayMatrix[0][3] == 1)||
						(displayMatrix[0][4] == 1) || (displayMatrix[0][5] == 1)) gameFinished = 1;

					currentBlock = I;
					blockMatrix[0][2] = 1;
					blockMatrix[0][3] = 1;
					blockMatrix[0][4] = 1;
					blockMatrix[0][5] = 1;
					displayMatrix[0][2] = 1;
					displayMatrix[0][3] = 1;
					displayMatrix[0][4] = 1;
					displayMatrix[0][5] = 1;
				break;
			case 2:
			    /*  o o o
			     *  o
			     * */
					/* Checking if we can place a new block */
					if ((displayMatrix[0][3] == 1) || (displayMatrix[0][4] == 1)||
						(displayMatrix[0][5] == 1) || (displayMatrix[1][3] == 1)) gameFinished = 1;

					currentBlock = L;
					blockMatrix[0][3] = 1;
					blockMatrix[0][4] = 1;
					blockMatrix[0][5] = 1;
					blockMatrix[1][3] = 1;
					displayMatrix[0][3] = 1;
					displayMatrix[0][4] = 1;
					displayMatrix[0][5] = 1;
					displayMatrix[1][3] = 1;
				break;

			case 3:
			    /*  o o o
			     *      o
			     * */
					/* Checking if we can place a new block */
					if ((displayMatrix[0][3] == 1) || (displayMatrix[0][4] == 1)||
						(displayMatrix[0][5] == 1) || (displayMatrix[1][5] == 1)) gameFinished = 1;

					currentBlock = J;
					blockMatrix[0][3] = 1;
					blockMatrix[0][4] = 1;
					blockMatrix[0][5] = 1;
					blockMatrix[1][5] = 1;
					displayMatrix[0][3] = 1;
					displayMatrix[0][4] = 1;
					displayMatrix[0][5] = 1;
					displayMatrix[1][5] = 1;
				break;
			case 4:
			    /*    o o
			     *  o o
			     * */
					/* Checking if we can place a new block */
					if ((displayMatrix[0][4] == 1) || (displayMatrix[0][5] == 1)||
						(displayMatrix[1][3] == 1) || (displayMatrix[1][4] == 1)) gameFinished = 1;

					currentBlock = S;
					blockMatrix[0][4] = 1;
					blockMatrix[0][5] = 1;
					blockMatrix[1][3] = 1;
					blockMatrix[1][4] = 1;
					displayMatrix[0][4] = 1;
					displayMatrix[0][5] = 1;
					displayMatrix[1][3] = 1;
					displayMatrix[1][4] = 1;
				break;
			case 5:
			    /*  o o
			     *    o o
			     * */
					/* Checking if we can place a new block */
					if ((displayMatrix[0][3] == 1) || (displayMatrix[0][4] == 1)||
						(displayMatrix[1][4] == 1) || (displayMatrix[1][5] == 1)) gameFinished = 1;

					currentBlock = Z;
					blockMatrix[0][3] = 1;
					blockMatrix[0][4] = 1;
					blockMatrix[1][4] = 1;
					blockMatrix[1][5] = 1;
					displayMatrix[0][3] = 1;
					displayMatrix[0][4] = 1;
					displayMatrix[1][4] = 1;
					displayMatrix[1][5] = 1;
				break;
			case 6:
			    /*  o o o
			     *    o
			     * */
					/* Checking if we can place a new block */
					if ((displayMatrix[0][4] == 1) || (displayMatrix[0][5] == 1)||
						(displayMatrix[1][3] == 1) || (displayMatrix[1][4] == 1)) gameFinished = 1;

					currentBlock = T;
					blockMatrix[0][3] = 1;
					blockMatrix[0][4] = 1;
					blockMatrix[0][5] = 1;
					blockMatrix[1][4] = 1;
					displayMatrix[0][3] = 1;
					displayMatrix[0][4] = 1;
					displayMatrix[0][5] = 1;
					displayMatrix[1][4] = 1;
				break;
			default:
					currentBlock = NONE;
					blockMatrix[2][3] = 1;
					blockMatrix[0][4] = 1;
					blockMatrix[0][5] = 1;
					blockMatrix[2][3] = 1;
					displayMatrix[2][3] = 1;
					displayMatrix[0][4] = 1;
					displayMatrix[0][5] = 1;
					displayMatrix[2][3] = 1;
				break;
		}

		if (gameFinished == 1){
			gameState = GAME_OVER;
		}else{
			/* If game not finished we got a new block and this will hold itscurrent status */
			rotation = 0;
		}


	}

	/* nextMove will decide what next move is going to be done by checking the input buttons
	 * We will differentiate between first time we press the button, long press and repetitions after long press detected
	 * The logic will be:
	 * if down pressed, it doesn't matter the others
	 * if not if up(rotate pressed, it doesn't matter left or right)
	 * if left or right are not pressed at the same time, the move is left of right otherwise nothing*/
	uint8_t GAME_nextMove(void){
		/*##### Variables #####*/
		/* next move variable */
		uint8_t move = 0;

		/* This variables will be used to see if we have a long press so we move/rotate every X ms */
		static uint32_t timeNow = 0;
		static uint32_t timePrev_LEFT = 0;
		static uint32_t timePrev_RIGHT = 0;
		static uint32_t timePrev_UP = 0;
		static uint32_t timePrev_DOWN = 0;
		/* Time variables to wait until repeat */
		static uint16_t repeat_LEFT = LONG_PRESS_MS;
		static uint16_t repeat_RIGHT = LONG_PRESS_MS;
		static uint16_t repeat_UP = LONG_PRESS_MS;
		static uint16_t repeat_DOWN = LONG_PRESS_MS;

		/* We need to see if it is the first time we press the button. In this way we can detect a long press
		 * slower and then the re-iterations will be faster */
		static uint8_t firstLeft  = 1;
		static uint8_t firstRight = 1;
		static uint8_t firstUp	  = 1;
		static uint8_t firstDown  = 1;
		/* These variables will hold the current button status
		 * */
		static GPIO_PinState left;
		static GPIO_PinState right;
		static GPIO_PinState up;
		static GPIO_PinState down;


		/*##### Function logic #####*/

		/* Retrieving data */
		timeNow = HAL_GetTick();
		left 	= HAL_GPIO_ReadPin(BUTTON_LEFT_GPIO_Port, BUTTON_LEFT_Pin);
		right 	= HAL_GPIO_ReadPin(BUTTON_RIGHT_GPIO_Port, BUTTON_RIGHT_Pin);
		up 		= HAL_GPIO_ReadPin(BUTTON_UP_GPIO_Port, BUTTON_UP_Pin);
		down 	= HAL_GPIO_ReadPin(BUTTON_DOWN_GPIO_Port, BUTTON_DOWN_Pin);




		if (down == GPIO_PIN_SET){
			timePrev_DOWN = timeNow;
			if(firstDown == 0){
				firstDown = 1;
				repeat_DOWN = LONG_DOWN_MS;
			}
		}else{
			if(firstDown == 1){
				firstDown = 0;
				move |= (DOWN  & (~down << 2));
			}else{
				if((timeNow - timePrev_DOWN) > repeat_DOWN){
					/* Long press */
					move |= (DOWN  & (~down << 2));
					timePrev_DOWN = timeNow;
					repeat_DOWN = REPEAT_DOWN_MS;
				}
			}

			/* If down is press we will ignore other buttons*/
			return move;
		}

		if (up == GPIO_PIN_SET){
			timePrev_UP = timeNow;
			if(firstUp == 0){
				firstUp = 1;
				repeat_UP = LONG_PRESS_MS;
			}
		}else{
			if(firstUp == 1){
				firstUp = 0;
				move |= (UP & (~up << 3));
			}else{
				if((timeNow - timePrev_UP) > repeat_UP){
					move |= (UP & (~up << 3));
					timePrev_UP = timeNow;
					repeat_UP = REPEAT_PRESS_MS;
				}
			}

			/* If rotate is pressed ignoring left and right */
			return move;
		}

		/* Move right, it will have first press and long presses */
		if (right == GPIO_PIN_SET){
			timePrev_RIGHT = timeNow;
			if(firstRight == 0){
				firstRight = 1;
				repeat_RIGHT = LONG_PRESS_MS;
			}
		}else{
			if( left != right ){
				if(firstRight == 1){
					firstRight = 0;
					move |= (RIGHT & (~right));
				}else{
					if((timeNow - timePrev_RIGHT) > repeat_RIGHT){
						move |= (RIGHT & (~right));
						timePrev_RIGHT = timeNow;
						repeat_RIGHT = REPEAT_PRESS_MS;
					}
				}
			}else return 0;
		}

		/* Move left, it will have first press and long presses */
		if (left == GPIO_PIN_SET){
			timePrev_LEFT = timeNow;
			if(firstLeft == 0){
				firstLeft = 1;
				repeat_LEFT = LONG_PRESS_MS;
			}
		}else{
			if( left != right ){
				if(firstLeft == 1){
					firstLeft = 0;
					move |= (LEFT & (~left << 1));
				}else{
					if((timeNow - timePrev_LEFT) > repeat_LEFT){
						move |= (LEFT & (~left << 1));
						timePrev_LEFT = timeNow;
						repeat_LEFT = REPEAT_PRESS_MS;

					}
				}
			}else return 0;
		}

		/* if every button is pressed or repeating buttons = 0x15   0x8 | 0x4 | 0x2 | 0x1 */

		return move;
	}



	/* This is the main game task where we will move, rotate, call sounds and control the whole game*/
	void GAME_EngineTask_20ms(void){
		/*##### Variables #####*/
		uint8_t buttons;
		uint8_t row,column;
		static uint8_t gameOver_WAIT = 0;
		static uint32_t timeNow = 0;
		static uint32_t timePrev = 0;

		/* Buttons pressed by the user */
		buttons = GAME_nextMove();

		/*## State machine BEGGINS ##*/
		if (gameState == IDLE){
			if (buttons == UP) {
				gameState = PLAYING;
				gameOver_WAIT = 0;
				/* Starting game */
				GAME_copyScreen(gameBlank);
				/* Restarting PILE */
				for(row = 0; row < ROW; row++){
					/* Updating the current Screen */
					for (column = 0; column < COLUMN; column++) {
						pileMatrix[row][column] = 0;
					}
				}
				currentBlock = NONE;
				numLines = 0;
			}
		}else if(gameState == GAME_OVER){
			if(gameOver_WAIT == 0){
				timeNow = HAL_GetTick();
				if ((timeNow - timePrev) > 1500){
					GAME_copyScreen(gameOver);
					gameOver_WAIT = 1;
				}
			}
			else{

				if (buttons == UP) {
					gameState = IDLE;
					GAME_copyScreen(gameIdle);
				}
			}
		}else if(gameState == PLAYING){

			/*##### Playing logic #####*/
			timeNow = HAL_GetTick();

			if (currentBlock == NONE){
				/* Checking for full rows */
				GAME_checkFullRows();
				GAME_CreateBlock();

				/* Restarting game status variables */
				timePrev = timeNow;
			}

			/* After TIME_ONE_DOWN in ms time to move the block down */
			if (timeNow - timePrev > TIME_ONE_DOWN){
				GAME_moveDown();
				timePrev = timeNow;
			}

			/* If left and right pressed at the same time, don't move (Lighting led pin)*/
			switch (buttons){
				case LEFT:
					GAME_moveLeft();
				break;
				case RIGHT:
					GAME_moveRight();
				break;
				case UP:
					GAME_rotateBlock();

				break;
				case DOWN:
					GAME_moveToBottom();
					/* We don't want the automatic down move to take action while down is pressed by the user */
					timePrev = timeNow;
				break;
				default:
					//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
				break;
			}



		}
		/*## State machine ENDS ##*/
		MATRIX_matrixVariableUpdate(displayMatrix);
	}






