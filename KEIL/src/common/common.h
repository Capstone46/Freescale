/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      common.h
 * @author    MSG
 * @version   1.0.1.0
 * @date      Jun-20-2013
 * @brief     Common macros header file.
 *
 * Revision History:
 *  1.	01/01/2010   AISG     Initially written
 *  2.	16/01/2013   B34185   Ported to Kinetis L
 *  2.	28/08/2013   B34185   Ported to Kinetis L -> KL43
 ******************************************************************************/
#ifndef __COMMON_H
#define __COMMON_H

/******************************************************************************
 * The basic data types                                                       *
 ******************************************************************************/
typedef unsigned char		uint8;  /*  8 bits */
typedef unsigned short int	uint16; /* 16 bits */
typedef unsigned long int	uint32; /* 32 bits */

typedef char			int8;   /*  8 bits */
typedef short int	        int16;  /* 16 bits */
typedef int		        int32;  /* 32 bits */

typedef volatile int8		vint8;  /*  8 bits */
typedef volatile int16		vint16; /* 16 bits */
typedef volatile int32		vint32; /* 32 bits */

typedef volatile uint8		vuint8;  /*  8 bits */
typedef volatile uint16		vuint16; /* 16 bits */
typedef volatile uint32		vuint32; /* 32 bits */

/******************************************************************************
 * Common macros and defines                                                  *
 ******************************************************************************/
#ifndef NULL
  #define NULL (void*)0
#endif

#define TRUE                        1
#define FALSE                       0

#define SET(mask)                       mask
#define CLR(mask)                       0
//#define REG_SetVal(reg,mask,val,shift)  { reg = ((reg & ~mask)|(val<<shift)); }
//#define REG_SetVal(reg,bf,val)  { reg=((reg&~reg##_##bf##_MASK)|(val<<reg##_##bf##_SHIFT)); }
#define REG_SetVal(reg,mask,x)  { reg=((reg&~mask##_MASK)|(x<<mask##_SHIFT)); }

#define REG_GetVal(reg,mask,x)  (reg&(x<<mask##_SHIFT))

/******************************************************************************
 * System register file declaration                                           *
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	extern __root __no_init volatile uint8 SystemRegisterFile[];
#elif defined(__ARMCC_VERSION)
	__attribute__((used)) extern volatile uint8 SystemRegisterFile[32] __attribute__((section(".sysregfile")));
#endif

/******************************************************************************
 * Include common utilities                                                   *
 ******************************************************************************/
#include "appconfig.h"
#include "device.h"

#if defined(__IAR_SYSTEMS_ICC__)
  //#include "intrinsics.h"
#endif
#include "startup.h"
#include "arm_cm0.h"
#include "arch_delay.h"

#endif /* __COMMON_H */
