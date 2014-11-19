/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      mcm.h
 * @version   1.0.7.0
 * @date      Jan-18-2013
 * @brief     Miscellaneous control module (MCM) driver header file.
 *
 * Revision History:
 *  1.	09/01/2013   B34185   Initialy writen for KL 
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup mcm_example0
 * @{
 * @par       Source code:
 * @include   axbs0_test\axbs0_test.c
 * @par       Appconfig.h:
 * @include   axbs0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of mcm_example0                                                    */
#ifndef __MCM_H
#define __MCM_H 

#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif

/******************************************************************************
* Flash memory controller configurations
*
*//*! @addtogroup mcm_fmccfgmacro
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief Enable flash controller speculation buffer. (instruction buffering 
 *        enabled automatically).
 *****************************************************************************/
#define MCM_FMC_SpeculationEnable()   REG_SetVal(MCM_PLACR,MCM_PLACR_DFCS,0x0);

/**************************************************************************/ /*!
 * @brief Disable flash controller speculation buffer.
 *****************************************************************************/
#define MCM_FMC_SpeculationDisable()  REG_SetVal(MCM_PLACR,MCM_PLACR_DFCS,0x1);

/**************************************************************************/ /*!
 * @brief Enable flash controller speculation buffer for data.
 *****************************************************************************/
#define MCM_FMC_DataSpeculationEnable()   REG_SetVal(MCM_PLACR,MCM_PLACR_EFDS,0x1);

/**************************************************************************/ /*!
 * @brief Disable flash controller speculation buffer for data.
 *****************************************************************************/
#define MCM_FMC_DataSpeculationDisable()  REG_SetVal(MCM_PLACR,MCM_PLACR_EFDS,0x0);

/**************************************************************************/ /*!
 * @brief Enable flash controller cache.
 *****************************************************************************/
#define MCM_FMC_CacheEnable()   REG_SetVal(MCM_PLACR,MCM_PLACR_DFCC,0x0);

/**************************************************************************/ /*!
 * @brief Disable flash controller cache.
 *****************************************************************************/
#define MCM_FMC_CacheDisable()  REG_SetVal(MCM_PLACR,MCM_PLACR_DFCC,0x1);

/**************************************************************************/ /*!
 * @brief Enable flash controller cache for instruction caching.
 *****************************************************************************/
#define MCM_FMC_InstructionsCacheEnable()   REG_SetVal(MCM_PLACR,MCM_PLACR_DFCIC,0x0);

/**************************************************************************/ /*!
 * @brief Disable flash controller cache for instruction caching.
 *****************************************************************************/
#define MCM_FMC_InstructionsCacheDisable()  REG_SetVal(MCM_PLACR,MCM_PLACR_DFCIC,0x1);

/**************************************************************************/ /*!
 * @brief Enable flash controller cache for data caching.
 *****************************************************************************/
#define MCM_FMC_DataCacheEnable()   REG_SetVal(MCM_PLACR,MCM_PLACR_DFCDA,0x0);

/**************************************************************************/ /*!
 * @brief Disable flash controller cache for data caching.
 *****************************************************************************/
#define MCM_FMC_DataCacheDisable()  REG_SetVal(MCM_PLACR,MCM_PLACR_DFCDA,0x1);

/**************************************************************************/ /*!
 * @brief Clear flash controller cache.
 *****************************************************************************/
#define MCM_FMC_CacheClear()  REG_SetVal(MCM_PLACR,MCM_PLACR_CFCC,0x1);
/*! @} End of mcm_fmccfgmacro                                                 */

/******************************************************************************
* Crossbar switch configuration
*
*//*! @addtogroup mcm_axbscfgmacro
* @{
*******************************************************************************/
#define MCM_AXBS_Arbitration_FIXED()            REG_SetVal(MCM_PLACR,MCM_PLACR_ARB,0x0);
#define MCM_AXBS_Arbitration_ROUND_ROBIN()      REG_SetVal(MCM_PLACR,MCM_PLACR_ARB,0x1);
/**************************************************************************/ /*!
 * @brief Enable flash controller speculation buffer. (instruction buffering 
 *        enabled automatically).
 * @param arbit - FIXED|ROUND_ROBIN
 *****************************************************************************/
#define MCM_AXBS_ArbitrationSel(arbit)   MCM_AXBS_Arbitration_##arbit##()

/**************************************************************************/ /*!
 * @brief Read the crossbar slave configuration.
 * @return present slave inputs on device
 *****************************************************************************/
#define MCM_AXBS_GetSlaveCfg()          (uint16)MCM_PLASC

/**************************************************************************/ /*!
 * @brief Read the crossbar master configuration.
 * @return present master input ports on device
 *****************************************************************************/
#define MCM_AXBS_GetMasterCfg()          (uint16)MCM_PLAMC
/*! @} End of mcm_axbscfgmacro                                                     */


/******************************************************************************
* Compute operation configuration
*
*//*! @addtogroup mcm_cocfgmacro
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief Enable wake up (clear CPO request bit) on interrupt when in compute 
 *        only operation mode.
 *****************************************************************************/
#define MCM_CPO_WakeupIrqEnable()   REG_SetVal(MCM_CPO,MCM_CPO_CPOWOI,0x1);

/**************************************************************************/ /*!
 * @brief Disable wake up on interrupt when in compute only operation mode -
 *        CPO request bit is not cleared on interrupt/exeption vector fetch.
 *****************************************************************************/
#define MCM_CPO_WakeupIrqDisable()  REG_SetVal(MCM_CPO,MCM_CPO_CPOWOI,0x0);

/**************************************************************************/ /*!
 * @brief Check the activity of compute operation mode.
 * @return TRUE - when compute operation mode is active, 
           FALSE - when compute operation mode is not active
 *****************************************************************************/
#define MCM_CPO_ActivityCheck()     (MCM_CPO&MCM_CPO_CPOACK_MASK?TRUE:FALSE);

/**************************************************************************/ /*!
 * @brief Set request for compute operation mode.
 *****************************************************************************/
#define MCM_CPO_RequestSet()        REG_SetVal(MCM_CPO,MCM_CPO_CPOREQ,0x1);
/*! @} End of mcm_cocfgmacro                                                  */


#endif /* __MCM_H */ 
