/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      smc.c
 * @version   1.0.2.0
 * @date      Jan-18-2013
 * @brief     System Mode Controller (SMC) driver source code.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.  01/01/2011   B12615   Updated 
 *  3.	17/01/2013   B34185   Ported to Kinetis L  
 ******************************************************************************/
#include "common.h"
#include "smc.h"

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
/***************************************************************************//*!
 * @brief   SMC initialization function.
 * @param   smc      - SMC module configuration structure passed by value: 
 *                     SMC_MODULE_CONFIG1
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
void SMC_Init (tSMC_INIT smc) { SMC_PMPROT = smc.PMPROT; }
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
