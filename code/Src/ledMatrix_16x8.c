/*
 * ledMatrix_16x8.c
 *
 *  Created on: Apr 25, 2016
 *      Author: Javier Oliver
 */

	#include "ledMatrix_16x8.h"
	#include "gpio.h"
	#include "game.h"


    /* Refreshes */
	void MATRIX_refreshMatrix(screenMatrix matrix){
		uint8_t i;

		for(i = 0; i < ROW; i++){
			/* The cathodes are common in both 8x8 matrixes. The anodes are not that's why we have 16 ROW and only 8 cathodes*/
			if( i < 8 ){
				MATRIX_selectCommonCathode(i);
			}else MATRIX_selectCommonCathode(i - 8);

			MATRIX_drawLine(matrix[i], i);

		}

	}

	/* Aux function to select the common cathode pin  */
	void MATRIX_selectCommonCathode(uint8_t cathode){
	  /* Reset X Pin*/


		HAL_GPIO_WritePin(MATRIX_X0_GPIO_Port, MATRIX_X0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X1_GPIO_Port, MATRIX_X1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MATRIX_X2_GPIO_Port, MATRIX_X2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X3_GPIO_Port, MATRIX_X3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X4_GPIO_Port, MATRIX_X4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X5_GPIO_Port, MATRIX_X5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X6_GPIO_Port, MATRIX_X6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MATRIX_X7_GPIO_Port, MATRIX_X7_Pin, GPIO_PIN_SET);



		/*
		if(cathode == 0){
			HAL_GPIO_WritePin(MATRIX_X7_GPIO_Port, MATRIX_X7_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MATRIX_X0_GPIO_Port, MATRIX_X0_Pin, GPIO_PIN_RESET);
		}else if(cathode == 1){
			HAL_GPIO_WritePin(MATRIX_X0_GPIO_Port, MATRIX_X0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MATRIX_X1_GPIO_Port, MATRIX_X1_Pin, GPIO_PIN_RESET);
		}else if(cathode == 2){
			HAL_GPIO_WritePin(MATRIX_X1_GPIO_Port, MATRIX_X1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MATRIX_X2_GPIO_Port, MATRIX_X2_Pin, GPIO_PIN_RESET);
		}else if(cathode == 3){
			HAL_GPIO_WritePin(MATRIX_X2_GPIO_Port, MATRIX_X2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MATRIX_X3_GPIO_Port, MATRIX_X3_Pin, GPIO_PIN_RESET);
		}else if(cathode == 4){
			HAL_GPIO_WritePin(MATRIX_X3_GPIO_Port, MATRIX_X3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MATRIX_X4_GPIO_Port, MATRIX_X4_Pin, GPIO_PIN_RESET);
		}else if(cathode == 5){
			HAL_GPIO_WritePin(MATRIX_X4_GPIO_Port, MATRIX_X4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MATRIX_X5_GPIO_Port, MATRIX_X5_Pin, GPIO_PIN_RESET);
		}else if(cathode == 6){
			HAL_GPIO_WritePin(MATRIX_X5_GPIO_Port, MATRIX_X5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MATRIX_X6_GPIO_Port, MATRIX_X6_Pin, GPIO_PIN_RESET);
		}else if(cathode == 7){
			HAL_GPIO_WritePin(MATRIX_X6_GPIO_Port, MATRIX_X6_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MATRIX_X7_GPIO_Port, MATRIX_X7_Pin, GPIO_PIN_RESET);
		}
		*/
	}

	/* draws a single line when the common cathode is selected */
    void MATRIX_drawLine(uint8_t *line, uint8_t cathode){
    	HAL_GPIO_WritePin(MATRIX_Y0_GPIO_Port, MATRIX_Y0_Pin, GPIO_PIN_RESET);
    	HAL_GPIO_WritePin(MATRIX_Y1_GPIO_Port, MATRIX_Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MATRIX_Y2_GPIO_Port, MATRIX_Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MATRIX_Y3_GPIO_Port, MATRIX_Y3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MATRIX_Y4_GPIO_Port, MATRIX_Y4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MATRIX_Y5_GPIO_Port, MATRIX_Y5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MATRIX_Y6_GPIO_Port, MATRIX_Y6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MATRIX_Y7_GPIO_Port, MATRIX_Y7_Pin, GPIO_PIN_SET);


/*
    	if (cathode < 8){
    		HAL_GPIO_WritePin(MATRIX_Y0_GPIO_Port, MATRIX_Y0_Pin, MATRIX_ledValue(line[0]));
    		HAL_GPIO_WritePin(MATRIX_Y1_GPIO_Port, MATRIX_Y1_Pin, MATRIX_ledValue(line[1]));
    		HAL_GPIO_WritePin(MATRIX_Y2_GPIO_Port, MATRIX_Y2_Pin, MATRIX_ledValue(line[2]));
    		HAL_GPIO_WritePin(MATRIX_Y3_GPIO_Port, MATRIX_Y3_Pin, MATRIX_ledValue(line[3]));
    		HAL_GPIO_WritePin(MATRIX_Y4_GPIO_Port, MATRIX_Y4_Pin, MATRIX_ledValue(line[4]));
    		HAL_GPIO_WritePin(MATRIX_Y5_GPIO_Port, MATRIX_Y5_Pin, MATRIX_ledValue(line[5]));
    		HAL_GPIO_WritePin(MATRIX_Y6_GPIO_Port, MATRIX_Y6_Pin, MATRIX_ledValue(line[6]));
    		HAL_GPIO_WritePin(MATRIX_Y7_GPIO_Port, MATRIX_Y7_Pin, MATRIX_ledValue(line[7]));
    	}else{
    		HAL_GPIO_WritePin(MATRIX_Y8_GPIO_Port, MATRIX_Y8_Pin, MATRIX_ledValue(line[0]));
    		HAL_GPIO_WritePin(MATRIX_Y9_GPIO_Port, MATRIX_Y9_Pin, MATRIX_ledValue(line[1]));
    		HAL_GPIO_WritePin(MATRIX_Y10_GPIO_Port, MATRIX_Y10_Pin, MATRIX_ledValue(line[2]));
    		HAL_GPIO_WritePin(MATRIX_Y11_GPIO_Port, MATRIX_Y11_Pin, MATRIX_ledValue(line[3]));
    		HAL_GPIO_WritePin(MATRIX_Y12_GPIO_Port, MATRIX_Y12_Pin, MATRIX_ledValue(line[4]));
    		HAL_GPIO_WritePin(MATRIX_Y13_GPIO_Port, MATRIX_Y13_Pin, MATRIX_ledValue(line[5]));
    		HAL_GPIO_WritePin(MATRIX_Y14_GPIO_Port, MATRIX_Y14_Pin, MATRIX_ledValue(line[6]));
    		HAL_GPIO_WritePin(MATRIX_Y15_GPIO_Port, MATRIX_Y15_Pin, MATRIX_ledValue(line[7]));

    	}
*/
    }

    GPIO_PinState MATRIX_ledValue(uint8_t value){
    	if (value == 1){
    		return GPIO_PIN_SET;
    	}else {
    		return GPIO_PIN_RESET;
    	}
    }
