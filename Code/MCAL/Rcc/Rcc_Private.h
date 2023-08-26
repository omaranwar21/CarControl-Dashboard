/**
 * Rcc_Private.h
 *
 *  Created on: Sun Mar 26 2023
 *  Author    : Abdullah Darwish
 */

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

#include "Std_Types.h"
#include "Utils.h"

#define RCC_BASE_ADDR 0x40023800

typedef struct
{
    __IO uint32 CR;
    __IO uint32 PLLCFGR;
    __IO uint32 CFGR;
    __IO uint32 CIR;
    __IO uint32 AHB1RSTR;
    __IO uint32 AHB2RSTR;
    uint32 RESERVED_1[2];
    __IO uint32 APB1RSTR;
    __IO uint32 APB2RSTR;
    uint32 RESERVED_2[2];
    __IO uint32 AHB1ENR;
    __IO uint32 AHB2ENR;
    uint32 RESERVED_3[2];
    __IO uint32 APB1ENR;
    __IO uint32 APB2ENR;
    uint32 RESERVED_4[2];
    __IO uint32 AHB1LPENR;
    __IO uint32 AHB2LPENR;
    uint32 RESERVED_5[2];
    __IO uint32 APB1LPENR;
    __IO uint32 APB2LPENR;
    uint32 RESERVED_6[2];
    __IO uint32 BDCR;
    __IO uint32 CSR;
    uint32 RESERVED_7[2];
    __IO uint32 SSCGR;
    __IO uint32 PLLI2SCFGR;
    uint32 RESERVED_8[1];
    __IO uint32 DCKCFGR;
}RCC_typeDef;


#endif /* RCC_PRIVATE_H */
