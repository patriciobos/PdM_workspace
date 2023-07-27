/*
 * FSM.c
 *
 *  Created on: Jul 13, 2023
 *      Author: santiagobualo
 */

#include "FSM.h"
#include "API_delay.h"
#include "Led.h"


static debounceState_t FSMPointer = BUTTON_DOWN;
static struct led_data LED;

static bool ButtonPressOcurred = false;


static delay_t timer;

void debounceFSM_init(void){		// debe cargar el estado inicial


	FSMPointer = BUTTON_UP;
	delayInit(&timer,BOUNCE_TIME_DELAY);
	LED_PLACA_init(&LED);

}

void debounceFSM_timer_update(void){
	switch(FSMPointer){
		case BUTTON_FALLING: {

				if (ButtonPressOcurred){  //Vuelvo a ver el estado del boton, si es igual -> avanzo
					FSMPointer = BUTTON_DOWN;
					buttonPressed();

				}else {
					FSMPointer = BUTTON_UP;

				}
				break;
				}
		case BUTTON_RAISING: {
				if (!ButtonPressOcurred){ //Vuelvo a ver el estado del boton, si es igual -> avanzo
					FSMPointer = BUTTON_UP;
					buttonReleased();
						}else {
							FSMPointer = BUTTON_DOWN;

						}
				break;
				}


	}
}




void debounceFSM_button_update(debounceState_t *myFSM){
	switch (*myFSM) {
	case BUTTON_UP: {
		*myFSM = BUTTON_FALLING;
		ButtonPressOcurred = true;
		delayStartTimer(&timer);
		break;
	}

	case BUTTON_DOWN: {
			*myFSM = BUTTON_RAISING;
			ButtonPressOcurred = false;
			delayStartTimer(&timer);
			break;
		}


	}

}
					// transición de estados y actualizar las salidas
void buttonPressed(void){

	LED_TURN_ON(LED);
}
void buttonReleased(void){

	LED_TURN_OFF(LED);
}

GPIO_PinState ReadButton(void){

	return HAL_GPIO_ReadPin(GPIOC,B1_Pin);
}

bool_t readKey(void){

		bool timesUp = delayRead(&timer);
		if (timesUp){
			debounceFSM_timer_update();
		}

return ButtonPressOcurred;

}

//Esto no corresponde que este aca
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	switch(GPIO_Pin){
	case B1_Pin:{

		debounceFSM_button_update(&FSMPointer);
		break;
		}
	default:
		break;
	}


}


