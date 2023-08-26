/*
 * ====================================================================================================================================
 *  Project		: Vehicle Door Handle Control Unit
 * 	File Name	: gpt.h
 *	Team 		: 20
 *	Members		: Abdelrahman Yasser - Omar Ahmed Anwar - Mo'men Mohamed - Neveen Mohamed
 *  ===================================================================================================================================
 */

#ifndef GPT_H_
#define GPT_H_

/*---------------------- Includes ----------------------------------*/
#include "Std_Types.h"
#include "GPT_Private.h"
#include "Bit_Operations.h"
#include "Rcc.h"
/*------------------------------------------------------------------*/

/*---------------------- Definitions -------------------------------*/
#define TIM2 ((TIMX_TYPE*)(TIM2_BASE_ADDRESS))
#define TIM3 ((TIMX_TYPE*)(TIM3_BASE_ADDRESS))
#define TIM4 ((TIMX_TYPE*)(TIM4_BASE_ADDRESS))
#define TIM5 ((TIMX_TYPE*)(TIM5_BASE_ADDRESS))
/*------------------------------------------------------------------*/


/*---------------------- Defined data Types ------------------------*/
typedef enum{
	GPT_Elapsed, GPT_NotElapsed
}GPT_TimeIsElapsed;

typedef enum
{
	GPT_Up_Counting, GPT_Down_Counting, GPT_Up_Down_Counting
}CR1_CounterDirection;

/*
 * 1) TIMx 		--> (TIM2, TIM3, TIM4, TIM5)
 * 2) prescaler --> value added in TIMx_PSC (PSC_VALUE+1)
 * 3) direction --> counting direction
 */
typedef struct{
	TIMX_TYPE* TIMx;
	uint16 prescaler;
	CR1_CounterDirection direction;
}TIMx_Configue;

typedef struct{
	TIMX_TYPE* TIMx;
	uint16 prescaler;
	uint32 ARR_Value;
}PWM_config;
/*------------------------------------------------------------------*/


/*---------------------- Functions prototype -----------------------*/

/*
 * description:
 * 	Argument(s):
 * 		--> Timer: an object holds selected timer, prescaler amd the mode.
 * 	Function to initialize the GPT registers with the needed initial values passed in
 * 	Timer object to support the needed timing actions.
 */
void GPT_Init(TIMx_Configue* Timer);

/*
 * description:
 * 	Argument(s):
 * 		--> Timer: an object holds selected timer, prescaler amd the mode.
 * 		--> overFlowTicks: number of tickets before timer overflow and stop.
 * 	A function to request the GPT to start and send its number of tickets before timer
 * 	overflow and stop.
 */
void GPT_StartTimer(TIMx_Configue* Timer,uint32 OverFlowTicks);

/*
 * description:
 * 	Argument(s):
 * 		--> Timer: an object holds selected timer, prescaler amd the mode.
 * 	A function to return (1) if an overflow occurred after the last call of GPT_StartTimer
 * 	and (0) if no overflow occurred or GPT_StartTimer is not called from the last read.
 */
GPT_TimeIsElapsed GPT_CheckTimeIsElapsed(TIMx_Configue* Timer);

/*
 * description:
 * 	Argument(s):
 * 		--> Timer: an object holds selected timer, prescaler amd the mode.
 * 	A function to return elapsed time.
 */
uint32 GPT_GetElapsedTime(TIMx_Configue* Timer);

/*
 * description:
 * 	Argument(s):
 * 		--> Timer: an object holds selected timer, prescaler amd the mode.
 * 	A function to return remaining time.
 */
uint32 GPT_GetRemainingTime(TIMx_Configue* Timer);

void PWM_Init(PWM_config* pwm);

void PWM_Output(PWM_config* pwm, uint32 duty_cycle);
/*------------------------------------------------------------------*/

#endif /* GPT_H_ */
