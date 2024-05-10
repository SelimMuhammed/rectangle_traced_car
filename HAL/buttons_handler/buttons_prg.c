/*
 * buttons_prg.c
 *
 *  Created on: 17 Apr 2024
 *      Author: Selim
 */
#include "../../LIB/bit_math.h"
#include "../../LIB/stdtypes.h"
#include "../../MCAL/dio/dio_int.h"
#include "buttons_int.h"

void Buttons_voidInit(void)
{
	DIO_u8setPinDirection(BUTTONS_PORT,PB1_PIN,INPUT);
	DIO_u8setPinValue(BUTTONS_PORT,PB1_PIN,HIGH);
	DIO_u8setPinValue(BUTTONS_PORT,PB2_PIN,HIGH);
}
