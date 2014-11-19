/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      rcm.h
 * @version   1.0.7.0
 * @date      Jan-18-2013
 * @brief     Reset control module (RCM) driver header file.
 *
 * Revision History:
 *  1.	09/01/2013   R55013   Initialy inherited from smc driver 
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup rcm_example0
 * @{
 * @par       Source code:
 * @include   rcm0_test\rcm0_test.c
 * @par       Appconfig.h:
 * @include   rcm0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of smc_example                                                     */
#ifndef __RCM_H
#define __RCM_H 

#if (defined (MCU_MKL46Z256))
// just for compability KL46 with KL43 headers
#define RCM_FM_FORCEROM(x)      x
#endif

/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct  { uint8 RPFC, RPFW, FM; } tRCM;

/******************************************************************************
* Reset sources definition returned by RCM_GetResetType() macro
*
*//*! @addtogroup rst_sources
* @{
*******************************************************************************/    
typedef enum    {                                                              
                  WAKEUP=(1<<0),        ///< Reset by wakeup source            
                  LVD=(1<<1),           ///< Reset by LVD trip
                  LOC=(1<<2),           ///< Reset by a loss of external clock
                  LOL=(1<<3),           ///< Reset by a loss of lock in the PLL
                  COP=(1<<5),           ///< Reset by watchdog timeout  
                  PIN=(1<<6),           ///< Reset by external reset pin
                  POR=(1<<7),           ///< Reset by power on/off
                  LOCKUP=(1<<9),        ///< Reset by core LOCKUP event
                  SW=(1<<10),           ///< Reset by setting of SYSRESETREQ bit               
                  MDM_AP=(1<<11),       ///< Reset by debugger system
                  SACKERR=(1<<13),      ///< Reset by stop mode ack error
                  PORLVD = 0x82,        ///< Reset by LVD trip and POR
                  WAKEUP_PIN = 0x41     ///< Reset by wakeup source and ext. pin
                } eRESET_TYPE;
/*! @} End of rst_sources                                                     */


/******************************************************************************
* Boot ROM sources definition.
*
*//*! @addtogroup rst_bootsource
* @{
*******************************************************************************/    
typedef enum    {                                                              
                  BOOTFLASH=0,          ///< boot from flash            
                  BOOTROM_PIN=1,        ///< boot form rom due to BOOTCFG0 pin assertion
                  BOOTROM_FOPT=2,       ///< boot from rom due to FOTP[7] configuration
                  BOOTROM_PIN_FOPT=3,   ///< boot from rom due to both pin and FOPT
                } eBOOT_TYPE;
/*! @} End of rst_bootsource                                                  */

/******************************************************************************
* RCM default configurations used by RCM_init() function
*
*//*! @addtogroup rcm_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief RCM module default config.
 *****************************************************************************/
#define RCM_DEFAULT_CONFIG                                                      \
(tRCM){                                                                         \
/* RPFC */ CLR(RCM_RPFC_RSTFLTSS_MASK)|SET(RCM_RPFC_RSTFLTSRW(0x0)),            \
/* RPFW */ SET(RCM_RPFW_RSTFLTSEL(0x0)),                                        \
/* FM   */ SET(RCM_FM_FORCEROM(0x0)),                                           \
}

/**************************************************************************/ /*!
 * @brief RCM module with reset pin filter in stop modes config.
 *****************************************************************************/
#define RCM_RSTPIN_STOP_CONFIG                                                  \
(tRCM){                                                                         \
/* RPFC */ SET(RCM_RPFC_RSTFLTSS_MASK)|SET(RCM_RPFC_RSTFLTSRW(0x0)),            \
/* RPFW */ SET(RCM_RPFW_RSTFLTSEL(0x0)),                                        \
/* FM   */ SET(RCM_FM_FORCEROM(0x0)),                                           \
}

/**************************************************************************/ /*!
 * @brief RCM module with reset pin filter (bus clock) in run/wait modes config.
 * @param count - 1 - 32 bus clock filter counts.
 *****************************************************************************/
#define RCM_RSTPIN_RUNWAIT_BUSCLK_CONFIG(count)                                 \
(tRCM){                                                                         \
/* RPFC */ CLR(RCM_RPFC_RSTFLTSS_MASK)|SET(RCM_RPFC_RSTFLTSRW(0x1)),            \
/* RPFW */ SET(RCM_RPFW_RSTFLTSEL(count)),                                      \
/* FM   */ SET(RCM_FM_FORCEROM(0x0)),                                           \
}

/**************************************************************************/ /*!
 * @brief RCM module with reset pin filter (LPO clock) in run/wait modes config.
 *****************************************************************************/
#define RCM_RSTPIN_RUNWAIT_LPOCLK_CONFIG                                        \
(tRCM){                                                                         \
/* RPFC */ CLR(RCM_RPFC_RSTFLTSS_MASK)|SET(RCM_RPFC_RSTFLTSRW(0x2)),            \
/* RPFW */ SET(RCM_RPFW_RSTFLTSEL(0x0)),                                        \
/* FM   */ SET(RCM_FM_FORCEROM(0x0)),                                           \
}

/**************************************************************************/ /*!
 * @brief RCM module with boot from FLASH.
 *****************************************************************************/
#define RCM_FLASHBOOT_CONFIG                                                    \
(tRCM){                                                                         \
/* RPFC */ CLR(RCM_RPFC_RSTFLTSS_MASK)|SET(RCM_RPFC_RSTFLTSRW(0x0)),            \
/* RPFW */ SET(RCM_RPFW_RSTFLTSEL(0x0)),                                        \
/* FM   */ SET(RCM_FM_FORCEROM(0x0)),                                           \
}

/**************************************************************************/ /*!
 * @brief RCM module with boot from ROM with BOOTCFG0 pin assertion.
 *****************************************************************************/
#define RCM_ROMBOOT_PIN_CONFIG                                                  \
(tRCM){                                                                         \
/* RPFC */ CLR(RCM_RPFC_RSTFLTSS_MASK)|SET(RCM_RPFC_RSTFLTSRW(0x0)),            \
/* RPFW */ SET(RCM_RPFW_RSTFLTSEL(0x0)),                                        \
/* FM   */ SET(RCM_FM_FORCEROM(0x1)),                                           \
}

/**************************************************************************/ /*!
 * @brief RCM module with boot from ROM with FOPT configuration.
 *****************************************************************************/
#define RCM_ROMBOOT_FOPT_CONFIG                                                 \
(tRCM){                                                                         \
/* RPFC */ CLR(RCM_RPFC_RSTFLTSS_MASK)|SET(RCM_RPFC_RSTFLTSRW(0x0)),            \
/* RPFW */ SET(RCM_RPFW_RSTFLTSEL(0x0)),                                        \
/* FM   */ SET(RCM_FM_FORCEROM(0x2)),                                           \
}

/**************************************************************************/ /*!
 * @brief RCM module with boot from ROM with both BOOTCFG0 and FORT.
 *****************************************************************************/
#define RCM_ROMBOOT_PIN_FOPT_CONFIG                                             \
(tRCM){                                                                         \
/* RPFC */ CLR(RCM_RPFC_RSTFLTSS_MASK)|SET(RCM_RPFC_RSTFLTSRW(0x0)),            \
/* RPFW */ SET(RCM_RPFW_RSTFLTSEL(0x0)),                                        \
/* FM   */ SET(RCM_FM_FORCEROM(0x3)),                                           \
}

/*! @} End of rcm_config                                                      */

/******************************************************************************
* RCM function and macro definitions
*
*//*! @addtogroup rcm_macro
* @{
*******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
/***************************************************************************//*!
 * @brief   Macro returns last reset source type.
 * @return  reset type  - @ref rst_sources
 * @note    Implemented as function call.
 ******************************************************************************/ 
#define RCM_GetResetType()   (eRESET_TYPE)(((uint16)RCM_SRS1<<8)|(uint16)RCM_SRS0)
// just for backward capability
#define SMC_GetResetType()   RCM_GetResetType()

#if (defined (MCU_MKL43Z256))
/***************************************************************************//*!
 * @brief   Macro returns reset source type caused after last POR, LVD, or VLLS 
 *          wakeup.
 * @return  reset type  - @ref rst_sources
 * @note    Implemented as function call.
 ******************************************************************************/ 
#define RCM_GetStickyResetType()  (eRESET_TYPE)(((uint16)RCM_SSRS1<<8)|(uint16)RCM_SSRS0)

/***************************************************************************//*!
 * @brief   Macro force the boot ROM source.
 * @param   bootsrc - @ref rst_bootsource
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define RCM_ForceBoot(bootsrc)    REG_SetVal(RCM_FM,RCM_FM_FORCEROM,bootsrc);

/***************************************************************************//*!
 * @brief   Macro read boot ROM option.
 * @param   bootsrc - @ref rst_bootsource
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define RCM_ReadBootSrc(bootsrc)    (eBOOT_TYPE)(RCM_MR>>1)

/***************************************************************************//*!
 * @brief   Macro clears flag of boot ROM option.
 * @param   bootsrc - @ref rst_bootsource
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define RCM_ClrBootFlag(bootsrc)  REG_SetVal(RCM_MR,RCM_MR_BOOTROM,bootsrc)

#endif

/***************************************************************************//*!
 * @brief   RCM initialization function.
 * @details This function initalizes System Mode Controller (SMC).
 * @param   cfg       Use one of following configuration structures @ref 
 *                    smc_config
 * @note    Implemented as function call.
 ******************************************************************************/ 
#define RCM_Init(cfg)     RCM_Init(cfg)
/*! @} End of rcm_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/    
extern void RCM_Init (tRCM rcm);

#endif /* __RCM_H */ 
