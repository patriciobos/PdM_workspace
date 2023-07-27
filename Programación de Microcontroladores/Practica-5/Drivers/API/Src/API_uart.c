/*
 * API_uart.c
 *
 *  Created on: Jul 27, 2023
 *      Author: santiagobualo
 */

#include "API_uart.h"
#include <string.h>




static UART_HandleTypeDef huart2;
bool uartInit(void){

	bool CorrectInicialization = false;
	MX_USART2_UART_Init();
	if (HAL_UART_Init(&huart2) == HAL_OK)
	  {
		//UART PRINT VARIABLES de CONFIGURACION
		CorrectInicialization=true;
	  }
	return CorrectInicialization;
}

void uartSendString(uint8_t * pstring){

	 HAL_USART_Transmit(&huart2, pstring, strlen(pstring), UART_TIMER_MS(50));


}

void uartSendStringSize(uint8_t * pstring, uint16_t size){

	 HAL_USART_Transmit(&huart2, pstring, size, UART_TIMER_MS(50));

}
void uartReceiveStringSize(uint8_t * pstring, uint16_t size){

	HAL_USART_Receive(&huart2, pstring, size, UART_TIMER_MS(50));

}



static int MX_USART2_UART_Init(void)
{


  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;



}
