/*
 * Stm32_Arduino.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Anwar
 */

#include "Gpio.h"
#include "uart.h"
#include "Rcc.h"
#include "systicTimer.h"
#include "gpt.h"
#include "lcd.h"
#include "message_handler.h"
#include "dashboard.h"
#include "Delay.h"
#include "servo_motor.h"
#include "dc_motor.h"

/*
 * Baud rate: 9600
 * Frame Format: 1 stop bit, 8bits, no parity.
 *
 * UART2_TX --> PA2,
 * UART2_RX --> PA3
 */

/*
 * Timer prescaler = 160
 */


extern Move_Info readings;

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm("CPSIE F")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm("CPSID F")

/* Go to low power mode while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm("WFI")

#define UART_TX_PIN		2
#define UART_RX_PIN		3

GPIO_handleTypedef UART1_gpio = {
		GPIO_A,
		GPIO_MEDIUM_SPEED,
		GPIO_AF,
		GPIO_PUSH_PULL,
		GPIO_NO_PULL_UP_DOWN,
		GPIO_AF07
};

UARTx_Handler uart2 = {
		UART2,
		{
			UART_MODE_TX_RX,
			UART_STD_BAUD_9600,
			UART_1START_8DATA,
			UART_ONE_STOP_BIT,
			UART_PARITY_DISABLED,
			UART_HW_FLOW_CTRL_NONE
		}

};

int main(void) {
	uint8 response = ' ';
	uint8 time[3]={0};

	Rcc_Init();
	Rcc_Enable(RCC_GPIOA);
	Rcc_Enable(RCC_GPIOB);
	Rcc_Enable(RCC_USART2);
	Rcc_Enable(RCC_TIM2);
	Rcc_Enable(RCC_TIM3);

	LCD_init();

	SERVO_Init();
	DcMotor_Init();



	GPIO_ConfigPin(&UART1_gpio, UART_TX_PIN);
	GPIO_ConfigPin(&UART1_gpio, UART_RX_PIN);

	UART_init(&uart2);

	SysTick_Init(Time_Update, time);
	uart2.bufferLength = 8;

	Wait_For_Interrupt();
	while(1){
		if (uart2.bufferLength == 0) {
			UART_SendData(&uart2, &response, 1);
			uart2.bufferLength = 8;
			INFO_LCD_update(uart2.pRxBuffer, &readings);
			SERVO_Activate(readings.angle, readings.angleDirection);
			DcMotor_Rotate(readings.direction, readings.speed);
		}
	}
}



