/*****************************************************************************
 * (c) Copyright 2010-2014, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flexio_i2c.h
 * @version   1.0.9.0
 * @date      May-22-2013
 * @brief     FlexIOIIC module driver header file.
 *
 * Revision History:
 *  1.	xx/xx/xxxx   Bxxxxx   Initially written for Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup flexio_i2c_example0
 * @{
 * @par       Source code:
 * @include   flexio_i2c_test\flexio_i2c_test.c
 * @par       Appconfig.h:
 * @include   flexio_i2c_test\appconfig.h
 ******************************************************************************/
/*! @} End of flexio_i2c_example0                                                    */
#ifndef __FLEXIO_I2C_H
#define __FLEXIO_I2C_H


#ifndef FLEXIO_I2C_INTERRUPT_MODE
  #define FLEXIO_I2C_INTERRUPT_MODE 0
#endif

/******************************************************************************
* FLEXIO_I2C types
*
*//*! @addtogroup flexio_i2c_types
* @{
*******************************************************************************/

/***************************************************************************//*!
 * @brief   FLEXIO_I2C result variables
 * @note    Used as a driver state value for interrupt driver version
 ******************************************************************************/
typedef enum {
    FLEXIO_I2C_ST_IDLE = 0,
    FLEXIO_I2C_ST_TX = 1,
    FLEXIO_I2C_ST_RX = 2
} FLEXIO_I2C_STATE;

/***************************************************************************//*!
 * @brief   FLEXIO_I2C state
 * @note    Used as a return result values of individual driver function
 ******************************************************************************/
typedef enum {
    FLEXIO_I2C_RES_OK = 0,
    FLEXIO_I2C_RES_INVALIDPARAMETER = -1,
    FLEXIO_I2C_RES_FAILED = -2,
    FLEXIO_I2C_RES_BUSY = -3,
    FLEXIO_I2C_RES_NACK = -4,
    FLEXIO_I2C_RES_BAUDRATE = -5
} FLEXIO_I2C_RESULT;

typedef void (*FLEXIO_I2C_CALLBACK)(FLEXIO_I2C_RESULT result);

/***************************************************************************//*!
 * @brief   FLEXIO_IIC configuration structure
 * @note    Used as a holder of configuration setting for the driver
 ******************************************************************************/
typedef struct {
  uint32_t shifterOutIx;    ///< Index of shifter out (SDA transmit)
  uint32_t shifterInIx;     ///< Index of shifter in (SDA receive & ACK)
  uint32_t timerOutIx;      ///< Index of timer out (SCL generation)
  uint32_t timerInIx;       ///< Index of timer in (SCL check)
  uint32_t baudRateDiv;     ///< Requested Baudrate Divider
  uint32_t combo;           ///< Flag that the transfer is Write/Read sequence

#if FLEXIO_I2C_INTERRUPT_MODE == 1
  uint8_t   address;
  const uint8_t * pBufferOut;
  uint32_t lenOut;
  uint8_t * pBufferIn;
  uint32_t lenIn;
  uint32_t dataIx;
  FLEXIO_I2C_STATE state;
  FLEXIO_I2C_CALLBACK pCallBack; ///< Pointer to Callback function for following operation
#endif
}FLEXIO_I2C_CONFIG;

/*! @} End of flexio_i2c_types                                                */

/******************************************************************************
* FLEXIO function and macro definitions
*
*//*! @addtogroup flexio_i2c_macro
* @{
*******************************************************************************/
#define FLEXIO_I2C_WRITE(DevAdr)            (uint8)((DevAdr<<1)&0xFE)	///< write i2c device
#define FLEXIO_I2C_READ(DevAdr)             (uint8)((DevAdr<<1)|0x01)	///< read i2c device
/*! @} End of flexio_i2c_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
/******************************************************************************
* FLEXIO function and macro definitions
*
*//*! @addtogroup flexio_i2c_functions
* @{
*******************************************************************************/
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
extern FLEXIO_I2C_RESULT FLEXIO_I2C_Init(
                                  FLEXIO_I2C_CONFIG * pConfig,
                                  uint32_t shifterOutIx,
                                  uint32_t shifterInIx,
                                  uint32_t timerOutIx,
                                  uint32_t timerInIx,
                                  uint32_t pinSclIx,
                                  uint32_t pinSdaIx,
                                  uint32_t baudRate,
                                  uint32_t FlexIoClk
                                  );


/***************************************************************************//*!
* @brief   FLEXIO_I2C module Write data function.
* @param   address - slave chip address
* @param   pBuffer - pointer to data buffer
* @param   len - length of data (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @return  Result of Write Operation
* @note    Implemented as function call.
******************************************************************************/								  
extern FLEXIO_I2C_RESULT FLEXIO_I2C_Write(FLEXIO_I2C_CONFIG * pConfig, const uint8_t address, const uint8_t * pBuffer, const uint32_t len);

/***************************************************************************//*!
* @brief   FLEXIO_I2C module Read data function.
* @param   address - slave chip address
* @param   pBuffer - pointer to data buffer
* @param   len - length of data (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @return  Result of Read Operation
* @note    Implemented as function call.
******************************************************************************/
extern FLEXIO_I2C_RESULT FLEXIO_I2C_Read(FLEXIO_I2C_CONFIG * pConfig, const uint8_t address, uint8_t * pBuffer, const uint32_t len);

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
extern FLEXIO_I2C_RESULT FLEXIO_I2C_Combo(FLEXIO_I2C_CONFIG * pConfig, const uint8_t address, const uint8_t * pBufferOut, const uint32_t lenOut, uint8_t * pBufferIn, const uint32_t lenIn);
#if FLEXIO_I2C_INTERRUPT_MODE != 0

/***************************************************************************//*!
* @brief   FLEXIO_I2C module Register CallBack function.
* @param   pCallback - pointer to function CallBack function (NULL for unregister)
* @return  Result of register CallBack function Operation
* @note    Implemented as function call.
******************************************************************************/
  extern FLEXIO_I2C_RESULT FLEXIO_I2C_SetCallBack(FLEXIO_I2C_CONFIG * pConfig, FLEXIO_I2C_CALLBACK pCallback);
#endif

/*! @} End of flexio_i2c_functions                                          */
#endif /* __FLEXIO_I2C_H */
