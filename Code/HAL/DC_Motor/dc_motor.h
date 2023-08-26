/******************************************************************************
 *
 * Module: DC_Motor
 *
 * File Name: dc_motor.h
 *
 * Description: header file for the DC Motor driver
 *
 * Author: Omar Ahmed Anwar Mansour
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "Std_Types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DC_MOTOR_ROTATION_DIRECTION_PORT 	GPIO_A

#define DC_MOTOR_ROTATION_DIRECTION_PIN1	4
#define DC_MOTOR_ROTATION_DIRECTION_PIN2	5

#define DC_MOTOR_EN_PORT	 				GPIO_A

#define DC_MOTOR_EN_PIN 					6

#define DC_MOTOR_SHIFT_RIGHT_ONE_BIT		1
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum{
	STOP = 0, ClockWise, Anti_ClockWise
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Function responsible for initialize the DC Motor driver.
 */
void DcMotor_Init(void);

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value,
 * and convert it to digital using the ADC driver.
 *
 * Send the required duty cycle to the PWM driver based on the
 * required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

void DcMotor_RotateClockWise(void);

void DcMotor_RotateAnti_ClockWise(void);

void DcMotor_Stop(void);



#endif /* DC_MOTOR_H_ */
