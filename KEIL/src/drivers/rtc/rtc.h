/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      rtc.h
 * @version   1.0.3.0
 * @date      Feb-18-2013
 * @brief     Real time clock module driver header file.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written for Kinetis K
 *  2.	17/01/2013   B34185   Ported to Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup rtc_example0
 * @{
 * @par       Source code:
 * @include   rtc0_test\rtc0_test.c
 * @par       Appconfig.h:
 * @include   rtc0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of rtc_example0                                                    */
#ifndef __RTC_H
#define __RTC_H
 
/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct { uint32 TSR, TPR, TAR, TCR, CR, SR, LR, IER;  } tRTC;

/******************************************************************************
* RTC data structure used by RTC_MkTime() adn RTC_GmTime() functions
*
*//*! @addtogroup rtc_struct
* @{
*******************************************************************************/
typedef struct 
{
  int16 tm_sec;                   ///< seconds after the minute [0, 59]        
  int16 tm_min;                   ///< minutes after the hour [0, 59]          
  int16 tm_hour;                  ///< hours since midnight [0, 23]            
  int16 tm_mday;                  ///< day of the month [1, 31]                
  int16 tm_mon;                   ///< months since January [0, 11]            
  int16 tm_year;                  ///< years [1970, 2038]                      
  int16 tm_wday;                  ///< days since Sunday [0, 6]                
  int16 tm_yday;                  ///< days since January 1 [0, 365]           
} tTIME;
/*! @} End of rtc_struct                                                      */

/******************************************************************************
* RTC configuration used by RTC_init() function
*
*//*! @addtogroup rtc_config
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Default RTC configuration.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define RTC_DEFAULT_CONFIG                                                    \
(tRTC){                                                                       \
/* TSR    */ 0l,                  /* value not used by the RTC_Init()     */  \
/* TPR    */ 0l,                  /* value not used by the RTC_Init()     */  \
/* TAR    */ 0l,                                                              \
/* TCR    */ SET(RTC_TCR_TCR(0x00))|SET(RTC_TCR_CIR(0x00)),                   \
/* CR     */ CLR(RTC_CR_SC2P_MASK)|CLR(RTC_CR_SC4P_MASK)|                     \
             CLR(RTC_CR_SC8P_MASK)|CLR(RTC_CR_SC16P_MASK)|                    \
             CLR(RTC_CR_CLKO_MASK)|CLR(RTC_CR_OSCE_MASK)|CLR(RTC_CR_UM_MASK)| \
             CLR(RTC_CR_SUP_MASK)|CLR(RTC_CR_WPE_MASK)|CLR(RTC_CR_SWR_MASK),  \
/* SR     */ CLR(RTC_SR_TCE_MASK),                                            \
/* LR     */ SET(RTC_LR_LRL_MASK)|SET(RTC_LR_SRL_MASK)|SET(RTC_LR_CRL_MASK)|  \
             SET(RTC_LR_TCL_MASK)|(0x87),                                     \
/* IER    */ CLR(RTC_IER_WPON_MASK)|CLR(RTC_IER_TSIE_MASK)|CLR(RTC_IER_TAIE_MASK)|                   \
             CLR(RTC_IER_TOIE_MASK)|CLR(RTC_IER_TIIE_MASK),                   \
}

#define RTC_DISABLE_CONFIG	RTC_DEFAULT_CONFIG

/***************************************************************************//*!
 * @brief   Basic RTC configuration.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define RTC_MODULE_CONFIG                                                     \
(tRTC){                                                                       \
/* TSR    */ 0l,                  /* value not used by the RTC_Init()     */  \
/* TPR    */ 0l,                  /* value not used by the RTC_Init()     */  \
/* TAR    */ 0l,                                                              \
/* TCR    */ SET(RTC_TCR_TCR(0x00))|SET(RTC_TCR_CIR(0x01)),                   \
/* CR     */ SET(RTC_CR_SC2P_MASK)|CLR(RTC_CR_SC4P_MASK)|                     \
             CLR(RTC_CR_SC8P_MASK)|CLR(RTC_CR_SC16P_MASK)|                    \
             CLR(RTC_CR_CLKO_MASK)|SET(RTC_CR_OSCE_MASK)|SET(RTC_CR_UM_MASK)| \
             CLR(RTC_CR_SUP_MASK)|CLR(RTC_CR_WPE_MASK)|CLR(RTC_CR_SWR_MASK),  \
/* SR     */ SET(RTC_SR_TCE_MASK),                                            \
/* LR     */ SET(RTC_LR_LRL_MASK)|SET(RTC_LR_SRL_MASK)|SET(RTC_LR_CRL_MASK)|  \
             SET(RTC_LR_TCL_MASK)|(0x87),                                     \
/* IER    */ CLR(RTC_IER_WPON_MASK)|SET(RTC_IER_TSIE_MASK)|SET(RTC_IER_TAIE_MASK)|                   \
             SET(RTC_IER_TOIE_MASK)|SET(RTC_IER_TIIE_MASK),                   \
}
/*! @} End of rtc_config                                                      */

/******************************************************************************
* RTC callback used in RTC_Init() function
*
*//*! @addtogroup rtc_callback
* @{
*******************************************************************************/
/*! @brief RTC_CALLBACK type declaration                                      */
typedef enum {TAF_CALLBACK=1, TOF_CALLBACK=2, TIF_CALLBACK=4, TSF_CALLBACK=8 } \
              RTC_CALLBACK_TYPE;
 /*! @brief RTC_CALLBACK function declaration                                 */
typedef void (*RTC_CALLBACK)(RTC_CALLBACK_TYPE type);
/*! @} End of rtc_callback                                                    */

/******************************************************************************
 * VBAT register file declaration                                             *
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	extern __root __no_init volatile uint8 VbatRegisterFile[];
#elif defined(__ARMCC_VERSION)
	__attribute__((used)) extern volatile uint8 VbatRegisterFile[32] __attribute__((section(".vbatregfile")));
#endif

/******************************************************************************
* RTC function and macro definitions
*
*//*! @addtogroup rtc_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro writes seconds to seconds register (TSR).
 * @param   nsec - number of seconds 
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define RTC_SetTime(nsec)      {                                              \
                                  if (RTC_SR & RTC_SR_TCE_MASK)               \
                                  {                                           \
                                    RTC_SR &= ~RTC_SR_TCE_MASK;               \
                                    RTC_TSR = (nsec);                         \
                                    RTC_SR |=  RTC_SR_TCE_MASK;               \
                                   }                                          \
                                  else { RTC_TSR = (nsec); }                  \
                                } 

/***************************************************************************//*!
 * @brief   Macro reads seconds from second register (TSR).
 * @return  number of seconds
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define RTC_GetTime()           RTC_TSR   
                         
/***************************************************************************//*!
 * @brief   Macro writes seconds to alarm register (TAR).
 * @param   nsec - number of seconds
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define RTC_SetAlarm(nsec)         { RTC_TAR = (nsec); }

/***************************************************************************//*!
 * @brief   Macro adjusts external clock compensation register (TCR).
 * @param   CIR     - compensation interval register 1..256 in seconds.
 * @param   TCR     - time compensation register -127..128 in number of clock 
 *                    cycles.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define RTC_Compensate(CIR,TCR) { RTC_TCR = RTC_TCR_CIR(CIR)|RTC_TCR_TCR(TCR); }

/***************************************************************************//*!
 * @brief   RTC initialization function.
 * @param   cfg      - RTC module configuration structure passed by value: 
 *                     RTC_MODULE_CONFIG
 * @param   sec  - number of seconds to initialize seconds register (TSR)
 * @param   ip       - interrupt priority 0..15
 * @param   callback - pointer to RTC_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define RTC_Init(cfg,sec,ip,callback)   RTC_Init(cfg,sec,ip,callback)

/***************************************************************************//*!
 * @brief   Converts calendar time to number of seconds.
 * @param   ptime   - pointer to calendar structure (@ref rtc_struct)
 * @return  number of seconds
 * @note    Implemented as function call.
 ******************************************************************************/
#define RTC_MkTime(ptime)       RTC_MkTime (ptime)

/***************************************************************************//*!
 * @brief   Converts number of seconds to calendar time.
 * @param   val - number of seconds
 * @param   ptime - pointer to calendar time (@ref rtc_struct)
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define RTC_GmTime(val,ptime)       RTC_GmTime (val,ptime)

/*! @} End of rtc_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/    
extern void   RTC_Init    (tRTC rtc, uint32 seconds, uint8 ip, RTC_CALLBACK pCallback);
extern uint32 RTC_MkTime  (tTIME *timep);
extern void   RTC_GmTime  (uint32 numSeconds, tTIME *timep);

#endif /* __RTC_H */ 
