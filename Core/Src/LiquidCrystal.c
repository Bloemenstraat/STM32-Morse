/*
 * LiquidCrystal.c
 *
 *  Created on: Nov 2, 2022
 *      Author: therapie
 */

#include <LiquidCrystal.h>

#include "stm32f4xx_hal.h"

/*********** Define the LCD PINS ****************/

#define GPIO_Port GPIOA
#define RS_Pin GPIO_PIN_1
#define RW_Pin GPIO_PIN_2
#define EN_Pin GPIO_PIN_3
#define D4_Pin GPIO_PIN_4
#define D5_Pin GPIO_PIN_5
#define D6_Pin GPIO_PIN_6
#define D7_Pin GPIO_PIN_7

/****************** define the timer handler  **************/
#define timer htim1


extern TIM_HandleTypeDef timer;
void delay (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&timer, 0);
	while (__HAL_TIM_GET_COUNTER(&timer) < us);
}

/****************************************************************************************************************************************************************/

void send_to_lcd (char data, int rs)
{
	HAL_GPIO_WritePin(GPIO_Port, RS_Pin, rs);  // rs = 1 for sending data, rs = 0 for command

	/* Write the data to their respective pin */
	HAL_GPIO_WritePin(GPIO_Port, D7_Pin, ((data>>3)&0x01));
	HAL_GPIO_WritePin(GPIO_Port, D6_Pin, ((data>>2)&0x01));
	HAL_GPIO_WritePin(GPIO_Port, D5_Pin, ((data>>1)&0x01));
	HAL_GPIO_WritePin(GPIO_Port, D4_Pin, ((data>>0)&0x01));

	HAL_GPIO_WritePin(GPIO_Port, EN_Pin, 1);
	delay (20);
	HAL_GPIO_WritePin(GPIO_Port, EN_Pin, 0);
	delay (20);
}

void LCD_SendCmd (char cmd)
{
    char datatosend;

    /* send upper nibble first */
    datatosend = ((cmd>>4)&0x0f);
    send_to_lcd(datatosend,0);  // RS = 0 for sending command

    /* send Lower Nibble */
    datatosend = ((cmd)&0x0f);
	send_to_lcd(datatosend, 0);
}

void LCD_SendData (char data)
{
	char datatosend;

	/* Send higher 4-bits */
	datatosend = ((data>>4)&0x0f);
	send_to_lcd(datatosend, 1);  // rs =1 for sending data

	/* Send lower 4-bits */
	datatosend = ((data)&0x0f);
	send_to_lcd(datatosend, 1);
}

void LCD_Clear (void)
{
	LCD_SendCmd(0x01);
	HAL_Delay(2);
}

void LCD_PutCur(int row, int col)
{

    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }
	//row ? col |= 0xC0 : col |= 0x80;

    LCD_SendCmd (col);
}


void LCD_Init (void)
{
	// 4-bit mode initialisation
	HAL_Delay(50);  // wait for >40ms
	LCD_SendCmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	LCD_SendCmd (0x30);
	HAL_Delay(1);  // wait for >100us
	LCD_SendCmd (0x30);
	HAL_Delay(10);
	LCD_SendCmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // Dislay initialisation
	LCD_SendCmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	LCD_SendCmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	LCD_SendCmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	LCD_SendCmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	LCD_SendCmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void LCD_SendString (char *str)
{
	while (*str) LCD_SendData (*str++);
}

