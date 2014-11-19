/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      tsi.c
 * @version   1.0.5.0
 * @date      Mar-8-2013
 * @brief     Touch sensing input (TSI) low level driver source code.
 *
 * Revision History:
 *  1.	28/02/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
#include "common.h"
#include "tsi.h"

#if (defined (MCU_MKL46Z256))
/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static TSI_CALLBACK pCallbackTSI0=NULL;

/******************************************************************************
 * interrupt function prototypes                                              *
 ******************************************************************************/
void tsi0_isr (void);

/******************************************************************************
 * Public function definitions                                                *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
/******************************************************************************
 * TSI calibration functions definition                                       *
 ******************************************************************************/
#define NUM_OF_LOOPS    16
int32 TSI0_Calib (tTSI tsi, uint8* p_u8Chan, uint8 u8NumChans, uint16 u16Sen, tTSI_CALIB *pCALIB)
{
  tTSI tsi_backup;
  uint16 u16TempCnt[NUM_OF_LOOPS];
  uint16 u16CntMax, u16CntMin;
  uint16 i, j;
  
  tsi_backup.GENCS = TSI0_GENCS;
  tsi_backup.DATA = TSI0_DATA;
  TSI_Disable (TSI0);
  TSI0_GENCS  = tsi.GENCS&(~(TSI_GENCS_TSIIEN_MASK|TSI_GENCS_STM_MASK|TSI_GENCS_STM_MASK));
  TSI0_DATA   = 0x0;
  TSI_Enable (TSI0);
  
  for (j = 0; j < u8NumChans; j++)
  {
    TSI_ChanSel (TSI0, (uint32)*(p_u8Chan+j));
    arch_delay (1000);
    u16CntMax = 0x0, u16CntMin = 0xFFFF;
    for (i = 0; i < NUM_OF_LOOPS; i++)
    { 
      TSI_ClrEOSF (TSI0);
      TSI_SwTrgStart (TSI0);
      while (TSI_GetStatus (TSI0, SCNIP) || !TSI_GetStatus (TSI0, EOSF));
      u16TempCnt[i] = TSI_GetCntVal (TSI0);
      arch_delay (1000);
      if (u16TempCnt[i] > u16CntMax)
      {
        u16CntMax = u16TempCnt[i];
      }
      if (u16TempCnt[i] < u16CntMin)
      {
        u16CntMin = u16TempCnt[i];
      }
    }
    if ((u16CntMax / (u16CntMax - u16CntMin)) < 10)
    {
      TSI_Disable (TSI0);
      TSI0_GENCS  = tsi_backup.GENCS ;
      TSI0_DATA   = tsi_backup.DATA;
      TSI_Enable (TSI0);
      return (int32)*(p_u8Chan+j);
    }
    if ((0xFFFF-u16CntMax) < (u16CntMax>>u16Sen))
      u16CntMax = 0xFFFF;
    else
      u16CntMax += (u16CntMax>>u16Sen);
    //u16CntMin -= (u16CntMin>>u16Sen);
    pCALIB->THRESH[*(p_u8Chan+j)] = (uint32)(u16CntMax);
    pCALIB->THRESL[*(p_u8Chan+j)] = 0x0;
  }
  TSI_Disable (TSI0);
  TSI0_GENCS  = tsi_backup.GENCS ;
  TSI0_DATA   = tsi_backup.DATA;
  TSI_Enable (TSI0);
  
  return 0; 
}

/******************************************************************************
 * TSI initialization functions definition                                    *
 ******************************************************************************/
void TSI0_Init  (tTSI tsi, uint32 threshl, uint32 threshh, uint8 ip, TSI_CALLBACK pCallback)
{
  if (pCallback != NULL)  
  { 
    pCallbackTSI0 = pCallback; 
    NVIC_SetIsr(INT_TSI0,ip); 
  }
  TSI0_GENCS  = tsi.GENCS;
  TSI0_DATA   = tsi.DATA;
  TSI0_TSHD  = ((threshh<<16)|threshl);
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void tsi0_isr (void) 
{
  if (pCallbackTSI0 != (TSI_CALLBACK)NULL) 
  {
    if (TSI_GetStatus(TSI0,OUTRGF) && !(TSI_GetStatus(TSI0,ESOR)))
    { 
      TSI_ClrOUTRGF (TSI0); TSI_ClrEOSF (TSI0); pCallbackTSI0 (OUTRGF_CALLBACK); 
    }
    if (TSI_GetStatus(TSI0,EOSF) && (TSI_GetStatus(TSI0,ESOR)))
    { 
      TSI_ClrEOSF (TSI0); pCallbackTSI0 (EOSF_CALLBACK); 
    } 
  } 
}

#endif
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
