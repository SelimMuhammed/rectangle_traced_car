/*
 * app.h
 *
 *  Created on: 16 Apr 2024
 *      Author: Selim
 */

#ifndef APP_APP_H_
#define APP_APP_H_

typedef enum
{
	BUTTON_PRESSED,
	BUTTON_NOT_PRESSED
}Buttons_States;

typedef enum
{
	RECTANGLE_START,
	RECTANGLE_WIDTH,
	RECTANGLE_LENGTH
}rectangleMovement_Paths;


void SW_PWM_Func(void);
void timer0_voidSetSW_PWM(void);
void extint_voidInit(void);
void Car_voidRectangleSequence(void);
void Emergency_voidStop(void);

#endif /* APP_APP_H_ */
