/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      mcg_lite.h
 * @version   1.0.2.0
 * @date      Oct-17-2013
 * @brief     Multipurpose clock generator lite (MCG_Lite) driver header file.
 *
 * Revision History:
 *  1.	18/12/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup mcglite_example0
 * @{
 * @par       Source code:
 * @include   mcglite0_test\mcglite0_test.c
 * @par       Appconfig.h:
 * @include   mcglite0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of mcglite_example0                                                */
#ifndef __MCG_LITE_H
#define __MCG_LITE_H 

/******************************************************************************
 * macro definitions                                                          *
 ******************************************************************************/
#define WAIT_FOR_STATUS_FLAG(reg,name1,name2)                                 \
{                                                                             \
  while (((MCG_S&MCG_S_##name2##_MASK)>>MCG_S_##name2##_SHIFT)!=              \
    ((reg&##reg##_##name1##_MASK)>>##reg##_##name1##_SHIFT));                 \
}

/******************************************************************************
 * definition configuration structure                                         *
 ******************************************************************************/
typedef struct { uint8 C1, C2, SC, MC; } tMCG_LITE;

/******************************************************************************
* Low frequency internal reference clock dividers (used for direct LIRC divider
* as well as for further divider used just for MCGIRCLK).
*
*//*! @addtogroup lirc_div_list
* @{
*******************************************************************************/
#define LIRC_DIV_1      (uint8)0x00   ///< Divide factor 1 is 1
#define LIRC_DIV_2      (uint8)0x01   ///< Divide factor 1 is 2
#define LIRC_DIV_4      (uint8)0x02   ///< Divide factor 1 is 4
#define LIRC_DIV_8      (uint8)0x03   ///< Divide factor 1 is 8
#define LIRC_DIV_16     (uint8)0x04   ///< Divide factor 1 is 16
#define LIRC_DIV_32     (uint8)0x05   ///< Divide factor 1 is 32
#define LIRC_DIV_64     (uint8)0x06   ///< Divide factor 1 is 64
#define LIRC_DIV_128    (uint8)0x07   ///< Divide factor 1 is 128
/*! @} End of lirc_div_list                                                   */

/******************************************************************************
* IRC clock selection macro definition.
*
*//*! @addtogroup irc_clk_list
* @{
*******************************************************************************/
/* Macros for internal clock selection                                        */
#define HIGH_IRC       (uint8)0x00      ///< high frequency clock (48MHz IRC)
#define LOW_IRC        (uint8)0x01      ///< low frequency clock (8/2MHz IRC)
#define EXT_CLK        (uint8)0x02      ///< external clock
/*! @} End of irc_clk_list                                                    */

/******************************************************************************
* Status flag macro definition.
*
*//*! @addtogroup mcglite_status_list
* @{
*******************************************************************************/
/* Macros for internal clock selection                                        */
#define HIRC_STATUS     (uint8)0x00      ///< mask for HIRC status
#define OSCINIT_STATUS  (uint8)0x02      ///< mask for OCSINIT status
#define LIRC_STATUS     (uint8)0x04      ///< mask for LIRC
#define EXTCLK_STATUS   (uint8)0x08      ///< mask for EXTCLK

/*! @} End of mcglite_status_list                                                    */

/******************************************************************************
* LIRC clock selection macro definition.
*
*//*! @addtogroup lirc_clk_list
* @{
*******************************************************************************/
/* Macros for low frequency internal clock selection                          */
#define LIRC_2MHZ      (uint8)0x00      ///< low frequency clock (2MHz IRC)
#define LIRC_8MHZ      (uint8)0x01      ///< low frequency clock (8MHz IRC)
/*! @} End of lirc_clk_list                                                   */

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
#define LOW_POWER_OSC           (uint8)0x00      ///< low power crystal oscilator mode
#define HIGH_GAIN_OSC      	(uint8)0x01      ///< high gain crystal oscilator mode
/*! @} End of hgo_list                                                      */

/******************************************************************************
* External clock source type.
*
*//*! @addtogroup extclksel_list
* @{
*******************************************************************************/
#define EXT_REQST               (uint8)0x00      	///< external clock
#define OSC_REQST               (uint8)0x01      	///< crystal oscilator
/*! @} End of extclksel_list                                                  */

/******************************************************************************
* MCG Lite configuration used by MCG_LITE_Init() function.
*
*//*! @addtogroup mcglite_config
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   High frequency IRC 48MHZ configuration.
 ******************************************************************************/
#define MCG_LITE_HIRC_48MHZ                                                    \
(tMCG_LITE){                                                                   \
/* C1 */ SET(MCG_C1_CLKS(0x00))|CLR(MCG_C1_IRCLKEN_MASK)|                      \
         CLR(MCG_C1_IREFSTEN_MASK),                                            \
/* C2 */ SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|CLR(MCG_C2_EREFS0_MASK)|\
         CLR(MCG_C2_IRCS_MASK),                                                \
/* SC */ SET(MCG_SC_FCRDIV(0x00)),                                             \
/* MC */ SET(MCG_MC_HIRCEN_MASK)|SET(MCG_MC_LIRC_DIV2(0x00)),                  \
}
                                     
/***************************************************************************//*!
 * @brief   Low frequency IRC 8MHZ configuration.
 ******************************************************************************/
#define MCG_LITE_LIRC_8MHZ                                                     \
(tMCG_LITE){                                                                   \
/* C1 */ SET(MCG_C1_CLKS(0x01))|SET(MCG_C1_IRCLKEN_MASK)|                      \
         CLR(MCG_C1_IREFSTEN_MASK),                                            \
/* C2 */ SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|CLR(MCG_C2_EREFS0_MASK)|\
         SET(MCG_C2_IRCS_MASK),                                                \
/* SC */ SET(MCG_SC_FCRDIV(0x00)),                                             \
/* MC */ CLR(MCG_MC_HIRCEN_MASK)|SET(MCG_MC_LIRC_DIV2(0x00)),                  \
}
                                     
/***************************************************************************//*!
 * @brief   Low frequency IRC 2MHZ configuration.
 ******************************************************************************/
#define MCG_LITE_LIRC_2MHZ                                                     \
(tMCG_LITE){                                                                   \
/* C1 */ SET(MCG_C1_CLKS(0x01))|SET(MCG_C1_IRCLKEN_MASK)|                      \
         CLR(MCG_C1_IREFSTEN_MASK),                                            \
/* C2 */ SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|CLR(MCG_C2_EREFS0_MASK)|\
         CLR(MCG_C2_IRCS_MASK),                                                \
/* SC */ SET(MCG_SC_FCRDIV(0x00)),                                             \
/* MC */ CLR(MCG_MC_HIRCEN_MASK)|SET(MCG_MC_LIRC_DIV2(0x00)),                  \
}

/***************************************************************************//*!
 * @brief   Low frequency IRC 8MHZ configuration with selected xMHz output.
 * @param   x - @ref lirc_div_list 
 ******************************************************************************/
#define MCG_LITE_LIRC8(div)                                                    \
(tMCG_LITE){                                                                   \
/* C1 */ SET(MCG_C1_CLKS(0x01))|SET(MCG_C1_IRCLKEN_MASK)|                      \
         CLR(MCG_C1_IREFSTEN_MASK),                                            \
/* C2 */ SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|CLR(MCG_C2_EREFS0_MASK)|\
         SET(MCG_C2_IRCS_MASK),                                                \
/* SC */ SET(MCG_SC_FCRDIV(div)),                                              \
/* MC */ CLR(MCG_MC_HIRCEN_MASK)|SET(MCG_MC_LIRC_DIV2(0x00)),                  \
}

#define MCG_LITE_LIRC8_4MHZ             MCG_LITE_LIRC8(LIRC_DIV_2)
#define MCG_LITE_LIRC8_2MHZ             MCG_LITE_LIRC8(LIRC_DIV_4)
#define MCG_LITE_LIRC8_1MHZ             MCG_LITE_LIRC8(LIRC_DIV_8)
#define MCG_LITE_LIRC8_500KHZ           MCG_LITE_LIRC8(LIRC_DIV_16)
#define MCG_LITE_LIRC8_250KHZ           MCG_LITE_LIRC8(LIRC_DIV_32)
#define MCG_LITE_LIRC8_125KHZ           MCG_LITE_LIRC8(LIRC_DIV_64)
#define MCG_LITE_LIRC8_62500HZ          MCG_LITE_LIRC8(LIRC_DIV_128)
                                     
/***************************************************************************//*!
 * @brief   Low frequency IRC 2MHZ configuration with selected xMHz output.
 * @param   x - @ref irc_clk_list 
 ******************************************************************************/
#define MCG_LITE_LIRC2(div)                                                    \
(tMCG_LITE){                                                                   \
/* C1 */ SET(MCG_C1_CLKS(0x01))|SET(MCG_C1_IRCLKEN_MASK)|                      \
         CLR(MCG_C1_IREFSTEN_MASK),                                            \
/* C2 */ SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|CLR(MCG_C2_EREFS0_MASK)|\
         CLR(MCG_C2_IRCS_MASK),                                                \
/* SC */ SET(MCG_SC_FCRDIV(div)),                                              \
/* MC */ CLR(MCG_MC_HIRCEN_MASK)|SET(MCG_MC_LIRC_DIV2(0x00)),                  \
}

#define MCG_LITE_LIRC2_1MHZ             MCG_LITE_LIRC2(LIRC_DIV_2)
#define MCG_LITE_LIRC2_500KHZ           MCG_LITE_LIRC2(LIRC_DIV_4)
#define MCG_LITE_LIRC2_250KHZ           MCG_LITE_LIRC2(LIRC_DIV_8)
#define MCG_LITE_LIRC2_125KHZ           MCG_LITE_LIRC2(LIRC_DIV_16)
#define MCG_LITE_LIRC2_62500HZ          MCG_LITE_LIRC2(LIRC_DIV_32)
#define MCG_LITE_LIRC2_31250HZ          MCG_LITE_LIRC2(LIRC_DIV_64)
#define MCG_LITE_LIRC2_15625HZ          MCG_LITE_LIRC2(LIRC_DIV_128)

/***************************************************************************//*!
 * @brief   External mode with 8MHz crystal oscilator (1Mohm feedback resistor 
 *          expected).OSC module should be configured before entering this mode.
 ******************************************************************************/
#define MCG_LITE_EXT_CRYSTAL_8MHZ                                              \
(tMCG_LITE){                                                                   \
/* C1 */ SET(MCG_C1_CLKS(0x02))|CLR(MCG_C1_IRCLKEN_MASK)|                      \
         CLR(MCG_C1_IREFSTEN_MASK),                                            \
/* C2 */ SET(MCG_C2_RANGE0(0x02))|SET(MCG_C2_HGO0_MASK)|SET(MCG_C2_EREFS0_MASK)|\
         CLR(MCG_C2_IRCS_MASK),                                                \
/* SC */ SET(MCG_SC_FCRDIV(0x0)),                                              \
/* MC */ CLR(MCG_MC_HIRCEN_MASK)|SET(MCG_MC_LIRC_DIV2(0x00)),                  \
}

/***************************************************************************//*!
 * @brief   External mode with 4MHz crystal oscilator (1Mohm feedback resistor 
 *          expected).OSC module should be configured before entering this mode.
 ******************************************************************************/
#define MCG_LITE_EXT_CRYSTAL_4MHZ                                              \
(tMCG_LITE){                                                                   \
/* C1 */ SET(MCG_C1_CLKS(0x02))|CLR(MCG_C1_IRCLKEN_MASK)|                      \
         CLR(MCG_C1_IREFSTEN_MASK),                                            \
/* C2 */ SET(MCG_C2_RANGE0(0x01))|SET(MCG_C2_HGO0_MASK)|SET(MCG_C2_EREFS0_MASK)|\
         CLR(MCG_C2_IRCS_MASK),                                                \
/* SC */ SET(MCG_SC_FCRDIV(0x0)),                                              \
/* MC */ CLR(MCG_MC_HIRCEN_MASK)|SET(MCG_MC_LIRC_DIV2(0x00)),                  \
}

/***************************************************************************//*!
 * @brief   External mode with 32MHz crystal oscilator (1Mohm feedback resistor 
 *          expected).OSC module should be configured before entering this mode.
 ******************************************************************************/
#define MCG_LITE_EXT_CRYSTAL_32KHZ                                              \
(tMCG_LITE){                                                                   \
/* C1 */ SET(MCG_C1_CLKS(0x02))|CLR(MCG_C1_IRCLKEN_MASK)|                      \
         CLR(MCG_C1_IREFSTEN_MASK),                                            \
/* C2 */ SET(MCG_C2_RANGE0(0x00))|CLR(MCG_C2_HGO0_MASK)|SET(MCG_C2_EREFS0_MASK)|\
         CLR(MCG_C2_IRCS_MASK),                                                \
/* SC */ SET(MCG_SC_FCRDIV(0x0)),                                              \
/* MC */ CLR(MCG_MC_HIRCEN_MASK)|SET(MCG_MC_LIRC_DIV2(0x00)),                  \
}

/*! @} End of mcglite_config                                                  */

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
 * @brief   Macro set clockn source select.
 * @param   x - @ref irc_clk_list 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_LITE_ClkSrcSel(x)            REG_SetVal(MCG_C1,MCG_C1_CLKS,x)
																		 
/***************************************************************************//*!
 * @brief   Macro enables high frequency IRC. 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_LITE_HIRC_Enable()           REG_SetVal(MCG_MC,MCG_MC_HIRCEN,0x1)

/***************************************************************************//*!
 * @brief   Macro disables high frequency IRC. 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_LITE_HIRC_Disable()           REG_SetVal(MCG_MC,MCG_MC_HIRCEN,0x0)

/***************************************************************************//*!
 * @brief   Macro enables low frequency IRC. 
 * @param   x - @ref irc_clk_list 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_LITE_LIRC_Enable()           REG_SetVal(MCG_C1,MCG_C1_IRCLKEN,0x1)

/***************************************************************************//*!
 * @brief   Macro disables low frequency IRC. 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_LITE_LIRC_Disable()           REG_SetVal(MCG_C1,MCG_C1_IRCLKEN,0x0)

/***************************************************************************//*!
 * @brief   Macro enables low frequency IRC in stop mode. 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_LITE_LIRC_StopEnable()        REG_SetVal(MCG_C1,MCG_C1_IREFSTEN,0x1)

/***************************************************************************//*!
 * @brief   Macro disables low frequency IRC in Stop mode. 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_LITE_LIRC_StopDisable()     REG_SetVal(MCG_C1,MCG_C1_IREFSTEN,0x0)

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
 * @brief   Macro initialize external clock (when separatelly used e.g. as OSCERCLK).
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
 * @brief   Macro low IRC clock selection. 
 * @param   x - @ref lirc_clk_list 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_LITE_LIRC_Sel(x)    REG_SetVal(MCG_C2,MCG_C2_IRCS,x)

/***************************************************************************//*!
 * @brief   Macro for wainting for status flag. 
 * @param   x - @ref mcglite_status_list 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_LITE_WaitForStatus(status)    {while(!(MCG_S&status));}
																		 
/***************************************************************************//*!
 * @brief   Macro sets first LIRC divider (used for MCGOUTCLK and MCGIRCLK output). 
 * @param   x - @ref lirc_div_list 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_LITE_LIRC_Div1(x)   REG_SetVal(MCG_SC,MCG_SC_FCRDIV,x)	 
	
/***************************************************************************//*!
 * @brief   Macro sets second LIRC divider (used for MCGIRCLK output). 
 * @param   x - @ref lirc_div_list 
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MCG_LITE_LIRC_Div2(x)   REG_SetVal(MCG_MC,MCG_MC_LIRC_DIV2,x)	
																		 
/***************************************************************************//*!
 * @brief   MCG initialization function.
 * @param   cfg - @ref mcg_config
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define MCG_LITE_Init(cfg)      MCG_LITE_Init(cfg)
/*! @} End of mcglite_macro                                                   */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern void MCG_LITE_Init(tMCG_LITE mcglite);
#endif /* __MCG_LITE_H */
