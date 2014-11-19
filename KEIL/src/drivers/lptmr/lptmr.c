/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      lptmr.c
 * @version   1.0.2.0
 * @date      Jan-18-2013
 * @brief     Low-Power Timer (LPTMR) driver source code.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	01/08/2012   R55013   Ported to Kinetis M
 *  3.	17/01/2013   B34185   Ported to Kinetis L  
 ******************************************************************************/
#include "common.h"
#include "lptmr.h"

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static LPTMR_CALLBACK pCallbackLPTMR=NULL;

/******************************************************************************
 * interrupt function prototypes                                              *
 ******************************************************************************/
void lptmr_isr (void);

/******************************************************************************
 * Public function definitions                                                *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif

void LPTMR_Init (tLPTMR lptmr, uint16 compValue, uint8 ip, LPTMR_CALLBACK pCallback)
{ 
  if (pCallback != NULL) { pCallbackLPTMR = pCallback; NVIC_SetIsr(INT_LPTMR0,ip); }
  LPTMR0_PSR = lptmr.PSR; 
  LPTMR0_CMR = compValue;
  LPTMR0_CSR = (lptmr.CSR | LPTMR_CSR_TCF_MASK); 
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void lptmr_isr (void) 
{ 
  LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;  /* clear interrupt flag                   */
  /* call interrupt function                                                  */
  if (pCallbackLPTMR != (LPTMR_CALLBACK)NULL) { pCallbackLPTMR (); }
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
