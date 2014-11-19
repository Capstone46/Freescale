/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      sim.c
 * @version   1.0.2.0
 * @date      Jan-18-2013
 * @brief     System Integration Module (SIM) driver source code.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	17/01/2013   B34185   Ported to Kinetis L
 ******************************************************************************/
#include "common.h"
#include "sim.h"

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 
/***************************************************************************//*!
 * @brief   SIM module initialization function.
 * @param   sim     - SIM module configuration structure passed by value:\n 
 *                    SIM_MODULE_CONFIG\n
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
void SIM_Init (tSIM sim)
{
  SIM_SOPT1CFG= sim.SOPT1CFG;
  if (!(sim.SOPT1&SIM_SOPT1_USBREGEN_MASK))
    SIM_SOPT1CFG |= SIM_SOPT1CFG_URWE_MASK;
  SIM_SOPT1   = sim.SOPT1;
  SIM_SOPT2   = sim.SOPT2;
  SIM_SOPT4   = sim.SOPT4;
  SIM_SOPT5   = sim.SOPT5;
  SIM_SOPT7   = sim.SOPT7;
  SIM_SCGC4   = sim.SCGC4;
  SIM_SCGC5   = sim.SCGC5;
  SIM_SCGC6   = sim.SCGC6;
  SIM_SCGC7   = sim.SCGC7;
  SIM_CLKDIV1 = sim.CLKDIV1;
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
