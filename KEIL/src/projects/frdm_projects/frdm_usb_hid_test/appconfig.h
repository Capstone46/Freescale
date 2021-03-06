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
*//*! @addtogroup frdm_usb_hid_test_config_def
* @{
*******************************************************************************/

/***************************************************************************//*!
 * @brief   Define processor device.
 * @details Supported devices - MCU_MKL43Z256  (MCU_MKL46Z256 temporarily used)
 ******************************************************************************/
#define MCU_MKL43Z256

  
/***************************************************************************//*!
 * @brief   Define accelerometer settings.
 * @details Tolerance (dead input range) and pointer step 
 ******************************************************************************/   
#define TOLERANCE            2000
#define STEP_SIZE            5         /* max 120 pixels in one step */

/**************************************************************************/ /*!
 * @brief   All peripherals enabled configuration.
 *****************************************************************************/
#define SIM_MODULE_FRDM_USB_VCOM_CONFIG                    /* all clocks on */  \
(tSIM){                                                                         \
/* SOPT1   */ SET(SIM_SOPT1_USBREGEN_MASK)|CLR(SIM_SOPT1_USBSSTBY_MASK)|        \
              CLR(SIM_SOPT1_USBVSTBY_MASK)|SET(SIM_SOPT1_OSC32KSEL(0x00))|      \
              SET(SIM_SOPT1_OSC32KOUT(0x00)),                                   \
/* SOPT1CFG*/ CLR(SIM_SOPT1CFG_USSWE_MASK)|CLR(SIM_SOPT1CFG_UVSWE_MASK)|        \
              CLR(SIM_SOPT1CFG_URWE_MASK),                                      \
/* SOPT2   */ SET(SIM_SOPT2_LPUART1SRC(0x01))|                                  \
              SET(SIM_SOPT2_LPUART0SRC(0x01))|SET(SIM_SOPT2_TPMSRC(0x01))|      \
              SET(SIM_SOPT2_FLEXIOSRC(0x01))|SET(SIM_SOPT2_USBSRC_MASK)|        \
              SET(SIM_SOPT2_CLKOUTSEL(0x02))|CLR(SIM_SOPT2_RTCCLKOUTSEL_MASK),  \
/* SOPT4   */ CLR(SIM_SOPT4_TPM2CLKSEL_MASK)|CLR(SIM_SOPT4_TPM1CLKSEL_MASK)|    \
              CLR(SIM_SOPT4_TPM0CLKSEL_MASK)|CLR(SIM_SOPT4_TPM2CH0SRC_MASK)|    \
              CLR(SIM_SOPT4_TPM1CH0SRC_MASK),                                   \
/* SOPT5   */ CLR(SIM_SOPT5_UART0ODE_MASK)|CLR(SIM_SOPT5_LPUART1ODE_MASK)|      \
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


/**************************************************************************/ /*!
 * @brief Configures pin to Alternative 6 (GPIO) mode with high drive strength.
 *****************************************************************************/
#define PORT_MODULE_ALT5_PULLUP_MODE       /* ALT6 push-pull mode high strength  */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(5))|SET(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|SET(PORT_PCR_PS_MASK),                    \
}


/**************************************************************************/ /*!
 * @brief Configures pin to Alternative 6 (GPIO) mode with high drive strength.
 *****************************************************************************/
#define PORT_MODULE_ALT6_PULLUP_MODE       /* ALT6 push-pull mode high strength  */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(6))|SET(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/******************************************************************************
 * @brief   Define interrupt vectors.
 * @example 
 *          extern void uart_isr (void); ///< uart isr prototype
 *          #undef  VECTOR_030
 *          #define VECTOR_030 uart_isr  ///< uart_isr interrupt vector re-definition
 ******************************************************************************/
extern void pit_isr (void);       ///< usb isr prototype
extern void USB_ISR (void);       ///< usb isr prototype

#undef  VECTOR_038
#define VECTOR_038 pit_isr        ///< pit_isr interrupt vector re-definition

#undef  VECTOR_040
#define VECTOR_040 USB_ISR        ///< USB interrupt vector re-definition

#undef  CONFIG_4
#define CONFIG_4		(pointer*)0xffff3ffe
/*! @} End of frdm_usb_hid_test_config_def                                           */

#endif /* __APPCONFIG_ */
