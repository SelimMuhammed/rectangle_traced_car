/*
 * dc_motor_prg.c
 *
 *  Created on: 16 Apr 2024
 *      Author: Selim
 */
#include "../../LIB/bit_math.h"
#include "../../LIB/stdtypes.h"
#include "../../MCAL/dio/dio_int.h"
#include "dc_motor_int.h"


void Motor_voidInit(void)
{
	DIO_u8setPinDirection(MOTORS_PORT,M1_PIN,OUTPUT);
	DIO_u8setPinDirection(MOTORS_PORT,M2_PIN,OUTPUT);
	DIO_u8setPinDirection(MOTORS_PORT,M3_PIN,OUTPUT);
	DIO_u8setPinDirection(MOTORS_PORT,M4_PIN,OUTPUT);
	DIO_u8setPinDirection(MOTORS_PORT,M_EN1_PIN,OUTPUT);
	DIO_u8setPinDirection(MOTORS_PORT,M_EN2_PIN,OUTPUT);
}
void Motor_voidFoward(void)
{
	DIO_u8setPinValue(MOTORS_PORT,M1_PIN,HIGH);
	DIO_u8setPinValue(MOTORS_PORT,M2_PIN,LOW);
	DIO_u8setPinValue(MOTORS_PORT,M3_PIN,HIGH);
	DIO_u8setPinValue(MOTORS_PORT,M4_PIN,LOW);
}
void Motor_voidBackward(void)
{
	DIO_u8setPinValue(MOTORS_PORT,M1_PIN,LOW);
	DIO_u8setPinValue(MOTORS_PORT,M2_PIN,HIGH);
	DIO_u8setPinValue(MOTORS_PORT,M3_PIN,LOW);
	DIO_u8setPinValue(MOTORS_PORT,M4_PIN,HIGH);
}
void Motor_voidLeftDir(void)
{
	DIO_u8setPinValue(MOTORS_PORT,M1_PIN,HIGH);
	DIO_u8setPinValue(MOTORS_PORT,M2_PIN,LOW);
	DIO_u8setPinValue(MOTORS_PORT,M3_PIN,LOW);
	DIO_u8setPinValue(MOTORS_PORT,M4_PIN,HIGH);
}
void Motor_voidRigthDir(void)
{
	DIO_u8setPinValue(MOTORS_PORT,M1_PIN,LOW);
	DIO_u8setPinValue(MOTORS_PORT,M2_PIN,HIGH);
	DIO_u8setPinValue(MOTORS_PORT,M3_PIN,HIGH);
	DIO_u8setPinValue(MOTORS_PORT,M4_PIN,LOW);
}
void Motor_voidStop(void)
{
	DIO_u8setPinValue(MOTORS_PORT,M1_PIN,LOW);
	DIO_u8setPinValue(MOTORS_PORT,M2_PIN,LOW);
	DIO_u8setPinValue(MOTORS_PORT,M3_PIN,LOW);
	DIO_u8setPinValue(MOTORS_PORT,M4_PIN,LOW);
}
