/* * main.c
 *
 *  Created on: 17 Dec 2023
 *      Author: Selim
 */
#include "../LIB/bit_math.h"
#include "../LIB/stdtypes.h"
#include "../HAL/dc_motor_handler/dc_motor_int.h"
#include "../HAL/buttons_handler/buttons_int.h"
#include "../HAL/leds_handler/leds_int.h"
#include "../MCAL/dio/dio_int.h"
#include "../MCAL/extint/extint_int.h"
#include "../MCAL/timer/timer_reg.h"
#include "../MCAL/timer/timer_int.h"
#include "app.h"

// States vales (used in Switch case in main)
#define INIT_VALUE               (u8)   0
#define PROCESS_VALUE_START      (u8)   1
#define PROCESS_VALUE_FOR_LEN    (u8)   2
#define PROCESS_VALUE_RIGHT      (u8)   3
#define PROCESS_VALUE_FOR_WID    (u8)   4
#define PROCESS_VALUE_STOP       (u8)   5

// Timer 1 delay values
#define DELAY_1_SEC           (u8)   15
#define DELAY_4_SECS          (u8)   61
#define DELAY_4_SECS_HALF     (u8)   70
#define DELAY_5_SECS          (u8)   79
#define DELAY_5_SECS_HALF     (u8)   88
#define DELAY_8_SECS          (u8)   123
#define DELAY_8_SECS_HALF     (u8)   132
#define DELAY_9_SECS          (u8)   141

// Timer 2 PWM Signal parameters
#define PWM_PERIODIC_TIME     (u8)   20
#define PWM_DUTY_30_PER       (u8)   6
#define PWM_DUTY_50_PER       (u8)   10

u8 global_u8PB1_StateCounter = INIT_VALUE;
u8 global_u8RectanglePathState = RECTANGLE_START;

void Emergency_voidStop(void)
{
	Motor_voidStop();
	global_u8PB1_StateCounter = INIT_VALUE;
	global_u8RectanglePathState = RECTANGLE_START;
	Timer_DeInit(TIMER_1);
}

void SW_PWM(void)
{
	static u8 Local_u8OVFCounter=0;

	Local_u8OVFCounter++;
	switch(global_u8RectanglePathState)
	{
	case RECTANGLE_WIDTH:
		if(Local_u8OVFCounter == PWM_DUTY_30_PER)
		{
			DIO_u8setPinValue(MOTORS_PORT,M_EN1_PIN,LOW);
			DIO_u8setPinValue(MOTORS_PORT,M_EN2_PIN,LOW);
		}
		else if(Local_u8OVFCounter == PWM_PERIODIC_TIME)
		{
			DIO_u8setPinValue(MOTORS_PORT,M_EN1_PIN,HIGH);
			DIO_u8setPinValue(MOTORS_PORT,M_EN2_PIN,HIGH);
			Local_u8OVFCounter=0;
		}
		break;

	case RECTANGLE_LENGTH:
		if(Local_u8OVFCounter == PWM_DUTY_50_PER)
		{
			DIO_u8setPinValue(MOTORS_PORT,M_EN1_PIN,LOW);
			DIO_u8setPinValue(MOTORS_PORT,M_EN2_PIN,LOW);
		}
		else if(Local_u8OVFCounter == PWM_PERIODIC_TIME)
		{
			DIO_u8setPinValue(MOTORS_PORT,M_EN1_PIN,HIGH);
			DIO_u8setPinValue(MOTORS_PORT,M_EN2_PIN,HIGH);
			Local_u8OVFCounter=0;
		}
		break;
	default:
		DIO_u8setPinValue(MOTORS_PORT,M_EN1_PIN,HIGH);
		DIO_u8setPinValue(MOTORS_PORT,M_EN2_PIN,HIGH);
		break;
	}
}

void DelaySec(void)
{
	static u8 Local_u8OVFCounter=0;

	Local_u8OVFCounter++;

	if(Local_u8OVFCounter == DELAY_1_SEC)
	{
		global_u8PB1_StateCounter = PROCESS_VALUE_FOR_LEN;
		global_u8RectanglePathState = RECTANGLE_LENGTH;
	}
	else if(Local_u8OVFCounter == DELAY_4_SECS)
	{
		global_u8PB1_StateCounter = PROCESS_VALUE_STOP;
	}
	else if(Local_u8OVFCounter == DELAY_4_SECS_HALF)
	{
		global_u8PB1_StateCounter = PROCESS_VALUE_RIGHT;
	}
	else if(Local_u8OVFCounter == DELAY_5_SECS)
	{
		global_u8PB1_StateCounter = PROCESS_VALUE_STOP;
	}
	else if(Local_u8OVFCounter == DELAY_5_SECS_HALF)
	{
		global_u8PB1_StateCounter = PROCESS_VALUE_FOR_WID;
		global_u8RectanglePathState = RECTANGLE_WIDTH;
	}
	else if(Local_u8OVFCounter == DELAY_8_SECS)
	{
		global_u8PB1_StateCounter = PROCESS_VALUE_STOP;
	}
	else if(Local_u8OVFCounter == DELAY_8_SECS_HALF)
	{
		global_u8PB1_StateCounter = PROCESS_VALUE_RIGHT;
	}
	else if(Local_u8OVFCounter == DELAY_9_SECS)
	{
		global_u8PB1_StateCounter = PROCESS_VALUE_STOP;
		Local_u8OVFCounter=0;
	}



}

void main (void)
{
	Leds_voidInit();
	Motor_voidInit();
	Buttons_voidInit();

	timer_config_type SW_PWM_timer2;
	SW_PWM_timer2.timer = TIMER_2;
	SW_PWM_timer2.operated_mode = NORMAL_MODE;
	SW_PWM_timer2.T2_used_freq = TIMER_2_PRE_SCALER_e_8;
	Timer_init(&SW_PWM_timer2);
	Set_CallBack_TIMER_2_OVF_INT(SW_PWM);

	timer_config_type delay_timer1;
	delay_timer1.timer = TIMER_1;
	delay_timer1.operated_mode = NORMAL_MODE;
	delay_timer1.T0_T1_used_freq = TIMER_0_1_PRE_SCALER_e_8;
	delay_timer1.initial_value = 48576; // Preload value to get 1 Sec
	Set_CallBack_TIMER_1_OVF_INT(DelaySec);

	//External interrupt as Emergency stop Button
	EXTINT_u8Enable(INT_1);
	EXTINT_u8SenseCtrl(INT_1,INT1_RISE_EDGE_EN);
	Set_CallBack_EXTINT_1(Emergency_voidStop);

	Global_VidINTEnable();

	while(1)
	{
		u8 local_u8PB1_State = BUTTON_NOT_PRESSED;

		// reading Push Button 1 to start the program
		DIO_u8getPinValue(BUTTONS_PORT,PB1_PIN,&local_u8PB1_State);

		if(local_u8PB1_State == BUTTON_PRESSED)
		{
			global_u8PB1_StateCounter = PROCESS_VALUE_START;
			Timer_init(&delay_timer1);
			global_u8RectanglePathState = RECTANGLE_START;
		}

		switch(global_u8PB1_StateCounter)
		{
		case INIT_VALUE:

			Motor_voidStop();
			DIO_u8setPinValue(LEDS_PORT, LED3_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED2_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED4_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED1_PIN, LOW);
			break;

		case PROCESS_VALUE_START:

			Motor_voidFoward();
			DIO_u8setPinValue(LEDS_PORT, LED3_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED2_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED4_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED1_PIN, LOW);
			break;

		case PROCESS_VALUE_FOR_LEN:

			Motor_voidFoward();
			DIO_u8setPinValue(LEDS_PORT, LED3_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED2_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED4_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED1_PIN, HIGH);
			break;

		case PROCESS_VALUE_RIGHT:

			Motor_voidRigthDir();
			DIO_u8setPinValue(LEDS_PORT, LED1_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED2_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED3_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED4_PIN, HIGH);
			break;

		case PROCESS_VALUE_STOP:

			Motor_voidStop();
			DIO_u8setPinValue(LEDS_PORT, LED1_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED2_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED4_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED3_PIN, HIGH);
			break;

		case PROCESS_VALUE_FOR_WID:

			Motor_voidFoward();
			DIO_u8setPinValue(LEDS_PORT, LED1_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED3_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED4_PIN, LOW);
			DIO_u8setPinValue(LEDS_PORT, LED2_PIN, HIGH);
		}
	}
}


