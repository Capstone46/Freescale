/*****************************************************************************
 * (c) Copyright 2010-2014, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flexio_uart.h
 * @version   1.0.3.0
 * @date      May-22-2013
 * @brief     FlexioUART module driver source file.
 *
 * Revision History:
 *  1.	20/03/2014   B20253   Initially written for Kinetis KL43
 *  2.	03/04/2014   B20253   UART polling driver finished
 *  3.	09/04/2014   B20253   UART interrupt driver finished
******************************************************************************/
/******************************************************************************
 *//*! @addtogroup flexio_uart_example0
 * @{
 * @par       Source code:
 * @include   flexio_uart_test\flexio_uart_test.c
 * @par       Appconfig.h:
 * @include   flexio_uart_test\appconfig.h
 ******************************************************************************/
/*! @} End of flexio_uart_example0                                            */

#ifndef __FLEXIO_UART_H 
#define __FLEXIO_UART_H 

#include "appconfig.h" 
   
/******************************************************************************
* FLEXIO_UART types
*
*//*! @addtogroup flexio_uart_types
* @{
*******************************************************************************/
#ifndef FLEXIO_UART_INTERRUPT_MODE
  #define FLEXIO_UART_INTERRUPT_MODE 0		///< FLEXIO UART  mode selection
#endif
   
#define FLEXIO_LIMIT_BAUDRATE      57600	///< FLEXIO UART  baud rate
#define FLEXIO_OSCERCLK            2000000	///< FLEXIO external clock
#define FLEXIO_MCGPCLK             48000000 ///< FLEXIO MCGPCLK clock

#define FLEXIO_TIMCTL_TRGSEL_SHIFTER(ix)        (((ix) * 4) + 1)
#define FLEXIO_UART_CALCULATE_TIMCMP(x)         (x | (((8 * 2) -1) << 8)) 

/***************************************************************************//*!
 * @brief   FLEXIO_UART result variables
 * @note    Used as a return result values of individual driver function
 ******************************************************************************/
typedef enum {
    FLEXIO_UART_RES_OK = 0,
    FLEXIO_UART_RES_INVALIDPARAMETER = -1,
    FLEXIO_UART_RES_FAILED = -2,
    FLEXIO_UART_RES_BAUDRATE = -3,
    FLEXIO_UART_RES_TXDONE = -4,
    FLEXIO_UART_RES_RXREADY = -5,
    FLEXIO_UART_RES_CLOCK = -6,
    FLEXIO_UART_RES_BUFF_OVF = -7,
    FLEXIO_UART_RES_TX_PENDING = -8
} FLEXIO_UART_RESULT;

/***************************************************************************//*!
 * @brief   FLEXIO_UART result variables
 * @note    Used as a driver state value for interrupt driver version
 ******************************************************************************/
typedef enum {
    FLEXIO_UART_ST_IDLE = 0,
    FLEXIO_UART_ST_SINGLE_TX = 1,    
    FLEXIO_UART_ST_TX = 2
} FLEXIO_UART_STATE;

typedef void (*FLEXIO_UART_CALLBACK)(FLEXIO_UART_RESULT result);
#define FLEXIO_UART_BUFF_IX  32
/***************************************************************************//*!
 * @brief   FLEXIO_UART configuration structure
 * @note    Used as a holder of configuration setting for the driver
 ******************************************************************************/
typedef struct {
  uint32 shifterInIx;     ///< Index of shifter in (RX receive )
  uint32 shifterOutIx;    ///< Index of shifter out (TX transmit)  
  uint32 timerInIx;       ///< Index of timer in (RX)
  uint32 timerOutIx;      ///< Index of timer out (TX)  
  uint32 pinRxIx;         ///< Uart rx pin 
  uint32 pinTxIx;         ///< Uart tx pin   
  uint32 baudRateDivTx;     ///< Requested Baudrate Divider
  uint32 baudRateDivRx;     ///< Requested Baudrate Divider
#if FLEXIO_UART_INTERRUPT_MODE == 0
  const uint8* pBufferOut;
#elif FLEXIO_UART_INTERRUPT_MODE == 1
  const uint8* pBufferOut[FLEXIO_UART_BUFF_IX];
  uint32 indexBuffRise;
  uint32 indexBuffFall;
  uint32 dataRx;
  uint32 lenOut[FLEXIO_UART_BUFF_IX];
  uint32 dataIx;
  FLEXIO_UART_STATE state;
  FLEXIO_UART_CALLBACK pCallBack; ///< Pointer to Callback function for following operation
#endif
}FLEXIO_UART_CONFIG;

/*! @} End of flexio_uart_types                                                */

/******************************************************************************
* FLEXIO UART functions
*
*//*! @addtogroup flexio_uart_functions
* @{
*******************************************************************************/
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
extern FLEXIO_UART_RESULT FLEXIO_UART_TxInit( 
                                              FLEXIO_UART_CONFIG * pConfig,
                                              uint32_t shifterOutIx,
                                              uint32_t timerOutIx,
                                              uint32_t pinTxIx,
                                              uint32_t baudRateTx,
                                              uint32_t flexioClk      
                                            );
											
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
extern FLEXIO_UART_RESULT FLEXIO_UART_RxInit( 
                                              FLEXIO_UART_CONFIG * pConfig,
                                              uint32_t shifterInIx,
                                              uint32_t timerInIx,
                                              uint32_t pinRxIx,
                                              uint32_t baudRateRx,
                                              uint32_t flexioClk      
                                            ); 
											
/***************************************************************************//*!
* @brief   FLEXIO_UART module Write string.
* @param   pConfig - pointer to configuration structure
* @param   str - pointer to string
* @return  Result of Write Operation
* @note    Implemented as function call.
******************************************************************************/
extern FLEXIO_UART_RESULT FLEXIO_UART_PutStr(FLEXIO_UART_CONFIG * pConfig, const int8_t * str);
  
/***************************************************************************//*!
* @brief   FLEXIO_UART module Write data function.
* @param   pConfig - pointer to configuration structure
* @param   pBuffer - pointer to input data buffer
* @param   len - length of data to be send
* @return  Result of Write Operation
* @note    Implemented as function call.
******************************************************************************/
extern FLEXIO_UART_RESULT FLEXIO_UART_SendBuffer(FLEXIO_UART_CONFIG * pConfig, const int8_t * pBuff, uint32 len);
  
/***************************************************************************//*!
* @brief   FLEXIO_UART module Read data function.
* @param   pConfig - pointer to configuration structure
* @return  Read byte of data in interrupt mode
* @note    Implemented as function call.
******************************************************************************/
  extern uint8_t FLEXIO_UART_GetChar(FLEXIO_UART_CONFIG * pConfig);  
#if FLEXIO_UART_INTERRUPT_MODE == 1

/***************************************************************************//*!
* @brief   FLEXIO_UART module putchar function.
* @param   pConfig - pointer to configuration structure
* @param   ch - pointer input character
* @return  Result of write Operation
* @note    Implemented as function call.
******************************************************************************/
  extern FLEXIO_UART_RESULT FLEXIO_UART_PutChar(FLEXIO_UART_CONFIG * pConfig, uint8 ch);
  
/***************************************************************************//*!
* @brief   FLEXIO_UART module register callBack function.
* @param   pConfig - pointer to configuration structure
* @param   pCallback - pointer to function CallBack function (NULL for unregister)
* @return  Result of register callBack function operation
* @note    Implemented as function call.
******************************************************************************/
  extern FLEXIO_UART_RESULT FLEXIO_UART_SetCallBack(FLEXIO_UART_CONFIG * pConfig, FLEXIO_UART_CALLBACK pCallback);
#endif

/*! @} End of flexio_uart_functions                                            */

#endif /* __FLEXIO_UART_H */

