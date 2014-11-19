/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      osc.h
 * @version   1.0.5.0
 * @date      Feb-21-2013
 * @brief     System Oscillator (OSC) driver header file.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	11/11/2012   R55013   Ported to Kinetis M
 *  3.	17/01/2013   B34185   Ported to Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup osc_example0
 * @{
 * @par       Source code:
 * @include   osc0_test\osc0_test.c
 * @par       Appconfig.h:
 * @include   osc0_test\appconfig.h
 ******************************************************************************/
/*! @} End of osc_example0                                                    */
#ifndef __OSC_H
#define __OSC_H 
 
/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct { uint8 CR; } tOSC;

/******************************************************************************
* OSC load capacitors definitions used by OSC_Init() function
*
*//*! @addtogroup osc_load_caps
* @{
*******************************************************************************/
#define OSC_SC16P (uint8)0x01   ///< Add 16 pF capacitor to the oscillator load
#define OSC_SC8P  (uint8)0x02   ///< Add 08 pF capacitor to the oscillator load
#define OSC_SC4P  (uint8)0x04   ///< Add 04 pF capacitor to the oscillator load
#define OSC_SC2P  (uint8)0x08   ///< Add 02 pF capacitor to the oscillator load
#define OSC_SC0P  (uint8)0x00   ///< No internal load capacitor applied
/*! @} End of osc_load_caps                                                   */

/******************************************************************************
* OSC default configurations used by OSC_Init() function
*
*//*! @addtogroup osc_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief   Disables external reference clock (OSCERCLK).
 * @details Configuration options:
 * - External reference (OSCERCLK) clock is inactive.
 * - External reference (OSCERCLK) is disabled in Stop mode.
 * - No load capacitors applied.
 *****************************************************************************/
#define OSC_MODULE_OSCERCLK_OFF_STOPMODE_OFF_CONFIG                           \
(tOSC){                                                                       \
/* CR */ CLR(OSC_CR_ERCLKEN_MASK)|CLR(OSC_CR_EREFSTEN_MASK)                   \
}

/**************************************************************************/ /*!
 * @brief   Enables external reference clock (OSCERCLK). The OSCERCLK is 
 *          disabled in STOP mode. 
 * @details Configuration options:
 * - External reference (OSCERCLK) clock is active.
 * - External reference (OSCERCLK) is disabled in Stop mode.
 * @param   caps  Select one or more load capacitors @ref osc_load_caps.
 *****************************************************************************/
#define OSC_MODULE_OSCERCLK_ON_STOPMODE_OFF_CONFIG(caps)        	      \
(tOSC){                                                                       \
/* CR */ SET(OSC_CR_ERCLKEN_MASK)|CLR(OSC_CR_EREFSTEN_MASK)|(caps)            \
}

/**************************************************************************/ /*!
 * @brief   Enables external reference clock (OSCERCLK). The OSCERCLK is enabled
 *          in STOP mode. 
 * @details Configuration options:
 * - External reference (OSCERCLK) clock is active.
 * - External reference (OSCERCLK) is enabled in Stop mode.
 * @param   caps  Select one or more load capacitors @ref osc_load_caps.
 *****************************************************************************/
#define OSC_MODULE_OSCERCLK_ON_STOPMODE_ON_CONFIG(caps)           	          \
(tOSC){                                                                       \
/* CR */ SET(OSC_CR_ERCLKEN_MASK)|SET(OSC_CR_EREFSTEN_MASK)|(caps)            \
}
/*! @} End of osc_config                                                      */

/******************************************************************************
*OSC function and macro definitions
*
*//*! @addtogroup osc_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   System oscillator initialization.
 * @details This macro initalizes system oscillator (OSC) module.
 * @param   cfg   Use one of following configuration structures @ref osc_config.
 * @note    Implemented as inline macro.
 ******************************************************************************/
 #define OSC_Init(cfg)          { OSC0_CR = cfg.CR; } 
/*! @} End of osc_macro                                                       */

#endif /* __OSC_H */
