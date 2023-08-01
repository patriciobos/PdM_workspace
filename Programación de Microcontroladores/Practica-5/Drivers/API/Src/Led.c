/*
 * Led.c
 *
 *  Created on: Jun 24, 2023
 *      Author: santiagobualo
 */


#include "Led.h"
#include "main.h"


//void LED1_init(struct led_data led1){
//	led1.GPIO_target = LED1_GPIO_Port;
//	led1.Pin_Nro = LED1_Pin;
//}
//void LED_TURN_ON(struct led_data led1){
//	HAL_GPIO_WritePin(led1.GPIO_target, led1.Pin_Nro,LED_ON);
//}
//void LED_TURN_OFF(struct led_data led1){
//	HAL_GPIO_WritePin(led1.GPIO_target, led1.Pin_Nro,LED_OFF);
//}
//void LED_TOGGLE(struct led_data led1){
//	HAL_GPIO_TogglePin(led1.GPIO_target, led1.Pin_Nro);
//}
//
//
//void LED2_init(struct led_data led2){
//	led2.GPIO_target = LED2_GPIO_Port;
//	led2.Pin_Nro = LED2_Pin;
//}
////void LED2_TURN_ON(struct led_data led2);
////void LED2_TURN_OFF(struct led_data);
////void LED2_TOGGLE(struct led_data);
//
//
//void LED3_init(struct led_data led3){
//	led3.GPIO_target = LED3_GPIO_Port;
//	led3.Pin_Nro = LED3_Pin;
//}

//void LED3_TURN_ON(struct led_data);
//void LED3_TURN_OFF(struct led_data);
//void LED3_TOGGLE(struct led_data);

void LED_PLACA_init(struct led_data *ledPlaca){

	ledPlaca->GPIO_target = LD2_GPIO_Port;
	ledPlaca->Pin_Nro = LD2_Pin;
}

void LED_TURN_ON(struct led_data led){

	 HAL_GPIO_WritePin(led.GPIO_target, led.Pin_Nro,LED_ON);
}
void LED_TURN_OFF(struct led_data led){
	 HAL_GPIO_WritePin(led.GPIO_target, led.Pin_Nro,LED_OFF);
}
void LED_TOGGLE(struct led_data led){
	 HAL_GPIO_TogglePin(led.GPIO_target, led.Pin_Nro);
}


//void LED_init(struct led_data led1,struct led_data led2,struct led_data led3){
//
//	//ACA CORRESPONDERIA HACER LA INICIALIZACION DE LOS GPIO
//
//	LED1_init(led1);
//	LED2_init(led2);
//	LED3_init(led3);
//
//	LED_TURN_ON(led1);
//	LED_TURN_ON(led2);
//	LED_TURN_ON(led3);
//}

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

