/*
 * ====================================================================================================================================
 *  Project		: NVIC_driver
 * 	File Name	: NVIC.c
 *	Author		: Omar Anwar
 *  ===================================================================================================================================
 */

#include "NVIC.h"
#include "Bit_Operations.h"
#include "Gpio.h"

void NVIC_LineEnable(NVIC_Lines line){
	uint8 iserReg = line/32;
	uint8 iserIndex = line%32;

	SET_BIT(NVIC_ISERx->ISERx[iserReg], iserIndex);
}

void NVIC_LineDisable(NVIC_Lines line){
	uint8 icerReg = line/32;
	uint8 icerIndex = line%32;

	SET_BIT(NVIC_ICERx->ICERx[icerReg], icerIndex);
}

NVIC_Flag NVIC_SetPending(NVIC_Lines line){
	uint8 isprReg = line/32;
	uint8 isprIndex = line%32;
	if (READ_BIT(NVIC_ISERx->ISERx[isprReg], isprIndex)) {
		return NVIC_NOK;
	}

	SET_BIT(NVIC_ISPRx->ISPRx[isprReg], isprIndex);

	return NVIC_OK;
}

NVIC_Flag NVIC_ClearPending(NVIC_Lines line){
	uint8 icprReg = line/32;
	uint8 icprIndex = line%32;

	if (READ_BIT(NVIC_ISERx->ISERx[icprReg], icprIndex)) {
		return NVIC_NOK;
	}

	SET_BIT(NVIC_ICPRx->ICPRx[icprReg], icprIndex);
	return NVIC_OK;
}

NVIC_Flag NVIC_CheckIsPending(NVIC_Lines line){
	uint8 isprReg = line/32;
	uint8 isprIndex = line%32;

	return (NVIC_Flag)READ_BIT(NVIC_ISPRx->ISPRx[isprReg], isprIndex);

}

NVIC_Flag NVIC_CheckIsActive(NVIC_Lines line){
	uint8 iabrReg = line/32;
	uint8 iabrIndex = line%32;

	return (NVIC_Flag)READ_BIT(NVIC_IABRx->IABRx[iabrReg], iabrIndex);
}

void NVIC_PrioritySetting(NVIC_Lines line, uint8 priority){
	uint8 IPR_number = line/4;
	uint8 byte_offset = line%4;

	uint8* pIPRx = (uint8*)&(NVIC_IPRx->IPRx[IPR_number]);


	pIPRx += byte_offset;

	*pIPRx = (priority << 4);
}

