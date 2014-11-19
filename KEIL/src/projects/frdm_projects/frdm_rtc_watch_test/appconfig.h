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
*//*! @addtogroup frdm_rtc_watch_test_config_def
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
#define SIM_MODULE_FRDM_RTC_WATCH_CONFIG                   /* all clocks on */  \
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
/* SOPT5   */ CLR(SIM_SOPT5_UART2ODE_MASK)|CLR(SIM_SOPT5_LPUART1ODE_MASK)|      \
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

/***************************************************************************//*!
 * @brief   SLCD use-case RTC configuration.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define RTC_MODULE_FRDM_RTC_WATCH_CONFIG                                      \
(tRTC){                                                                       \
/* TSR    */ 0l,                  /* value not used by the RTC_Init()     */  \
/* TPR    */ 0l,                  /* value not used by the RTC_Init()     */  \
/* TAR    */ 0l,                                                              \
/* TCR    */ SET(RTC_TCR_TCR(0x00))|SET(RTC_TCR_CIR(0x01)),                   \
/* CR     */ SET(RTC_CR_SC2P_MASK)|CLR(RTC_CR_SC4P_MASK)|                     \
             CLR(RTC_CR_SC8P_MASK)|CLR(RTC_CR_SC16P_MASK)|                    \
             CLR(RTC_CR_CLKO_MASK)|SET(RTC_CR_OSCE_MASK)|CLR(RTC_CR_UM_MASK)| \
             CLR(RTC_CR_SUP_MASK)|CLR(RTC_CR_WPE_MASK)|CLR(RTC_CR_SWR_MASK),  \
/* SR     */ SET(RTC_SR_TCE_MASK),                                            \
/* LR     */ SET(RTC_LR_LRL_MASK)|SET(RTC_LR_SRL_MASK)|SET(RTC_LR_CRL_MASK)|  \
             SET(RTC_LR_TCL_MASK)|(0x87),                                     \
/* IER    */ CLR(RTC_IER_WPON_MASK)|SET(RTC_IER_TSIE_MASK)|SET(RTC_IER_TAIE_MASK)|\
             CLR(RTC_IER_TOIE_MASK)|CLR(RTC_IER_TIIE_MASK),                   \
}

/* Buid data and time formatting                                              */
#define _SEC_   ((__TIME__[6]==' '?0:__TIME__[6]-'0')*10+(__TIME__[7]-'0'))
#define _MIN_   ((__TIME__[3]==' '?0:__TIME__[3]-'0')*10+(__TIME__[4]-'0'))
#define _HOUR_  ((__TIME__[0]==' '?0:__TIME__[0]-'0')*10+(__TIME__[1]-'0'))
#define _DAY_   ((__DATE__[4]==' '?0:__DATE__[4]-'0')*10+(__DATE__[5]-'0'))
#define _MON_   (__DATE__[2] == 'n' ? (__DATE__[1] == 'a' ? 1 : 6)            \
                :__DATE__[2] == 'b' ? 2                                       \
                :__DATE__[2] == 'r' ? (__DATE__[0] == 'M' ? 3 : 4)            \
                :__DATE__[2] == 'y' ? 5                                       \
                :__DATE__[2] == 'l' ? 7                                       \
                :__DATE__[2] == 'g' ? 8                                       \
                :__DATE__[2] == 'p' ? 9                                       \
                :__DATE__[2] == 't' ? 10                                      \
                :__DATE__[2] == 'v' ? 11 : 12)
#define _YEAR_  ((((__DATE__[7]-'0')*10+(__DATE__[8] -'0'))*10+               \
                   (__DATE__[9]-'0'))*10+(__DATE__[10]-'0'))
#define M_TAB   (_MON_ == 1 ? 6: _MON_ == 2 ? 2: _MON_ == 3 ? 2:              \
                 _MON_ == 4 ? 5: _MON_ == 5 ? 0: _MON_ == 6 ? 3:              \
                 _MON_ == 7 ? 5: _MON_ == 8 ? 1: _MON_ == 9 ? 4:              \
                 _MON_ == 10? 6: _MON_ == 11? 2: 4)
#define Y2000   (_YEAR_ % 2000)
#define _WDAY_  (((!(Y2000%4)) && (_MON_<3))?(Y2000+Y2000/4+M_TAB+_DAY_-1)%7: \
                                             (Y2000+Y2000/4+M_TAB+_DAY_)%7)

#define BUILD_DATE_TIME(t)                                                     \
{                                                                              \
  t.tm_sec = _SEC_; t.tm_min = _MIN_; t.tm_hour = _HOUR_; t.tm_mday = _DAY_;   \
  t.tm_mon = _MON_; t.tm_year= _YEAR_; t.tm_wday = _WDAY_;                     \
}

/******************************************************************************
 * @brief   Define interrupt vectors.
 * @example 
 *          extern void uart_isr (void);       ///< uart isr prototype
 *          #undef  VECTOR_030
 *          #define VECTOR_030 uart_isr        ///< uart_isr interrupt vector re-definition
 ******************************************************************************/
extern void rtc_isr(void);      ///< rtc isr prototype (defined in rtc.c)

#undef  VECTOR_036
#define VECTOR_036 rtc_isr      ///< rtc_isr alarm interrupt vector re-definition

#undef  VECTOR_037
#define VECTOR_037 rtc_isr      ///< rtc_isr second interrupt vector re-definition

#undef  CONFIG_4
#define CONFIG_4 (pointer*)0xffff3bfe ///< FOPT - NMI is disabled
/*! @} End of frdm_rtc_watch_test_config_def                                           */

#endif /* __APPCONFIG_ */
