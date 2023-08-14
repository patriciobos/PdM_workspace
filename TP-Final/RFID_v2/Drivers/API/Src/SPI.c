
#include "SPI.h"


SPI_HandleTypeDef hspi1;
bool_t SPI_is_running=0;



/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
void SPI_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI_SDA_GPIO_GPIO_Port, SPI_SDA_GPIO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RFC_RST_GPIO_GPIO_Port, RFC_RST_GPIO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : SPI_SDA_GPIO_Pin */
  GPIO_InitStruct.Pin = SPI_SDA_GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI_SDA_GPIO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : RFC_RST_GPIO_Pin */
  GPIO_InitStruct.Pin = RFC_RST_GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RFC_RST_GPIO_GPIO_Port, &GPIO_InitStruct);


  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}


uint8_t SPI_TransmitReceiveBlocking(uint8_t data,uint8_t size,bool_t endOfCom)
{
	uint8_t rx_data;
	//Selecciono el SS
	if (!SPI_is_running){
		HAL_GPIO_WritePin(SPI_SDA_GPIO_GPIO_Port,SPI_SDA_GPIO_Pin,SPI_ENABLE_CS);
		SPI_is_running = true;
	}
	HAL_SPI_TransmitReceive(&hspi1,&data,&rx_data,1,SPI_TIMEOUT);

	if (endOfCom) {
		HAL_GPIO_WritePin(SPI_SDA_GPIO_GPIO_Port,SPI_SDA_GPIO_Pin,SPI_DISABLE_CS);
		SPI_is_running = false;
	}
	return rx_data;
}
