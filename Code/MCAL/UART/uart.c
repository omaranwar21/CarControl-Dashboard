/*
 * uart.c
 *
 *  Created on: Aug 22, 2023
 *      Author: Anwar
 */


#include "uart.h"
#include "Bit_Operations.h"
#include "Rcc.h"
#include "NVIC.h"

UARTx_Handler* g_UARTx;


void UART_PeripheralControl(UARTx_Handler* UARTx, UART_ControlState EnOrDi){
	switch (EnOrDi) {
		case UART_ENABLE:
			SET_BIT(UARTx->pUARTx->CR1, UART_CR1_UE);
			break;
		case UART_DISABLE:
			CLEAR_BIT(UARTx->pUARTx->CR1, UART_CR1_UE);
			break;
	}
}

void UART_SetBaudRate(UARTx_Handler *pUARTx, uint32 BaudRate)
{

	//Variable to hold the APB clock
	uint32 PCLKx;

	uint32 uartdiv;

	//variables to hold Mantissa and Fraction values
	uint32 M_part,F_part;

	uint32 tempreg=0;

	//Get the value of APB bus clock in to the variable PCLKx
	if(pUARTx->pUARTx == UART1 || pUARTx->pUARTx == UART6)
	{
		//USART1 and USART6 are hanging on APB2 bus
		PCLKx = RCC_GetPCLK2Value();
	}else
	{
		PCLKx = RCC_GetPCLK1Value();
	}

	//Check for OVER8 configuration bit
	if(pUARTx->pUARTx->CR1 & (1 << UART_CR1_OVER8))
	{
		//OVER8 = 1 , over sampling by 8
		uartdiv = ((25 * PCLKx) / (2 *BaudRate));
	}else
	{
		//over sampling by 16
		uartdiv = ((25 * PCLKx) / (4 *BaudRate));
	}

	//Calculate the Mantissa part
	M_part = uartdiv/100;

	//Place the Mantissa part in appropriate bit position . refer USART_BRR
	tempreg |= M_part << 4;

	//Extract the fraction part
	F_part = (uartdiv - (M_part * 100));

	//Calculate the final fractional
	if(READ_BIT(pUARTx->pUARTx->CR1, UART_CR1_OVER8))
	{
		//OVER8 = 1 , over sampling by 8
		F_part = ((( F_part * 8)+ 50) / 100)& ((uint8)0x07);

	}else
	{
		//over sampling by 16
		F_part = ((( F_part * 16)+ 50) / 100) & ((uint8)0x0F);

	}

	//Place the fractional part in appropriate bit position . refer USART_BRR
	tempreg |= F_part;

	//copy the value of tempreg in to BRR register
	pUARTx->pUARTx->BRR = tempreg;
}

void UART_init(UARTx_Handler* UARTx){

	g_UARTx = UARTx;
	// UART Enable
	UART_PeripheralControl(UARTx, UART_ENABLE);

	// UART mode configurations.
	switch (UARTx->UART_config.mode) {
		case UART_MODE_RX:
			SET_BIT(UARTx->pUARTx->CR1, UART_CR1_RE);
			break;
		case UART_MODE_TX:
			SET_BIT(UARTx->pUARTx->CR1, UART_CR1_TE);
			break;
		case UART_MODE_TX_RX:
			SET_BIT(UARTx->pUARTx->CR1, UART_CR1_RE);
			SET_BIT(UARTx->pUARTx->CR1, UART_CR1_TE);
			break;
	}

	// UART word length
	CLEAR_BIT(UARTx->pUARTx->CR1,UART_CR1_M);
	UARTx->pUARTx->CR1 |= (UARTx->UART_config.word_legth<< UART_CR1_M);

	// UART parity control
	switch (UARTx->UART_config.parity_control) {
		case UART_PARITY_EVEN:
			SET_BIT(UARTx->pUARTx->CR1, UART_CR1_PCE);
			CLEAR_BIT(UARTx->pUARTx->CR1, UART_CR1_PCE);
			break;
		case UART_PARITY_ODD:
			SET_BIT(UARTx->pUARTx->CR1, UART_CR1_PCE);
			SET_BIT(UARTx->pUARTx->CR1, UART_CR1_PCE);
			break;
		case UART_PARITY_DISABLED:
			CLEAR_BIT(UARTx->pUARTx->CR1, UART_CR1_PCE);
			break;
		default:
			break;
	}

	//UART Stop bits
	UARTx->pUARTx->CR2 &= ~(3 << UART_CR2_STOP);
	UARTx->pUARTx->CR2 |= (UARTx->UART_config.no_stop_bits << UART_CR2_STOP);

	//UART HW flow control
	UARTx->pUARTx->CR3 &= ~(3 << UART_CR3_RTSE);
	UARTx->pUARTx->CR3 |= (UARTx->UART_config.HW_flowControl << UART_CR3_RTSE);

	//UART Baud rate
	UART_SetBaudRate(UARTx, UARTx->UART_config.baud_rate);

	NVIC_LineEnable(NVIC_USART2);
	UARTx->pUARTx->CR1 |= (1<<UART_CR1_RXNEIE);

}

void UART_SendData(UARTx_Handler* UARTx, uint8 *pTxBuffer, uint32 length){

	uint16 *data;
	while(length){
		// wait until data is transferred
		while(! READ_BIT(UARTx->pUARTx->SR, UART_SR_TXE));

		//Check word length
		switch (UARTx->UART_config.word_legth) {
			case UART_1START_9DATA:
				data = (uint16*)pTxBuffer;
				UARTx->pUARTx->DR = (*data & (uint16)0x01FF);

				if(UARTx->UART_config.parity_control == UART_PARITY_DISABLED){
					/*No parity is used in this transfer , so 9bits of user data will be sent
					 *Move pBuffer twice */
					pTxBuffer++;
					pTxBuffer++;
				}
				else {
					/*Parity bit is used in this transfer . so 8bits of user data will be sent
					 *The 9th bit will be replaced by parity bit by the hardware*/
					pTxBuffer++;
				}

			case UART_1START_8DATA:
				UARTx->pUARTx->DR = (*pTxBuffer & (uint8)0xFF);
				pTxBuffer++;
				break;
		}

		// wait till TC flag is set in the SR
		while(! READ_BIT(UARTx->pUARTx->SR, UART_SR_TC));

		// decrement buffer length
		length--;
	}
}

void UART_ReceiveData(UARTx_Handler* UARTx, uint8 *pRxBuffer, uint32 length){

	while(length){
		// wait until data is Received
		while(! READ_BIT(UARTx->pUARTx->SR, UART_SR_RXNE));

		//Check word length
		switch (UARTx->UART_config.word_legth) {
			case UART_1START_9DATA:

				if(UARTx->UART_config.parity_control == UART_PARITY_DISABLED){
					/*No parity is used in this transfer , so 9bits of user data will be sent
					 *Move pBuffer twice */
					*((uint16*)pRxBuffer) = (UARTx->pUARTx->DR & (uint16)0x01FF);
					pRxBuffer++;
					pRxBuffer++;
				}
				else {
					/*Parity bit is used in this transfer . so 8bits of user data will be sent
					 *The 9th bit will be replaced by parity bit by the hardware*/
					*pRxBuffer = (UARTx->pUARTx->DR & (uint8)0x00FF);
					pRxBuffer++;
				}

			case UART_1START_8DATA:
				if(UARTx->UART_config.parity_control == UART_PARITY_DISABLED){
					/*No parity is used in this transfer , so 9bits of user data will be sent
					 *Move pBuffer twice */
					*pRxBuffer = (uint8)(UARTx->pUARTx->DR & (uint8)0xFF);
				}
				else {
					/*Parity bit is used in this transfer . so 8bits of user data will be sent
					 *The 9th bit will be replaced by parity bit by the hardware*/
					*pRxBuffer = (uint8) (UARTx->pUARTx->DR & (uint8)0x7F);
				}
				pRxBuffer++;
				break;
		}


		// decrement buffer length
		length--;
	}
}

void USART2_IRQHandler(void){
	Disable_Exceptions();
	g_UARTx->pRxBuffer[8-g_UARTx->bufferLength] = (uint8)g_UARTx->pUARTx->DR;
	g_UARTx->bufferLength--;
	Enable_Exceptions();
}
