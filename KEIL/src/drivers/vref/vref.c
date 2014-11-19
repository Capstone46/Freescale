/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      vref.c
 * @version   1.0.1.0
 * @date      Jun-20-2013
 * @brief     Voltage reference (VREF) driver source file.
 *
 * Revision History:
 *  1.	15/05/2013   B34185   Initially written for Kinetis K
 ******************************************************************************/
#include "common.h"
#include "vref.h"


#if (defined (MCU_MKL43Z256))
/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
/***************************************************************************//*!
 * @brief   VREF initialization function.
 ******************************************************************************/
void VREF_Init (tVREF vref)
{     
  VREF_SC    = VREF_SC_VREFEN_MASK;   /* enable module and keep mode 0        */           
  /* check and wait until reference is stable                                 */
  if (vref.SC & VREF_SC_VREFEN_MASK)  
    while (!(VREF_SC & VREF_SC_VREFST_MASK));
  VREF_SC    = vref.SC;               /* write control register               */   
}

#endif
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
