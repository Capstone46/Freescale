/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      frdm_light_sensor_test.c
 * @author    
 * @version   0.0.1.0
 * @date      Jun-20-2013
 * @brief     The LED brightness (both LEDs are inversed) is changing with light
 *            sensor shielding.
 ******************************************************************************/
#include "common.h"
#include "drivers.h"
#include "derivative.h"    
#include "types.h"          
#include "usb_hid.h"

/* callback functions prototypes                                              */
void dma0_callback(DMA_CALLBACK_TYPE type);
void dma1_callback(DMA_CALLBACK_TYPE type);

/* module function prototypes                                                 */

/*******************************************************************************
*//*! @addtogroup frdm_light_sensor_test_variables_def
* @{ 
*   Module global variables definitions are provided here.
*******************************************************************************/
static tADC_CALIB adc0_calib;   ///< adc calibration structure (defined in adc.h)
/*! @} End of frdm_light_sensor_test_variables_def                                        */


/*******************************************************************************
 * @brief   main routine
 ******************************************************************************/
int main (void)
{  
  SIM_Init (SIM_MODULE_CONFIG_ALL_PERIPH_ON);
  MCG_LITE_Init (MCG_LITE_HIRC_48MHZ);
  
  // ADCO CHA is trigger by PIT CH0 
  SIM_ADC0TrgSel (SIM_PIT0_TRG_ADC0_A);
  // ADC calibration and initialization
  ADC_ExecCalib (ADC0, ADC_FAST_MUXB_HWTRG_IREF_DMA_CONFIG(SE_10BIT), &adc0_calib);
  ADC_Init  (ADC0, ADC_FAST_MUXB_HWTRG_IREF_DMA_CONFIG(SE_10BIT),\
             ADC_CH_SE_POLL_CONFIG(DAD3), ADC_CH_DISABLE,\
             0, NULL);
  // PIT initialization - CH0 used just as trigger for ADC
  PIT_Init (PIT0, CH0, PIT_CH_TIMER_EN_CONFIG, 24000, 0, NULL);
  // LED D5 and LED D7 are configured for PWM mode
  PORT_Init(PORTD, PORT_MODULE_ALT4_MODE, PIN_5, 0, NULL);
  PORT_Init(PORTE, PORT_MODULE_ALT3_MODE, PIN_31, 0, NULL);
  TPM_Init(TPM0, TPM_MODULE_SYSCLK_DIVBY32_EDGEALIGN_CONFIG, 1024, 0, NULL);
  TPM_CHAN_Init (TPM0, CH4, TPM_CHANNEL_PWMNORMAL_CONFIG, 0);
  TPM_CHAN_Init (TPM0, CH5, TPM_CHANNEL_PWMINVERT_CONFIG, 0);
  DMAMUX0_Init(CH0, DMAMUX_CONFIG1(DMA_SRC_ADC0));
  DMA_Init(DMA0, DMA_SINGLE_ERQ_IRQ_CONFIG(1200,2,2), (uint32*)&ADC0_RA, \
           (uint32*)&TPM0_C4V, 1, dma0_callback);
  DMAMUX0_Init(CH1, DMAMUX_CONFIG1(DMA_SRC_ADC0));
  DMA_Init(DMA1, DMA_SINGLE_ERQ_IRQ_CONFIG(1200,2,2), (uint32*)&ADC0_RA, \
            (uint32*)&TPM0_C5V, 2, dma1_callback);
  
  __enable_irq();
  
  while (1)
  {
    
  }
}

/*******************************************************************************
*//*! @addtogroup frdm_light_sensor_test_functions_def
* @{ 
*   Module local function definitions are provided here.
*******************************************************************************/

/***************************************************************************//*!
 * @brief   DMA0 Callback function
 ******************************************************************************/
void dma0_callback(DMA_CALLBACK_TYPE type) 
{
  DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(1200);
}

/***************************************************************************//*!
 * @brief   DMA1 Callback function
 ******************************************************************************/
void dma1_callback(DMA_CALLBACK_TYPE type) 
{
  DMA_DSR_BCR1 |= DMA_DSR_BCR_BCR(1200);
}

/*! @} End of frdm_light_sensor_test_functions_def                                        */


/*******************************************************************************
 * End of main module                                                          *
 *******************************************************************************/

