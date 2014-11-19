/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      llwu.h
 * @version   1.0.6.0
 * @date      Feb-18-2013
 * @brief     Low-Leakage Wakeup Unit (LLWU) driver header file.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	01/08/2012   R55013   Ported to Kinetis M 
 *  3.	17/01/2012   B34185   Ported to Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup llwu_example0
 * @{
 * @par       Source code:
 * @include   llwu0_test\llwu0_test.c
 * @par       Appconfig.h:
 * @include   llwu0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of llwu_example0                                                   */
#ifndef __LLWU_H
#define __LLWU_H 
 
/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct { uint8 PE1, PE2, PE3, PE4, ME, FILT1, FILT2; } tLLWU;

/******************************************************************************
* LLWU wakeup sources used by LLWU_GetFlags() and LLWU_ClrFlags() macros
*
*//*! @addtogroup llwu_sources
* @{
*******************************************************************************/
#define WUF0          (uint32)(1 << 0)  ///< LLWU_P0 external input pin
#define WUF1          (uint32)(1 << 1)  ///< LLWU_P1 external input pin
#define WUF2          (uint32)(1 << 2)  ///< LLWU_P2 external input pin
#define WUF3          (uint32)(1 << 3)  ///< LLWU_P3 external input pin
#define WUF4          (uint32)(1 << 4)  ///< LLWU_P4 external input pin
#define WUF5          (uint32)(1 << 5)  ///< PTB0
#define WUF6          (uint32)(1 << 6)  ///< PTC1
#define WUF7          (uint32)(1 << 7)  ///< PTC3
#define WUF8          (uint32)(1 << 8)  ///< PTC4
#define WUF9          (uint32)(1 << 9)  ///< PTC5
#define WUF10         (uint32)(1 << 10) ///< PTC6
#define WUF11         (uint32)(1 << 11) ///< LLWU_P11 external input pin
#define WUF12         (uint32)(1 << 12) ///< LLWU_P12 external input pin
#define WUF13         (uint32)(1 << 13) ///< LLWU_P13 external input pin
#define WUF14         (uint32)(1 << 14) ///< PTD4
#define WUF15         (uint32)(1 << 15) ///< PTD6
#define MWUF0         (uint32)(1 << 16) ///< LPTMR0
#define MWUF1         (uint32)(1 << 17) ///< CMP0
#define MWUF2         (uint32)(1 << 18) ///< Reserved
#define MWUF3         (uint32)(1 << 19) ///< Reserved
#define MWUF4         (uint32)(1 << 20) ///< TSI0
#define MWUF5         (uint32)(1 << 21) ///< RTC Alarm
#define MWUF6         (uint32)(1 << 22) ///< Reserved
#define MWUF7         (uint32)(1 << 23) ///< RTC Second
#define WUFALL        (uint32)(0x0FFFFFFF)     ///< LLWU_P0 external input pin 
/*! @} End of llwu_sources                                                    */

/******************************************************************************
* LLWU default configuration used by LLWU_init() function
*
*//*! @addtogroup llwu_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief All LLWU direct and filtered wakeup sources disabled.
 *****************************************************************************/
#define LLWU_MODULE_DISABLE_ALL_CONFIG   /*  */                               \
(tLLWU){                                                                      \
/* PE1  */ SET(LLWU_PE1_WUPE0 (0x00))|SET(LLWU_PE1_WUPE1 (0x00))|             \
           SET(LLWU_PE1_WUPE2 (0x00))|SET(LLWU_PE1_WUPE3 (0x00)),             \
/* PE2  */ SET(LLWU_PE2_WUPE4 (0x00))|SET(LLWU_PE2_WUPE5 (0x00))|             \
           SET(LLWU_PE2_WUPE6 (0x00))|SET(LLWU_PE2_WUPE7 (0x00)),             \
/* PE3  */ SET(LLWU_PE3_WUPE8 (0x00))|SET(LLWU_PE3_WUPE9 (0x00))|             \
           SET(LLWU_PE3_WUPE10(0x00))|SET(LLWU_PE3_WUPE11(0x00)),             \
/* PE4  */ SET(LLWU_PE4_WUPE12(0x00))|SET(LLWU_PE4_WUPE13(0x00))|             \
           SET(LLWU_PE4_WUPE14(0x00))|SET(LLWU_PE4_WUPE15(0x00)),             \
/* ME   */ CLR(LLWU_ME_WUME0_MASK)|CLR(LLWU_ME_WUME1_MASK)|                   \
           CLR(LLWU_ME_WUME2_MASK)|CLR(LLWU_ME_WUME3_MASK)|                   \
           CLR(LLWU_ME_WUME4_MASK)|CLR(LLWU_ME_WUME5_MASK)|                   \
           CLR(LLWU_ME_WUME6_MASK)|CLR(LLWU_ME_WUME7_MASK)|                   \
/* FILT1*/ SET(LLWU_FILT1_FILTE(0x00))|SET(LLWU_FILT1_FILTSEL(0x00)),         \
/* FILT2*/ SET(LLWU_FILT2_FILTE(0x00))|SET(LLWU_FILT2_FILTSEL(0x00)),         \
}

/**************************************************************************/ /*!
 * @brief All LLWU wakeup sources enabled (rising edge on pin).
 *****************************************************************************/
#define LLWU_ALL_RE_PM_ENABLE_CONFIG                                          \
(tLLWU){                                                                      \
/* PE1  */ SET(LLWU_PE1_WUPE0 (0x01))|SET(LLWU_PE1_WUPE1 (0x01))|             \
           SET(LLWU_PE1_WUPE2 (0x01))|SET(LLWU_PE1_WUPE3 (0x01)),             \
/* PE2  */ SET(LLWU_PE2_WUPE4 (0x01))|SET(LLWU_PE2_WUPE5 (0x01))|             \
           SET(LLWU_PE2_WUPE6 (0x01))|SET(LLWU_PE2_WUPE7 (0x01)),             \
/* PE3  */ SET(LLWU_PE3_WUPE8 (0x01))|SET(LLWU_PE3_WUPE9 (0x01))|             \
           SET(LLWU_PE3_WUPE10(0x01))|SET(LLWU_PE3_WUPE11(0x01)),             \
/* PE4  */ SET(LLWU_PE4_WUPE12(0x01))|SET(LLWU_PE4_WUPE13(0x01))|             \
           SET(LLWU_PE4_WUPE14(0x01))|SET(LLWU_PE4_WUPE15(0x01)),             \
/* ME   */ SET(LLWU_ME_WUME0_MASK)|SET(LLWU_ME_WUME1_MASK)|                   \
           SET(LLWU_ME_WUME2_MASK)|SET(LLWU_ME_WUME3_MASK)|                   \
           SET(LLWU_ME_WUME4_MASK)|SET(LLWU_ME_WUME5_MASK)|                   \
           SET(LLWU_ME_WUME6_MASK)|SET(LLWU_ME_WUME7_MASK)|                   \
/* FILT1*/ SET(LLWU_FILT1_FILTE(0x00))|SET(LLWU_FILT1_FILTSEL(0x00)),         \
/* FILT2*/ SET(LLWU_FILT2_FILTE(0x00))|SET(LLWU_FILT2_FILTSEL(0x00)),         \
}

/**************************************************************************/ /*!
 * @brief All LLWU wakeup sources enabled (falling edge on pin).
 *****************************************************************************/
#define LLWU_ALL_FE_PM_ENABLE_CONFIG                                          \
(tLLWU){                                                                      \
/* PE1  */ SET(LLWU_PE1_WUPE0 (0x02))|SET(LLWU_PE1_WUPE1 (0x02))|             \
           SET(LLWU_PE1_WUPE2 (0x02))|SET(LLWU_PE1_WUPE3 (0x02)),             \
/* PE2  */ SET(LLWU_PE2_WUPE4 (0x02))|SET(LLWU_PE2_WUPE5 (0x02))|             \
           SET(LLWU_PE2_WUPE6 (0x02))|SET(LLWU_PE2_WUPE7 (0x02)),             \
/* PE3  */ SET(LLWU_PE3_WUPE8 (0x02))|SET(LLWU_PE3_WUPE9 (0x02))|             \
           SET(LLWU_PE3_WUPE10(0x02))|SET(LLWU_PE3_WUPE11(0x02)),             \
/* PE4  */ SET(LLWU_PE4_WUPE12(0x02))|SET(LLWU_PE4_WUPE13(0x02))|             \
           SET(LLWU_PE4_WUPE14(0x02))|SET(LLWU_PE4_WUPE15(0x02)),             \
/* ME   */ SET(LLWU_ME_WUME0_MASK)|SET(LLWU_ME_WUME1_MASK)|                   \
           SET(LLWU_ME_WUME2_MASK)|SET(LLWU_ME_WUME3_MASK)|                   \
           SET(LLWU_ME_WUME4_MASK)|SET(LLWU_ME_WUME5_MASK)|                   \
           SET(LLWU_ME_WUME6_MASK)|SET(LLWU_ME_WUME7_MASK)|                   \
/* FILT1*/ SET(LLWU_FILT1_FILTE(0x00))|SET(LLWU_FILT1_FILTSEL(0x00)),         \
/* FILT2*/ SET(LLWU_FILT2_FILTE(0x00))|SET(LLWU_FILT2_FILTSEL(0x00)),         \
}

/**************************************************************************/ /*!
 * @brief All LLWU wakeup sources enabled (both edges on pin).
 *****************************************************************************/
#define LLWU_ALL_BE_PM_ENABLE_ALL_CONFIG                                      \
(tLLWU){                                                                      \
/* PE1  */ SET(LLWU_PE1_WUPE0 (0x03))|SET(LLWU_PE1_WUPE1 (0x03))|             \
           SET(LLWU_PE1_WUPE2 (0x03))|SET(LLWU_PE1_WUPE3 (0x03)),             \
/* PE2  */ SET(LLWU_PE2_WUPE4 (0x03))|SET(LLWU_PE2_WUPE5 (0x03))|             \
           SET(LLWU_PE2_WUPE6 (0x03))|SET(LLWU_PE2_WUPE7 (0x03)),             \
/* PE3  */ SET(LLWU_PE3_WUPE8 (0x03))|SET(LLWU_PE3_WUPE9 (0x03))|             \
           SET(LLWU_PE3_WUPE10(0x03))|SET(LLWU_PE3_WUPE11(0x03)),             \
/* PE4  */ SET(LLWU_PE4_WUPE12(0x03))|SET(LLWU_PE4_WUPE13(0x03))|             \
           SET(LLWU_PE4_WUPE14(0x03))|SET(LLWU_PE4_WUPE15(0x03)),             \
/* ME   */ SET(LLWU_ME_WUME0_MASK)|SET(LLWU_ME_WUME1_MASK)|                   \
           SET(LLWU_ME_WUME2_MASK)|SET(LLWU_ME_WUME3_MASK)|                   \
           SET(LLWU_ME_WUME4_MASK)|SET(LLWU_ME_WUME5_MASK)|                   \
           SET(LLWU_ME_WUME6_MASK)|SET(LLWU_ME_WUME7_MASK)|                   \
/* FILT1*/ SET(LLWU_FILT1_FILTE(0x00))|SET(LLWU_FILT1_FILTSEL(0x00)),         \
/* FILT2*/ SET(LLWU_FILT2_FILTE(0x00))|SET(LLWU_FILT2_FILTSEL(0x00)),         \
}

// used just for compatibility with older examples
/**************************************************************************/ /*!
 * @brief LPTMR and RTC alarn wakeup sources enabled.
 *****************************************************************************/
#define LLWU_MODULE_CONFIG1   /*  */                                          \
(tLLWU){                                                                      \
/* PE1  */ SET(LLWU_PE1_WUPE0 (0x00))|SET(LLWU_PE1_WUPE1 (0x00))|             \
           SET(LLWU_PE1_WUPE2 (0x00))|SET(LLWU_PE1_WUPE3 (0x00)),             \
/* PE2  */ SET(LLWU_PE2_WUPE4 (0x00))|SET(LLWU_PE2_WUPE5 (0x00))|             \
           SET(LLWU_PE2_WUPE6 (0x00))|SET(LLWU_PE2_WUPE7 (0x00)),             \
/* PE3  */ SET(LLWU_PE3_WUPE8 (0x00))|SET(LLWU_PE3_WUPE9 (0x00))|             \
           SET(LLWU_PE3_WUPE10(0x00))|SET(LLWU_PE3_WUPE11(0x00)),             \
/* PE4  */ SET(LLWU_PE4_WUPE12(0x00))|SET(LLWU_PE4_WUPE13(0x00))|             \
           SET(LLWU_PE4_WUPE14(0x00))|SET(LLWU_PE4_WUPE15(0x00)),             \
/* ME   */ SET(LLWU_ME_WUME0_MASK)|CLR(LLWU_ME_WUME1_MASK)|                   \
           CLR(LLWU_ME_WUME2_MASK)|CLR(LLWU_ME_WUME3_MASK)|                   \
           CLR(LLWU_ME_WUME4_MASK)|SET(LLWU_ME_WUME5_MASK)|                   \
           CLR(LLWU_ME_WUME6_MASK)|CLR(LLWU_ME_WUME7_MASK)|                   \
/* FILT1*/ SET(LLWU_FILT1_FILTE(0x00))|SET(LLWU_FILT1_FILTSEL(0x00)),         \
/* FILT2*/ SET(LLWU_FILT2_FILTE(0x00))|SET(LLWU_FILT2_FILTSEL(0x00)),         \
}

/**************************************************************************/ /*!
 * @brief LPTMR and RTC alarn wakeup sources enabled.
 *****************************************************************************/
#define LLWU_LPTMR_RTC_ALARM_CONFIG                                            \
(tLLWU){                                                                      \
/* PE1  */ SET(LLWU_PE1_WUPE0 (0x00))|SET(LLWU_PE1_WUPE1 (0x00))|             \
           SET(LLWU_PE1_WUPE2 (0x00))|SET(LLWU_PE1_WUPE3 (0x00)),             \
/* PE2  */ SET(LLWU_PE2_WUPE4 (0x00))|SET(LLWU_PE2_WUPE5 (0x00))|             \
           SET(LLWU_PE2_WUPE6 (0x00))|SET(LLWU_PE2_WUPE7 (0x00)),             \
/* PE3  */ SET(LLWU_PE3_WUPE8 (0x00))|SET(LLWU_PE3_WUPE9 (0x00))|             \
           SET(LLWU_PE3_WUPE10(0x00))|SET(LLWU_PE3_WUPE11(0x00)),             \
/* PE4  */ SET(LLWU_PE4_WUPE12(0x00))|SET(LLWU_PE4_WUPE13(0x00))|             \
           SET(LLWU_PE4_WUPE14(0x00))|SET(LLWU_PE4_WUPE15(0x00)),             \
/* ME   */ SET(LLWU_ME_WUME0_MASK)|CLR(LLWU_ME_WUME1_MASK)|                   \
           CLR(LLWU_ME_WUME2_MASK)|CLR(LLWU_ME_WUME3_MASK)|                   \
           CLR(LLWU_ME_WUME4_MASK)|SET(LLWU_ME_WUME5_MASK)|                   \
           CLR(LLWU_ME_WUME6_MASK)|CLR(LLWU_ME_WUME7_MASK)|                   \
/* FILT1*/ SET(LLWU_FILT1_FILTE(0x00))|SET(LLWU_FILT1_FILTSEL(0x00)),         \
/* FILT2*/ SET(LLWU_FILT2_FILTE(0x00))|SET(LLWU_FILT2_FILTSEL(0x00)),         \
}

// used just for compatibility with older examples
/**************************************************************************/ /*!
 * @brief LLWU_P7 (PTC3) wakeup source enabled on rising edge detection.
 *****************************************************************************/
#define LLWU_MODULE_PTC3_RISING                                                \
        LLWU_PTC3_RE_CONFIG

/**************************************************************************/ /*!
 * @brief LLWU_P7 (PTC3) wakeup source enabled on rising edge detection.
 *****************************************************************************/
#define LLWU_PTC3_RE_CONFIG     /* PTC3 - LLWU_P7 enabled as wakeup source */ \
(tLLWU){                                                                      \
/* PE1  */ SET(LLWU_PE1_WUPE0 (0x00))|SET(LLWU_PE1_WUPE1 (0x00))|             \
           SET(LLWU_PE1_WUPE2 (0x00))|SET(LLWU_PE1_WUPE3 (0x00)),             \
/* PE2  */ SET(LLWU_PE2_WUPE4 (0x00))|SET(LLWU_PE2_WUPE5 (0x00))|             \
           SET(LLWU_PE2_WUPE6 (0x00))|SET(LLWU_PE2_WUPE7 (0x01)),             \
/* PE3  */ SET(LLWU_PE3_WUPE8 (0x00))|SET(LLWU_PE3_WUPE9 (0x00))|             \
           SET(LLWU_PE3_WUPE10(0x00))|SET(LLWU_PE3_WUPE11(0x00)),             \
/* PE4  */ SET(LLWU_PE4_WUPE12(0x00))|SET(LLWU_PE4_WUPE13(0x00))|             \
           SET(LLWU_PE4_WUPE14(0x00))|SET(LLWU_PE4_WUPE15(0x00)),             \
/* ME   */ CLR(LLWU_ME_WUME0_MASK)|CLR(LLWU_ME_WUME1_MASK)|                   \
           CLR(LLWU_ME_WUME2_MASK)|CLR(LLWU_ME_WUME3_MASK)|                   \
           CLR(LLWU_ME_WUME4_MASK)|CLR(LLWU_ME_WUME5_MASK)|                   \
           CLR(LLWU_ME_WUME6_MASK)|CLR(LLWU_ME_WUME7_MASK)|                   \
/* FILT1*/ SET(LLWU_FILT1_FILTE(0x00))|SET(LLWU_FILT1_FILTSEL(0x00)),         \
/* FILT2*/ SET(LLWU_FILT2_FILTE(0x00))|SET(LLWU_FILT2_FILTSEL(0x00)),         \
}

// used just for compatibility with older examples
/**************************************************************************/ /*!
 * @brief LLWU_P7 (PTC3) wakeup source enabled on falling edge detection.
 *****************************************************************************/
#define LLWU_MODULE_PTC3_FALLING                                               \
        LLWU_PTC3_FE_CONFIG

/**************************************************************************/ /*!
 * @brief LLWU_P7 (PTC3) wakeup source enabled on falling edge detection.
 *****************************************************************************/
#define LLWU_PTC3_FE_CONFIG     /* PTC3 - LLWU_P7 enabled as wakeup source */ \
(tLLWU){                                                                      \
/* PE1  */ SET(LLWU_PE1_WUPE0 (0x00))|SET(LLWU_PE1_WUPE1 (0x00))|             \
           SET(LLWU_PE1_WUPE2 (0x00))|SET(LLWU_PE1_WUPE3 (0x00)),             \
/* PE2  */ SET(LLWU_PE2_WUPE4 (0x00))|SET(LLWU_PE2_WUPE5 (0x00))|             \
           SET(LLWU_PE2_WUPE6 (0x00))|SET(LLWU_PE2_WUPE7 (0x02)),             \
/* PE3  */ SET(LLWU_PE3_WUPE8 (0x00))|SET(LLWU_PE3_WUPE9 (0x00))|             \
           SET(LLWU_PE3_WUPE10(0x00))|SET(LLWU_PE3_WUPE11(0x00)),             \
/* PE4  */ SET(LLWU_PE4_WUPE12(0x00))|SET(LLWU_PE4_WUPE13(0x00))|             \
           SET(LLWU_PE4_WUPE14(0x00))|SET(LLWU_PE4_WUPE15(0x00)),             \
/* ME   */ SET(LLWU_ME_WUME0_MASK)|CLR(LLWU_ME_WUME1_MASK)|                   \
           CLR(LLWU_ME_WUME2_MASK)|CLR(LLWU_ME_WUME3_MASK)|                   \
           CLR(LLWU_ME_WUME4_MASK)|SET(LLWU_ME_WUME5_MASK)|                   \
           CLR(LLWU_ME_WUME6_MASK)|CLR(LLWU_ME_WUME7_MASK)|                   \
/* FILT1*/ SET(LLWU_FILT1_FILTE(0x00))|SET(LLWU_FILT1_FILTSEL(0x00)),         \
/* FILT2*/ SET(LLWU_FILT2_FILTE(0x00))|SET(LLWU_FILT2_FILTSEL(0x00)),         \
}

// used just for compatibility with older examples
/**************************************************************************/ /*!
 * @brief LLWU_P7 (PTC3) wakeup source enabled on both edges detection.
 *****************************************************************************/
#define LLWU_MODULE_PTC3_BOTH                                                 \
        LLWU_PTC3_BE_CONFIG

/**************************************************************************/ /*!
 * @brief LLWU_P7 (PTC3) wakeup source enabled on both edges detection.
 *****************************************************************************/
#define LLWU_PTC3_BE_CONFIG     /* PTC3 - LLWU_P7 enabled as wakeup source */ \
(tLLWU){                                                                      \
/* PE1  */ SET(LLWU_PE1_WUPE0 (0x00))|SET(LLWU_PE1_WUPE1 (0x00))|             \
           SET(LLWU_PE1_WUPE2 (0x00))|SET(LLWU_PE1_WUPE3 (0x00)),             \
/* PE2  */ SET(LLWU_PE2_WUPE4 (0x00))|SET(LLWU_PE2_WUPE5 (0x00))|             \
           SET(LLWU_PE2_WUPE6 (0x00))|SET(LLWU_PE2_WUPE7 (0x03)),             \
/* PE3  */ SET(LLWU_PE3_WUPE8 (0x00))|SET(LLWU_PE3_WUPE9 (0x00))|             \
           SET(LLWU_PE3_WUPE10(0x00))|SET(LLWU_PE3_WUPE11(0x00)),             \
/* PE4  */ SET(LLWU_PE4_WUPE12(0x00))|SET(LLWU_PE4_WUPE13(0x00))|             \
           SET(LLWU_PE4_WUPE14(0x00))|SET(LLWU_PE4_WUPE15(0x00)),             \
/* ME   */ SET(LLWU_ME_WUME0_MASK)|CLR(LLWU_ME_WUME1_MASK)|                   \
           CLR(LLWU_ME_WUME2_MASK)|CLR(LLWU_ME_WUME3_MASK)|                   \
           CLR(LLWU_ME_WUME4_MASK)|SET(LLWU_ME_WUME5_MASK)|                   \
           CLR(LLWU_ME_WUME6_MASK)|CLR(LLWU_ME_WUME7_MASK)|                   \
/* FILT1*/ SET(LLWU_FILT1_FILTE(0x00))|SET(LLWU_FILT1_FILTSEL(0x00)),         \
/* FILT2*/ SET(LLWU_FILT2_FILTE(0x00))|SET(LLWU_FILT2_FILTSEL(0x00)),         \
}
/*! @} End of llwu_config                                                     */

/******************************************************************************
* LLWU callback registered by LLWU_Init() function
*
*//*! @addtogroup llwu_callback
* @{
*******************************************************************************/
/*! @brief LLWU_CALLBACK function declaration.                           
    @details This callback is called by the LLWU module upon recovery from VLLS modes.
             The service routine shall restore I/O and release latch states by @ref 
             PMC_SetACKISO() macro.
    @param   flags  Wakeup source @ref llwu_sources
*******************************************************************************/
typedef void (*LLWU_CALLBACK)(uint32 flags);
/*! @} End of llwu_callback                                                   */

/******************************************************************************
* LLWU function and macro definitions
*
*//*! @addtogroup llwu_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro returns mask of wakeup flags indicating which internal 
 *          wakeup source caused the MCU to exit LLS or VLLS mode.
 * @return  32-bit unsigned integer indicating wakeup source @ref llwu_sources
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LLWU_GetFlags()   (((uint32)LLWU_F3<<16)|((uint32)LLWU_F2<<8)|(uint32)LLWU_F1)

/***************************************************************************//*!
 * @brief  Macro clears wakeup flags indicated by input mask.
 * @param  mask  Use one or more ORed wakeup sources @ref llwu_sources.
 * @note   Implemented as inlined macro.
 ******************************************************************************/
#define LLWU_ClrFlags(mask)   {                                                 \
                                LLWU_F3 = (uint8)((mask>>16)&0xff);             \
                                LLWU_F2 = (uint8)((mask>> 8)&0xff);             \
                                LLWU_F1 = (uint8)((mask>> 0)&0xff);             \
                              }

/***************************************************************************//*!
 * @brief   LLWU initialization function.
 * @details This function initalizes LLWU module. Wakeup sources shall be 
 *          configured by the user in configuration structure @ref llwu_config.
 *          Function also installs callback function for interrupt vector 28 (LLWU).
 * @param   cfg       Use one of following configuration structure @ref 
 *                    llwu_config
 * @param   ip        Interrupt priority 0..3
 * @param   callback  pointer to @ref llwu_callback function
 * @note    Implemented as function call.
 ******************************************************************************/ 
#define LLWU_Init(cfg,ip,callback)      LLWU_Init(cfg,ip,callback)
/*! @} End of llwu_macro                                                      */ 

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/    
extern void LLWU_Init (tLLWU llwu, uint8 ip, LLWU_CALLBACK pCallback);

#endif /* __LLWU_H */ 
