/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "stdbool.h"

/* Private define ------------------------------------------------------------*/
#define TIMEoN 	200
#define TIMEoFF 200

/* Private variables ---------------------------------------------------------*/
Led_TypeDef LED_sequence[] = { LED1, LED2, LED3 };

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void LED_blink(Led_TypeDef led, uint32_t timeOn, uint32_t timeOff);
void Init_peripherals();

/* Private user code ---------------------------------------------------------*/

/**
 * @brief  The application entry point.
 * @retval None
 */
int main(void) {
	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all required peripherals */
	Init_peripherals();

	const uint8_t MAXLED = sizeof(LED_sequence) / sizeof(Led_TypeDef);
	bool ascendingOrder = true;
	uint8_t index = 0;

	/* Infinite loop */
	while (1) {
		LED_blink(LED_sequence[index], TIMEoN, TIMEoFF);

		if (BSP_PB_GetState(BUTTON_USER)) {
			ascendingOrder = !ascendingOrder;
		}

		if (ascendingOrder) { // Loop through the array in ascending order
			index = (index < MAXLED - 1) ? index + 1 : 0;
		} else { // Loop through the array in descending order
			index = (index > 0) ? index - 1 : MAXLED - 1;
		}
	}
}

/**
 * @brief Initializes all required peripherals
 * @retval None
 */
void Init_peripherals() {

	/* Initialize BSP Led for LED2 */
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

}

/**
 * @brief  Blinks led
 * @param  led: LED number
 * @param  timeOn: time in which the led remains on
 * @param  timeOff: time in which the led remains off
 * @retval None
 */
void LED_blink(Led_TypeDef led, uint32_t timeOn, uint32_t timeOff) {
	BSP_LED_On(led);
	HAL_Delay(timeOn);
	BSP_LED_Off(led);
	HAL_Delay(timeOff);
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 168;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1) {
	}
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif /* USE_FULL_ASSERT */
