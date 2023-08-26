/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for DC Motor driver
 *
 * Author: Omar Ahmed Anwar Mansour
 *
 *******************************************************************************/
#include "dc_motor.h" 		/* DC Motor Header file */
#include "gpio.h" 			/* To use GPIO driver*/
#include "gpt.h" 			/* PWM HEADER FILE */

GPIO_handleTypedef gpioDC ={
		DC_MOTOR_ROTATION_DIRECTION_PORT,
		GPIO_MEDIUM_SPEED,
		GPIO_OUTPUT,
		GPIO_PUSH_PULL,
		GPIO_NO_PULL_UP_DOWN,
		GPIO_AF00
};

GPIO_handleTypedef gpioEN ={
		DC_MOTOR_EN_PORT,
		GPIO_MEDIUM_SPEED,
		GPIO_AF,
		GPIO_PUSH_PULL,
		GPIO_NO_PULL_UP_DOWN,
		GPIO_AF02
};

PWM_config DC_MOTOR_pwm = {
		TIM3,
		0,
		16000000
};

void DcMotor_Init(void){
	/* Enable pinS OF the direction of the rotation of the motor*/
	GPIO_ConfigPin(&gpioDC, DC_MOTOR_ROTATION_DIRECTION_PIN1);
	GPIO_ConfigPin(&gpioDC, DC_MOTOR_ROTATION_DIRECTION_PIN2);

	/* Enable Configuration with Alternative function (AF02) OF port A */
	GPIO_ConfigPin(&gpioEN, DC_MOTOR_EN_PIN);

	/* Initialize the motor with Stop state*/
	GPIO_WritePinValue(&gpioDC, (0X01 & STOP), DC_MOTOR_ROTATION_DIRECTION_PIN1);
	GPIO_WritePinValue(&gpioDC, ((0X02 & STOP) >> DC_MOTOR_SHIFT_RIGHT_ONE_BIT), DC_MOTOR_ROTATION_DIRECTION_PIN2);


	PWM_Init(&DC_MOTOR_pwm);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	/* ADJUST THE STATE ACCORDING TO THE STATE PASSED*/
	GPIO_WritePinValue(&gpioDC, (0X01 & state), DC_MOTOR_ROTATION_DIRECTION_PIN1);
	GPIO_WritePinValue(&gpioDC, ((0X02 & state) >> DC_MOTOR_SHIFT_RIGHT_ONE_BIT), DC_MOTOR_ROTATION_DIRECTION_PIN2);

	/* ADJUST MOTOR SPEED BY ADJUSTING DUTY CYCLE OF TIMER0 IN FAST PWM MODE */
	uint32 pwmValue = (DC_MOTOR_pwm.ARR_Value-1) * (((float32)speed/100));
	PWM_Output(&DC_MOTOR_pwm, pwmValue);

}

void DcMotor_RotateClockWise(void){
	DcMotor_Rotate(ClockWise, 100);
}

void DcMotor_RotateAnti_ClockWise(void){
	DcMotor_Rotate(Anti_ClockWise, 100);
}

void DcMotor_Stop(void){
	DcMotor_Rotate(STOP, 0);
}

