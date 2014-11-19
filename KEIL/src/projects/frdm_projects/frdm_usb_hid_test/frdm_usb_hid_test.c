/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      frdm_usb_hid_test.c
 * @author    
 * @version   0.0.1.0
 * @date      Jun-20-2013
 * @brief     
 ******************************************************************************/
#include "common.h"
#include "drivers.h"
#include "derivative.h"
#include "types.h"
#include "usb_hid.h"
#include "usb_mouse.h"

#include "mma845x.h"

#define BUTTON_LEFT()   (GPIO_Get(GPIOC) & PIN_3)
#define BUTTON_RIGTH()  (GPIO_Get(GPIOA) & PIN_4)
#define LED1_ON()       GPIO_Clr(GPIOE, PIN_31)
#define LED1_OFF()      GPIO_Set(GPIOE, PIN_31)
#define LED2_ON()       GPIO_Clr(GPIOD, PIN_5)
#define LED2_OFF()      GPIO_Set(GPIOD, PIN_5)

/* callback functions prototypes                                              */

/* module function prototypes                                                 */
void pit_callback (PIT_CALLBACK_TYPE type); ///< PIT Callback fuction

void debug_prints(char *str);               ///< Debug print string function

/*******************************************************************************
*//*! @addtogroup frdm_usb_hid_test_variables_def
* @{ 
*   Module global variables definitions are provided here.
*******************************************************************************/
static uint16_t  x_refval, y_refval;       ///< pointer reference position
static uint8_t   is_calibrated;
static uint8_t left_button, rigth_button;  ///< mouse button variables
static int8_t  x, y;                       ///< mouse cursor variables
/*! @} End of frdm_usb_hid_test_variables_def                                 */


/*******************************************************************************
 * @brief   main routine
 ******************************************************************************/
int main (void)
{  
  SIM_Init (SIM_MODULE_FRDM_USB_VCOM_CONFIG);
  MCG_LITE_Init (MCG_LITE_HIRC_48MHZ);

  /* Initialize Debug UART module */
  PORT_Init  (PORTA, PORT_MODULE_ALT2_MODE, PIN_1|PIN_2, 0, NULL);
  LPUART_Init(LPUART0, LPUART_POLLMODE_CONFIG(115200, 48e6), 0, NULL);
  
  /* Initialize GPIO module (Buttons) */
  PORT_Init  (PORTC, PORT_MODULE_BUTTON_MODE, PIN_3, 0, NULL);  /* SW1  */
  PORT_Init  (PORTA, PORT_MODULE_BUTTON_MODE, PIN_4, 0, NULL);  /* SW2  */
  
  /* Initialize GPIO module (LEDs) */
  PORT_Init  (PORTE, PORT_MODULE_LED_MODE, PIN_31, 0, NULL);    /* LED1 */
  GPIOE_Init (GPIO_PIN_OUTPUT, PIN_31);
  PORT_Init  (PORTD, PORT_MODULE_LED_MODE, PIN_5, 0, NULL);     /* LED2 */
  GPIOD_Init (GPIO_PIN_OUTPUT, PIN_5);
  
  /* PIT initialization - CH0 used just as ACCEL data reading */
  PIT_Init (PIT0, CH0, PIT_CH_TIMER_EN_CONFIG, 500000, 3, pit_callback);
  
  /* I2C initialization */
  PORT_Init (PORTE, PORT_MODULE_ALT5_PULLUP_MODE, PIN_24|PIN_25, 0, NULL);
  I2C_Init(I2C0, I2C_MODULE_MASTER_BAUD_50K_CLK_48MHZ, 0, NULL);
  
  /* Accelerometer initialization */
  MMA845x_Init(I2C0);
  MMA845x_Active(I2C0);
      
  debug_prints("<I> CORE Initialization OK \n\r");
    
  __enable_irq();     /* Enable global interrupt */
  
  USB_Mouse_Init();   /* Initialize USB module   */
  
  is_calibrated = 0;

  while (1)
  {
    
  }
}

/*******************************************************************************
*//*! @addtogroup frdm_usb_hid_test_functions_def
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

/***************************************************************************//*!
 * @brief   PIT Callback function - CH0 and CH1
 ******************************************************************************/
void pit_callback (PIT_CALLBACK_TYPE type)
{  
  uint16_t x_accval, y_accval;
  
  if (type & PIT0CH0_CALLBACK)
  {    
    TWR_MMA845X  sMMA845x_AccelData;
    MMA845x_ReadRawData(I2C0, &sMMA845x_AccelData);
    
    /* convert signed values from accelerometer to unsigned */
    x_accval = (uint16_t)(sMMA845x_AccelData.x + (0xFFFF/2));
    y_accval = (uint16_t)(sMMA845x_AccelData.y + (0xFFFF/2));
      
    /* reset old values */
    left_button = rigth_button = x = y = 0;
    
    if(!is_calibrated)
    {
      is_calibrated = 1;
      
      /* update pointer reference values */
      x_refval = x_accval;
      y_refval = y_accval;
    }
    
    /* Read Left Button state */
    if(!BUTTON_LEFT())
    {
      left_button = 1;
      LED1_ON();
    }
    else
    {
      LED1_OFF();
    }
    
    /* Read Rigth Button state */
    if(!BUTTON_RIGTH())
    {
      rigth_button = 1;
      LED2_ON();
    }
    else
    {
      LED2_OFF();
    }
    
    if((x_refval - (TOLERANCE/2)) > x_accval)
    {
      /* move rigth */
      x = (x_refval - (TOLERANCE*2)) > x_accval ? STEP_SIZE*4 : STEP_SIZE; 
    }
    
    if((x_refval + (TOLERANCE/2)) < x_accval)
    {   
      /* move rigth */
      x = (x_refval + (TOLERANCE*2)) < x_accval ? -STEP_SIZE*4 : -STEP_SIZE; 
    }
    
    if((y_refval - (TOLERANCE/2)) > y_accval)
    {
      /* move up */
      y = (y_refval - (TOLERANCE*2)) > y_accval ? STEP_SIZE*4 : STEP_SIZE;    
    }
        
    if((y_refval + (TOLERANCE/2)) < y_accval)
    {
      /* move down */
      y = (y_refval + (TOLERANCE*2)) < y_accval ? -STEP_SIZE*4 : -STEP_SIZE;
    }
    
    /* Update Mouse data */
    USB_Mouse_Update(left_button, rigth_button, x, y);
  }
}

/*! @} End of frdm_usb_hid_test_functions_def                                        */


/*******************************************************************************
 * End of main module                                                          *
 *******************************************************************************/

