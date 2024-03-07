/*
 * FSM.c
 *
 *  Created on: Aug 11, 2023
 *      Author: santiagobualo
 */

#include "FSM.h"
#include "FSM_Table.h"
#include "RC522.h"
#include "TTP229.h"
#include "USERS_DATA.h"
#include "TIMER.h"
#include "LED.h"

static int tarjetavalida=0;
static uint8_t NumeroPulsado = -1;
static int pinValido = 0;

STATE* FSM_GetInitState(void){

	STATE* initialState = estado_puerta_cerrada;
	return initialState; //El sistema comienza con la puerta cerrada

}

/*Interprete de la maquina de estados*/
STATE* fsm( STATE *p_tabla_estado , eventos evento_actual){		// Puntero al estado actual , Evento recibido
	// 1-Recorremos las tabla de estado ( Ej estado_0) hasta encontrar el arco que contenga el evento actual
	while (p_tabla_estado -> evento != evento_actual && p_tabla_estado -> evento !=FIN_TABLA) ++p_tabla_estado;

	(*p_tabla_estado -> p_rutina_accion)(); /*2- Ejecuta Rutina de accion corresondiente*/

	p_tabla_estado=p_tabla_estado -> proximo_estado; /*3-Encuentro próximo estado*/

	return(p_tabla_estado);
}

eventos get_event(void){

	if(get_RFID_event_ocurrence()){
		return LECTURA_TARJETA;
	}

	if (NumeroPulsado==0){
	uint8_t pulsedNumber = KEYBOARD_ReadData();
	if (pulsedNumber>0){
			LED_KeyboardPress();
			HAL_Delay(500);
			NumeroPulsado = pulsedNumber;
			return LECTURA_NUMERO_TECLADO;
		}
	}


	if(tarjetavalida >0){
		LED_Card_Blink();
		tarjetavalida = 0;
		return TARJETA_VALIDA;
	}
	if(tarjetavalida <0){
			tarjetavalida = 0;
			return TARJETA_INVALIDA;
	}
	if(pinValido >0){
		pinValido = 0;
			return PIN_VALIDO;
		}
	if(pinValido <0){
		LED_Wrong_Pin_Blink();
		pinValido = 0;
			return PIN_INVALIDO;
		}

	if (TIME_GetTimeStatus(TIMER_TIMEOUT)){
		TIME_ResetTimeStatus(TIMER_TIMEOUT);
		return TIMEOUT_DEFAULT;
	}
	return FIN_TABLA;

}

//Rutinas de accion

//No hacer nada
void no_operation(void){

}


void validar_id_tarjeta(void){
	TIMER_Start(TIMER_TIMEOUT);
	if (USERS_DATA_VALIDATE_KEYCARD(GetKeyRead())){
		tarjetavalida = 1;
		NumeroPulsado=0; //permito eventos de teclado
	}
	else {
		tarjetavalida = -1;
	}
}

void lectura_primer_numero(void){
	TIMER_Start(TIMER_TIMEOUT);
	USERS_DATA_COLLECT_FIRST_NUMBER( &NumeroPulsado);
	NumeroPulsado=0;
	LED_KeyboardPress();
}
void lectura_segundo_numero(void){
	TIMER_Start(TIMER_TIMEOUT);
	USERS_DATA_COLLECT_SECOND_NUMBER( &NumeroPulsado);
	NumeroPulsado=0;
	LED_KeyboardPress();

}
void lectura_tercer_numero(void){
	TIMER_Start(TIMER_TIMEOUT);
	USERS_DATA_COLLECT_THIRD_NUMBER( &NumeroPulsado);
	NumeroPulsado=0;
	LED_KeyboardPress();
}
void lectura_cuarto_numero(void){
	TIMER_Start(TIMER_TIMEOUT);
	USERS_DATA_COLLECT_FOURTH_NUMBER( &NumeroPulsado);
	NumeroPulsado=0;
	LED_KeyboardPress();
	if ( USERS_DATA_VALIDATE_PIN()){
		pinValido=1;
	}else {
		pinValido = -1;
	}
}
void validar_pin_numerico(void){

}
void abrir_puerta(void){
	LED_OPEN_DOOR();
	NumeroPulsado = -1;

}
void cerrar_puerta(void){

	LED_OPEN_DOOR();
}
void reset_FSM(void){
tarjetavalida=0;
NumeroPulsado = -1;
pinValido = 0;
}
