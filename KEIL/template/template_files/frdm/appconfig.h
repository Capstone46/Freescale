/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      appconfig.h
 * @author    
 * @version   0.0.1.0
 * @date      Jun-20-2013
 * @brief     Application configuration and interrupt vector definitions.
 ******************************************************************************/
#ifndef __APPCONFIG_H
#define __APPCONFIG_H

/*******************************************************************************
*//*! @addtogroup _template__config_def
* @{
*******************************************************************************/

/***************************************************************************//*!
 * @brief   Define processor device.
 * @details Supported devices - MCU_MKL43Z256  (MCU_MKL46Z256 temporarily used)
 ******************************************************************************/
#define MCU_MKL43Z256

// Place your definitions here (see examples bellow)

// Redefine you own macros from existing macros in drivers
///**************************************************************************/ /*!
// * @brief Timer channel PWM special configuration.
// *****************************************************************************/
//#define TPM_CHANNEL_PWM_XXX_CONFIG                                            \
//(tTPM_CH)  {                                                                  \
///* CnSC    */ CLR(TPM_CnSC_CHIE_MASK)|SET(TPM_CnSC_MSB_MASK)|                 \
//              SET(TPM_CnSC_MSA_MASK)|SET(TPM_CnSC_ELSB_MASK)|                 \
//              SET(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
//}

// Define your new macros and comment it by two separate approaches
//#define PI     3.14       ///< Ludolf's number        
//#define SQRT2  1.44       ///< number represents squere root of 2

///***************************************************************************//*!
// * @brief   Macro returns number of cycles for calculation.
// * @param   y  - number from 0 to 100
// * @return  numer of cycles
// * @note    Implemented as inlined macro.
// ******************************************************************************/
//#define XXXXX_XX(y)        ((y)<<3)

/******************************************************************************
 * @brief   Define interrupt vectors.
 * @example 
 *          extern void uart_isr (void);       ///< uart isr prototype
 *          #undef  VECTOR_030
 *          #define VECTOR_030 uart_isr        ///< uart_isr interrupt vector re-definition
 ******************************************************************************/

/*! @} End of _template__config_def                                           */

#endif /* __APPCONFIG_ */
