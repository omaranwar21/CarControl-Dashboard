/*
 * ====================================================================================================================================
 *  Project		: Vehicle Door Handle Control Unit
 * 	File Name	: Gpio.h
 *	Team 		: 20
 *	Members		: Abdelrahman Yasser - Omar Ahmed Anwar - Mo'men Mohamed - Neveen Mohamed
 *  ===================================================================================================================================
 */

#ifndef GPIO_H
#define GPIO_H

/*---------------------- Includes ----------------------*/
#include "Gpio_Private.h"
/*------------------------------------------------------*/

/*--------------------- Definitions -------------------- */
#define GPIO_A 'A'
#define GPIO_B 'B'
#define GPIO_C 'C'
#define GPIO_D 'D'
#define GPIO_E 'E'

#define GPIO_DATA_FALLING	1
#define GPIO_DATA_RISING	0
/*------------------------------------------------------*/

/*----------------- Defined types ----------------------*/
/*PinMode*/
typedef enum{
	GPIO_INPUT, GPIO_OUTPUT, GPIO_AF, GPIO_ANALOG
}GPIO_PinMode;

/*DefaultState*/
typedef enum{
	GPIO_PUSH_PULL, GPIO_OPEN_DRAIN
}GPIO_DefaultState;

/*Data*/
typedef enum{
	LOW, HIGH
}GPIO_Data;

/*Flag*/
typedef enum{
	NOK, OK
}GPIO_WriteDataFlag;

/*Pull up, Pull down*/
typedef enum{
	GPIO_NO_PULL_UP_DOWN, GPIO_PULL_UP,
	GPIO_PULL_DOWN, GPIO_RESERVED
}GPIO_PullState;

/* Speed configuration*/
typedef enum{
	GPIO_LOW_SPEED, GPIO_MEDIUM_SPEED,
	GPIO_HIGH_SPEED, GPIO_VERY_HIH_SPEED
}GPIO_SpeedState;

typedef enum{
	GPIO_AF00,
	GPIO_AF01,
	GPIO_AF02,
	GPIO_AF03,
	GPIO_AF04,
	GPIO_AF05,
	GPIO_AF06,
	GPIO_AF07,
	GPIO_AF08,
	GPIO_AF09,
	GPIO_AF10,
	GPIO_AF11,
	GPIO_AF12,
	GPIO_AF13,
	GPIO_AF14,
	GPIO_AF15,
}GPIO_AFx;

typedef struct{
	uint8 portName;
	GPIO_SpeedState pinSpeed;
	GPIO_PinMode pinMode;
	GPIO_DefaultState DefaultState;
	GPIO_PullState pullState;
	GPIO_AFx alternateFunction;
}GPIO_handleTypedef;
/*------------------------------------------------------*/

/*---------------------- Functions Prototype ----------------------*/

/*
 * description:
 * 	Argument(s):
 * 		--> PortName: Port needed to be configured.
 * 		--> PinNum: The pin needed to be configured.
 * 		--> PinMode: Modeof the Pin (Output, Input, Alternative function
 * 					 or Analog).
 * 		--> DefaultState: state of the pin whether being push/pull or
 * 						  open drain.
 * 		--> pullState: state of the pin (no pull up/down, pull up, pull down,
 * 					   or Reserved).
 * 	Function to configure the selected pin in the selected port.
 */
void GPIO_ConfigPin(GPIO_handleTypedef *GPIOx, uint8 pinNum);

/*
 * description:
 * 	Argument(s):
 * 		--> PortName: Port needed to be configured.
 * 		--> PinNum: The pin needed to be configured.
 * 		--> Data: data is wanted to be written (High or Low).
 * 	Function to write data on the selected pin in the selected port.
 * 	Return:
 * 		--> Gpio_WriteDataFlag: data has been written successfully or not
 * 								(OK or NOK)
 * 								if the pin was output --> OK.
 * 								if the pin was input  --> NOK
 */
GPIO_WriteDataFlag GPIO_WritePinValue(GPIO_handleTypedef *GPIOx, GPIO_Data Data , uint8 pinNum);

/*
 * description:
 * 	Argument(s):
 * 		--> PortName: Port needed to be configured.
 * 		--> PinNum: The pin needed to be configured.
 * 	Function to read data from the selected pin in the selected port.
 * 	Return:
 * 		--> Gpio_Data: Logic (High or Low).
 */

GPIO_WriteDataFlag GPIO_WritePortValue(GPIO_handleTypedef *GPIOx, uint16 Data);

GPIO_WriteDataFlag GPIO_TogglePin(GPIO_handleTypedef *GPIOx, uint8 pinNum);

GPIO_Data GPIO_ReadPinState(GPIO_handleTypedef *GPIOx, uint8 pinNum);

uint16 GPIO_ReadInputPortState(GPIO_handleTypedef *GPIOx);

uint16 GPIO_ReadOutputPortState(GPIO_handleTypedef *GPIOx);
/*--------------------------------------------------------------------*/

#endif /* GPIO_H */
