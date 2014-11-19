/*****************************************************************************
 * (c) Copyright 2010-2014, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flexio_uart.c
 * @version   1.0.3.0
 * @date      May-22-2013
 * @brief     FlexioUART module driver source file.
 *
 * Revision History:
 *  1.	20/03/2014   B20253   Initially written for Kinetis KL43
 *  2.	03/04/2014   B20253   UART polling driver finished
 *  3.	09/04/2014   B20253   UART interrupt driver finished
******************************************************************************/
#include "common.h"
#include "drivers.h"
#include "flexio_uart.h"

#if (defined (MCU_MKL43Z256))

/******************************************************************************
* private functions definitions                                              *
******************************************************************************/
static uint8 GetStringLength(uint8 * pString);

/******************************************************************************
* data type definitions                                                      *
******************************************************************************/

/******************************************************************************
* interrupt callback functions prototype                                     *
******************************************************************************/
#if FLEXIO_UART_INTERRUPT_MODE != 0
void flexio_uart_tx_isr_callback(FLEXIO_CALLBACK_TYPE type, void* user_data);
void flexio_uart_rx_isr_callback(FLEXIO_CALLBACK_TYPE type, void* user_data);
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
* @brief   FLEXIO_UART module initialization function.
* @param   pConfig - pointer to configuration structure
* @param   shifterInIx - Index of shifter for receive and ACK
* @param   timerInIx - Index of timer for clocking of shifter registers
* @param   pinRxIx - Index of flexio Pin for Rx signal
* @param   baudRate - Requested baudrate
* @param   FlexIoClk - Clock frequency of flexio peripheral
* @return  Result of Init Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_UART_RESULT FLEXIO_UART_RxInit( 
                                      FLEXIO_UART_CONFIG * pConfig,
                                      uint32_t shifterInIx,
                                      uint32_t timerInIx,
                                      uint32_t pinRxIx,
                                      uint32_t baudRate,
                                      uint32_t flexioClk      
                                      )              
{
  if((((flexioClk / baudRate) / 2) - 1) > 255)
    return FLEXIO_UART_RES_BAUDRATE;  

  if((baudRate > FLEXIO_LIMIT_BAUDRATE) && (flexioClk <= FLEXIO_OSCERCLK))
    return FLEXIO_UART_RES_CLOCK;
  
  // Store the configuration information
  pConfig->shifterInIx = shifterInIx;
  pConfig->timerInIx = timerInIx;
  pConfig->pinRxIx = pinRxIx;
  pConfig->baudRateDivRx = (((flexioClk / baudRate) / 2) - 1);  

    /************ SHIFTER IN CONFIGURATION **************************************/

  // Initialize the FlexIO shifter register to receive UART rx data
  FLEXIO_ShifterIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  FLEXIO_ShifterErrIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  FLEXIO_ShifterDmaDisable(FLEXIO_MAKE_MASK(pConfig->shifterInIx));
  // SetUp Shifter In CTL
  FLEXIO_ShifterTimerSel(pConfig->shifterInIx, pConfig->timerInIx);
  FLEXIO_ShifterTimerPol(pConfig->shifterInIx, FLEXIO_TIMER_NEGATIVE_EDGE);
  FLEXIO_ShifterPinCfg(pConfig->shifterInIx, FLEXIO_PIN_DISABLED);
  FLEXIO_ShifterPinSel(pConfig->shifterInIx, pConfig->pinRxIx);
  FLEXIO_ShifterPinPol(pConfig->shifterInIx, FLEXIO_POLARITY_HIGH);
  FLEXIO_ShifterMode(pConfig->shifterInIx, FLEXIO_SHIFTER_RX_MODE);
  
  // SetUp Shifter In CFG
  FLEXIO_ShifterInSrc(pConfig->shifterInIx, FLEXIO_INSRC_PIN);
  FLEXIO_ShifterStopBit(pConfig->shifterInIx, FLEXIO_STOPBIT_LOG1);
  FLEXIO_ShifterStartBit(pConfig->shifterInIx, FLEXIO_STARTBIT_LOG0);

  /************* TIMER IN CONFIGURATION ***************************************/

  // Configure 8-bit transfer. Set TIMCMP[15:0] = (number of bits x 2) - 1.
  // SetUp the counter of Input timer of clocks
  FLEXIO_SetTimerCompareVal(pConfig->timerInIx, FLEXIO_UART_CALCULATE_TIMCMP(pConfig->baudRateDivRx));

  FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerInIx));
  // SetUp Timer In CFG
  FLEXIO_TimerClock(pConfig->timerInIx, FLEXIO_LOG1_ON_EN);
  FLEXIO_TimerInc(pConfig->timerInIx, FLEXIO_INC_ALWAYS);
  FLEXIO_TimerResets(pConfig->timerInIx, FLEXIO_RST_NEVER);
  FLEXIO_TimerDisablesOn(pConfig->timerInIx, FLEXIO_DIS_ON_COMPARE);
  FLEXIO_TimerEnablesOn(pConfig->timerInIx, FLEXIO_EN_PIN_REDGE);
  FLEXIO_TimerStopBit(pConfig->timerInIx, FLEXIO_STOP_ON_TIMER_DISABLED);
  FLEXIO_TimerStartBit(pConfig->timerInIx, START_ENABLED);
  // SetUp Timer In CTL
  FLEXIO_TimerTrgSel(pConfig->timerInIx, FLEXIO_TIMTRG_PIN(pConfig->pinRxIx));
  FLEXIO_TimerTrgPol(pConfig->timerInIx, FLEXIO_POLARITY_HIGH);
  FLEXIO_TimerTrgSrc(pConfig->timerInIx, EXT_TRG);
  FLEXIO_TimerPinCfg(pConfig->timerInIx, FLEXIO_PIN_DISABLED);
  FLEXIO_TimerPinSel(pConfig->timerInIx, pinRxIx);
  FLEXIO_TimerPinPol(pConfig->timerInIx, FLEXIO_POLARITY_LOW);
  FLEXIO_TimerMode(pConfig->timerInIx, FLEXIO_TIMER_8BIT_BAUD_MODE);

  #if FLEXIO_UART_INTERRUPT_MODE != 0
  {
    pConfig->pCallBack = NULL;
    // Register the own CallBack function in FlexIO driver
    tFLEXIO_CALLBACK_DESC callBackDesc;

    callBackDesc.SHIFTERR_MASK = 0;
    callBackDesc.SHIFTFLG_MASK = FLEXIO_MAKE_MASK(pConfig->shifterInIx);
    callBackDesc.TIMERFLG_MASK = 0;
    callBackDesc.user_data = (void*)pConfig;
    
    FLEXIO_ShifterIrqEnable(FLEXIO_MAKE_MASK(pConfig->shifterInIx)); 
    
    callBackDesc.pCallBack = flexio_uart_rx_isr_callback;
    if(FLEXIO_RegisterCallback(&callBackDesc, 0) < 0)
      return FLEXIO_UART_RES_FAILED;
  }
  #endif
  
  return FLEXIO_UART_RES_OK;  
}  

/***************************************************************************//*!
* @brief   GetStringLength return lenght of input string.
* @param   *pString - pointer to input string
* @return  Length of the input string in bytes
* @note    Implemented as function call.
******************************************************************************/
static uint8 GetStringLength(uint8 * pString)
{
  int len = 0;
  while(*(pString + len)) len++;
  return len;
}

/***************************************************************************//*!
* @brief   FLEXIO_UART module initialization function.
* @param   pConfig - pointer to configuration structure
* @param   shifterOutIx - Index of shifter for transmit
* @param   timerOutIx - Index of timer for transmit
* @param   pinTxIx - Index of FlexIO Pin for Tx signal
* @param   baudRate - Requested baudrate
* @param   FlexIoClk - Clock frequency of flexio peripheral
* @return  Result of Init Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_UART_RESULT FLEXIO_UART_TxInit( 
                                      FLEXIO_UART_CONFIG * pConfig,
                                      uint32_t shifterOutIx,
                                      uint32_t timerOutIx,
                                      uint32_t pinTxIx,
                                      uint32_t baudRate,
                                      uint32_t flexioClk      
                                      )              
{
  if((((flexioClk / baudRate) / 2) - 1) > 255)
    return FLEXIO_UART_RES_BAUDRATE;

  if((baudRate > FLEXIO_LIMIT_BAUDRATE) && (flexioClk <= FLEXIO_OSCERCLK))
    return FLEXIO_UART_RES_CLOCK;

  if((baudRate > FLEXIO_LIMIT_BAUDRATE) && (flexioClk == FLEXIO_MCGPCLK))
    return FLEXIO_UART_RES_CLOCK;
  
  // Store the configuration information
  pConfig->shifterOutIx = shifterOutIx;
  pConfig->timerOutIx = timerOutIx;
  pConfig->pinTxIx = pinTxIx;
  pConfig->baudRateDivTx = (((flexioClk / baudRate) / 2) - 1);
#if FLEXIO_UART_INTERRUPT_MODE == 1  
  pConfig->indexBuffRise = 0;
  pConfig->indexBuffFall = 0;
  pConfig->dataIx = 0;
#endif  
  /************ SHIFTER OUT CONFIGURATION *************************************/

  // Initialize the FlexIO shifter register to transmit UART data
  FLEXIO_ShifterIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  FLEXIO_ShifterErrIrqDisable(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  FLEXIO_ShifterDmaDisable(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  
  // SetUp Shifter Out CFG
  FLEXIO_ShifterInSrc(pConfig->shifterOutIx, FLEXIO_INSRC_PIN);
  FLEXIO_ShifterStopBit(pConfig->shifterOutIx, FLEXIO_STOPBIT_LOG1);
  FLEXIO_ShifterStartBit(pConfig->shifterOutIx, FLEXIO_STARTBIT_LOG0);
  
  // SetUp Shifter Out CTL
  FLEXIO_ShifterTimerSel(pConfig->shifterOutIx, pConfig->timerOutIx);
  FLEXIO_ShifterTimerPol(pConfig->shifterOutIx, FLEXIO_TIMER_POSITIVE_EDGE);
  FLEXIO_ShifterPinCfg(pConfig->shifterOutIx, FLEXIO_PIN_OUTPUT);
  FLEXIO_ShifterPinSel(pConfig->shifterOutIx, pConfig->pinTxIx);
  FLEXIO_ShifterPinPol(pConfig->shifterOutIx, FLEXIO_POLARITY_HIGH);
  FLEXIO_ShifterMode(pConfig->shifterOutIx, FLEXIO_SHIFTER_TX_MODE);

  /************* TIMER OUT CONFIGURATION **************************************/

  // Initialize the FlexIO timers for generate SCL clock
  // Configure 2 word transfer with baud rate of divide by 4 of the FlexIO clock. Set
  // TIMCMP[15:8] = (number of words x 18) + 1. Set TIMCMP[7:0] = (baud rate divider / 2) - 1.
  FLEXIO_SetTimerCompareVal(pConfig->timerInIx, FLEXIO_UART_CALCULATE_TIMCMP(pConfig->baudRateDivTx));
  
  FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerOutIx));
  // SetUp Timer Out CFG
  FLEXIO_TimerClock(pConfig->timerOutIx, FLEXIO_LOG1_ON_EN);
  FLEXIO_TimerInc(pConfig->timerOutIx, FLEXIO_INC_ALWAYS);
  FLEXIO_TimerResets(pConfig->timerOutIx, FLEXIO_RST_NEVER);
  FLEXIO_TimerDisablesOn(pConfig->timerOutIx, FLEXIO_DIS_ON_COMPARE);
  FLEXIO_TimerEnablesOn(pConfig->timerOutIx, FLEXIO_EN_TRIGGER_HIGH);
  FLEXIO_TimerStopBit(pConfig->timerOutIx, FLEXIO_STOP_ON_TIMER_DISABLED);
  FLEXIO_TimerStartBit(pConfig->timerOutIx, START_ENABLED);
// SetUp Timer Out CTL
  FLEXIO_TimerTrgSel(pConfig->timerOutIx, FLEXIO_TIMCTL_TRGSEL_SHIFTER(pConfig->shifterOutIx));
  FLEXIO_TimerTrgPol(pConfig->timerOutIx, FLEXIO_POLARITY_LOW);
  FLEXIO_TimerTrgSrc(pConfig->timerOutIx, INT_TRG);
  FLEXIO_TimerPinCfg(pConfig->timerOutIx, FLEXIO_PIN_DISABLED);
  FLEXIO_TimerPinSel(pConfig->timerOutIx, pinTxIx);
  FLEXIO_TimerPinPol(pConfig->timerOutIx, FLEXIO_POLARITY_HIGH);
  FLEXIO_TimerMode(pConfig->timerOutIx, FLEXIO_TIMER_8BIT_BAUD_MODE);

  #if FLEXIO_UART_INTERRUPT_MODE != 0
  {
    pConfig->pCallBack = NULL;
    // Register the own CallBack function in FlexIO driver
    tFLEXIO_CALLBACK_DESC callBackDesc;

    callBackDesc.SHIFTERR_MASK = 0;
    callBackDesc.SHIFTFLG_MASK = 0;
    callBackDesc.TIMERFLG_MASK = FLEXIO_MAKE_MASK(pConfig->timerOutIx);
    callBackDesc.user_data = (void*)pConfig;

    callBackDesc.pCallBack = flexio_uart_tx_isr_callback;
    pConfig->state = FLEXIO_UART_ST_IDLE;
    if(FLEXIO_RegisterCallback(&callBackDesc, 0) < 0)
      return FLEXIO_UART_RES_FAILED;
  }
  #endif
  
  return FLEXIO_UART_RES_OK;  
}



/******************************************************************************
* FLEXIO_UART interrupt mode                                                  *
*******************************************************************************/
#if FLEXIO_UART_INTERRUPT_MODE != 0

/***************************************************************************//*!
* @brief   FLEXIO_UART module register callBack function.
* @param   pConfig - pointer to configuration structure
* @param   pCallback - pointer to function CallBack function (NULL for unregister)
* @return  Result of register callBack function operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_UART_RESULT FLEXIO_UART_SetCallBack(FLEXIO_UART_CONFIG * pConfig, FLEXIO_UART_CALLBACK pCallback)
{
  pConfig->pCallBack = pCallback;
  return FLEXIO_UART_RES_OK;
}

/***************************************************************************//*!
* @brief   FLEXIO_UART module Write string.
* @param   pConfig - pointer to configuration structure
* @param   str - pointer to string
* @return  Result of Write Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_UART_RESULT FLEXIO_UART_PutStr(FLEXIO_UART_CONFIG * pConfig, const int8_t * str)
{
  return FLEXIO_UART_SendBuffer(pConfig, str, GetStringLength((uint8*)str));
}
   
/***************************************************************************//*!
* @brief   FLEXIO_UART module Write data function.
* @param   pConfig - pointer to configuration structure
* @param   pBuff - pointer to input buffer
* @return  Result of write Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_UART_RESULT FLEXIO_UART_SendBuffer(FLEXIO_UART_CONFIG * pConfig, const int8_t * pBuff, uint32 len)
{
  register uint32_t i = 0;

  // Check input parameters
  if(pBuff == NULL)
    return FLEXIO_UART_RES_INVALIDPARAMETER;

  if(pConfig->state == FLEXIO_UART_ST_IDLE)
  { 
    pConfig->state = FLEXIO_UART_ST_TX; 
    // Clear possible pending flags
    FLEXIO_ClrErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
    FLEXIO_ClrTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerOutIx));

    pConfig->indexBuffRise = (pConfig->indexBuffRise & (FLEXIO_UART_BUFF_IX-1));
    pConfig->pBufferOut[pConfig->indexBuffRise] = (uint8*)pBuff;  
    pConfig->lenOut[pConfig->indexBuffRise] = len;    
    pConfig->dataIx++;
      
    FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, DEFAULT, *pConfig->pBufferOut[((FLEXIO_UART_BUFF_IX-1) & pConfig->indexBuffRise)]++); 
    FLEXIO_TimerIrqEnable(FLEXIO_MAKE_MASK(pConfig->timerOutIx)); 
    // return the status
    return FLEXIO_UART_RES_OK;    
  }
  else{
    pConfig->indexBuffRise++;
    pConfig->indexBuffRise &= (FLEXIO_UART_BUFF_IX-1);
    pConfig->pBufferOut[pConfig->indexBuffRise] = (uint8*)pBuff;  
    pConfig->lenOut[pConfig->indexBuffRise] = len;  
    
    return FLEXIO_UART_RES_TX_PENDING;
  }
}

/***************************************************************************//*!
* @brief   FLEXIO_UART module putchar function.
* @param   pConfig - pointer to configuration structure
* @param   ch - pointer input character
* @return  Result of write Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_UART_RESULT FLEXIO_UART_PutChar(FLEXIO_UART_CONFIG * pConfig, uint8  ch)
{
  pConfig->state = FLEXIO_UART_ST_SINGLE_TX; 
  // Clear possible pending flags
  FLEXIO_ClrErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  FLEXIO_ClrTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerOutIx));
    
  FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, DEFAULT, ch); 
  FLEXIO_TimerIrqEnable(FLEXIO_MAKE_MASK(pConfig->timerOutIx)); 

  return FLEXIO_UART_RES_OK;  
}

/***************************************************************************//*!
* @brief   FLEXIO_UART module Read data function.
* @param   pConfig - pointer to configuration structure
* @return  Read byte of data in interrupt mode
* @note    Implemented as function call.
******************************************************************************/
uint8_t FLEXIO_UART_GetChar(FLEXIO_UART_CONFIG * pConfig)
{
  return pConfig->dataRx;
}                                      
                                      
/******************************************************************************
* Tx interrupt functions definitions                                          *
*******************************************************************************/
void flexio_uart_tx_isr_callback(FLEXIO_CALLBACK_TYPE type, void* user_data)
{
  FLEXIO_UART_CONFIG * pConfig = (FLEXIO_UART_CONFIG*)user_data;
  
  // *************** Transmit mode ******************************
  if((uint32_t)type & (FLEXIO_MAKE_MASK(pConfig->timerOutIx) << 8) )
  {
    switch(pConfig->state)
    { // if sent complete buffer (string) which is in flash memory
      case FLEXIO_UART_ST_TX:
        // data to be send
        if(pConfig->dataIx < (pConfig->lenOut[pConfig->indexBuffFall & (FLEXIO_UART_BUFF_IX-1)] ))
        {
          FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, DEFAULT, *pConfig->pBufferOut[pConfig->indexBuffFall & (FLEXIO_UART_BUFF_IX-1)]++);
          pConfig->dataIx++;
        }
        else
        { // after the last byte is sent than disable interrupt from shifter
          pConfig->dataIx = 1; 

          if((pConfig->indexBuffFall & (FLEXIO_UART_BUFF_IX-1)) >= (pConfig->indexBuffRise & (FLEXIO_UART_BUFF_IX-1)))
          { // disable timer interrupt if all data was sent
            FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerOutIx));
            pConfig->state = FLEXIO_UART_ST_IDLE;
          }
          else 
          { 
            pConfig->lenOut[(pConfig->indexBuffFall++) & (FLEXIO_UART_BUFF_IX-1)] = 0;        
            FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, DEFAULT, *pConfig->pBufferOut[pConfig->indexBuffFall]++);
          }
          if(pConfig->pCallBack) // tx done callback to main application 
            pConfig->pCallBack(FLEXIO_UART_RES_TXDONE);
        }
        break;
      // if sent only one char (runtime)   
      case FLEXIO_UART_ST_SINGLE_TX:
        FLEXIO_TimerIrqDisable(FLEXIO_MAKE_MASK(pConfig->timerOutIx));
        pConfig->state = FLEXIO_UART_ST_IDLE;     
       break;
    }
  }
}

/******************************************************************************
* Rx interrupt functions definitions                                          *
*******************************************************************************/
void flexio_uart_rx_isr_callback(FLEXIO_CALLBACK_TYPE type, void* user_data)
{
  FLEXIO_UART_CONFIG * pConfig = (FLEXIO_UART_CONFIG*)user_data;
  
  // *************** Receive mode ******************************
  if((uint32_t)type & (FLEXIO_MAKE_MASK(pConfig->shifterInIx)))
  { // read receive regiter 
    pConfig->dataRx = FLEXIO_ReadBuffer_BYTE_SWAPED(pConfig->shifterInIx);
    // clear shifter flag 
    FLEXIO_ClrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx));    
    // callback to main app if the receive transaction was finished
    if(pConfig->pCallBack)
      pConfig->pCallBack(FLEXIO_UART_RES_RXREADY);
  }

}
#else

/***************************************************************************//*!
* @brief   FLEXIO_UART module Write data function.
* @param   pConfig - pointer to configuration structure
* @param   pBuffer - pointer to input data buffer
* @param   len - length of data to be send
* @return  Result of Write Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_UART_RESULT FLEXIO_UART_SendBuffer(FLEXIO_UART_CONFIG * pConfig, const int8_t * pBuff, uint32 len)
{
  uint32_t i;

  // Check input parameters
  if((!len) || (pBuff == NULL))
    return FLEXIO_UART_RES_INVALIDPARAMETER;

  pConfig->pBufferOut = (uint8*)pBuff;
    
  // Clear possible pending flags
  FLEXIO_ClrErrShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterOutIx));
  FLEXIO_ClrTimerFlag(FLEXIO_MAKE_MASK(pConfig->timerOutIx));
  // wait for the flag
  while(!FLEXIO_GetShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterOutIx))){};
 
  // transmit the data
  for(i=0; i<len; i++)
  {
    FLEXIO_WriteShifterBuffer(pConfig->shifterOutIx, DEFAULT, (uint32)pConfig->pBufferOut[i]);
    while(!FLEXIO_GetShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterOutIx))){};
  }
  // return the status
  return FLEXIO_UART_RES_OK;
}

/***************************************************************************//*!
* @brief   FLEXIO_UART module Write data function.
* @param   pConfig - pointer to configuration structure
* @param   str - pointer to string
* @return  Result of Write Operation
* @note    Implemented as function call.
******************************************************************************/
FLEXIO_UART_RESULT FLEXIO_UART_PutStr(FLEXIO_UART_CONFIG * pConfig, const int8_t * str)
{
  return FLEXIO_UART_SendBuffer(pConfig, str, GetStringLength((uint8*)str));
}

/***************************************************************************//*!
* @brief   FLEXIO_UART module Read data function.
* @param   pConfig - pointer to configuration structure
* @return  Read byte of data
* @note    Implemented as function call.
******************************************************************************/
uint8_t FLEXIO_UART_GetChar(FLEXIO_UART_CONFIG * pConfig)
{
  while(!FLEXIO_GetShifterFlag(FLEXIO_MAKE_MASK(pConfig->shifterInIx))){};
  
  return FLEXIO_ReadShifterBuffer(pConfig->shifterInIx,BYTE_SWAPED);
}

#endif

#endif

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/

