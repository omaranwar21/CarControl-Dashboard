/*
 * sevo_motor.c
 *
 *  Created on: Aug 25, 2023
 *      Author: Anwar
 */
#include "servo_motor.h"
#include "gpt.h"
#include "Gpio.h"

GPIO_handleTypedef gpio ={
		SERVO_PORT,
		GPIO_MEDIUM_SPEED,
		GPIO_AF,
		GPIO_PUSH_PULL,
		GPIO_NO_PULL_UP_DOWN,
		GPIO_AF01
};

PWM_config SERVO_pwm = {
		TIM2,
		127,
		2499
};

void SERVO_Init(void){
	GPIO_ConfigPin(&gpio, SERVO_PIN);
	SERVO_Activate(0, '-');
	PWM_Init(&SERVO_pwm);
}
void SERVO_Activate(uint8 angle, uint8 direction){

	uint8 orientation = 0;
	switch (direction) {
		case '+':
			orientation = SERVO_ZERO_DEG + (uint8)((float32)1.4  * angle);
			break;
		case '-':
			orientation = SERVO_ZERO_DEG - (uint8)((float32)1.4 * angle);
			break;
		default:
			break;
	}
	PWM_Output(&SERVO_pwm, orientation);
}

