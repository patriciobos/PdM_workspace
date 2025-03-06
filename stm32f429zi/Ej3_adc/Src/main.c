/**
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define INTERNAL_TEMPSENSOR_AVGSLOPE   ((float)    2.5)	       /* Internal temperature sensor, parameter Avg_Slope (unit: mV/DegCelsius). Refer to device datasheet for min/typ/max values. */
#define INTERNAL_TEMPSENSOR_V25        ((int32_t)  760)        /* Internal temperature sensor, parameter V25 (unit: mV). Refer to device datasheet for min/typ/max values. */
#define INTERNAL_TEMPSENSOR_V25_TEMP   ((int32_t)   25)
#define INTERNAL_TEMPSENSOR_V25_VREF   ((int32_t) 3300)

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef uartHandle;
ADC_HandleTypeDef adcHandler;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/
static void MX_UART3_Init(void);
static void MX_ADC1_Init(void);

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {
	/* STM32F4xx HAL library initialization:
	 - Configure the Flash prefetch
	 - Systick timer is configured by default as source of time base, but user
	 can eventually implement his proper time base source (a general purpose
	 timer for example or other time source), keeping in mind that Time base
	 duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
	 handled in milliseconds basis.
	 - Set NVIC Group Priority to 4
	 - Low Level Initialization
	 */
	HAL_Init();

	//Nucleo_BSP_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	/* Initialize BSP Led for LED2 and LED3*/
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	/* Initialize all configured peripherals */
	MX_UART3_Init();

	MX_ADC1_Init();

	HAL_ADC_Start(&adcHandler);

	/* Infinite loop */
	while (1) {
		char msg[50];
		uint16_t rawValue;
		float temp;

		HAL_ADC_PollForConversion(&adcHandler, HAL_MAX_DELAY);

		rawValue = HAL_ADC_GetValue(&adcHandler);
		temp = ((float) rawValue) / 4095 * INTERNAL_TEMPSENSOR_V25_VREF;
		temp = ((temp - INTERNAL_TEMPSENSOR_V25) / INTERNAL_TEMPSENSOR_AVGSLOPE) + INTERNAL_TEMPSENSOR_V25_TEMP;

		sprintf(msg, "rawValue: %hu\r\n", rawValue);
		HAL_UART_Transmit(&uartHandle, (uint8_t*) msg, strlen(msg), HAL_MAX_DELAY);

		// Limitar la precisión a 2 decimales
		sprintf(msg, "Temperature (C): %.2f\r\n", temp);
		HAL_UART_Transmit(&uartHandle, (uint8_t*) msg, strlen(msg), HAL_MAX_DELAY);

		BSP_LED_Toggle(LED3);
		HAL_Delay(100);
	}
}

/* UART2 init function*/
static void MX_UART3_Init(void){
	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
		 - Word Length = 8 Bits
		 - Stop Bit    = One Stop bit
		 - Parity      = NONE parity
		 - BaudRate    = 9600 baud
		 - Hardware flow control disabled (RTS and CTS signals) */
	uartHandle.Instance = USARTx;

	uartHandle.Init.BaudRate = 9600;
	uartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	uartHandle.Init.StopBits = UART_STOPBITS_1;
	uartHandle.Init.Parity = UART_PARITY_NONE;
	uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uartHandle.Init.Mode = UART_MODE_TX_RX;
	uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&uartHandle) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	/* Output a message on Hyperterminal using printf function */
	printf(
			"\n\r UART Printf Example: retarget the C library printf function to the UART\n\r");
	printf("** Test finished successfully. ** \n\r");
}

/* ADC1 init function */
static void MX_ADC1_Init(void) {
	ADC_ChannelConfTypeDef sConfig;

	/* Enable ADC peripheral */
	__HAL_RCC_ADC1_CLK_ENABLE();

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	adcHandler.Instance = ADC1;
	adcHandler.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	adcHandler.Init.Resolution = ADC_RESOLUTION_12B;
	adcHandler.Init.ScanConvMode = DISABLE;
	adcHandler.Init.ContinuousConvMode = ENABLE;
	adcHandler.Init.DiscontinuousConvMode = DISABLE;
	adcHandler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	adcHandler.Init.NbrOfConversion = 1;
	adcHandler.Init.DMAContinuousRequests = DISABLE;
	adcHandler.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	HAL_ADC_Init(&adcHandler);

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	HAL_ADC_ConfigChannel(&adcHandler, &sConfig);
}

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART3 and Loop until the end of transmission */
	HAL_UART_Transmit(&uartHandle, (uint8_t*) &ch, 1, 0xFFFF);

	return ch;
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 180000000
 *            HCLK(Hz)                       = 180000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 8000000
 *            PLL_M                          = 8
 *            PLL_N                          = 360
 *            PLL_P                          = 2
 *            PLL_Q                          = 7
 *            PLL_R                          = 2
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 5
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
	 clocked below the maximum system frequency, to update the voltage scaling value
	 regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}
}
/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void) {
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
#endif
