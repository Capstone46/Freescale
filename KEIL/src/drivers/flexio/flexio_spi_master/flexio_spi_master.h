/*****************************************************************************
 * (c) Copyright 2010-2014, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flexio_spi_master.h
 * @version   1.0.9.0
 * @date      May-22-2013
 * @brief     FlexIOIIC module driver header file.
 *
 * Revision History:
 *  1.	xx/xx/xxxx   Bxxxxx   Initially written for Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup flexio_spi_master_example0
 * @{
 * @par       Source code:
 * @include   flexio_spi_master_test\flexio_spi_master_test.c
 * @par       Appconfig.h:
 * @include   flexio_spi_master_test\appconfig.h
 ******************************************************************************/
/*! @} End of flexio_spi_master_example0                                                    */
#ifndef __FLEXIO_SPI_MASTER_H
#define __FLEXIO_SPI_MASTER_H


#ifndef FLEXIO_SPI_MASTER_INTERRUPT_MODE
  #define FLEXIO_SPI_MASTER_INTERRUPT_MODE 0
#endif

/******************************************************************************
* FLEXIO_SPI_MASTER types
*
*//*! @addtogroup flexio_spi_master_types
* @{
*******************************************************************************/

#define FLEXIO_SPI_MASTER_CPHA_FEDGE_MIDDLE_MASK  0x00
#define FLEXIO_SPI_MASTER_CPHA_FEDGE_START_MASK  0x01

#define FLEXIO_SPI_MASTER_CPOL_ACTLOW_MASK  0x00
#define FLEXIO_SPI_MASTER_CPOL_ACTHIGH_MASK  0x02

#define FLEXIO_SPI_MASTER_LSB_FIRST_MASK  0x00
#define FLEXIO_SPI_MASTER_MSB_FIRST_MASK  0x04

/***************************************************************************//*!
 * @brief   FLEXIO_SPI_MASTER result variables
 * @note    Used as a driver state value for interrupt driver version
 ******************************************************************************/
typedef enum {
    FLEXIO_SPI_MASTER_ST_IDLE = 0,
    FLEXIO_SPI_MASTER_ST_TRANSFER = 1
} FLEXIO_SPI_MASTER_STATE;

/***************************************************************************//*!
 * @brief   FLEXIO_SPI_MASTER state
 * @note    Used as a return result values of individual driver function
 ******************************************************************************/
typedef enum {
    FLEXIO_SPI_MASTER_RES_OK = 0,
    FLEXIO_SPI_MASTER_RES_INVALIDPARAMETER = -1,
    FLEXIO_SPI_MASTER_RES_FAILED = -2,
    FLEXIO_SPI_MASTER_RES_BUSY = -3,
    FLEXIO_SPI_MASTER_RES_BAUDRATE = -4
} FLEXIO_SPI_MASTER_RESULT;

typedef void (*FLEXIO_SPI_MASTER_CALLBACK)(FLEXIO_SPI_MASTER_RESULT result);

/***************************************************************************//*!
 * @brief   FLEXIO_SPI_MASTER configuration structure
 * @note    Used as a holder of configuration setting for the driver
 ******************************************************************************/
typedef struct {
  uint32_t shifterMosiIx;       ///< Index of shifter out (MOSI)
  uint32_t shifterMisoIx;       ///< Index of shifter in (MISO)
  uint32_t timerSclkIx;         ///< Index of timer out (SCLK)
  uint32_t timerCsIx;           ///< Index of timer out (CS)
  uint32_t baudRateDiv;         ///< Requested Baudrate Divider
  uint32_t mode;                ///< Mode of operation of SPI
  volatile unsigned int * pShifterDataOut;   ///< Pointer to shifter Mosi data register
  volatile unsigned int * pShifterDataIn;    ///< Pointer to shifter Miso data register
#if FLEXIO_SPI_MASTER_INTERRUPT_MODE == 1
  const uint8_t * pBufferOut;       ///< Pointer to data to send
  uint8_t * pBufferIn;              ///< Pointer to data buffer for receive
  uint32_t len;                     ///< Length of the data
  uint32_t dataIx;                  ///< Internal data index counter
  FLEXIO_SPI_MASTER_STATE state;    ///< Internal state of the peripheral
  FLEXIO_SPI_MASTER_CALLBACK pCallBack; ///< Pointer to Callback function for following operation
#endif
}FLEXIO_SPI_MASTER_CONFIG;

/*! @} End of flexio_spi_master_types                                                */

/******************************************************************************
* FLEXIO function and macro definitions
*
*//*! @addtogroup flexio_spi_master_macro
* @{
*******************************************************************************/

/*! @} End of flexio_spi_master_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/

 /******************************************************************************
* FLEXIO function and macro definitions
*
*//*! @addtogroup flexio_spi_master_functions
* @{
*******************************************************************************/

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
extern FLEXIO_SPI_MASTER_RESULT FLEXIO_SPI_MASTER_Init(
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
                                  );

/***************************************************************************//*!
* @brief   FLEXIO_SPI_MASTER module Write data function.
* @param   address - slave chip address
* @param   pBuffer - pointer to data buffer
* @param   len - length of data (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @return  Result of Write Operation
* @note    Implemented as function call.
******************************************************************************/
extern FLEXIO_SPI_MASTER_RESULT FLEXIO_SPI_MASTER_Write(FLEXIO_SPI_MASTER_CONFIG * pConfig, const uint8_t * pBuffer, const uint32_t len);


/***************************************************************************//*!
* @brief   FLEXIO_SPI_MASTER module Read data function.
* @param   address - slave chip address
* @param   pBuffer - pointer to data buffer
* @param   len - length of data (restricted to 13 bytes, due to limitation of FlexIO peripheral)
* @return  Result of Read Operation
* @note    Implemented as function call.
******************************************************************************/
extern FLEXIO_SPI_MASTER_RESULT FLEXIO_SPI_MASTER_Read(FLEXIO_SPI_MASTER_CONFIG * pConfig, uint8_t * pBuffer, const uint32_t len);

/***************************************************************************//*!
* @brief   FLEXIO_SPI_MASTER module transfer (Write/Read sequence) data function.
* @param   pConfig - pointer to SPI module instance data structure
* @param   pBufferOut - pointer to data buffer for write sequence
* @param   pBufferIn - pointer to data buffer for read sequence
* @param   len - length of data for transfer sequence
* @return  Result of Transfer (Write/Read sequence) Operation
* @note    Implemented as function call.
******************************************************************************/
extern FLEXIO_SPI_MASTER_RESULT FLEXIO_SPI_MASTER_Transfer(FLEXIO_SPI_MASTER_CONFIG * pConfig, const uint8_t * pBufferOut, uint8_t * pBufferIn, const uint32_t len);
#if FLEXIO_SPI_MASTER_INTERRUPT_MODE != 0
/***************************************************************************//*!
* @brief   FLEXIO_SPI_MASTER module Register CallBack function.
* @param   pCallback - pointer to function CallBack function (NULL for unregister)
* @return  Result of register CallBack function Operation
* @note    Implemented as function call.
******************************************************************************/
  extern FLEXIO_SPI_MASTER_RESULT FLEXIO_SPI_MASTER_SetCallBack(FLEXIO_SPI_MASTER_CONFIG * pConfig, FLEXIO_SPI_MASTER_CALLBACK pCallback);
#endif
/*! @} End of flexio_spi_master_functions                                     */
#endif /* __FLEXIO_SPI_MASTER_H */
