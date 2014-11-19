/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      lpuart.c
 * @version   1.0.7.0
 * @date      Feb-13-2013
 * @brief     Low power Universal Asynchronous Receiver/Transmitter (UART)  
 *            driver source code.
 *
 * Revision History:
 *  1.	07/01/2014   B34185   Initially written
 ******************************************************************************/
#include "common.h"
#include "lpuart.h"

#if (defined (MCU_MKL43Z256))
/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static LPUART_CALLBACK volatile pCallbackLPUART0=NULL;
static LPUART_CALLBACK volatile pCallbackLPUART1=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void lpuart0_isr (void);
void lpuart1_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
   
void LPUART0_Init (tLPUART sci, uint8 ip, LPUART_CALLBACK pCallback)
{   
  LPUART0_CTRL &= ~(LPUART_CTRL_TE_MASK|LPUART_CTRL_RE_MASK );  /* disable lpuart operation */
  if (pCallback != NULL) { pCallbackLPUART0 = pCallback; NVIC_SetIsr(INT_LPUART0,ip);} 
  else { NVIC_ClrIsr (INT_LPUART0);}
  LPUART0_BAUD     = sci.BAUD;
  LPUART0_MATCH    = sci.MATCH;
  LPUART0_STAT    = sci.STAT;
  LPUART0_CTRL     = sci.CTRL;                      /* enable uart operation  */
  LPUART_ClrFlags(LPUART0, STAT_ALL);
}

void LPUART1_Init (tLPUART sci, uint8 ip, LPUART_CALLBACK pCallback)
{   
  LPUART1_CTRL &= ~(LPUART_CTRL_TE_MASK|LPUART_CTRL_RE_MASK );  /* disable lpuart operation */
  if (pCallback != NULL) { pCallbackLPUART1 = pCallback; NVIC_SetIsr(INT_LPUART1,ip);} 
  else { NVIC_ClrIsr (INT_LPUART0);}
  LPUART1_BAUD     = sci.BAUD;
  LPUART1_MATCH    = sci.MATCH;
  LPUART1_STAT    = sci.STAT;
  LPUART1_CTRL     = sci.CTRL;                      /* enable uart operation  */
  LPUART_ClrFlags(LPUART1, STAT_ALL);
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void lpuart0_isr (void)
{
  register vuint32 temp;
 
  if (pCallbackLPUART0 != (LPUART_CALLBACK)NULL) 
  { 
    temp = LPUART0_STAT & (LPUART0_CTRL & (LPUART_CTRL_RIE_MASK|                \
                           LPUART_CTRL_TCIE_MASK|LPUART_CTRL_TIE_MASK)); 
    if(temp & LPUART_STAT_RDRF_MASK)
    { 
      pCallbackLPUART0 (LPUART_RX_CALLBACK, temp);
    }
    if(temp & (LPUART_STAT_TC_MASK|LPUART_STAT_TDRE_MASK))
    { 
      pCallbackLPUART0 (LPUART_TX_CALLBACK, temp); 
    }
    temp = LPUART0_STAT & (LPUART0_CTRL & (LPUART_CTRL_PEIE_MASK|               \
                           LPUART_CTRL_FEIE_MASK|LPUART_CTRL_NEIE_MASK|         \
                           LPUART_CTRL_ORIE_MASK));
    if(temp != 0)
    { 
      pCallbackLPUART0 (LPUART_ER_CALLBACK, temp);
    }     
  }  
}

void lpuart1_isr (void)
{
  register vuint32 temp;
  
  if (pCallbackLPUART1 != (LPUART_CALLBACK)NULL) 
  { 
    temp = LPUART1_STAT & (LPUART1_CTRL & (LPUART_CTRL_RIE_MASK|                \
                           LPUART_CTRL_TCIE_MASK|LPUART_CTRL_TIE_MASK)); 
    if(temp & LPUART_STAT_RDRF_MASK)
    { 
      pCallbackLPUART1 (LPUART_RX_CALLBACK, temp); 
    }
    if(temp & (LPUART_STAT_TC_MASK|LPUART_STAT_TDRE_MASK))
    { 
      pCallbackLPUART1 (LPUART_TX_CALLBACK, temp); 
    }
    
    temp = LPUART1_STAT & (LPUART1_CTRL & (LPUART_CTRL_PEIE_MASK|               \
                           LPUART_CTRL_FEIE_MASK|LPUART_CTRL_NEIE_MASK|           \
                           LPUART_CTRL_ORIE_MASK));
    if(temp != 0)                                 
    { 
      pCallbackLPUART1 (LPUART_ER_CALLBACK, temp); 
    }     
  }  
}

#endif

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/

