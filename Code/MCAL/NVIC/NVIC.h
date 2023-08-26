/*
 * ====================================================================================================================================
 *  Project		: NVIC_driver
 * 	File Name	: NVIC.h
 *	Author		: Omar Anwar
 *  ===================================================================================================================================
 */
#ifndef NVIC_H_
#define NVIC_H_

#include "NVIC_Private.h"
#include "Std_Types.h"

#define NVIC_ISERx	((NVIC_ISER*)(NVIC_BASE_ADDRESS + NVIC_ISER_OFFSET))
#define NVIC_ICERx	((NVIC_ICER*)(NVIC_BASE_ADDRESS + NVIC_ICER_OFFSET))
#define NVIC_ISPRx	((NVIC_ISPR*)(NVIC_BASE_ADDRESS + NVIC_ISPR_OFFSET))
#define NVIC_ICPRx	((NVIC_ICPR*)(NVIC_BASE_ADDRESS + NVIC_ICPR_OFFSET))
#define NVIC_IABRx	((NVIC_IABR*)(NVIC_BASE_ADDRESS + NVIC_IABR_OFFSET))
#define NVIC_IPRx	((NVIC_IPR*)(NVIC_BASE_ADDRESS  + NVIC_IPR_OFFSET ))
#define NVIC_STIR	((NVIC_STIR*)(NVIC_BASE_ADDRESS + NVIC_STIR_OFFSET))

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmble Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm("CPSIE I")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmble Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm("CPSID I")

typedef enum{
	NVIC_WWDG,
	NVIC_EXTI16,
	NVIC_PVD = 1,
	NVIC_EXTI21,
	NVIC_TAMP_STAMP = 2,
	NVIC_EXTI22,
	NVIC_RTC_WKUP = 3,
	NVIC_FLASH,
	NVIC_RCC,
	NVIC_EXTI0,
	NVIC_EXTI1,
	NVIC_EXTI2,
	NVIC_EXTI3,
	NVIC_EXTI4,
	NVIC_DMA1_Stream0,
	NVIC_DMA1_Stream1,
	NVIC_DMA1_Stream2,
	NVIC_DMA1_Stream3,
	NVIC_DMA1_Stream4,
	NVIC_DMA1_Stream5,
	NVIC_DMA1_Stream6,
	NVIC_ADC,
	NVIC_EXTI9_5 = 23,
	NVIC_TIM1_BRK,
	NVIC_TIM9 = 24,
	NVIC_TIM1_UP,
	NVIC_TIM10 = 25,
	NVIC_TIM1_TRG_COM,
	NVIC_TIM11 = 26,
	NVIC_TIM1_CC,
	NVIC_TIM2,
	NVIC_TIM3,
	NVIC_TIM4,
	NVIC_I2C1_EV,
	NVIC_I2C1_ER,
	NVIC_I2C2_EV,
	NVIC_I2C2_ER,
	NVIC_SPI1,
	NVIC_SPI2,
	NVIC_USART1,
	NVIC_USART2,
	NVIC_EXTI15_10 = 40,
	NVIC_EXTI17,
	NVIC_RTC_Alarm = 41,
	NVIC_EXTI18,
	NVIC_OTG_FS_WKUP = 42,
	NVIC_DMA1_Stream7 = 47,
	NVIC_SDIO = 49,
	NVIC_TIM5,
	NVIC_SPI3,
	NVIC_DMA2_Stream0 = 56,
	NVIC_DMA2_Stream1,
	NVIC_DMA2_Stream2,
	NVIC_DMA2_Stream3,
	NVIC_DMA2_Stream4,
	NVIC_OTG_FS = 67,
	NVIC_DMA2_Stream5,
	NVIC_DMA2_Stream6,
	NVIC_DMA2_Stream7,
	NVIC_USART6,
	NVIC_I2C3_EV,
	NVIC_I2C3_ER,
	NVIC_FPU = 81,
	NVIC_SPI4 = 84
}NVIC_Lines;

typedef enum{
	NVIC_NOK, NVIC_OK
}NVIC_Flag;

void NVIC_LineEnable(NVIC_Lines line);

void NVIC_LineDisable(NVIC_Lines line);

NVIC_Flag NVIC_SetPending(NVIC_Lines line);

NVIC_Flag NVIC_ClearPending(NVIC_Lines line);

NVIC_Flag NVIC_CheckIsPending(NVIC_Lines line);

NVIC_Flag NVIC_CheckIsActive(NVIC_Lines line);

void NVIC_PrioritySetting(NVIC_Lines line, uint8 priority);

#endif /* NVIC_H_ */
