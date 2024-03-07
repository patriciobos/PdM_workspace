/*
 * TIMER.h
 *
 *  Created on: Aug 12, 2023
 *      Author: santiagobualo
 */

#ifndef API_INC_TIMER_H_
#define API_INC_TIMER_H_
#include "main.h"


typedef enum {
  TIMER_TIMEOUT
  //TIMER_DOOR_OPENED
} TIMERS;


void TIM10_Init(void);

void TIMERS_Init(void);
void TIMER_Start(TIMERS myTimer);

uint8_t TIME_GetTimeStatus(TIMERS myTimer);
void TIME_ResetTimeStatus(TIMERS myTimer);
#endif /* API_INC_TIMER_H_ */
