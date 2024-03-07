/*
 * FSM_Table.h
 *
 *  Created on: Aug 11, 2023
 *      Author: santiagobualo
 */

#ifndef API_INC_FSM_TABLE_H_
#define API_INC_FSM_TABLE_H_

#include "FSM.h"

/*** estado_0 ***/
STATE estado_puerta_cerrada[]= {
{LECTURA_TARJETA,estado_validando_tarjeta,validar_id_tarjeta},
{TIMEOUT_DEFAULT,estado_puerta_cerrada,reset_FSM},
{FIN_TABLA,estado_puerta_cerrada,no_operation}
};
/*** estado_1 ***/
STATE estado_validando_tarjeta[]= {
{TARJETA_VALIDA,estado_ingreso_primer_numero,no_operation},
{TARJETA_INVALIDA,estado_puerta_cerrada,no_operation},
{TIMEOUT_DEFAULT,estado_puerta_cerrada,reset_FSM},
{FIN_TABLA,estado_validando_tarjeta,no_operation}
};
/*** estado_2 ***/
STATE estado_ingreso_primer_numero[]= {
{LECTURA_NUMERO_TECLADO,estado_ingreso_segundo_numero,lectura_primer_numero},
{TIMEOUT_DEFAULT,estado_puerta_cerrada,reset_FSM},
{FIN_TABLA,estado_ingreso_primer_numero,no_operation}
};

/*** estado_3 ***/
STATE estado_ingreso_segundo_numero[]= {
{LECTURA_NUMERO_TECLADO,estado_ingreso_tercer_numero,lectura_segundo_numero},
{TIMEOUT_DEFAULT,estado_puerta_cerrada,reset_FSM},
{FIN_TABLA,estado_ingreso_segundo_numero,no_operation}
};

/*** estado_4 ***/
STATE estado_ingreso_tercer_numero[]= {
{LECTURA_NUMERO_TECLADO,estado_ingreso_cuarto_numero,lectura_tercer_numero},
{TIMEOUT_DEFAULT,estado_puerta_cerrada,reset_FSM},
{FIN_TABLA,estado_ingreso_tercer_numero,no_operation}
};

/*** estado_5 ***/
STATE estado_ingreso_cuarto_numero[]= {
{LECTURA_NUMERO_TECLADO,estado_validando_pin,lectura_cuarto_numero},
{TIMEOUT_DEFAULT,estado_puerta_cerrada,reset_FSM},
{FIN_TABLA,estado_ingreso_cuarto_numero,no_operation}
};


/*** estado_6 ***/
STATE estado_validando_pin[]= {
{PIN_VALIDO,estado_puerta_abierta,abrir_puerta},
{PIN_INVALIDO,estado_ingreso_primer_numero,no_operation},
{TIMEOUT_DEFAULT,estado_puerta_cerrada,reset_FSM},
{FIN_TABLA,estado_validando_pin,no_operation}
};

/*** estado_7 ***/
STATE estado_puerta_abierta[]= {
{TIMEOUT_DEFAULT,estado_puerta_cerrada,cerrar_puerta}, //este es el unico en el que timeout cumple un sentido logico, por eso no anula todos los comportamientos como en los otros
{FIN_TABLA,estado_puerta_abierta,no_operation}//Cambiar despues
};




#endif /* API_INC_FSM_TABLE_H_ */
