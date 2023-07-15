/*
 * API_Delay.h
 *
 *  Created on: Jul 6, 2023
 *      Author: santiagobualo
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>



typedef uint32_t tick_t; // Qué biblioteca se debe incluir para que esto compile?
typedef bool bool_t;	  // Qué biblioteca se debe incluir para que esto compile?
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );
void delayStartTimer (delay_t * delay );

#endif /* API_INC_API_DELAY_H_ */
