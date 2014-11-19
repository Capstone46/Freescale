/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      uart.c
 * @version   1.0.7.0
 * @date      Feb-13-2013
 * @brief     Universal Asynchronous Receiver/Transmitter (UART) driver source 
 *            code.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	01/08/2012   B34185   Ported to Kinetis L  
 ******************************************************************************/
#include "common.h"
#include "uart.h"

 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif   
   
#if (defined (MCU_MKL43Z256))
/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static UART_CALLBACK volatile pCallbackUART=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void uart_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
void UART_KLx3_Init (tUART sci, uint8 ip, UART_CALLBACK pCallback)
{   
  UART0_C2 &= ~(UART_C2_TE_MASK|UART_C2_RE_MASK );  /* disable uart operation */
  if (pCallback != NULL) { pCallbackUART = pCallback; NVIC_SetIsr(INT_UART0_FLEXIO,ip);} 
  else { NVIC_ClrIsr (INT_UART0_FLEXIO);}
  UART0_BDH     = sci.BDH;
  UART0_BDL     = sci.BDL;
  UART0_C1      = sci.C1;
  UART0_S2      = sci.S2;
  UART0_C3      = sci.C3;
  UART0_MA1     = sci.MA1;
  UART0_MA2     = sci.MA2;
  UART0_C4      = sci.C4;
  UART0_C2      = sci.C2;                           /* enable uart operation  */
  UART_ClrFlags(UART0, 0xC01F);
}

void UART0_KLx3_Init (tUART sci, uint8 ip, UART_CALLBACK pCallback)
{   
  UART0_C2 &= ~(UART_C2_TE_MASK|UART_C2_RE_MASK );  /* disable uart operation */
  if (pCallback != NULL) { pCallbackUART = pCallback; NVIC_SetIsr(INT_UART0_FLEXIO,ip);} 
  else { NVIC_ClrIsr (INT_UART0_FLEXIO);}
  UART0_BDH     = sci.BDH;
  UART0_BDL     = sci.BDL;
  UART0_C1      = sci.C1;
  UART0_S2      = sci.S2;
  UART0_C3      = sci.C3;
  UART0_MA1     = sci.MA1;
  UART0_MA2     = sci.MA2;
  UART0_C4      = sci.C4;
  UART0_C2      = sci.C2;                           /* enable uart operation  */
  UART_ClrFlags(UART0, 0xC01F);
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void uart_isr (void)
{
  register vuint8 temp;
 
  if (pCallbackUART != (UART_CALLBACK)NULL) 
  { 
    temp = UART0_S1 & (UART0_C2 & (UART_C2_RIE_MASK|UART_C2_TCIE_MASK|          \
                                   UART_C2_TIE_MASK)); 
    if(temp & UART_S1_RDRF_MASK)
    { 
      pCallbackUART (RX_CALLBACK, temp);
    }
    if(temp & (UART_S1_TC_MASK|UART_S1_TDRE_MASK))
    { 
      pCallbackUART (TX_CALLBACK, temp); 
    }
    temp = UART0_S1 & (UART0_C3 & (UART_C3_PEIE_MASK|UART_C3_FEIE_MASK|         \
                                   UART_C3_NEIE_MASK|UART_C3_ORIE_MASK));
    if(temp != 0) 
    { 
      pCallbackUART (ER_CALLBACK, temp); 
    }     
  }  
}
#endif

#if (defined (MCU_MKL46Z256))
/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static UART_CALLBACK volatile pCallbackUART0=NULL;
static UART_CALLBACK volatile pCallbackUART1=NULL;
static UART_CALLBACK volatile pCallbackUART2=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void uart0_isr (void);
void uart1_isr (void);
void uart2_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
void UART0_Init (tUART sci, uint8 ip, UART_CALLBACK pCallback)
{   
  UART0_C2 &= ~(UART_C2_TE_MASK|UART_C2_RE_MASK );  /* disable uart operation */
  if (pCallback != NULL) { pCallbackUART0 = pCallback; NVIC_SetIsr(INT_UART0,ip);} 
  else { NVIC_ClrIsr (INT_UART0);}
  UART0_BDH     = sci.BDH;
  UART0_BDL     = sci.BDL;
  UART0_C1      = sci.C1;
  UART0_S2      = sci.S2;
  UART0_C3      = sci.C3;
  UART0_MA1     = sci.MA1;
  UART0_MA2     = sci.MA2;
  UART0_C4      = sci.C4;
  UART0_C2      = sci.C2;                           /* enable uart operation  */
  UART_ClrFlags(UART0, 0xC01F);
}

void UART1_Init (tUART sci, uint8 ip, UART_CALLBACK pCallback)
{   
  UART1_C2 &= ~(UART_C2_TE_MASK|UART_C2_RE_MASK );  /* disable uart operation */
  if (pCallback != NULL) { pCallbackUART1 = pCallback; NVIC_SetIsr(INT_UART1,ip); }
  else { NVIC_ClrIsr (INT_UART1);}
  UART1_BDH     = sci.BDH;
  UART1_BDL     = sci.BDL;
  UART1_C1      = sci.C1;
  UART1_S2      = sci.S2;
  UART1_C3      = sci.C3;
  UART1_C4      = sci.C4; // UART1 has different contains of this regster in comparison to UART0
  UART1_C2      = sci.C2;                           /* enable uart operation  */
  UART_ClrFlags(UART1, 0xC01F);
}

void UART2_Init (tUART sci, uint8 ip, UART_CALLBACK pCallback)
{   
  UART2_C2 &= ~(UART_C2_TE_MASK|UART_C2_RE_MASK );  /* disable uart operation */
  if (pCallback != NULL) { pCallbackUART2 = pCallback; NVIC_SetIsr(INT_UART2,ip); }
  else { NVIC_ClrIsr (INT_UART2);}
  UART2_BDH     = sci.BDH;
  UART2_BDL     = sci.BDL;
  UART2_C1      = sci.C1;
  UART2_S2      = sci.S2;
  UART2_C3      = sci.C3;
  UART2_C4      = sci.C4; // UART2 has different contains of this regster in comparison to UART0
  UART2_C2      = sci.C2;                           /* enable uart operation  */
  UART_ClrFlags(UART2, 0xC01F);
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void uart0_isr (void)
{
  register vuint8 temp;
 
  if (pCallbackUART0 != (UART_CALLBACK)NULL) 
  { 
    temp = UART0_S1 & (UART0_C2 & (UART_C2_RIE_MASK|UART_C2_TCIE_MASK|          \
                                   UART_C2_TIE_MASK)); 
    if(temp & UART_S1_RDRF_MASK)
    { 
      pCallbackUART0 (RX_CALLBACK, temp);
    }
    if(temp & (UART_S1_TC_MASK|UART_S1_TDRE_MASK))
    { 
      pCallbackUART0 (TX_CALLBACK, temp); 
    }
    temp = UART0_S1 & (UART0_C3 & (UART_C3_PEIE_MASK|UART_C3_FEIE_MASK|         \
                                   UART_C3_NEIE_MASK|UART_C3_ORIE_MASK));
    if(temp != 0) 
    { 
      pCallbackUART0 (ER_CALLBACK, temp); 
    }     
  }  
}

void uart1_isr (void)
{
  register vuint8 temp;
  
  if (pCallbackUART1 != (UART_CALLBACK)NULL) 
  { 
    temp = UART1_S1 & (UART1_C2 & (UART_C2_RIE_MASK|UART_C2_TCIE_MASK|UART_C2_TIE_MASK)); 
    if(temp &                   UART_S1_RDRF_MASK){ pCallbackUART1 (RX_CALLBACK, temp); }
    if(temp & (UART_S1_TC_MASK|UART_S1_TDRE_MASK)){ pCallbackUART1 (TX_CALLBACK, temp); }
    
    temp = UART1_S1 & (UART1_C3 & (UART_C3_PEIE_MASK|UART_C3_FEIE_MASK|UART_C3_NEIE_MASK| \
                                   UART_C3_ORIE_MASK));
    if(temp != 0)                                 { pCallbackUART1 (ER_CALLBACK, temp); }     
  }  
}

void uart2_isr (void)
{
  register vuint8 temp;
  
  if (pCallbackUART2 != (UART_CALLBACK)NULL) 
  { 
    temp = UART2_S1 & (UART2_C2 & (UART_C2_RIE_MASK|UART_C2_TCIE_MASK|UART_C2_TIE_MASK)); 
    if(temp &                   UART_S1_RDRF_MASK){ pCallbackUART2 (RX_CALLBACK, temp); }
    if(temp & (UART_S1_TC_MASK|UART_S1_TDRE_MASK)){ pCallbackUART2 (TX_CALLBACK, temp); }
    
    temp = UART2_S1 & (UART2_C3 & (UART_C3_PEIE_MASK|UART_C3_FEIE_MASK|UART_C3_NEIE_MASK| \
                                   UART_C3_ORIE_MASK));
    if(temp != 0)                                 { pCallbackUART2 (ER_CALLBACK, temp); }     
  }  
}

#endif
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/

