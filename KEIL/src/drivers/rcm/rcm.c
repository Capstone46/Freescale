/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      rcm.c
 * @version   1.0.2.0
 * @date      Jan-18-2013
 * @brief     Reset control module (RCM) driver source code.
 *
 * Revision History:
 *  1.	09/01/2013   R55013   Initialy inherited from smc driver 
 ******************************************************************************/
#include "common.h"
#include "rcm.h"

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
void RCM_Init (tRCM rcm) 
{ 
  RCM_RPFC = rcm.RPFC;
  RCM_RPFW = rcm.RPFW; 
#if (defined (MCU_MKL43Z256))
  RCM_FM = rcm.FM;
  RCM_MR = 0x12; // clears flags indicate the boot source
#endif
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
