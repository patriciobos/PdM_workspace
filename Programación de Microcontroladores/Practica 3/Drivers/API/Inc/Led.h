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
#include "API_delay.h"
#include "Led.h"

//File donde se incluyen todas las definiciones relativas a la operacion de los leds

#define LED1_TIMMER 100
#define LED2_TIMMER 200
#define LED3_TIMMER 500

struct led_data {
	GPIO_TypeDef * 	GPIO_target;
	uint16_t 		Pin_Nro;

};




//Cada funcion tiene un parpadeo diferente, para poder usar siempre el mismo led

void LED_init(struct led_data,struct led_data,struct led_data);

void LED1_init(struct led_data);
void LED2_init(struct led_data);
void LED3_init(struct led_data);

void LED_TURN_ON(struct led_data);
void LED_TURN_OFF(struct led_data);
void LED_TOGGLE(struct led_data);

/*
void LED2_TURN_ON(struct led_data);
void LED2_TURN_OFF(struct led_data);
void LED2_TOGGLE(struct led_data);



void LED3_TURN_ON(struct led_data);
void LED3_TURN_OFF(struct led_data);
void LED3_TOGGLE(struct led_data);
*/

#endif /* INC_LED_H_ */
