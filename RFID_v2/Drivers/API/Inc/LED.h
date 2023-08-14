/*
 * LED.h
 *
 *  Created on: Aug 12, 2023
 *      Author: santiagobualo
 */

#ifndef API_INC_LED_H_
#define API_INC_LED_H_
#include "main.h"

#define TURN_LED_ON GPIO_PIN_SET
#define TURN_LED_OFF GPIO_PIN_RESET

void LED_Init(void);
void LED_Timeout_Blink(void);
void LED_delay(void);
void LED_KeyboardPress(void);
void LED_Card_Blink(void);
void LED_OPEN_DOOR(void);
void LED_Wrong_Pin_Blink(void);
#endif /* API_INC_LED_H_ */
