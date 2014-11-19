/*****************************************************************************
 * (c) Copyright 2010-2014, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flexio_i2c.c
 * @version   1.0.9.0
 * @date      May-22-2013
 * @brief     FlexIOIIC module driver source file.
 *
 * Revision History:
 *  1.	xx/xx/xxxx   Bxxxxx   Initially written for Kinetis L
 ******************************************************************************/
#include "common.h"
#include "drivers.h"
#include "flexio_i2c.h"

#if (defined (MCU_MKL43Z256))

/******************************************************************************
* private functions definitions                                              *
******************************************************************************/
#if FLEXIO_I2C_INTERRUPT_MODE == 0
  static FLEXIO_I2C_RESULT FLEXIO_I2C_Write_Internal(FLEXIO_I2C_CONFIG * pConfig, const uint8_t address, const uint8_t * pBuffer, const uint32_t len);
#endif

static void  FLEXIO_I2C_Stop(FLEXIO_I2C_CONFIG * pConfig);
/******************************************************************************
* data type definitions                                                      *
******************************************************************************/


/******************************************************************************
* interrupt callback functions prototype                                     *
******************************************************************************/
#if FLEXIO_I2C_INTERRUPT_MODE != 0
void flexio_i2c_isr_callback(FLEXIO_CALLBACK_TYPE type, void* user_data);
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
* @brief   FLEXIOI2C module initialization function.
* @param   shifterOutIx - Index of shifter for transmit
* @param   shifterInIx - Index of shifter for receive and ACK
* @param   timerOutIx - Index of timer for transmit
* @param   timerInIx - Index of timer for clocking of shifter registers
* @param   pinSclIx - Index of FlexIO Pin for SCL signal
* @param   pinSdaIx - Index of FlexIO Pin for SDA signal
* @param   baudRate - Requested baudrate
* @param   FlexIoClk - Clock frequency of LexIO peripheral
* @return  Result of Init Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_I2C_RESULT FLEXIO_I2C_Init(
                                  FLEXIO_I2C_CONFIG * pConfig,
                                  uint32_t shifterOutIx,
                                  uint32_t shifterInIx,
                                  uint32_t timerOutIx,
                                  uint32_t timerInIx,
                                  uint32_t pinSclIx,
                                  uint32_t pinSdaIx,
                                  uint32_t baudRate,
                                  uint32_t FlexIoClk
                                  )
{
  if((((FlexIoClk / baudRate) / 2) - 3) > 255)
    return FLEXIO_I2C_RES_BAUDRATE;

  // Store the configuration information
  pConfig->shifterOutIx = shifterOutIx;
  pConfig->shifterInIx = shifterInIx;
  pConfig->timerOutIx = timerOutIx;
  pConfig->timerInIx = timerInIx;
  pConfig->baudRateDiv = (((FlexIoClk / baudRate) / 2) - 3);

  /************ SHIFTER OUT CONFIGURATION *************************************/

  // Initialize the FlexIO shifter register to trensmit I2C data
  FLEXIO_ShifterIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  FLEXIO_ShifterErrIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  FLEXIO_ShifterDmaDisable(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  // SetUp Shifter Out CTL
  FLEXIO_ShifterTimerSel(pConfig->shifterOutIx, pConfig->timerInIx);
  FLEXIO_ShifterTimerPol(pConfig->shifterOutIx, FLEXIO_POLARITY_HIGH);
  FLEXIO_ShifterPinCfg(pConfig->shifterOutIx, FLEXIO_PIN_OD_BI_OUTPUT);
  FLEXIO_ShifterPinSel(pConfig->shifterOutIx, pinSdaIx);
  FLEXIO_ShifterPinPol(pConfig->shifterOutIx, FLEXIO_POLARITY_LOW);
  FLEXIO_ShifterMode(pConfig->shifterOutIx, FLEXIO_SHIFTER_TX_MODE);

  // SetUp Shifter Out CFG
  FLEXIO_ShifterInSrc(pConfig->shifterOutIx, FLEXIO_INSRC_PIN);
  FLEXIO_ShifterStopBit(pConfig->shifterOutIx, FLEXIO_STOPBIT_LOG1);
  FLEXIO_ShifterStartBit(pConfig->shifterOutIx, FLEXIO_STARTBIT_LOG0);

  /************ SHIFTER IN CONFIGURATION **************************************/

  // Initialize the FlexIO shifter register to receive I2C data
  FLEXIO_ShifterIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  FLEXIO_ShifterErrIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  FLEXIO_ShifterDmaDisable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  // SetUp Shifter In CTL
  FLEXIO_ShifterTimerSel(pConfig->shifterInIx, pConfig->timerInIx);
  FLEXIO_ShifterTimerPol(pConfig->shifterInIx, FLEXIO_POLARITY_LOW);
  FLEXIO_ShifterPinCfg(pConfig->shifterInIx, FLEXIO_PIN_DISABLED);
  FLEXIO_ShifterPinSel(pConfig->shifterInIx, pinSdaIx);
  FLEXIO_ShifterPinPol(pConfig->shifterInIx, FLEXIO_POLARITY_HIGH);
  FLEXIO_ShifterMode(pConfig->shifterInIx, FLEXIO_SHIFTER_RX_MODE);

  // SetUp Shifter In CFG
  FLEXIO_ShifterInSrc(pConfig->shifterInIx, FLEXIO_INSRC_PIN);
  FLEXIO_ShifterStopBit(pConfig->shifterInIx, FLEXIO_STOPBIT_LOG0);
  FLEXIO_ShifterStartBit(pConfig->shifterInIx, FLEXIO_STARTBIT_DISABLED_ON_EN);

  /************* TIMER OUT CONFIGURATION **************************************/

  // Initialize the FlexIO timers for generate SCL clock
  // Configure 2 word transfer with baud rate of divide by 4 of the FlexIO clock. Set
  // TIMCMP[15:8] = (number of words x 18) + 1. Set TIMCMP[7:0] = (baud rate divider / 2) - 1.
  FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, 0x00000101);
  FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerOutIx));
  // SetUp Timer Out CFG
  FLEXIO_TimerClock(pConfig->timerOutIx, FLEXIO_LOG0_ON_EN);
  FLEXIO_TimerInc(pConfig->timerOutIx, FLEXIO_INC_ALWAYS);
  FLEXIO_TimerResets(pConfig->timerOutIx, FLEXIO_RST_PIN_OUT);
  FLEXIO_TimerDisablesOn(pConfig->timerOutIx, FLEXIO_DIS_ON_COMPARE);
  FLEXIO_TimerEnablesOn(pConfig->timerOutIx, FLEXIO_EN_TRIGGER_HIGH);
  FLEXIO_TimerStopBit(pConfig->timerOutIx, FLEXIO_STOP_ON_TIMER_DISABLED);
  FLEXIO_TimerStartBit(pConfig->timerOutIx, START_ENABLED);
// SetUp Timer Out CTL
  FLEXIO_TimerTrgSel(pConfig->timerOutIx, FLEXIO_TIMTRG_SHIFTER(pConfig->shifterOutIx));
  FLEXIO_TimerTrgPol(pConfig->timerOutIx, FLEXIO_POLARITY_LOW);
  FLEXIO_TimerTrgSrc(pConfig->timerOutIx, INT_TRG);
  FLEXIO_TimerPinCfg(pConfig->timerOutIx, FLEXIO_PIN_OD_BI_OUTPUT);
  FLEXIO_TimerPinSel(pConfig->timerOutIx, pinSclIx);
  FLEXIO_TimerPinPol(pConfig->timerOutIx, FLEXIO_POLARITY_HIGH);
  FLEXIO_TimerMode(pConfig->timerOutIx, FLEXIO_TIMER_8BIT_BAUD_MODE);

  /************* TIMER IN CONFIGURATION ***************************************/

  // Configure 8-bit transfer. Set TIMCMP[15:0] = (number of bits x 2) - 1.
  // SetUp the counter of Input timer of clocks
  FLEXIO_SetTimerCompareVal(pConfig->timerInIx, 0x0000000F);

  FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerInIx));
  // SetUp Timer Out CFG
  FLEXIO_TimerClock(pConfig->timerInIx, FLEXIO_LOG1_ON_EN);
  FLEXIO_TimerInc(pConfig->timerInIx, FLEXIO_INC_PIN);
  FLEXIO_TimerResets(pConfig->timerInIx, FLEXIO_RST_NEVER);
  FLEXIO_TimerDisablesOn(pConfig->timerInIx, FLEXIO_DIS_PREVIOUS_TIM_DIS);
  FLEXIO_TimerEnablesOn(pConfig->timerInIx, FLEXIO_EN_PREVIOUS_TIM_DIS);
  FLEXIO_TimerStopBit(pConfig->timerInIx, FLEXIO_STOP_ON_COMPARE);
  FLEXIO_TimerStartBit(pConfig->timerInIx, START_ENABLED);
  // SetUp Timer Out CTL
  FLEXIO_TimerTrgSel(pConfig->timerInIx, FLEXIO_TIMTRG_SHIFTER(pConfig->shifterOutIx));
  FLEXIO_TimerTrgPol(pConfig->timerInIx, FLEXIO_POLARITY_LOW);
  FLEXIO_TimerTrgSrc(pConfig->timerInIx, INT_TRG);
  FLEXIO_TimerPinCfg(pConfig->timerInIx, FLEXIO_PIN_DISABLED);
  FLEXIO_TimerPinSel(pConfig->timerInIx, pinSclIx);
  FLEXIO_TimerPinPol(pConfig->timerInIx, FLEXIO_POLARITY_LOW);
  FLEXIO_TimerMode(pConfig->timerInIx, FLEXIO_TIMER_16BIT_MODE);

  pConfig->combo = 0;


  #if FLEXIO_I2C_INTERRUPT_MODE != 0
  {
    pConfig->pCallBack = NULL;
    // Register the own CallBack function in FlexIO driver
    tFLEXIO_CALLBACK_DESC callBackDesc;

    pConfig->state = FLEXIO_I2C_ST_IDLE;

    callBackDesc.SHIFTERR_MASK = 0;
    callBackDesc.SHIFTFLG_MASK = FLEXIO_MAKE_MASK(pConfig->shifterInIx);
    callBackDesc.TIMERFLG_MASK = FLEXIO_MAKE_MASK(pConfig->timerOutIx);
    callBackDesc.pCallBack = flexio_i2c_isr_callback;
    callBackDesc.user_data = (void*)pConfig;

    if(FLEXIO_RegisterCallback(&callBackDesc, 0) < 0)
      return FLEXIO_I2C_RES_FAILED;
  }
  #endif


  return FLEXIO_I2C_RES_OK;
}

#if FLEXIO_I2C_INTERRUPT_MODE != 0

/***************************************************************************//*!
* @brief   FLEXIO_I2C module Register CallBack function.
* @param   pCallback - pointer to function CallBack function (NULL for unregister)
* @return  Result of register CallBack function Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_I2C_RESULT FLEXIO_I2C_SetCallBack(FLEXIO_I2C_CONFIG * pConfig, FLEXIO_I2C_CALLBACK pCallback)
{
  // Check the configuration structure
  if(pConfig == NULL)
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  // Check if the driver is ready to access to BUS
  if(pConfig->state != FLEXIO_I2C_ST_IDLE)
    return FLEXIO_I2C_RES_BUSY;

  pConfig->pCallBack = pCallback;

  return FLEXIO_I2C_RES_OK;
}

/***************************************************************************//*!
* @brief   FLEXIO_I2C module Write data function.
* @param   address - slave chip address
* @param   pBuffer - pointer to data buffer
* @param   len - length of data (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @return  Result of Write Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_I2C_RESULT FLEXIO_I2C_Write(FLEXIO_I2C_CONFIG * pConfig, const uint8_t address, const uint8_t * pBuffer, const uint32_t len)
{
  // Check the configuration structure
  if(pConfig == NULL)
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  // Check if the driver is ready to access to BUS
  if(pConfig->state != FLEXIO_I2C_ST_IDLE)
    return FLEXIO_I2C_RES_BUSY;

  // Check input parameters
  if((!len) || (pBuffer == NULL))
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  pConfig->state = FLEXIO_I2C_ST_TX;

  // Select the mode of transfer
  pConfig->combo = 0;
  pConfig->address = address;
  pConfig->pBufferOut = pBuffer;
  pConfig->lenOut = len;
  pConfig->dataIx = 0;

  // Clear possible pending flags
  FLEXIO_ClrErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  FLEXIO_ClrTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerOutIx));
  FLEXIO_ClrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));

  // Set up timer
  // 9 bits * 2 - 1,- shifted to second byte
  FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, ((17 << 8) + pConfig->baudRateDiv));

  FLEXIO_ShifterIrqEnable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  // Write the chip address byte
  FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, FLEXIO_I2C_WRITE(address));

  return FLEXIO_I2C_RES_OK;
}

/***************************************************************************//*!
* @brief   FLEXIO_I2C module Read data function.
* @param   address - slave chip address
* @param   pBuffer - pointer to data buffer
* @param   len - length of data (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @return  Result of Read Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_I2C_RESULT FLEXIO_I2C_Read(FLEXIO_I2C_CONFIG * pConfig, const uint8_t address, uint8_t * pBuffer, const uint32_t len)
{
  // Check the configuration structure
  if(pConfig == NULL)
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  // Check if the driver is ready to access to BUS
  if(pConfig->state != FLEXIO_I2C_ST_IDLE)
    return FLEXIO_I2C_RES_BUSY;

  if((!len) || (pBuffer == NULL))
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  pConfig->state = FLEXIO_I2C_ST_RX;

  // Select the mode of transfer
  pConfig->combo = 0;
  pConfig->address = address;
  pConfig->pBufferIn = pBuffer;
  pConfig->lenIn = len;
  pConfig->dataIx = -1;

  FLEXIO_ClrErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));  //Clear the possible shifter error flag
  FLEXIO_ClrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  FLEXIO_ClrTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerOutIx));

  FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, ((17 << 8) + pConfig->baudRateDiv)); // Set up timer

  FLEXIO_ShifterIrqEnable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));

  FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, FLEXIO_I2C_READ(address)); // Write the chip address byte

  return FLEXIO_I2C_RES_OK;
}

/***************************************************************************//*!
* @brief   FLEXIO_I2C module Combo (Write/Read sequence) data function.
* @param   address - slave chip address
* @param   pBufferOut - pointer to data buffer for write sequence
* @param   lenOut - length of data for write sequence (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @param   pBufferIn - pointer to data buffer for read sequence
* @param   lenIn - length of data for read sequence (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @return  Result of Combo (Write/Read sequence) Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_I2C_RESULT FLEXIO_I2C_Combo(FLEXIO_I2C_CONFIG * pConfig, const uint8_t address, const uint8_t * pBufferOut, const uint32_t lenOut, uint8_t * pBufferIn, const uint32_t lenIn)
{
  // Check the configuration structure
  if(pConfig == NULL)
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  // Check if the driver is ready to access to BUS
  if(pConfig->state != FLEXIO_I2C_ST_IDLE)
    return FLEXIO_I2C_RES_BUSY;

  // Check input parameters
  if((!lenOut) || (pBufferOut == NULL) || (!lenIn) || (pBufferOut == NULL))
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  pConfig->state = FLEXIO_I2C_ST_TX;

  // Select the mode of transfer
  pConfig->combo = 0xFF;
  pConfig->address = address;
  pConfig->pBufferOut = pBufferOut;
  pConfig->lenOut = lenOut;
  pConfig->pBufferIn = pBufferIn;
  pConfig->lenIn = lenIn;
  pConfig->dataIx = 0;

  // Clear possible pending flags
  FLEXIO_ClrErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  FLEXIO_ClrTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerOutIx));
  FLEXIO_ClrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));

  // Set up timer
  // 9 bits * 2 - 1,- shifted to second byte
  FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, ((17 << 8) + pConfig->baudRateDiv));

  FLEXIO_ShifterIrqEnable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  // Write the chip address byte
  FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, FLEXIO_I2C_WRITE(address));

  return FLEXIO_I2C_RES_OK;
}

/******************************************************************************
* interrupt functions definitions                                             *
*******************************************************************************/
void flexio_i2c_isr_callback(FLEXIO_CALLBACK_TYPE type, void* user_data)
{
  FLEXIO_I2C_CONFIG * pConfig = (FLEXIO_I2C_CONFIG*)user_data;

  if(pConfig->state == FLEXIO_I2C_ST_TX)
  {
    // *************** Transmit mode ******************************
    if((uint32_t)type & (FLEXIO_MAKE_MASK(pConfig->shifterInIx)))
    {

      // Check the Slave ACK
      if(FLEXIO_GetErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx)))
      {
        FLEXIO_I2C_Stop(pConfig);
        pConfig->state = FLEXIO_I2C_ST_IDLE;

        if(pConfig->pCallBack)
          pConfig->pCallBack(FLEXIO_I2C_RES_NACK);

        return;
      }

      if(pConfig->dataIx < pConfig->lenOut)
      {
        // 9 bits * 2 - 1,- shifted to second byte
        FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, ((17 << 8) + pConfig->baudRateDiv));

        // Write Data on BUS
        FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, pConfig->pBufferOut[pConfig->dataIx]);

        pConfig->dataIx++;
      }else
      {
        // 1bit stop,- shifted to second byte
        FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, ((1 << 8) + pConfig->baudRateDiv));

        FLEXIO_ShifterStartBit(pConfig->shifterOutIx, FLEXIO_STARTBIT_DISABLED_ON_FIRST);

        // Generate Repeat Start or Stop condition on BUS
        FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, pConfig->combo);
        pConfig->dataIx = 0;

        FLEXIO_ShifterIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
        FLEXIO_TimerIrqEnable(FLEXIO_MAKE_MASK(pConfig->timerOutIx));

      }
    }

    if((uint32_t)type & ((FLEXIO_MAKE_MASK(pConfig->timerOutIx)) << 8))
    {

      FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerOutIx));

      FLEXIO_ShifterStartBit(pConfig->shifterOutIx, FLEXIO_STARTBIT_LOG0);

      //Finished of whole transmition
      if(pConfig->combo)
      {
        // Repeat start is generated do read operation
        pConfig->dataIx = -1;

        pConfig->state = FLEXIO_I2C_ST_RX;

        FLEXIO_ClrErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));  //Clear the possible shifter error flag
        FLEXIO_ClrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
        FLEXIO_ClrTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerOutIx));

        FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, ((17 << 8) + pConfig->baudRateDiv)); // Set up timer

        FLEXIO_ShifterIrqEnable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));

        FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, FLEXIO_I2C_READ(pConfig->address)); // Write the chip address byte

      }else
      {
        pConfig->state = FLEXIO_I2C_ST_IDLE;

        if(pConfig->pCallBack)
          pConfig->pCallBack(FLEXIO_I2C_RES_OK);
      }
    }
  }else if(pConfig->state == FLEXIO_I2C_ST_RX)
  {
    // *************** Receive mode ******************************
    if((uint32_t)type & (FLEXIO_MAKE_MASK(pConfig->shifterInIx)))
    {
      //Check the address stage ACK
      if(pConfig->dataIx == -1)
      {
        // Check the Slave ACK
        if(FLEXIO_GetErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx)))
        {
          FLEXIO_I2C_Stop(pConfig);
          pConfig->state = FLEXIO_I2C_ST_IDLE;

          if(pConfig->pCallBack)
            pConfig->pCallBack(FLEXIO_I2C_RES_NACK);

          return;
        }

        (void)FLEXIO_ReadShifterBuffer(pConfig->shifterInIx, DEFAULT);

        FLEXIO_ShifterStopBit(pConfig->shifterOutIx, FLEXIO_STOPBIT_LOG0);

        // 9 bits * 2 - 1,- shifted to second byte
        FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, ((17 << 8) + pConfig->baudRateDiv));

        pConfig->dataIx = 0;

        // Last Byte should NOT be acknowledged
        if(pConfig->dataIx == (pConfig->lenIn - 1))
          FLEXIO_ShifterStopBit(pConfig->shifterOutIx, FLEXIO_STOPBIT_LOG1);

        // Write the dummy logic ones
        FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, 0xFF);

      }else
      {
        if(pConfig->dataIx < (pConfig->lenIn - 1))
        {
          // Get the received data
          pConfig->pBufferIn[pConfig->dataIx] = FLEXIO_ReadShifterBuffer(pConfig->shifterInIx, BITBYTE_SWAPED);

          pConfig->dataIx++;

          // 9 bits * 2 - 1,- shifted to second byte
          FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, ((17 << 8) + pConfig->baudRateDiv));

          // Last Byte should NOT be acknowledged
          if(pConfig->dataIx == (pConfig->lenIn - 1))
            FLEXIO_ShifterStopBit(pConfig->shifterOutIx, FLEXIO_STOPBIT_LOG1);

          // Write the dummy logic ones
          FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, 0xFF);
        }else
        {
          pConfig->pBufferIn[pConfig->dataIx] = FLEXIO_ReadShifterBuffer(pConfig->shifterInIx, BITBYTE_SWAPED);
          // Do STOP condition
          // 1bit stop,- shifted to second byte
          FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, ((1 << 8) + pConfig->baudRateDiv));

          FLEXIO_ShifterStartBit(pConfig->shifterOutIx, FLEXIO_STARTBIT_DISABLED_ON_FIRST);

          // Generate Repeat Start or Stop condition on BUS
          FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, 0x00);

          FLEXIO_ShifterIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
          FLEXIO_TimerIrqEnable(FLEXIO_MAKE_MASK(pConfig->timerOutIx));
        }
      }
    }

    if((uint32_t)type & ((FLEXIO_MAKE_MASK(pConfig->timerOutIx)) << 8))
    {
      FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerOutIx));

      FLEXIO_ShifterStartBit(pConfig->shifterOutIx, FLEXIO_STARTBIT_LOG0);

      pConfig->state = FLEXIO_I2C_ST_IDLE;

      if(pConfig->pCallBack)
        pConfig->pCallBack(FLEXIO_I2C_RES_OK);

    }
  }
}

#else

/***************************************************************************//*!
* @brief   FLEXIO_I2C module Write data function.
* @param   address - slave chip address
* @param   pBuffer - pointer to data buffer
* @param   len - length of data (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @return  Result of Write Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_I2C_RESULT FLEXIO_I2C_Write(FLEXIO_I2C_CONFIG * pConfig, const uint8_t address, const uint8_t * pBuffer, const uint32_t len)
{
  // Check the configuration structure
  if(pConfig == NULL)
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  pConfig->combo = 0;
  return FLEXIO_I2C_Write_Internal(pConfig, address, pBuffer, len);
}

/***************************************************************************//*!
* @brief   FLEXIO_I2C module Read data function.
* @param   address - slave chip address
* @param   pBuffer - pointer to data buffer
* @param   len - length of data (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @return  Result of Read Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_I2C_RESULT FLEXIO_I2C_Read(FLEXIO_I2C_CONFIG * pConfig, const uint8_t address, uint8_t * pBuffer, const uint32_t len)
{
  uint32_t timerCompare, i;

  // Check the configuration structure
  if(pConfig == NULL)
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  if((!len) || (pBuffer == NULL))
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  FLEXIO_ClrErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));  //Clear the possible shifter error flag
  FLEXIO_ClrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  FLEXIO_ClrTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerOutIx));

  timerCompare = (17 << 8) + pConfig->baudRateDiv; // 9 bits * 2 - 1,- shifted to second byte
  FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, timerCompare); // Set up timer

  FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, FLEXIO_I2C_READ(address)); // Write the chip address byte

  while(!FLEXIO_GetShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx))){};

  if(FLEXIO_GetErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx)))
  {
    FLEXIO_I2C_Stop(pConfig);
    return FLEXIO_I2C_RES_NACK;
  }

  (void)FLEXIO_ReadShifterBuffer(pConfig->shifterInIx, DEFAULT);

  FLEXIO_ShifterStopBit(pConfig->shifterOutIx, FLEXIO_STOPBIT_LOG0);

  for(i = 0; i < len; i++)
  {
    timerCompare = (17 << 8) + pConfig->baudRateDiv; // 9 bits * 2 - 1,- shifted to second byte
    FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, timerCompare);

    // Last Byte MUST NOT have ACK
    if(i == (len - 1))
      FLEXIO_ShifterStopBit(pConfig->shifterOutIx, FLEXIO_STOPBIT_LOG1);

    FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, 0xFF); // Write the dummy logic ones

    while(!FLEXIO_GetShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx))){};

    pBuffer[i] = FLEXIO_ReadShifterBuffer(pConfig->shifterInIx, BITBYTE_SWAPED);
  }

  FLEXIO_I2C_Stop(pConfig);

  return FLEXIO_I2C_RES_OK;
}

/***************************************************************************//*!
* @brief   FLEXIO_I2C module Combo (Write/Read sequence) data function.
* @param   address - slave chip address
* @param   pBufferOut - pointer to data buffer for write sequence
* @param   lenOut - length of data for write sequence (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @param   pBufferIn - pointer to data buffer for read sequence
* @param   lenIn - length of data for read sequence (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @return  Result of Combo (Write/Read sequence) Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_I2C_RESULT FLEXIO_I2C_Combo(FLEXIO_I2C_CONFIG * pConfig, const uint8_t address, const uint8_t * pBufferOut, const uint32_t lenOut, uint8_t * pBufferIn, const uint32_t lenIn)
{
  FLEXIO_I2C_RESULT res;

  // Check the configuration structure
  if(pConfig == NULL)
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  if((!lenIn) || (pBufferIn == NULL))
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  pConfig->combo = 0xff;
  res = FLEXIO_I2C_Write_Internal(pConfig, address, pBufferOut, lenOut);

  if(res != FLEXIO_I2C_RES_OK)
    return res;

  return FLEXIO_I2C_Read(pConfig, address, pBufferIn, lenIn);
}

/******************************************************************************
* Driver Private functions                                                    *
*******************************************************************************/

/********************************************
* Internal Implementation of Write function *
*********************************************/
static FLEXIO_I2C_RESULT FLEXIO_I2C_Write_Internal(FLEXIO_I2C_CONFIG * pConfig, const uint8_t address, const uint8_t * pBuffer, const uint32_t len)
{
  uint32_t timerCompare, i;

  // Check the configuration structure
  if(pConfig == NULL)
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  // Check input parameters
  if((!len) || (pBuffer == NULL))
    return FLEXIO_I2C_RES_INVALIDPARAMETER;

  // Clear possible pending flags
  FLEXIO_ClrErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  FLEXIO_ClrTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerOutIx));
  FLEXIO_ClrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));

  // Set up timer
  timerCompare = (17 << 8) + pConfig->baudRateDiv; // 9 bits * 2 - 1,- shifted to second byte
  FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, timerCompare);

  // Write the chip address byte
  FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, FLEXIO_I2C_WRITE(address));

  while(!FLEXIO_GetShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx))){};

  // Check the Slave ACK
  if(FLEXIO_GetErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx)))
  {
    FLEXIO_I2C_Stop(pConfig);
    return FLEXIO_I2C_RES_NACK;
  }

  (void)FLEXIO_ReadShifterBuffer(pConfig->shifterInIx, DEFAULT);

  for(i = 0; i < len; i++)
  {
    timerCompare = (17 << 8) + pConfig->baudRateDiv; // 9 bits * 2 - 1,- shifted to second byte
    FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, timerCompare);

    // Write Data on BUS
    FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, pBuffer[i]);

    // Wait for send  & receive of data
    while(!FLEXIO_GetShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx))){};

    //Check the ACK from Slave
    if(FLEXIO_GetErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx)))
    {
      FLEXIO_I2C_Stop(pConfig);
      return FLEXIO_I2C_RES_NACK;
    }

    (void)FLEXIO_ReadShifterBuffer(pConfig->shifterInIx, DEFAULT);
  }

  timerCompare = (1 << 8) + pConfig->baudRateDiv; // 1 bit (STOP),- shifted to second byte
  FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, timerCompare);
  // Generate Repeat Start or Stop condition on BUS
  FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, pConfig->combo);
  //Wait for finish of whole transmition
  while(!FLEXIO_GetTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerOutIx))){};

  // return the status

  return FLEXIO_I2C_RES_OK;
}

#endif

/********************************************
* Internal Implementation of Stop function  *
*********************************************/
static void  FLEXIO_I2C_Stop(FLEXIO_I2C_CONFIG * pConfig)
{
  uint32_t timerCompare;

  // Check the configuration structure
  if(pConfig == NULL)
    return;

  FLEXIO_ClrTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerOutIx));

  timerCompare = 256 + pConfig->baudRateDiv; // 1,- shifted to second byte

  FLEXIO_SetTimerCompareVal(pConfig->timerOutIx, timerCompare); // Set up timer

  FLEXIO_ShifterStartBit(pConfig->shifterOutIx, FLEXIO_STARTBIT_DISABLED_ON_FIRST);

  FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, BIT_SWAPED, 0x00); // Write the chip address byte

  //Wait for finish of whole transmition
  while(!FLEXIO_GetTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerOutIx))){};

  FLEXIO_ShifterStartBit(pConfig->shifterOutIx, FLEXIO_STARTBIT_LOG0);
}


#endif

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
