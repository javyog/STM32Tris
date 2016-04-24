/*
 * game.h
 *
 *  Created on: Apr 24, 2016
 *      Author: Javier Oliver
 */

#ifndef INC_GAME_H_
#define INC_GAME_H_

/* Game configuration */
void GAME_Config(void);

/* Configuration function for the Syst*/
void SystemClock_Config(void);

/* Task to move down the current block*/
void GAME_BlockDownTask_1000ms(void);

/**/

#endif /* INC_GAME_H_ */

