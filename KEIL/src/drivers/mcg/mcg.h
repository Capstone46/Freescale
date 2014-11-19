/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      mcg.h
 * @version   1.0.2.0
 * @date      Oct-17-2013
 * @brief     Multipurpose clock generator (MCG) driver header file.
 *
 * Revision History:
 *  1.	15/05/2013   B34185   Initially written for Kinetis K
 *  2.	26/11/2013   B34185   Re-writen for Kinetis L
 *  3.	18/03/2014   B34185   Updated by external clock macros
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup fll_example0
 * @{
 * @par       Source code:
 * @include   fll_test\fll_test.c
 * @par       Appconfig.h:
 * @include   fll_test\appconfig.h  
 ******************************************************************************/
/*! @} End of fll_example0                                                    */
#ifndef __MCG_H
#define __MCG_H 
 
#if (defined (MCU_MKL46Z256))
/******************************************************************************
 * macro definitions                                                          *
 ******************************************************************************/
#define WAIT_FOR_STATUS_FLAG(reg,name1,name2)                                 \
{                                                                             \
  while (((MCG_S&MCG_S_##name2##_MASK)>>MCG_S_##name2##_SHIFT)!=              \
    ((reg&##reg##_##name1##_MASK)>>##reg##_##name1##_SHIFT));                 \
}

// remove when defined in device header file    
/* C7 Bit Fields */
#define MCG_C7_OSCSEL_MASK                        0x1u
#define MCG_C7_OSCSEL_SHIFT                       0   
#endif   
   
/******************************************************************************
 * definition configuration structure                                         *
 ******************************************************************************/
typedef struct { uint8 C1, C2, C4, C5, C6, SC, C7, C8; } tMCG;

/******************************************************************************
* Fast IRC clock divider macro definition.
*
*//*! @addtogroup fllirc_div_list
* @{
*******************************************************************************/
#define FIRC_DIV_1      (uint8)0x00   ///< Divide factor is 1
#define FIRC_DIV_2      (uint8)0x01   ///< Divide factor is 2
#define FIRC_DIV_4      (uint8)0x02   ///< Divide factor is 4
#define FIRC_DIV_8      (uint8)0x03   ///< Divide factor is 8
#define FIRC_DIV_16     (uint8)0x04   ///< Divide factor is 16
#define FIRC_DIV_32     (uint8)0x05   ///< Divide factor is 32
#define FIRC_DIV_64     (uint8)0x06   ///< Divide factor is 64
#define FIRC_DIV_128    (uint8)0x07   ///< Divide factor is 128
/*! @} End of fllirc_div_list                                                 */

/******************************************************************************
* IRC clock selection macro definition.
*
*//*! @addtogroup fllirc_clk_list
* @{
*******************************************************************************/
/* Macros for internal clock selection                                        */
#define SLOW_IRC       (uint8)0x00      ///< slow clock (32 kHz IRC)
#define FAST_IRC       (uint8)0x01      ///< fast clock (4MHz IRC)
/*! @} End of fllirc_clk_list                                                 */

/******************************************************************************
* External crystal frequency range selection.
*
*//*! @addtogroup range_list
* @{
*******************************************************************************/
#define LOW_FREQ_RANGE       (uint8)0x00      ///< (32k-40)kHZ range 
#define HIGH_FREQ_RANGE      (uint8)0x01      ///< (2M-8)MHZ range 
#define VERY_HIGH_FREQ_RANGE (uint8)0x02      ///< (8-32)MHZ range 
/*! @} End of range_list                                                      */

/******************************************************************************
* Crystal oscilator operation mode selection.
*
*//*! @addtogroup hgo_list
* @{
*******************************************************************************/
#define LOW_POWER_OSC       (uint8)0x00      ///< low power crystal oscilator mode
#define HIGH_GAIN_OSC      	(uint8)0x01      ///< high gain crystal oscilator mode
/*! @} End of hgo_list                                                      */

/******************************************************************************
* External clock source type.
*
*//*! @addtogroup extclksel_list
* @{
*******************************************************************************/
#define EXT_REQST      			(uint8)0x00      	///< low power crystal oscilator mode
#define OSC_REQST      			(uint8)0x01      	///< high gain crystal oscilator mode
/*! @} End of extclksel_list                                                  */

/******************************************************************************
* PLL external reference divider macro definition.
*
*//*! @addtogroup pll_pr_div_list
* @{
*******************************************************************************/
#define PR_DIV_1      (uint8)0x00   ///< Divide factor is 1
#define PR_DIV_2      (uint8)0x01   ///< Divide factor is 2
#define PR_DIV_3      (uint8)0x02   ///< Divide factor is 3
#define PR_DIV_4      (uint8)0x03   ///< Divide factor is 4
#define PR_DIV_5      (uint8)0x04   ///< Divide factor is 5
#define PR_DIV_6      (uint8)0x05   ///< Divide factor is 6
#define PR_DIV_7      (uint8)0x06   ///< Divide factor is 7
#define PR_DIV_8      (uint8)0x07   ///< Divide factor is 8
#define PR_DIV_9      (uint8)0x08   ///< Divide factor is 9
#define PR_DIV_10     (uint8)0x09   ///< Divide factor is 10
#define PR_DIV_11     (uint8)0x0A   ///< Divide factor is 11
#define PR_DIV_12     (uint8)0x0B   ///< Divide factor is 12
#define PR_DIV_13     (uint8)0x0C   ///< Divide factor is 13
#define PR_DIV_14     (uint8)0x0D   ///< Divide factor is 14
#define PR_DIV_15     (uint8)0x0E   ///< Divide factor is 15
#define PR_DIV_16     (uint8)0x0F   ///< Divide factor is 16
#define PR_DIV_17     (uint8)0x10   ///< Divide factor is 17
#define PR_DIV_18     (uint8)0x11   ///< Divide factor is 18
#define PR_DIV_19     (uint8)0x12   ///< Divide factor is 19
#define PR_DIV_20     (uint8)0x13   ///< Divide factor is 20
#define PR_DIV_21     (uint8)0x14   ///< Divide factor is 21
#define PR_DIV_22     (uint8)0x15   ///< Divide factor is 22
#define PR_DIV_23     (uint8)0x16   ///< Divide factor is 23
#define PR_DIV_24     (uint8)0x17   ///< Divide factor is 24
#define PR_DIV_25     (uint8)0x18   ///< Divide factor is 25
/*! @} End of pll_pr_div_list                                                 */

/******************************************************************************
* PLL voltage controller oscilator VCO divider macro definition.
*
*//*! @addtogroup pll_vco_div_list
* @{
*******************************************************************************/
#define VCO_DIV_24      (uint8)0x00   ///< Divide/multiply factor is 24
#define VCO_DIV_25      (uint8)0x01   ///< Divide/multiply factor is 25
#define VCO_DIV_26      (uint8)0x02   ///< Divide/multiply factor is 26
#define VCO_DIV_27      (uint8)0x03   ///< Divide/multiply factor is 27
#define VCO_DIV_28      (uint8)0x04   ///< Divide/multiply factor is 28
#define VCO_DIV_29      (uint8)0x05   ///< Divide/multiply factor is 29
#define VCO_DIV_30      (uint8)0x06   ///< Divide/multiply factor is 30
#define VCO_DIV_31      (uint8)0x07   ///< Divide/multiply factor is 31
#define VCO_DIV_32      (uint8)0x08   ///< Divide/multiply factor is 32
#define VCO_DIV_33      (uint8)0x09   ///< Divide/multiply factor is 33
#define VCO_DIV_34      (uint8)0x0A   ///< Divide/multiply factor is 34
#define VCO_DIV_35      (uint8)0x0B   ///< Divide/multiply factor is 35
#define VCO_DIV_36      (uint8)0x0C   ///< Divide/multiply factor is 36
#define VCO_DIV_37      (uint8)0x0D   ///< Divide/multiply factor is 37
#define VCO_DIV_38      (uint8)0x0E   ///< Divide/multiply factor is 38
#define VCO_DIV_39      (uint8)0x0F   ///< Divide/multiply factor is 39
#define VCO_DIV_40      (uint8)0x10   ///< Divide/multiply factor is 40
#define VCO_DIV_41      (uint8)0x11   ///< Divide/multiply factor is 41
#define VCO_DIV_42      (uint8)0x12   ///< Divide/multiply factor is 42
#define VCO_DIV_43      (uint8)0x13   ///< Divide/multiply factor is 43
#define VCO_DIV_44      (uint8)0x14   ///< Divide/multiply factor is 44
#define VCO_DIV_45      (uint8)0x15   ///< Divide/multiply factor is 45
#define VCO_DIV_46      (uint8)0x16   ///< Divide/multiply factor is 46
#define VCO_DIV_47      (uint8)0x17   ///< Divide/multiply factor is 47
#define VCO_DIV_48      (uint8)0x18   ///< Divide/multiply factor is 48
#define VCO_DIV_49      (uint8)0x19   ///< Divide/multiply factor is 49
#define VCO_DIV_50      (uint8)0x1A   ///< Divide/multiply factor is 50
#define VCO_DIV_51      (uint8)0x1B   ///< Divide/multiply factor is 51
#define VCO_DIV_52      (uint8)0x1C   ///< Divide/multiply factor is 52
#define VCO_DIV_53      (uint8)0x1D   ///< Divide/multiply factor is 53
#define VCO_DIV_54      (uint8)0x1E   ///< Divide/multiply factor is 54
#define VCO_DIV_55      (uint8)0x1F   ///< Divide/multiply factor is 55
/*! @} End of pll_vco_div_list                                                */  


/******************************************************************************
* FLL configuration used by MCG_Init(FLL,...) or FLL_init() function.
*
*//*! @addtogroup mcg_fllconfig
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   FLL engage internal with DCO range in 20-25MHz (FLL factor 640).
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FEI_20_25MHZ                                         \
(tMCG){                                                                        \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x00))|                      \
         SET(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|\
         CLR(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),    \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FEI_20_25MHZ    FLL_MODULE_CONFIG_FEI_20_25MHZ 

/***************************************************************************//*!
 * @brief   FLL engage internal with DCO range in 24MHz (FLL factor 732).
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FEI_24MHZ                                           \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x00))|                      \
         SET(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|\
         CLR(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),    \
/* C4 */ SET(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FEI_24MHZ       FLL_MODULE_CONFIG_FEI_24MHZ

/***************************************************************************//*!
 * @brief   FLL engage internal with DCO range in 40-50MHz (FLL factor 1280).
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FEI_40_50MHZ                                        \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x00))|                      \
         SET(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|\
         CLR(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),    \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x01))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FEI_40_50MHZ    FLL_MODULE_CONFIG_FEI_40_50MHZ

/***************************************************************************//*!
 * @brief   FLL engage internal with DCO range in 48MHz (FLL factor 1464).
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FEI_48MHZ                                           \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x00))|                      \
         SET(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|\
         CLR(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),    \
/* C4 */ SET(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x01))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FEI_48MHZ       FLL_MODULE_CONFIG_FEI_48MHZ 

/***************************************************************************//*!
 * @brief   FLL engage internal with DCO range in 60-75MHz (FLL factor 1920).
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FEI_60_75MHZ                                        \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x00))|                      \
         SET(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|\
         CLR(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),    \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x02))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FEI_60_75MHZ    FLL_MODULE_CONFIG_FEI_60_75MHZ

/***************************************************************************//*!
 * @brief   FLL engage internal with DCO range in 72MHz (FLL factor 2197).
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FEI_72MHZ                                           \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x00))|                      \
         SET(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|\
         CLR(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),    \
/* C4 */ SET(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x02))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FEI_72MHZ       FLL_MODULE_CONFIG_FEI_72MHZ

/***************************************************************************//*!
 * @brief   FLL engage internal with DCO range in 80-100MHz (FLL factor 2560).
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FEI_80_100MHZ                                       \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x00))|                      \
         SET(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|\
         CLR(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),    \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x03))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FEI_80_100MHZ   FLL_MODULE_CONFIG_FEI_80_100MHZ 

/***************************************************************************//*!
 * @brief   FLL engage internal with DCO range in 96MHz (FLL factor 2929).
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FEI_96MHZ                                           \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x00))|                      \
         SET(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|\
         CLR(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),    \
/* C4 */ SET(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x03))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FEI_96MHZ       FLL_MODULE_CONFIG_FEI_96MHZ 

/***************************************************************************//*!
 * @brief   FLL engage external with DCO range in 20MHz (8MHz osc or higher expected).
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FEE_20MHZ_OSC_8MHZ                                  \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x03))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|SET(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),    \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FEE_20MHZ_OSC_8MHZ      FLL_MODULE_CONFIG_FEE_20MHZ_OSC_8MHZ

/***************************************************************************//*!
 * @brief   FLL engage external with DCO range in 40MHz (8MHz osc or higher expected).
 ******************************************************************************/ 
#define FLL_MODULE_CONFIG_FEE_40MHZ_OSC_8MHZ                                  \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x03))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|SET(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),    \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x01))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FEE_40MHZ_OSC_8MHZ      FLL_MODULE_CONFIG_FEE_40MHZ_OSC_8MHZ 

/***************************************************************************//*!
 * @brief   FLL engage external with DCO range in 60MHz (8MHz osc or higher expected).
 ******************************************************************************/ 
#define FLL_MODULE_CONFIG_FEE_60MHZ_OSC_8MHZ                                  \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x03))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|SET(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),    \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x02))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FEE_60MHZ_OSC_8MHZ      FLL_MODULE_CONFIG_FEE_60MHZ_OSC_8MHZ 

/***************************************************************************//*!
 * @brief   FLL engage external with DCO range in 80MHz (8MHz osc or higher expected).
 ******************************************************************************/ 
#define FLL_MODULE_CONFIG_FEE_80MHZ_OSC_8MHZ                                  \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x03))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|SET(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),    \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x03))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FEE_80MHZ_OSC_8MHZ      FLL_MODULE_CONFIG_FEE_80MHZ_OSC_8MHZ

/***************************************************************************//*!
 * @brief   FLL bypass internal 2MHz.
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FBI_02MHZ                                           \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x01))|SET(MCG_C1_FRDIV(0x00))|                      \
         SET(MCG_C1_IREFS_MASK)|SET(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|\
         CLR(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|SET(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FBI_02MHZ       FLL_MODULE_CONFIG_FBI_02MHZ 

/***************************************************************************//*!
 * @brief   FLL bypass internal 4MHz.
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FBI_04MHZ                                           \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x01))|SET(MCG_C1_FRDIV(0x00))|                      \
         SET(MCG_C1_IREFS_MASK)|SET(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|\
         CLR(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|SET(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x00)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FBI_04MHZ       FLL_MODULE_CONFIG_FBI_04MHZ

/***************************************************************************//*!
 * @brief   FLL bypassed external mode (8MHz osc or higher expected).
 * @warning Please, follow the harware restriction related to RANGE and HGO in 
 *          order to initialyye PLL and external reference properly. Especially 
 *          feedback resitor and crystal frequency range.
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FBE_OSC_8MHZ                                        \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x02))|SET(MCG_C1_FRDIV(0x03))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|CLR(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x00)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FBE_OSC_8MHZ    FLL_MODULE_CONFIG_FBE_OSC_8MHZ

/***************************************************************************//*!
 * @brief   FLL bypassed external mode (8MHz osc or higher expected) with 
 *          clock monitor enabled - loss of external reference clock IRQ enabled.
 * @warning Please, follow the harware restriction related to RANGE and HGO in 
 *          order to initialyye PLL and external reference properly. Especially 
 *          feedback resitor and crystal frequency range.
 ******************************************************************************/
#define FLL_MODULE_CONFIG_FBE_OSC_8MHZ_LOCEN_IRQ                              \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x02))|SET(MCG_C1_FRDIV(0x03))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ CLR(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|CLR(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|SET(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x00)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define FBE_OSC_8MHZ_LOCEN_IRQ  FLL_MODULE_CONFIG_FBE_OSC_8MHZ_LOCEN_IRQ

/***************************************************************************//*!
 * @brief   FLL bypass low power internal 2MHz.
 ******************************************************************************/
#define FLL_MODULE_CONFIG_BLPI_02MHZ                                          \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x01))|SET(MCG_C1_FRDIV(0x00))|                      \
         SET(MCG_C1_IREFS_MASK)|SET(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|\
         CLR(MCG_C2_EREFS0_MASK)|LP(MCG_C2_LP_MASK)|SET(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x07)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x01)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define BLPI_02MHZ      FLL_MODULE_CONFIG_BLPI_02MHZ

/***************************************************************************//*!
 * @brief   FLL bypass low power internal 4MHz.
 ******************************************************************************/
#define FLL_MODULE_CONFIG_BLPI_04MHZ                                          \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x01))|SET(MCG_C1_FRDIV(0x00))|                      \
         SET(MCG_C1_IREFS_MASK)|SET(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|\
         CLR(MCG_C2_EREFS0_MASK)|SET(MCG_C2_LP_MASK)|SET(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x07)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x00)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define BLPI_04MHZ      FLL_MODULE_CONFIG_BLPI_04MHZ

/***************************************************************************//*!
 * @brief   FLL bypassed low power external mode (8MHz osc or higher expected).
 * @warning Please, follow the harware restriction related to RANGE and HGO in 
 *          order to initialyye PLL and external reference properly. Especially 
 *          feedback resitor and crystal frequency range.
 ******************************************************************************/
#define FLL_MODULE_CONFIG_BLPE_OSC_8MHZ                                       \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x02))|SET(MCG_C1_FRDIV(0x03))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|CLR(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|SET(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ CLR(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(0x00)),                                            \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|CLR(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(0x00)),                                             \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x00)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define BLPE_OSC_8MHZ   FLL_MODULE_CONFIG_BLPE_OSC_8MHZ
/*! @} End of mcg_fllconfig                                                   */

/******************************************************************************
* PLL module default configurations used by MCG(PLL, ...) or PLL_Init() function.
*
*//*! @addtogroup mcg_pllconfig
* @{
*******************************************************************************/

/***************************************************************************//*!
 * @brief   PLL engage external with very high frequency range, high gain. 
 *          External divider set to 4 (8MHz/4 = 2MHz) and resulting input
 *          PLL frequency set to 2MHz (considering 8MHz external crystal).
 *          Multiplication factor set to 48 (48*2MHZ = 96MHz).
 * @note    Please, follow the MCG mode moving restrictions provided in RM - 
 *          MCG mode state diagram.
 * @warning Please, follow the hardware restriction related to RANGE and HGO in 
 *          order to initialyze PLL and external reference properly. Especially 
 *          feedback resitor and crystal frequency range.
 ******************************************************************************/
#define PLL_MODULE_CONFIG_PEE_96MHZ_OSC_8MHZ                                  \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x00))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|CLR(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ SET(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(PR_DIV_4)),                                        \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|SET(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(VCO_DIV_48)),                                       \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x00)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define PEE_96MHZ_OSC_8MHZ      PLL_MODULE_CONFIG_PEE_96MHZ_OSC_8MHZ

/***************************************************************************//*!
 * @brief   PLL engage external with very high frequency range, high gain. 
 *          External divider set to 4 (8MHz/4 = 2MHz) and resulting input
 *          PLL frequency set to 2MHz (considering 8MHz external crystal).
 *          Multiplication factor set to 36 (48*2MHZ = 72MHz).
 * @note    Please, follow the MCG mode moving restrictions provided in RM - 
 *          MCG mode state diagram.
 * @warning Please, follow the hardware restriction related to RANGE and HGO in 
 *          order to initialyze PLL and external reference properly. Especially 
 *          feedback resitor and crystal frequency range.
 ******************************************************************************/
#define PLL_MODULE_CONFIG_PEE_72MHZ_OSC_8MHZ                                  \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x00))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|CLR(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ SET(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(PR_DIV_4)),                                        \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|SET(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(VCO_DIV_36)),                                       \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x00)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define PEE_72MHZ_OSC_8MHZ      PLL_MODULE_CONFIG_PEE_72MHZ_OSC_8MHZ

/***************************************************************************//*!
 * @brief   PLL engage external with very high frequency range, high gain. 
 *          External divider set to 4 (8MHz/4 = 2MHz) and resulting input
 *          PLL frequency set to 2MHz (considering 8MHz external crystal).
 *          Multiplication factor set to 24 (24*2MHZ = 48MHz).
 * @note    Please, follow the MCG mode moving restrictions provided in RM - 
 *          MCG mode state diagram.
 * @warning Please, follow the hardware restriction related to RANGE and HGO in 
 *          order to initialyze PLL and external reference properly. Especially 
 *          feedback resitor and crystal frequency range.
 ******************************************************************************/
#define PLL_MODULE_CONFIG_PEE_48MHZ_OSC_8MHZ                                  \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x00))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|CLR(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ SET(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(PR_DIV_4)),                                        \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|SET(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(VCO_DIV_24)),                                       \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x00)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define PEE_48MHZ_OSC_8MHZ      PLL_MODULE_CONFIG_PEE_48MHZ_OSC_8MHZ  

/***************************************************************************//*!
 * @brief   PLL engage external with very high frequency range, high gain. 
 *          External divider set to 4 (8MHz/4 = 2MHz) and resulting input
 *          PLL frequency set to 2MHz (considering 8MHz external crystal).
 *          Multiplication factor set to 24 (24*2MHZ = 48MHz). Loss of clock
 *          and loss of lock interrupt enabled.
 * @note    Please, follow the MCG mode moving restrictions provided in RM - 
 *          MCG mode state diagram.
 * @note    Please, instal interrupt using MCG_InstallCallback function prior to
 *          PLL_Init with this macro initialization.
 * @warning Please, follow the harware restriction related to RANGE and HGO in 
 *          order to initialyye PLL and external reference properly. Especially 
 *          feedback resitor and crystal frequency range.
 ******************************************************************************/
#define PLL_MODULE_CONFIG_PEE_48MHZ_OSC_8MHZ_LOCEN_LOLEN_IRQ                  \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x00))|SET(MCG_C1_FRDIV(0x00))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ CLR(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|CLR(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ SET(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(PR_DIV_4)),                                        \
/* C6 */ SET(MCG_C6_LOLIE0_MASK)|SET(MCG_C6_PLLS_MASK)|SET(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(VCO_DIV_24)),                                       \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x00)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define PEE_48MHZ_OSC_8MHZ_LOCEN_LOLEN_IRQ                                     \
        PLL_MODULE_CONFIG_PEE_48MHZ_OSC_8MHZ_LOCEN_LOLEN_IRQ
          

/***************************************************************************//*!
 * @brief   PLL bypass external. PLL with very high frequency range, high gain. 
 *          External divider set to 4 (8MHz/4 = 2MHz) and resulting input
 *          PLL frequency set to 2MHz (considering 8MHz external crystal).
 *          Multiplication factor set to 48 (48*2MHZ = 96MHz). MCGOUTCLK is 
 *          derived from externall clock, it means 8MHz in this case.
 * @note    Please, follow the MCG mode moving restrictions provided in RM - 
 *          MCG mode state diagram.
 * @warning Please, follow the harware restriction related to RANGE and HGO in 
 *          order to initialyye PLL and external reference properly. Especially 
 *          feedback resitor and crystal frequency range.
 ******************************************************************************/                                            
#define PLL_MODULE_CONFIG_PBE_96MHZ_OSC_8MHZ                                  \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x02))|SET(MCG_C1_FRDIV(0x00))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|CLR(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ SET(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(PR_DIV_4)),                                        \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|SET(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(VCO_DIV_48)),                                       \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x00)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define PBE_96MHZ_OSC_8MHZ      PLL_MODULE_CONFIG_PBE_96MHZ_OSC_8MHZ 

/***************************************************************************//*!
 * @brief   PLL bypass external. PLL with very high frequency range, high gain. 
 *          External divider set to 4 (8MHz/4 = 2MHz) and resulting input
 *          PLL frequency set to 2MHz (considering 8MHz external crystal).
 *          Multiplication factor set to 24 (24*2MHZ = 48MHz). MCGOUTCLK is 
 *          derived from externall clock, it means 8MHz in this case.
 * @note    Please, follow the MCG mode moving restrictions provided in RM - 
 *          MCG mode state diagram.
 * @warning Please, follow the harware restriction related to RANGE and HGO in 
 *          order to initialyye PLL and external reference properly. Especially 
 *          feedback resitor and crystal frequency range.
 ******************************************************************************/                                            
#define PLL_MODULE_CONFIG_PBE_48MHZ_OSC_8MHZ                                  \
(tMCG){                                                                       \
/* C1 */ SET(MCG_C1_CLKS(0x02))|SET(MCG_C1_FRDIV(0x00))|                      \
         CLR(MCG_C1_IREFS_MASK)|CLR(MCG_C1_IRCLKEN_MASK)|                     \
         CLR(MCG_C1_IREFSTEN_MASK),                                           \
/* C2 */ SET(MCG_C2_LOCRE0_MASK)|SET(MCG_C2_RANGE0(0x02))|CLR(MCG_C2_HGO0_MASK)|\
         SET(MCG_C2_EREFS0_MASK)|CLR(MCG_C2_LP_MASK)|CLR(MCG_C2_IRCS_MASK),   \
/* C4 */ CLR(MCG_C4_DMX32_MASK)|SET(MCG_C4_DRST_DRS(0x00))|                   \
         SET(MCG_C4_FCTRIM(0x08)),                                            \
/* C5 */ SET(MCG_C5_PLLCLKEN0_MASK)|CLR(MCG_C5_PLLSTEN0_MASK)|                \
         SET(MCG_C5_PRDIV0(PR_DIV_4)),                                        \
/* C6 */ CLR(MCG_C6_LOLIE0_MASK)|SET(MCG_C6_PLLS_MASK)|CLR(MCG_C6_CME0_MASK)| \
         SET(MCG_C6_VDIV0(VCO_DIV_24)),                                       \
/* SC */ CLR(MCG_SC_ATME_MASK)|CLR(MCG_SC_ATMS_MASK)|                         \
         CLR(MCG_SC_FLTPRSRV_MASK)|SET(MCG_SC_FCRDIV(0x00)),                  \
/* C7 */ CLR(MCG_C7_OSCSEL_MASK),                                             \
/* C8 */ CLR(MCG_C8_LOLRE_MASK),                                              \
}
#define PBE_48MHZ_OSC_8MHZ      PLL_MODULE_CONFIG_PBE_48MHZ_OSC_8MHZ
 
/*! @} End of mcg_pllconfig                                                   */

/******************************************************************************
* MCG function and macro definitions
*
*//*! @addtogroup mcg_macro
* @{
*******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
#endif
/***************************************************************************//*!
 * @brief   Macro set high gain of crystal oscilator. 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_SetHighGainOsc()            { MCG_C2 |= MCG_C2_HGO0_MASK; }

/***************************************************************************//*!
 * @brief   Macro set low power of crystal oscilator. 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_SetLowPowerOsc()            { MCG_C2 &= ~MCG_C2_HGO0_MASK; }

/***************************************************************************//*!
 * @brief   Macro sets slow clock trim value (SCTRIM and SCFTRIM bits).
 *          Increasing the trim value increases the period, and decreasing 
 *          the value decreases the period. Upon reset this value is loaded with
 *          a factory trim value. 
 * @param   x - 9-bit trim value in range <0,511> 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_SetSlowClockTrimVal(x)                                            \
{                                                                             \
  MCG_C3 = (0xff & (x>>1));                                                   \
  REG_SetVal(MCG_C4,MCG_C4_SCFTRIM,(x&0x01));                                 \
}

/***************************************************************************//*!
 * @brief   Macro reads slow clock trim values (SCTRIM and SCFTRIM bits). 
 * @return  9-bit trim value in range <0,511>
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_GetSlowClockTrimVal()   ((((uint16)MCG_C3)<<1)|(uint16)(MCG_C4&0x01))

/***************************************************************************//*!
 * @brief   Macro sets fast clock trim value (FCTRIM bits). Increasing the trim
 *          value increases the period, and decreasing the value decreases 
 *          the period. Upon reset this value is loaded with a factory trim value. 
 * @param   x - 4-bit trim value in range <0,15> 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_SetFastClockTrimVal(x)                                            \
{                                                                             \
  REG_SetVal(MCG_C4,MCG_C4_FCTRIM,(x&0x0f));                                  \
}

/***************************************************************************//*!
 * @brief   Macro reads fast clock trim values (FCTRIM bits). 
 * @return  4-bit trim value in range <0,15>
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_GetFastClockTrimVal() ((MCG_C4&MCG_C4_FCTRIM_MASK)>>MCG_C4_FCTRIM_SHIFT)

/***************************************************************************//*!
 * @brief   Macro enables/disables internal reference clock for use as MCGIRCLK. 
 * @param   x - 1 (MCGIRCLK active) 
 * @param   x - 0 (MCGIRCLK inactive)
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_CtrlIRCLKEN(x)                                                    \
{                                                                             \
  REG_SetVal(MCG_C1,MCG_C1_IRCLKEN,(x&0x01));                                 \
}

/***************************************************************************//*!
 * @brief   Macro controls whether or not the internal reference clock remains 
 *          enabled when the MCG enters Stop mode. 
 * @param   x - 1 (Internal reference clock is enabled in Stop mode if IRCLKEN 
 *                 is set or if MCG is in FEI, FBI, or BLPI modes before entering 
 *                 Stop mode.) 
 * @param   x - 0 (Internal reference clock is disabled in Stop mode)
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_CtrlIREFSTEN(x)                                                   \
{                                                                             \
  REG_SetVal(MCG_C1,MCG_C1_IREFSTEN,(x&0x01));                                \
}

/***************************************************************************//*!
 * @brief   Macro controls whether the FLL (or PLL) is disabled in BLPI and 
 *          BLPE modes. In FBE or PBE modes, calling setting LP bit to 1 will 
 *          transition the MCG into BLPE mode; in FBI mode, setting this bit 
 *          to 1 will transition the MCG into BLPI mode. In any other MCG mode, 
 *          LP bit has no affect.
 * @param   x - 1 (FLL or PLL is disabled in bypass modes) 
 * @param   x - 0 (FLL or PLL is not disabled in bypass modes)
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_CtrlLP(x)                                                         \
{                                                                             \
  REG_SetVal(MCG_C2,MCG_C2_LP,(x&0x01));                                      \
}

/***************************************************************************//*!
 * @brief   Macro select between external clock and oscilator clock. 
 * @param   x - @ref erefsel_list 
 * @return  none
 * @note    Implemented as inlined macro.
 * @warning When enabling the crystal oscilater by this macro the specificied
 *          order for writting to MCG_C2 must be considered:
 *         -> EREFFS0 -> HGO0 -> RANGE0
 ******************************************************************************/
#define MCG_ExtClkType(x)               REG_SetVal(MCG_C2,MCG_C2_EREFS0,x)

/***************************************************************************//*!
 * @brief   Macro sets crystal oscilator operation mode. 
 * @param   x - @ref hgo_list 
 * @return  none
 * @note    Implemented as inlined macro.
 * @warning When enabling the crystal oscilater by this macro the specificied
 *          order for writting to MCG_C2 must be considered:
 *         -> EREFFS0 -> HGO0 -> RANGE0
 ******************************************************************************/
#define MCG_CrystalMode(x)              REG_SetVal(MCG_C2,MCG_C2_HGO0,x)

/***************************************************************************//*!
 * @brief   Macro sets the frequency range for external crystal. 
 * @param   x - @ref range_list 
 * @return  none
 * @note    Implemented as inlined macro.
 * @warning When enabling the crystal oscilater by this macro the specificied
 *          order for writting to MCG_C2 must be considered:
 *         -> EREFFS0 -> HGO0 -> RANGE0
 ******************************************************************************/
#define MCG_CrystalFreqRangeSel(x)      REG_SetVal(MCG_C2,MCG_C2_RANGE0,x)

/***************************************************************************//*!
 * @brief   Macro waits for oscilator initialization. 
 * @param   x - @ref erefsel_list 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_WaitOscInit()       WAIT_FOR_STATUS_FLAG (MCG_C2, EREFS0, OSCINIT0);

/***************************************************************************//*!
 * @brief   Macro initialize external clock (when separatelly used e.g. as OSCERCLK or MCGPLLCLK).
 * @param   range - @ref range_list
 * @param   gain - @ref hgo_list
 * @param   src - @ref erefsel_list
 * @return  none
 * @note    Implemented as inlined macro.
 * @note    If used for MCGPLLCLK output then PLL_Enable() should be called after.
 ******************************************************************************/
#define MCG_ExtClkInit(range,gain,src)                                          \
{                                                                               \
  MCG_ExtClkType(src);                                                          \
  MCG_CrystalMode(gain);                                                        \
  MCG_CrystalFreqRangeSel(range);                                               \
  if (MCG_C2 & MCG_C2_EREFS0_MASK)                                              \
  {                                                                             \
    MCG_WaitOscInit();                                                          \
  }                                                                             \
}

/***************************************************************************//*!
 * @brief   Macro controls external clock monitor. Determines if a reset 
 *          request is made following a loss of external clock indication. 
 *          The CME bit should only be set to a logic 1 when either the MCG is 
 *          in an operational mode that uses the external clock (FEE, FBE, PEE, 
 *          PBE, or BLPE) or the external reference is enabled. Whenever the 
 *          CME bit is set to a logic 1, the value of the RANGE bits in the C2 
 *          register should not be changed. CME bit should be set to a logic 0
 *          before the MCG enters Stop mode. 
 *          Otherwise, a reset request may occur while in Stop mode.
 * @param   x - 1 (Generate a reset request on loss of external clock) 
 * @param   x - 0 (External clock monitor is disabled.)
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_CtrlCME(x)                                                        \
{                                                                             \
  REG_SetVal(MCG_C6,MCG_C6_CME0,(x&0x01));                                    \
}

/***************************************************************************//*!
 * @brief   Macro select fast clock internal reference divider. 
 * @param   x -  @ref mcgirc_div_list.
 * @return  none
 * @note    Implemented as inlined macro. Fast clock internal reference divider
 *          must be selected before fast IRC is enabled.
 ******************************************************************************/
#define MCG_SetFastClockDivider(x)                                            \
{                                                                             \
  REG_SetVal(MCG_SC,MCG_SC_FCRDIV,(x&0x7));                                   \
}

/***************************************************************************//*!
 * @brief   Macro selects between fast or slow IRC used at IRCSCLK. 
 * @param   x - @ref mcgirc_clk_list
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_SelectIrcClock(x)                                                 \
{                                                                             \
  REG_SetVal(MCG_C2,MCG_C2_IRCS,(x&0x01));                                    \
  while ((MCG_S & MCG_S_IRCST_MASK) != x);                                    \
}

/***************************************************************************//*!
 * @brief   MCG initialization function.
 * @param   module - FLL|PLL
 * @param   cfg - @ref mcg_config
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define MCG_Init(module,cfg)           module##_Init(cfg)
/*! @} End of MCG_macro                                                       */

/******************************************************************************
* FLL function and macro definitions
*
*//*! @addtogroup pll_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro selects PLL 32Khz reference clock and enables PLL module.
 * @details This macro selects PLL 32Khz reference clock and enables PLL module.
 *          PLL is enabled by setting PLLCLKEN0 bit. 
 * @note    Implemented as inlined macro.
 * @warning FLL or PLL is enabled by this macro (LP bit is deasserted). The 
 *          MCGPLLCLK is prevented from coming out of the MCG until it is
 *          enabled and S[LOCK0] is set. 
 ******************************************************************************/
#define PLL_Enable()                                                          \
{                                                                             \
  REG_SetVal(MCG_C2, MCG_C2_LP, 0);                                           \
  REG_SetVal(MCG_C5, MCG_C5_PLLCLKEN0, 1);                                    \
  while (!(MCG_S & MCG_S_LOCK0_MASK));    /* wait until S[LOCK0] is set */    \
}

/***************************************************************************//*!
 * @brief   Macro disables PLL module.
 * @details This macro disables PLL module by clearing PLLCLKEN0 bit.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define PLL_Disable()   { REG_SetVal(MCG_C5, MCG_C5_PLLCLKEN0, 0);            }

/***************************************************************************//*!
 * @brief   PLL Stop Enable/Disable. 
 * @details This macro enables/disables the PLL Clock during Normal Stop by 
 *          setting/clearing PLLSTEN0 bit, respectively . 
 * @param   x   TRUE  (MCGPLLCLK is enabled if system is in Normal Stop mode)
 * @param   x   FALSE (MCGPLLCLK is disabled in any of the Stop modes)
 * @return  none
 * @note    Implemented as inlined macro.
 * @warning In Low Power Stop mode, the PLL clock gets disabled even if PLL 
 *          operation was enabled using this macro (PLLSTEN0=1). In all other 
 *          power modes PLLSTEN0 bit has no affect and does not enable the PLL Clock
 *          to run if it is written to 1 using this macro.
 ******************************************************************************/
#define PLL_CtrlPLLSTEN(x)     { REG_SetVal(MCG_C5,MCG_C5_PLLSTEN0,(x&0x01)); }
/*! @} End of pll_macro                                                       */

/******************************************************************************
* MCG callback used in MCG_InstallCallback function
*
*//*! @addtogroup mcg_callback
* @{
*******************************************************************************/
/*! @brief MCG_CALLBACK type declaration                                      */
typedef enum {LOC_CALLBACK=1, LOL_CALLBACK=2} MCG_CALLBACK_TYPE;
/*! MCG_CALLBACK function declaration                                         */
typedef void (*MCG_CALLBACK)(MCG_CALLBACK_TYPE eType);
/*! @} End of mcg_callback                                                    */

/******************************************************************************
* MCG interrupt install function definition
*
*//*! @addtogroup mcg_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   MCG interrupt install function.
 * @details This function initalizes MCG interrupt.
 * @param   ip      - interrupt priority 0..15
 * @param   callback- pointer to MCG_CALLBACK function
 * @note    Implemented as function call.
 * @note    To disable interrupt back use MCG_InstallCallback with ip set to 0
 *          and calback point to NULL.
 * @warning Should only be in relation with FEE, FBE, PEE, PBE, or BLPE working
 *          with external clock monitor for OSC enabled.
 ******************************************************************************/ 
#define MCG_InstallCallback(ip,callback)   MCG_InstallCallback(ip,callback)
/*! @} End of mcg_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern void FLL_Init(tMCG fll);
extern void PLL_Init(tMCG pll);
extern void EXTCLK_Init(tMCG extclk);
extern void MCG_InstallCallback (uint8 ip, MCG_CALLBACK pCallback);
#endif /* __MCG_H */
