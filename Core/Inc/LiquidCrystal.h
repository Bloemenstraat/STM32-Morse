/*
 * LiquidCrystal.h
 *
 *  Created on: Nov 2, 2022
 *      Author: therapie
 */

#ifndef INC_LIQUIDCRYSTAL_H_
#define INC_LIQUIDCRYSTAL_H_


void LCD_Init (void);   // initialize lcd

void LCD_SendCmd (char cmd);  // send command to the lcd

void LCD_SendData (char data);  // send data to the lcd

void LCD_SendString (char *str);  // send string to the lcd

void LCD_PutCur(int row, int col);  // put cursor at the entered position row (0 or 1), col (0-15);

void LCD_Clear (void);

#endif /* INC_LIQUIDCRYSTAL_H_ */
