/*
 * message_handler.h
 *
 *  Created on: Aug 25, 2023
 *      Author: Anwar
 */

#ifndef MESSAGE_HANDLER_MESSAGE_HANDLER_H_
#define MESSAGE_HANDLER_MESSAGE_HANDLER_H_

#include "Std_Types.h"
typedef struct{
	uint8 speed;
	uint8 direction;
	uint8 angle;
	uint8 angleDirection;
}Move_Info;

typedef enum{
	INFO_INVALID, INFO_VALID, DIRECTION_ERROR = 3, ANGLE_DIRECTION_ERROR, ANGLE_ERROR = 46, SPEED_ERROR = 101
}INFO_Errors;

uint8 INFO_GetSpeed(uint8 *msg);
uint8 INFO_GetDirection(uint8 *msg);
uint8 INFO_GetAngleDirection(uint8 *msg);
uint8 INFO_GetAngle(uint8 *msg);
INFO_Errors Info_translate(uint8 *msg);

#endif /* MESSAGE_HANDLER_MESSAGE_HANDLER_H_ */
