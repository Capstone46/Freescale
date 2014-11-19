/*****************************************************************************
 * (c) Copyright 2010-2014, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flexio_i2s.h
 * @version   1.0.9.0
 * @date      May-22-2013
 * @brief     FlexIOIIC module driver header file.
 *
 * Revision History:
 *  1.	xx/xx/xxxx   Bxxxxx   Initially written for Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup flexio_i2s_example0
 * @{
 * @par       Source code:
 * @include   flexio_i2s_test\flexio_i2c_test.c
 * @par       Appconfig.h:
 * @include   flexio_i2s_test\appconfig.h
 ******************************************************************************/

/*! @} End of flexio_i2s_example0                                             */
#ifndef __FLEXIO_I2S_H
#define __FLEXIO_I2S_H


 /******************************************************************************
* FLEXIO function and macro definitions
*
*//*! @addtogroup flexio_i2s_macro
* @{
*******************************************************************************/
#define I2S_BUF_CNT 2 ///< number of i2s data buffers 2 =double buffered
/*! @} End of flexio_i2s_macro                                                */

   
/******************************************************************************
* FLEXIO_I2S types
*
*//*! @addtogroup flexio_i2s_types
* @{
*******************************************************************************/

/***************************************************************************//*!
 * @brief   FLEXIO_I2S result variables
 * @note    Used as a driver state value for interrupt driver version
 ******************************************************************************/
typedef enum {
    FLEXIO_I2S_ST_IDLE=  0,
    FLEXIO_I2S_ST_TX =   1,
    FLEXIO_I2S_ST_RX =   2,
    FLEXIO_I2S_ST_STOP = 3,
} FLEXIO_I2S_STATE;

/***************************************************************************//*!
 * @brief   FLEXIO_I2S state
 * @note    Used as a return result values of individual driver function
 ******************************************************************************/
typedef enum {
    FLEXIO_I2S_RES_OK = 0,
    FLEXIO_I2S_RES_INVALIDPARAMETER = -1,
    FLEXIO_I2S_RES_FAILED = -2,
    FLEXIO_I2S_RES_BUSY = -3,
    FLEXIO_I2S_RES_BAUDRATE = -5
} FLEXIO_I2S_RESULT;

typedef void (*FLEXIO_I2S_CALLBACK)(FLEXIO_I2S_RESULT result);
typedef void (*FLEXIO_I2S_NEEDDATA_CALLBACK)(int16_t * pData);

/***************************************************************************//*!
 * @brief   FLEXIO_I2S configuration structure
 * @note    Used as a holder of configuration setting for the driver
 ******************************************************************************/
typedef struct {
  
  int16_t *pData;
  uint32 len;
}FLEXIO_I2S_BUF;

typedef struct {
  uint32_t shifterOutIx; ///< Index of shifter out(I2S DOUT transmit)
  uint32_t shifterInIx;  ///< Index of shifter in (I2S DIN receive)
  uint32_t timerBclkIx;  ///< Index of timer out  (BCLK generation)
  uint32_t timerFsyncIx; ///< Index of timer out  (FS/WS generation)
  uint32_t timerMclkIx;  ///< Index of timer out  (MCLK generation)
  uint32_t baudRateDiv;  ///< Requested Baudrate Divider
  FLEXIO_I2S_BUF  outbuf[I2S_BUF_CNT]; 
  uint32_t buffIx;       ///< Index of buffer
  uint32_t dataIx;       ///< Index of data
  FLEXIO_I2S_STATE state;///< Current status of the SW driver
  FLEXIO_I2S_CALLBACK pCallBack; ///< Pointer to Callback function for following operation
  FLEXIO_I2S_NEEDDATA_CALLBACK pDataCallBack;
}FLEXIO_I2S_CONFIG;
  
/*! @} End of flexio_i2s_types                                                */


/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
/******************************************************************************
* FLEXIO I2S functions
*
*//*! @addtogroup flexio_i2s_functions
* @{
*******************************************************************************/
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
 extern FLEXIO_I2S_RESULT FLEXIO_I2S_Init(
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
                                  );
 
 extern FLEXIO_I2S_RESULT FLEXIO_I2S_PutData(FLEXIO_I2S_CONFIG * pConfig, int16_t* pData, uint32_t length);
 
 /***************************************************************************//*!
* @brief   FLEXIO_I2S module Register CallBack function.
* @param   pCallback - pointer to function CallBack function (NULL for unregister)
* @return  Result of register CallBack function Operation
* @note    Implemented as function call.
******************************************************************************/
 extern FLEXIO_I2S_RESULT FLEXIO_I2S_SetCallBack(FLEXIO_I2S_CONFIG * pConfig, FLEXIO_I2S_NEEDDATA_CALLBACK pCallback);
 
 /***************************************************************************//*!
* @brief   FLEXIO_I2S Enable playback funnction.
* @param   pConfig - pointer to flexio i2s config structure
* @return  Result of register CallBack function Operation
* @note    Implemented as function call.
******************************************************************************/
 extern FLEXIO_I2S_RESULT FLEXIO_I2S_Play(FLEXIO_I2S_CONFIG * pConfig);
 
 /***************************************************************************//*!
* @brief   FLEXIO_I2S Stop playback funnction.
* @param   pConfig - pointer to flexio i2s config structure
* @return  Result of register CallBack function Operation
* @note    Implemented as function call.
******************************************************************************/
 extern FLEXIO_I2S_RESULT FLEXIO_I2S_Stop(FLEXIO_I2S_CONFIG * pConfig);
 
 /*! @} End of flexio_i2s_functions                                                */

#endif /* __FLEXIO_I2S_H */
