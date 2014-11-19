/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      frdm_accel_test.c
 * @author    
 * @version   0.0.1.0
 * @date      Jun-20-2013
 * @brief     
 ******************************************************************************/
#include "common.h"
#include "drivers.h"
#include "mma845x.h"
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* User Defined Data Types */
#include "usb_hid.h"

/* callback functions prototypes                                              */
extern void pit_callback (PIT_CALLBACK_TYPE type);
static void portc_callback(vuint32 pin_number);
/* module function prototypes                                                 */
static void lcd_accelvalue (TWR_MMA845X *AccelData);

/*******************************************************************************
*//*! @addtogroup frdm_accel_test_variables_def
* @{ 
*   Module global variables definitions are provided here.
*******************************************************************************/
static TWR_MMA845X sMMA845x_AccelData;  ///> accelerometer data structure
/*! @} End of frdm_accel_test_variables_def                                        */


/*******************************************************************************
 * @brief   main routine
 ******************************************************************************/
int main (void)
{  
  SIM_Init (SIM_MODULE_CONFIG_FRDM_ACCEL_CONFIG);
  MCG_LITE_Init (MCG_LITE_HIRC_48MHZ);
  
  // OSC module initialization
  OSC_Init(OSC_MODULE_OSCERCLK_ON_STOPMODE_ON_CONFIG(OSC_SC16P));
  MCG_ExtClkType(OSC_REQST);
  MCG_CrystalMode(LOW_POWER_OSC);
  MCG_CrystalFreqRangeSel(LOW_FREQ_RANGE);
//  MCG_WaitOscInit();
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
  
  // PIT initialization - CH0 used just as ACCEL data reading
  PIT_Init (PIT0, CH0, PIT_CH_TIMER_EN_CONFIG, 1000000, 3, pit_callback);
    // Configure PTE 0/1 as SCL/SDA
  PORT_Init (PORTE, PORT_MODULE_ALT5_PULLUP_MODE, PIN_24|PIN_25, 0, NULL);  
  I2C_Init(I2C0, I2C_MODULE_MASTER_BAUD_100K_CLK_48MHZ, 0, NULL);
  // Accel initialization
  MMA845x_Init(I2C0);
  MMA845x_Standby(I2C0);
  MMA845x_IntPolarityLow(I2C0);
  MMA845x_OpenDrainEnable(I2C0);
  MMA845x_InterruptDisable(I2C0, 0xFF);
  MMA845x_InterruptEnable(I2C0, INT_CFG_DRDY_MASK);
  MMA845x_InterruptOnINT1(I2C0, INT_CFG_DRDY_MASK);
  MMA845X_WRITE_REGISTER(I2C0, MMA845x_CTRL_REG1_REG, DR_100HZ);
  MMA845x_Active(I2C0);
    // INT1/INT2 pins of MMA845x
  PORT_Init(PORTC, PORT_MODULE_BUTTON_IRQRE_MODE, PIN_5, 1, portc_callback);
  GPIO_Init(GPIOC, GPIO_PIN_INPUT, PIN_5);
  
  __enable_irq();
  
  while (1)
  {
    
  }
}

/*******************************************************************************
*//*! @addtogroup frdm_accel_test_functions_def
* @{ 
*   Module local function definitions are provided here.
*******************************************************************************/

/***************************************************************************//*!
 * @brief   PORTC Callback function - INT1 of MMA845x
 ******************************************************************************/
static void portc_callback(vuint32 pin_number)
{
  if (pin_number&PIN_5)
  {
    lcd_accelvalue(&sMMA845x_AccelData);
  }
}

/***************************************************************************//*!
* @brief   PIT Callback function - CH0
 ******************************************************************************/
void pit_callback (PIT_CALLBACK_TYPE type)
{  
  if (type&PIT0CH0_CALLBACK)
  {
    MMA845x_ReadRawData(I2C0,&sMMA845x_AccelData);
  }
}

/***************************************************************************//*!
 * @brief   Function for signalizing an accelerometer data to LCD.
 ******************************************************************************/
static void lcd_accelvalue (TWR_MMA845X *AccelData)
{
  if ((AccelData->y > 1000) || (AccelData->y < (-8000)))
    { _LCD_CHAR_V_1E_ON; _LCD_CHAR_V_1F_ON; }
  else 
    { _LCD_CHAR_V_1E_OFF; _LCD_CHAR_V_1F_OFF; }
  if ((AccelData->y > 2000) || (AccelData->y < (-7000)))
    { _LCD_CHAR_V_1B_ON; _LCD_CHAR_V_1C_ON; }
  else 
    { _LCD_CHAR_V_1B_OFF; _LCD_CHAR_V_1C_OFF; }
  if ((AccelData->y > 3000) || (AccelData->y < (-6000))) 
    { _LCD_CHAR_V_2E_ON; _LCD_CHAR_V_2F_ON; }
  else 
    { _LCD_CHAR_V_2E_OFF; _LCD_CHAR_V_2F_OFF; }
  if ((AccelData->y > 4000) || (AccelData->y < (-5000)))
    { _LCD_CHAR_V_2B_ON; _LCD_CHAR_V_2C_ON; }
  else 
    { _LCD_CHAR_V_2B_OFF; _LCD_CHAR_V_2C_OFF; }
  if ((AccelData->y > 5000) || (AccelData->y < (-4000))) 
    { _LCD_CHAR_V_3E_ON; _LCD_CHAR_V_3F_ON; }
  else 
    { _LCD_CHAR_V_3E_OFF; _LCD_CHAR_V_3F_OFF; }
  if ((AccelData->y > 6000) || (AccelData->y < (-3000)))
    { _LCD_CHAR_V_3B_ON; _LCD_CHAR_V_3C_ON; }
  else 
    { _LCD_CHAR_V_3B_OFF; _LCD_CHAR_V_3C_OFF; }
  if ((AccelData->y > 7000)  || (AccelData->y < (-2000)))
    { _LCD_CHAR_V_4E_ON; _LCD_CHAR_V_4F_ON; }
  else 
    { _LCD_CHAR_V_4E_OFF; _LCD_CHAR_V_4F_OFF; }
  if ((AccelData->y > 8000) || (AccelData->y < (-1000)))
    { _LCD_CHAR_V_4B_ON; _LCD_CHAR_V_4C_ON; }
  else 
    { _LCD_CHAR_V_4B_OFF; _LCD_CHAR_V_4C_OFF; }
}

/*! @} End of frdm_accel_test_functions_def                                        */


/*******************************************************************************
 * End of main module                                                          *
 *******************************************************************************/

