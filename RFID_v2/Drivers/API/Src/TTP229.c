/*
 * TTP229.c
 *
 *  Created on: Aug 10, 2023
 *      Author: santiagobualo
 */


#include "TTP229.h"

void KEYBOAD_Init(void){

	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	 /*Configure GPIO pins : RFC_RST_GPIO_Pin KEYBOARD_CLK_Pin */
	  GPIO_InitStruct.Pin = RFC_RST_GPIO_Pin|KEYBOARD_CLK_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//	  /*Configure GPIO pin : KEYBOARD_DATA_Pin */
//	  GPIO_InitStruct.Pin = KEYBOARD_DATA_Pin;
//	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//	  GPIO_InitStruct.Pull = GPIO_MODE_IT_RISING_FALLING;
//	  HAL_GPIO_Init(KEYBOARD_DATA_GPIO_Port, &GPIO_InitStruct);
//
	  /*Configure GPIO pin : KEYBOARD_DATA_Pin */
	  GPIO_InitStruct.Pin = KEYBOARD_DATA_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(KEYBOARD_DATA_GPIO_Port, &GPIO_InitStruct);

	  KEYBOARD_Write_CLK(HIGH);

}


uint8_t KEYBOARD_ReadData(void)
{
	uint8_t Count;
	uint8_t Key_State = 0;

/* Pulse the clock pin 16 times (one for each key of the keypad)
and read the state of the data pin on each pulse */
	for(Count = 1; Count <= 16; Count++)
	{
		KEYBOARD_Write_CLK(LOW);
	/* If the data pin is low (active low mode) then store the
	current key number */
		for (int i=0;i<25;i++){
		if (!KEYBOARD_Read_DATA()){
			Key_State = Count;
		}
		}
		KEYBOARD_Write_CLK(HIGH);
	}
	HAL_Delay(100);
	return Key_State;
}


void KEYBOARD_Write_CLK(GPIO_PinState value){

	HAL_GPIO_WritePin(KEYBOARD_CLK_GPIO_Port,KEYBOARD_CLK_Pin,value);

}

GPIO_PinState KEYBOARD_Read_DATA(){

	GPIO_PinState value = HAL_GPIO_ReadPin(KEYBOARD_DATA_GPIO_Port,KEYBOARD_DATA_Pin);
	return value;
}
