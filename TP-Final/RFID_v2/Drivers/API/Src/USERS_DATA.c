/*
 * USERS_DATA.c
 *
 *  Created on: Aug 11, 2023
 *      Author: santiagobualo
 */

#include "USERS_DATA.h"


//
////E3 CD D8 1B Chapita
uint8_t AdminKey_Card[4]  = {147, 32, 216, 27};
uint8_t AdminPIN[4]  = {1, 2, 3, 4};
////92 94 B7 21 Tarjeta
//uint8_t Key_Card2[4] = {0x92, 0x94, 0xB7, 0x21};

user ArrayOfUsers[MAX_USERS];
uint8_t CurrentMaxUserNumbers=0;
uint8_t WhoIsThis=0;

uint8_t ReadKeyCard[4]={0,0,0,0};
uint8_t ReadPIN[4]={0,0,0,0};


void USERS_DATA_INIT(void){
	for (int i=0;i<4;i++){
		ArrayOfUsers[0].UserKeyCard[i] = AdminKey_Card[i];
		ArrayOfUsers[0].UserPin[i] = AdminPIN[i];
	}
	CurrentMaxUserNumbers++;
}

bool USERS_DATA_VALIDATE_KEYCARD(uint8_t * KeyCardReaded){

	for (uint8_t j=0;j<CurrentMaxUserNumbers;j++){
		if((KeyCardReaded[0]==ArrayOfUsers[j].UserKeyCard[0]) || (KeyCardReaded[1]==ArrayOfUsers[j].UserKeyCard[1]) || (KeyCardReaded[2]==ArrayOfUsers[j].UserKeyCard[2]) || (KeyCardReaded[3]==ArrayOfUsers[j].UserKeyCard[3]) ){
			WhoIsThis = j;
			return true;
		}
	}
return false;
}

void USERS_DATA_COLLECT_FIRST_NUMBER(uint8_t * PIN_FirstNumber){

	ReadPIN[0]=*PIN_FirstNumber;

}

void USERS_DATA_COLLECT_SECOND_NUMBER(uint8_t * PIN_SecondNumber){
	ReadPIN[1]=*PIN_SecondNumber;
}
void USERS_DATA_COLLECT_THIRD_NUMBER(uint8_t * PIN_ThirdNumber){
	ReadPIN[2]=*PIN_ThirdNumber;
}
void USERS_DATA_COLLECT_FOURTH_NUMBER(uint8_t * PIN_FourtNumber){
	ReadPIN[3]=*PIN_FourtNumber;
}

bool USERS_DATA_VALIDATE_PIN(void){

	for (int i=0;i<4;i++){
		if (ReadPIN[i] != ArrayOfUsers[WhoIsThis].UserPin[i]){
			return false;
		}
	}
return true;
}


