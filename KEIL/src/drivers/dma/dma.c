/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      dma.c
 * @author    B34185
 * @version   1.0.1.0
 * @date      Aug-16-2012
 * @brief     DMA driver implementation.
 * @par       Driver example:
 * @include   tpm2_test\tpm2_test.c 
 * @par       Interrupt vectors and peripherals configuration(s):
 * @include   tpm2_test\appconfig.h		
 ******************************************************************************/
#include "common.h"
#include "dma.h"

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static DMA_CALLBACK volatile pCallbackDMA0=NULL;
static DMA_CALLBACK volatile pCallbackDMA1=NULL;
static DMA_CALLBACK volatile pCallbackDMA2=NULL;
static DMA_CALLBACK volatile pCallbackDMA3=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void dma0_isr (void);
void dma1_isr (void);
void dma2_isr (void);
void dma3_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
   
void DMAMUX0_CH0_Init(tDMAMUX dmamux)
{
  DMAMUX0_CHCFG0 = dmamux.MUX_CHCFG;
}

void DMAMUX0_CH1_Init(tDMAMUX dmamux)
{
  DMAMUX0_CHCFG1 = dmamux.MUX_CHCFG;
} 

void DMAMUX0_CH2_Init(tDMAMUX dmamux)
{
  DMAMUX0_CHCFG2 = dmamux.MUX_CHCFG;
} 

void DMAMUX0_CH3_Init(tDMAMUX dmamux)
{
  DMAMUX0_CHCFG3 = dmamux.MUX_CHCFG;
}
   
void DMA0_Init(tDMA dma, uint32* sard, uint32* dadr, uint8 ip, DMA_CALLBACK pCallback)
{
  uint32 u32Temp;
  
  u32Temp = DMAMUX0_CHCFG0;
  DMAMUX0_CHCFG0 = 0x0;
  if (pCallback != NULL) { pCallbackDMA0 = pCallback; NVIC_SetIsr(INT_DMA0,ip);}
  DMA_SAR0 = (uint32)sard;
  DMA_DAR0 = (uint32)dadr;
  DMA_DCR0 = dma.DCR;
  DMA_DSR_BCR0 = dma.BCR;
  DMAMUX0_CHCFG0 = u32Temp;
}

void DMA1_Init(tDMA dma, uint32* sard, uint32* dadr, uint8 ip, DMA_CALLBACK pCallback)
{
  uint32 u32Temp;
  
  u32Temp = DMAMUX0_CHCFG1;
  DMAMUX0_CHCFG1 = 0x0;
  if (pCallback != NULL) { pCallbackDMA1 = pCallback; NVIC_SetIsr(INT_DMA1,ip);}
  DMA_SAR1 = (uint32)sard;
  DMA_DAR1 = (uint32)dadr;
  DMA_DCR1 = dma.DCR;
  DMA_DSR_BCR1 = dma.BCR;
  DMAMUX0_CHCFG1 = u32Temp;
}

void DMA2_Init(tDMA dma, uint32* sard, uint32* dadr, uint8 ip, DMA_CALLBACK pCallback)
{
  uint32 u32Temp;
  
  u32Temp = DMAMUX0_CHCFG2;
  DMAMUX0_CHCFG2 = 0x0;
  if (pCallback != NULL) { pCallbackDMA2 = pCallback; NVIC_SetIsr(INT_DMA2,ip);}
  DMA_SAR2 = (uint32)sard;
  DMA_DAR2 = (uint32)dadr;
  DMA_DCR2 = dma.DCR;
  DMA_DSR_BCR2 = dma.BCR;
  DMAMUX0_CHCFG2 = u32Temp;
}

void DMA3_Init(tDMA dma, uint32* sard, uint32* dadr, uint8 ip, DMA_CALLBACK pCallback)
{
  uint32 u32Temp;
  
  u32Temp = DMAMUX0_CHCFG3;
  DMAMUX0_CHCFG3 = 0x0;
  if (pCallback != NULL) { pCallbackDMA3 = pCallback; NVIC_SetIsr(INT_DMA3,ip);}
  DMA_SAR3 = (uint32)sard;
  DMA_DAR3 = (uint32)dadr;
  DMA_DCR3 = dma.DCR;
  DMA_DSR_BCR3 = dma.BCR;
  DMAMUX0_CHCFG3 = u32Temp;
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void dma0_isr (void) 
{ 
  if (pCallbackDMA0 != (DMA_CALLBACK)NULL) 
  { 
    if (DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK) 
    { 
      DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
      pCallbackDMA0 (CH0_CALLBACK);
    }
  }
}

void dma1_isr (void) 
{ 
  if (pCallbackDMA1 != (DMA_CALLBACK)NULL) 
  { 
    if (DMA_DSR_BCR1 & DMA_DSR_BCR_DONE_MASK) 
    { 
      DMA_DSR_BCR1 |= DMA_DSR_BCR_DONE_MASK;
      pCallbackDMA1 (CH1_CALLBACK);
    }
  }
}

void dma2_isr (void) 
{ 
  if (pCallbackDMA2 != (DMA_CALLBACK)NULL) 
  { 
    if (DMA_DSR_BCR2 & DMA_DSR_BCR_DONE_MASK) 
    { 
      DMA_DSR_BCR2 |= DMA_DSR_BCR_DONE_MASK;
      pCallbackDMA2 (CH2_CALLBACK);
    }
  }
}

void dma3_isr (void) 
{ 
  if (pCallbackDMA3 != (DMA_CALLBACK)NULL) 
  { 
    if (DMA_DSR_BCR3 & DMA_DSR_BCR_DONE_MASK) 
    { 
      DMA_DSR_BCR3 |= DMA_DSR_BCR_DONE_MASK;
      pCallbackDMA3 (CH3_CALLBACK);
    }
  }
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
