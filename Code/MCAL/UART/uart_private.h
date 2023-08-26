/*
 * uart_private.h
 *
 *  Created on: Aug 22, 2023
 *      Author: Anwar
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/*---------------------- Includes ----------------------*/
#include "Std_Types.h" // to use standard types such as (uint32)
/*------------------------------------------------------*/

/*--------------------- Definitions -------------------- */
#define UART1_BASE_ADDR		0x40011000UL
#define UART6_BASE_ADDR		0x40011400UL
#define UART2_BASE_ADDR		0x40004400UL
/*------------------------------------------------------*/

/*---------------------- defined data types --------------- */
typedef struct{
	__IO uint32 SR;
	__IO uint32 DR;
	__IO uint32 BRR;
	__IO uint32 CR1;
	__IO uint32 CR2;
	__IO uint32 CR3;
	__IO uint32 GTPR;
}UART_TypeDef;
/*-------------------------------------------------------------*/


#endif /* UART_PRIVATE_H_ */
