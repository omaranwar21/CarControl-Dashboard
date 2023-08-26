/*
 * servo_motor.h
 *
 *  Created on: Aug 25, 2023
 *      Author: Anwar
 */

#ifndef SERVO_MOTOR_SERVO_MOTOR_H_
#define SERVO_MOTOR_SERVO_MOTOR_H_

#define SERVO_PORT			GPIO_A
#define SERVO_PIN			0
#define SERVO_TIMER			TIM2
#define SERVO_ZERO_DEG		187

#include "Std_Types.h"



void SERVO_Init(void);
void SERVO_Activate(uint8 angle, boolean direction);


#endif /* SERVO_MOTOR_SERVO_MOTOR_H_ */
