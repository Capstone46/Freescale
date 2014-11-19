/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      tpm.c
 * @version   1.0.3.0
 * @date      Jan-18-2013
 * @brief     TPM driver source code file.
 *
 * Revision History:
 *  1.	11/01/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
#include "common.h"
#include "tpm.h"

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static TPM_CALLBACK volatile pCallbackTPM0=NULL;
static TPM_CALLBACK volatile pCallbackTPM1=NULL;
static TPM_CALLBACK volatile pCallbackTPM2=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void tpm0_isr (void);
void tpm1_isr (void);
void tpm2_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
void TPM0_Init (tTPM tpm, uint16 modVal, uint8 ip, TPM_CALLBACK pCallback)
{
  if (pCallback != NULL) { pCallbackTPM0 = pCallback; NVIC_SetIsr(INT_TPM0,ip);}
  TPM0_CONF 	= tpm.CONF;
  TPM0_CNT      = 0l; 
  TPM0_MOD      = modVal;
  TPM0_SC       = tpm.SC;
}

void TPM1_Init (tTPM tpm, uint16 modVal, uint8 ip, TPM_CALLBACK pCallback)
{
  if (pCallback != NULL) { pCallbackTPM1 = pCallback; NVIC_SetIsr(INT_TPM1,ip);}
  TPM1_CONF 	= tpm.CONF;
  TPM1_CNT      = 0l;
  TPM1_MOD      = modVal;
  TPM1_SC       = tpm.SC;
}

void TPM2_Init (tTPM tpm, uint16 modVal, uint8 ip, TPM_CALLBACK pCallback)
{
  if (pCallback != NULL) { pCallbackTPM2 = pCallback; NVIC_SetIsr(INT_TPM2,ip);}
  TPM2_CONF 	= tpm.CONF;
  TPM2_CNT      = 0l; 
  TPM2_MOD      = modVal;
  TPM2_SC       = tpm.SC;
}

/* channels */
void TPM0CH0_Init (tTPM_CH tpm_ch, uint16 value)
{
    TPM0_C0SC = tpm_ch.CnSC;
    TPM0_C0V  = value;
}

void TPM0CH1_Init (tTPM_CH tpm_ch, uint16 value)
{
    TPM0_C1SC = tpm_ch.CnSC;
    TPM0_C1V  = value;
}

void TPM0CH2_Init (tTPM_CH tpm_ch, uint16 value)
{
    TPM0_C2SC = tpm_ch.CnSC;
    TPM0_C2V  = value;
}

void TPM0CH3_Init (tTPM_CH tpm_ch, uint16 value)
{
    TPM0_C3SC = tpm_ch.CnSC;
    TPM0_C3V  = value;
}

void TPM0CH4_Init (tTPM_CH tpm_ch, uint16 value)
{
    TPM0_C4SC = tpm_ch.CnSC;
    TPM0_C4V  = value;
}

void TPM0CH5_Init (tTPM_CH tpm_ch, uint16 value)
{
    TPM0_C5SC = tpm_ch.CnSC;
    TPM0_C5V  = value;
}

void TPM1CH0_Init (tTPM_CH tpm_ch, uint16 value)
{
    TPM1_C0SC = tpm_ch.CnSC;
    TPM1_C0V  = value;
}

void TPM1CH1_Init (tTPM_CH tpm_ch, uint16 value)
{
    TPM1_C1SC = tpm_ch.CnSC;
    TPM1_C1V  = value;
}

void TPM2CH0_Init (tTPM_CH tpm_ch, uint16 value)
{
    TPM2_C0SC = tpm_ch.CnSC;
    TPM2_C0V  = value;
}

void TPM2CH1_Init (tTPM_CH tpm_ch, uint16 value)
{
    TPM2_C1SC = tpm_ch.CnSC;
    TPM2_C1V  = value;
}

/******************************************************************************
 * interrupt functions definitions                                            *
 * NOTE: no need to change flag clearing TPM0_SC |= TPM_SC_TOF_MASK; because 
 *       just one w1c bit in whole register
 ******************************************************************************/
void tpm0_isr (void)
{      
  /* process interrupt callback function                                      */  
  if (pCallbackTPM0 != (TPM_CALLBACK)NULL) 
  { 
    if ((TPM0_SC & TPM_SC_TOIE_MASK) && (TPM0_SC & TPM_SC_TOF_MASK)) 
    { 
      TPM0_SC |= TPM_SC_TOF_MASK; pCallbackTPM0 (TOF_CALLBACK_MASK); 
    }   
    if ((TPM0_C0SC & TPM_CnSC_CHIE_MASK) && (TPM0_C0SC & TPM_CnSC_CHF_MASK)) 
    { 
      TPM0_C0SC |= TPM_CnSC_CHF_MASK; pCallbackTPM0 (CH0F_CALLBACK_MASK);
    }
    if ((TPM0_C1SC & TPM_CnSC_CHIE_MASK) && (TPM0_C1SC & TPM_CnSC_CHF_MASK)) 
    { 
      TPM0_C1SC |= TPM_CnSC_CHF_MASK; pCallbackTPM0 (CH1F_CALLBACK_MASK);
    }
    if ((TPM0_C2SC & TPM_CnSC_CHIE_MASK) && (TPM0_C2SC & TPM_CnSC_CHF_MASK)) 
    { 
      TPM0_C2SC |= TPM_CnSC_CHF_MASK; pCallbackTPM0 (CH2F_CALLBACK_MASK);
    }
    if ((TPM0_C3SC & TPM_CnSC_CHIE_MASK) && (TPM0_C3SC & TPM_CnSC_CHF_MASK)) 
    { 
      TPM0_C3SC |= TPM_CnSC_CHF_MASK; pCallbackTPM0 (CH3F_CALLBACK_MASK);
    }
    if ((TPM0_C4SC & TPM_CnSC_CHIE_MASK) && (TPM0_C4SC & TPM_CnSC_CHF_MASK)) 
    { 
      TPM0_C4SC |= TPM_CnSC_CHF_MASK; pCallbackTPM0 (CH4F_CALLBACK_MASK);
    }
    if ((TPM0_C5SC & TPM_CnSC_CHIE_MASK) && (TPM0_C5SC & TPM_CnSC_CHF_MASK)) 
    { 
      TPM0_C5SC |= TPM_CnSC_CHF_MASK; pCallbackTPM0 (CH5F_CALLBACK_MASK);
    }
  }    
}

void tpm1_isr (void)
{      
  /* process interrupt callback function                                      */  
  if (pCallbackTPM1 != (TPM_CALLBACK)NULL) 
  { 
    if ((TPM1_SC & TPM_SC_TOIE_MASK) && (TPM1_SC & TPM_SC_TOF_MASK)) 
    { 
      TPM1_SC |= TPM_SC_TOF_MASK; pCallbackTPM1 (TOF_CALLBACK_MASK); 
    }   
    if ((TPM1_C0SC & TPM_CnSC_CHIE_MASK) && (TPM1_C0SC & TPM_CnSC_CHF_MASK)) 
    { 
      TPM1_C0SC |= TPM_CnSC_CHF_MASK; pCallbackTPM1 (CH0F_CALLBACK_MASK);
    }
    if ((TPM1_C1SC & TPM_CnSC_CHIE_MASK) && (TPM1_C1SC & TPM_CnSC_CHF_MASK)) 
    { 
      TPM1_C1SC |= TPM_CnSC_CHF_MASK; pCallbackTPM1 (CH1F_CALLBACK_MASK);
    }
  }    
}

void tpm2_isr (void)
{      
  /* process interrupt callback function                                      */  
  if (pCallbackTPM2 != (TPM_CALLBACK)NULL) 
  { 
    if ((TPM2_SC & TPM_SC_TOIE_MASK) && (TPM2_SC & TPM_SC_TOF_MASK)) 
    { 
      TPM2_SC |= TPM_SC_TOF_MASK; pCallbackTPM2 (TOF_CALLBACK_MASK); 
    }   
    if ((TPM2_C0SC & TPM_CnSC_CHIE_MASK) && (TPM2_C0SC & TPM_CnSC_CHF_MASK)) 
    { 
      TPM2_C0SC |= TPM_CnSC_CHF_MASK; pCallbackTPM2 (CH0F_CALLBACK_MASK);
    }
    if ((TPM2_C1SC & TPM_CnSC_CHIE_MASK) && (TPM2_C1SC & TPM_CnSC_CHF_MASK)) 
    { 
      TPM2_C1SC |= TPM_CnSC_CHF_MASK; pCallbackTPM2 (CH1F_CALLBACK_MASK);
    }
  }    
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
