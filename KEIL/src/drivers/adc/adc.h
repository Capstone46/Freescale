/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      adc.h
 * @version   1.0.4.0
 * @date      Jan-31-2013
 * @brief     ADC driver header file.
 *
 * Revision History:
 *  1.	15/01/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup adc_example0
 * @{
 * @par       Source code:
 * @include   adc0_test\adc0_test.c
 * @par       Appconfig.h:
 * @include   adc0_test\appconfig.h
 * 
 ******************************************************************************/
/*! @} End of adc_example0                                                    */
#ifndef __ADC_H
#define __ADC_H 

/******************************************************************************
 * ADC calibration data structure definition                                  *
 ******************************************************************************/
typedef struct { uint32 OFS, PG, MG, CLPD, CLPS, CLP[5], CLMD, CLMS, CLM[5]; } tADC_CALIB;
 
/******************************************************************************
 * definition configuration structure                                         *
 ******************************************************************************/
typedef struct { uint32 CFG1, CFG2, CV1, CV2, SC2, SC3; } tADC;
typedef struct { uint32 SC1; } tADC_CH;

/******************************************************************************
* Mode of ADC conversion factors definition
*
*//*! @addtogroup adc_mode_list
* @{
*******************************************************************************/
#define SE_8BIT        (uint8)0x00 ///< 8-bit single-ended conversion
#define SE_10BIT       (uint8)0x02 ///< 10-bit single-ended conversion
#define SE_12BIT       (uint8)0x01 ///< 12-bit single-ended conversion
#define SE_16BIT       (uint8)0x03 ///< 16-bit single-ended conversion
#define DIFF_9BIT      (uint8)0x00 ///< 8-bit differential conversion
#define DIFF_11BIT     (uint8)0x02 ///< 10-bit differential conversion
#define DIFF_13BIT     (uint8)0x01 ///< 12-bit differential conversion
#define DIFF_16BIT     (uint8)0x03 ///< 16-bit differential conversion
/*! @} End of adc_mode_list                                                   */

/******************************************************************************
* ADC hardware averaging factors definition
*
*//*! @addtogroup adc_avg_list
* @{
*******************************************************************************/
#define HWAVG_OFF   (uint8)0xff ///< hardware averaging disabled
#define HWAVG_4     (uint8)0x00 ///< 4 samples averaged.
#define HWAVG_8     (uint8)0x01 ///< 8 samples averaged.
#define HWAVG_16    (uint8)0x02 ///< 16 samples averaged.
#define HWAVG_32    (uint8)0x03 ///< 32 samples averaged.
/*! @} End of adc_avg_list                                                    */

/******************************************************************************
* ADC input channel definition
*
*//*! @addtogroup adc_channel
* @{
* This device contains up to 16 single ended channels tied to the package pins
* (number varies on each package).
*******************************************************************************/
#define DAD0          (uint8)0  ///< ADC0_DP0/ADC0_SE0 for DIFF = 0 (or ADC0_DP0 and ADC0_DM0 for DIFF = 1)   
#define DAD1          (uint8)1  ///< ADC0_DP1/ADC0_SE1 for DIFF = 0 (or ADC0_DP1 and ADC0_DM1 for DIFF = 1)
#define DAD2          (uint8)2  ///< ADC0_DP2/ADC0_SE2 for DIFF = 0 (or ADC0_DP2 and ADC0_DM2 for DIFF = 1)
#define DAD3          (uint8)3  ///< ADC0_DP3/ADC0_SE3 for DIFF = 0 (or ADC0_DP3 and ADC0_DM3 for DIFF = 1)
#define AD04          (uint8)4  ///< ADC0_DM0/ADC0_SE4a for MUXA (or ADC0_SE4b for MUXB)
#define AD05          (uint8)5  ///< ADC0_DM1/ADC0_SE5a for MUXA (or ADC0_SE5b for MUXB)
#define AD06          (uint8)6  ///< ADC0_DM2/ADC0_SE6a for MUXA (or ADC0_SE6b for MUXB)
#define AD07          (uint8)7  ///< ADC0_DM3/ADC0_SE7a for MUXA (or ADC0_SE7b for MUXB)
#define AD08          (uint8)8  ///< ADC0_SE8
#define AD09          (uint8)9  ///< ADC0_SE9
#define AD10          (uint8)10  ///<
#define AD11          (uint8)11  ///< ADC0_SE11
#define AD12          (uint8)12  ///< ADC0_SE12
#define AD13          (uint8)13  ///< ADC0_SE13
#define AD14          (uint8)14  ///< ADC0_SE14
#define AD15          (uint8)15  ///< ADC0_SE15
#define AD16          (uint8)16  ///<
#define AD17          (uint8)17  ///<
#define AD18          (uint8)18  ///<
#define AD19          (uint8)19  ///<
#define AD20          (uint8)20  ///<
#define AD21          (uint8)21  ///<
#define AD22          (uint8)22  ///<
#define AD23          (uint8)23  ///< ADC0_SE23/12-bit DAC0 Output
#define AD24          (uint8)24  ///<
#define AD25          (uint8)25  ///<
#define AD26          (uint8)26  ///< Temperature Sensor (S.E. or Diff)
#define AD27          (uint8)27  ///< Bandgap (S.E. or Diff) Note: If used, ensure bandgap buffer is enabled (PMC_REGSC[BGBE]) 
#define AD28          (uint8)28  ///<
#define AD29          (uint8)29  ///< VREFH (S.E. or Diff)
#define AD30          (uint8)30  ///< VREFL (only S.E.)
#define AD31          (uint8)31  ///< Module disabled
/*! @} End of adc_channel                                                     */

/******************************************************************************
* ADC default configurations used by ADC_init() function
*
*//*! @addtogroup adc_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief Default ADC config.
 * @details
 * - ADC disabled
 *****************************************************************************/
#define ADC_DEFAULT_CONFIG                                                    \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(0))|                 \
              CLR(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(0))|                \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              CLR(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  CLR(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(0)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              CLR(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(0)),                    \
}

#define ADC_DISABLE_CONFIG      ADC_DEFAULT_CONFIG 

/**************************************************************************/ /*!
 * @brief Selects n-bit fast mode with optional trigger and reference selection.
 * @details
 * - Normal power config (MUXb)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/2, considered as 12MHz max. ADCCLK)
 * - fast = short sample time, high speed sequence, shortest sample time
 * - optional trigger selection
 * - ADxxa channels selected
 * - internal voltage reference
 * - one conversion
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 * @param  trigsel - SWTRG or HWTRG 
 * @param  vrefsel - IREF or XREF
 *****************************************************************************/
#define ADC_FAST_CONFIG(nbit,trigsel,vrefsel)                                 \
        ADC_FAST_##trigsel##_##vrefsel##_CONFIG(nbit)


/**************************************************************************/ /*!
 * @brief Selects n-bit fast mode with SW trig. and int. reference.
 * @details
 * - Normal power config (MUXb)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/2, considered as 12MHz max. ADCCLK)
 * - fast = short sample time, high speed sequence, shortest sample time
 * - SW trigger
 * - ADxxa channels selected
 * - internal voltage reference
 * - one conversion
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 *****************************************************************************/
#define ADC_FAST_SWTRG_IREF_CONFIG(nbit)                                      \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(1))|                 \
              CLR(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(nbit))|             \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(3)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  CLR(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              CLR(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(0)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects n-bit fast mode with SW trig. and ext. reference.
 * @details
 * - Normal power config (MUXb)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/2, considered as 12MHz max. ADCCLK)
 * - fast = short sample time, high speed sequence, shortest sample time
 * - SW trigger
 * - ADxxa channels selected
 * - external voltage reference (VREFH and VREFL)
 * - one conversion
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 *****************************************************************************/
#define ADC_FAST_SWTRG_XREF_CONFIG(nbit)                                      \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(1))|                 \
              CLR(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(nbit))|             \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(3)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  CLR(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(0)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              CLR(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(0)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects n-bit fast mode with HW trig. and int. reference.
 * @details
 * - Normal power config (MUXb)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/2, considered as 12MHz max. ADCCLK)
 * - fast = short sample time, high speed sequence, shortest sample time
 * - HW trigger
 * - ADxxa channels selected
 * - internal voltage reference
 * - one conversion
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 *****************************************************************************/
#define ADC_FAST_HWTRG_IREF_CONFIG(nbit)                                      \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(1))|                 \
              CLR(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(nbit))|             \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(3)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  SET(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              CLR(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(0)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects n-bit fast mode with HW trig. and ext. reference.
 * @details
 * - Normal power config (MUXb)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/2, considered as 12MHz max. ADCCLK)
 * - fast = short sample time, high speed sequence, shortest sample time
 * - HW trigger
 * - ADxxa channels selected
 * - external voltage reference (VREH and VREFL)
 * - one conversion
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 *****************************************************************************/
#define ADC_FAST_HWTRG_XREF_CONFIG(nbit)                                      \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(1))|                 \
              CLR(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(nbit))|             \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(3)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  SET(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(0)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              CLR(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(0)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects n-bit fast mode with SW trig. and int. reference.
 * @details
 * - Normal power config (MUXb)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/2, considered as 12MHz max. ADCCLK)
 * - fast = short sample time, high speed sequence, shortest sample time
 * - SW trigger
 * - ADxxb channels selected
 * - internal voltage reference
 * - one conversion
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 *****************************************************************************/
#define ADC_FAST_SWTRG_IREF_MUXB_CONFIG(nbit)                                 \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(1))|                 \
              CLR(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(nbit))|             \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(3)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  CLR(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              CLR(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(0)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects n-bit fast mode with HW trig. and ext. reference.
 * @details
 * - Normal power config (MUXb)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/2, considered as 12MHz max. ADCCLK)
 * - fast = short sample time, high speed sequence, shortest sample time
 * - HW trigger
 * - ADxxb channels selected
 * - external voltage reference (VREFH and VREFL)
 * - one conversion
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 *****************************************************************************/
#define ADC_FAST_HWTRG_XREF_MUXB_CONFIG(nbit)                                 \
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
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(0)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              CLR(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(0)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects n-bit precise mode with optional trigger and ref. selection.
 * @details
 * - Normal power config (MUXa)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - precise = long sample time, high speed sequence, longest sample time
 * - SW trigger
 * - ADxxa channels selected
 * - internal voltage reference
 * - one conversion (also include set of conversions when AVG enable)
 * - hardware avegaring enabled
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 * @param  trigsel - SWTRG or HWTRG 
 * @param  vrefsel - IREF or XREF
 * @param  avgsampl - number of samples to be averaged (@ref adc_avg_list)
 *****************************************************************************/
#define ADC_PRECISE_CONFIG(nbit,trigsel,vrefsel,avgsampl)                      \
        ADC_PRECISE_##trigsel##_##vrefsel##_CONFIG(nbit,avgsampl)


/**************************************************************************/ /*!
 * @brief Selects n-bit precise mode with SW trig., int. reference and avg func.
 * @details
 * - Normal power config (MUXa)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - precise = long sample time, high speed sequence, longest sample time
 * - SW trigger
 * - ADxxa channels selected
 * - internal voltage reference
 * - one conversion (also include set of conversions when AVG enable)
 * - hardware avegaring enabled
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 * @param  avgsampl - number of samples to be averaged (@ref adc_avg_list)
 *****************************************************************************/
#define ADC_PRECISE_SWTRG_IREF_CONFIG(nbit,avgsampl)                          \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(3))|                 \
              SET(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(nbit))|             \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  CLR(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              SET(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(avgsampl)),             \
}

/**************************************************************************/ /*!
 * @brief Selects n-bit precise mode with SW trig., ext. reference and avg func.
 * @details
 * - Normal power config (MUXa)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - precise = long sample time, high speed sequence, longest sample time
 * - SW trigger
 * - ADxxa channels selected
 * - external voltage reference
 * - one conversion (also include set of conversions when AVG enable)
 * - hardware avegaring enabled
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 * @param  avgsampl - number of samples to be averaged (@ref adc_avg_list)
 *****************************************************************************/
#define ADC_PRECISE_SWTRG_XREF_CONFIG(nbit,avgsampl)                          \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(3))|                 \
              SET(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(nbit))|             \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  CLR(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(0)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              SET(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(avgsampl)),             \
}

/**************************************************************************/ /*!
 * @brief Selects n-bit precise mode with HW trig., int. reference and avg func.
 * @details
 * - Normal power config (MUXa)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - precise = long sample time, high speed sequence, longest sample time
 * - HW trigger
 * - ADxxa channels selected
 * - internal voltage reference
 * - one conversion (also include set of conversions when AVG enable)
 * - hardware avegaring enabled
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 * @param  avgsampl - number of samples to be averaged (@ref adc_avg_list)
 *****************************************************************************/
#define ADC_PRECISE_HWTRG_IREF_CONFIG(nbit,avgsampl)                          \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(3))|                 \
              SET(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(nbit))|             \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  SET(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              SET(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(avgsampl)),             \
}

/**************************************************************************/ /*!
 * @brief Selects n-bit precise mode with HW trig., ext. reference and avg func.
 * @details
 * - Normal power config (MUXa)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - precise = long sample time, high speed sequence, longest sample time
 * - HW trigger
 * - ADxxa channels selected
 * - external voltage reference
 * - one conversion (also include set of conversions when AVG enable)
 * - hardware avegaring enabled
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 * @param  avgsampl - number of samples to be averaged (@ref adc_avg_list)
 *****************************************************************************/
#define ADC_PRECISE_HWTRG_XREF_CONFIG(nbit,avgsampl)                          \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(3))|                 \
              SET(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(nbit))|             \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  SET(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(0)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              SET(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(avgsampl)),             \
}

/**************************************************************************/ /*!
 * @brief Selects n-bit precise mode with SW trig., int. reference and avg func.
 * @details
 * - Normal power config (MUXb)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - precise = long sample time, high speed sequence, longest sample time
 * - SW trigger
 * - ADxxb channels selected
 * - internal voltage reference
 * - one conversion (also include set of conversions when AVG enable)
 * - hardware avegaring enabled
 * @param  nbit - number of bits to be converted (@ref adc_mode_list)
 * @param  avgsampl - number of samples to be averaged (@ref adc_avg_list)
 *****************************************************************************/
#define ADC_PRECISE_SWTRG_IREF_MUXB_CONFIG(nbit,avgsampl)                     \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(3))|                 \
              SET(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(nbit))|             \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  CLR(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              SET(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(avgsampl)),             \
}

/**************************************************************************/ /*!
 * @brief Provide shortest sampled 16-bit SW triggered conversion with internal
 *        reference (MUXa).
 * @details
 * - Normal power config (MUXA)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/2)
 * - short sample time + shortest sample time
 * - 16-bit conversion mode
 * - SW trigger
 * - internal reference
 * - hardware avegaring disabled
 *****************************************************************************/
#define ADC_MODULE_DIV1_16B_SHORTEST_SWTRG_IREF_CONFIG                        \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(1))|                 \
              CLR(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(3))|                \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(3)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  CLR(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              CLR(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(0)),                    \
}

/**************************************************************************/ /*!
 * @brief Provide shortest sampled 16-bit SW triggered conversion with internal
 *        reference (MUXb).
 * @details
 * - Normal power config (MUXB)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/2)
 * - short sample time + shortest sample time
 * - 16-bit conversion mode
 * - SW trigger
 * - ADxxb channels selected
 * - internal reference
 * - hardware avegaring disabled
 *****************************************************************************/
#define ADC_MODULE_DIV1_16B_MUXB_SHORTEST_SWTRG_IREF_CONFIG                   \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(1))|                 \
              CLR(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(3))|                \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  SET(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(3)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  CLR(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              CLR(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(0)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects 16-bit software triggered mode with internal voltage reference.
 * @details
 * - Normal power config (MUXa)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - long sample time
 * - 16-bit conversion mode
 * - SW trigger
 * - ADxxa channels selected
 * - internal reference
 * - continuous conversion disabled
 * - hardware avegaring enabled with 32 samples
 *****************************************************************************/
#define ADC_MODULE_16B_SWTRG_IREF_AVG32_CONFIG                                \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(3))|                 \
              SET(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(3))|                \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  CLR(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              SET(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(3)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects 16-bit software triggered mode with internal voltage reference.
 * @details
 * - Normal power config (MUXb)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - long sample time
 * - 16-bit conversion mode
 * - SW trigger
 * - ADxxb channels selected
 * - internal reference
 * - continuous conversion disabled
 * - hardware avegaring enabled with 32 samples
 *****************************************************************************/
#define ADC_MODULE_16B_SWTRG_IREF_AVG32_MUXB_CONFIG                           \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(3))|                 \
              SET(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(3))|                \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  SET(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  CLR(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              SET(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(3)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects 16-bit software triggered mode with internal voltage reference.
 * @details
 * - Normal power config (MUXa)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - long sample time
 * - 16-bit conversion mode
 * - SW trigger
 * - ADxxa channels selected
 * - external reference
 * - continuous conversion disabled
 * - hardware avegaring enabled with 32 samples
 *****************************************************************************/
#define ADC_MODULE_16B_SWTRG_XREF_AVG32_CONFIG                                \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(3))|                 \
              SET(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(3))|                \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  CLR(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(0)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              SET(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(3)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects 16-bit hardware triggered mode with internal voltage reference.
 * @details
 * - Normal power config (MUXA)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - long sample time
 * - 16-bit conversion mode
 * - HW trigger
 * - ADxxa channels selected
 * - internal reference
 * - continuous conversion disabled
 * - hardware avegaring enabled with 32 samples
 *****************************************************************************/
#define ADC_MODULE_16B_HWTRG_IREF_AVG32_CONFIG                                \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(3))|                 \
              SET(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(3))|                \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  SET(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              SET(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(3)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects 16-bit hardware triggered mode with internal voltage reference.
 * @details
 * - Normal power config (MUXB)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - long sample time
 * - 16-bit conversion mode
 * - HW trigger
 * - ADxxb channels selected
 * - internal reference
 * - continuous conversion disabled
 * - hardware avegaring enabled with 4 samples
 *****************************************************************************/
#define ADC_MODULE_16B_HWTRG_IREF_AVG4_MUXB_CONFIG                            \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(3))|                 \
              SET(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(3))|                \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  SET(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  SET(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              SET(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(0)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects 16-bit hardware triggered mode with internal voltage reference.
 * @details
 * - Normal power config (MUXB)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - long sample time
 * - 16-bit conversion mode
 * - HW trigger
 * - ADxxb channels selected
 * - internal reference
 * - continuous conversion disabled
 * - hardware avegaring enabled with 32 samples
 *****************************************************************************/
#define ADC_MODULE_16B_HWTRG_IREF_AVG32_MUXB_CONFIG                           \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(3))|                 \
              SET(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(3))|                \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  SET(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  SET(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(1)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              SET(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(3)),                    \
}

/**************************************************************************/ /*!
 * @brief Selects 16-bit hardware triggered mode with external voltage reference.
 * @details
 * - Normal power config (MUXB)
 * - Input clock is BUSCLK
 * - Clock divider set to 2 (ADCLK = BUSCLK/8)
 * - long sample time
 * - 16-bit conversion mode
 * - HW trigger
 * - ADxxb channels selected
 * - external reference
 * - continuous conversion disabled
 * - hardware avegaring enabled with 32 samples
 *****************************************************************************/
#define ADC_MODULE_16B_HWTRG_XREF_AVG32_CONFIG                                \
(tADC){                                                                       \
/* CFG1   */  CLR(ADC_CFG1_ADLPC_MASK)|SET(ADC_CFG1_ADIV(3))|                 \
              SET(ADC_CFG1_ADLSMP_MASK)|SET(ADC_CFG1_MODE(3))|                \
              SET(ADC_CFG1_ADICLK(0)),                                        \
/* CFG2   */  CLR(ADC_CFG2_MUXSEL_MASK)|CLR(ADC_CFG2_ADACKEN_MASK)|           \
              SET(ADC_CFG2_ADHSC_MASK)|SET(ADC_CFG2_ADLSTS(0)),               \
/* CV1    */  0l,                                                             \
/* CV2    */  0l,                                                             \
/* SC2    */  SET(ADC_SC2_ADTRG_MASK)|CLR(ADC_SC2_ACFE_MASK)|                 \
              CLR(ADC_SC2_ACFGT_MASK)|CLR(ADC_SC2_ACREN_MASK)|                \
              CLR(ADC_SC2_DMAEN_MASK)|SET(ADC_SC2_REFSEL(0)),                 \
/* SC3    */  CLR(ADC_SC3_CAL_MASK)|CLR(ADC_SC3_ADCO_MASK)|                   \
              SET(ADC_SC3_AVGE_MASK)|SET(ADC_SC3_AVGS(3)),                    \
}
/*! @} End of adc_config                                                      */

/******************************************************************************
* ADC channel configurations used by ADC_init() function
*
*//*! @addtogroup adc_chan_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief Selects single ended channel mode with IRQ enabled.
 *****************************************************************************/
#define ADC_CH_SE_IRQ_CONFIG(inp)     /* single ended, interrupt enabled  */  \
(tADC_CH){                                                                    \
/* SC1    */ SET(ADC_SC1_AIEN_MASK)|CLR(ADC_SC1_DIFF_MASK)|inp,               \
}

/**************************************************************************/ /*!
 * @brief Selects single ended channel mode in polling mode.
 *****************************************************************************/
#define ADC_CH_SE_POLL_CONFIG(inp)    /* single ended, polling mode       */  \
(tADC_CH){                                                                    \
/* SC1    */ CLR(ADC_SC1_AIEN_MASK)|CLR(ADC_SC1_DIFF_MASK)|inp,               \
}

/**************************************************************************/ /*!
 * @brief Selects differential channel mode with IRQ enabled.
 *****************************************************************************/
#define ADC_CH_DI_IRQ_CONFIG(inp)     /* differential, interrupt enabled  */  \
(tADC_CH){                                                                    \
/* SC1    */ SET(ADC_SC1_AIEN_MASK)|SET(ADC_SC1_DIFF_MASK)|inp,               \
}

/**************************************************************************/ /*!
 * @brief Selects differential channel mode in polling mode.
 *****************************************************************************/
#define ADC_CH_DI_POLL_CONFIG(inp)    /* differential, polling mode       */  \
(tADC_CH){                                                                    \
/* SC1    */ CLR(ADC_SC1_AIEN_MASK)|SET(ADC_SC1_DIFF_MASK)|inp,               \
}

/**************************************************************************/ /*!
 * @brief Channel disabled.
 *****************************************************************************/
#define ADC_CH_DISABLE    			  /* disable channel       			  */  \
(tADC_CH){                                                                    \
/* SC1    */ CLR(ADC_SC1_AIEN_MASK)|CLR(ADC_SC1_DIFF_MASK)|AD31,              \
}
/*! @} End of adc_chan_config                                                */

/******************************************************************************
* ADC callback used by ADC_init() function
*
*//*! @addtogroup adc_callback
* @{
*******************************************************************************/
/*! @brief ADC_CALLBACK type declaration                                      */
typedef enum {CHA_CALLBACK=1, CHB_CALLBACK=2 } ADC_CALLBACK_TYPE;
/*! ADC_CALLBACK function declaration                                         */
typedef void (*ADC_CALLBACK)(ADC_CALLBACK_TYPE type, int16 result);
/*! @} End of adc_callback                                                    */

/******************************************************************************
* ADC function and macro definitions
*
*//*! @addtogroup adc_macro
* @{
*******************************************************************************/
/* ADC macro definitions                                                      */
/***************************************************************************//*!
 * @brief   Macro select input ADC channel for measurement.
 * @param   module  - ADC0
 * @param   ch      - CHA|CHB
 * @param   inp     - AD0..AD31
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define ADC_InChanSel(module,ch,inp) module##_##ch##_Start(inp)
 
#define ADC0_CHA_Start(inp)     REG_SetVal(ADC0_SC1A, ADC_SC1_ADCH,inp)
#define ADC0_CHB_Start(inp)     REG_SetVal(ADC0_SC1B, ADC_SC1_ADCH,inp)
/***************************************************************************//*!
 * @brief   Macro starts ADC conversion on given input.
 * @param   module  - ADC0
 * @param   ch      - CHA|CHB
 * @param   inp     - AD0..AD31
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define ADC_Start(module,ch,inp) module##_##ch##_Start(inp)

#define ADC0_CHA_Ready           (ADC0_SC1A & ADC_SC1_COCO_MASK)
#define ADC0_CHB_Ready           (ADC0_SC1B & ADC_SC1_COCO_MASK)
/***************************************************************************//*!
 * @brief   Macro returns ADC conversion status (COCO flag)
 * @param   module  - ADC0
 * @param   ch      - CHA|CHB
 * @return  TRUE    - conversion completed
 * @return  FALSE   - conversion pending
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define ADC_Ready(module,ch)     module##_##ch##_Ready

#define ADC0_CHA_Read            (uint16)ADC0_RA
#define ADC0_CHB_Read            (uint16)ADC0_RB
/***************************************************************************//*!
 * @brief   Macro returns ADC result register value.
 * @param   module  - ADC0
 * @param   ch      - CHA|CHB
 * @return  result register value
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define ADC_Read(module,ch)      module##_##ch##_Read

/* Function redefinition                                                      */
/***************************************************************************//*!
 * @brief   ADC initialization function.
 * @param   module  - ADC0
 * @param   cfg     - @ref adc_config.
 * @param   CHA     - @ref adc_chan_config 
 * @param   CHB     - @ref adc_chan_config 
 * @param   ip      - interrupt priority 0..3
 * @param   callback- pointer to ADC_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define ADC_Init(module,cfg,CHA,CHB,ip,callback)  module##_Init(cfg,CHA,CHB,ip,callback)

/***************************************************************************//*!
 * @brief   ADC calibration function. Function performs calibration and updates
 *          calibration registers.
 * @param   module  - ADC0
 * @param   cfg     - @ref adc_config.
 * @param   *pCALIB - pointer to tCALIB data structure.
 * @return  0 - SUCCESS 
 * @return  1 - ERROR
 * @note    Implemented as function call.
 ******************************************************************************/
#define ADC_ExecCalib(module,cfg,pCALIB)          module##_ExecCalib(cfg,pCALIB)

/***************************************************************************//*!
 * @brief   Function updates calibration registers of the ADC.
 * @param   module  - ADC0
 * @param   *pCALIB - pointer to tCALIB data structure.
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define ADC_SaveCalib(module,pCALIB)              module##_SaveCalib(pCALIB)
/*! @} End of adc_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/    
 int  ADC0_ExecCalib (tADC adc, tADC_CALIB *pCALIB);
 void ADC0_SaveCalib (tADC_CALIB *pCALIB);
 void ADC0_Init (tADC adc, tADC_CH CHA, tADC_CH CHB, uint8 ip, ADC_CALLBACK pCallback);
   
#endif /* __ADC_H */ 
