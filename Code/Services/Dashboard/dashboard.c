/*
 * dashboard.c
 *
 *  Created on: Aug 25, 2023
 *      Author: Anwar
 */
#include "dashboard.h"
#include "lcd.h"
#include "NVIC.h"



void Time_Display(uint8* time){
	LCD_moveCursor(1, 7);
	LCD_displayString("Time: ");
	LCD_moveCursor(1, 13);
	LCD_intgerToString(time[2]/10);
	LCD_moveCursor(1, 14);
	LCD_intgerToString(time[2]%10);
	LCD_moveCursor(1, 15);
	LCD_displayCharacter(':');
	LCD_moveCursor(1, 16);
	LCD_intgerToString(time[1]/10);
	LCD_moveCursor(1, 17);
	LCD_intgerToString(time[1]%10);
	LCD_moveCursor(1, 18);
	LCD_displayCharacter(':');
	LCD_moveCursor(1, 19);
	LCD_intgerToString(time[0]/10);
	LCD_moveCursor(1, 20);
	LCD_intgerToString(time[0]%10);
	LCD_moveCursor(1, 21);
	if(time[2] > 12){
		LCD_displayString(" PM");
	}else {
		LCD_displayString(" AM");
	}
}

void Time_Update(uint8* time){

	time[0]++;
	if (time[0] == 60) {
		time[0] = 0;
		time[1]++;
	}

	if (time[1] == 60) {
		time[0] = 0;
		time[1] = 0;
		time[2]++;
	}
	if (time[2] == 24) {
		time[0] = 0;
		time[1] = 0;
		time[2] = 0;
	}
	Time_Display(time);
}

void INFO_LCD_update(uint8 *msg, Move_Info* readings){
	Info_translate((uint8 *)msg);
	Disable_Exceptions();
	LCD_moveCursor(0, 0);
	LCD_displayString("Speed: ");
	LCD_moveCursor(0, 7);
	LCD_displayString("   ");
	LCD_moveCursor(0, 7);
	LCD_intgerToString(readings->speed);
	LCD_moveCursor(0, 11);
	LCD_displayCharacter('%');
	LCD_moveCursor(0, 17);
	LCD_displayString(" Direction: ");
	LCD_moveCursor(0, 28);
	LCD_displayCharacter(' ');
	LCD_moveCursor(0, 29);
	LCD_displayCharacter(readings->angleDirection);
	LCD_moveCursor(0, 30);
	LCD_displayString("  ");
	LCD_moveCursor(0, 30);
	LCD_intgerToString(readings->angle);
	Enable_Exceptions();
}
