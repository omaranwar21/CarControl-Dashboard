/*
 * ====================================================================================================================================
 *  Project		: Vehicle Door Handle Control Unit
 * 	File Name	: Gpio.c
 *	Team 		: 20
 *	Members		: Abdelrahman Yasser - Omar Ahmed Anwar - Mo'men Mohamed - Neveen Mohamed
 *  ===================================================================================================================================
 */

/*---------------------- Includes ----------------------*/
#include "Gpio.h"
#include "Bit_Operations.h"
/*------------------------------------------------------*/

/*--------------- Global variables --------------------*/
uint32 gpioAddresses[6] = {
		GPIOA_BASE_ADDR,
		GPIOB_BASE_ADDR,
		GPIOC_BASE_ADDR,
		GPIOD_BASE_ADDR,
		GPIOE_BASE_ADDR,
		GPIOH_BASE_ADDR
};
/*------------------------------------------------------*/

/*---------------------- Functions Definition ----------------------*/

/*
 * description:
 * 	Argument(s):
 * 		--> PortName: Port needed to be configured.
 * 		--> PinNum: The pin needed to be configured.
 * 		--> PinMode: Mode of the Pin (Output, Input, Alternative function
 * 					 or Analog).
 * 		--> DefaultState: state of the pin whether being push/pull or
 * 						  open drain.
 * 		--> pullState: state of the pin (no pull up/down, pull up, pull down,
 * 					   or Reserved).
 * 	Function to configure the selected pin in the selected port.
 */
void GPIO_ConfigPin(GPIO_handleTypedef *GPIOx, uint8 pinNum)
{

	uint8 portID = GPIOx->portName - GPIO_A;

	GPIO_TypeDef *GPIO_Port = (GPIO_TypeDef *)gpioAddresses[portID];
	/*
	 * Configure mode of gpio pin.
	 */
	CLEAR_2_BITS(GPIO_Port->MODER, pinNum);
	GPIO_Port->MODER |= (GPIOx->pinMode << (pinNum * 2));

	/*
	 * Configure the speed of gpio pin.
	 */
	CLEAR_2_BITS(GPIO_Port->OSPEEDR, pinNum);
	GPIO_Port->OSPEEDR |= (GPIOx->pinSpeed << (pinNum * 2));

	/*
	 * Configure output type of gpio pin.
	 */
	CLEAR_BIT(GPIO_Port->OTYPER, pinNum);
	GPIO_Port->OTYPER |= (GPIOx->DefaultState << pinNum);

	/*
	 * Configure pull up/pull down settings of gpio pin.
	 */
	CLEAR_BIT(GPIO_Port->PUPDR, pinNum);
	GPIO_Port->PUPDR |= (GPIOx->pullState << (pinNum * 2));

	/*
	 * Configure the alternate functionality.
	 */
	if (GPIOx->pinMode == GPIO_AF) {
		uint8 AFReg = ((pinNum)/8);
		uint8 AFx = ((pinNum)%8);
		GPIO_Port->AFR[AFReg] &= ~((GPIOx->alternateFunction) << (4 * AFx));
		GPIO_Port->AFR[AFReg] |= ((GPIOx->alternateFunction) << (4 * AFx));
	}

}

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
GPIO_WriteDataFlag GPIO_WritePinValue(GPIO_handleTypedef *GPIOx, GPIO_Data Data, uint8 pinNum){

	uint8 portID = GPIOx->portName - GPIO_A;

	GPIO_TypeDef *GPIO_Port = (GPIO_TypeDef *)gpioAddresses[portID];

	if (( (GPIO_Port->MODER) & (0x03 << (pinNum * 2))) >> (pinNum*2) != GPIO_OUTPUT)
	{
		return NOK;
	}

	if(Data == HIGH){
		SET_BIT(GPIO_Port->ODR, pinNum);
	}
	else {
		CLEAR_BIT(GPIO_Port->ODR, pinNum);
	}

	return OK;
}

GPIO_WriteDataFlag GPIO_WritePortValue(GPIO_handleTypedef *GPIOx, uint16 Data){

	uint8 portID = GPIOx->portName - GPIO_A;

	GPIO_TypeDef *GPIO_Port = (GPIO_TypeDef *)gpioAddresses[portID];

	GPIO_Port->ODR = Data;

	return OK;
}

GPIO_WriteDataFlag GPIO_TogglePin(GPIO_handleTypedef *GPIOx, uint8 pinNum){

	uint8 portID = GPIOx->portName - GPIO_A;

	GPIO_TypeDef *GPIO_Port = (GPIO_TypeDef *)gpioAddresses[portID];

	if (( (GPIO_Port->MODER) & (0x03 << (pinNum * 2))) >> (pinNum*2) != GPIO_OUTPUT)
	{
		return NOK;
	}


	TOGGLE_BIT(GPIO_Port->ODR, pinNum);


	return OK;
}

/*
 * description:
 * 	Argument(s):
 * 		--> PortName: Port needed to be configured.
 * 		--> PinNum: The pin needed to be configured.
 * 	Function to read data from the selected pin in the selected port.
 * 	Return:
 * 		--> Gpio_Data: Logic (High or Low).
 */
GPIO_Data GPIO_ReadPinState(GPIO_handleTypedef *GPIOx, uint8 pinNum){

	uint8 portID = GPIOx->portName - GPIO_A;

	GPIO_TypeDef *GPIO_Port = (GPIO_TypeDef *)gpioAddresses[portID];

	GPIO_Data data;
	if ( ((GPIO_Port->MODER & (0x03 << (pinNum * 2))) >> (pinNum*2) ) == GPIO_OUTPUT) {
		data = ( (GPIO_Port->ODR) & (1 << pinNum))? GPIO_DATA_FALLING : GPIO_DATA_RISING;
	}
	else if ( ((GPIO_Port->MODER & (0x03 << (pinNum * 2))) >> (pinNum*2) ) == GPIO_INPUT){
		data = ( (GPIO_Port->IDR) & (1 << pinNum))? GPIO_DATA_RISING : GPIO_DATA_FALLING;
	}
	return data;
}

uint16 GPIO_ReadInputPortState(GPIO_handleTypedef *GPIOx){

	uint8 portID = GPIOx->portName - GPIO_A;

	GPIO_TypeDef *GPIO_Port = (GPIO_TypeDef *)gpioAddresses[portID];

	return (uint16)GPIO_Port->IDR;
}

uint16 GPIO_ReadOutputPortState(GPIO_handleTypedef *GPIOx){

	uint8 portID = GPIOx->portName - GPIO_A;

	GPIO_TypeDef *GPIO_Port = (GPIO_TypeDef *)gpioAddresses[portID];

	return (uint16)GPIO_Port->ODR;
}
/*------------------------------------------------------*/





