/*
 * Led.c
 *
 *  Created on: Jun 24, 2023
 *      Author: santiagobualo
 */


#include "Led.h"




void LED1_function(struct led_data led){

	 HAL_GPIO_WritePin(led.GPIO_target, led.Pin_Nro,LED_ON);
	 HAL_Delay(300);
	 HAL_GPIO_WritePin(led.GPIO_target, led.Pin_Nro,LED_OFF);
	 HAL_Delay(300);
	 HAL_GPIO_WritePin(led.GPIO_target, led.Pin_Nro,LED_ON);
	 HAL_Delay(300);
	 HAL_GPIO_WritePin(led.GPIO_target, led.Pin_Nro,LED_OFF);
}

void LED2_function(struct led_data led){

	 HAL_GPIO_WritePin(led.GPIO_target, led.Pin_Nro,LED_ON);
	 HAL_Delay(1000);
	 HAL_GPIO_WritePin(led.GPIO_target, led.Pin_Nro,LED_OFF);
}


void LED3_function(struct led_data led){

	for (int i=0;i<5;i++){
	 HAL_GPIO_WritePin(led.GPIO_target, led.Pin_Nro,LED_ON);
	 HAL_Delay(100);
	 HAL_GPIO_WritePin(led.GPIO_target, led.Pin_Nro,LED_OFF);
	 HAL_Delay(100);
	 HAL_GPIO_WritePin(led.GPIO_target, led.Pin_Nro,LED_ON);
	 HAL_Delay(100);
	 HAL_GPIO_WritePin(led.GPIO_target, led.Pin_Nro,LED_OFF);
	}
}

