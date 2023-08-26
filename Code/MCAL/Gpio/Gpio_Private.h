/*
 * ====================================================================================================================================
 *  Project		: Vehicle Door Handle Control Unit
 * 	File Name	: Gpio_Private.h
 *	Team 		: 20
 *	Members		: Abdelrahman Yasser - Omar Ahmed Anwar - Mo'men Mohamed - Neveen Mohamed
 *  ===================================================================================================================================
 */

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/*---------------------- Includes ----------------------*/
#include "Std_Types.h" // to use standard types such as (uint32)
/*------------------------------------------------------*/

/*--------------------- Definitions -------------------- */
#define GPIOA_BASE_ADDR		0x40020000UL
#define GPIOB_BASE_ADDR		0x40020400UL
#define GPIOC_BASE_ADDR		0x40020800UL
#define GPIOD_BASE_ADDR		0x40020C00UL
#define GPIOE_BASE_ADDR		0x40021000UL
#define GPIOH_BASE_ADDR		0x40021C00UL
/*------------------------------------------------------*/

/*---------------------- defined data types --------------- */
typedef struct{
	__IO uint32 MODER;
	__IO uint32 OTYPER;
	__IO uint32 OSPEEDR;
	__IO uint32 PUPDR;
	__IO uint32 IDR;
	__IO uint32 ODR;
	__IO uint32 BSRR;
	__IO uint32 LCKR;
	__IO uint32 AFR[2];
}GPIO_TypeDef;
/*-------------------------------------------------------------*/

#endif /* GPIO_PRIVATE_H */
