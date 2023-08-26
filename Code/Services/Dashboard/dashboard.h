/*
 * dashboard.h
 *
 *  Created on: Aug 25, 2023
 *      Author: Anwar
 */

#ifndef DASHBOARD_DASHBOARD_H_
#define DASHBOARD_DASHBOARD_H_

#include "Std_Types.h"
#include "message_handler.h"

void Time_Display(uint8* time);
void Time_Update(uint8* time);
void INFO_LCD_update(uint8 *msg, Move_Info* readings);


#endif /* DASHBOARD_DASHBOARD_H_ */
