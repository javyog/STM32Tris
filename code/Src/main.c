/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  * Author			   : Javier Oliver
  ******************************************************************************
  */


/* Include external APIs */
	#include "stm32f1xx_hal.h"
	#include "gpio.h"
	#include "osd_api.h"
	#include "game.h"



	int main(void)
	{

		/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
		HAL_Init();

		/* Configure the game and the system clock */
		GAME_Config();

		/* Initialize all configured peripherals */
		MX_GPIO_Init();

		while (1)
		{


		}

	}


