/*
 * spi.h
 *
 *  Created on: Jan 16, 2022
 *      Author: hussam
 */

#ifndef SPI_H_
#define SPI_H_
#include "stdint.h"
#include "main.h"
#include <stdbool.h>



#define CS_ON 	GPIO_PIN_SET
#define CS_OFF 	GPIO_PIN_RESET

#define MAX_SIZE_TX_RX_SPI_BUFFER 32

#define SPI_TRANSMIT_INIT 	false
#define SPI_TRANSMIT_END 	true


typedef struct  {
	uint8_t TxBuffer[MAX_SIZE_TX_RX_SPI_BUFFER];
	uint8_t RxBuffer[MAX_SIZE_TX_RX_SPI_BUFFER];
}SPI_Data_Buffer;

//Funciones publicas
void SPI_Init(void);
int8_t SPI_Transmit_IT(uint8_t *data, uint32_t size);
int8_t SPI_Receive_IT(uint8_t *data, uint32_t size);
int8_t SPI_Transmit_Receive_IT(uint8_t *data, uint32_t size);

int8_t SPI_Transmit_Blocking(uint8_t *data, uint32_t size, bool endComunication);
int8_t SPI_Receive_Blocking(uint8_t *data, uint32_t size,bool endComunication);
int8_t SPI_Transmit_Receive_Blocking (uint8_t *pTxData, uint32_t size);
void SPI_Abort_Blocking(void);

bool SPI_Read_Rx_Buffer (uint8_t * Rxdata,uint32_t size);
uint8_t RC522_SPI_Transfer(uint8_t data);

//Funciones privadas
void SPI_CS_Enable(bool state);
static void SPI_Fill_Tx_Buffer(uint8_t * data,uint32_t size);



#endif /* SPI_H_ */
