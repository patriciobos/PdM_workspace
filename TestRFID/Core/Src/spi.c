

#include "stdint.h"
#include "stdio.h"
#include "main.h"
#include "stm32f4xx.h"
#include "spi.h"


SPI_HandleTypeDef hspi1; //No puede ser static pq sino la IRQ no la ve

static GPIO_InitTypeDef GPIO_InitStruct = {0};

static SPI_Data_Buffer SPIDataBuffers;

static bool BufferIsUsed = false;
static bool DataReadyToExport = true;

void SPI_Init(void)
{

	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	  if (HAL_SPI_Init(&hspi1) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  //Inicializo el CS
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  /*Configure GPIO pin : GPIO_SPI_CS_Pin */
	  GPIO_InitStruct.Pin = GPIO_SPI_CS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIO_SPI_CS_GPIO_Port, &GPIO_InitStruct);

	  //El CS es activo en bajo
	  HAL_GPIO_WritePin(GPIO_SPI_CS_GPIO_Port, GPIO_SPI_CS_Pin,CS_ON); //Escribo un 1 logico en el GPIO

}

 void SPI_CS_Enable(bool state)
{
	if(state)
	  {
		HAL_GPIO_WritePin(GPIO_SPI_CS_GPIO_Port, GPIO_SPI_CS_Pin,CS_ON); //Escribo un 1 logico en el GPIO
	  }
	  else
	  {
		 HAL_GPIO_WritePin(GPIO_SPI_CS_GPIO_Port, GPIO_SPI_CS_Pin,CS_OFF); //Escribo un 0 logico en el GPIO
	  }
}

int8_t SPI_Transmit_IT(uint8_t *data, uint32_t size)
{

	SPI_CS_Enable(SPI_TRANSMIT_INIT);
	HAL_SPI_Transmit_IT( &hspi1, data, size);

return 0;
}

int8_t SPI_Transmit_Blocking(uint8_t *data, uint32_t size, bool endComunication)
{


	SPI_CS_Enable(SPI_TRANSMIT_INIT);
	HAL_StatusTypeDef halstatus =  HAL_SPI_Transmit(&hspi1, data, size, 0xFF);
	if (endComunication){
	SPI_CS_Enable(SPI_TRANSMIT_END);
	}

return 0;
}


int8_t SPI_Receive_IT(uint8_t *data, uint32_t size)
{

	SPI_CS_Enable(SPI_TRANSMIT_INIT);
	HAL_SPI_Receive_IT(&hspi1, data, size);


	return 0;
}

int8_t SPI_Receive_Blocking(uint8_t *data, uint32_t size,bool endComunication)
{

	SPI_CS_Enable(SPI_TRANSMIT_INIT);
	HAL_SPI_Receive(&hspi1, data, size, 0xFF);
	if (endComunication){
		SPI_CS_Enable(SPI_TRANSMIT_END);
	}

return 0;
}


int8_t SPI_Transmit_Receive_IT (uint8_t *pTxData, uint32_t size){

	SPI_Fill_Tx_Buffer(pTxData,size);
	BufferIsUsed = true;
	SPI_CS_Enable(SPI_TRANSMIT_INIT);
	HAL_SPI_TransmitReceive_IT(&hspi1,SPIDataBuffers.TxBuffer,SPIDataBuffers.RxBuffer,size);
	return 0;

}


int8_t SPI_Transmit_Receive_Blocking (uint8_t *pTxData, uint32_t size){

	SPI_Fill_Tx_Buffer(pTxData,size);
	BufferIsUsed = true;
	SPI_CS_Enable(SPI_TRANSMIT_INIT);
	HAL_SPI_TransmitReceive_IT(&hspi1,SPIDataBuffers.TxBuffer,SPIDataBuffers.RxBuffer,size);
	SPI_Read_Rx_Buffer(pTxData,size);
	return 0;

}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef * hspi)
{
    // TX Done .. Do Something ...
	SPI_CS_Enable(SPI_TRANSMIT_END);

}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef * hspi)
{
    // RX Done .. Do Something ...
	SPI_CS_Enable(SPI_TRANSMIT_END);
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef * hspi)
{
    // TX-RX Done .. Do Something ...
	SPI_CS_Enable(SPI_TRANSMIT_END);
	BufferIsUsed = false;
	DataReadyToExport = true;
}


static void SPI_Fill_Tx_Buffer(uint8_t * data,uint32_t size){

	for (int i=0;i<size;i++){
		SPIDataBuffers.TxBuffer[i] = data[i];
	}

}

bool SPI_Read_Rx_Buffer (uint8_t * Rxdata,uint32_t size){
bool DataExportedSuccesfully = false;
	if (DataReadyToExport && !BufferIsUsed){
		for (int i=0;i<size;i++){
				Rxdata[i] = SPIDataBuffers.RxBuffer[i];
		}
		DataExportedSuccesfully = true;
	}

return DataExportedSuccesfully;
}


void SPI_Abort_Blocking(void){
	HAL_SPI_Abort(&hspi1);
	HAL_SPI_DeInit(&hspi1);
	HAL_SPI_Init(&hspi1);
	SPI_CS_Enable(SPI_TRANSMIT_END);
}

uint8_t RC522_SPI_Transfer(uint8_t data)
{
	uint8_t rx_data;
	HAL_SPI_TransmitReceive(&hspi1,&data,&rx_data,1,100);

	return rx_data;
}

