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
*//*! @addtogroup frdm_light_sensor_test_config_def
* @{
*******************************************************************************/

/***************************************************************************//*!
 * @brief   Define processor device.
 * @details Supported devices - MCU_MKL43Z256  (MCU_MKL46Z256 temporarily used)
 ******************************************************************************/
#define MCU_MKL43Z256

/**************************************************************************/ /*!
 * @brief Selects n-bit fast mode with HW trig. and ext. reference.
 * @details
 * - A power config
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/2, considered as 12MHz max. ADCCLK)
 * - fast = short sample time, high speed sequence, shortest sample time
 * - HW trigger
 * - ADxxb channels selected
 * - internal voltage reference (VDDA and VSSA)
 * - one conversion
 * - DMA transfer enabled
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 *****************************************************************************/
#define ADC_FAST_MUXB_HWTRG_IREF_DMA_CONFIG(nbit)                             \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(1))|                 \
              CLR(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(nbit))|             \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  SET(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(3)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  SET(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              SET(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              CLR(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(0)),                    \
}

/**************************************************************************/ /*!
 * @brief Edge aligned timer mode with source clock divided by 32.
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY32_EDGEALIGN_CONFIG                           \
(tTPM)  {                                                                     \
/* SC      */ CLR(TPM_SC_DMA_MASK)|CLR(TPM_SC_TOIE_MASK)|                     \
              CLR(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0x05)),\
/* CONF    */ SET(TPM_CONF_TRGSEL(0x0))|CLR(TPM_CONF_CROT_MASK)|              \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/******************************************************************************
 * @brief   Define interrupt vectors.
 * @example 
 *          extern void uart_isr (void);       ///< uart isr prototype
 *          #undef  VECTOR_030
 *          #define VECTOR_030 uart_isr        ///< uart_isr interrupt vector re-definition
 ******************************************************************************/
extern void dma0_isr(void);     ///< dma0 isr prototype (defined in dma.c)
extern void dma1_isr(void);     ///< dma1 isr prototype (defined in dma.c)
extern void adc0_isr (void);    ///< adc isr prototype (defined in adc.c)
extern void pit_isr(void);      ///< pit isr prototype (defined in pit.c)

#undef  VECTOR_016
#define VECTOR_016 dma0_isr     ///< dma0_isr interrupt vector re-definition

#undef  VECTOR_017
#define VECTOR_017 dma1_isr			///< dma1_isr interrupt vector re-definition

#undef  VECTOR_031
#define VECTOR_031 adc0_isr     ///< adc0_isr interrupt vector re-definition

#undef  VECTOR_038
#define VECTOR_038 pit_isr      ///< pit_isr interrupt vector re-definition

#undef  CONFIG_4
#define CONFIG_4 (pointer*)0xffff3bfe ///< FOPT - NMI is disabled
/*! @} End of frdm_light_sensor_test_config_def                                           */

#endif /* __APPCONFIG_ */
