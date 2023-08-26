/*
 * message_handler.c
 *
 *  Created on: Aug 25, 2023
 *      Author: Anwar
 */

#include "message_handler.h"

#define DC_CW		1
#define DC_ACW		2

Move_Info readings;

uint8 INFO_GetSpeed(uint8 *msg){
	uint8 speed = 0;
	uint8 loop;
	for (loop = 0; loop < 3; ++loop) {
		if (msg[loop] < 48 || msg[loop] > 57) {
			return (uint8)SPEED_ERROR;
		}
		speed = speed*10 + (msg[loop] - 48);
	}

	return speed;
}

uint8 INFO_GetDirection(uint8 *msg){
	switch (msg[3]) {
		case 'B':
			return DC_CW;
			break;
		case 'F':
			return DC_ACW;
			break;
		default:
			return (uint8)DIRECTION_ERROR;
			break;
	}
	return msg[3];
}

uint8 INFO_GetAngleDirection(uint8 *msg){
	switch (msg[6]) {
		case 'R':
			return (uint8)'+';
		case 'L':
			return (uint8)'-';
			break;
		default:
			return (uint8)ANGLE_DIRECTION_ERROR;
			break;
	}
}

uint8 INFO_GetAngle(uint8 *msg){
	uint8 angle = 0;
	uint8 loop;
	for (loop = 4; loop < 6; ++loop) {
		if (msg[loop] < 48 || msg[loop] > 57) {
			return (uint8)ANGLE_ERROR;
		}
		angle = angle*10 + (msg[loop] - 48);
	}

	return angle;
}

INFO_Errors Info_translate(uint8 *msg){
	if(msg[7] != 'E'){
		return INFO_INVALID;
	}

	uint8 speed = INFO_GetSpeed(msg);
	if (speed > 100 || speed == SPEED_ERROR) {
		return INFO_INVALID;
	}

	uint8 direction = INFO_GetDirection(msg);
	if (direction == DIRECTION_ERROR) {
		return INFO_INVALID;
	}

	uint8 angle = INFO_GetAngle(msg);
	if (angle == ANGLE_ERROR) {
		return INFO_INVALID;
	}

	uint8 angleDirection = INFO_GetAngleDirection(msg);
	if (angleDirection == ANGLE_DIRECTION_ERROR) {
		return INFO_INVALID;
	}


	readings.speed = speed;
	readings.direction = direction;
	readings.angle = angle;
	readings.angleDirection = angleDirection;

	return INFO_VALID;
}
