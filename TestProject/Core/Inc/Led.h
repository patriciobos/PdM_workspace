/*
 * Led.h
 *
 *  Created on: Jun 24, 2023
 *      Author: santiagobualo
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#define LED_ON 	GPIO_PIN_SET
#define LED_OFF GPIO_PIN_RESET
#define LENGTH_FUNCTION_ARRAY 3

#include "main.h"
//File donde se incluyen todas las definiciones relativas a la operacion de los leds

struct led_data {
	GPIO_TypeDef * 	GPIO_target;
	uint16_t 		Pin_Nro;

};


typedef void (*function)(struct led_data);

//Cada funcion tiene un parpadeo diferente, para poder usar siempre el mismo led

void LED1_function(struct led_data);
void LED2_function(struct led_data);
void LED3_function(struct led_data);

void LED_init(void);


#endif /* INC_LED_H_ */
