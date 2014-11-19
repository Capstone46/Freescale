/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      sim.h
 * @version   1.0.9.0
 * @date      Mar-1-2013
 * @brief     System Integration Module (SIM) driver header file.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	17/01/2013   B34185   Ported to Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup cop_example0
 * @{
 * @par       Source code:
 * @include   cop0_test\cop0_test.c
 * @par       Appconfig.h:
 * @include   cop0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of cop_example                                                    */
#ifndef __SIM_H
#define __SIM_H 
 
/******************************************************************************
 * definition configuration structure                                         *
 ******************************************************************************/
typedef struct 
{ 
  uint32 SOPT1, SOPT1CFG, SOPT2, SOPT4, SOPT5, SOPT7, SCGC4, SCGC5, SCGC6, SCGC7, 
         CLKDIV1;
} tSIM;

/******************************************************************************
* SIM system clock divider definitions used by SIM_SetClockDiv() function
*
*//*! @addtogroup sim_sysdiv
* @{
*******************************************************************************/
#define DIV_01    (uint8)0x00           ///< divide-by-1
#define DIV_02    (uint8)0x01           ///< divide-by-2
#define DIV_03    (uint8)0x02           ///< divide-by-3
#define DIV_04    (uint8)0x03           ///< divide-by-4
#define DIV_05    (uint8)0x04           ///< divide-by-5
#define DIV_06    (uint8)0x05           ///< divide-by-6
#define DIV_07    (uint8)0x06           ///< divide-by-7
#define DIV_08    (uint8)0x07           ///< divide-by-8
#define DIV_09    (uint8)0x08           ///< divide-by-9
#define DIV_10    (uint8)0x09           ///< divide-by-10
#define DIV_11    (uint8)0x0a           ///< divide-by-11
#define DIV_12    (uint8)0x0b           ///< divide-by-12
#define DIV_13    (uint8)0x0c           ///< divide-by-13
#define DIV_14    (uint8)0x0d           ///< divide-by-14
#define DIV_15    (uint8)0x0e           ///< divide-by-15
#define DIV_16    (uint8)0x0f           ///< divide-by-16
/*! @} End of sim_sysdiv                                                      */

/******************************************************************************
* SIM clkout clock source definitions used by SIM_SelClkoutSrc() function
*
*//*! @addtogroup sim_clkout_src
* @{
*******************************************************************************/
#define CLKOUT_DISABLED (uint32)0x00  ///< Disabled
#define CLKOUT_BUSCLK   (uint32)0x02  ///< Bus clock
#define CLKOUT_LPO      (uint32)0x03  ///< LPO clock (1kHz)
#define CLKOUT_MCGIRCLK (uint32)0x04  ///< MCGIRCLK
#define CLKOUT_OSCERCLK (uint32)0x06  ///< OSCERCLK
#define CLKOUT_IRC48M   (uint32)0x07  ///< High frequency IRC 48MHz clock
/*! @} End of sim_clkout_src                                                      */

/******************************************************************************
* COP watchdog timeout macros based on COP mode used by SIM_COPConfig(x)
*
*//*! @addtogroup sim_coptimeout
* @{
*******************************************************************************/
#if (defined (MCU_MKL46Z256))
  #define COP_DISABLE                     (0x00)                                  ///< COP disabled
  #define COP_8192_BUSCLK_NORMAL          (0x0000000F & ((1<<2) | (1<<1)) | 0)    ///< COP timeout after 2^5 bus cycles in normal mode
  #define COP_65536_BUSCLK_NORMAL         (0x0000000F & ((1<<3) | (1<<1)) | 0)    ///< COP timeout after 2^8 bus cycles in normal mode 
  #define COP_262144_BUSCLK_NORMAL        (0x0000000F & ((3<<2) | (1<<1)) | 0)    ///< COP timeout after 2^10 bus cycles in normal mode
  #define COP_8192_BUSCLK_WINDOWED        (0x0000000F & ((1<<2) | (1<<1)) | 1)    ///< COP timeout after 2^5 bus cycles in windowed mode
  #define COP_65536_BUSCLK_WINDOWED       (0x0000000F & ((1<<3) | (1<<1)) | 1)    ///< COP timeout after 2^8 bus cycles in windowed mode
  #define COP_262144_BUSCLK_WINDOWED      (0x0000000F & ((3<<2) | (1<<1)) | 1)    ///< COP timeout after 2^10 bus cycles in windowed mode
  #define COP_32ms                        (0x0000000F & ((1<<2) | (0<<1)) | 0)    ///< COP timeout after 2^5 LPO cycles in normal mode
  #define COP_256ms                       (0x0000000F & ((1<<3) | (0<<1)) | 0)    ///< COP timeout after 2^8 LPO cycles in normal mode
  #define COP_1024ms                      (0x0000000F & ((3<<2) | (0<<1)) | 0)    ///< COP timeout after 2^10 LPO cycles in normal mode
#elif (defined (MCU_MKL43Z256))
  #define COP_DISABLE                     (0x00)                                  ///< COP disabled
  
  #define SIM_COPC_CONFIG_MASK            0x3Fu
  #define SIM_COPC_CONFIG_SHIFT           0x0
  
  #define COP_LPO                         0x0    ///< LPO as COP clock source 
  #define COP_MCGIRCLK                    0x1    ///< MCGIRCLK as COP clock source 
  #define COP_OSCERCLK                    0x2    ///< OSCERCLK as COP clock source 
  #define COP_BUSCLK                      0x3    ///< BUSCLK as COP clock source
  
  #define COP_32_CYCLES                   0x4    ///< 32 cycles timeout 
  #define COP_256_CYCLES                  0x8    ///< 256 cycles timeout 
  #define COP_1024_CYCLES                 0xC    ///< 1024 cycles timeout 
  #define COP_8191_CYCLES                 0x6    ///< 8191 cycles timeout
  #define COP_65535_CYCLES                0xA    ///< 65535 cycles timeout 
  #define COP_262144_CYCLES               0xE    ///< 262144 cycles timeout

  #define COP_NORMAL                      0x0    ///< normal mode 
  #define COP_WINDOW                      0x1    ///< windowed mode


#endif
/*! @} End of sim_coptimeout                                                  */

/******************************************************************************
* SIM ADC0 start of conversion trigger selection macros used by SIM_ADC0TrgSel()
*
*//*! @addtogroup sim_adc0trgsel
* @{
*******************************************************************************/
#define SIM_TPM1_TRG_ADC0_AB    (uint32)0x00    ///< TPM1 CH0 triggers SoC of ADC0 A and TPM1 CH1 triggers SoC of ADC0 B  
#define SIM_EXTIN_TRG_ADC0_A    (uint32)0x80    ///< External pin input triggers SoC of ADC0 A
#define SIM_EXTIN_TRG_ADC0_B    (uint32)0x90    ///< External pin input triggers SoC of ADC0 B
#define SIM_HSCMP0_TRG_ADC0_A   (uint32)0x81    ///< HSCMP0 output triggers SoC of ADC0 A
#define SIM_HSCMP0_TRG_ADC0_B   (uint32)0x91    ///< HSCMP0 output triggers SoC of ADC0 B
#define SIM_PIT0_TRG_ADC0_A     (uint32)0x84    ///< PIT0 CH0 triggers SoC of ADC0 A
#define SIM_PIT0_TRG_ADC0_B     (uint32)0x94    ///< PIT0 CH0 triggers SoC of ADC0 B
#define SIM_PIT1_TRG_ADC0_A     (uint32)0x85    ///< PIT0 CH0 triggers SoC of ADC0 A
#define SIM_PIT1_TRG_ADC0_B     (uint32)0x95    ///< PIT0 CH0 triggers SoC of ADC0 B
#define SIM_TPM0_TRG_ADC0_A     (uint32)0x88    ///< TPM0 overflow triggers SoC of ADC0 A
#define SIM_TPM0_TRG_ADC0_B     (uint32)0x98    ///< TPM0 overflow triggers SoC of ADC0 B
#define SIM_TPM1_TRG_ADC0_A     (uint32)0x89    ///< TPM1 overflow triggers SoC of ADC0 A
#define SIM_TPM1_TRG_ADC0_B     (uint32)0x99    ///< TPM1 overflow triggers SoC of ADC0 B
#define SIM_TPM2_TRG_ADC0_A     (uint32)0x8A    ///< TPM2 overflow triggers SoC of ADC0 A
#define SIM_TPM2_TRG_ADC0_B     (uint32)0x9A    ///< TPM2 overflow triggers SoC of ADC0 B
#define SIM_RTCALARM_TRG_ADC0_A (uint32)0x8C    ///< RTC alarm triggers SoC of ADC0 A
#define SIM_RTCALARM_TRG_ADC0_B (uint32)0x9C    ///< RTC alarm triggers SoC of ADC0 B
#define SIM_RTCSEC_TRG_ADC0_A   (uint32)0x8D    ///< RTC second triggers SoC of ADC0 A
#define SIM_RTCSEC_TRG_ADC0_B   (uint32)0x9D    ///< RTC second triggers SoC of ADC0 B
#define SIM_LPTMR0_TRG_ADC0_A   (uint32)0x8E    ///< LPTMR0 triggers SoC of ADC0 A
#define SIM_LPTMR0_TRG_ADC0_B   (uint32)0x9E    ///< LPTMR0 triggers SoC of ADC0 B
/*! @} End of sim_adc0trgsel                                                  */

#define TPM_CH0_PIN             (0x00)
#define UART_RX_PIN             (0x00)
#define COMP0_OUT               (0x01)

/******************************************************************************
* SIM default configurations used by SIM_init() function
*
*//*! @addtogroup sim_config
* @{
*******************************************************************************/
#if (defined (MCU_MKL46Z256))
/**************************************************************************/ /*!
 * @brief   All peripherals enabled configuration.
 *****************************************************************************/
#define SIM_MODULE_CONFIG_ALL_PERIPH_ON                    /* all clocks on */  \
(tSIM){                                                                         \
/* SOPT1   */ SET(SIM_SOPT1_USBREGEN_MASK)|CLR(SIM_SOPT1_USBSSTBY_MASK)|        \
              CLR(SIM_SOPT1_USBVSTBY_MASK)|SET(SIM_SOPT1_OSC32KSEL(0x00)),      \
/* SOPT1CFG*/ CLR(SIM_SOPT1CFG_USSWE_MASK)|CLR(SIM_SOPT1CFG_UVSWE_MASK)|        \
              CLR(SIM_SOPT1CFG_URWE_MASK),                                      \
/* SOPT2   */ CLR(SIM_SOPT2_USBSRC_MASK)|CLR(SIM_SOPT2_PLLFLLSEL_MASK)|         \
              SET(SIM_SOPT2_UART0SRC(0x01))|SET(SIM_SOPT2_TPMSRC(0x01))|        \
              SET(SIM_SOPT2_CLKOUTSEL(0x02))|CLR(SIM_SOPT2_RTCCLKOUTSEL_MASK),  \
/* SOPT4   */ CLR(SIM_SOPT4_TPM2CLKSEL_MASK)|CLR(SIM_SOPT4_TPM1CLKSEL_MASK)|    \
              CLR(SIM_SOPT4_TPM0CLKSEL_MASK)|CLR(SIM_SOPT4_TPM2CH0SRC_MASK)|    \
              SET(SIM_SOPT4_TPM1CH0SRC(0x0)),                                   \
/* SOPT5   */ CLR(SIM_SOPT5_UART2ODE_MASK)|CLR(SIM_SOPT5_UART1ODE_MASK)|        \
              CLR(SIM_SOPT5_UART0ODE_MASK)|                                     \
              CLR(SIM_SOPT5_UART1RXSRC_MASK)|SET(SIM_SOPT5_UART1TXSRC(0x00))|   \
              CLR(SIM_SOPT5_UART0RXSRC_MASK)|SET(SIM_SOPT5_UART0TXSRC(0x00)),   \
/* SOPT7   */ CLR(SIM_SOPT7_ADC0ALTTRGEN_MASK)|CLR(SIM_SOPT7_ADC0PRETRGSEL_MASK)|\
              SET(SIM_SOPT7_ADC0TRGSEL(0x00)),                                  \
/* SCGC4   */ SET(SIM_SCGC4_SPI1_MASK)|SET(SIM_SCGC4_SPI0_MASK)|                \
              SET(SIM_SCGC4_CMP_MASK)|SET(SIM_SCGC4_USBOTG_MASK)|               \
              SET(SIM_SCGC4_UART2_MASK)|SET(SIM_SCGC4_UART1_MASK)|              \
              SET(SIM_SCGC4_UART0_MASK)|SET(SIM_SCGC4_I2C1_MASK)|               \
              SET(SIM_SCGC4_I2C0_MASK),                                         \
/* SCGC5   */ SET(SIM_SCGC5_PORTE_MASK)|SET(SIM_SCGC5_PORTD_MASK)|              \
              SET(SIM_SCGC5_PORTC_MASK)|SET(SIM_SCGC5_PORTB_MASK)|              \
              SET(SIM_SCGC5_PORTA_MASK)|SET(SIM_SCGC5_TSI_MASK)|                \
              SET(SIM_SCGC5_LPTMR_MASK)|SET(SIM_SCGC5_SLCD_MASK),               \
/* SCGC6   */ SET(SIM_SCGC6_DAC0_MASK)|                                         \
              SET(SIM_SCGC6_RTC_MASK)|SET(SIM_SCGC6_ADC0_MASK)|                 \
              SET(SIM_SCGC6_TPM2_MASK)|SET(SIM_SCGC6_TPM1_MASK)|                \
              SET(SIM_SCGC6_TPM0_MASK)|SET(SIM_SCGC6_PIT_MASK)|                 \
              SET(SIM_SCGC6_I2S_MASK)|SET(SIM_SCGC6_DMAMUX_MASK)|               \
              SET(SIM_SCGC6_FTF_MASK),                                          \
/* SCGC7   */ SET(SIM_SCGC7_DMA_MASK),                                          \
/* CLKDIV1 */ SET(SIM_CLKDIV1_OUTDIV1(DIV_01))|SET(SIM_CLKDIV1_OUTDIV4(DIV_02)),\
}
#endif

#if (defined (MCU_MKL43Z256))
/**************************************************************************/ /*!
 * @brief   All peripherals enabled configuration.
 *****************************************************************************/
#define SIM_MODULE_CONFIG_ALL_PERIPH_ON                    /* all clocks on */  \
(tSIM){                                                                         \
/* SOPT1   */ SET(SIM_SOPT1_USBREGEN_MASK)|CLR(SIM_SOPT1_USBSSTBY_MASK)|        \
              CLR(SIM_SOPT1_USBVSTBY_MASK)|SET(SIM_SOPT1_OSC32KSEL(0x00))|      \
              SET(SIM_SOPT1_OSC32KOUT(0x00)),                                   \
/* SOPT1CFG*/ CLR(SIM_SOPT1CFG_USSWE_MASK)|CLR(SIM_SOPT1CFG_UVSWE_MASK)|        \
              CLR(SIM_SOPT1CFG_URWE_MASK),                                      \
/* SOPT2   */ SET(SIM_SOPT2_LPUART1SRC(0x01))|                                  \
              SET(SIM_SOPT2_LPUART0SRC(0x01))|SET(SIM_SOPT2_TPMSRC(0x01))|      \
              SET(SIM_SOPT2_FLEXIOSRC(0x01))|CLR(SIM_SOPT2_USBSRC_MASK)|        \
              SET(SIM_SOPT2_CLKOUTSEL(0x02))|CLR(SIM_SOPT2_RTCCLKOUTSEL_MASK),  \
/* SOPT4   */ CLR(SIM_SOPT4_TPM2CLKSEL_MASK)|CLR(SIM_SOPT4_TPM1CLKSEL_MASK)|    \
              CLR(SIM_SOPT4_TPM0CLKSEL_MASK)|CLR(SIM_SOPT4_TPM2CH0SRC_MASK)|    \
              SET(SIM_SOPT4_TPM1CH0SRC(0x0)),                                   \
/* SOPT5   */ CLR(SIM_SOPT5_UART2ODE_MASK)|CLR(SIM_SOPT5_LPUART1ODE_MASK)|      \
              CLR(SIM_SOPT5_LPUART0ODE_MASK)|                                   \
              CLR(SIM_SOPT5_LPUART1RXSRC_MASK)|SET(SIM_SOPT5_LPUART1TXSRC(0x00))|\
              CLR(SIM_SOPT5_LPUART0RXSRC_MASK)|SET(SIM_SOPT5_LPUART0TXSRC(0x00)),\
/* SOPT7   */ CLR(SIM_SOPT7_ADC0ALTTRGEN_MASK)|CLR(SIM_SOPT7_ADC0PRETRGSEL_MASK)|\
              SET(SIM_SOPT7_ADC0TRGSEL(0x00)),                                  \
/* SCGC4   */ SET(SIM_SCGC4_SPI1_MASK)|SET(SIM_SCGC4_SPI0_MASK)|                \
              SET(SIM_SCGC4_CMP_MASK)|SET(SIM_SCGC4_USBFS_MASK)|                \
              SET(SIM_SCGC4_UART0_MASK)|SET(SIM_SCGC4_VREF_MASK)|               \
              SET(SIM_SCGC4_I2C1_MASK)|SET(SIM_SCGC4_I2C0_MASK),                \
/* SCGC5   */ SET(SIM_SCGC5_LPUART0_MASK)|SET(SIM_SCGC5_LPUART1_MASK)|          \
              SET(SIM_SCGC5_PORTE_MASK)|SET(SIM_SCGC5_PORTD_MASK)|              \
              SET(SIM_SCGC5_PORTC_MASK)|SET(SIM_SCGC5_PORTB_MASK)|              \
              SET(SIM_SCGC5_PORTA_MASK)|SET(SIM_SCGC5_FLEXIO_MASK)|             \
              SET(SIM_SCGC5_LPTMR_MASK)|SET(SIM_SCGC5_SLCD_MASK),               \
/* SCGC6   */ SET(SIM_SCGC6_DAC0_MASK)|                                         \
              SET(SIM_SCGC6_RTC_MASK)|SET(SIM_SCGC6_ADC0_MASK)|                 \
              SET(SIM_SCGC6_TPM2_MASK)|SET(SIM_SCGC6_TPM1_MASK)|                \
              SET(SIM_SCGC6_TPM0_MASK)|SET(SIM_SCGC6_PIT_MASK)|                 \
              SET(SIM_SCGC6_I2S_MASK)|SET(SIM_SCGC6_DMAMUX_MASK)|               \
              SET(SIM_SCGC6_FTF_MASK),                                          \
/* SCGC7   */ SET(SIM_SCGC7_DMA_MASK),                                          \
/* CLKDIV1 */ SET(SIM_CLKDIV1_OUTDIV1(DIV_01))|SET(SIM_CLKDIV1_OUTDIV4(DIV_02)),\
}
#endif

/*! @} End of sim_config                                                      */

/******************************************************************************
* SIM function and macro definitions
*
*//*! @addtogroup sim_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro sets the divide value for the core/system clock.
 * @param   div - @ref sim_sysdiv
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define SIM_SetOUTDIV1(div) { REG_SetVal(SIM_CLKDIV1,SIM_CLKDIV1_OUTDIV1,      \
                                      (uint32)(div&0x0f));                     \
                          }

/***************************************************************************//*!
 * @brief   Macro sets the divide value for the bus/flash clock.
 * @param   div - @ref sim_sysdiv (use only up to div 8)
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define SIM_SetOUTDIV4(div) { REG_SetVal(SIM_CLKDIV1,SIM_CLKDIV1_OUTDIV4,      \
                                      (uint32)(div&0x0f));                     \
                          } 

/***************************************************************************//*!
 * @brief   Macro selects the MCGPLLCLK/2 or MCGFLLCLK clock for various  
 *          peripheral clocking options.
 * @param   clk - TRUE for MCGPLLCLK/2 or FALSE for MCGFLLCLK
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define SIM_SetPllFllClockSource(clk) {REG_SetVal(SIM_SOPT2,SIM_SOPT2_PLLFLLSEL,\
                                                    clk);                       \
                                    }

/***************************************************************************//*!
 * @brief   Macro selects the clock to output on the CLKOUT pin..
 * @param   clk   @ref sim_clkout_src
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define SIM_SelClkoutSrc(clk)     {REG_SetVal(SIM_SOPT2,SIM_SOPT2_CLKOUTSEL,clk);}

/***************************************************************************//*!
 * @brief   SIM initialization function.
 * @details This function initializes System Integration Module (SIM).  
 * @param   cfg       Use one of the following configuration structures 
 *                    @ref sim_config
 * @note    Implemented as function call.
 ******************************************************************************/
#define SIM_Init(cfg)                   SIM_Init(cfg)
/*! @} End of sim_macro                                                       */

/******************************************************************************
* SIM COP function and macro definitions
*
*//*! @addtogroup sim_copmacro
* @{
*******************************************************************************/
#if (defined (MCU_MKL43Z256))
/***************************************************************************//*!
 * @brief   Macro enables COP in debug mode.
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define SIM_COPDebugEnable      { REG_SetVal(SIM_COPC,SIM_COPC_COPDBGEN,0x1); }

/***************************************************************************//*!
 * @brief   Macro disables COP in debug mode.
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define SIM_COPDebugDisable     { REG_SetVal(SIM_COPC,SIM_COPC_COPDBGEN,0x0); }

/***************************************************************************//*!
 * @brief   Macro enables COP in stop mode.
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define SIM_COPStopEnable       { REG_SetVal(SIM_COPC,SIM_COPC_COPSTPEN,0x1); }

/***************************************************************************//*!
 * @brief   Macro disables COP in stop mode.
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define SIM_COPStopDisable      { REG_SetVal(SIM_COPC,SIM_COPC_COPSTPEN,0x0); }

/***************************************************************************//*!
 * @brief   Macro configures COP.
 * @param   clksrc - @ref sim_coptimeout
 * @param   cycles - @ref sim_coptimeout
 * @param   mode - @ref sim_coptimeout
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define COP_CFG(clksrc,cycles,mode)     {REG_SetVal(SIM_COPC,SIM_COPC_CONFIG,((clksrc<<SIM_COPC_COPW_MASK)|(cycles<<SIM_COPC_COPCLKS_SHIFT)|mode));}

/***************************************************************************//*!
 * @brief   Macro provides the COP configuration.
 * @param   timeout - use COP_DISABLE or COP_CFG() macro
 * @return  none
 * @note    Implemented as inlined macro. This configuration can only be done  
 *          once after a reset.
 ******************************************************************************/
#define SIM_COPConfig(timeout)                SIM_COPC = (timeout)

#elif (defined (MCU_MKL46Z256))
/***************************************************************************//*!
 * @brief   Macro provides the COP configuration.
 * @param   timeout - @ref sim_coptimeout
 * @return  none
 * @note    Implemented as inlined macro. This configuration can only be done  
 *          once after a reset.
 ******************************************************************************/
#define SIM_COPConfig(timeout)                SIM_COPC = (timeout)

#endif

/***************************************************************************//*!
 * @brief   Macro selects the MCGPLLCLK or MCGFLLCLK clock for various peripheral 
 *          clocking options.
 * @return  none
 * @note    Implemented as inlined macro. Writing of any different values to
            COP service register will force MCU reset.
 ******************************************************************************/
#define SIM_COPReset                    {                                       \
                                          SIM_SRVCOP = 0x55;                    \
                                          SIM_SRVCOP = 0xAA;                    \
                                        }

/*! @} End of sim_copmacro                                                    */


/******************************************************************************
* SIM module to module interconnection macro definitions
*
*//*! @addtogroup sim_module_to_module
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro sets ADC0 start of conversion trigger.
 * @param   cfg - @ref sim_adc0trgsel
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define SIM_ADC0TrgSel(cfg)     {SIM_SOPT7 = ((SIM_SOPT7&0xFFFFFF00)|cfg);}

/***************************************************************************//*!
 * @brief   Macro sets TPM channel 0 input capture source.
 * @param   module - TPM1|TPM2
 * @param   src - TPM_CH0_PIN or CMP0_OUT
 * @return  none
 * @note    Implemented as inlined macro. When TPMx is not in input capture 
 *          mode, clear this field.
 ******************************************************************************/
#define SIM_TPMCH0_InCap_SrcSel(module,src) {REG_SetVal(SIM_SOPT4,SIM_SOPT4_##module##CH0SRC,src)};

/***************************************************************************//*!
 * @brief   Macro sets UART receive data source.
 * @param   module - UART0|UART1
 * @param   src - UART_RX_PIN or CMP0_OUT
 * @return  none
 * @note    Implemented as inlined macro. When TPMx is not in input capture 
 *          mode, clear this field.
 ******************************************************************************/
#define SIM_UART_RX_SrcSel(module,src) {REG_SetVal(SIM_SOPT5,SIM_SOPT5_##module##RXSRC,src)};

/*! @} End of sim_module_to_module                                            */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/    
extern void SIM_Init (tSIM sim);
   
#endif /* __SIM_H */ 
