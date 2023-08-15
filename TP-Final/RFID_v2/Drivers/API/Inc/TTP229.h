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


void KEYBOAD_Init(void);
uint8_t KEYBOARD_ReadData(void);

void KEYBOARD_Write_CLK(GPIO_PinState value);
GPIO_PinState KEYBOARD_Read_DATA();


#endif /* API_INC_TTP229_H_ */
