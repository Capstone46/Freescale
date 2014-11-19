/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      frdm_adc_temp_test.c
 * @author    
 * @version   0.0.1.0
 * @date      Jun-20-2013
 * @brief     
 ******************************************************************************/
#include "common.h"
#include "drivers.h"
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* User Defined Data Types */
#include "usb_hid.h"

/* callback functions prototypes                                              */

/* module function prototypes                                                 */

/*******************************************************************************
*//*! @addtogroup frdm_adc_temp_test_variables_def
* @{ 
*   Module global variables definitions are provided here.
*******************************************************************************/
// place your module global variables here and comment it (example below)
//static uint8 volatile *p_u8Temp;        ///< pointer to ...
/*! @} End of frdm_adc_temp_test_variables_def                                        */


/*******************************************************************************
 * @brief   main routine
 ******************************************************************************/
int main (void)
{  
  SIM_Init (SIM_MODULE_CONFIG_ALL_PERIPH_ON);
  MCG_LITE_Init (MCG_LITE_HIRC_48MHZ);
  
  __enable_irq();
  
  while (1)
  {
    
  }
}

/*******************************************************************************
*//*! @addtogroup frdm_adc_temp_test_functions_def
* @{ 
*   Module local function definitions are provided here.
*******************************************************************************/
// place your local function definitions here (example bellow)
///***************************************************************************//*!
// * @brief   Local (callback) function definition
// * @details Function provided ...
// * @param   u8Temp - temporary variable ...
// * @return  number of ... in uint32
// * @note    Implemented as ...
// * @warning Non.
// ******************************************************************************/
//static uin32 fTemp(u8int u8Temp)
//{
//  return (uint32)u8Temp;
//}
/*! @} End of frdm_adc_temp_test_functions_def                                        */


/*******************************************************************************
 * End of main module                                                          *
 *******************************************************************************/

