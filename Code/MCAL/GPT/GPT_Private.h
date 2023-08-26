/*
 * ====================================================================================================================================
 *  Project		: Vehicle Door Handle Control Unit
 * 	File Name	: GPT_Private.h
 *	Team 		: 20
 *	Members		: Abdelrahman Yasser - Omar Ahmed Anwar - Mo'men Mohamed - Neveen Mohamed
 *  ===================================================================================================================================
 */

#ifndef GPT_PRIVATE_H_
#define GPT_PRIVATE_H_

/*---------------------- Includes -------------------------------------------*/
#include "Std_Types.h"
/*---------------------------------------------------------------------------*/

/*---------------------- Definitions ----------------------------------------*/
// Define the base addresses for the four Timers.
#define TIM2_BASE_ADDRESS  0x40000000
#define TIM3_BASE_ADDRESS  0x40000400
#define TIM4_BASE_ADDRESS  0x40000800
#define TIM5_BASE_ADDRESS  0x40000C00
/*----------------------------------------------------------------------------*/

/*---------------------- Defined Data Types ----------------------------------*/
typedef struct{
	uint32 TIMx_CR1;
	uint32 TIMx_CR2;
	uint32 TIMx_SMCR;
	uint32 TIMx_DIER;
	uint32 TIMx_SR;
	uint32 TIMx_EGR;
	uint32 TIMx_CCMR1;
	uint32 TIMx_CCMR2;
	uint32 TIMx_CCER;
	uint32 TIMx_CNT;
	uint32 TIMx_PSC;
	uint32 TIMx_ARR;
	uint32 RESERVED_1;
	uint32 TIMx_CCR1;
	uint32 TIMx_CCR2;
	uint32 TIMx_CCR3;
	uint32 TIMx_CCR4;
	uint32 RESERVED_2;
	uint32 TIMx_DCR;
	uint32 TIMx_DMAR;
	uint32 TIM2_OR;
	uint32 TIM5_OR;
}TIMX_TYPE;

/* -------------------------------- CR1 ------------------------------------- */
typedef enum
{
	CR1_CEN_BIT, 			// Counter Enable Bit.
	EGR_UG_BIT = 0,			// Update Generation Bit.
	CR1_DIR_BIT = 4,  		// Counting Direction Bit.
}CR1_REG;

/*----------------------------------------------------------------------------*/

#endif /* GPT_PRIVATE_H_ */
