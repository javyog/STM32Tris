/*
 * ledMatrix_16x8.h
 *
 *  Created on: Apr 25, 2016
 *      Author: Javier Oliver
 */

	#ifndef INC_LEDMATRIX_16X8_H_
	#define INC_LEDMATRIX_16X8_H_

	/* includes */
	#include "gpio.h"

	/* typedefs */
	typedef uint8_t TScreenMatrix[16][8];

	/* matrix will contain the data to show*/
	TScreenMatrix currentMatrix;

	/* Functions */
    /* Refreshes */
	void MATRIX_refreshMatrix(TScreenMatrix matrix);

	/* Aux function to select the common cathode pin (0-7)*/
	void MATRIX_selectX(uint8_t cathode);

	/* Draws a single column (cathode)*/
    void MATRIX_drawY(TScreenMatrix matrix, uint8_t cathode);

    /* De-selects all X (columns)*/
    void MATRIX_resetX(void);

    /* Update the matrix */
    void MATRIX_matrixVariableUpdate(TScreenMatrix matrix);

	/* Refreshes the screen at 200hz. Absolute minimum 50hz otherwise blinking noticiable. */
	void MATRIX_refreshScreenTask_5ms(void);

    /* This function will transform the values at the current matrix to PIN states (SET / RESET)*/
    GPIO_PinState MATRIX_ledValue(uint8_t value);

	#endif /* INC_LEDMATRIX_16X8_H_ */
