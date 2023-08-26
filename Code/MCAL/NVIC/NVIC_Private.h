/*
 * ====================================================================================================================================
 *  Project		: NVIC_driver
 * 	File Name	: NVIC_Private.h
 *	Author		: Omar Anwar
 *  ===================================================================================================================================
 */
#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

#include "Std_Types.h"

#define NVIC_BASE_ADDRESS		(0xE000E100UL)

/*---------------------OFFSETS---------------------*/
#define NVIC_ISER_OFFSET		(0x000UL)
#define NVIC_ICER_OFFSET		(0x080UL)
#define NVIC_ISPR_OFFSET		(0x100UL)
#define NVIC_ICPR_OFFSET		(0x180UL)
#define NVIC_IABR_OFFSET		(0x200UL)
#define NVIC_IPR_OFFSET			(0x300UL)
#define NVIC_STIR_OFFSET		(0xE00UL)


typedef struct{
	uint32 ISERx[3];
}NVIC_ISER;

typedef struct{
	uint32 ICERx[3];
}NVIC_ICER;

typedef struct{
	uint32 ISPRx[3];
}NVIC_ISPR;

typedef struct{
	uint32 ICPRx[3];
}NVIC_ICPR;

typedef struct{
	uint32 IABRx[3];
}NVIC_IABR;

typedef struct{
	uint32 IPRx[20];
}NVIC_IPR;

typedef struct{
	uint32 STIR;
}NVIC_STIR;



#endif /* NVIC_PRIVATE_H_ */
