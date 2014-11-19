/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      dac.c
 * @version   1.0.2.0
 * @date      Jan-17-2013
 * @brief     Digital to Analog converter (DAC) driver source code.
 *
 * Revision History:
 *  1.	15/01/2013   B34185   Initially written for Kinetis L
 *  2.	26/03/2014   B34185   dac callback re-defined
 ******************************************************************************/
#include "common.h"
#include "dac.h"

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static DAC_CALLBACK volatile pCallbackDAC0=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void dac0_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
void DAC0_Init (tDAC dac, uint16 data, uint8 ip, DAC_CALLBACK pCallback)
{
  if (pCallback != NULL) 
  {
    pCallbackDAC0 = pCallback;
    NVIC_SetIsr(INT_DAC0,ip);
  } 
  DAC0_DAT0L    = (uint8)(0x00FF&data);
  DAC0_DAT0H    = (uint8)(0x000F&(data>>8));
  DAC0_DAT1L    = (uint8)data;
  DAC0_DAT1H    = (uint8)data;
  DAC0_SR       = dac.SR;
  DAC0_C0       = dac.C0;
  DAC0_C1       = dac.C1;
  DAC0_C2       = dac.C2;
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void dac0_isr (void) 
{
  if (pCallbackDAC0 != (DAC_CALLBACK)NULL) 
  {
    /* process DAC0 TOP flag interrupt                                    */  
    if ((DAC0_SR & CMP_SCR_IER_MASK) && (DAC0_SR & DAC_SR_DACBFRPTF_MASK))
    {
      pCallbackDAC0 (DAC_TOP_CALLBACK);
    }
    /* process CMP0 BOTTOM flag interrupt                                    */  
    if ((DAC0_SR & CMP_SCR_IEF_MASK) && (DAC0_SR & DAC_SR_DACBFRPBF_MASK))
    {
      pCallbackDAC0 (DAC_BOTTOM_CALLBACK);
    }
  } 
}

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/

