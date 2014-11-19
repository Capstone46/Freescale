/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      pit.c
 * @version   1.0.2.0
 * @date      Jan-18-2013
 * @brief     Periodic Interrupt Timer (PIT) driver source code.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	01/08/2012   R55013   Ported to Kinetis M
 *  3.	17/01/2013   B34185   Ported to Kinetis L
 ******************************************************************************/
#include "common.h"
#include "pit.h"

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static PIT_CALLBACK pCallbackPIT=NULL;

/******************************************************************************
 * interrupt function prototypes                                              *
 ******************************************************************************/
void pit_isr (void);

/******************************************************************************
 * Public function definitions                                                *
 ******************************************************************************/
void PIT0_CH0_Init  (tPIT_CH ch, uint32 value, uint8 ip, PIT_CALLBACK pCallback)
{
  if (pCallback != NULL)  
  { 
    pCallbackPIT = pCallback; 
    NVIC_SetIsr(INT_PIT,ip); 
  }
  else
  { 
    pCallbackPIT = NULL; 
    NVIC_ClrIsr(INT_PIT); 
  }
  PIT_LDVAL0  = value;
  PIT_TFLG0   = PIT_TFLG_TIF_MASK;   /* clear interrupt flag                 */
  PIT_TCTRL0  = ch.TCTRL;
  PIT_MCR    &= ~0x0002;             /* clear MDIS bit                       */  
}

void PIT0_CH1_Init  (tPIT_CH ch, uint32 value, uint8 ip, PIT_CALLBACK pCallback)
{
  if (pCallback != NULL)  
  { 
    pCallbackPIT = pCallback; 
    NVIC_SetIsr(INT_PIT,ip); 
  }
  else
  { 
    pCallbackPIT = NULL; 
    NVIC_ClrIsr(INT_PIT); 
  }
  PIT_LDVAL1  = value;
  PIT_TFLG1   = PIT_TFLG_TIF_MASK;   /* clear interrupt flag                 */
  PIT_TCTRL1  = ch.TCTRL;
  PIT_MCR    &= ~0x0002;             /* clear MDIS bit                       */
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void pit_isr (void) 
{ 
  /* CH0 interrupt                                                            */
  if (PIT_TFLG0 == PIT_TFLG_TIF_MASK)
  {
    PIT_TFLG0 = PIT_TFLG_TIF_MASK;   /* clear interrupt flag                  */
    if (pCallbackPIT != (PIT_CALLBACK)NULL) 
      pCallbackPIT (PIT0CH0_CALLBACK);
  }

  /* CH1 interrupt                                                            */
  if (PIT_TFLG1 == PIT_TFLG_TIF_MASK)
  {
    PIT_TFLG1 = PIT_TFLG_TIF_MASK;   /* clear interrupt flag                  */
    if (pCallbackPIT != (PIT_CALLBACK)NULL) 
      pCallbackPIT (PIT0CH1_CALLBACK);
  }
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
