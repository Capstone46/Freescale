/*****************************************************************************
 * (c) Copyright 2010-2014, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flexio_spi_master.c
 * @version   1.0.9.0
 * @date      May-22-2013
 * @brief     FlexIOIIC module driver source file.
 *
 * Revision History:
 *  1.	xx/xx/xxxx   Bxxxxx   Initially written for Kinetis L
 ******************************************************************************/
#include "common.h"
#include "drivers.h"
#include "flexio_spi_master.h"

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
#if FLEXIO_SPI_MASTER_INTERRUPT_MODE != 0
void flexio_spi_master_isr_callback(FLEXIO_CALLBACK_TYPE type, void* user_data);
#endif

/******************************************************************************
* Public functions definitions                                               *
******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif


/***************************************************************************//*!
* @brief   FLEXIO_SPI_MASTER module initialization function.
* @param   shifterMosiIx - Index of shifter for MOSI
* @param   shifterMisoIx - Index of shifter for MISO
* @param   timerSclkIx - Index of timer for SCLK
* @param   timerCsIx - Index of timer CS
* @param   pinMosiIx - Index of FlexIO Pin for MISO signal
* @param   pinMisoIx - Index of FlexIO Pin for MOSI signal
* @param   pinSclkIx - Index of FlexIO Pin for SCLK signal
* @param   pinCsIx - Index of FlexIO Pin for CS signal
* @param   baudRate - Requested baudrate
* @param   FlexIoClk - Clock frequency of FlexIO peripheral
* @return  Result of Init Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_SPI_MASTER_RESULT FLEXIO_SPI_MASTER_Init(
                                  FLEXIO_SPI_MASTER_CONFIG * pConfig,
                                  uint32_t shifterMosiIx,
                                  uint32_t shifterMisoIx,
                                  uint32_t timerSclkIx,
                                  uint32_t timerCsIx,
                                  uint32_t pinMosiIx,
                                  uint32_t pinMisoIx,
                                  uint32_t pinSclkIx,
                                  uint32_t pinCsIx,
                                  uint32_t mode,
                                  uint32_t baudRate,
                                  uint32_t FlexIoClk
                                  )
{
  // Check if the baudrate is achievable
  if((((FlexIoClk / baudRate) / 2) - 1) > 255)
    return FLEXIO_SPI_MASTER_RES_BAUDRATE;

  // The baudare MUST be at least 4 times slower than the FlexIO clock
  if((FlexIoClk / baudRate) < 4)
    return FLEXIO_SPI_MASTER_RES_BAUDRATE;

  // The driver requires that the CS timer MUST follow the SCLK timer to proper work
  if((timerSclkIx+1) != timerCsIx)
    return FLEXIO_SPI_MASTER_RES_INVALIDPARAMETER;

  // Store the configuration information
  pConfig->shifterMosiIx = shifterMosiIx;
  pConfig->shifterMisoIx = shifterMisoIx;
  pConfig->timerSclkIx = timerSclkIx;
  pConfig->timerCsIx = timerCsIx;
  pConfig->baudRateDiv = (((FlexIoClk / baudRate) / 2) - 1);
  pConfig->mode = mode;


  if(!(pConfig->mode & FLEXIO_SPI_MASTER_MSB_FIRST_MASK))
  {
    pConfig->pShifterDataOut = &FLEXIO_SHIFTBUF(pConfig->shifterMosiIx);
    pConfig->pShifterDataIn = &FLEXIO_SHIFTBUF(pConfig->shifterMisoIx);
  }else
  {
    pConfig->pShifterDataOut = &FLEXIO_SHIFTBUFBIS(pConfig->shifterMosiIx);
    pConfig->pShifterDataIn = &FLEXIO_SHIFTBUFBIS(pConfig->shifterMisoIx);
  }
  /************ SHIFTER MOSI CONFIGURATION *************************************/

  // Initialize the FlexIO shifter register to trensmit I2C data
  FLEXIO_ShifterIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterMosiIx));
  FLEXIO_ShifterErrIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterMosiIx));
  FLEXIO_ShifterDmaDisable(FLEXIO_MAKE_MASK(pConfig->shifterMosiIx));
  // SetUp Shifter Out CTL
  FLEXIO_ShifterTimerSel(pConfig->shifterMosiIx, pConfig->timerSclkIx);
  FLEXIO_ShifterTimerPol(pConfig->shifterMosiIx, (mode & FLEXIO_SPI_MASTER_CPHA_FEDGE_START_MASK)? FLEXIO_POLARITY_HIGH : FLEXIO_POLARITY_LOW);
  FLEXIO_ShifterPinCfg(pConfig->shifterMosiIx, FLEXIO_PIN_OUTPUT);
  FLEXIO_ShifterPinSel(pConfig->shifterMosiIx, pinMosiIx);
  FLEXIO_ShifterPinPol(pConfig->shifterMosiIx, FLEXIO_POLARITY_HIGH);
  FLEXIO_ShifterMode(pConfig->shifterMosiIx, FLEXIO_SHIFTER_TX_MODE);

  // SetUp Shifter Out CFG
  FLEXIO_ShifterInSrc(pConfig->shifterMosiIx, FLEXIO_INSRC_PIN);
  FLEXIO_ShifterStopBit(pConfig->shifterMosiIx, (mode & FLEXIO_SPI_MASTER_CPHA_FEDGE_START_MASK)? FLEXIO_STOPBIT_LOG0 : FLEXIO_STOPBIT_DISABLED);
  FLEXIO_ShifterStartBit(pConfig->shifterMosiIx,(mode & FLEXIO_SPI_MASTER_CPHA_FEDGE_START_MASK)? FLEXIO_STARTBIT_DISABLED_ON_FIRST : FLEXIO_STARTBIT_DISABLED_ON_EN);

  /************ SHIFTER MISO CONFIGURATION **************************************/

  // Initialize the FlexIO shifter register to receive I2C data
  FLEXIO_ShifterIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterMisoIx));
  FLEXIO_ShifterErrIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterMisoIx));
  FLEXIO_ShifterDmaDisable(FLEXIO_MAKE_MASK(pConfig->shifterMisoIx));
  // SetUp Shifter In CTL
  FLEXIO_ShifterTimerSel(pConfig->shifterMisoIx, pConfig->timerSclkIx);
  FLEXIO_ShifterTimerPol(pConfig->shifterMisoIx, (mode & FLEXIO_SPI_MASTER_CPHA_FEDGE_START_MASK)? FLEXIO_POLARITY_LOW : FLEXIO_POLARITY_HIGH);
  FLEXIO_ShifterPinCfg(pConfig->shifterMisoIx, FLEXIO_PIN_DISABLED);
  FLEXIO_ShifterPinSel(pConfig->shifterMisoIx, pinMisoIx);
  FLEXIO_ShifterPinPol(pConfig->shifterMisoIx, FLEXIO_POLARITY_HIGH);
  FLEXIO_ShifterMode(pConfig->shifterMisoIx, FLEXIO_SHIFTER_RX_MODE);

  // SetUp Shifter In CFG
  FLEXIO_ShifterInSrc(pConfig->shifterMisoIx, FLEXIO_INSRC_PIN);
  FLEXIO_ShifterStopBit(pConfig->shifterMisoIx, FLEXIO_STOPBIT_DISABLED);
  FLEXIO_ShifterStartBit(pConfig->shifterMisoIx, FLEXIO_STARTBIT_DISABLED_ON_EN);

  /************* TIMER SCLK CONFIGURATION **************************************/

  // Initialize the FlexIO timers for generate SCLK clock

  FLEXIO_SetTimerCompareVal(pConfig->timerSclkIx, (0x00000F00 | pConfig->baudRateDiv));
  FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerSclkIx));
  // SetUp Timer Out CFG
  FLEXIO_TimerClock(pConfig->timerSclkIx, FLEXIO_LOG0_ON_EN);
  FLEXIO_TimerInc(pConfig->timerSclkIx, FLEXIO_INC_ALWAYS);
  FLEXIO_TimerResets(pConfig->timerSclkIx, FLEXIO_RST_NEVER);
  FLEXIO_TimerDisablesOn(pConfig->timerSclkIx, FLEXIO_DIS_ON_COMPARE);
  FLEXIO_TimerEnablesOn(pConfig->timerSclkIx, FLEXIO_EN_TRIGGER_HIGH);
  FLEXIO_TimerStopBit(pConfig->timerSclkIx, FLEXIO_STOP_ON_TIMER_DISABLED);
  FLEXIO_TimerStartBit(pConfig->timerSclkIx, START_ENABLED);
// SetUp Timer Out CTL
  FLEXIO_TimerTrgSel(pConfig->timerSclkIx, FLEXIO_TIMTRG_SHIFTER(pConfig->shifterMosiIx));
  FLEXIO_TimerTrgPol(pConfig->timerSclkIx, FLEXIO_POLARITY_LOW);
  FLEXIO_TimerTrgSrc(pConfig->timerSclkIx, INT_TRG);
  FLEXIO_TimerPinCfg(pConfig->timerSclkIx, FLEXIO_PIN_OUTPUT);
  FLEXIO_TimerPinSel(pConfig->timerSclkIx, pinSclkIx);
  FLEXIO_TimerPinPol(pConfig->timerSclkIx, (mode & FLEXIO_SPI_MASTER_CPOL_ACTHIGH_MASK)? FLEXIO_POLARITY_HIGH : FLEXIO_POLARITY_LOW);
  FLEXIO_TimerMode(pConfig->timerSclkIx, FLEXIO_TIMER_8BIT_BAUD_MODE);

  /************* TIMER CS CONFIGURATION ***************************************/

  // Never Compare
  FLEXIO_SetTimerCompareVal(pConfig->timerCsIx, 0x0000FFFF);

  FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerCsIx));
  // SetUp Timer Out CFG
  FLEXIO_TimerClock(pConfig->timerCsIx, FLEXIO_LOG1_ON_EN);
  FLEXIO_TimerInc(pConfig->timerCsIx, FLEXIO_INC_ALWAYS);
  FLEXIO_TimerResets(pConfig->timerCsIx, FLEXIO_RST_NEVER);
  FLEXIO_TimerDisablesOn(pConfig->timerCsIx, FLEXIO_DIS_PREVIOUS_TIM_DIS);
  FLEXIO_TimerEnablesOn(pConfig->timerCsIx, FLEXIO_EN_PREVIOUS_TIM_DIS);
  FLEXIO_TimerStopBit(pConfig->timerCsIx, FLEXIO_STOP_DISABLED);
  FLEXIO_TimerStartBit(pConfig->timerCsIx, START_DISABLED);
  // SetUp Timer Out CTL
  FLEXIO_TimerTrgSel(pConfig->timerCsIx, FLEXIO_TIMTRG_PIN(pinMosiIx));
  FLEXIO_TimerTrgPol(pConfig->timerCsIx, FLEXIO_POLARITY_HIGH);
  FLEXIO_TimerTrgSrc(pConfig->timerCsIx, EXT_TRG);
  FLEXIO_TimerPinCfg(pConfig->timerCsIx, FLEXIO_PIN_OUTPUT);
  FLEXIO_TimerPinSel(pConfig->timerCsIx, pinCsIx);
  FLEXIO_TimerPinPol(pConfig->timerCsIx, FLEXIO_POLARITY_LOW);
  FLEXIO_TimerMode(pConfig->timerCsIx, FLEXIO_TIMER_16BIT_MODE);



  #if FLEXIO_SPI_MASTER_INTERRUPT_MODE != 0
  {
    pConfig->pCallBack = NULL;
    // Register the own CallBack function in FlexIO driver
    tFLEXIO_CALLBACK_DESC callBackDesc;

    pConfig->state = FLEXIO_SPI_MASTER_ST_IDLE;

    callBackDesc.SHIFTERR_MASK = 0;
    callBackDesc.SHIFTFLG_MASK = FLEXIO_MAKE_MASK(pConfig->shifterMisoIx);
    callBackDesc.TIMERFLG_MASK = 0;
    callBackDesc.pCallBack = flexio_spi_master_isr_callback;
    callBackDesc.user_data = (void*)pConfig;

    if(FLEXIO_RegisterCallback(&callBackDesc, 0) < 0)
      return FLEXIO_SPI_MASTER_RES_FAILED;
  }
  #endif


  return FLEXIO_SPI_MASTER_RES_OK;
}

/***************************************************************************//*!
* @brief   FLEXIO_SPI_MASTER module Write data function.
* @param   address - slave chip address
* @param   pBuffer - pointer to data buffer
* @param   len - length of data (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @return  Result of Write Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_SPI_MASTER_RESULT FLEXIO_SPI_MASTER_Write(FLEXIO_SPI_MASTER_CONFIG * pConfig, const uint8_t * pBuffer, const uint32_t len)
{
  return FLEXIO_SPI_MASTER_Transfer(pConfig, pBuffer, NULL, len);
}

/***************************************************************************//*!
* @brief   FLEXIO_SPI_MASTER module Read data function.
* @param   address - slave chip address
* @param   pBuffer - pointer to data buffer
* @param   len - length of data (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @return  Result of Read Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_SPI_MASTER_RESULT FLEXIO_SPI_MASTER_Read(FLEXIO_SPI_MASTER_CONFIG * pConfig, uint8_t * pBuffer, const uint32_t len)
{
  return FLEXIO_SPI_MASTER_Transfer(pConfig, NULL, pBuffer, len);
}



#if FLEXIO_SPI_MASTER_INTERRUPT_MODE != 0

/***************************************************************************//*!
* @brief   FLEXIO_SPI_MASTER module Register CallBack function.
* @param   pCallback - pointer to function CallBack function (NULL for unregister)
* @return  Result of register CallBack function Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_SPI_MASTER_RESULT FLEXIO_SPI_MASTER_SetCallBack(FLEXIO_SPI_MASTER_CONFIG * pConfig, FLEXIO_SPI_MASTER_CALLBACK pCallback)
{
  // Check if the driver is ready to access to BUS
  if(pConfig->state != FLEXIO_SPI_MASTER_ST_IDLE)
    return FLEXIO_SPI_MASTER_RES_BUSY;

  pConfig->pCallBack = pCallback;

  return FLEXIO_SPI_MASTER_RES_OK;
}

/***************************************************************************//*!
* @brief   FLEXIO_SPI_MASTER module transfer (Write/Read sequence) data function.
* @param   pConfig - pointer to SPI module instance data structure
* @param   pBufferOut - pointer to data buffer for write sequence
* @param   pBufferIn - pointer to data buffer for read sequence
* @param   len - length of data for transfer sequence
* @return  Result of Transfer (Write/Read sequence) Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_SPI_MASTER_RESULT FLEXIO_SPI_MASTER_Transfer(FLEXIO_SPI_MASTER_CONFIG * pConfig, const uint8_t * pBufferOut, uint8_t * pBufferIn, const uint32_t len)
{
  uint32_t  data;

  // Check if the config structure exists
  if(pConfig == NULL)
    return FLEXIO_SPI_MASTER_RES_INVALIDPARAMETER;

  // Check if there is at least one direction valid parameters
  if((!len) || ((pBufferIn == NULL) && (pBufferOut == NULL)))
    return FLEXIO_SPI_MASTER_RES_INVALIDPARAMETER;

  pConfig->state = FLEXIO_SPI_MASTER_ST_TRANSFER;

  //Fill up the interrupt content structure
  pConfig->pBufferOut = pBufferOut;
  pConfig->pBufferIn = pBufferIn;
  pConfig->len = len;
  pConfig->dataIx = 0;

  // Clear possible pending flags
  (void)FLEXIO_ReadShifterBuffer(pConfig->shifterMisoIx, DEFAULT);

  // In case of 1 byte transfer prepare the CS deassert
  if(len != 1)
  {
    FLEXIO_TimerDisablesOn(pConfig->timerCsIx, FLEXIO_DIS_NEVER);
  }

  // Prepare the interrupt source
  FLEXIO_ClrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterMisoIx));
  FLEXIO_ShifterIrqEnable(FLEXIO_MAKE_MASK(pConfig->shifterMisoIx));

  // Prepare data to write on BUS
  if(pBufferOut)
    data = pBufferOut[0];
  else
    data = -1;

  *(pConfig->pShifterDataOut) = data;

  return FLEXIO_SPI_MASTER_RES_OK;
}

/******************************************************************************
* interrupt functions definitions                                             *
*******************************************************************************/
void flexio_spi_master_isr_callback(FLEXIO_CALLBACK_TYPE type, void* user_data)
{
  FLEXIO_SPI_MASTER_CONFIG * pConfig = (FLEXIO_SPI_MASTER_CONFIG*)user_data;
  uint32_t data;

  // Get data read on MISO signal
  data = *(pConfig->pShifterDataIn);

  // Store it, it is possible
  if(pConfig->pBufferIn)
    pConfig->pBufferIn[pConfig->dataIx] = data;

  // Incremeant the dat index
  pConfig->dataIx++;

  if(pConfig->dataIx >= pConfig->len)
  {
    FLEXIO_ShifterIrqEnable(FLEXIO_MAKE_MASK(pConfig->shifterMisoIx));

    pConfig->state = FLEXIO_SPI_MASTER_ST_IDLE;

    if(pConfig->pCallBack)
      pConfig->pCallBack(FLEXIO_SPI_MASTER_RES_OK);

  }else
  {

    // Write Data on BUS
    if(pConfig->pBufferOut)
      data = pConfig->pBufferOut[pConfig->dataIx];
    else
      data = -1;

    if(pConfig->dataIx+1 >= pConfig->len)
    {
      FLEXIO_TimerDisablesOn(pConfig->timerCsIx, FLEXIO_DIS_PREVIOUS_TIM_DIS);
    }

    *(pConfig->pShifterDataOut) = data;
  }
}

#else

/***************************************************************************//*!
* @brief   FLEXIO_SPI_MASTER module transfer (Write/Read sequence) data function.
* @param   pConfig - pointer to SPI module instance data structure
* @param   pBufferOut - pointer to data buffer for write sequence
* @param   pBufferIn - pointer to data buffer for read sequence
* @param   len - length of data for transfer sequence
* @return  Result of Transfer (Write/Read sequence) Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_SPI_MASTER_RESULT FLEXIO_SPI_MASTER_Transfer(FLEXIO_SPI_MASTER_CONFIG * pConfig, const uint8_t * pBufferOut, uint8_t * pBufferIn, const uint32_t len)
{
  uint32_t i, data;
  if(pConfig == NULL)
    return FLEXIO_SPI_MASTER_RES_INVALIDPARAMETER;

  if((!len) || ((pBufferIn == NULL) && (pBufferOut == NULL)))
    return FLEXIO_SPI_MASTER_RES_INVALIDPARAMETER;

  // Clear possible pending flags
  FLEXIO_ClrTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerSclkIx));
  FLEXIO_ClrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterMisoIx));

  (void)FLEXIO_ReadShifterBuffer(pConfig->shifterMisoIx, DEFAULT);

  FLEXIO_TimerDisablesOn(pConfig->timerCsIx, FLEXIO_DIS_NEVER);

  for(i = 0; i < len; i++)
  {
    if(i+1 >= len)
    {
      FLEXIO_TimerDisablesOn(pConfig->timerCsIx, FLEXIO_DIS_PREVIOUS_TIM_DIS);
    }

    // Write Data on BUS
    if(pBufferOut)
      data = pBufferOut[i];
    else
      data = -1;

    *(pConfig->pShifterDataOut) = data;

    // Wait for send  & receive of data
    while(!FLEXIO_GetShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterMisoIx))){};

    data = *(pConfig->pShifterDataIn);

    if(pBufferIn)
      pBufferIn[i] = data;
  }

  // return the status
  return FLEXIO_SPI_MASTER_RES_OK;
}

/******************************************************************************
* Driver Private functions                                                    *
*******************************************************************************/


#endif

#endif

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
