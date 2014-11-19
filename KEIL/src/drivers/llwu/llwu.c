/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      llwu.c
 * @version   1.0.4.0
 * @date      Jan-18-2013
 * @brief     Low-Leakage Wakeup Unit (LLWU) driver source code.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	01/08/2012   R55013   Ported to Kinetis M 
 *  3.	17/01/2012   B34185   Ported to Kinetis L
 ******************************************************************************/
#include "common.h"
#include "llwu.h"

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static LLWU_CALLBACK volatile pCallbackLLWU=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void llwu_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
/***************************************************************************//*!
 * @brief   LLWU initialization function.
 * @param   llwu      - LLWU module configuration structure passed by value: 
 *                      LLWU_MODULE_CONFIG1.
 * @param   ip        - interrupt priority 0..15
 * @param   pCallback - pointer to LLWU_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
void LLWU_Init (tLLWU llwu, uint8 ip, LLWU_CALLBACK pCallback)
{
  /* interrupt configuration                                                  */
  if (pCallback != NULL) { pCallbackLLWU = pCallback; }
  NVIC_SetIsr(INT_LLWU,ip);
  /* register setting                                                         */
  LLWU_PE1 = llwu.PE1;
  LLWU_PE2 = llwu.PE2;
  LLWU_PE3 = llwu.PE3;
  LLWU_PE4 = llwu.PE4;
  LLWU_FILT1 = llwu.FILT1;
  LLWU_FILT2 = llwu.FILT2;
  LLWU_ME  = llwu.ME;  
  /* clear flags                                                              */
  LLWU_ClrFlags(WUFALL); 
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void llwu_isr (void) 
{ 
  register uint32 tmp = ((uint32)LLWU_F3<<16)|((uint32)LLWU_F2<<8)|(uint32)LLWU_F1;
  /* clear flags                                                              */
  LLWU_ClrFlags(WUFALL);
  if (pCallbackLLWU != (LLWU_CALLBACK)NULL) { pCallbackLLWU (tmp); }
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
