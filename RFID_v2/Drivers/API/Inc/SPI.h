/*
 * SPI.h
 *
 *  Created on: Aug 10, 2023
 *      Author: santiagobualo
 */

#ifndef API_INC_SPI_H_
#define API_INC_SPI_H_

#include "main.h"
#include <stdbool.h>
#define SPI_TIMEOUT 100

#define SPI_ENABLE_CS 	GPIO_PIN_RESET
#define SPI_DISABLE_CS 	GPIO_PIN_SET

#define SPI_END_COM 		true
#define SPI_CONTINUE_COM 	false

typedef bool bool_t;

void SPI_Init(void);
uint8_t SPI_TransmitReceiveBlocking(uint8_t data,uint8_t size,bool_t endOfCom);

#endif /* API_INC_SPI_H_ */
