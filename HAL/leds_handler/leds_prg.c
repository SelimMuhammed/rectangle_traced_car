/*
 * leds_prg.c
 *
 *  Created on: 17 Apr 2024
 *      Author: Selim
 */
#include "../../LIB/bit_math.h"
#include "../../LIB/stdtypes.h"
#include "../../MCAL/dio/dio_int.h"
#include "leds_int.h"

void Leds_voidInit(void)
{
	DIO_u8setPinDirection(LEDS_PORT,LED1_PIN,OUTPUT);
	DIO_u8setPinDirection(LEDS_PORT,LED2_PIN,OUTPUT);
	DIO_u8setPinDirection(LEDS_PORT,LED3_PIN,OUTPUT);
	DIO_u8setPinDirection(LEDS_PORT,LED4_PIN,OUTPUT);
}
