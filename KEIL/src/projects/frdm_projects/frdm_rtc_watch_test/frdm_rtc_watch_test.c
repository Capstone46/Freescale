/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      frdm_rtc_watch_test.c
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
extern void rtc_callback (RTC_CALLBACK_TYPE type);
/* module function prototypes                                                 */
static void lcd_settime (tTIME *p_time);

/*******************************************************************************
*//*! @addtogroup frdm_rtc_watch_test_variables_def
* @{ 
*   Module global variables definitions are provided here.
*******************************************************************************/
static tTIME time;              ///< rtc data structure (defined in rtc.h)

static uint16 alarm_interval = 60;      ///< variable for setting the alarm interval (10s)
static const char digits[]=
{
  '0','1','2','3','4','5','6','7','8','9'
};   
/*! @} End of frdm_rtc_watch_test_variables_def                                        */


/*******************************************************************************
 * @brief   main routine
 ******************************************************************************/
int main (void)
{  
  SIM_Init (SIM_MODULE_FRDM_RTC_WATCH_CONFIG);
  MCG_LITE_Init (MCG_LITE_HIRC_48MHZ);
  
  // OSC module initialization
  OSC_Init(OSC_MODULE_OSCERCLK_ON_STOPMODE_ON_CONFIG(OSC_SC16P));
  MCG_ExtClkType(OSC_REQST);
  MCG_CrystalMode(LOW_POWER_OSC);
  MCG_CrystalFreqRangeSel(LOW_FREQ_RANGE);
  MCG_WaitOscInit();
  
  // LEDs initialization
  PORT_Init (PORTD, PORT_MODULE_ALT1_MODE, PIN_5, 0, NULL);
  GPIO_Init (GPIOD, GPIO_PIN_OUTPUT, PIN_5);
  GPIO_Set (GPIOD, PIN_5);
  PORT_Init (PORTE, PORT_MODULE_ALT1_MODE, PIN_31, 0, NULL);
  GPIO_Init (GPIOE, GPIO_PIN_OUTPUT, PIN_31);
  GPIO_Set (GPIOE, PIN_31);
  
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
  LCD_Delete_Char(0);
  LCD_Delete_Char(1);
  LCD_Delete_Char(2);
  LCD_Delete_Char(3);
  
  // Set the time according to system clock
  BUILD_DATE_TIME(time);
  // RTC initialization
  RTC_Init (RTC_MODULE_FRDM_RTC_WATCH_CONFIG, RTC_MkTime (&time), 3, rtc_callback);
  RTC_SetAlarm (RTC_GetTime ()+alarm_interval);
  // Write time to the LCD
  lcd_settime(&time);
  
  __enable_irq();
  
  while (1)
  {
    
  }
}

/*******************************************************************************
*//*! @addtogroup frdm_rtc_watch_test_functions_def
* @{ 
*   Module local function definitions are provided here.
*******************************************************************************/
/***************************************************************************//*!
 * @brief   RTC Callback function (second interrupt, alarm interrupt).
 ******************************************************************************/
void rtc_callback (RTC_CALLBACK_TYPE type)
{ 
  if (type == TAF_CALLBACK) 
  { 
    RTC_SetAlarm (RTC_GetTime()+alarm_interval);
    GPIO_Tgl (GPIOE, PIN_31);
  }
  if (type == TSF_CALLBACK) 
  { 
    RTC_GmTime (RTC_GetTime(),&time);
    lcd_settime(&time);
    GPIO_Tgl (GPIOD, PIN_5);
  }
}

/***************************************************************************//*!
 * @brief   Function for writting a time to LCD.
 ******************************************************************************/
static void lcd_settime (tTIME *p_time)
{ 
  static uint8 u8Tgl = 0;
  LCD_Delete_Char(0);
  LCD_Delete_Char(1);
  LCD_Delete_Char(2);
  LCD_Delete_Char(3);
  LCD_GOTO(0);
  LCD_Write_Char (digits[p_time->tm_hour/10]);
  LCD_GOTO(1);
  LCD_Write_Char (digits[p_time->tm_hour%10]);
  LCD_GOTO(2);
  LCD_Write_Char (digits[p_time->tm_min/10]);  
  LCD_GOTO(3);
  LCD_Write_Char (digits[p_time->tm_min%10]);
  if(u8Tgl=!u8Tgl)  
  {
    _LCD_CHAR_V_COL_ON;
  }
  else
  {
    _LCD_CHAR_V_COL_OFF;
  }
}

/*! @} End of frdm_rtc_watch_test_functions_def                                        */


/*******************************************************************************
 * End of main module                                                          *
 *******************************************************************************/

