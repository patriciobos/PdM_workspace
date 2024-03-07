/*
 * TTP229.h
 *
 *  Created on: Aug 10, 2023
 *      Author: santiagobualo
 */

#ifndef API_INC_TTP229_H_
#define API_INC_TTP229_H_

#include "main.h"

#define LOW 	GPIO_PIN_RESET	//lo pone en 0 V
#define HIGH 	GPIO_PIN_SET

#define MAX_RETRY_READ 25

void KEYBOAD_Init(void);
uint8_t KEYBOARD_ReadData(void);


#endif /* API_INC_TTP229_H_ */
