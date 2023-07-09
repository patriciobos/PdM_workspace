/*
 * API_delay.c
 *
 *  Created on: Jul 6, 2023
 *      Author: santiagobualo
 */

#include "API_delay.h"
#include "main.h"



void delayInit( delay_t * delay, tick_t duration ){ //Setea el tiempo pero no inicializa el tim

	if (delay == NULL || duration <=0){
		Error_Handler();
	}
	delay->running = false;
	delay->duration = duration;

}

bool_t delayRead( delay_t * delay ){
	if (delay == NULL){
			Error_Handler();
		}
	if (delay->running == false){ 				//No estaba inicializado
		delay->startTime = HAL_GetTick();
		delay->running = true;	//Empueza a correr
		return false;
	}else{
		if( HAL_GetTick() - delay->startTime > delay->duration){
			//Termino el tiempo
			delay->running = false;
			return true;
		} else {
			return false;
		}
	}

}

void delayWrite( delay_t * delay, tick_t duration ){
	if (delay == NULL || duration <=0){
			Error_Handler();
		}
	delay->duration = duration;
}
