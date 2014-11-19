/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      frdm_led_test.c
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
void pit_callback (PIT_CALLBACK_TYPE type);
/* module function prototypes                                                 */

/*******************************************************************************
*//*! @addtogroup frdm_led_test_variables_def
* @{ 
*   Module global variables definitions are provided here.
*******************************************************************************/
// place your module global variables here and comment it (example below)
//static uint8 volatile *p_u8Temp;        ///< pointer to ...
/*! @} End of frdm_led_test_variables_def                                        */


/*******************************************************************************
 * @brief   main routine
 ******************************************************************************/
int main (void)
{  
  SIM_Init (SIM_MODULE_CONFIG_ALL_PERIPH_ON);
  MCG_LITE_Init (MCG_LITE_HIRC_48MHZ);

  // LED pins configuration 
  PORT_Init (PORTD, PORT_MODULE_ALT1_MODE, PIN_5, 0, NULL);
  GPIO_Init (GPIOD, GPIO_PIN_OUTPUT, PIN_5);
  GPIO_Set (GPIOD, PIN_5);
  PORT_Init (PORTE, PORT_MODULE_ALT1_MODE, PIN_31, 0, NULL);
  GPIO_Init (GPIOE, GPIO_PIN_OUTPUT, PIN_31);
  GPIO_Clr (GPIOE, PIN_31);
  // PIT initialization - CH0 used for LED blinking
  PIT_Init (PIT0, CH0, PIT_CH_TIMER_EN_CONFIG, 3000000, 1, pit_callback);
  
  __enable_irq();
  
  while (1)
  {
    
  }
}

/*******************************************************************************
*//*! @addtogroup frdm_led_test_functions_def
* @{ 
*   Module local function definitions are provided here.
*******************************************************************************/
/***************************************************************************//*!
* @brief   PIT Callback function - CH0
 ******************************************************************************/
void pit_callback (PIT_CALLBACK_TYPE type)
{
  if (type&PIT0CH0_CALLBACK)
  {
    GPIO_Tgl (GPIOD, PIN_5); GPIO_Tgl (GPIOE, PIN_31);
  }
}
/*! @} End of frdm_led_test_functions_def                                        */


/*******************************************************************************
 * End of main module                                                          *
 *******************************************************************************/

