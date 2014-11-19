/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      frdm_lpuart_test.c
 * @author    
 * @version   0.0.1.0
 * @date      Jun-20-2013
 * @brief     LPUART in VLPS uses address mark to wake up
 * @details   LPUART enetr VLPS mode and then waits to specified character to wake
 *            up. MCGIRCLK is used as source clock for LPUART0. The baud rate is 
 *            set to 9600. To enter VLPS mode it is necessary to send 'e' or 'E' 
 *            character from PC terminal. Ater entering VLPS mode LPUART0 is in 
 *            match address mode. The match addresses set to 0x81 and 0xAA. MCU wake
 *            up from VLPS when match address event occur. Match address mode must
 *            be disabled after wake up to avoid entering to address matching again
 *            by sending data with address mark (then sending 'e' or  'E' can be locked).
 *            Sending 'e' or 'E' again address matching should be restarted by 
 *            enabling match address mode again and by sending appropriate data 
 *            with address mark in internal loop.
 * 
 * @note      The current cunsumption when MCU running in VLPS mode should be around
 *            80uA.   
 ******************************************************************************/
#include "common.h"
#include "drivers.h"
#include "derivative.h"
#include "types.h"
#include "usb_hid.h"

/* callback functions prototypes                                              */
static void lpuart0_callback(LPUART_CALLBACK_TYPE type, vuint8 status);
/* module function prototypes                                                 */

/*******************************************************************************
*//*! @addtogroup frdm_lpuart_test_variables_def
* @{ 
*   Module global variables definitions are provided here.
*******************************************************************************/
static uint8 volatile c;        ///< receive character variable
/*! @} End of frdm_lpuart_test_variables_def                                        */


/*******************************************************************************
 * @brief   main routine
 ******************************************************************************/
int main (void)
{  
  SIM_Init (SIM_MODULE_FRDM_LPUART_CONFIG);
  MCG_LITE_Init (MCG_LITE_HIRC_48MHZ);
  
  MCG_LITE_LIRC_Enable();
  MCG_LITE_LIRC_StopEnable();
  MCG_LITE_LIRC_Sel(LIRC_8MHZ);
  MCG_LITE_LIRC_Div2(LIRC_DIV_2);
  PORT_Init (PORTA, PORT_MODULE_ALT2_MODE, PIN_1|PIN_2, 0, NULL);
  LPUART_Init (LPUART0, LPUART_FRDM_LPUART_CONFIG(9600,4e6), 1, \
  (LPUART_CALLBACK)lpuart0_callback);

   SMC_Init (SMC_MODULE_CONFIG1);
  
  __enable_irq();
  
  LPUART_PutStr(LPUART0,INTRO_MESSAGE);
  
  while (1)
  {
    LPUART_PutStr(LPUART0,REQUEST_MESSAGE);
    c = 0x00;
    while (!c);
    if ((c == 'e') || (c == 'E'))
    {
      LPUART_PutStr(LPUART0, VLPS_ENTER_MESSAGE);
      while(!LPUART_TxComplete(LPUART0));
      LPUART_MatchAdrConfig(LPUART0, LPUART_MAEN1|LPUART_MAEN2, 0x81, 0xAA);
      LPUART_LoopEnable(LPUART0);
      while(!(LPUART0_CTRL & LPUART_CTRL_LOOPS_MASK));
      LPUART_PutChar(LPUART0,0xCC);
      while(!LPUART_TxComplete(LPUART0));
      LPUART_LoopDisable(LPUART0);
      SMC_SetMode (VLPS);
      LPUART_MatchAdrDisable(LPUART0);
    }
    else
    {
      LPUART_PutStr(LPUART0, WARNING_MESSAGE);
    }    
  }
}

/*******************************************************************************
*//*! @addtogroup frdm_lpuart_test_functions_def
* @{ 
*   Module local function definitions are provided here.
*******************************************************************************/
/***************************************************************************//*!
 * @brief   LPUART02 Callback function - receive buffer full
 * @param   type - RX_CALLBACK|CHB_CALLBACK (@ref uart_callback)
 * @param   result - 16-bit result value   
 ******************************************************************************/
static void lpuart0_callback(LPUART_CALLBACK_TYPE type, vuint8 status)
{
  if (type == LPUART_RX_CALLBACK)
  {
    c = LPUART_GetChar(LPUART0);
  }
}
/*! @} End of frdm_lpuart_test_functions_def                                        */


/*******************************************************************************
 * End of main module                                                          *
 *******************************************************************************/

