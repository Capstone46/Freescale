/*****************************************************************************
 * (c) Copyright 2010-2014, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flexio_i2s.c
 * @version   1.0.9.0
 * @date      May-22-2013
 * @brief     FlexIOI2S module driver source file.
 *
 * Revision History:
 *  1.	xx/xx/xxxx   Bxxxxx   Initially written for Kinetis L
 ******************************************************************************/
#include "common.h"
#include "drivers.h"
#include "flexio_i2s.h"

#if (defined (MCU_MKL43Z256))

/******************************************************************************
* private functions definitions                                              *
******************************************************************************/
#if FLEXIO_I2S_DMA_MODE == 0
 // Prepared for DMA mode, not implemented so far  
#endif

/******************************************************************************
* data type definitions                                                      *
******************************************************************************/
FLEXIO_I2S_CONFIG flexio_i2s_config;

/******************************************************************************
* interrupt callback functions prototype                                     *
******************************************************************************/
void flexio_i2s_isr_callback(FLEXIO_CALLBACK_TYPE type, void* user_data);

/******************************************************************************
* Public functions definitions                                               *
******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif

/***************************************************************************//*!
* @brief   FLEXIOI2S module initialization function.
* @param   shifterOutIx - Index of shifter for transmit
* @param   shifterInIx - Index of shifter for receive 
* @param   timerBclkIx - Index of timer for I2S bit clock a shift registers clk
* @param   timerFsyncIx - Index of timer for I2S FS (WS) Word Select signal
* @param   timerMclkIx  - Index of timer for I2S MCLK (Master Clock)
* @param   pinDoutIx - Index of FlexIO Pin for I2S DOUT signal
* @param   pinDinIx - Index of FlexIO Pin for I2S DIN signal
* @param   pinBclkIx - Index of FlexIO Pin for I2S BCLK signal 
* @param   pinFsyncIx - Index of FlexIO Pin for I2S FS signal  
* @param   pinMclkIx - Index of FlexIO Pin for I2S MCLK signal 
* @param   wordSize  - size of the audio samples in bits (16,32) 
* @param   sampleRate - Requested audio samplerate 
* @param   iisMclk - I2S master clock frequency [Hz] 
* @param   FlexIoClk - Clock frequency of FlexIO peripheral [Hz] 
* @return  Result of Init Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_I2S_RESULT FLEXIO_I2S_Init(
                                  FLEXIO_I2S_CONFIG * pConfig,
                                  uint32_t shifterOutIx,
                                  uint32_t shifterInIx,
                                  uint32_t timerBclkIx,  
                                  uint32_t timerFsyncIx,
                                  uint32_t timerMclkIx,
                                  uint32_t pinDoutIx,
                                  uint32_t pinDinIx,
                                  uint32_t pinBclkIx,
                                  uint32_t pinFsyncIx,
                                  uint32_t pinMclkIx,
                                  uint32_t wordSize,
                                  uint32_t sampleRate,
                                  uint32_t iisMclk,
                                  uint32_t FlexIoClk
                                  )
{
  uint32_t temp; // local temporary
  
  // Store the configuration information
  pConfig->shifterOutIx = shifterOutIx;
  pConfig->shifterInIx  = shifterInIx;
  pConfig->timerBclkIx  = timerBclkIx;
  pConfig->timerFsyncIx = timerFsyncIx;
  pConfig->timerMclkIx  = timerMclkIx;
  pConfig->baudRateDiv  = (uint32)(((double)iisMclk)/((double)wordSize*(double)sampleRate)+0.5f);
  pConfig->pDataCallBack = NULL;
  pConfig->dataIx = 0;
  pConfig->buffIx = 0;
  
  for(temp=0;temp<I2S_BUF_CNT;temp++)
    pConfig->outbuf[temp].pData = NULL;
  
  /************ SHIFTER OUT CONFIGURATION *************************************/
  // Initialize the FlexIO shifter register to trensmit I2S data
  FLEXIO_ShifterIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  FLEXIO_ShifterErrIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  FLEXIO_ShifterDmaDisable(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  
  // SetUp Shifter Out CTL
  FLEXIO_ShifterTimerSel(pConfig->shifterOutIx, pConfig->timerBclkIx);
  FLEXIO_ShifterTimerPol(pConfig->shifterOutIx, FLEXIO_POLARITY_LOW);
  FLEXIO_ShifterPinCfg(pConfig->shifterOutIx, FLEXIO_PIN_DISABLED);
  
  FLEXIO_ShifterPinSel(pConfig->shifterOutIx, pinDoutIx);            
  FLEXIO_ShifterPinPol(pConfig->shifterOutIx, FLEXIO_POLARITY_HIGH); 
  FLEXIO_ShifterMode(pConfig->shifterOutIx, FLEXIO_SHIFTER_TX_MODE);  

  // SetUp Shifter Out CFG
  FLEXIO_ShifterInSrc(pConfig->shifterOutIx, FLEXIO_INSRC_PIN);         
  FLEXIO_ShifterStopBit(pConfig->shifterOutIx, FLEXIO_STOPBIT_DISABLED);
  FLEXIO_ShifterStartBit(pConfig->shifterOutIx, FLEXIO_STARTBIT_DISABLED_ON_FIRST); 

  /************ SHIFTER IN CONFIGURATION **************************************/
  // Initialize the FlexIO shifter register to receive I2S data
  FLEXIO_ShifterIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  FLEXIO_ShifterErrIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  FLEXIO_ShifterDmaDisable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  // SetUp Shifter In CTL
  FLEXIO_ShifterTimerSel(pConfig->shifterInIx, pConfig->timerBclkIx);
  FLEXIO_ShifterTimerPol(pConfig->shifterInIx, FLEXIO_POLARITY_HIGH); 
  FLEXIO_ShifterPinCfg(pConfig->shifterInIx, FLEXIO_PIN_DISABLED); 
  FLEXIO_ShifterPinSel(pConfig->shifterInIx, pinDinIx); 
  FLEXIO_ShifterPinPol(pConfig->shifterInIx, FLEXIO_POLARITY_HIGH); 
  FLEXIO_ShifterMode(pConfig->shifterInIx, FLEXIO_SHIFTER_RX_MODE); 

  // SetUp Shifter In CFG
  FLEXIO_ShifterInSrc(pConfig->shifterInIx, FLEXIO_INSRC_PIN); 
  FLEXIO_ShifterStopBit(pConfig->shifterInIx, FLEXIO_STOPBIT_DISABLED); 
  FLEXIO_ShifterStartBit(pConfig->shifterInIx, FLEXIO_STARTBIT_DISABLED_ON_EN); 

  /************* TIMER BCLK OUT CONFIGURATION *********************************/
  // Initialize the FlexIO timer for generate BCLK
  // Configure 2 word transfer with baud rate of divide by 4 of the FlexIO clock. Set
  // TIMCMP[15:8] = (number of words x 2)-1 Set TIMCMP[7:0] = (BR divider) - 1.
  temp = (uint32)((uint32)((wordSize*2)-1)<<8)|(pConfig->baudRateDiv -1);
  FLEXIO_SetTimerCompareVal(pConfig->timerBclkIx, temp);
  FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerBclkIx));
  
  // SetUp Timer Out CFG
  FLEXIO_TimerClock(pConfig->timerBclkIx, FLEXIO_LOG1_ON_EN); 
  FLEXIO_TimerInc(pConfig->timerBclkIx, FLEXIO_INC_ALWAYS); 
  FLEXIO_TimerResets(pConfig->timerBclkIx, FLEXIO_RST_NEVER); 
  FLEXIO_TimerDisablesOn(pConfig->timerBclkIx, FLEXIO_DIS_NEVER);  
  FLEXIO_TimerEnablesOn(pConfig->timerBclkIx, FLEXIO_EN_TRIGGER_HIGH); 
  FLEXIO_TimerStopBit(pConfig->timerBclkIx, FLEXIO_STOP_DISABLED);  
  FLEXIO_TimerStartBit(pConfig->timerBclkIx, START_ENABLED);
  
  // SetUp Timer Out CTL
  FLEXIO_TimerTrgSel(pConfig->timerBclkIx, FLEXIO_TIMTRG_SHIFTER(pConfig->shifterOutIx)); 
  FLEXIO_TimerTrgPol(pConfig->timerBclkIx, FLEXIO_POLARITY_LOW);  
  FLEXIO_TimerTrgSrc(pConfig->timerBclkIx, INT_TRG);
  FLEXIO_TimerPinCfg(pConfig->timerBclkIx, FLEXIO_PIN_DISABLED); 
  
  FLEXIO_TimerPinSel(pConfig->timerBclkIx, pinBclkIx);
  FLEXIO_TimerPinPol(pConfig->timerBclkIx, FLEXIO_POLARITY_HIGH); 
  FLEXIO_TimerMode(pConfig->timerBclkIx, FLEXIO_TIMER_8BIT_BAUD_MODE);  

  /************* TIMER FS OUT CONFIGURATION ***********************************/
  // Configure transfer. Set TIMCMP[15:0] = (2x number of bits x BR divider) -1.
  temp = (2 * wordSize * (pConfig->baudRateDiv))-1;
  FLEXIO_SetTimerCompareVal(pConfig->timerFsyncIx, temp);
  FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerFsyncIx));
  // SetUp Timer Out CFG
  FLEXIO_TimerClock(pConfig->timerFsyncIx, FLEXIO_LOG1_ON_EN); 
  FLEXIO_TimerInc(pConfig->timerFsyncIx, FLEXIO_INC_ALWAYS);  
  FLEXIO_TimerResets(pConfig->timerFsyncIx, FLEXIO_RST_NEVER);  
  FLEXIO_TimerDisablesOn(pConfig->timerFsyncIx, FLEXIO_DIS_NEVER);  
  FLEXIO_TimerEnablesOn(pConfig->timerFsyncIx, FLEXIO_EN_TRIGGER_HIGH);  
  FLEXIO_TimerStopBit(pConfig->timerFsyncIx, FLEXIO_STOP_DISABLED);  
  FLEXIO_TimerStartBit(pConfig->timerFsyncIx, START_DISABLED);
  // SetUp Timer Out CTL
  FLEXIO_TimerTrgSel(pConfig->timerFsyncIx, FLEXIO_TIMTRG_TIMER(pConfig->timerBclkIx)); 
  FLEXIO_TimerTrgPol(pConfig->timerFsyncIx, FLEXIO_POLARITY_HIGH); 
  FLEXIO_TimerTrgSrc(pConfig->timerFsyncIx, INT_TRG);
  FLEXIO_TimerPinCfg(pConfig->timerFsyncIx, FLEXIO_PIN_DISABLED);
  
  FLEXIO_TimerPinSel(pConfig->timerFsyncIx, pinFsyncIx);
  FLEXIO_TimerPinPol(pConfig->timerFsyncIx, FLEXIO_POLARITY_LOW); 
  FLEXIO_TimerMode(pConfig->timerFsyncIx,   FLEXIO_TIMER_16BIT_MODE); 
  
  /************* TIMER MCLK OUT CONFIGURATION *********************************/
  temp = (uint32)((uint32)((wordSize*2)-1)<<8)|((FlexIoClk/iisMclk)-3); 
  FLEXIO_SetTimerCompareVal(pConfig->timerMclkIx, temp);
  FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerMclkIx));
  
  // SetUp Timer Out CFG
  FLEXIO_TimerClock(pConfig->timerMclkIx, FLEXIO_LOG1_ON_EN); 
  FLEXIO_TimerInc(pConfig->timerMclkIx, FLEXIO_INC_ALWAYS);  
  FLEXIO_TimerResets(pConfig->timerMclkIx, FLEXIO_RST_NEVER);  
  FLEXIO_TimerDisablesOn(pConfig->timerMclkIx, FLEXIO_DIS_NEVER); 
  FLEXIO_TimerEnablesOn(pConfig->timerMclkIx, FLEXIO_EN_TRIGGER_HIGH); 
  FLEXIO_TimerStopBit(pConfig->timerMclkIx, FLEXIO_STOP_DISABLED);  
  FLEXIO_TimerStartBit(pConfig->timerMclkIx, START_DISABLED);
  
  // SetUp Timer Out CTL
  FLEXIO_TimerTrgSel(pConfig->timerMclkIx, FLEXIO_TIMTRG_SHIFTER(pConfig->shifterOutIx)); 
  FLEXIO_TimerTrgPol(pConfig->timerMclkIx, FLEXIO_POLARITY_LOW); 
  FLEXIO_TimerTrgSrc(pConfig->timerMclkIx, INT_TRG);
  FLEXIO_TimerPinCfg(pConfig->timerMclkIx, FLEXIO_PIN_OUTPUT); 
  FLEXIO_TimerPinSel(pConfig->timerMclkIx, pinMclkIx);
  FLEXIO_TimerPinPol(pConfig->timerMclkIx, FLEXIO_POLARITY_HIGH); 
  FLEXIO_TimerMode(pConfig->timerMclkIx, FLEXIO_TIMER_8BIT_BAUD_MODE);   
  
  pConfig->pCallBack = NULL;
  
  // Run MCLK
  FLEXIO_ClrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx ,BITBYTE_SWAPED,0xFFFFFFFF);
  while(!FLEXIO_GetShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterOutIx)));
  FLEXIO_ClrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  
  // Register the own CallBack function in FlexIO driver
  pConfig->pCallBack = NULL;
  tFLEXIO_CALLBACK_DESC callBackDesc;
  
  pConfig->state = FLEXIO_I2S_ST_IDLE;
  
  callBackDesc.SHIFTERR_MASK = 0;
  callBackDesc.SHIFTFLG_MASK = FLEXIO_MAKE_MASK(pConfig->shifterOutIx);
  callBackDesc.TIMERFLG_MASK = 0;
  callBackDesc.pCallBack = flexio_i2s_isr_callback;
  callBackDesc.user_data = (void*)pConfig; 

  if(FLEXIO_RegisterCallback(&callBackDesc, 0) < 0)
    return FLEXIO_I2S_RES_FAILED;
    
  // Initialize the FlexIO shifter register to trensmit I2S data
  FLEXIO_ShifterIrqEnable(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  
  // Dummy initial shifter write to trigger the timer 
  FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx,BITBYTE_SWAPED,0xFFFFFFFF);
  
  return FLEXIO_I2S_RES_OK;
}

/***************************************************************************//*!
* @brief   FLEXIO_I2S module Register CallBack function.
* @param   pCallback - pointer to function CallBack function (NULL for unregister)
* @return  Result of register CallBack function Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_I2S_RESULT FLEXIO_I2S_SetCallBack(FLEXIO_I2S_CONFIG * pConfig, FLEXIO_I2S_NEEDDATA_CALLBACK pCallback)
{  
  // Check if the driver is ready to access to BUS
  if(pConfig->state != FLEXIO_I2S_ST_IDLE)
    return FLEXIO_I2S_RES_BUSY;
  
  pConfig->pDataCallBack = pCallback;

  return FLEXIO_I2S_RES_OK;
}

/***************************************************************************//*!
* @brief   FLEXIO_I2S Enable playback funnction.
* @param   pConfig - pointer to flexio i2s config structure
* @return  Result of register CallBack function Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_I2S_RESULT FLEXIO_I2S_Play(FLEXIO_I2S_CONFIG * pConfig)
{
  // TODO check if the driver is in idle
  // Check if the driver is ready to access to BUS
  if(pConfig->state != FLEXIO_I2S_ST_IDLE)
    return FLEXIO_I2S_RES_BUSY;
  
  FLEXIO_ShifterPinCfg(pConfig->shifterOutIx, FLEXIO_PIN_OUTPUT);
  FLEXIO_TimerPinCfg(pConfig->timerBclkIx, FLEXIO_PIN_OUTPUT);
  FLEXIO_TimerPinCfg(pConfig->timerFsyncIx, FLEXIO_PIN_OUTPUT); 
  pConfig->state = FLEXIO_I2S_ST_TX;
  
  return FLEXIO_I2S_RES_OK;
}

/***************************************************************************//*!
* @brief   FLEXIO_I2S Stop playback funnction.
* @param   pConfig - pointer to flexio i2s config structure
* @return  Result of register CallBack function Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_I2S_RESULT FLEXIO_I2S_Stop(FLEXIO_I2S_CONFIG * pConfig)
{
  // Check if the driver is ready to access to BUS
  //if(pConfig->state != FLEXIO_I2S_ST_TX)
    //return FLEXIO_I2S_RES_BUSY;
  
  FLEXIO_ShifterPinCfg(pConfig->shifterOutIx, FLEXIO_PIN_DISABLED);
  FLEXIO_TimerPinCfg(pConfig->timerBclkIx, FLEXIO_PIN_DISABLED);
  FLEXIO_TimerPinCfg(pConfig->timerFsyncIx, FLEXIO_PIN_DISABLED);
  pConfig->state = FLEXIO_I2S_ST_STOP;
  
  return FLEXIO_I2S_RES_OK;
}

/******************************************************************************
* interrupt functions definitions                                             *
*******************************************************************************/
void flexio_i2s_isr_callback(FLEXIO_CALLBACK_TYPE type, void* user_data)
{
  FLEXIO_I2S_CONFIG * pConfig = (FLEXIO_I2S_CONFIG*)user_data;
  FLEXIO_I2S_BUF * pBuff = &pConfig->outbuf[pConfig->buffIx];
 
  // *************** Transmit mode ******************************
  // FXIO I2S Tx IRQ event
  if(pConfig->state == FLEXIO_I2S_ST_TX){
    if((uint32_t)type & (FLEXIO_MAKE_MASK(pConfig->shifterOutIx)))   
    {
       // feed the audio data to output, shift if data wide is < 32bits
       FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx,BITBYTE_SWAPED,(pBuff->pData[pConfig->dataIx])<<16);
       pConfig->dataIx++;
       
      if(pConfig->dataIx >= pBuff->len)
      {
        // TODO What if the data not ready?
        pConfig->buffIx++;
        pConfig->buffIx &= 0x01;
        pConfig->dataIx = 0;
        
        if(pConfig->pDataCallBack)
          pConfig->pDataCallBack(pBuff->pData);
        
        pBuff->pData = NULL;
      }    
    }
  }  
  
  // *************** Receive mode ******************************
  else if(pConfig->state == FLEXIO_I2S_ST_RX)
  {
    // FXIO I2S Rx IRQ event  
    if((uint32_t)type & (FLEXIO_MAKE_MASK(pConfig->shifterInIx)))
    {
       {asm ("nop");}   // do nothing so far
    }
  }
}

/******************************************************************************
* Driver Private functions                                                    *
*******************************************************************************/
FLEXIO_I2S_RESULT FLEXIO_I2S_PutData(FLEXIO_I2S_CONFIG * pConfig, int16_t* pData, uint32_t length)
{
  uint32_t i = (pConfig->buffIx + 1) & 0x01; // try currently used buff+1
  uint32_t j = i; // count number of this function calls
  
  while(pConfig->outbuf[i].pData != NULL) // buffer free? find first free
  {
    i++;
    i &= 0x01;
    if(i == j)
      return FLEXIO_I2S_RES_BUSY;     
  } 
  pConfig->outbuf[i].pData = pData;
  pConfig->outbuf[i].len   = length; 
  return FLEXIO_I2S_RES_OK;
}

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
#endif //(defined (MCU_MKL43Z256))



