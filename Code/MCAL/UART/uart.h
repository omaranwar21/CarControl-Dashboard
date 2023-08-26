/*
 * uart.h
 *
 *  Created on: Aug 22, 2023
 *      Author: Anwar
 */

#ifndef UART_H_
#define UART_H_

/*---------------------- Includes ----------------------*/
#include "uart_private.h"
/*------------------------------------------------------*/
#define UART1								((UART_TypeDef*)(UART1_BASE_ADDR))
#define UART6								((UART_TypeDef*)(UART6_BASE_ADDR))
#define UART2								((UART_TypeDef*)(UART2_BASE_ADDR))


#define UART_STD_BAUD_1200					1200
#define UART_STD_BAUD_2400					400
#define UART_STD_BAUD_9600					9600
#define UART_STD_BAUD_19200 				19200
#define UART_STD_BAUD_38400 				38400
#define UART_STD_BAUD_57600 				57600
#define UART_STD_BAUD_115200 				115200
#define UART_STD_BAUD_230400 				230400
#define UART_STD_BAUD_460800 				460800
#define UART_STD_BAUD_921600 				921600
#define UART_STD_BAUD_2M 					2000000
#define UART_STD_BAUD_3M 					3000000

typedef enum{
	UART_SR_PE,				/* Parity Error							  */
	UART_SR_FE,				/* Framing Error						  */
	UART_SR_NF,				/* Noise detected flag					  */
	UART_SR_ORE,			/* Overrun error						  */
	UART_SR_IDLE,			/* IDLE line detected					  */
	UART_SR_RXNE,			/* Read data register not empty			  */
	UART_SR_TC,				/* Transmission complete	  			  */
	UART_SR_TXE,			/* Transmit data register empty			  */
	UART_SR_LBD,			/* LIN break detection flag				  */
	UART_SR_CTS,			/* CTS Flag		 				 		  */
}UARTx_SR;

typedef enum{
	UART_CR1_SBK,			/* Send break							  */
	UART_CR1_RWE,			/* Receiver Wakeup						  */
	UART_CR1_RE,			/* Receiver enable						  */
	UART_CR1_TE,			/* Transmitter enable					  */
	UART_CR1_IDLEIE,		/* IDLE Interrupt enable				  */
	UART_CR1_RXNEIE,		/* RXNE Interrupt enable				  */
	UART_CR1_TCIE,			/* Transmission complete interrupt enable */
	UART_CR1_TXEIE,			/* TXE Interrupt Enable					  */
	UART_CR1_PEIE,			/* PE Interrupt Enable	 				  */
	UART_CR1_PS,			/* Parity Selection		 				  */
	UART_CR1_PCE,			/* Parity control enable 				  */
	UART_CR1_WAKE,			/* Wakeup Method		 				  */
	UART_CR1_M,				/* Word Length			 				  */
	UART_CR1_UE,			/* UART Enable			 				  */
	UART_CR1_OVER8 = 15,	/* Oversampling mode	 				  */
}UARTx_CR1;

typedef enum{
	UART_CR2_ADD,			/* Address of the UART node				  */
	UART_CR2_LBDL = 5,		/* LIN break detection length			  */
	UART_CR2_LBDIE,			/* LIN break detection interrupt enable   */
	UART_CR2_LBCL = 8,		/* Last bit clock pulse	 				  */
	UART_CR2_CPHA,			/* Clock phase			 				  */
	UART_CR2_CPOL,			/* Clock polarity		 				  */
	UART_CR2_CLKEN,			/* Clock Enable			 				  */
	UART_CR2_STOP,			/* Stop Bits			 				  */
	UART_CR2_LINEN = 14,	/* LIN mode enable		 				  */
}UARTx_CR2;

typedef enum{
	UART_CR3_EIE,			/* Error Interrupt enable				  */
	UART_CR3_IREN,			/* IrDA mode Enable						  */
	UART_CR3_IRLP,			/* IrDA low-power						  */
	UART_CR3_HDSEL,			/* Half-duplex selection 				  */
	UART_CR3_NACK,			/* Smartcard NACK enable 				  */
	UART_CR3_SCEN,			/* Smartcard mode enable 				  */
	UART_CR3_DMAR,			/* DMA Enable receiver	 				  */
	UART_CR3_DMAT,			/* DMA enable transmitter 				  */
	UART_CR3_RTSE,			/* RTS Enable			 				  */
	UART_CR3_CTSE,			/* CTS Enable			 				  */
	UART_CR3_CTSIE,			/* CTS Interrupt enable	 				  */
	UART_CR3_ONEBIT,		/* One sample bit method enable			  */
}UARTx_CR3;

typedef enum{
	UART_MODE_TX,
	UART_MODE_RX,
	UART_MODE_TX_RX
}UART_Mode;

typedef enum{
	UART_1START_8DATA,
	UART_1START_9DATA
}UART_WordLength;

typedef enum{
	UART_ONE_STOP_BIT,
	UART_HALF_STOP_BIT,
	UART_TWO_STOP_BITS,
	UART_ONE_HALF_STOP_BIT,
}UART_StopBits;

typedef enum{
	UART_PARITY_ODD,
	UART_PARITY_EVEN,
	UART_PARITY_DISABLED,
}UART_ParityControl;

typedef enum{
	UART_DISABLE,
	UART_ENABLE
}UART_ControlState;

typedef enum{
	UART_HW_FLOW_CTRL_NONE,
	UART_HW_FLOW_CTRL_CTS,
	UART_HW_FLOW_CTRL_RTS,
	UART_HW_FLOW_CTRL_CTS_RTS
}UART_HWFlowControl;

typedef struct{
	UART_Mode				mode;
	uint32					baud_rate;
	UART_WordLength 		word_legth;
	UART_StopBits			no_stop_bits;
	UART_ParityControl 		parity_control;
	uint8	 				HW_flowControl;
}UARTx_Config;

typedef struct{
	UART_TypeDef	*pUARTx;
	UARTx_Config 	UART_config;
	uint8 			pRxBuffer[8];
	uint8 			*pTxBuffer;
	uint8 			bufferLength;
}UARTx_Handler;

void UART_PeripheralControl(UARTx_Handler* UARTx, UART_ControlState EnOrDi);
void UART_init(UARTx_Handler* UARTx);

void UART_SendData(UARTx_Handler* UARTx, uint8 *pTxBuffer, uint32 length);
void UART_ReceiveData(UARTx_Handler* UARTx, uint8 *pRxBuffer, uint32 length);

void UART_ReceiveDataInterrupt(UARTx_Handler* UARTx, uint8 *pRxBuffer);

#endif /* UART_H_ */
