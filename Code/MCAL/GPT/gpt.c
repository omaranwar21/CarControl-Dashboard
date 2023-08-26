/*
 * ====================================================================================================================================
 *  Project		: Vehicle Door Handle Control Unit
 * 	File Name	: gpt.c
 *	Team 		: 20
 *	Members		: Abdelrahman Yasser - Omar Ahmed Anwar - Mo'men Mohamed - Neveen Mohamed
 *  ===================================================================================================================================
 */

/*---------------------- Includes ------------------------------------------*/
#include "gpt.h"
/*--------------------------------------------------------------------------*/

/*---------------------- Global Variables ----------------------------------*/

/*
 *  g_flag is a flag to make sure that function start timer has been called
 *  before calling check time is elapsed function.
 */
uint8 g_flag          = 0;

/*
 *  This flag is used while using counting up and down mode
 *  to hold the mode of the current counter mode(Down/Up).
 */
uint8 Counting_UpDown = 0;

/*--------------------------------------------------------------------------*/

/*---------------------- Functions Definition ------------------------------*/

/*
 * description:
 * 	Argument(s):
 * 		--> Timer: an object holds selected timer, prescaler amd the mode.
 * 	Function to initialize the GPT registers with the needed initial values passed in
 * 	Timer object to support the needed timing actions.
 */
void GPT_Init(TIMx_Configue* Timer){

	/*
	 * --> Add the prescaler value in TIMx_PSC register.
	 * --> Adjust counting direction through TIMx_CR1 register.
	 * --> Adjust update generation bit in TIMx_EGR in order to have the
	 * 	   ability to adust TIMx_CNT while counting is enabled.
	 */
	Timer->TIMx->TIMx_PSC = (Timer->prescaler)-1; // Add the prescaler value in TIMx_PSC register

	if (Timer->direction == GPT_Down_Counting)
	{
		SET_BIT(Timer->TIMx->TIMx_CR1,CR1_DIR_BIT); // Adjust down counting through TIMx_CR1 register
	}
	else if (Timer->direction == GPT_Up_Counting)
	{
		CLEAR_BIT(Timer->TIMx->TIMx_CR1, CR1_DIR_BIT); // Adjust up counting through TIMx_CR1 register
	}
	else if (Timer->direction == GPT_Up_Down_Counting)
	{
		SET_2_BITS(Timer->TIMx->TIMx_CR1,5); // Adjust up/down counting through TIMx_CR1 register
	}

	SET_BIT(Timer->TIMx->TIMx_EGR, EGR_UG_BIT); // Adjust update generation bit in TIMx_EGR

	SET_BIT(Timer->TIMx->TIMx_CR1, CR1_CEN_BIT); // Enable counting by set CEI_BIT in TIMx_CR1 register.

}

/*
 * description:
 * 	Argument(s):
 * 		--> Timer: an object holds selected timer, prescaler amd the mode.
 * 		--> overFlowTicks: number of tickets before timer overflow and stop.
 * 	A function to request the GPT to start and send its number of tickets before timer
 * 	overflow and stop.
 */
void GPT_StartTimer(TIMx_Configue* Timer,uint32 OverFlowTicks){

	/*
	 * --> Add number of ticks in TIMx_ARR register
	 * --> Reset counter by add one to TIMx_CNT
	 * --> Update g_flag to one in order to allow
	 *     entering check time is elapsed function
	 * --> Enable counting by set CEI_BIT in TIMx_CR1 register.
	 */

	if (Timer->direction == GPT_Up_Down_Counting && g_flag){
		Counting_UpDown= READ_BIT(Timer->TIMx->TIMx_CR1, CR1_DIR_BIT);
	}

	if (( (Timer->direction == GPT_Down_Counting) || (Counting_UpDown == GPT_Down_Counting ) )) {

		Timer->TIMx->TIMx_CNT = OverFlowTicks; // Reset counter by add one to TIMx_CNT

	}else{

		Timer->TIMx->TIMx_CNT = 1;
	}


	Timer->TIMx->TIMx_ARR = OverFlowTicks; // Add number of ticks in TIMx_ARR register

	g_flag = 1; // Update g_flag to one

}

/*
 * description:
 * 	Argument(s):
 * 		--> Timer: an object holds selected timer, prescaler amd the mode.
 * 	A function to return (1) if an overflow occurred after the last call of GPT_StartTimer
 * 	and (0) if no overflow occurred or GPT_StartTimer is not called from the last read.
 */
GPT_TimeIsElapsed GPT_CheckTimeIsElapsed(TIMx_Configue* Timer){

	/*
	 * In case up counting:
	 * 		--> Check if TIMx_CNT = TIMx_ARR-1
	 * In case down counting:
	 * 		--> Check if TIMx_CNT = 1
	 * clear g_flag.
	 */

	if (Timer->direction == GPT_Up_Down_Counting && g_flag){
		Counting_UpDown= READ_BIT(Timer->TIMx->TIMx_CR1, CR1_DIR_BIT);
	}

	/*
	 * In case down counting:
	 * 		--> Check if TIMx_CNT = 1
	 */
	if( ( (Timer->direction == GPT_Down_Counting) || (Counting_UpDown == GPT_Down_Counting ) ) && g_flag)
	{
		if (Timer->TIMx->TIMx_CNT == 0)
		{
			g_flag = 0; // clear g_flag
			return GPT_Elapsed;
		}
		else
		{
			return GPT_NotElapsed;
		}

	}
	/*
	 * In case up counting:
	 * 		--> Check if TIMx_CNT = TIMx_ARR-1
	 */
	else
	{
		if (Timer->TIMx->TIMx_CNT == ((Timer->TIMx->TIMx_ARR)-1))
		{
			g_flag = 0; //clear g_flag
			return GPT_Elapsed;
		}
		else
		{
			return GPT_NotElapsed;
		}
	}
}

/*
 * description:
 * 	Argument(s):
 * 		--> Timer: an object holds selected timer, prescaler amd the mode.
 * 	A function to return elapsed time.
 */
uint32 GPT_GetElapsedTime(TIMx_Configue* Timer){

	/*
	 * check direction:
	 * 		if up counting:
	 * 			return value in TIMx_CNT
	 * 		else
	 * 			return (TIMx_ARR - TIMx_CNT)
	 */
	uint32 Counter = Timer->TIMx->TIMx_CNT; // Get TIMx_CNT value in counter variable

	uint32 maxVal  = Timer->TIMx->TIMx_ARR; // Get TIMx_ARR value

	/*
	 * Check counting direction
	 */
	if (Timer->direction == GPT_Up_Down_Counting ){
		Counting_UpDown= READ_BIT(Timer->TIMx->TIMx_CR1, CR1_DIR_BIT);
	}

	if ((Timer->direction == GPT_Down_Counting) || (Counting_UpDown == GPT_Down_Counting))
	{
		Counter = maxVal - Counter ; // (TIMx_ARR - TIMx_CNT) in counter
	}
	return Counter;
}

/*
 * description:
 * 	Argument(s):
 * 		--> Timer: an object holds selected timer, prescaler amd the mode.
 * 	A function to return remaining time.
 */
uint32 GPT_GetRemainingTime(TIMx_Configue* Timer){

	/*
	 * check direction:
	 * 		if up counting:
	 * 			return (TIMx_ARR - TIMx_CNT)
	 * 		else
	 * 			return value in TIMx_CNT
	 */

	uint32 remainingTime = 0;

	/*
	 * Check counting direction
	 */
	if (Timer->direction == GPT_Up_Down_Counting ){
		Counting_UpDown= READ_BIT(Timer->TIMx->TIMx_CR1, CR1_DIR_BIT);
	}

	if( (Timer->direction == GPT_Down_Counting) ||(Counting_UpDown == GPT_Down_Counting) )
	{
		remainingTime = Timer->TIMx->TIMx_CNT; //Get TIMx_CNT value in remainingTime variable
	}
	else
	{
		remainingTime= (Timer->TIMx->TIMx_ARR - Timer->TIMx->TIMx_CNT); // (TIMx_ARR - TIMx_CNT) in remainingTime

	}

	return remainingTime;
}

void PWM_Init(PWM_config* pwm){
	pwm->TIMx->TIMx_PSC = pwm->prescaler;

	pwm->TIMx->TIMx_ARR = pwm->ARR_Value;

	pwm->TIMx->TIMx_CCMR1 |= (6 << 4);

	pwm->TIMx->TIMx_CCMR1 |= (1<< 3);

	pwm->TIMx->TIMx_CR1 |= (1<<7);

	pwm->TIMx->TIMx_CCER |= (1<<0);
}

void PWM_Output(PWM_config* pwm, uint32 duty_cycle){
	pwm->TIMx->TIMx_CCR1 = duty_cycle;
	SET_BIT(pwm->TIMx->TIMx_CR1, CR1_CEN_BIT);

}
/*--------------------------------------------------------------------------*/



