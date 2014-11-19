/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      pmc.c
 * @version   1.0.3.0
 * @date      Jan-18-2013
 * @brief     PMC driver header file.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	01/08/2012   R55013   Ported to Kinetis M  
 *  3.	15/01/2013   B34185   Re-written to Kinetis L
******************************************************************************/
#include "common.h"
#include "pmc.h"

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static PMC_CALLBACK volatile pCallbackPMC=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void pmc_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
/***************************************************************************//*!
 * @brief   PMC initialization function.
 * @param   pmc       - PMC module configuration structure passed by value: 
 *                      PMC_MODULE_CONFIG1.
 * @param   ip        - interrupt priority 0..15
 * @param   pCallback - pointer to PMC_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
void PMC_Init (tPMC pmc, uint8 ip, PMC_CALLBACK pCallback)
{
  if (pCallback != NULL) { pCallbackPMC = pCallback; }
  NVIC_SetIsr(INT_PMC,ip);
  PMC_LVDSC1 = (pmc.LVDSC1 | PMC_LVDSC1_LVDACK_MASK);
  PMC_LVDSC2 = (pmc.LVDSC2 | PMC_LVDSC2_LVWACK_MASK);
  PMC_REGSC  = pmc.REGSC;
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void pmc_isr (void) 
{ 
  if (pCallbackPMC != (PMC_CALLBACK)NULL)
  {
    if ((PMC_LVDSC1 & PMC_LVDSC1_LVDF_MASK) && (PMC_LVDSC1 & PMC_LVDSC1_LVDIE_MASK))
    {
      PMC_LVDSC1 |= PMC_LVDSC1_LVDACK_MASK;   /* clear interrupt flag         */
      pCallbackPMC (LVD_CALLBACK);
    }
    if ((PMC_LVDSC2 & PMC_LVDSC2_LVWF_MASK) && (PMC_LVDSC2 & PMC_LVDSC2_LVWIE_MASK))
    {
      PMC_LVDSC2 |= PMC_LVDSC2_LVWACK_MASK;  /* clear interrupt flag          */
      pCallbackPMC (LVW_CALLBACK);
    }
  }
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
