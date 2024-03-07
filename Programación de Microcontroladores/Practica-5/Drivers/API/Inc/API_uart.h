/*
 * API_uart.h
 *
 *  Created on: Jul 27, 2023
 *      Author: santiagobualo
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"




#define UART_TIMER_MS(ms) ((uint32_t)((ms) * (SystemCoreClock / 1000)))
#define UART_BAUDRATE 115200

bool uartInit(void);
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);


#endif /* API_INC_API_UART_H_ */
