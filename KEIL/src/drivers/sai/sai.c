/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      sai.c
 * @version   1.0.7.0
 * @date      Feb-13-2013
 * @brief     SAI source code.
 *
 * Revision History:
 *  1.	xx/xx/xxxxx   Bxxxxx   Initially written
 ******************************************************************************/
#include "common.h"
#include "sai.h"

#if (defined (MCU_MKL43Z256))
/* workaround for fixed 24.0MHz MCLK and 16-bit data */
/* (((12.0MHz/SampleRate)/BIT_DEPTH)/2)-1 */
#if I2S_BIT_DEPTH == 16 
const SAMPLES_DESCR samples_descr[] = 
{
  {8000, MCLK_IX0, 46},
  {11025, MCLK_IX0, 33},
  {12000, MCLK_IX0, 30},
  {16000, MCLK_IX0, 22},
  {22050, MCLK_IX0, 16},
  {24000, MCLK_IX0, 15},
  {32000, MCLK_IX0, 11},
  {44100, MCLK_IX0, 8},
  {48000, MCLK_IX0, 7},
  {0, 0, 0}
};

#else
#error Unsupported I2S_BIT_DEPTH!
#endif

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static SAI_CALLBACK     volatile pCallbackSAI0=NULL;

signed long sai_buff1[4];
signed long sai_buff2[4];
unsigned int FillBuff=1;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void sai0_isr (void); 

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif

/******************************************************************************
 * SPI Init functions                                                         *
 ******************************************************************************/
void SAI0_Init (tI2S i2s, uint32 srate, uint8 ip, SAI_CALLBACK pC1)
{     
  /* main callback function initialization */
  if (pC1 != NULL)  
  { 
    pCallbackSAI0 = pC1; 
    NVIC_SetIsr(INT_I2S0,ip); 
  }
  
  /* SAI configuration */  
  I2S0_TCSR = i2s.TCSR;
//  I2S0_TCR1 = i2s.TCR1; 
  I2S0_TCR2 = i2s.TCR2;
  I2S0_TCR3 = i2s.TCR3;
  I2S0_TCR4 = i2s.TCR4;
  I2S0_TCR5 = i2s.TCR5;
  I2S0_TDR0 = i2s.TDR0;
//  I2S0_TFR0 = i2s.TFR0;
  I2S0_TMR  = i2s.TMR; 
  I2S0_RCSR = i2s.RCSR;
//  I2S0_RCR1 = i2s.RCR1;
  I2S0_RCR2 = i2s.RCR2;
  I2S0_RCR3 = i2s.RCR3;
  I2S0_RCR4 = i2s.RCR4;
  I2S0_RCR5 = i2s.RCR5;
  I2S0_RDR0 = i2s.RDR0;
//  I2S0_RFR0 = i2s.RFR0;
  I2S0_RMR  = i2s.RMR; 
  I2S0_MCR  = i2s.MCR; 
  I2S0_MDR  = i2s.MDR; 
  
  /* do sw reset of Tx control reg. */
  I2S0_TCSR |= I2S_TCSR_SR_MASK;
  I2S0_TCSR &= ~I2S_TCSR_SR_MASK;
  /* do sw reset of Rx control reg. */
  I2S0_RCSR |= I2S_RCSR_SR_MASK;
  I2S0_RCSR &= ~I2S_RCSR_SR_MASK;
  
  SAI0_SetSampleRate(srate);
  
  SAI0_Enable();
  
}


/******************************************************************************
 * SAI Enable Tx data                                                         *
 ******************************************************************************/
void SAI0_Enable(void)
{
  I2S0_TCSR |= (I2S_TCSR_TE_MASK | I2S_TCSR_FWIE_MASK);
  I2S0_TCR3 |= I2S_TCR3_TCE_MASK;
}

/******************************************************************************
 * SAI Disable Tx data                                                        *
 ******************************************************************************/
void SAI0_Disable(void)
{
  I2S0_TCSR &= ~(I2S_TCSR_TE_MASK | I2S_TCSR_FWIE_MASK);
  I2S0_TCR3 &= ~(I2S_TCR3_TCE_MASK);
}  

/******************************************************************************
 * SAI                                           *
 ******************************************************************************/
int SAI0_SetSampleRate(int smprate)
{
   /* Get samplerate from index */
   int srIx = SAI_GetSampleRateIx(smprate); 
   
   /* Check if requested sample rate is supported */
   if(srIx < 0)
     return -1;

  /* disable MCLK output */
  I2S0_MCR &= ~I2S_MCR_MOE_MASK; 
   
  /* Clear possible clock settings */
  while(I2S0_MCR & I2S_MCR_DUF_MASK)
  {};
   I2S0_MDR = 0;
  
  while(I2S0_MCR & I2S_MCR_DUF_MASK)
  {};
  
  /* bit clock divider (4 = (DIV + 1) * 2) */
  I2S0_TCR2 &= ~I2S_TCR2_DIV_MASK;
  I2S0_TCR2 |= I2S_TCR2_DIV(samples_descr[srIx].bitClockDivider);
  
  /* enable MCLK output */
  I2S0_MCR  |= I2S_MCR_MOE_MASK;
  
  while(I2S0_MCR & I2S_MCR_DUF_MASK)
  {};
  
  return 0;
}

/******************************************************************************
 * SAI Select standard samplerate settings from table                         *
 ******************************************************************************/
int SAI_GetSampleRateIx(int smprate)
{
  int ix = 0;
  /* go through the sample rate table */
  while(samples_descr[ix].samplerate)
  {
  /* if the requested sample rate is found, return the index (positive numer) */
    if(samples_descr[ix].samplerate == smprate)
      return ix;
    
    ix++;
  } 
  return -1;
}


/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void sai0_isr (void)
{
    
  register uint32 tcsr = I2S0_TCSR;
  register uint32 rcsr = I2S0_RCSR;
  
  
  if (pCallbackSAI0 != (SAI_CALLBACK)NULL)
  {
    
    // Rx
    if(rcsr & (I2S_RCSR_FWF_MASK ))
      {pCallbackSAI0 (RXSAI_CALLBACK);}
    
    // Tx
    if(tcsr & (I2S_RCSR_FWF_MASK))
      {pCallbackSAI0 (TXSAI_CALLBACK);}
    
    // Error
    //if(temp & (SPI_SR_TFUF_MASK|SPI_SR_RFOF_MASK|SPI_SR_SPEF_MASK))
      //{pCallbackSPI2 (ERSPI_CALLBACK, temp);}
    
  } 
  
 /* Clear Tx IRQ flags */
 I2S0_TCSR |= I2S_TCSR_WSF_MASK | I2S_TCSR_SEF_MASK | I2S_TCSR_FEF_MASK;  
    
}

#endif
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
