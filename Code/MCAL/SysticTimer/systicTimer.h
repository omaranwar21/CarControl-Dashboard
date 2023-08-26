/*
 * systicTimer.h
 *
 *  Created on: Aug 25, 2023
 *      Author: Anwar
 */

#ifndef SYSTICTIMER_H_
#define SYSTICTIMER_H_

#include "Std_Types.h"

#define SYSTICK_COUNT_FLAG_POS	   16

#define SYSTICK_CTRL_REG          (*((volatile uint32 *)0xE000E010))
#define SYSTICK_RELOAD_REG        (*((volatile uint32 *)0xE000E014))
#define SYSTICK_CURRENT_REG       (*((volatile uint32 *)0xE000E018))

void SysTick_Init(void(*ptrToFunction)(uint8*), uint8* time);
//void SysTick_WaitForOverFlow(void(*ptrToFunction)(uint8*), uint8* time);


#endif /* SYSTICTIMER_H_ */
