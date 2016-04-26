/*
 * ledMatrix_16x8.c
 *
 *  Created on: Apr 25, 2016
 *      Author: Javier Oliver
 */

	#include "ledMatrix_16x8.h"
	#include "gpio.h"
	#include "game.h"

	/* variables */
	const screenMatrix test  = {
			/*     (0,0) X ——►
			 *      Y
			 *      |
			 *      ▼
			 *      ..
			 *      ..
			 *      ..
			 *    				(15,7)
			 * */
					{1,1,1,1,0,0,0,0},
					{1,1,1,1,0,0,0,0},
					{0,1,1,0,0,0,0,0},
					{0,1,1,0,1,1,1,1},
					{0,1,1,0,1,0,0,0},
					{0,0,0,0,1,1,1,0},
					{0,0,0,0,1,0,0,0},
					{0,0,0,0,1,1,1,1},
					{0,1,1,1,0,0,0,0},
					{1,0,0,0,0,0,0,0},
					{0,1,0,0,0,0,0,0},
					{0,0,1,0,1,1,1,1},
					{0,0,0,1,1,1,1,1},
					{1,1,1,0,0,1,1,0},
					{0,0,0,0,0,1,1,0},
					{0,0,0,0,0,1,1,0}
				   };

    /* Refreshes the screen*/
	void MATRIX_refreshMatrix(screenMatrix matrix){
		uint8_t cathode;

		/* We will refresh from columns from 0 to 7*/
		for(cathode = 0; cathode < COLUMN; cathode++){
			MATRIX_drawY(matrix, cathode);
		}
		MATRIX_resetX();
	}

	/* Aux function to select the common cathode pin  */
	void MATRIX_selectX(uint8_t cathode){
		if(cathode == 0){
			HAL_GPIO_WritePin(MATRIX_X0_GPIO_Port, MATRIX_X0_Pin, GPIO_PIN_RESET);
		}else if(cathode == 1){
			HAL_GPIO_WritePin(MATRIX_X1_GPIO_Port, MATRIX_X1_Pin, GPIO_PIN_RESET);
		}else if(cathode == 2){
			HAL_GPIO_WritePin(MATRIX_X2_GPIO_Port, MATRIX_X2_Pin, GPIO_PIN_RESET);
		}else if(cathode == 3){
			HAL_GPIO_WritePin(MATRIX_X3_GPIO_Port, MATRIX_X3_Pin, GPIO_PIN_RESET);
		}else if(cathode == 4){
			HAL_GPIO_WritePin(MATRIX_X4_GPIO_Port, MATRIX_X4_Pin, GPIO_PIN_RESET);
		}else if(cathode == 5){
			HAL_GPIO_WritePin(MATRIX_X5_GPIO_Port, MATRIX_X5_Pin, GPIO_PIN_RESET);
		}else if(cathode == 6){
			HAL_GPIO_WritePin(MATRIX_X6_GPIO_Port, MATRIX_X6_Pin, GPIO_PIN_RESET);
		}else if(cathode == 7){
			HAL_GPIO_WritePin(MATRIX_X7_GPIO_Port, MATRIX_X7_Pin, GPIO_PIN_RESET);
		}

	}

	/* draws a single line when the common cathode is selected */
    void MATRIX_drawY(screenMatrix matrix, uint8_t cathode){

    	/* Resets all common cathodes. They are shorted 1 to 1 in both Matrixes */
    	MATRIX_resetX();

		/* Selects Y (anodes)values from 0 to 15*/
		HAL_GPIO_WritePin(MATRIX_Y0_GPIO_Port, MATRIX_Y0_Pin, matrix[0][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y1_GPIO_Port, MATRIX_Y1_Pin, matrix[1][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y2_GPIO_Port, MATRIX_Y2_Pin, matrix[2][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y3_GPIO_Port, MATRIX_Y3_Pin, matrix[3][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y4_GPIO_Port, MATRIX_Y4_Pin, matrix[4][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y5_GPIO_Port, MATRIX_Y5_Pin, matrix[5][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y6_GPIO_Port, MATRIX_Y6_Pin, matrix[6][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y7_GPIO_Port, MATRIX_Y7_Pin, matrix[7][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y8_GPIO_Port, MATRIX_Y8_Pin, matrix[8][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y9_GPIO_Port, MATRIX_Y9_Pin, matrix[9][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y10_GPIO_Port, MATRIX_Y10_Pin, matrix[10][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y11_GPIO_Port, MATRIX_Y11_Pin, matrix[11][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y12_GPIO_Port, MATRIX_Y12_Pin, matrix[12][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y13_GPIO_Port, MATRIX_Y13_Pin, matrix[13][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y14_GPIO_Port, MATRIX_Y14_Pin, matrix[14][cathode]);
		HAL_GPIO_WritePin(MATRIX_Y15_GPIO_Port, MATRIX_Y15_Pin, matrix[15][cathode]);

		/* Select the next common X (cathode)*/
		MATRIX_selectX(cathode);

    }

    /* de-selects all X (columns)*/
    void MATRIX_resetX(void){
		HAL_GPIO_WritePin(MATRIX_X0_GPIO_Port, MATRIX_X0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X1_GPIO_Port, MATRIX_X1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X2_GPIO_Port, MATRIX_X2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X3_GPIO_Port, MATRIX_X3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X4_GPIO_Port, MATRIX_X4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X5_GPIO_Port, MATRIX_X5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X6_GPIO_Port, MATRIX_X6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X7_GPIO_Port, MATRIX_X7_Pin, GPIO_PIN_SET);
    }

    void MATRIX_testScreen(void){
    	MATRIX_refreshMatrix(test);
    }


    GPIO_PinState MATRIX_ledValue(uint8_t value){
    	if (value == 1){
    		return GPIO_PIN_SET;
    	}else {
    		return GPIO_PIN_RESET;
    	}
    }
