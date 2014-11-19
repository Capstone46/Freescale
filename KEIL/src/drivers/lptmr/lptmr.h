/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      lptmr.h
 * @version   1.0.4.0
 * @date      Feb-18-2013
 * @brief     Low-Power Timer (LPTMR) driver header file.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	01/08/2012   R55013   Ported to Kinetis M
 *  3.	17/01/2013   B34185   Ported to Kinetis L  
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup lptmr_example0
 * @{
 * @par       Source code:
 * @include   lptmr0_test\lptmr0_test.c
 * @par       Appconfig.h:
 * @include   lptmr0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of lptmr_example0                                                  */
#ifndef __LPTMR_H
#define __LPTMR_H 
 
/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct { uint32 CSR, PSR; } tLPTMR;

/******************************************************************************
* LPTMR pulse counter input options
*
*//*! @addtogroup lptmr_insrc_list
* @{
*******************************************************************************/
#define LPTMR_CMP0_OUT  (uint32)(0x00)  ///< Comparator output 
#define LPTMR_ALT1_PIN  (uint32)(0x01)  ///< LPTMR alternative 1
#define LPTMR_ALT2_PIN  (uint32)(0x02)  ///< LPTMR alternative 2
#define LPTMR_ALT3_PIN  (uint32)(0x03)  ///< LPTMR alternative 3
/*! @} End of lptmr_insrc_list                                                */

/******************************************************************************
* LPTMR prescaler/glitch filter clocking options used by configuration
* structures of LPTMR_Init() function
*
*//*! @addtogroup lptmr_clock_list
* @{
*******************************************************************************/
#define LPTMR_MCGIRCLK  (uint32)0x00  ///< MCGIRCLK internal reference clock (not
                                      ///  available in low leakage power modes)
#define LPTMR_LPOCLK    (uint32)0x01  ///< Internal 1 kHz LPO clock.
#define LPTMR_OSCCLK32K (uint32)0x02  ///< 32.768 kHz clock from OSC32K. This 
                                      ///  connection is optimized for minimal 
                                      ///  power consumption in stop modes.
#define LPTMR_OSCERCLK  (uint32)0x03  ///< External clock (ERCLK) from the 
                                      ///  Crystal Oscillator (XOSC)
/*! @} End of lptmr_clock_list                                                */ 

/******************************************************************************
* LPTMR default configurations used by LPTMR_Init() function
*
*//*! @addtogroup lptmr_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief Timer mode with prescaler bypassed selected and timer operation is 
 *        disabled after @ref LPTMR_Init() function call. Timer counts until  
 *        TCF flag is set then counter is reseted and counting starts again.
 *        Timer interrupt is enabled.
 * @param   clksrc    Use one of following clock sources @ref lptmr_clock_list.
 *****************************************************************************/
#define LPTMR_TIMER_PBYP_CNT_RST_ONTCF_MODE_IRQ_CONFIG(clksrc)                \
(tLPTMR){                                                                     \
/* CSR    */ SET(LPTMR_CSR_TIE_MASK)|SET(LPTMR_CSR_TPS(0))|                   \
             CLR(LPTMR_CSR_TPP_MASK)|CLR(LPTMR_CSR_TCF_MASK)|                 \
             CLR(LPTMR_CSR_TMS_MASK)|CLR(LPTMR_CSR_TEN_MASK),                 \
/* PSR    */ SET(LPTMR_PSR_PCS(clksrc))|SET(LPTMR_PSR_PRESCALE(0x0))|         \
             SET(LPTMR_PSR_PBYP_MASK)                                         \
}

/**************************************************************************/ /*!
 * @brief Timer mode selected and timer operation is disabled after @ref LPTMR_Init()
 *        function call. Timer counts until TCF flag is set then counter is reseted 
 *        and counting starts again. Timer interrupt is enabled.
 * @param   presc     Input clock divider value in range from 0 up 15. It divides 
 *                    timer clock by factor \f$2^(presc+1)\f$.
 * @param   clksrc    Use one of following clock sources @ref lptmr_clock_list.
 *****************************************************************************/
#define LPTMR_TIMER_CNT_RST_ONTCF_MODE_IRQ_CONFIG(presc,clksrc)                \
(tLPTMR){                                                                     \
/* CSR    */ SET(LPTMR_CSR_TIE_MASK)|SET(LPTMR_CSR_TPS(0))|                   \
             CLR(LPTMR_CSR_TPP_MASK)|CLR(LPTMR_CSR_TCF_MASK)|                 \
             CLR(LPTMR_CSR_TMS_MASK)|CLR(LPTMR_CSR_TEN_MASK),                 \
/* PSR    */ SET(LPTMR_PSR_PCS(clksrc))|SET(LPTMR_PSR_PRESCALE(presc))|       \
             CLR(LPTMR_PSR_PBYP_MASK)                                         \
}

#define LPTMR_TIMER_CNT_RST_ONTCF_MODE_INT_ENABLED_CONFIG(presc,clksrc)        \
        LPTMR_TIMER_CNT_RST_ONTCF_MODE_IRQ_CONFIG(presc,clksrc)
          
/**************************************************************************/ /*!
 * @brief Timer mode selected and timer operation is disabled after @ref LPTMR_Init()
 *        function call. Timer counts until TCF flag is set then counter is reseted 
 *        and counting starts again. Timer interrupt is disabled.
 * @param   presc     Input clock divider value in range from 0 up 15. It divides 
 *                    timer clock by factor \f$2^(presc+1)\f$.
 * @param   clksrc    Use one of following clock sources @ref lptmr_clock_list.
 *****************************************************************************/
#define LPTMR_TIMER_CNT_RST_ONTCF_MODE_CONFIG(presc,clksrc)                   \
(tLPTMR){                                                                     \
/* CSR    */ CLR(LPTMR_CSR_TIE_MASK)|SET(LPTMR_CSR_TPS(0))|                   \
             CLR(LPTMR_CSR_TPP_MASK)|CLR(LPTMR_CSR_TCF_MASK)|                 \
             CLR(LPTMR_CSR_TMS_MASK)|CLR(LPTMR_CSR_TEN_MASK),                 \
/* PSR    */ SET(LPTMR_PSR_PCS(clksrc))|SET(LPTMR_PSR_PRESCALE(presc))|       \
             CLR(LPTMR_PSR_PBYP_MASK)                                         \
}

#define LPTMR_TIMER_CNT_RST_ONTCF_MODE_INT_DISABLED_CONFIG(presc,clksrc)       \
        LPTMR_TIMER_CNT_RST_ONTCF_MODE_CONFIG(presc,clksrc)
          
/**************************************************************************/ /*!
 * @brief Timer mode selected and timer operation is disabled after @ref LPTMR_Init()
 *        function call. Timer counts in free running mode. Timer interrupt is disabled.
 * @param   presc     Input clock divider value in range from 0 up 15. It divides 
 *                    timer clock by factor \f$2^(presc+1)\f$.
 * @param   clksrc    Use one of following clock sources @ref lptmr_clock_list.
 *****************************************************************************/
#define LPTMR_TIMER_FREERUN_MODE_CONFIG(presc,clksrc)                         \
(tLPTMR){                                                                     \
/* CSR    */ CLR(LPTMR_CSR_TIE_MASK)|SET(LPTMR_CSR_TPS(0))|                   \
             CLR(LPTMR_CSR_TPP_MASK)|SET(LPTMR_CSR_TCF_MASK)|                 \
             CLR(LPTMR_CSR_TMS_MASK)|CLR(LPTMR_CSR_TEN_MASK),                 \
/* PSR    */ SET(LPTMR_PSR_PCS(clksrc))|SET(LPTMR_PSR_PRESCALE(presc))|       \
             CLR(LPTMR_PSR_PBYP_MASK)                                         \
}

#define LPTMR_TIMER_FREERUN_MODE_INT_DISABLED_CONFIG(presc,clksrc)       \
        LPTMR_TIMER_FREERUN_MODE_CONFIG(presc,clksrc)

/**************************************************************************/ /*!
 * @brief Timer mode selected and timer operation is disabled after @ref LPTMR_Init()
 *        function call. Timer counts in free running mode. Timer interrupt is enabled.
 * @param   presc     Input clock divider value in range from 0 up 15. It divides 
 *                    timer clock by factor \f$2^(presc+1)\f$.
 * @param   clksrc    Use one of following clock sources @ref lptmr_clock_list.
 *****************************************************************************/
#define LPTMR_TIMER_FREERUN_MODE_IRQ_CONFIG(presc,clksrc)                     \
(tLPTMR){                                                                     \
/* CSR    */ SET(LPTMR_CSR_TIE_MASK)|SET(LPTMR_CSR_TPS(0))|                   \
             CLR(LPTMR_CSR_TPP_MASK)|SET(LPTMR_CSR_TCF_MASK)|                 \
             CLR(LPTMR_CSR_TMS_MASK)|CLR(LPTMR_CSR_TEN_MASK),                 \
/* PSR    */ SET(LPTMR_PSR_PCS(clksrc))|SET(LPTMR_PSR_PRESCALE(presc))|       \
             CLR(LPTMR_PSR_PBYP_MASK)                                         \
}         
          
/**************************************************************************/ /*!
 * @brief Pulse mode selected and timer operation is disabled after @ref LPTMR_Init()
 *        function call. Counter is reset on overflow. Counter increment on 
 *        input source rising edge. Interrupt is enabled.
 * @param   presc     Input clock divider value in range from 0 up 15. It divides 
 *                    timer clock by factor \f$2^(presc+1)\f$.
 * @param   clksrc    Use one of following clock sources @ref lptmr_clock_list.
 * @param   insrc     Use one of following clock sources @ref lptmr_insrc_list.
 *****************************************************************************/
#define LPTMR_PULSE_FREERUN_ACTHIGH_MODE_IRQ_CONFIG(presc,clksrc,insrc)       \
(tLPTMR){                                                                     \
/* CSR    */ SET(LPTMR_CSR_TIE_MASK)|SET(LPTMR_CSR_TPS(insrc))|               \
             CLR(LPTMR_CSR_TPP_MASK)|SET(LPTMR_CSR_TCF_MASK)|                 \
             SET(LPTMR_CSR_TMS_MASK)|CLR(LPTMR_CSR_TEN_MASK),                 \
/* PSR    */ SET(LPTMR_PSR_PCS(clksrc))|SET(LPTMR_PSR_PRESCALE(presc))|       \
             CLR(LPTMR_PSR_PBYP_MASK)                                         \
}

/**************************************************************************/ /*!
 * @brief Pulse mode selected and timer operation is disabled after @ref LPTMR_Init()
 *        function call. Counter is reset on compare. Counter increment on 
 *        input source rising edge. Interrupt is enabled.
 * @param   presc     Input clock divider value in range from 0 up 15. It divides 
 *                    timer clock by factor \f$2^(presc+1)\f$.
 * @param   clksrc    Use one of following clock sources @ref lptmr_clock_list.
 * @param   insrc     Use one of following input pin sources @ref lptmr_insrc_list.
 *****************************************************************************/
#define LPTMR_PULSE_COMPARE_ACTHIGH_MODE_IRQ_CONFIG(presc,clksrc,insrc)       \
(tLPTMR){                                                                     \
/* CSR    */ SET(LPTMR_CSR_TIE_MASK)|SET(LPTMR_CSR_TPS(insrc))|               \
             CLR(LPTMR_CSR_TPP_MASK)|CLR(LPTMR_CSR_TCF_MASK)|                 \
             SET(LPTMR_CSR_TMS_MASK)|CLR(LPTMR_CSR_TEN_MASK),                 \
/* PSR    */ SET(LPTMR_PSR_PCS(clksrc))|SET(LPTMR_PSR_PRESCALE(presc))|       \
             CLR(LPTMR_PSR_PBYP_MASK)                                         \
}

/*! @} End of lptmr_config                                                    */

/******************************************************************************
* AFE callback registered by LPTMR_Init() function
*
*//*! @addtogroup lptmr_callback
* @{
*******************************************************************************/
/*! LPTMR_CALLBACK type declaration                                           */
typedef void (*LPTMR_CALLBACK)(void);
/*! @} End of lptmr_callback                                                  */

/******************************************************************************
* XBAR function and macro definitions
*
*//*! @addtogroup lptmr_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro resumes timer operation.
 * @details This macro enables operation of the Low-Power Timer (LPTMR) block.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTMR_Enable()          { LPTMR0_CSR |=  LPTMR_CSR_TEN_MASK;           } 

/***************************************************************************//*!
 * @brief   Macro stops timer operation.
 * @details This macro terminates operation of the Low-Power Timer (LPTMR) block.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTMR_Disable()         { LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;           }

/***************************************************************************//*!
 * @brief   Macro select time counter mode.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTMR_TimeModeEnable()  { LPTMR0_CSR &= ~LPTMR_CSR_TMS_MASK;           } 

/***************************************************************************//*!
 * @brief   Macro select pulse counter mode.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTMR_PulseModeEnable()  { LPTMR0_CSR |= LPTMR_CSR_TMS_MASK;           } 

/***************************************************************************//*!
 * @brief   Macro enable free runnning mode - CNT is reset on oveflow.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTMR_FreeRunnningEnable()  { LPTMR0_CSR |= LPTMR_CSR_TFC_MASK;         } 

/***************************************************************************//*!
 * @brief   Macro disable free runnning mode - CNT is reset on compare.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTMR_FreeRunnningDisable()  { LPTMR0_CSR &= ~LPTMR_CSR_TFC_MASK;       } 

#define LPTMR_PinPolarity_ACTIVE_LOW()   LPTMR0_CSR |= LPTMR_CSR_TPP_MASK;
#define LPTMR_PinPolarity_ACTIVE_HIGH()  LPTMR0_CSR &= ~LPTMR_CSR_TPP_MASK;
/***************************************************************************//*!
 * @brief   Macro disable free runnning mode - CNT is reset on compare.
 * @param   actpol - ACTIVE_LOW or ACTIVE_HIGH
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTMR_PinPolarity(actpol)     LPTMR_PinPolarity_##actpol##() 

/***************************************************************************//*!
 * @brief   Macro selects the input source for pulse counter mode.
 * @param   insrc - 0x00 or 0x10 or 0x20 or 0x30 (@ref lptmr_insrc_list)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTMR_InputSource(insrc)     LPTMR0_CSR = SET(LPTMR_CSR_TPS(insrc))|    \
                                                (uint32)(0xCF&LPTMR0_CSR); 

/***************************************************************************//*!
 * @brief   Macro resets counter of running timer. 
 * @details This macro resets counter of the running timer. After counter reset
 *          timer continue in operation..
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTMR_Reset()          { LPTMR_Disable(); LPTMR_Enable();             }

/***************************************************************************//*!
 * @brief   Macro reads timer counter value.
 * @details This macro returns current value of the LPTMR counter.
 * @param   cntval - variable to be stored counter value
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTMR_ReadCnr(cntval)   {LPTMR0_CNR = 0x00; cntval = (int16)LPTMR0_CNR;}

/***************************************************************************//*!
 * @brief   Macro returns timer compare flag.
 * @details This macro returns timer compare flag when timer increments.
 * @return  TRUE - value of counter is equal to compare value.
 *          FALSE- value of counter is not equal to compare value.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTMR_GetCmpFlag()        ((LPTMR0_CSR>>LPTMR_CSR_TCF_SHIFT)&0x00001)

/***************************************************************************//*!
 * @brief   Macro clears timer compare flag.
 * @details This macro clears timer compare flag.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTMR_ClrCmpFlag()      { LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;            } 


/***************************************************************************//*!
 * @brief   Macro sets compare register.
 * @details This macro sets new value into compare register. 
 * @param   x     16-bit integer value
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPTRM_SetCompVal(x)     { LPTMR0_CMR  = (x);                           }

/***************************************************************************//*!
 * @brief   LPTMR initialization function.
 * @details This function initalizes Low-Power Timer (LPTRM) block. It also 
 *          installs callback function for LPTMR interrupt vector 46.
 * @param   cfg       Use one of following configuration structures @ref 
 *                    lptmr_config
 * @param   cmpval    16-bit integer compare register value (defines period of 
 *                    the interrupt generation).
 * @param   ip        Interrupt priority 0..3
 * @param   callback  pointer to @ref LPTMR_CALLBACK function
 * @note    Implemented as function call. 
 ******************************************************************************/ 
#define LPTMR_Init(cfg,cmpval,ip,callback)  LPTMR_Init(cfg,cmpval,ip,callback)
/*! @} End of lptmr_macro                                                     */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern void LPTMR_Init  (tLPTMR lptmr, uint16 compValue, uint8 ip, LPTMR_CALLBACK pCallback);

#endif /* __LPTMR_H */ 
