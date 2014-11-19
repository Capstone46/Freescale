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
*//*! @addtogroup frdm_slcd_test_config_def
* @{
*******************************************************************************/

/***************************************************************************//*!
 * @brief   Define processor device.
 * @details Supported devices - MCU_MKL43Z256  (MCU_MKL46Z256 temporarily used)
 ******************************************************************************/
#define MCU_MKL43Z256

/***************************************************************************//*!
 * @brief   Define the HW platform.
 * @param   Supported platforms - TWR_KL43Z48M|FRDM_KL43Z48M|TWR_KL46Z48M|FRDM_KL46Z48M
 ******************************************************************************/
#define FRDM_KL43Z48M

/**************************************************************************/ /*!
 * @brief   SIM module configuration. 
 *          - 32K oscillator clock selected for RTC_CLKIN
 *****************************************************************************/
#define SIM_MODULE_FRDM_SLCD_CONFIG                        /* all clocks on */  \
(tSIM){                                                                         \
/* SOPT1   */ CLR(SIM_SOPT1_USBREGEN_MASK)|CLR(SIM_SOPT1_USBSSTBY_MASK)|        \
              CLR(SIM_SOPT1_USBVSTBY_MASK)|SET(SIM_SOPT1_OSC32KSEL(0x00))|      \
              SET(SIM_SOPT1_OSC32KOUT(0x00)),                                   \
/* SOPT1CFG*/ CLR(SIM_SOPT1CFG_USSWE_MASK)|CLR(SIM_SOPT1CFG_UVSWE_MASK)|        \
              CLR(SIM_SOPT1CFG_URWE_MASK),                                      \
/* SOPT2   */ SET(SIM_SOPT2_LPUART1SRC(0x01))|                                  \
              SET(SIM_SOPT2_LPUART0SRC(0x01))|SET(SIM_SOPT2_TPMSRC(0x01))|      \
              SET(SIM_SOPT2_FLEXIOSRC(0x00))|CLR(SIM_SOPT2_USBSRC_MASK)|        \
              SET(SIM_SOPT2_CLKOUTSEL(0x00))|CLR(SIM_SOPT2_RTCCLKOUTSEL_MASK),  \
/* SOPT4   */ CLR(SIM_SOPT4_TPM2CLKSEL_MASK)|CLR(SIM_SOPT4_TPM1CLKSEL_MASK)|    \
              CLR(SIM_SOPT4_TPM0CLKSEL_MASK)|CLR(SIM_SOPT4_TPM2CH0SRC_MASK)|    \
              CLR(SIM_SOPT4_TPM1CH0SRC_MASK),                                   \
/* SOPT5   */ CLR(SIM_SOPT5_UART0ODE_MASK)|CLR(SIM_SOPT5_LPUART1ODE_MASK)|      \
              CLR(SIM_SOPT5_LPUART0ODE_MASK)|                                   \
              CLR(SIM_SOPT5_LPUART1RXSRC_MASK)|SET(SIM_SOPT5_LPUART1TXSRC(0x00))|\
              CLR(SIM_SOPT5_LPUART0RXSRC_MASK)|SET(SIM_SOPT5_LPUART0TXSRC(0x00)),\
/* SOPT7   */ CLR(SIM_SOPT7_ADC0ALTTRGEN_MASK)|CLR(SIM_SOPT7_ADC0PRETRGSEL_MASK)|\
              SET(SIM_SOPT7_ADC0TRGSEL(0x00)),                                  \
/* SCGC4   */ CLR(SIM_SCGC4_SPI1_MASK)|CLR(SIM_SCGC4_SPI0_MASK)|                \
              CLR(SIM_SCGC4_CMP_MASK)|CLR(SIM_SCGC4_USBFS_MASK)|                \
              CLR(SIM_SCGC4_UART0_MASK)|CLR(SIM_SCGC4_VREF_MASK)|               \
              CLR(SIM_SCGC4_I2C1_MASK)|SET(SIM_SCGC4_I2C0_MASK),                \
/* SCGC5   */ SET(SIM_SCGC5_LPUART0_MASK)|CLR(SIM_SCGC5_LPUART1_MASK)|          \
              SET(SIM_SCGC5_PORTE_MASK)|SET(SIM_SCGC5_PORTD_MASK)|              \
              SET(SIM_SCGC5_PORTC_MASK)|SET(SIM_SCGC5_PORTB_MASK)|              \
              SET(SIM_SCGC5_PORTA_MASK)|CLR(SIM_SCGC5_FLEXIO_MASK)|             \
              CLR(SIM_SCGC5_LPTMR_MASK)|SET(SIM_SCGC5_SLCD_MASK),               \
/* SCGC6   */ CLR(SIM_SCGC6_DAC0_MASK)|                                         \
              SET(SIM_SCGC6_RTC_MASK)|SET(SIM_SCGC6_ADC0_MASK)|                 \
              CLR(SIM_SCGC6_TPM2_MASK)|CLR(SIM_SCGC6_TPM1_MASK)|                \
              SET(SIM_SCGC6_TPM0_MASK)|SET(SIM_SCGC6_PIT_MASK)|                 \
              CLR(SIM_SCGC6_I2S_MASK)|SET(SIM_SCGC6_DMAMUX_MASK)|               \
              SET(SIM_SCGC6_FTF_MASK),                                          \
/* SCGC7   */ SET(SIM_SCGC7_DMA_MASK),                                          \
/* CLKDIV1 */ SET(SIM_CLKDIV1_OUTDIV1(DIV_01))|SET(SIM_CLKDIV1_OUTDIV4(DIV_02)),\
}

/******************************************************************************
 * @brief   Define interrupt vectors.
 * @example 
 *          extern void uart_isr (void);       ///< uart isr prototype
 *          #undef  VECTOR_030
 *          #define VECTOR_030 uart_isr        ///< uart_isr interrupt vector re-definition
 ******************************************************************************/
extern void pit_isr(void);      ///< pit isr prototype (defined in pit.c)

#undef  VECTOR_038
#define VECTOR_038 pit_isr      ///< pit_isr interrupt vector re-definition

#undef  CONFIG_4
#define CONFIG_4 (pointer*)0xffff3bfe ///< FOPT - NMI is disabled
  
/*! @} End of frdm_slcd_test_config_def                                           */

#endif /* __APPCONFIG_ */
