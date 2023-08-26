/*
 * systicTimer.c
 *
 *  Created on: Aug 25, 2023
 *      Author: Anwar
 */

#include "systicTimer.h"
#include "Bit_Operations.h"

void (*pSysticFunction)(uint8*);
uint8* arg;
void SysTick_Init(void(*ptrToFunction)(uint8*), uint8* time)
{
    SYSTICK_CTRL_REG    = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
    /* Set the Reload value with 15999999 - 7000 to count one Second
     * 7000 is for ms seconds delay of the LCD Display*/
    SYSTICK_RELOAD_REG  = 15999999 - 1700000;
    SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */
    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x07;

//    SysTick_WaitForOverFlow(ptrToFunction, time);
	pSysticFunction = ptrToFunction;
	arg = time;
}

//void SysTick_WaitForOverFlow(void(*ptrToFunction)(uint8*), uint8* time){
//	/* wait until the COUNT flag = 1 which mean SysTick Timer reaches ZERO value ...
//	 *  COUNT flag is cleared after read the CTRL register value */
////	while(!( READ_BIT(SYSTICK_CTRL_REG, SYSTICK_COUNT_FLAG_POS) ));
//}

void SysTick_Handler(void){
	pSysticFunction(arg);
}

