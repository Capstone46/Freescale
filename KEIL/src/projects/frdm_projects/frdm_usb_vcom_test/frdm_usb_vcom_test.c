/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      frdm_usb_vcom_test.c
 * @author    
 * @version   0.0.1.0
 * @date      Jun-20-2013
 * @brief     
 ******************************************************************************/
#include "common.h"
#include "drivers.h"
#include "derivative.h"
#include "types.h"
#include "usb_vcom.h"

/* callback functions prototypes                                              */

/* module function prototypes                                                 */
void debug_prints(char *str);                 ///< Debug print string function

/*******************************************************************************
*//*! @addtogroup frdm_usb_vcom_test_variables_def
* @{ 
*   Module global variables definitions are provided here.
*******************************************************************************/
static uint8_t vbus_buffer[DATA_BUFF_SIZE];  ///< uart buffer array
static uint8_t vbus_len;                     ///< uart buffer length
/*! @} End of frdm_usb_vcom_test_variables_def                                */

/*******************************************************************************
 * @brief   main routine
 ******************************************************************************/
int main (void)
{   
  SIM_Init (SIM_MODULE_FRDM_USB_VCOM_CONFIG);
  MCG_LITE_Init (MCG_LITE_HIRC_48MHZ);

  /* Initialize Debug UART module */
  PORT_Init  (PORTA, PORT_MODULE_ALT2_MODE, PIN_1|PIN_2, 0, NULL);   /* FRDM */
  LPUART_Init(LPUART0, LPUART_POLLMODE_CONFIG(115200, 48e6), 0, NULL);
  
  /* Initialize GPIO module (Buttons) */
  PORT_Init  (PORTC, PORT_MODULE_BUTTON_MODE, PIN_3, 0, NULL);  /* SW1  */
  PORT_Init  (PORTA, PORT_MODULE_BUTTON_MODE, PIN_4, 0, NULL);  /* SW2  */
  
  /* Initialize GPIO module (LEDs) */
  PORT_Init  (PORTD, PORT_MODULE_LED_MODE, PIN_5, 0, NULL);     /* LED1 */
  GPIOD_Init (GPIO_PIN_OUTPUT, PIN_5);
  PORT_Init  (PORTE, PORT_MODULE_LED_MODE, PIN_31, 0, NULL);    /* LED2 */
  GPIOE_Init (GPIO_PIN_OUTPUT, PIN_31);
     
  debug_prints("<I> CORE Initialization OK \n\r");
    
  __enable_irq();     /* Enable global interrupt */
  
  USB_VCOM_Init();    /* Initialize USB VCOM module   */ 
  
  while (1)
  {
    /* call the periodic task internal functions */
    USB_VCOM_PeriodicTask();
    
    /* Recive data from virtual com-port */
    vbus_len = USB_VCOM_Receive(vbus_buffer, DATA_BUFF_SIZE);
    
    if(vbus_len)
    {
      GPIO_Tgl(GPIOD, PIN_5);     
    }
    
    /* Send data to virtual com-port */
    (void) USB_VCOM_Send(vbus_buffer, vbus_len);
  }
}


/*******************************************************************************
*//*! @addtogroup frdm_usb_vcom_test_functions_def
* @{ 
*   Module local function definitions are provided here.
*******************************************************************************/

/***************************************************************************//*!
 * @brief   Debug uart function definition
 * @details Function provided debug print
 * @param   str - pointer to string array
 * @note    Implemented as glogal function
 * @warning Non.
 ******************************************************************************/
void debug_prints(char *str)
{
  LPUART_PutStr(LPUART0, str);
}
/*! @} End of frdm_usb_vcom_test_functions_def                                        */

/*******************************************************************************
 * End of main module                                                          *
 *******************************************************************************/

