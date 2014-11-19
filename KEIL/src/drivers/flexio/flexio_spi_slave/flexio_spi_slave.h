/*****************************************************************************
 * (c) Copyright 2010-2014, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flexio_spi_slave.h
 * @version   1.0.0.0
 * @date      May-22-2014
 * @brief     FlexIO SPI slave module driver header file.
 *
 * Revision History:
 *  1.	02/04/2014   B20253   Initially written for Kinetis KL43
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup flexio_spi_master_example0
 * @{
 * @par       Source code:
 * @include   flexio_spi_master_test\flexio_spi_master_test.c
 * @par       Appconfig.h:
 * @include   flexio_spi_master_test\appconfig.h
 ******************************************************************************/
/*! @} End of flexio_spi_master_example0    
*/
#ifndef __FLEXIO_SPI_SLAVE_H
#define __FLEXIO_SPI_SLAVE_H


/******************************************************************************
* FLEXIO_SPI_SLAVE types
*
*//*! @addtogroup flexio_spi_master_types
* @{
*******************************************************************************/

#define FLEXIO_SPI_SLAVE_CPHA_FEDGE_MIDDLE_MASK  0x00
#define FLEXIO_SPI_SLAVE_CPHA_FEDGE_START_MASK  0x01

#define FLEXIO_SPI_SLAVE_CPOL_ACTLOW_MASK  0x00
#define FLEXIO_SPI_SLAVE_CPOL_ACTHIGH_MASK  0x02

#define FLEXIO_SPI_SLAVE_LSB_FIRST_MASK  0x00
#define FLEXIO_SPI_SLAVE_MSB_FIRST_MASK  0x04

#define FLEXIO_CALCULATE_CMP_VAL(numberOfBits)       ((numberOfBits * 2) - 1)

/***************************************************************************//*!
 * @brief   FLEXIO_SPI_SLAVE result variables
 * @note    Used as a driver state value for interrupt driver version
 ******************************************************************************/
typedef enum {
    FLEXIO_SPI_SLAVE_ST_IDLE = 0,
    FLEXIO_SPI_SLAVE_ST_READY = 1,
    FLEXIO_SPI_SLAVE_ST_TRANSFER = 2
} FLEXIO_SPI_SLAVE_STATE;

/***************************************************************************//*!
 * @brief   FLEXIO_SPI_SLAVE state
 * @note    Used as a return result values of individual driver function
 ******************************************************************************/
typedef enum {
    FLEXIO_SPI_SLAVE_RES_OK = 0,
    FLEXIO_SPI_SLAVE_RES_INVALIDPARAMETER = -1,
    FLEXIO_SPI_SLAVE_RES_FAILED = -2,
    FLEXIO_SPI_SLAVE_RES_BUSY = -3,
    FLEXIO_SPI_SLAVE_RES_BAUDRATE = -4,
    FLEXIO_SPI_SLAVE_BUFF_OVF = -5,
    FLEXIO_SPI_SLAVE_TX_BUSY = -6
} FLEXIO_SPI_SLAVE_RESULT;

typedef void (*FLEXIO_SPI_SLAVE_CALLBACK)(FLEXIO_SPI_SLAVE_RESULT result);

/***************************************************************************//*!
 * @brief   FLEXIO_SPI_SLAVE configuration structure
 * @note    Used as a holder of configuration setting for the driver
 ******************************************************************************/
typedef struct {
  uint32_t shifterMosiIx;       ///< Index of shifter out (MOSI)
  uint32_t shifterMisoIx;       ///< Index of shifter in (MISO)
  uint32_t timerIx;             ///< Index of timer out (SCLK)
  uint32_t baudRateDiv;         ///< Requested Baudrate Divider
  uint32_t mode;                ///< Mode of operation of SPI
  const uint8_t * pBufferOut;
  uint8_t * pBufferIn;
  uint32_t buffOutLen;
  uint32_t buffInLen;  
  uint32_t dataIx;
  uint32_t dataOutIx;
  uint32_t dataOutLen;
  FLEXIO_SPI_SLAVE_STATE state;
  FLEXIO_SPI_SLAVE_CALLBACK pCallBack; ///< Pointer to Callback function for following operation
}FLEXIO_SPI_SLAVE_CONFIG;

/*! @} End of flexio_spi_master_types                                                */

/******************************************************************************
* FLEXIO function and macro definitions
*
*//*! @addtogroup flexio_spi_slave_macro
* @{
*******************************************************************************/

/*! @} End of flexio_spi_slave_macro                                                       */

/******************************************************************************
* FLEXIO function definitions
*
*//*! @addtogroup flexio_spi_slave_functions
* @{
*******************************************************************************/
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
extern FLEXIO_SPI_SLAVE_RESULT FLEXIO_SPI_SLAVE_Init(   FLEXIO_SPI_SLAVE_CONFIG * pConfig,
                                                        uint32 shifterMosiIx,
                                                        uint32 shifterMisoIx,
                                                        uint32 timerIx,
                                                        uint32 pinMosiIx,
                                                        uint32 pinMisoIx,
                                                        uint32 pinSclkIx,
                                                        uint32 pinCsIx,
                                                        uint32 mode
                                                      );

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
extern FLEXIO_SPI_SLAVE_RESULT FLEXIO_SPI_SLAVE_WriteTransfer(FLEXIO_SPI_SLAVE_CONFIG * pConfig, uint32 dataLen);

/***************************************************************************//*!
* @brief   FLEXIO_SPI_SLAVE_WriteTransfer  
* @param   pConfig - Pointer to configuration structure
* @param   dataLen - Length of the tx data 
* @return  Result of Read Operation
* @note    Implemented as function call.
******************************************************************************/
extern FLEXIO_SPI_SLAVE_RESULT FLEXIO_SPI_SLAVE_SetBuffers(FLEXIO_SPI_SLAVE_CONFIG * pConfig, const uint8_t * pBuffOut, uint8_t * pBuffIn, uint32 buffOutLen, uint32 buffInLen);

/***************************************************************************//*!
* @brief   FLEXIO_SPI_SLAVE_SetCallBack module Register CallBack function.
* @param   pConfig - pointer to configuration structure
* @param   pCallback - pointer to function CallBack function (NULL for unregister)
* @return  Result of register CallBack function Operation
* @note    Implemented as function call.
******************************************************************************/
extern FLEXIO_SPI_SLAVE_RESULT FLEXIO_SPI_SLAVE_SetCallBack(FLEXIO_SPI_SLAVE_CONFIG * pConfig, FLEXIO_SPI_SLAVE_CALLBACK pCallback);

/*! @} End of flexio_spi_slave_functions                                     */

#endif /* __FLEXIO_SPI_SLAVE_H */
