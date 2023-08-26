/**
 * Rcc.c
 *
 *  Created on: Sun Mar 26 2023
 *  Author    : Abdullah Darwish
 */

#include "Rcc.h"

#include "Bit_Operations.h"
#include "Rcc_Private.h"
#include "Std_Types.h"

uint16 AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint8 APB1_PreScaler[4] = { 2, 4 , 8, 16};

void Rcc_Init(void) {
	SET_BIT(RCC->CR , 0);
}

void Rcc_Enable(Rcc_PeripheralIdType PeripheralId) {
  uint8 BusId = PeripheralId / 32;
  uint8 PeripheralBitPosition = PeripheralId % 32;
  switch (BusId) {
    case RCC_AHB1:
      SET_BIT(RCC->AHB1ENR, PeripheralBitPosition);
      break;
    case RCC_AHB2:
      SET_BIT(RCC->AHB2ENR, PeripheralBitPosition);
      break;
    case RCC_APB1:
      SET_BIT(RCC->APB1ENR, PeripheralBitPosition);
      break;
    case RCC_APB2:
      SET_BIT(RCC->APB2ENR, PeripheralBitPosition);
      break;
    default:
      break;
  }
}

void Rcc_Disable(Rcc_PeripheralIdType PeripheralId) {
     uint8 BusId = PeripheralId / 32;
  uint8 PeripheralBitPosition = PeripheralId % 32;
  switch (BusId) {
    case RCC_AHB1:
      SET_BIT(RCC->AHB1RSTR, PeripheralBitPosition);
      break;
    case RCC_AHB2:
      SET_BIT(RCC->AHB2RSTR, PeripheralBitPosition);
      break;
    case RCC_APB1:
      SET_BIT(RCC->APB1RSTR, PeripheralBitPosition);
      break;
    case RCC_APB2:
      SET_BIT(RCC->APB2RSTR, PeripheralBitPosition);
      break;
    default:
      break;
  }
}


uint32 RCC_GetPCLK1Value(void){
	uint32 pclk1,SystemClk;

	uint8 clksrc,temp,ahbp,apb1p;

	clksrc = ((RCC->CFGR >> 2) & 0x3);

	if(clksrc == 0 )
	{
		SystemClk = 16000000;
	}else if(clksrc == 1)
	{
		SystemClk = 8000000;
	}else if (clksrc == 2)
	{
		SystemClk = RCC_GetPLLOutputClock();
	}

	//for ahb
	temp = ((RCC->CFGR >> 4 ) & 0xF);

	if(temp < 8)
	{
		ahbp = 1;
	}else
	{
		ahbp = AHB_PreScaler[temp-8];
	}



	//apb1
	temp = ((RCC->CFGR >> 10 ) & 0x7);

	if(temp < 4)
	{
		apb1p = 1;
	}else
	{
		apb1p = APB1_PreScaler[temp-4];
	}

	pclk1 =  (SystemClk / ahbp) /apb1p;

	return pclk1;
}

uint32 RCC_GetPCLK2Value(void){
	uint32 SystemClock=0,tmp,pclk2;
	uint8 clk_src = ( RCC->CFGR >> 2) & 0X3;

	uint8 ahbp,apb2p;

	if(clk_src == 0)
	{
		SystemClock = 16000000;
	}else
	{
		SystemClock = 8000000;
	}
	tmp = (RCC->CFGR >> 4 ) & 0xF;

	if(tmp < 0x08)
	{
		ahbp = 1;
	}else
	{
       ahbp = AHB_PreScaler[tmp-8];
	}

	tmp = (RCC->CFGR >> 13 ) & 0x7;
	if(tmp < 0x04)
	{
		apb2p = 1;
	}else
	{
		apb2p = APB1_PreScaler[tmp-4];
	}

	pclk2 = (SystemClock / ahbp )/ apb2p;

	return pclk2;
}

uint32 RCC_GetPLLOutputClock(void)
{

	return 0;
}
