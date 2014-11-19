/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      frdm_slcd_test.c
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
extern void pit_callback (PIT_CALLBACK_TYPE type);

/* module function prototypes                                                 */
static void lcd_runningtext (uint8 u8TextPos, int8 *p_u8Char);

/*******************************************************************************
*//*! @addtogroup frdm_slcd_test_variables_def
* @{ 
*   Module global variables definitions are provided here.
*******************************************************************************/

/*! @} End of frdm_slcd_test_variables_def                                        */


/*******************************************************************************
 * @brief   main routine
 ******************************************************************************/
int main (void)
{  
  SIM_Init (SIM_MODULE_FRDM_SLCD_CONFIG);
  MCG_LITE_Init (MCG_LITE_HIRC_48MHZ);
  
  // OSC module initialization
  OSC_Init(OSC_MODULE_OSCERCLK_ON_STOPMODE_ON_CONFIG(OSC_SC16P));
  MCG_ExtClkType(OSC_REQST);
  MCG_CrystalMode(LOW_POWER_OSC);
  MCG_CrystalFreqRangeSel(LOW_FREQ_RANGE);
  MCG_WaitOscInit();
  
  // VLLx, VCAPx pins disable
  PORT_Init(PORTC, PORT_MODULE_DISABLED_MODE, PIN_20|PIN_21|PIN_22|PIN_23, 0, NULL);
  // SLCD pin configuration
  PORT_Init(PORTE, PORT_MODULE_ALT0_MODE, PIN_20|PIN_21, 0, NULL);
  PORT_Init(PORTB, PORT_MODULE_ALT0_MODE, PIN_18|PIN_19, 0, NULL);
  PORT_Init(PORTC, PORT_MODULE_ALT0_MODE, PIN_0|PIN_4|PIN_6|PIN_7, 0, NULL);
  PORT_Init(PORTD, PORT_MODULE_ALT0_MODE, PIN_0|PIN_2|PIN_3|PIN_4, 0, NULL);
  // SLCD initialization
  LCD_Init (LCD_FRDM_CONFIG,                                                    \
            LCD_FRONT_PLANE_PINS_FRDM_KL43,                                     \
            LCD_BACK_PLANE_PINS_FRDM_KL43,                                      \
            LCD_ASSIGN_BACK_PLANES_FRDM_KL43);
  //LCD_Write_Segments(LCD_ALL_SEGMENTS_OFF_FRDM_KL43);
  LCD_Delete_Char(0);
  LCD_Delete_Char(1);
  LCD_Delete_Char(2);
  LCD_Delete_Char(3);
  // PIT initialization - CH0 for LCD intro text running 
  PIT_Init (PIT0, CH0, PIT_CH_TIMER_EN_CONFIG, 6000000, 1, pit_callback);
  
  __enable_irq();
  
  while (1)
  {
    
  }
}

/*******************************************************************************
*//*! @addtogroup frdm_slcd_test_functions_def
* @{ 
*   Module local function definitions are provided here.
*******************************************************************************/
/***************************************************************************//*!
* @brief   PIT Callback function - CH0
 ******************************************************************************/
void pit_callback (PIT_CALLBACK_TYPE type)
{
  static uint8 u8Blink = 2;
  
  if (type&PIT0CH0_CALLBACK)
  {
    lcd_runningtext((u8Blink&0xF),"HELLO FSL LCD  ");
    u8Blink++;
  }
}

/***************************************************************************//*!
 * @brief   Function for signalizing an accelerometer data to LCD.
 ******************************************************************************/
static void lcd_runningtext (uint8 u8TextPos, int8 *p_u8Char)
{
  static uint8 i, u8ActChar;
  
  LCD_Delete_Char(0);
  LCD_Delete_Char(1);
  LCD_Delete_Char(2);
  LCD_Delete_Char(3);
  for (i = 0; i < 4; i++)
  {
    LCD_GOTO(i);
    u8ActChar = *(p_u8Char+u8TextPos+i-2);
    LCD_Write_Char (u8ActChar); 
  }
}
/*! @} End of frdm_slcd_test_functions_def                                        */


/*******************************************************************************
 * End of main module                                                          *
 *******************************************************************************/

