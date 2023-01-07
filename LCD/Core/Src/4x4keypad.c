/*
 * 4x4keypad.c
 *
 *  Created on: Nov 7, 2022
 *      Author: admin
 */


#include "4x4keypad.h"
#include "main.h"
#include "LCD.h"

const char KEY[16]={
		'7','8','9','/',
		'4','5','6','x',
		'1','2','3','-',
		'#','0','=','+'
};
char operator;

unsigned char check_col(unsigned char row){
	if (!(HAL_GPIO_ReadPin (C0_GPIO_Port, C0_Pin)))   return KEY[row+0];// if the Col 0 is low

	if (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)))   return KEY[row+1];// if the Col 1 is low

	if (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)))   return KEY[row+2];// if the Col 2 is low

	if (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)))   return KEY[row+3];// if the Col 3 is low

	return 0xFF;

}
unsigned char KEYPAD_Read(void){
	unsigned char key;
	HAL_GPIO_WritePin(GPIOB, R0_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, R1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, R2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, R3_Pin,GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOB, R0_Pin, RESET);
	key = check_col(0);
	HAL_GPIO_WritePin(GPIOB, R0_Pin, SET);
	if(key != 0xFF)	return key;

	HAL_GPIO_WritePin(GPIOB, R1_Pin, RESET);
	key = check_col(4);
	HAL_GPIO_WritePin(GPIOB, R1_Pin, SET);
	if(key != 0xFF)	return key;

	HAL_GPIO_WritePin(GPIOB, R2_Pin, RESET);
	key = check_col(8);
	HAL_GPIO_WritePin(GPIOB, R2_Pin, SET);
	if(key != 0xFF)	return key;

	HAL_GPIO_WritePin(GPIOB, R3_Pin, RESET);
	key = check_col(12);
	HAL_GPIO_WritePin(GPIOB, R3_Pin, SET);
	if(key != 0xFF)	return key;

	return 0xFF;
}

void Key_Read(){
	char text = KEYPAD_Read();
	if(text != 0xFF)
	{
		text = KEYPAD_Read();
		if(text != 0xFF)
		{
			LCD_add_To_String(text);
//			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		}

	}
}
