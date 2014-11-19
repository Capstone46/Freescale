/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      smc.h
 * @version   1.0.7.0
 * @date      Jan-18-2013
 * @brief     System Mode Controller (SMC) driver header file.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.  01/01/2011   B12615   Updated 
 *  3.	17/01/2013   B34185   Ported to Kinetis L  
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup smc_example0
 * @{
 * @par       Source code:
 * @include   smc0_test\smc0_test.c
 * @par       Appconfig.h:
 * @include   smc0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of smc_example0                                                     */
#ifndef __SMC_H
#define __SMC_H 
 
/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct  { uint8 PMPROT;      } tSMC_INIT;
typedef struct  { uint8 PMCTRL, STOPCTRL, SCR, WFI; } tSMC_MODE;

/******************************************************************************
* Operation modes definition returned by SMC_GetMode() macro
*
*//*! @addtogroup smc_modes
* @{
*******************************************************************************/
typedef enum    {                                                               
                  RUN=(1<<0),           ///< Current power mode is RUN
                  STOP=(1<<1),          ///< Current power mode is STOP
                  VLPR=(1<<2),          ///< Current power mode is VLPR
                  VLPW=(1<<3),          ///< Current power mode is VLPW
                  VLPS=(1<<4),          ///< Current power mode is VLPS   
                  LLS=(1<<5),           ///< Current power mode is LLS
                  VLLS=(1<<6)           ///< Current power mode is VLLS                                    
                } eMODE_TYPE;
/*! @} End of smc_modes                                                       */

/******************************************************************************
* SMC default configurations used by SMC_init() function
*
*//*! @addtogroup smc_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief All Very-Low-Power (VLPS) and Low-Leakage (LLS, VLLSx) modes enabled.
 *****************************************************************************/
#define SMC_MODULE_CONFIG1     SMC_MODULE_ALL_ON_CONFIG

/**************************************************************************/ /*!
 * @brief All Very-Low-Power (VLPS) and Low-Leakage (LLS, VLLSx) modes enabled.
 *****************************************************************************/
#define SMC_MODULE_ALL_ON_CONFIG     /* enable all low power modes         */  \
(tSMC_INIT){                                                                   \
/* PMPROT*/ SET(SMC_PMPROT_AVLP_MASK)|SET(SMC_PMPROT_ALLS_MASK)|               \
            SET(SMC_PMPROT_AVLLS_MASK),                                        \
}

/**************************************************************************/ /*!
 * @brief Only Very-Low-Power (VLPS) modes enabled.
 *****************************************************************************/
#define SMC_MODULE_VLP_CONFIG  /* enable just low power modes              */  \
(tSMC_INIT){                                                                   \
/* PMPROT*/ SET(SMC_PMPROT_AVLP_MASK)|CLR(SMC_PMPROT_ALLS_MASK)|               \
            CLR(SMC_PMPROT_AVLLS_MASK),                                        \
}

/**************************************************************************/ /*!
 * @brief Only one Low-Leakage (LLS) mode enabled.
 *****************************************************************************/
#define SMC_MODULE_LLS_CONFIG  /* enable just low leakage mode             */  \
(tSMC_INIT){                                                                   \
/* PMPROT*/ CLR(SMC_PMPROT_AVLP_MASK)|SET(SMC_PMPROT_ALLS_MASK)|               \
            CLR(SMC_PMPROT_AVLLS_MASK),                                        \
}

/**************************************************************************/ /*!
 * @brief Only Veru-Low-Leakage (VLLSx) modes enabled.
 *****************************************************************************/
#define SMC_MODULE_VLLS_CONFIG  /* enable just very low leakage modes      */  \
(tSMC_INIT){                                                                   \
/* PMPROT*/ CLR(SMC_PMPROT_AVLP_MASK)|CLR(SMC_PMPROT_ALLS_MASK)|               \
            SET(SMC_PMPROT_AVLLS_MASK),                                        \
}

/**************************************************************************/ /*!
 * @brief Only Low-Leakage (LLS, VLLSx) modes enabled.
 *****************************************************************************/
#define SMC_MODULE_LLS_VLLS_CONFIG  /* enable just low leakage modes  */       \
(tSMC_INIT){                                                                   \
/* PMPROT*/ CLR(SMC_PMPROT_AVLP_MASK)|SET(SMC_PMPROT_ALLS_MASK)|               \
            SET(SMC_PMPROT_AVLLS_MASK),                                        \
}
/*! @} End of smc_config                                                      */

/******************************************************************************
* SMC function and macro definitions
*
*//*! @addtogroup smc_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro returns reset type.
 * @return  eRESET_TYPE (@ref rst_sources)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif

/***************************************************************************//*!
 * @brief   Macro returns operating mode.
 * @return  eMODE_TYPE (@ref smc_modes)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define SMC_GetMode()     (eMODE_TYPE)SMC_PMSTAT

#define SMC_SetModeRUN    {                                                    \
                            REG_SetVal(SMC_PMCTRL,SMC_PMCTRL_RUNM,0x00);       \
                          }
#define SMC_SetModeRUN_COP                                                     \
                          {                                                    \
                            REG_SetVal(MCM_CPO,MCM_CPO_CPOWOI,0x01);           \
                            REG_SetVal(MCM_CPO,MCM_CPO_CPOREQ,0x01);           \
                            while(!(MCM_CPO & MCM_CPO_CPOACK_MASK));           \
                            while(MCM_CPO & MCM_CPO_CPOACK_MASK);              \
                          }
#define SMC_SetModeWAIT   {                                                    \
                            REG_SetVal(SMC_PMCTRL,SMC_PMCTRL_STOPM,0x00);      \
                            wait();                                            \
                          }
#define SMC_SetModeSTOP   {                                                    \
                            REG_SetVal(SMC_STOPCTRL,SMC_STOPCTRL_PSTOPO,0x00); \
                            REG_SetVal(SMC_PMCTRL,SMC_PMCTRL_STOPM,0x00);      \
                            stop();                                            \
                          }
#define SMC_SetModePSTOP1                                                      \
                          {                                                    \
                            REG_SetVal(SMC_PMCTRL  ,SMC_PMCTRL_STOPM,0x00);    \
                            REG_SetVal(SMC_STOPCTRL,SMC_STOPCTRL_PSTOPO,0x01); \
                            stop();                                            \
                          }
#define SMC_SetModePSTOP2                                                      \
                          {                                                    \
                            REG_SetVal(SMC_PMCTRL  ,SMC_PMCTRL_STOPM,0x00);    \
                            REG_SetVal(SMC_STOPCTRL,SMC_STOPCTRL_PSTOPO,0x02); \
                            stop();                                            \
                          }
#define SMC_SetModeVLPR   {                                                    \
                            REG_SetVal(SMC_PMCTRL,SMC_PMCTRL_RUNM,0x02);       \
                            while (SMC_GetMode() != VLPR);                     \
                          }
#define SMC_SetModeVLPR_COP                                                    \
                          {                                                    \
                            REG_SetVal(SMC_PMCTRL,SMC_PMCTRL_RUNM,0x02);       \
                            while (SMC_GetMode() != VLPR);                     \
                            REG_SetVal(MCM_CPO,MCM_CPO_CPOWOI,0x00);           \
                            REG_SetVal(MCM_CPO,MCM_CPO_CPOREQ,0x01);           \
                            while(!(MCM_CPO & MCM_CPO_CPOACK_MASK));           \
                            while(MCM_CPO & MCM_CPO_CPOACK_MASK);              \
                          }
#define SMC_SetModeVLPW   {                                                    \
                            REG_SetVal(SMC_PMCTRL,SMC_PMCTRL_STOPM,0x00);      \
                            wait();                                            \
                          }
#define SMC_SetModeVLPS   {                                                    \
                            REG_SetVal(SMC_PMCTRL,SMC_PMCTRL_STOPM,0x02);      \
                            stop();                                            \
                          }
#define SMC_SetModeVLPS_PSTOP1                                                 \
                          {                                                    \
                            REG_SetVal(SMC_STOPCTRL,SMC_STOPCTRL_PSTOPO,0x01); \
                            while((SMC_STOPCTRL & SMC_STOPCTRL_PSTOPO_MASK) != 0x40);\
                            REG_SetVal(SMC_PMCTRL  ,SMC_PMCTRL_STOPM,0x02);    \
                            stop();                                            \
                          }
#define SMC_SetModeVLPS_PSTOP2                                                 \
                          {                                                    \
                            REG_SetVal(SMC_STOPCTRL,SMC_STOPCTRL_PSTOPO,0x02); \
                            while((SMC_STOPCTRL & SMC_STOPCTRL_PSTOPO_MASK) != 0x80);\
                            REG_SetVal(SMC_PMCTRL  ,SMC_PMCTRL_STOPM,0x02);    \
                            stop();                                            \
                          }
#define SMC_SetModeLLS    {                                                    \
                            REG_SetVal(SMC_PMCTRL,SMC_PMCTRL_STOPM,0x03);      \
                            stop();                                            \
                          }
#define SMC_SetModeVLLS3  {                                                    \
                            REG_SetVal(SMC_STOPCTRL,SMC_STOPCTRL_VLLSM,0x03);  \
                            REG_SetVal(SMC_PMCTRL  ,SMC_PMCTRL_STOPM,0x04);    \
                            stop();                                            \
                          }
#define SMC_SetModeVLLS1  {                                                    \
                            REG_SetVal(SMC_STOPCTRL,SMC_STOPCTRL_VLLSM,0x01);  \
                            REG_SetVal(SMC_PMCTRL  ,SMC_PMCTRL_STOPM,0x04);    \
                            stop();                                            \
                          }
#define SMC_SetModeVLLS0_POR_ON                                                \
                          {                                                    \
                            REG_SetVal(SMC_STOPCTRL,SMC_STOPCTRL_PORPO,0x00);  \
                            REG_SetVal(SMC_STOPCTRL,SMC_STOPCTRL_VLLSM,0x00);  \
                            REG_SetVal(SMC_PMCTRL  ,SMC_PMCTRL_STOPM,0x04);    \
                            stop();                                            \
                          }
#define SMC_SetModeVLLS0_POR_OFF                                               \
                          {                                                    \
                            REG_SetVal(SMC_STOPCTRL,SMC_STOPCTRL_PORPO,0x01);  \
                            REG_SetVal(SMC_STOPCTRL,SMC_STOPCTRL_VLLSM,0x00);  \
                            REG_SetVal(SMC_PMCTRL  ,SMC_PMCTRL_STOPM,0x04);    \
                            stop();                                            \
                          }

/***************************************************************************//*!
 * @brief   Macro sets device operating mode.
 * @param   mode      <b>Operation modes supported:</b>
 *                    RUN|WAIT|STOP|PSTOP1|PSTOP2|VLPR|VLPW|VLPS|VLPS_PSTOP1|
 *                    VLPS_PSTOP2|LLS|VLLS3|VLLS1|VLLS0_POR_ON|VLLS0_POR_OFF|
 *                    RUN_COP|VLPR_COP
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define SMC_SetMode(mode) SMC_SetMode##mode

/***************************************************************************//*!
 * @brief   SMC initialization function.
 * @details This function initalizes System Mode Controller (SMC).
 * @param   cfg       Use one of following configuration structures @ref 
 *                    smc_config
 * @note    Implemented as function call.
 ******************************************************************************/ 
#define SMC_Init(cfg)     SMC_Init(cfg)
/*! @} End of smc_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/    
extern void SMC_Init (tSMC_INIT smc);

#endif /* __SMC_H */ 
