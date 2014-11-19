/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      cmp.h
 * @version   1.0.5.0
 * @date      Jan-22-2013
 * @brief     Analog comparator (CMP) driver header file.
 *
 * Revision History:
 *  1.	15/01/2013   B34185   Initially written for Kinetis L
 *  2.	26/03/2014   B34185   comparator callback re-defined
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup cmp_example0
 * @{
 * @par       Source code:
 * @include   cmp0_test\cmp_test.c
 * @par       Appconfig.h:
 * @include   cmp0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of cmp_example0                                                     */
#ifndef __CMP_H
#define __CMP_H 

/******************************************************************************
 * definition configuration structure                                         *
 ******************************************************************************/
typedef struct { uint8 CR0, CR1, FPR, SCR, DACCR; } tCMP;

/******************************************************************************
* Comparator input connections for use in CMP_Init() macro.
*
*//*! @addtogroup cmp_channel
* @{
*******************************************************************************/
#define IN0          (uint8)0   ///< input CMP0_IN0
#define IN1          (uint8)1   ///< input CMP0_IN1
#define IN2          (uint8)2   ///< input CMP0_IN2
#define IN3          (uint8)3   ///< input CMP0_IN3
#define IN4          (uint8)4   ///< input CMP0_IN4/12-bit DAC0 reference
#define IN5          (uint8)5   ///< input CMP0_IN5
#define IN6          (uint8)6   ///< Bandgap
#define IN7_DAC      (uint8)7   ///< 6-bit DAC0 reference
/*! @} End of cmp_channel                                                     */

/******************************************************************************
* Comparator default configurations used by CMP_init() function
*
*//*! @addtogroup cmp_config
* @{
*******************************************************************************/

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - disabled mode
  *****************************************************************************/
#define CMP_DISABLE_CONFIG()                                                  \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(0)) |SET(CMP_CR0_HYSTCTR(0)),            \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |CLR(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |CLR(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

// Internally driven modes
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - continuous mode
  * - filter sample count set to 0
  * - sampling disabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_CONTINUOUS_MODE_CONFIG()                                         \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_CONFIG(0,0) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode internally driven
  * - filter sample count set to 1
  * - sampling disabled
  * - filter disabled
  * @param   samp_per       select one sample periode 1 to 255
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_NOFILTER_MODE_CONFIG(samp_per)                    \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_CONFIG(1,samp_per) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode internally driven
  * - filter sample count set by parameter flt_count 
  * - sampling disabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_FILTER_MODE_CONFIG(flt_count,samp_per)           \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+INV
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - continuous mode
  * - filter sample count set to 0
  * - sampling disabled
  * - inverted output enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_CONTINUOUS_MODE_INV_CONFIG()                                     \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_INV_CONFIG(0,0) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode internally driven
  * - filter sample count set to 1
  * - sampling disabled
  * - inverted output enabled
  * - filter disabled
  * @param   samp_per       select one sample periode 1 to 255
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_NOFILTER_MODE_INV_CONFIG(samp_per)                \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_INV_CONFIG(1,samp_per) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode internally driven
  * - filter sample count set by parameter flt_count 
  * - sampling disabled
  * - inverted output enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_FILTER_MODE_INV_CONFIG(flt_count,samp_per)       \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              SET(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+IER
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - continuous mode
  * - filter sample count set to 0
  * - sampling disabled
  * - rising edge interrupt enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_CONTINUOUS_MODE_IER_CONFIG()                                     \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_IER_CONFIG(0,0) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode internally driven
  * - filter sample count set to 1
  * - sampling disabled
  * - rising edge interrupt enabled
  * - filter disabled
  * @param   samp_per       select one sample periode 1 to 255
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_NOFILTER_MODE_IER_CONFIG(samp_per)                \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_IER_CONFIG(1,samp_per) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode internally driven
  * - filter sample count set by parameter flt_count 
  * - sampling disabled
  * - rising edge interrupt enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_FILTER_MODE_IER_CONFIG(flt_count,samp_per)       \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+IEF
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - continuous mode
  * - filter sample count set to 0
  * - sampling disabled
  * - falling edge interrupt enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_CONTINUOUS_MODE_IEF_CONFIG()                                     \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_IEF_CONFIG(0,0) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode internally driven
  * - filter sample count set to 1
  * - sampling disabled
  * - falling edge interrupt enabled
  * - filter disabled
  * @param   samp_per       select one sample periode 1 to 255
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_NOFILTER_MODE_IEF_CONFIG(samp_per)                \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_IEF_CONFIG(1,samp_per) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode internally driven
  * - filter sample count set by parameter flt_count 
  * - sampling disabled
  * - falling edge interrupt enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_FILTER_MODE_IEF_CONFIG(flt_count,samp_per)       \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+IERF
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - continuous mode
  * - filter sample count set to 0
  * - sampling disabled
  * - both edges interrupt enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_CONTINUOUS_MODE_IERF_CONFIG()                                    \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_IERF_CONFIG(0,0) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode internally driven
  * - filter sample count set to 1
  * - sampling disabled
  * - both edges interrupt enabled
  * - filter disabled
  * @param   samp_per       select one sample periode 1 to 255
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_NOFILTER_MODE_IERF_CONFIG(samp_per)               \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_IERF_CONFIG(1,samp_per)
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode internally driven
  * - filter sample count set by parameter flt_count 
  * - sampling disabled
  * - both edges interrupt enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_FILTER_MODE_IERF_CONFIG(flt_count,samp_per)      \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+DMA
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - continuous mode
  * - filter sample count set to 0
  * - sampling disabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_CONTINUOUS_MODE_DMA_CONFIG()                                     \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_DMA_CONFIG(0,0) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode internally driven
  * - filter sample count set to 1
  * - sampling disabled
  * - filter disabled
  * @param   samp_per       select one sample periode 1 to 255
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_NOFILTER_MODE_DMA_CONFIG(samp_per)                \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_DMA_CONFIG(1,samp_per) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode internally driven
  * - filter sample count set by parameter flt_count 
  * - sampling disabled
  * - DMA enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_FILTER_MODE_DMA_CONFIG(flt_count,samp_per)       \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  SET(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

// Internally driven modes with DAC enabled
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - continuous mode
  * - filter sample count set to 0
  * - sampling disabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_CONTINUOUS_MODE_DAC_CONFIG(dac_voltage)                          \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_DAC_CONFIG(0,0,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode internally driven
  * - filter sample count set to 1
  * - sampling disabled
  * - filter disabled
  * - DAC enabled
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_NOFILTER_MODE_DAC_CONFIG(samp_per,dac_voltage)    \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_DAC_CONFIG(1,samp_per,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode internally driven
  * - filter sample count set by parameter flt_count 
  * - sampling disabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_FILTER_MODE_DAC_CONFIG(flt_count,samp_per,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+INV
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - continuous mode
  * - filter sample count set to 0
  * - sampling disabled
  * - inverted output enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_CONTINUOUS_MODE_INV_DAC_CONFIG(dac_voltage)                      \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_INV_DAC_CONFIG(0,0,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode internally driven
  * - filter sample count set to 1
  * - sampling disabled
  * - inverted output enabled
  * - filter disabled
  * - DAC enabled
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_NOFILTER_MODE_INV_DAC_CONFIG(samp_per,dac_voltage)\
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_INV_DAC_CONFIG(1,samp_per,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode internally driven
  * - filter sample count set by parameter flt_count 
  * - sampling disabled
  * - inverted output enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_FILTER_MODE_INV_DAC_CONFIG(flt_count,samp_per,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              SET(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+IER
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - continuous mode
  * - filter sample count set to 0
  * - sampling disabled
  * - rising edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_CONTINUOUS_MODE_IER_DAC_CONFIG(dac_voltage)                      \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_IER_DAC_CONFIG(0,0,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode internally driven
  * - filter sample count set to 1
  * - sampling disabled
  * - rising edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_NOFILTER_MODE_IER_DAC_CONFIG(samp_per,dac_voltage)\
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_IER_DAC_CONFIG(1,samp_per,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode internally driven
  * - filter sample count set by parameter flt_count 
  * - sampling disabled
  * - rising edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_FILTER_MODE_IER_DAC_CONFIG(flt_count,samp_per,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+IEF
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - continuous mode
  * - filter sample count set to 0
  * - sampling disabled
  * - falling edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_CONTINUOUS_MODE_IEF_DAC_CONFIG(dac_voltage)                      \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_IEF_DAC_CONFIG(0,0,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode internally driven
  * - filter sample count set to 1
  * - sampling disabled
  * - falling edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_NOFILTER_MODE_IEF_DAC_CONFIG(samp_per,dac_voltage)\
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_IEF_DAC_CONFIG(1,samp_per,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode internally driven
  * - filter sample count set by parameter flt_count 
  * - sampling disabled
  * - falling edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_FILTER_MODE_IEF_DAC_CONFIG(flt_count,samp_per,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+IERF
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - continuous mode
  * - filter sample count set to 0
  * - sampling disabled
  * - both edges interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_CONTINUOUS_MODE_IERF_DAC_CONFIG(dac_voltage)                     \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_IERF_DAC_CONFIG(0,0,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode internally driven
  * - filter sample count set to 1
  * - sampling disabled
  * - both edges interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_NOFILTER_MODE_IERF_DAC_CONFIG(samp_per,dac_voltage)\
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_IERF_DAC_CONFIG(1,samp_per,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode internally driven
  * - filter sample count set by parameter flt_count 
  * - sampling disabled
  * - both edges interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_FILTER_MODE_IERF_DAC_CONFIG(flt_count,samp_per,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+DMA
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - continuous mode
  * - filter sample count set to 0
  * - sampling disabled
  * - DMA enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_CONTINUOUS_MODE_DMA_DAC_CONFIG(dac_voltage)                      \
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_DMA_DAC_CONFIG(0,0,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode internally driven
  * - filter sample count set to 1
  * - sampling disabled
  * - DMA enabled
  * - filter disabled
  * - DAC enabled
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_NOFILTER_MODE_DMA_DAC_CONFIG(samp_per,dac_voltage)\
        HSCMP_SAMPLED_INTDRV_FILTER_MODE_DMA_DAC_CONFIG(1,samp_per,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode internally driven
  * - filter sample count set by parameter flt_count 
  * - sampling disabled
  * - DMA enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  *****************************************************************************/
#define HSCMP_SAMPLED_INTDRV_FILTER_MODE_DMA_DAC_CONFIG(flt_count,samp_per,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  SET(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

// SE Externally driven modes
#define LIMIT_FLT_CNT(x)                ((x<1)?1:x)                        
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode externally driven
  * - filter sample count set to 1
  * - sampling enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_NOFILTER_MODE_CONFIG()                            \
        HSCMP_SAMPLED_EXTDRV_FILTER_MODE_CONFIG(1)                            

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode externally driven
  * - filter sample count set by parameter flt_count
  * - sampling enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  * @warning It is not recommended to set flt_count to 0 in this case.
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_FILTER_MODE_CONFIG(flt_count)                    \
(tCMP){                                                                       \
/* CR0    */  ((LIMIT_FLT_CNT(flt_count))<<4)|SET(CMP_CR0_HYSTCTR(0)),        \
/* CR1    */  SET(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+INV
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode externally driven
  * - filter sample count set to 1
  * - sampling enabled
  * - inverted output enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_NOFILTER_MODE_INV_CONFIG()                        \
        HSCMP_SAMPLED_EXTDRV_FILTER_MODE_INV_CONFIG(1)
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode externally driven
  * - filter sample count set by parameter flt_count
  * - sampling enabled
  * - inverted output enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7 
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  * @warning It is not recommended to set flt_count to 0 in this case.
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_FILTER_MODE_INV_CONFIG(flt_count)                \
(tCMP){                                                                       \
/* CR0    */  ((LIMIT_FLT_CNT(flt_count))<<4)|SET(CMP_CR0_HYSTCTR(0)),        \
/* CR1    */  SET(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              SET(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+IER
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode externally driven
  * - filter sample count set to 1
  * - sampling enabled
  * - rising edge interrupt enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_NOFILTER_MODE_IER_CONFIG()                        \
        HSCMP_SAMPLED_EXTDRV_FILTER_MODE_IER_CONFIG(1) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode externally driven
  * - filter sample count set by parameter flt_count
  * - sampling enabled
  * - rising edge interrupt enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7 
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  * @warning It is not recommended to set flt_count to 0 in this case.
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_FILTER_MODE_IER_CONFIG(flt_count)                \
(tCMP){                                                                       \
/* CR0    */  ((LIMIT_FLT_CNT(flt_count))<<4)|SET(CMP_CR0_HYSTCTR(0)),        \
/* CR1    */  SET(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+IEF
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode externally driven
  * - filter sample count set to 1
  * - sampling enabled
  * - falling edge interrupt enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_NOFILTER_MODE_IEF_CONFIG()                        \
        HSCMP_SAMPLED_EXTDRV_FILTER_MODE_IEF_CONFIG(1) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode externally driven
  * - filter sample count set by parameter flt_count
  * - sampling enabled
  * - falling edge interrupt enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  * @warning It is not recommended to set flt_count to 0 in this case.
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_FILTER_MODE_IEF_CONFIG(flt_count)                \
(tCMP){                                                                       \
/* CR0    */  ((LIMIT_FLT_CNT(flt_count))<<4)|SET(CMP_CR0_HYSTCTR(0)),        \
/* CR1    */  SET(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+IERF
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode externally driven
  * - filter sample count set to 1
  * - sampling enabled
  * - both edges interrupt enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_NOFILTER_MODE_IERF_CONFIG()                       \
        HSCMP_SAMPLED_EXTDRV_FILTER_MODE_IERF_CONFIG(1) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode externally driven
  * - filter sample count set by parameter flt_count
  * - sampling enabled
  * - both edges interrupt enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  * @warning It is not recommended to set flt_count to 0 in this case.
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_FILTER_MODE_IERF_CONFIG(flt_count)               \
(tCMP){                                                                       \
/* CR0    */  ((LIMIT_FLT_CNT(flt_count))<<4)|SET(CMP_CR0_HYSTCTR(0)),        \
/* CR1    */  SET(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+DMA
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode externally driven
  * - filter sample count set to 1
  * - sampling enabled
  * - DMA enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_NOFILTER_MODE_DMA_CONFIG()                        \
        HSCMP_SAMPLED_EXTDRV_FILTER_MODE_DMA_CONFIG(1) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode externally driven
  * - filter sample count set by parameter flt_count
  * - sampling enabled
  * - DMA enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  * @warning It is not recommended to set flt_count to 0 in this case.
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_FILTER_MODE_DMA_CONFIG(flt_count)                \
(tCMP){                                                                       \
/* CR0    */  ((LIMIT_FLT_CNT(flt_count))<<4)|SET(CMP_CR0_HYSTCTR(0)),        \
/* CR1    */  SET(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  SET(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

// SE Externally driven modes with DAC enabled
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode externally driven
  * - filter sample count set to 1
  * - sampling enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_NOFILTER_MODE_DAC_CONFIG(dac_voltage)             \
        HSCMP_SAMPLED_EXTDRV_FILTER_MODE_DAC_CONFIG(1,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode externally driven
  * - filter sample count set by parameter flt_count
  * - sampling enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7 
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  * @warning It is not recommended to set flt_count to 0 in this case.
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_FILTER_MODE_DAC_CONFIG(flt_count,dac_voltage)    \
(tCMP){                                                                       \
/* CR0    */  ((LIMIT_FLT_CNT(flt_count))<<4)|SET(CMP_CR0_HYSTCTR(0)),        \
/* CR1    */  SET(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+INV
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode externally driven
  * - filter sample count set to 1
  * - sampling enabled
  * - inverted output enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_NOFILTER_MODE_INV_DAC_CONFIG(dac_voltage)         \
        HSCMP_SAMPLED_EXTDRV_FILTER_MODE_INV_DAC_CONFIG(1,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode externally driven
  * - filter sample count set by parameter flt_count
  * - sampling enabled
  * - inverted output enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7 
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  * @warning It is not recommended to set flt_count to 0 in this case.
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_FILTER_MODE_INV_DAC_CONFIG(flt_count,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  ((LIMIT_FLT_CNT(flt_count))<<4)|SET(CMP_CR0_HYSTCTR(0)),        \
/* CR1    */  SET(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              SET(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+IER
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode externally driven
  * - filter sample count set to 1
  * - sampling enabled
  * - rising edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_NOFILTER_MODE_IER_DAC_CONFIG(dac_voltage)         \
        HSCMP_SAMPLED_EXTDRV_FILTER_MODE_IER_DAC_CONFIG(1,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode externally driven
  * - filter sample count set by parameter flt_count
  * - sampling enabled
  * - rising edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7 
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  * @warning It is not recommended to set flt_count to 0 in this case.
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_FILTER_MODE_IER_DAC_CONFIG(flt_count,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  ((LIMIT_FLT_CNT(flt_count))<<4)|SET(CMP_CR0_HYSTCTR(0)),        \
/* CR1    */  SET(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+IEF
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode externally driven
  * - filter sample count set to 1
  * - sampling enabled
  * - falling edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_NOFILTER_MODE_IEF_DAC_CONFIG(dac_voltage)         \
        HSCMP_SAMPLED_EXTDRV_FILTER_MODE_IEF_DAC_CONFIG(1,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode externally driven
  * - filter sample count set by parameter flt_count
  * - sampling enabled
  * - falling edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  * @warning It is not recommended to set flt_count to 0 in this case.
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_FILTER_MODE_IEF_DAC_CONFIG(flt_count,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  ((LIMIT_FLT_CNT(flt_count))<<4)|SET(CMP_CR0_HYSTCTR(0)),        \
/* CR1    */  SET(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+IERF
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode externally driven
  * - filter sample count set to 1
  * - sampling enabled
  * - both edges interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_NOFILTER_MODE_IERF_DAC_CONFIG(dac_voltage)        \
        HSCMP_SAMPLED_EXTDRV_FILTER_MODE_IERF_DAC_CONFIG(1,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode externally driven
  * - filter sample count set by parameter flt_count
  * - sampling enabled
  * - both edges interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  * @warning It is not recommended to set flt_count to 0 in this case.
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_FILTER_MODE_IERF_DAC_CONFIG(flt_count,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  ((LIMIT_FLT_CNT(flt_count))<<4)|SET(CMP_CR0_HYSTCTR(0)),        \
/* CR1    */  SET(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+DMA
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled non-filtered mode externally driven
  * - filter sample count set to 1
  * - sampling enabled
  * - DMA enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_NOFILTER_MODE_DMA_DAC_CONFIG(dac_voltage)         \
        HSCMP_SAMPLED_EXTDRV_FILTER_MODE_DMA_DAC_CONFIG(1,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - sampled filtered mode externally driven
  * - filter sample count set by parameter flt_count
  * - sampling enabled
  * - DMA enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7 
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then sampled non-filtered mode is 
  *          configured.
  * @warning It is not recommended to set flt_count to 0 in this case.
  *****************************************************************************/
#define HSCMP_SAMPLED_EXTDRV_FILTER_MODE_DMA_DAC_CONFIG(flt_count,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  ((LIMIT_FLT_CNT(flt_count))<<4)|SET(CMP_CR0_HYSTCTR(0)),        \
/* CR1    */  SET(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x00)),                                    \
/* SCR    */  SET(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

// WE windowed modes
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed mode
  * - filter sample count set to 0
  * - windowing enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_WINDOWED_MODE_CONFIG()                                          \
        HSCMP_WINDOWED_FILTER_MODE_CONFIG(0,0) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed/resampled mode
  * - filter sample count set to 1
  * - windowing enabled
  * - filter disabled
  * @param   samp_per       select one sample periode 1 to 255
  *****************************************************************************/
#define HSCMP_WINDOWED_RESAMPLED_MODE_CONFIG(samp_per)                        \
        HSCMP_WINDOWED_FILTER_MODE_CONFIG(1,samp_per) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed filtered mode
  * - filter sample count set by parameter flt_count 
  * - windowing enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @note    If flt_count is set to 1 then windowed/resampled mode  is 
  *          configured.
  *****************************************************************************/
#define HSCMP_WINDOWED_FILTER_MODE_CONFIG(flt_count,samp_per)                 \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |SET(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+INV
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed mode
  * - filter sample count set to 0
  * - windowing enabled
  * - inverted output enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_WINDOWED_MODE_INV_CONFIG()                                      \
        HSCMP_WINDOWED_FILTER_MODE_INV_CONFIG(0,0) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed/resampled mode
  * - filter sample count set to 1
  * - windowing enabled
  * - inverted output enabled
  * - filter disabled
  * @param   samp_per       select one sample periode 1 to 255
  *****************************************************************************/
#define HSCMP_WINDOWED_RESAMPLED_MODE_INV_CONFIG(samp_per)                    \
        HSCMP_WINDOWED_FILTER_MODE_INV_CONFIG(1,samp_per) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed filtered mode
  * - filter sample count set by parameter flt_count 
  * - windowing enabled
  * - inverted output enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @note    If flt_count is set to 1 then windowed/resampled mode  is 
  *          configured.
  *****************************************************************************/
#define HSCMP_WINDOWED_FILTER_MODE_INV_CONFIG(flt_count,samp_per)             \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |SET(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              SET(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+IER
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed mode
  * - filter sample count set to 0
  * - windowing enabled
  * - rising edge interrupt enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_WINDOWED_MODE_IER_CONFIG()                                      \
        HSCMP_WINDOWED_FILTER_MODE_IER_CONFIG(0,0) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed/resampled mode
  * - filter sample count set to 1
  * - windowing enabled
  * - rising edge interrupt enabled
  * - filter disabled
  * @param   samp_per       select one sample periode 1 to 255
  *****************************************************************************/
#define HSCMP_WINDOWED_RESAMPLED_MODE_IER_CONFIG(samp_per)                    \
        HSCMP_WINDOWED_FILTER_MODE_IER_CONFIG(1,samp_per) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed filtered mode
  * - filter sample count set by parameter flt_count 
  * - windowing enabled
  * - rising edge interrupt enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @note    If flt_count is set to 1 then windowed/resampled mode  is 
  *          configured.
  *****************************************************************************/
#define HSCMP_WINDOWED_FILTER_MODE_IER_CONFIG(flt_count,samp_per)             \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |SET(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+IEF
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed mode
  * - filter sample count set to 0
  * - windowing enabled
  * - falling edge interrupt enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_WINDOWED_MODE_IEF_CONFIG()                                      \
        HSCMP_WINDOWED_FILTER_MODE_IEF_CONFIG(0,0) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed/resampled mode
  * - filter sample count set to 1
  * - windowing enabled
  * - falling edge interrupt enabled
  * - filter disabled
  * @param   samp_per       select one sample periode 1 to 255
  *****************************************************************************/
#define HSCMP_WINDOWED_RESAMPLED_MODE_IEF_CONFIG(samp_per)                    \
        HSCMP_WINDOWED_FILTER_MODE_IEF_CONFIG(1,samp_per) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed filtered mode
  * - filter sample count set by parameter flt_count 
  * - windowing enabled
  * - falling edge interrupt enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @note    If flt_count is set to 1 then windowed/resampled mode  is 
  *          configured.
  *****************************************************************************/
#define HSCMP_WINDOWED_FILTER_MODE_IEF_CONFIG(flt_count,samp_per)             \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |SET(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+IERF
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed mode
  * - filter sample count set to 0
  * - windowing enabled
  * - both edges interrupt enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_WINDOWED_MODE_IERF_CONFIG()                                     \
        HSCMP_WINDOWED_FILTER_MODE_IERF_CONFIG(0,0) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed/resampled mode
  * - filter sample count set to 1
  * - windowing enabled
  * - both edges interrupt enabled
  * - filter disabled
  * @param   samp_per       select one sample periode 1 to 255
  *****************************************************************************/
#define HSCMP_WINDOWED_RESAMPLED_MODE_IERF_CONFIG(samp_per)                   \
        HSCMP_WINDOWED_FILTER_MODE_IERF_CONFIG(1,samp_per)
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed filtered mode
  * - filter sample count set by parameter flt_count 
  * - windowing enabled
  * - both edges interrupt enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @note    If flt_count is set to 1 then windowed/resampled mode  is 
  *          configured.
  *****************************************************************************/
#define HSCMP_WINDOWED_FILTER_MODE_IERF_CONFIG(flt_count,samp_per)            \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |SET(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

//+DMA
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed mode
  * - filter sample count set to 0
  * - windowing enabled
  * - filter disabled
  *****************************************************************************/
#define HSCMP_WINDOWED_MODE_DMA_CONFIG()                                      \
        HSCMP_WINDOWED_FILTER_MODE_DMA_CONFIG(0,0) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed/resampled mode
  * - filter sample count set to 1
  * - windowing enabled
  * - filter disabled
  * @param   samp_per       select one sample periode 1 to 255
  *****************************************************************************/
#define HSCMP_WINDOWED_RESAMPLED_MODE_DMA_CONFIG(samp_per)                    \
        HSCMP_WINDOWED_FILTER_MODE_DMA_CONFIG(1,samp_per) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed filtered mode
  * - filter sample count set by parameter flt_count 
  * - windowing enabled
  * - DMA enabled
  * - filter disabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @note    If flt_count is set to 1 then windowed/resampled mode  is 
  *          configured.
  *****************************************************************************/
#define HSCMP_WINDOWED_FILTER_MODE_DMA_CONFIG(flt_count,samp_per)             \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |SET(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  SET(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|0         \
}

// WE modes with DAC enabled
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed mode
  * - filter sample count set to 0
  * - windowing enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_WINDOWED_MODE_DAC_CONFIG(dac_voltage)                           \
        HSCMP_WINDOWED_FILTER_MODE_DAC_CONFIG(0,0,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed/resampled mode
  * - filter sample count set to 1
  * - windowing enabled
  * - filter disabled
  * - DAC enabled
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_WINDOWED_RESAMPLED_MODE_DAC_CONFIG(samp_per,dac_voltage)        \
        HSCMP_WINDOWED_FILTER_MODE_DAC_CONFIG(1,samp_per,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed filtered mode
  * - filter sample count set by parameter flt_count 
  * - windowing enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then windowed/resampled mode  is 
  *          configured.
  *****************************************************************************/
#define HSCMP_WINDOWED_FILTER_MODE_DAC_CONFIG(flt_count,samp_per,dac_voltage) \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |SET(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+INV
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed mode
  * - filter sample count set to 0
  * - windowing enabled
  * - inverted output enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_WINDOWED_MODE_INV_DAC_CONFIG(dac_voltage)                      \
        HSCMP_WINDOWED_FILTER_MODE_INV_DAC_CONFIG(0,0,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed/resampled mode
  * - filter sample count set to 1
  * - windowing enabled
  * - inverted output enabled
  * - filter disabled
  * - DAC enabled
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_WINDOWED_RESAMPLED_MODE_INV_DAC_CONFIG(samp_per,dac_voltage)    \
        HSCMP_WINDOWED_FILTER_MODE_INV_DAC_CONFIG(1,samp_per,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed filtered mode
  * - filter sample count set by parameter flt_count 
  * - windowing enabled
  * - inverted output enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then windowed/resampled mode  is 
  *          configured.
  *****************************************************************************/
#define HSCMP_WINDOWED_FILTER_MODE_INV_DAC_CONFIG(flt_count,samp_per,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |SET(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              SET(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+IER
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed mode
  * - filter sample count set to 0
  * - windowing enabled
  * - rising edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_WINDOWED_MODE_IER_DAC_CONFIG(dac_voltage)                       \
        HSCMP_WINDOWED_FILTER_MODE_IER_DAC_CONFIG(0,0,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed/resampled mode
  * - filter sample count set to 1
  * - windowing enabled
  * - rising edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_WINDOWED_RESAMPLED_MODE_IER_DAC_CONFIG(samp_per,dac_voltage)    \
        HSCMP_WINDOWED_FILTER_MODE_IER_DAC_CONFIG(1,samp_per,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed filtered mode
  * - filter sample count set by parameter flt_count 
  * - windowing enabled
  * - rising edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then windowed/resampled mode  is 
  *          configured.
  *****************************************************************************/
#define HSCMP_WINDOWED_FILTER_MODE_IER_DAC_CONFIG(flt_count,samp_per,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |SET(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+IEF
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed mode
  * - filter sample count set to 0
  * - windowing enabled
  * - falling edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_WINDOWED_MODE_IEF_DAC_CONFIG(dac_voltage)                       \
        HSCMP_WINDOWED_FILTER_MODE_IEF_DAC_CONFIG(0,0,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed/resampled mode
  * - filter sample count set to 1
  * - windowing enabled
  * - falling edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_WINDOWED_RESAMPLED_MODE_IEF_DAC_CONFIG(samp_per,dac_voltage)    \
        HSCMP_WINDOWED_FILTER_MODE_IEF_DAC_CONFIG(1,samp_per,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed filtered mode
  * - filter sample count set by parameter flt_count 
  * - windowing enabled
  * - falling edge interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then windowed/resampled mode  is 
  *          configured.
  *****************************************************************************/
#define HSCMP_WINDOWED_FILTER_MODE_IEF_DAC_CONFIG(flt_count,samp_per,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |SET(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+IERF
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed mode
  * - filter sample count set to 0
  * - windowing enabled
  * - both edges interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_WINDOWED_MODE_IERF_DAC_CONFIG(dac_voltage)                      \
        HSCMP_WINDOWED_FILTER_MODE_IERF_DAC_CONFIG(0,0,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed/resampled mode
  * - filter sample count set to 1
  * - windowing enabled
  * - both edges interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_WINDOWED_RESAMPLED_MODE_IERF_DAC_CONFIG(samp_per,dac_voltage)   \
        HSCMP_WINDOWED_FILTER_MODE_IERF_DAC_CONFIG(1,samp_per,dac_voltage) 
          
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed filtered mode
  * - filter sample count set by parameter flt_count 
  * - windowing enabled
  * - both edges interrupt enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then windowed/resampled mode  is 
  *          configured.
  *****************************************************************************/
#define HSCMP_WINDOWED_FILTER_MODE_IERF_DAC_CONFIG(flt_count,samp_per,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |SET(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

//+DMA
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed mode
  * - filter sample count set to 0
  * - windowing enabled
  * - DMA enabled
  * - filter disabled
  * - DAC enabled
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_WINDOWED_MODE_DMA_DAC_CONFIG(dac_voltage)                       \
        HSCMP_WINDOWED_FILTER_MODE_DMA_DAC_CONFIG(0,0,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed/resampled mode
  * - filter sample count set to 1
  * - windowing enabled
  * - DMA enabled
  * - filter disabled
  * - DAC enabled
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  *****************************************************************************/
#define HSCMP_WINDOWED_RESAMPLED_MODE_DMA_DAC_CONFIG(samp_per,dac_voltage)    \
        HSCMP_WINDOWED_FILTER_MODE_DMA_DAC_CONFIG(1,samp_per,dac_voltage) 

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - windowed filtered mode
  * - filter sample count set by parameter flt_count 
  * - windowing enabled
  * - DMA enabled
  * - filter disabled
  * - DAC enabled
  * @param   flt_count       filter sample counts select from 2 to 7
  * @param   samp_per        select one sample periode 1 to 255
  * @param   dac_voltage     DAC output voltage select from 0 to 63
  * @note    If flt_count is set to 1 then windowed/resampled mode  is 
  *          configured.
  *****************************************************************************/
#define HSCMP_WINDOWED_FILTER_MODE_DMA_DAC_CONFIG(flt_count,samp_per,dac_voltage)\
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(flt_count)) |SET(CMP_CR0_HYSTCTR(0)),    \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |SET(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(samp_per)),                                \
/* SCR    */  SET(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac_voltage\
}

// Just for compatibility with older drivers
/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - filter enable 1 counts - simply sampled, 
  * - module enable after initialization,
  * - hi speed mode,
  * - filter period 
  * - irq. enable (only CFR generate IRQ)
  * @param   dac       DAC output voltage select from 0 to 63 
  *****************************************************************************/
#define CMP_FILTER1_MODULE_EN_SAMPLE_PER_1_IRQ_RISING_CONFIG(dac)             \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(1)) |SET(CMP_CR0_HYSTCTR(0)),            \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x01)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac       \
}

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - filter enable 1 counts - simply sampled, 
  * - module enable after initialization,
  * - hi speed mode,
  * - filter period 
  * - irq. enable (only CFR generate IRQ)
  * @param   dac       DAC output voltage select from 0 to 63 
  *****************************************************************************/
#define CMP_FILTER1_MODULE_EN_SAMPLE_PER_1_IRQ_RISING_DAC_EN_CONFIG(dac)      \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(1)) |SET(CMP_CR0_HYSTCTR(0)),            \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x01)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac       \
}

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - filter enable 1 counts - simply sampled, 
  * - module enable after initialization,
  * - hi speed mode,
  * - filter period 
  * - irq. enable (only CFF generate IRQ)
  * @param   dac       DAC output voltage select from 0 to 63 
  *****************************************************************************/
#define CMP_FILTER1_MODULE_EN_SAMPLE_PER_1_IRQ_FALLING_CONFIG(dac)            \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(1)) |SET(CMP_CR0_HYSTCTR(0)),            \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x01)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac       \
}

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - filter enable 1 counts - simply sampled, 
  * - module enable after initialization,
  * - hi speed mode,
  * - filter period 
  * - irq. enable (both CFR and CFF generate IRQ)
  * @param   dac       DAC output voltage select from 0 to 63 
  *****************************************************************************/
#define CMP_FILTER1_MODULE_EN_SAMPLE_PER_1_IRQ_BOTH_CONFIG(dac)               \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(1)) |SET(CMP_CR0_HYSTCTR(0)),            \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x01)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              SET(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac       \
}

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - filter enable 1 counts - simply sampled, 
  * - module enable after initialization,
  * - hi speed mode,
  * - filter period 
  * - DMA enable (CFR or CFF generate request)
  * @param   dac       DAC output voltage select from 0 to 63 
  *****************************************************************************/
#define CMP_FILTER1_MODULE_EN_SAMPLE_PER_1_IRQ_EN_CONFIG(dac)                 \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(1)) |SET(CMP_CR0_HYSTCTR(0)),            \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0x01)),                                    \
/* SCR    */  SET(CMP_SCR_DMAEN_MASK)    |CLR(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac       \
}

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - filter enable 7 counts, 
  * - module enable after initialization,
  * - hi speed mode, 
  * - irq. enable
  * @param   dac       DAC output voltage select from 0 to 63 
  *****************************************************************************/
#define CMP_FILTER7_MODULE_EN_SAMPLE_PER_255_IRQ_EN_CONFIG(dac)               \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(7)) |SET(CMP_CR0_HYSTCTR(0)),            \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0xFF)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  CLR(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac       \
}

/**************************************************************************/ /*!
  * @brief Comparator setting:
  * - filter enable 7 counts, 
  * - module enable after initialization,
  * - hi speed mode, 
  * - irq. enable,
  * - AC enable
  * @param   dac       DAC output voltage select from 0 to 63 
  *****************************************************************************/
#define CMP_FILTER7_MODULE_EN_SAMPLE_PER_255_IRQ_EN_DAC_EN_CONFIG(dac)        \
(tCMP){                                                                       \
/* CR0    */  SET(CMP_CR0_FILTER_CNT(7)) |SET(CMP_CR0_HYSTCTR(0)),            \
/* CR1    */  CLR(CMP_CR1_SE_MASK)       |CLR(CMP_CR1_WE_MASK)|               \
              CLR(CMP_CR1_TRIGM_MASK)    |SET(CMP_CR1_PMODE_MASK)|            \
              CLR(CMP_CR1_INV_MASK)      |CLR(CMP_CR1_COS_MASK)|              \
              CLR(CMP_CR1_OPE_MASK)      |SET(CMP_CR1_EN_MASK),               \
/* FPR    */  SET(CMP_FPR_FILT_PER(0xFF)),                                    \
/* SCR    */  CLR(CMP_SCR_DMAEN_MASK)    |SET(CMP_SCR_IER_MASK)|              \
              CLR(CMP_SCR_IEF_MASK),                                          \
/* DACCR  */  SET(CMP_DACCR_DACEN_MASK)  |CLR(CMP_DACCR_VRSEL_MASK)|dac       \
}
/*! @} End of cmp_config                                                      */

/******************************************************************************
* CMP callback used in CMP_Init() function
*
*//*! @addtogroup cmp_callback
* @{
*******************************************************************************/
/*! @brief CMP_CALLBACK type declaration                                      */
typedef enum 
{
    CMP_RE_CALLBACK=0,      ///< rissing edge detection indentification
    CMP_FE_CALLBACK=1,      ///< falling edge detection indentification
} CMP_CALLBACK_TYPE;

/*! CMP_CALLBACK function declaration                                         */
typedef void (*CMP_CALLBACK)(CMP_CALLBACK_TYPE type);
/*! @} End of cmp_callback                                                    */

/******************************************************************************
* CMP function and macro definitions
*
*//*! @addtogroup cmp_macro
* @{
*******************************************************************************/

#define CMP0_GetOutput()                CMP0_SCR&CMP_SCR_COUT_MASK
/***************************************************************************//*!
 * @brief   Read output value of CMP.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_GetOutput(module)           module##_GetOutput()

#define CMP0_SamplingEnable()           CMP0_CR1 |= CMP_CR1_SE_MASK
/***************************************************************************//*!
 * @brief   Sampling mode enable.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_SamplingEnable(module)     module##_SamplingEnable()

#define CMP0_SamplingDisable()         CMP0_CR1 &= ~CMP_CR1_SE_MASK
/***************************************************************************//*!
 * @brief   Sampling mode disable.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_SamplingDisable(module)     module##_SamplingDisable()

#define CMP0_WindowingEnable()          CMP0_CR1 |= CMP_CR1_WE_MASK
/***************************************************************************//*!
 * @brief   Windowing mode enable.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_WindowingEnable(module)     module##_WindowingEnable()

#define CMP0_WindowingDisable()         CMP0_CR1 &= ~CMP_CR1_WE_MASK
/***************************************************************************//*!
 * @brief   Windowing mode disable.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_WindowingDisable(module)    module##_WindowingDisable()

#define CMP0_TriggerModeEnable()        CMP0_CR1 |= CMP_CR1_TRIGM_MASK
/***************************************************************************//*!
 * @brief   Trigger mode enable.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_TriggerModeEnable(module)   module##_TriggerModeEnable()

#define CMP0_TriggerModeDisable()       CMP0_CR1 &= ~CMP_CR1_TRIGM_MASK
/***************************************************************************//*!
 * @brief   Trigger mode disable.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_TriggerModeDisable(module)  module##_TriggerModeDisable()

#define CMP0_PowerMode_LSCMP()          CMP0_CR1 &= ~CMP_CR1_PMODE_MASK
#define CMP0_PowerMode_HSCMP()          CMP0_CR1 |= CMP_CR1_PMODE_MASK
/***************************************************************************//*!
 * @brief   Select between low speed LSCMP or high speed HSCMP power modes.
 * @param   module  - CMP0
 * @param   mode  - LSCMP or HSCMP
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_PowerMode(module, mode)     module##_PowerMode_##mode##()

#define CMP0_InvertEnable()             CMP0_CR1 |= CMP_CR1_INV_MASK
/***************************************************************************//*!
 * @brief   Enable CMP output inverting.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_InvertEnable(module)        module##_InvertEnable()

#define CMP0_InvertDisable()            CMP0_CR1 &= ~CMP_CR1_INV_MASK
/***************************************************************************//*!
 * @brief   Disable CMP output inverting.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_InvertDisable(module)       module##_InvertDisable()

#define CMP0_Output_COUT()              CMP0_CR1 &= ~CMP_CR1_COS_MASK
#define CMP0_Output_COUTA()             CMP0_CR1 |= CMP_CR1_COS_MASK
/***************************************************************************//*!
 * @brief   Select between filtered COUT or unfiltered COUTA CMP outputs.
 * @param   module  - CMP0
 * @param   output  - COUT or COUTA
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_OutputSelect(module, output)  module##_Output_##output##()

#define CMP0_OutputPinEnable()          CMP0_CR1 |= CMP_CR1_OPE_MASK
/***************************************************************************//*!
 * @brief   Enable associated CMP output pin.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_OutputPinEnable(module)     module##_OutputPinEnable()

#define CMP0_OutputPinDisable()         CMP0_CR1 &= ~CMP_CR1_OPE_MASK
/***************************************************************************//*!
 * @brief   Disable associated CMP output pin.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_OutputPinDisable(module)    module##_OutputPinDisable()

#define CMP0_Enable()                   CMP0_CR1 |= CMP_CR1_EN_MASK
/***************************************************************************//*!
 * @brief   Enable CMP module.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_Enable(module)              module##_Enable()

#define CMP0_Disable()                  CMP0_CR1 &= ~CMP_CR1_EN_MASK
/***************************************************************************//*!
 * @brief   Disable CMP module.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_Disable(module)             module##_Disable()

#define CMP0_DACEnable()                CMP0_DACCR |= CMP_DACCR_DACEN_MASK
/***************************************************************************//*!
 * @brief   Enable 6-bit DAC in CMP module.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_DACEnable(module)           module##_DACEnable()

#define CMP0_DACDisable()               CMP0_DACCR &= ~CMP_DACCR_DACEN_MASK
/***************************************************************************//*!
 * @brief   Disable 6-bit DAC in CMP module.
 * @param   module  - CMP0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_DACDisable(module)          module##_DACDisable()

#define CMP0_DACVref_VDD()              CMP0_DACCR |= CMP_DACCR_VRSEL_MASK
#define CMP0_DACVref_VREFH()            CMP0_DACCR &= ~CMP_DACCR_VRSEL_MASK
/***************************************************************************//*!
 * @brief   Disable 6-bit DAC in CMP module.
 * @param   module  - CMP0
 * @param   ref  - VREFH or VDD
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_DACVref(module,ref)          module##_DACVref_##ref##()

#define CMP0_DACOutputVoltage(vsel)      CMP0_DACCR = CMP_DACCR_VOSEL(vsel)|   \
                                                      (CMP0_DACCR&0xC0)
/***************************************************************************//*!
 * @brief   Select the output voltage of 6-bit DAC in CMP module.
 * @param   module  - CMP0
 * @param   vsel  - number from 0 to 63 (DACO = ((vsel+1)*Vref)/64)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define CMP_DACOutputVoltage(module,vsel)  module##_DACOutputVoltage(vsel)


/***************************************************************************//*!
 * @brief   CMP initialization function.
 * @details This function initializes selected comparator module
 * @param   module  - CMP0
 * @param   cfg     - Use one of the configuration structures @ref cmp_config
 * @param   psel    - Plus input mux control select @ref cmp_channel 
 * @param   nsel    - Minus input mux control select @ref cmp_channel
 * @param   ip        Interrupt priority 0..3
 * @param   callback  Pointer to @ref CMP_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define CMP_Init(module,cfg,psel,nsel,ip,callback)  module##_Init(cfg,psel,nsel,ip,callback)
/*! @} End of cmp_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/    
extern void CMP0_Init (tCMP cmp, uint8 psel, uint8 nsel, uint8 ip, CMP_CALLBACK pCallback);

#endif /* __CMP_H */
