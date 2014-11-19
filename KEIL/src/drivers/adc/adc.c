/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      adc.c
 * @version   1.0.2.0
 * @date      Jan-17-2013
 * @brief     ADC driver header file.
 *
 * Revision History:
 *  1.	15/01/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
#include "common.h"
#include "adc.h"

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static ADC_CALLBACK volatile pCallbackADC0=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void adc0_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
void ADC0_Init  (tADC adc, tADC_CH CHA, tADC_CH CHB, uint8 ip, ADC_CALLBACK pCallback)
{
  if (pCallback != NULL) 
  { 
    pCallbackADC0 = pCallback; 
    NVIC_SetIsr(INT_ADC0,ip); 
  }
  else
  { 
    NVIC_ClrIsr(INT_ADC0);
  }
  ADC0_CFG1 = adc.CFG1;
  ADC0_CFG2 = adc.CFG2;
  ADC0_CV1  = adc.CV1;
  ADC0_CV2  = adc.CV2;
  ADC0_SC2  = adc.SC2;
  ADC0_SC3  = adc.SC3;
  ADC0_SC1A = CHA.SC1;
  ADC0_SC1B = CHB.SC1;  
}

#define TWO_POWER_N_SAMPLES  6  /* select carefully - COP timer not updated */
int ADC0_ExecCalib (tADC adc, tADC_CALIB *pCALIB)
{
  long tmp=0;
  unsigned long tmp_1[7]={0,0,0,0,0,0,0}, tmp_2[7]={0,0,0,0,0,0,0}; 
  register uint16 i=0, numLoops = ((uint16)1<<TWO_POWER_N_SAMPLES);
  
  ADC0_CFG1 = adc.CFG1;
  ADC0_CFG2 = adc.CFG2;
  ADC0_SC2  = (adc.SC2 & (~ADC_SC2_ADTRG_MASK));
  
  /* calibration loop                                                       */
  while ((i++) < numLoops)
  { 
    /* The input channel, conversion mode continuous function, compare      */
    /* function, resolution mode, and differential/single-ended mode are    */
    /* all ignored during the calibration function.                         */
    ADC0_SC1A = 0x1f;
    ADC0_SC3  = (adc.SC3 & (~ADC_SC3_CAL_MASK));
    ADC0_SC3 |= ADC_SC3_CAL_MASK;
    while (!ADC_Ready (ADC0,CHA));
    if (ADC0_SC3 & ADC_SC3_CALF_MASK) { ADC0_SC3 |= ADC_SC3_CALF_MASK; return 1; }
    
    tmp+= (short int)ADC0_OFS;
    
    tmp_1[0]+=(unsigned long)ADC0_CLP0;
    tmp_1[1]+=(unsigned long)ADC0_CLP1;
    tmp_1[2]+=(unsigned long)ADC0_CLP2;
    tmp_1[3]+=(unsigned long)ADC0_CLP3;
    tmp_1[4]+=(unsigned long)ADC0_CLP4;
    tmp_1[5]+=(unsigned long)ADC0_CLPS;
    tmp_1[6]+=(unsigned long)ADC0_CLPD;
    
    tmp_2[0]+=(unsigned long)ADC0_CLM0;
    tmp_2[1]+=(unsigned long)ADC0_CLM1;
    tmp_2[2]+=(unsigned long)ADC0_CLM2;
    tmp_2[3]+=(unsigned long)ADC0_CLM3;
    tmp_2[4]+=(unsigned long)ADC0_CLM4;
    tmp_2[5]+=(unsigned long)ADC0_CLMS;
    tmp_2[6]+=(unsigned long)ADC0_CLMD;
  }
  pCALIB->OFS  = tmp >> TWO_POWER_N_SAMPLES;
  
  pCALIB->CLP[0] = tmp_1[0] >> TWO_POWER_N_SAMPLES;  
  pCALIB->CLP[1] = tmp_1[1] >> TWO_POWER_N_SAMPLES;  
  pCALIB->CLP[2] = tmp_1[2] >> TWO_POWER_N_SAMPLES;  
  pCALIB->CLP[3] = tmp_1[3] >> TWO_POWER_N_SAMPLES;  
  pCALIB->CLP[4] = tmp_1[4] >> TWO_POWER_N_SAMPLES;  
  pCALIB->CLPS   = tmp_1[5] >> TWO_POWER_N_SAMPLES;  
  pCALIB->CLPD   = tmp_1[6] >> TWO_POWER_N_SAMPLES;    
  
  tmp = tmp_1[0]+tmp_1[1]+tmp_1[2]+tmp_1[3]+tmp_1[4]+tmp_1[5];
  pCALIB->PG  = ((tmp>>(1+TWO_POWER_N_SAMPLES))|0x8000);
  
  pCALIB->CLM[0] = tmp_2[0] >> TWO_POWER_N_SAMPLES;  
  pCALIB->CLM[1] = tmp_2[1] >> TWO_POWER_N_SAMPLES;  
  pCALIB->CLM[2] = tmp_2[2] >> TWO_POWER_N_SAMPLES;  
  pCALIB->CLM[3] = tmp_2[3] >> TWO_POWER_N_SAMPLES;  
  pCALIB->CLM[4] = tmp_2[4] >> TWO_POWER_N_SAMPLES;  
  pCALIB->CLMS   = tmp_2[5] >> TWO_POWER_N_SAMPLES;  
  pCALIB->CLMD   = tmp_2[6] >> TWO_POWER_N_SAMPLES;    
  
  tmp = tmp_2[0]+tmp_2[1]+tmp_2[2]+tmp_2[3]+tmp_2[4]+tmp_2[5];
  pCALIB->MG  = ((tmp>>(1+TWO_POWER_N_SAMPLES))|0x8000);
  
  ADC_SaveCalib (ADC0, pCALIB);     /* update calibration registers         */

  return 0; 
}

void ADC0_SaveCalib (tADC_CALIB *pCALIB)
{
  ADC0_CLP0 = pCALIB->CLP[0]; 
  ADC0_CLP1 = pCALIB->CLP[1];
  ADC0_CLP2 = pCALIB->CLP[2];
  ADC0_CLP3 = pCALIB->CLP[3];
  ADC0_CLP4 = pCALIB->CLP[4];
  ADC0_CLPS = pCALIB->CLPS;
  ADC0_CLPD = pCALIB->CLPD;  
  ADC0_CLM0 = pCALIB->CLM[0];
  ADC0_CLM1 = pCALIB->CLM[1];
  ADC0_CLM2 = pCALIB->CLM[2];
  ADC0_CLM3 = pCALIB->CLM[3];
  ADC0_CLM4 = pCALIB->CLM[4];
  ADC0_CLMS = pCALIB->CLMS;
  ADC0_CLMD = pCALIB->CLMD;
  ADC0_PG   = pCALIB->PG; 
  ADC0_MG   = pCALIB->MG; 
  ADC0_OFS  = pCALIB->OFS;     
}
/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void adc0_isr (void) 
{ 
  if (pCallbackADC0 != (ADC_CALLBACK)NULL) 
  { 
    if (ADC0_SC1A & ADC_SC1_COCO_MASK) { pCallbackADC0 (CHA_CALLBACK, ADC0_RA); }
    if (ADC0_SC1B & ADC_SC1_COCO_MASK) { pCallbackADC0 (CHB_CALLBACK, ADC0_RB); }
  }
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
