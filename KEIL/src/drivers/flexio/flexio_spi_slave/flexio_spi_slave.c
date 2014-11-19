/*****************************************************************************
 * (c) Copyright 2010-2014, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flexio_spi_slave.c
 * @version   1.0.0.0
 * @date      May-22-2013
 * @brief     FlexIO SPI slave module driver source file.
 *
 * Revision History:
 *  1.	02/04/2014   B20253   Initially written for Kinetis KL43
 ******************************************************************************/
#include "common.h"
#include "drivers.h"
#include "flexio_spi_slave.h"

#if (defined (MCU_MKL43Z256))

/******************************************************************************
* private functions definitions                                              *
******************************************************************************/

/******************************************************************************
* data type definitions                                                      *
******************************************************************************/

/******************************************************************************
* interrupt callback functions prototype                                     *
******************************************************************************/
void flexio_spi_slave_isr_callback(FLEXIO_CALLBACK_TYPE type, void* user_data);

/******************************************************************************
* Public functions definitions                                               *
******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif


/***************************************************************************//*!
* @brief   FLEXIO_SPI_SLAVE_Init module initialization function.
* @param   pConfig - pointer to configuration structure 
* @param   shifterMosiIx - Index of shifter for MOSI
* @param   shifterMisoIx - Index of shifter for MISO
* @param   timerIx - Index of timer for SCLK
* @param   pinMosiIx - Index of FlexIO Pin for MISO signal
* @param   pinMisoIx - Index of FlexIO Pin for MOSI signal
* @param   pinSclkIx - Index of FlexIO Pin for SCLK signal
* @param   pinCsIx - Index of FlexIO Pin for CS signal
* @param   mode - Mode of operation   
* @return  Result of Init Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_SPI_SLAVE_RESULT FLEXIO_SPI_SLAVE_Init(  FLEXIO_SPI_SLAVE_CONFIG * pConfig,
                                                uint32 shifterMosiIx,
                                                uint32 shifterMisoIx,
                                                uint32 timerIx,
                                                uint32 pinMosiIx,
                                                uint32 pinMisoIx,
                                                uint32 pinSclkIx,
                                                uint32 pinCsIx,
                                                uint32 mode
                                              )
{
  // Store the configuration information
  pConfig->shifterMosiIx = shifterMosiIx;
  pConfig->shifterMisoIx = shifterMisoIx;
  pConfig->timerIx = timerIx;
  pConfig->mode = mode;
  pConfig->pBufferOut = NULL;
  pConfig->pBufferIn = NULL;
  
  /************ SHIFTER MOSI CONFIGURATION *************************************/

  // Initialize the FlexIO shifter register to receive SPI data
  FLEXIO_ShifterIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterMosiIx));
  FLEXIO_ShifterErrIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterMosiIx));
  FLEXIO_ShifterDmaDisable(FLEXIO_MAKE_MASK(pConfig->shifterMosiIx));
  // SetUp Shifter In CTL
  FLEXIO_ShifterTimerSel(pConfig->shifterMosiIx, pConfig->timerIx);
  FLEXIO_ShifterTimerPol(pConfig->shifterMosiIx, (mode & FLEXIO_SPI_SLAVE_CPHA_FEDGE_START_MASK)? FLEXIO_POLARITY_HIGH : FLEXIO_POLARITY_LOW);
  FLEXIO_ShifterPinCfg(pConfig->shifterMosiIx, FLEXIO_PIN_DISABLED);
  FLEXIO_ShifterPinSel(pConfig->shifterMosiIx, pinMosiIx);
  FLEXIO_ShifterPinPol(pConfig->shifterMosiIx, FLEXIO_POLARITY_HIGH);
  FLEXIO_ShifterMode(pConfig->shifterMosiIx, FLEXIO_SHIFTER_RX_MODE);

  // SetUp Shifter In CFG
  FLEXIO_ShifterInSrc(pConfig->shifterMosiIx, FLEXIO_INSRC_PIN);
  FLEXIO_ShifterStopBit(pConfig->shifterMosiIx, FLEXIO_STOPBIT_DISABLED);
  FLEXIO_ShifterStartBit(pConfig->shifterMosiIx, FLEXIO_STARTBIT_DISABLED_ON_EN);
  
  /************* TIMER CONFIGURATION **************************************/
  
  // Initialize the FlexIO timers for generate SCLK clock
  FLEXIO_SetTimerCompareVal(pConfig->timerIx, FLEXIO_CALCULATE_CMP_VAL(8));
  FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerIx));
  // SetUp Timer Out CFG
  FLEXIO_TimerClock(pConfig->timerIx, FLEXIO_LOG0_ON_EN);
  FLEXIO_TimerInc(pConfig->timerIx, FLEXIO_INC_PIN);
  FLEXIO_TimerResets(pConfig->timerIx, FLEXIO_RST_NEVER);
  FLEXIO_TimerDisablesOn(pConfig->timerIx, FLEXIO_DIS_TRIGGER_FEDGE);
  FLEXIO_TimerEnablesOn(pConfig->timerIx, FLEXIO_EN_TRIGGER_REDGE);
  
  FLEXIO_TimerStopBit(pConfig->timerIx, FLEXIO_STOP_DISABLED);
  FLEXIO_TimerStartBit(pConfig->timerIx, START_DISABLED);
  
// SetUp Timer Out CTL
  FLEXIO_TimerTrgSel(pConfig->timerIx, FLEXIO_TIMTRG_PIN(pinCsIx));
  FLEXIO_TimerTrgPol(pConfig->timerIx, FLEXIO_POLARITY_LOW);
  FLEXIO_TimerTrgSrc(pConfig->timerIx, INT_TRG);
  FLEXIO_TimerPinCfg(pConfig->timerIx, FLEXIO_PIN_DISABLED);
  FLEXIO_TimerPinSel(pConfig->timerIx, pinSclkIx);
  FLEXIO_TimerPinPol(pConfig->timerIx, (mode & FLEXIO_SPI_SLAVE_CPOL_ACTHIGH_MASK)? FLEXIO_POLARITY_HIGH : FLEXIO_POLARITY_LOW);
  FLEXIO_TimerMode(pConfig->timerIx, FLEXIO_TIMER_16BIT_MODE);
  
  /************ SHIFTER MISO CONFIGURATION **************************************/
  
  // Initialize the FlexIO shifter register to receive SPI data
  FLEXIO_ShifterIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterMisoIx));
  FLEXIO_ShifterErrIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterMisoIx));
  FLEXIO_ShifterDmaDisable(FLEXIO_MAKE_MASK(pConfig->shifterMisoIx));
  // SetUp Shifter In CTL
  FLEXIO_ShifterTimerSel(pConfig->shifterMisoIx, pConfig->timerIx);
  FLEXIO_ShifterTimerPol(pConfig->shifterMisoIx, (mode & FLEXIO_SPI_SLAVE_CPHA_FEDGE_START_MASK)? FLEXIO_POLARITY_LOW : FLEXIO_POLARITY_HIGH);
  FLEXIO_ShifterPinCfg(pConfig->shifterMisoIx, FLEXIO_PIN_OUTPUT);
  FLEXIO_ShifterPinSel(pConfig->shifterMisoIx, pinMisoIx);
  FLEXIO_ShifterPinPol(pConfig->shifterMisoIx, FLEXIO_POLARITY_HIGH);
  FLEXIO_ShifterMode(pConfig->shifterMisoIx, FLEXIO_SHIFTER_TX_MODE);

  // SetUp Shifter In CFG
  FLEXIO_ShifterInSrc(pConfig->shifterMisoIx, FLEXIO_INSRC_PIN);
  FLEXIO_ShifterStopBit(pConfig->shifterMisoIx, FLEXIO_STOPBIT_DISABLED);
  FLEXIO_ShifterStartBit(pConfig->shifterMisoIx, FLEXIO_STARTBIT_DISABLED_ON_EN);

  /************* Interrupt and callback CONFIGURATION *****************************/
  pConfig->pCallBack = NULL;
  // Register the own CallBack function in FlexIO driver
  tFLEXIO_CALLBACK_DESC callBackDesc;

  pConfig->state = FLEXIO_SPI_SLAVE_ST_IDLE;

  callBackDesc.SHIFTERR_MASK = 0;
  callBackDesc.SHIFTFLG_MASK = 0;
  callBackDesc.TIMERFLG_MASK = FLEXIO_MAKE_MASK(pConfig->timerIx);
  callBackDesc.pCallBack = flexio_spi_slave_isr_callback;
  callBackDesc.user_data = (void*)pConfig;

  if(FLEXIO_RegisterCallback(&callBackDesc, 0) < 0)
    return FLEXIO_SPI_SLAVE_RES_FAILED;

  FLEXIO_TimerIrqEnable(FLEXIO_MAKE_MASK(pConfig->timerIx));
  pConfig->state = FLEXIO_SPI_SLAVE_ST_IDLE;
  
  return FLEXIO_SPI_SLAVE_RES_OK;
}

/***************************************************************************//*!
* @brief   FLEXIO_SPI_SLAVE_SetBuffers 
* @param   pConfig - Pointer to configuration structure
* @param   pBuffOut - Pointer to data buffer
* @param   pBuffIn - Pointer to data buffer
* @param   buffOutLen - Length of the output buffer
* @param   buffInLen - Length of the input buffer
* @return  Result of Read Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_SPI_SLAVE_RESULT FLEXIO_SPI_SLAVE_SetBuffers(FLEXIO_SPI_SLAVE_CONFIG * pConfig, const uint8_t * pBuffOut, uint8_t * pBuffIn, uint32 buffOutLen, uint32 buffInLen)
{
  if(pBuffOut == NULL) return FLEXIO_SPI_SLAVE_RES_FAILED;
  pConfig->pBufferOut = pBuffOut;
  
  if(pBuffIn == NULL) return FLEXIO_SPI_SLAVE_RES_FAILED;
  pConfig->pBufferIn = pBuffIn;
  
  if(buffOutLen == 0) return FLEXIO_SPI_SLAVE_RES_FAILED;
  pConfig->buffOutLen = buffOutLen;
    
  if(buffInLen == 0) return FLEXIO_SPI_SLAVE_RES_FAILED;
  pConfig->buffInLen = buffInLen;

  return FLEXIO_SPI_SLAVE_RES_OK;  
}

/***************************************************************************//*!
* @brief   FLEXIO_SPI_SLAVE_WriteTransfer  
* @param   pConfig - Pointer to configuration structure
* @param   dataLen - Length of the tx data 
* @return  Result of Read Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_SPI_SLAVE_RESULT FLEXIO_SPI_SLAVE_WriteTransfer(FLEXIO_SPI_SLAVE_CONFIG * pConfig, uint32 dataLen)
{
  // check if out buffer initialized
  if(NULL == pConfig->pBufferOut) return FLEXIO_SPI_SLAVE_RES_FAILED;
  // check correct length of the data vs buffer out 
  if(dataLen > pConfig->buffOutLen) return FLEXIO_SPI_SLAVE_BUFF_OVF;
  // if some data pending return busy 
  if(pConfig->dataOutIx != 0) return FLEXIO_SPI_SLAVE_TX_BUSY;
    
  // data to be sent
  pConfig->dataOutLen = dataLen;
  pConfig->state = FLEXIO_SPI_SLAVE_ST_TRANSFER;
  
  return FLEXIO_SPI_SLAVE_RES_OK;  
}

/***************************************************************************//*!
* @brief   FLEXIO_SPI_SLAVE_SetCallBack module Register CallBack function.
* @param   pConfig - pointer to configuration structure
* @param   pCallback - pointer to function CallBack function (NULL for unregister)
* @return  Result of register CallBack function Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_SPI_SLAVE_RESULT FLEXIO_SPI_SLAVE_SetCallBack(FLEXIO_SPI_SLAVE_CONFIG * pConfig, FLEXIO_SPI_SLAVE_CALLBACK pCallback)
{
  // Check if the driver is ready to access to BUS
  if(pConfig->state != FLEXIO_SPI_SLAVE_ST_IDLE)
    return FLEXIO_SPI_SLAVE_RES_BUSY;

  pConfig->pCallBack = pCallback;

  return FLEXIO_SPI_SLAVE_RES_OK;
}

/******************************************************************************
* interrupt functions definitions                                             *
*******************************************************************************/
void flexio_spi_slave_isr_callback(FLEXIO_CALLBACK_TYPE type, void* user_data)
{
  FLEXIO_SPI_SLAVE_CONFIG * pConfig = (FLEXIO_SPI_SLAVE_CONFIG*)user_data;

  if((uint32_t)type & (FLEXIO_MAKE_MASK(pConfig->timerIx) << 8) )
  {  
    // Get data read on MISO signal
    if(!(pConfig->mode & FLEXIO_SPI_SLAVE_MSB_FIRST_MASK))
    {
      // if the data transfer is LSB first 
      if(pConfig->pBufferIn)
        pConfig->pBufferIn[pConfig->dataIx] = FLEXIO_ReadShifterBuffer(pConfig->shifterMosiIx, DEFAULT);
    }else
    {
      // if the data transfer is MSB first 
      if(pConfig->pBufferIn)
        pConfig->pBufferIn[pConfig->dataIx] = (FLEXIO_ReadShifterBuffer(pConfig->shifterMosiIx, BIT_SWAPED)>>24);
    }
    // Increment and test the data index
    if(++pConfig->dataIx >= pConfig->buffInLen)
    {
      // data index is set to begin of the input buffer        
      pConfig->dataIx = 0;
      if(pConfig->pCallBack)
        pConfig->pCallBack(FLEXIO_SPI_SLAVE_BUFF_OVF);
    }
    // if the tx transfer was initialized than start to send data to master
    if(pConfig->state == FLEXIO_SPI_SLAVE_ST_TRANSFER)
    { 
     // some pending data is in output buffer ?   
      if(pConfig->dataOutIx++ < pConfig->dataOutLen)
      {
        if(!(pConfig->mode & FLEXIO_SPI_MASTER_MSB_FIRST_MASK))
        {
          FLEXIO_WriteShifterBuffer(pConfig->shifterMisoIx, DEFAULT, pConfig->pBufferOut[pConfig->dataOutIx]);
        }else
        {
          FLEXIO_WriteShifterBuffer(pConfig->shifterMisoIx, BIT_SWAPED, pConfig->pBufferOut[pConfig->dataOutIx]);
        }   
      }
      else {
        // the last data was sent, switch to ready state and clear index counter
        pConfig->dataOutIx = 0;
        pConfig->state = FLEXIO_SPI_SLAVE_ST_READY;
      }
    }
  }
}

/******************************************************************************
* Driver Private functions                                                    *
*******************************************************************************/

#endif

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
