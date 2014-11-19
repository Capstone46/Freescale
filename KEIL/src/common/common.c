/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      common.c
 * @author    MSG
 * @version   1.0.1.0
 * @date      Jun-20-2013
 * @brief     Common definitions.
 *
 * Revision History:
 *  1.	01/01/2010   AISG     Initially written
 *  2.	25/12/2013   B34185   Ported to Kinetis L (KL43 based)
 ******************************************************************************/
#include "common.h"

/******************************************************************************
 * System register file definition                                            *
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	__root __no_init volatile uint8 SystemRegisterFile[32] @ 0x40041000;
#elif defined(__ARMCC_VERSION)
	volatile uint8 SystemRegisterFile[32] __attribute__((section(".sysregfile"))) __attribute__((used));
#endif

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/

