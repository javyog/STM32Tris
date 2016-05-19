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
	#include "rtc.h"
	#include "osd.h"
	#include "game.h"

	int main(void)
	{

		/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
		HAL_Init();

		/* Configure system clock tick for the scheduler. It is configured at 1ms and included inside osd.c */
		SystemClock_Config();

		/* Configure the game
		 * so far we only start the screen */
		GAME_Config();

		/* Initialize all configured peripherals */
		MX_GPIO_Init();

		/* The game works with SysTick interruptions. Tasks are scheduled in a sequential fashion in osd.c*/
		while (1)
		{


		}

	}


