/*
 * TIMER.c
 *
 *  Created on: Aug 12, 2023
 *      Author: santiagobualo
 */

#include "TIMER.h"
#include "LED.h"

TIM_HandleTypeDef htim10;
uint8_t TimeIsDone=0;


void TIMERS_Init(void){
	TIM10_Init();

}

uint8_t TIME_GetTimeStatus(TIMERS myTimer){

	uint8_t TimeStatus=0;
	switch (myTimer){
			case TIMER_TIMEOUT :{

				TimeStatus=TimeIsDone;

			}
		}

return TimeStatus;
}

void TIME_ResetTimeStatus(TIMERS myTimer){

	switch (myTimer){
				case TIMER_TIMEOUT :{

					TimeIsDone=0;

				}
			}

	TIMER_Start(myTimer);
}

void TIMER_Start(TIMERS myTimer){

	switch (myTimer){
		case TIMER_TIMEOUT :{

				__HAL_TIM_SetCounter(&htim10, 0); //resetea el contador

		}
	}

}

/**
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
void TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 17200-1;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 50000-1;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */
  HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 15 ,0U);
  HAL_TIM_Base_Start_IT(&htim10);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if (htim == &htim10){
		TimeIsDone = 1;
		LED_Timeout_Blink();
	}
}
