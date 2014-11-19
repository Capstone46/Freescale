/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      pit.h
 * @version   1.0.2.0
 * @date      Jan-18-2013
 * @brief     Periodic Interrupt Timer (PIT) driver header file.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	01/08/2012   R55013   Ported to Kinetis M
 *  3.	17/01/2013   B34185   Ported to Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup pit_example0
 * @{
 * @par       Source code:
 * @include   pit0_test\pit0_test.c
 * @par       Appconfig.h:
 * @include   pit0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of pit_example0                                                    */
#ifndef __PIT_H
#define __PIT_H 
 
/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct { uint32 TCTRL;  } tPIT_CH;

/******************************************************************************
* PIT timer channel default configurations used by PIT_init() function
*
*//*! @addtogroup pit_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief Timer channel enabled and timer runs after initialization.
 * Interrupt enabled on the peripheral level.
 *****************************************************************************/
#define PIT_CH_TIMER_EN_CONFIG                                                \
(tPIT_CH){                                                                    \
/* TCTRL  */  CLR(PIT_TCTRL_CHN_MASK)|SET(PIT_TCTRL_TIE_MASK)|                \
              SET(PIT_TCTRL_TEN_MASK),                                        \
}

/**************************************************************************/ /*!
 * @brief Timer channel enabled but timer stops. Use @ref PIT_Enable() macro 
 * to start timer operation. Interrupt enabled on the peripheral level.
 *****************************************************************************/
#define PIT_CH_TIMER_DI_CONFIG                                                \
(tPIT_CH){                                                                    \
/* TCTRL  */  CLR(PIT_TCTRL_CHN_MASK)|SET(PIT_TCTRL_TIE_MASK)|                \
              CLR(PIT_TCTRL_TEN_MASK),                                        \
}

/**************************************************************************/ /*!
 * @brief Timer channel default configuration.
 *****************************************************************************/
#define PIT_CH_TIMER_DEFAULT_CONFIG                                           \
(tPIT_CH){                                                                    \
/* TCTRL  */  CLR(PIT_TCTRL_CHN_MASK)|CLR(PIT_TCTRL_TIE_MASK)|                \
              CLR(PIT_TCTRL_TEN_MASK),                                        \
}

#define PIT_CH_TIMER_DISABLE_CONFIG     PIT_CH_TIMER_DEFAULT_CONFIG
/*! @} End of pit_config                                                      */

/******************************************************************************
* PIT callback registered by PIT_InstallCallback() function
*
*//*! @addtogroup pit_callback
* @{
*******************************************************************************/
/*! @brief PIT_CALLBACK type declaration                                      */
typedef enum 
{ 
  PIT0CH0_CALLBACK=1, ///< PIT0_CH0 interrupt
  PIT0CH1_CALLBACK=2, ///< PIT0_CH1 interrupt
} PIT_CALLBACK_TYPE;

/*! @brief PIT_CALLBACK function declaration                                  */
typedef void (*PIT_CALLBACK)(PIT_CALLBACK_TYPE type);
/*! @} End of pit_callback                                                    */

/******************************************************************************
* PIT function and macro definitions
*
*//*! @addtogroup pit_macro
* @{
*******************************************************************************/
#define PIT0CH0_SetLoadVal(value)   { PIT_LDVAL0 = value;                    }
#define PIT0CH1_SetLoadVal(value)   { PIT_LDVAL1 = value;                    }
/***************************************************************************//*!
 * @brief   Macro sets load value register.
 * @details This macro sets new load register value.
 * @param   module    PIT0
 * @param   ch        CH0,CH1
 * @param   value     @ref uint32 load register value 
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define PIT_SetLoadVal(module,ch,value) module##ch##_SetLoadVal(value)

#define PIT0CH0_Enable          { PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;          }
#define PIT0CH1_Enable          { PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK;          }
/***************************************************************************//*!
 * @brief   Macro enables PIT channel.
 * @details This macro enables PIT channel operation.
 * @param   module    PIT0
 * @param   ch        CH0,CH1
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define PIT_Enable(module,ch)           module##ch##_Enable

#define PIT0CH0_Disable         { PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;         }
#define PIT0CH1_Disable         { PIT_TCTRL1 &= ~PIT_TCTRL_TEN_MASK;         }
/***************************************************************************//*!
 * @brief   Macro disables PIT channel.
 * @details This macro disables PIT channel operation.
 * @param   module    PIT0
 * @param   ch        CH0,CH1
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define PIT_Disable(module,ch)          module##ch##_Disable

/***************************************************************************//*!
 * @brief   Macro controls PIT module operation in debug mode.
 * @details This macro controls operation mode of the PIT module in the debug
 *          mode.
 * @param   module    PIT0
 * @param   ctrl      TRUE  (Timer module runs in Debug mode)\n
 *                    FALSE (Timer module stopped in Debug mode)\n
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define PIT_DebugFreezeOn(module,ctrl)  {                                     \
                                          if (ctrl == TRUE)                   \
                                            module##_MCR |= PIT_MCR_FRZ_MASK; \
                                          else                                \
                                            module##_MCR &=~PIT_MCR_FRZ_MASK; \
                                        }

/***************************************************************************//*!
 * @brief   PIT initialization function.
 * @details This function initializes selected timer channel of the 
 *          Periodic Interrupt Timer (PIT) block.  
 * @param   module    PIT0
 * @param   ch        CH0,CH1
 * @param   cfg       Use one of following configuration structures 
 *                    @ref pit_config
 * @param   value     @ref uint32 load register value  e
 * @param   ip        Interrupt priority 0..3
 * @param   callback  Pointer to @ref PIT_CALLBACK function
 * @note    Implemented as function call.
 ******************************************************************************/
#define PIT_Init(module,ch,cfg,value,ip,callback) module##_##ch##_Init(cfg,value,ip,callback)
/*! @} End of pit_macro                                                       */
  
/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern void PIT0_CH0_Init  (tPIT_CH ch, uint32 value, uint8 ip, PIT_CALLBACK pCallback);
extern void PIT0_CH1_Init  (tPIT_CH ch, uint32 value, uint8 ip, PIT_CALLBACK pCallback);

#endif /* __PIT_H */ 
