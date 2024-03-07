/*
 * FSM.h
 *
 *  Created on: Aug 11, 2023
 *      Author: santiagobualo
 */

#ifndef API_INC_FSM_H_
#define API_INC_FSM_H_

#define FIN_ARCHIVO 0xFF

/*Listado de Eventos*/
typedef enum {
  LECTURA_TARJETA,
  TARJETA_VALIDA,
  TARJETA_INVALIDA,
  LECTURA_NUMERO_TECLADO,
  PIN_VALIDO,
  PIN_INVALIDO,
  TIMEOUT_DEFAULT,
  TIMEOUT_PUERTA_ABIERTA,
  FIN_TABLA
} eventos;

typedef struct state_diagram_edge STATE;


struct state_diagram_edge{

	eventos evento;
	STATE * proximo_estado;
	void(*p_rutina_accion)(void);
};

/*Interprete de la maquina de estados*/
STATE* fsm( STATE *p_tabla_estado , eventos evento_actual);
STATE* FSM_GetInitState(void);

/*Generador de eventos*/

eventos get_event(void);

/*Rutinas de accion*/

void no_operation(void);
void validar_id_tarjeta(void);
void lectura_primer_numero(void);
void lectura_segundo_numero(void);
void lectura_tercer_numero(void);
void lectura_cuarto_numero(void);
void validar_pin_numerico(void);
void abrir_puerta(void);
void cerrar_puerta(void);
void reset_FSM(void);

/*Foward Declarations*/
extern STATE estado_puerta_cerrada[];
extern STATE estado_validando_tarjeta[];
extern STATE estado_ingreso_primer_numero[];
extern STATE estado_ingreso_segundo_numero[];
extern STATE estado_ingreso_tercer_numero[];
extern STATE estado_ingreso_cuarto_numero[];
extern STATE estado_validando_pin[];
extern STATE estado_puerta_abierta[];


#endif /* API_INC_FSM_H_ */
