/*
 * USERS_DATA.h
 *
 *  Created on: Aug 11, 2023
 *      Author: santiagobualo
 */

#ifndef API_INC_USERS_DATA_H_
#define API_INC_USERS_DATA_H_
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t KeyCard[4];
typedef uint8_t PIN[4];

#define MAX_USERS 10


typedef struct {
	KeyCard UserKeyCard;
	PIN UserPin;
}user;

void USERS_DATA_INIT(void);
bool USERS_DATA_VALIDATE_KEYCARD(uint8_t * KeyCardReaded);
bool USERS_DATA_VALIDATE_PIN(void);

void USERS_DATA_COLLECT_FIRST_NUMBER(uint8_t * PIN_FirstNumber);
void USERS_DATA_COLLECT_SECOND_NUMBER(uint8_t * PIN_SecondNumber);
void USERS_DATA_COLLECT_THIRD_NUMBER(uint8_t * PIN_ThirdNumber);
void USERS_DATA_COLLECT_FOURTH_NUMBER(uint8_t * PIN_FourtNumber);

#endif /* API_INC_USERS_DATA_H_ */
