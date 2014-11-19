/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flexio.c
 * @version   1.0.9.0
 * @date      May-22-2013
 * @brief     FlexIO module driver source file.
 *
 * Revision History:
 *  1.	xx/xx/xxxx   Bxxxxx   Initially written for Kinetis L
 ******************************************************************************/
#include "common.h"
#include "flexio.h"

#if (defined (MCU_MKL43Z256))
/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
typedef struct { FLEXIO_CALLBACK pCallBack; uint32_t INT_MASK; void* user_data;} tFLEXIO_CALLBACK_DESC_INT;

static tFLEXIO_CALLBACK_DESC_INT volatile flexio_CallBackDesc[FLEXIO_MAX_CALLBACKS];
/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void flexio_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif

/***************************************************************************//*!
 * @brief   FLEXIO module initialization function.
 ******************************************************************************/
void FLEXIO_Init(tFLEXIO flexio, uint8 ip, FLEXIO_CALLBACK pCallback)
{
  uint32_t i;

  NVIC_ClrIsr(INT_UART0_FLEXIO);

  for(i=0; i< FLEXIO_MAX_CALLBACKS; i++)
    flexio_CallBackDesc[i].pCallBack = NULL;

  NVIC_SetPriority((IRQn_Type)INT_UART0_FLEXIO, ip);

  if (pCallback != NULL)
  {
    tFLEXIO_CALLBACK_DESC callBackDesc;
    callBackDesc.pCallBack = pCallback;
    callBackDesc.SHIFTERR_MASK = 0x0F;
    callBackDesc.SHIFTFLG_MASK = 0x0F;
    callBackDesc.TIMERFLG_MASK = 0x0F;
    FLEXIO_RegisterCallback(&callBackDesc, 0);

   NVIC_EnableIRQ((IRQn_Type)(INT_UART0_FLEXIO - 16));
  }

  FLEXIO_CTRL     = flexio.CTRL;
}

/***************************************************************************//*!
* @brief   FLEXIO module register special callback
******************************************************************************/
int32_t FLEXIO_RegisterCallback(tFLEXIO_CALLBACK_DESC *pCallBackDesc, uint32 high_priority)
{
  uint32_t i;
  tFLEXIO_CALLBACK_DESC_INT callBackDescInt;
  // Check parameters
  if(pCallBackDesc == NULL)
    return -1;

  if(pCallBackDesc->pCallBack == NULL)
    return -1;

  // Find free position
  for(i=0; i< FLEXIO_MAX_CALLBACKS; i++)
  {
    if(!flexio_CallBackDesc[i].pCallBack)
      break;
  }

  // Check if there is place in buffer
  if(i >= FLEXIO_MAX_CALLBACKS)
    return -1;

  NVIC_DisableIRQ((IRQn_Type)(INT_UART0_FLEXIO - 16));
  // Register

  // Clear the possible pending interrupt events
  FLEXIO_TIMSTAT = pCallBackDesc->TIMERFLG_MASK;
  FLEXIO_SHIFTSTAT = pCallBackDesc->SHIFTFLG_MASK;
  FLEXIO_SHIFTERR = pCallBackDesc->SHIFTERR_MASK;

  callBackDescInt.INT_MASK =  (pCallBackDesc->TIMERFLG_MASK << 8) | (pCallBackDesc->SHIFTERR_MASK << 4) | pCallBackDesc->SHIFTFLG_MASK;
  callBackDescInt.pCallBack =  pCallBackDesc->pCallBack;
  callBackDescInt.user_data = pCallBackDesc->user_data;
  // if high_priority of callback is needed move all rest to other positions
  if(high_priority)
  {
    while(i)
    {
       flexio_CallBackDesc[i-i] = flexio_CallBackDesc[i];
       i--;
    }
  }

  flexio_CallBackDesc[i] = callBackDescInt;

  NVIC_EnableIRQ((IRQn_Type)(INT_UART0_FLEXIO - 16));

  return 0;
}

/***************************************************************************//*!
* @brief   FLEXIO module unregister special callback
******************************************************************************/
extern int32_t FLEXIO_UnRegisterCallback(FLEXIO_CALLBACK pCallBack)
{
  uint32_t i;

  if(pCallBack == NULL)
    return -1;

  // Find this position
  for(i=0; i< FLEXIO_MAX_CALLBACKS; i++)
  {
    if(flexio_CallBackDesc[i].pCallBack == pCallBack)
      break;
  }

  // Check if there is place in buffer
  if(i >= FLEXIO_MAX_CALLBACKS)
    return -1;

  NVIC_DisableIRQ((IRQn_Type)(INT_UART0_FLEXIO - 16));
  // Register
  flexio_CallBackDesc[i].pCallBack = NULL;

  while( (i + 1) < FLEXIO_MAX_CALLBACKS)
  {
      if(flexio_CallBackDesc[i+1].pCallBack)
      {
         flexio_CallBackDesc[i] = flexio_CallBackDesc[i+1];
      }
      i++;
  }

  NVIC_EnableIRQ((IRQn_Type)(INT_UART0_FLEXIO - 16));
  return 0;
}

/***************************************************************************//*!
 * @brief   FLEXIO shifter 0 initialization function.
 ******************************************************************************/
void FLEXIO_SHIFTER0_Init(tFLEXIO_SHIFTER flexio_shifter)
{
  FLEXIO_SHIFTSIEN = flexio_shifter.SHIFTSIEN<<0;
  FLEXIO_SHIFTEIEN = flexio_shifter.SHIFTEIEN<<0;
  FLEXIO_SHIFTSDEN = flexio_shifter.SHIFTSDEN<<0;
  FLEXIO_SHIFTCFG0 = flexio_shifter.SHIFTCFG;
  FLEXIO_SHIFTCTL0 = flexio_shifter.SHIFTCTL;
}
/***************************************************************************//*!
 * @brief   FLEXIO shifter 1 initialization function.
 ******************************************************************************/
void FLEXIO_SHIFTER1_Init(tFLEXIO_SHIFTER flexio_shifter)
{
  FLEXIO_SHIFTSIEN = flexio_shifter.SHIFTSIEN<<1;
  FLEXIO_SHIFTEIEN = flexio_shifter.SHIFTEIEN<<1;
  FLEXIO_SHIFTSDEN = flexio_shifter.SHIFTSDEN<<1;
  FLEXIO_SHIFTCFG1 = flexio_shifter.SHIFTCFG;
  FLEXIO_SHIFTCTL1 = flexio_shifter.SHIFTCTL;
}
/***************************************************************************//*!
 * @brief   FLEXIO shifter 2 initialization function.
 ******************************************************************************/
void FLEXIO_SHIFTER2_Init(tFLEXIO_SHIFTER flexio_shifter)
{
  FLEXIO_SHIFTSIEN = flexio_shifter.SHIFTSIEN<<2;
  FLEXIO_SHIFTEIEN = flexio_shifter.SHIFTEIEN<<2;
  FLEXIO_SHIFTSDEN = flexio_shifter.SHIFTSDEN<<2;
  FLEXIO_SHIFTCFG2 = flexio_shifter.SHIFTCFG;
  FLEXIO_SHIFTCTL2 = flexio_shifter.SHIFTCTL;
}
/***************************************************************************//*!
 * @brief   FLEXIO shifter 3 initialization function.
 ******************************************************************************/
void FLEXIO_SHIFTER3_Init(tFLEXIO_SHIFTER flexio_shifter)
{
  FLEXIO_SHIFTSIEN = flexio_shifter.SHIFTSIEN<<3;
  FLEXIO_SHIFTEIEN = flexio_shifter.SHIFTEIEN<<3;
  FLEXIO_SHIFTSDEN = flexio_shifter.SHIFTSDEN<<3;
  FLEXIO_SHIFTCFG3 = flexio_shifter.SHIFTCFG;
  FLEXIO_SHIFTCTL3 = flexio_shifter.SHIFTCTL;
}

/***************************************************************************//*!
 * @brief   FLEXIO timer 0 initialization function.
 ******************************************************************************/
void FLEXIO_TIMER0_Init(tFLEXIO_TIMER flexio_timer, uint32 u32TimerComVal)
{
  FLEXIO_SetTimerCompareVal(FLEXIO_TIMER0, u32TimerComVal);
  FLEXIO_TIMIEN = flexio_timer.TIMIEN<<0;
  FLEXIO_TIMCFG0 = flexio_timer.TIMCFG;
  FLEXIO_TIMCTL0 = flexio_timer.TIMCTL;
}
/***************************************************************************//*!
 * @brief   FLEXIO timer 1 initialization function.
 ******************************************************************************/
void FLEXIO_TIMER1_Init(tFLEXIO_TIMER flexio_timer, uint32 u32TimerComVal)
{
  FLEXIO_SetTimerCompareVal(FLEXIO_TIMER1, u32TimerComVal);
  FLEXIO_TIMIEN = flexio_timer.TIMIEN<<1;
  FLEXIO_TIMCFG1 = flexio_timer.TIMCFG;
  FLEXIO_TIMCTL1 = flexio_timer.TIMCTL;
}
/***************************************************************************//*!
 * @brief   FLEXIO timer 2 initialization function.
 ******************************************************************************/
void FLEXIO_TIMER2_Init(tFLEXIO_TIMER flexio_timer, uint32 u32TimerComVal)
{
  FLEXIO_SetTimerCompareVal(FLEXIO_TIMER2, u32TimerComVal);
  FLEXIO_TIMIEN = flexio_timer.TIMIEN<<2;
  FLEXIO_TIMCFG2 = flexio_timer.TIMCFG;
  FLEXIO_TIMCTL2 = flexio_timer.TIMCTL;
}
/***************************************************************************//*!
 * @brief   FLEXIO timer 3 initialization function.
 ******************************************************************************/
void FLEXIO_TIMER3_Init(tFLEXIO_TIMER flexio_timer, uint32 u32TimerComVal)
{
  FLEXIO_TIMIEN = flexio_timer.TIMIEN<<3;
  FLEXIO_TIMCFG3 = flexio_timer.TIMCFG;
  FLEXIO_TIMCTL3 = flexio_timer.TIMCTL;
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void flexio_isr (void)
{
  if (flexio_CallBackDesc[0].pCallBack) // At least one callback is available/registered
  {
    uint32_t timerStat_mask = FLEXIO_TIMSTAT;
    uint32_t shifterStat_mask = FLEXIO_SHIFTSTAT;
    uint32_t shifterErr_mask = FLEXIO_SHIFTERR;
    uint32_t i = 0;
    uint32_t callbacksMask;

    // Let masks only what are arrived by interrupts
    timerStat_mask &= (FLEXIO_TIMIEN & FLEXIO_TIMIEN_TEIE_MASK);
    shifterStat_mask &= (FLEXIO_SHIFTSIEN & FLEXIO_SHIFTSIEN_SSIE_MASK);
    shifterErr_mask &= (FLEXIO_SHIFTEIEN & FLEXIO_SHIFTEIEN_SEIE_MASK);

    callbacksMask =  (timerStat_mask << 8) | (shifterErr_mask << 4) | shifterStat_mask;

    // Look for all registered callbacks if there is interesting source of interrupt for them
    while((i < FLEXIO_MAX_CALLBACKS) && (flexio_CallBackDesc[i].pCallBack))
    {
      if(callbacksMask & flexio_CallBackDesc[i].INT_MASK)
      {
        flexio_CallBackDesc[i].pCallBack((FLEXIO_CALLBACK_TYPE)(callbacksMask & flexio_CallBackDesc[i].INT_MASK), flexio_CallBackDesc[i].user_data);
      }
      i++;
    }
    // Clear flags
    FLEXIO_TIMSTAT = timerStat_mask;
    FLEXIO_SHIFTSTAT = shifterStat_mask;
    FLEXIO_SHIFTERR = shifterErr_mask;
  }
}

#endif

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
