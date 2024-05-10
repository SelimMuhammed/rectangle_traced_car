/*
 * buttons_int.h
 *
 *  Created on: 17 Apr 2024
 *      Author: Selim
 */

#ifndef HAL_BUTTONS_HANDLER_BUTTONS_INT_H_
#define HAL_BUTTONS_HANDLER_BUTTONS_INT_H_

#define  BUTTONS_PORT   PORT_D
#define  PB1_PIN     PIN_1
#define  PB2_PIN     PIN_3 //interrupt Emergency

void Buttons_voidInit(void);
#endif /* HAL_BUTTONS_HANDLER_BUTTONS_INT_H_ */
