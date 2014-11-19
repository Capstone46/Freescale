/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      appconfig.h
 * @author    
 * @version   0.0.1.0
 * @date      Jun-20-2013
 * @brief     Application configuration and interrupt vector definitions.
 ******************************************************************************/
#ifndef __APPCONFIG_H
#define __APPCONFIG_H

/*******************************************************************************
*//*! @addtogroup frdm_lpuart_test_config_def
* @{
*******************************************************************************/

/***************************************************************************//*!
 * @brief   Define processor device.
 * @details Supported devices - MCU_MKL43Z256  (MCU_MKL46Z256 temporarily used)
 ******************************************************************************/
#define MCU_MKL43Z256

/**************************************************************************/ /*!
 * @brief   All peripherals enabled configuration.
 *****************************************************************************/
#define SIM_MODULE_FRDM_LPUART_CONFIG                                           \
(tSIM){                                                                         \
/* SOPT1   */ CLR(SIM_SOPT1_USBREGEN_MASK)|CLR(SIM_SOPT1_USBSSTBY_MASK)|        \
              CLR(SIM_SOPT1_USBVSTBY_MASK)|SET(SIM_SOPT1_OSC32KSEL(0x00))|      \
              SET(SIM_SOPT1_OSC32KOUT(0x00)),                                   \
/* SOPT1CFG*/ CLR(SIM_SOPT1CFG_USSWE_MASK)|CLR(SIM_SOPT1CFG_UVSWE_MASK)|        \
              CLR(SIM_SOPT1CFG_URWE_MASK),                                      \
/* SOPT2   */ SET(SIM_SOPT2_LPUART1SRC(0x00))|                                  \
              SET(SIM_SOPT2_LPUART0SRC(0x03))|SET(SIM_SOPT2_TPMSRC(0x00))|      \
              SET(SIM_SOPT2_FLEXIOSRC(0x00))|CLR(SIM_SOPT2_USBSRC_MASK)|        \
              SET(SIM_SOPT2_CLKOUTSEL(0x00))|CLR(SIM_SOPT2_RTCCLKOUTSEL_MASK),  \
/* SOPT4   */ CLR(SIM_SOPT4_TPM2CLKSEL_MASK)|CLR(SIM_SOPT4_TPM1CLKSEL_MASK)|    \
              CLR(SIM_SOPT4_TPM0CLKSEL_MASK)|CLR(SIM_SOPT4_TPM2CH0SRC_MASK)|    \
              SET(SIM_SOPT4_TPM1CH0SRC(0x0)),                                   \
/* SOPT5   */ CLR(SIM_SOPT5_UART0ODE_MASK)|CLR(SIM_SOPT5_LPUART1ODE_MASK)|      \
              CLR(SIM_SOPT5_LPUART0ODE_MASK)|                                   \
              CLR(SIM_SOPT5_LPUART1RXSRC_MASK)|SET(SIM_SOPT5_LPUART1TXSRC(0x00))|\
              CLR(SIM_SOPT5_LPUART0RXSRC_MASK)|SET(SIM_SOPT5_LPUART0TXSRC(0x00)),\
/* SOPT7   */ CLR(SIM_SOPT7_ADC0ALTTRGEN_MASK)|CLR(SIM_SOPT7_ADC0PRETRGSEL_MASK)|\
              SET(SIM_SOPT7_ADC0TRGSEL(0x00)),                                  \
/* SCGC4   */ CLR(SIM_SCGC4_SPI1_MASK)|CLR(SIM_SCGC4_SPI0_MASK)|                \
              CLR(SIM_SCGC4_CMP_MASK)|CLR(SIM_SCGC4_USBFS_MASK)|                \
              CLR(SIM_SCGC4_UART0_MASK)|CLR(SIM_SCGC4_VREF_MASK)|               \
              CLR(SIM_SCGC4_I2C1_MASK)|CLR(SIM_SCGC4_I2C0_MASK),                \
/* SCGC5   */ SET(SIM_SCGC5_LPUART0_MASK)|CLR(SIM_SCGC5_LPUART1_MASK)|          \
              SET(SIM_SCGC5_PORTE_MASK)|SET(SIM_SCGC5_PORTD_MASK)|              \
              SET(SIM_SCGC5_PORTC_MASK)|SET(SIM_SCGC5_PORTB_MASK)|              \
              SET(SIM_SCGC5_PORTA_MASK)|CLR(SIM_SCGC5_FLEXIO_MASK)|             \
              SET(SIM_SCGC5_LPTMR_MASK)|CLR(SIM_SCGC5_SLCD_MASK),               \
/* SCGC6   */ CLR(SIM_SCGC6_DAC0_MASK)|                                         \
              CLR(SIM_SCGC6_RTC_MASK)|CLR(SIM_SCGC6_ADC0_MASK)|                 \
              CLR(SIM_SCGC6_TPM2_MASK)|CLR(SIM_SCGC6_TPM1_MASK)|                \
              CLR(SIM_SCGC6_TPM0_MASK)|CLR(SIM_SCGC6_PIT_MASK)|                 \
              CLR(SIM_SCGC6_I2S_MASK)|SET(SIM_SCGC6_DMAMUX_MASK)|               \
              SET(SIM_SCGC6_FTF_MASK),                                          \
/* SCGC7   */ CLR(SIM_SCGC7_DMA_MASK),                                          \
/* CLKDIV1 */ SET(SIM_CLKDIV1_OUTDIV1(DIV_01))|SET(SIM_CLKDIV1_OUTDIV4(DIV_02)),\
}

/**************************************************************************/ /*!
 * @brief General LPUART configuration for lpuart usecase 2. 
 * @param   brate     Baud rate.
 * @param   bclk      Buss clock in Hz.
 *****************************************************************************/
#define LPUART_FRDM_LPUART_CONFIG(brate,bclk)                                   \
(tLPUART){                                                                      \
/* BAUD     */ CLR(LPUART_BAUD_MAEN1_MASK)|CLR(LPUART_BAUD_MAEN2_MASK)|         \
               CLR(LPUART_BAUD_M10_MASK)|((CALC_BRFA(brate,bclk)<<23)&0x1f000000)|\
               CLR(LPUART_BAUD_TDMAE_MASK)|CLR(LPUART_BAUD_RDMAE_MASK)|         \
               SET(LPUART_BAUD_MATCFG(0x0))|CLR(LPUART_BAUD_BOTHEDGE_MASK)|     \
               CLR(LPUART_BAUD_RESSYNCDIS_MASK)|CLR(LPUART_BAUD_LBKDIE_MASK)|   \
               CLR(LPUART_BAUD_RXEDGIE)|CLR(LPUART_BAUD_SBNS_MASK)|             \
               (CALC_SBR(brate,bclk)&0x1FFF),                                   \
/* STAT     */ CLR(LPUART_STAT_MSBF_MASK)|CLR(LPUART_STAT_RXINV_MASK)|          \
               CLR(LPUART_STAT_RWUID_MASK)|CLR(LPUART_STAT_BRK13_MASK)|         \
               CLR(LPUART_STAT_LBKDE_MASK),                                     \
/* CTRL     */ CLR(LPUART_CTRL_R8T9_MASK)|CLR(LPUART_CTRL_R9T8_MASK)|           \
               CLR(LPUART_CTRL_TXDIR_MASK)|CLR(LPUART_CTRL_TXINV_MASK)|         \
               CLR(LPUART_CTRL_ORIE_MASK)|CLR(LPUART_CTRL_NEIE_MASK)|           \
               CLR(LPUART_CTRL_FEIE_MASK)|CLR(LPUART_CTRL_PEIE_MASK)|           \
               CLR(LPUART_CTRL_TIE_MASK)|CLR(LPUART_CTRL_TCIE_MASK)|            \
               SET(LPUART_CTRL_RIE_MASK)|CLR(LPUART_CTRL_ILIE_MASK)|            \
               SET(LPUART_CTRL_TE_MASK)|SET(LPUART_CTRL_RE_MASK)|               \
               CLR(LPUART_CTRL_RWU_MASK)|CLR(LPUART_CTRL_SBK_MASK)|             \
               CLR(LPUART_CTRL_MA1IE_MASK)|CLR(LPUART_CTRL_MA2IE_MASK)|         \
               SET(LPUART_CTRL_IDLECFG(0x0))|CLR(LPUART_CTRL_LOOPS_MASK)|       \
               CLR(LPUART_CTRL_DOZEEN_MASK)|CLR(LPUART_CTRL_RSRC_MASK)|         \
               CLR(LPUART_CTRL_M_MASK)|CLR(LPUART_CTRL_WAKE_MASK)|              \
               CLR(LPUART_CTRL_ILT_MASK)|CLR(LPUART_CTRL_PE_MASK)|              \
               CLR(LPUART_CTRL_PT_MASK),                                        \
/* MATCH    */ SET(LPUART_MATCH_MA2(0x0))|SET(LPUART_MATCH_MA1(0x0)),           \
}

#define INTRO_MESSAGE "\n\rThis is FRDM LPUART test:\n\r---------------------\n\r"

#define REQUEST_MESSAGE "\n\rPress <<e>> to enter VLPS mode with LPUART0 address\
 match wake up\n\r"

#define VLPS_ENTER_MESSAGE "\n\rVLPS entered ...\n\rSend 0x81 or 0xAA to wake up\
\n\r"
   
#define WARNING_MESSAGE "\n\rWrong setting. Try again.\n\r" 

/******************************************************************************
 * @brief   Define interrupt vectors.
 * @example 
 *          extern void uart_isr (void);       ///< uart isr prototype
 *          #undef  VECTOR_030
 *          #define VECTOR_030 uart_isr        ///< uart_isr interrupt vector re-definition
 ******************************************************************************/
extern void lpuart0_isr (void);   ///< lpuart0 isr prototype (defined in uart.c)

#undef  VECTOR_028
#define VECTOR_028 lpuart0_isr    ///< lpuart0_isr interrupt vector re-definition

#undef  CONFIG_4
#define CONFIG_4 (pointer*)0xffff3bfe ///< FOPT - NMI is disabled
/*! @} End of frdm_lpuart_test_config_def                                           */

#endif /* __APPCONFIG_ */
