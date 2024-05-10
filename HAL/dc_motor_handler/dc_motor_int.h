/*
 * dc_motor_int.h
 *
 *  Created on: 16 Apr 2024
 *      Author: Selim
 */

#ifndef HAL_DC_MOTOR_HANDLER_DC_MOTOR_INT_H_
#define HAL_DC_MOTOR_HANDLER_DC_MOTOR_INT_H_

#define  MOTORS_PORT    PORT_C

#define  M1_PIN      PIN_0
#define  M2_PIN      PIN_1
#define  M3_PIN      PIN_2
#define  M4_PIN      PIN_3

#define M_EN1_PIN    PIN_4
#define M_EN2_PIN    PIN_5

void Motor_voidInit(void);
void Motor_voidFoward(void);
void Motor_voidBackward(void);
void Motor_voidLeftDir(void);
void Motor_voidRigthDir(void);
void Motor_voidStop(void);



#endif /* HAL_DC_MOTOR_HANDLER_DC_MOTOR_INT_H_ */
