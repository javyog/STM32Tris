/*
 * ledMatrix_16x8.h
 *
 *  Created on: Apr 25, 2016
 *      Author: Javier Oliver
 */

	#ifndef INC_LEDMATRIX_16X8_H_
	#define INC_LEDMATRIX_16X8_H_

	/* includes */
	#include "game.h"
	#include "gpio.h"

	int refreshColumn;
	/* functions */
    /* Refreshes */
	void MATRIX_refreshMatrix(screenMatrix matrix);

	/* Aux function to select the common cathode pin (0-7)*/
	void MATRIX_selectX(uint8_t cathode);

	/* draws a single column (cathode)*/
    void MATRIX_drawY(screenMatrix matrix, uint8_t cathode);

    /* de-selects all X (columns)*/
    void MATRIX_resetX(void);

    /* This function will transform the values at the current matrix to PIN states (SET / RESET)*/
    GPIO_PinState MATRIX_ledValue(uint8_t value);

	#endif /* INC_LEDMATRIX_16X8_H_ */
