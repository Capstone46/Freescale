/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      pmc.h
 * @version   1.0.3.0
 * @date      Jan-18-2013
 * @brief     PMC driver header file.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	01/08/2012   R55013   Ported to Kinetis M  
 *  3.	15/01/2013   B34185   Re-written to Kinetis L
******************************************************************************/
/******************************************************************************
 *//*! @addtogroup pmc_example
 * @{
 * @par       Source code:
 * @include   pmc0_test\pmc0_test.c
 * @par       Appconfig.h:
 * @include   pmc0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of pmc_example                                                     */
#ifndef __PMC_H
#define __PMC_H 
 
/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct { uint8 LVDSC1, LVDSC2, REGSC; } tPMC;

/******************************************************************************
* PMC default configurations used by PMC_init() function
*
*//*! @addtogroup pmc_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
  * @brief PMC default configuration.
  *****************************************************************************/
#define PMC_MODULE_CONFIG1    /* default setting after reset  */              \
(tPMC){                                                                       \
/* LVDSC1 */  CLR(PMC_LVDSC1_LVDACK_MASK)|CLR(PMC_LVDSC1_LVDIE_MASK)|         \
              SET(PMC_LVDSC1_LVDRE_MASK)|SET(PMC_LVDSC1_LVDV(0)),             \
/* LVDSC2 */  CLR(PMC_LVDSC2_LVWACK_MASK)|CLR(PMC_LVDSC2_LVWIE_MASK)|         \
              SET(PMC_LVDSC2_LVWV(0)),                                        \
/* REGSC  */  CLR(PMC_REGSC_BGEN_MASK)|CLR(PMC_REGSC_ACKISO_MASK)|            \
              CLR(PMC_REGSC_BGBE_MASK)                                        \
}

/**************************************************************************/ /*!
  * @brief PMC default configuration (the same as PMC_MODULE_CONFIG1).
  *****************************************************************************/
#define PMC_MODULE_CONFIG       PMC_MODULE_CONFIG1

/**************************************************************************/ /*!
  * @brief PMC with bandgep buffer enabled.
  *****************************************************************************/
#define PMC_MODULE_BANDGAP_CONFIG /* Banggap buffer enabled  */               \
(tPMC){                                                                       \
/* LVDSC1 */  CLR(PMC_LVDSC1_LVDACK_MASK)|CLR(PMC_LVDSC1_LVDIE_MASK)|         \
              SET(PMC_LVDSC1_LVDRE_MASK)|SET(PMC_LVDSC1_LVDV(0)),             \
/* LVDSC2 */  CLR(PMC_LVDSC2_LVWACK_MASK)|CLR(PMC_LVDSC2_LVWIE_MASK)|         \
              SET(PMC_LVDSC2_LVWV(0)),                                        \
/* REGSC  */  CLR(PMC_REGSC_BGEN_MASK)|CLR(PMC_REGSC_ACKISO_MASK)|            \
              SET(PMC_REGSC_BGBE_MASK)                                        \
}

/***************************************************************************//*!
 * @brief   Power management integration module configuration for low power.
 ******************************************************************************/
#define PMC_MODULE_LOW_POWER_CONFIG  /* low power config  */                  \
(tPMC){                                                                       \
/* LVDSC1 */  CLR(PMC_LVDSC1_LVDACK_MASK)|CLR(PMC_LVDSC1_LVDIE_MASK)|         \
              CLR(PMC_LVDSC1_LVDRE_MASK)|SET(PMC_LVDSC1_LVDV(0)),             \
/* LVDSC2 */  CLR(PMC_LVDSC2_LVWACK_MASK)|CLR(PMC_LVDSC2_LVWIE_MASK)|         \
              SET(PMC_LVDSC2_LVWV(0)),                                        \
/* REGSC  */  CLR(PMC_REGSC_BGEN_MASK)|CLR(PMC_REGSC_ACKISO_MASK)|            \
              CLR(PMC_REGSC_BGBE_MASK)                                        \
}
/*! @} End of pmc_config                                                      */

/******************************************************************************
* PMC callback used in PMC_Init function
*
*//*! @addtogroup pmc_callback
* @{
*******************************************************************************/
/*! @brief PMC_CALLBACK type declaration                                      */
typedef enum {LVD_CALLBACK=1, LVW_CALLBACK=2} PMC_CALLBACK_TYPE;
/*! PMC_CALLBACK function declaration                                         */
typedef void (*PMC_CALLBACK)(PMC_CALLBACK_TYPE eType);
/*! @} End of pmc_callback                                                    */

/******************************************************************************
* PMC function and macro definitions
*
*//*! @addtogroup pmc_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro returns LVDF status.
 * @return  TRUE  - Internal supply voltage falls below the selected internal 
 *                  monitor trip point (VLVD).
 * @return  FALSE - Normal operation.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define PMC_GetLVDF()       (PMC_LVDSC1 & PMC_LVDSC1_LVDF_MASK )

/***************************************************************************//*!
 * @brief   Macro returns LVWF status.
 * @return  TRUE  - Internal supply voltage falls below the selected internal 
 *                  monitor trip point (VLVW).
 * @return  FALSE - Normal operation.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define PMC_GetLVWF()       (PMC_LVDSC2 & PMC_LVDSC2_LVWF_MASK )

/***************************************************************************//*!
 * @brief   Macro returns regulator status.
 * @return  TRUE  - Regulator is in stop regulation or in transition to/from it.
 * @return  FALSE - Regulator is in run regulation.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define PMC_GetREGONS()     (PMC_REGSC  & PMC_REGSC_REGONS_MASK)

/***************************************************************************//*!
 * @brief   Macro releases held state (the I/O states are held on a wakeup event 
 *          until the wakeup has been acknowledged via a write to ACKISO bit).
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define PMC_SetACKISO()       { PMC_REGSC |= PMC_REGSC_ACKISO_MASK; }

/***************************************************************************//*!
 * @brief   Macro returns state indicating whether certain peripherals and the 
 *          I/O pads are in a latched state as a result of having been in a 
 *          VLLS mode. Writing one to this bit when it is set releases the 
 *          I/O pads and certain peripherals to their normal run mode state -
 *          see PMC_SetACKISO().
 * @return  TRUE    - Certain peripherals and I/O pads are in an isolated 
 *                    and latched state
 * @return  FALSE   - Peripherals and I/O pads are in normal run state
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define PMC_GetACKISO()      (PMC_REGSC & PMC_REGSC_ACKISO_MASK)
/*! @} End of pmc_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/    
extern void PMC_Init (tPMC pmc, uint8 ip, PMC_CALLBACK pCallback);

#endif /* __PMC_H */ 
