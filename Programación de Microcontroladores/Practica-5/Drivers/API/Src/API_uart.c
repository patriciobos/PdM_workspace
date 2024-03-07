/*
 * API_uart.c
 *
 *  Created on: Jul 27, 2023
 *      Author: santiagobualo
 */

#include "API_uart.h"
#include <string.h>




static UART_HandleTypeDef huart2;

static void MX_USART2_UART_Init(void);


bool uartInit(void){

	bool CorrectInicialization = false;
	MX_USART2_UART_Init();
	if (HAL_UART_Init(&huart2) == HAL_OK)
	  {
		uartSendString("\033[2J\r");

		uartSendString("UART INICIALIZADA CORRECTAMENTE \r\n");
		//UART PRINT VARIABLES de CONFIGURACION
		uint16_t size = sizeof(uint8_t);
		char* baudrate = "115200";
		uartSendString(baudrate);

		CorrectInicialization=true;
	  }
	return CorrectInicialization;
}

void uartSendString(uint8_t * pstring){

	 int length = 0;
	  // Loop through the array, counting the number of bytes before the terminating null character.
	  while (pstring[length] != '\0') {
	    length++;
	  }

	 HAL_UART_Transmit(&huart2, pstring, length, UART_TIMER_MS(50));


}

void uartSendStringSize(uint8_t * pstring, uint16_t size){

	 HAL_UART_Transmit(&huart2, pstring, size, UART_TIMER_MS(50));

}
void uartReceiveStringSize(uint8_t * pstring, uint16_t size){

	HAL_UART_Receive(&huart2, pstring, size, UART_TIMER_MS(50));

}



static void MX_USART2_UART_Init(void)
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
