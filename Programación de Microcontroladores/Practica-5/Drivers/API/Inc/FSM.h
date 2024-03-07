/*
 * FSM.h
 *
 *  Created on: Jul 13, 2023
 *      Author: santiagobualo
 */

#ifndef API_INC_FSM_H_
#define API_INC_FSM_H_

#include "main.h"
#include "API_delay.h"
#define BOUNCE_TIME_DELAY 40
/* USER CODE BEGIN Private defines */

typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounceState_t;


void debounceFSM_init(void);		// debe cargar el estado inicial
void debounceFSM_button_update(debounceState_t *myFSM);	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas
void buttonPressed(void);			// debe invertir el estado del LED1
void buttonReleased(void);		// debe invertir el estado del LED3
bool_t readKey(void);

GPIO_PinState ReadButton(void);
void debounceFSM_timer_update(void);

#endif /* API_INC_FSM_H_ */
