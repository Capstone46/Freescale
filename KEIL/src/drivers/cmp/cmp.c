/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      cmp.c
 * @version   1.0.2.0
 * @date      Jan-17-2013
 * @brief     Analog comparator (CMP) driver source code.
 *
 * Revision History:
 *  1.	15/01/2013   B34185   Initially written for Kinetis L
 *  2.	26/03/2014   B34185   comparator callback re-defined
 ******************************************************************************/
#include "common.h"
#include "cmp.h"

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static CMP_CALLBACK volatile pCallbackCMP0=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void cmp0_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
void CMP0_Init (tCMP cmp, uint8 psel, uint8 nsel, uint8 ip, CMP_CALLBACK pCallback)
{
  if (pCallback != NULL) 
  { 
    pCallbackCMP0 = pCallback;
    NVIC_SetIsr(INT_CMP0,ip);
  } 
  CMP0_CR0   = cmp.CR0;
  CMP0_CR1   = cmp.CR1;
  CMP0_FPR   = cmp.FPR;
  CMP0_SCR   = cmp.SCR;
  CMP0_DACCR = cmp.DACCR;
  CMP0_MUXCR = (uint8)((psel<<3)|nsel);
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void cmp0_isr (void) 
{
  if (pCallbackCMP0 != (CMP_CALLBACK)NULL) 
  {
    /* process CMP0 CFR interrupt                                    */  
    if ((CMP0_SCR & CMP_SCR_IER_MASK) && (CMP0_SCR & CMP_SCR_CFR_MASK))
    {
      CMP0_SCR = (CMP0_SCR&(~CMP_SCR_CFR_MASK))|CMP_SCR_CFR_MASK;
      pCallbackCMP0 (CMP_RE_CALLBACK);
    }
    /* process CMP0 CFF interrupt                                    */  
    if ((CMP0_SCR & CMP_SCR_IEF_MASK) && (CMP0_SCR & CMP_SCR_CFF_MASK))
    {
      CMP0_SCR = (CMP0_SCR&(~CMP_SCR_CFF_MASK))|CMP_SCR_CFF_MASK;
      pCallbackCMP0 (CMP_FE_CALLBACK);
    }
  } 
}

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/

