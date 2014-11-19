/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      sgtl5000.c
 * @author    b01800
 * @version   0.0.1.0
 * @date      March-28-2014
 * @brief     Driver for TWR-AUDIO-SGTL5000 card
 * @note          
 ******************************************************************************/
#include "common.h"
#include "sgtl5000.h"
#include "i2c\i2c.h"

/* I2C Address */
#define I2C_AUDIO_CODEC_ADDRESS 0x0A ///< SGTL5000 I2C address

/* module function prototypes                                                 */
static void writeSgtl500Reg(unsigned short regNumber, unsigned short regValue);
static void EnterCriticalSection(void);
static void ExitCriticalSection(void);
/*******************************************************************************
*//*! @addtogroup sgtl5000_variables_def
* @{ 
*   Module global variables definitions are provided here.
*******************************************************************************/
unsigned char i2cData[4];             ///< sgtl5000 i2c data buffer
/*! @} End of sgtl5000_variables_def                                          */

/**************************************************************************//*!
 * @brief  Function manages the initial codec setup via I2C
 * @param  none
 * @return none 
 ******************************************************************************/
void sgtl5000_Init(void)
{  
    // Configuration for 1.8V, 1.8V, 1.8V VDDD, VDDA, VDDIO
    // Set VDDD regulator
    writeSgtl500Reg( SGTL5000_CHIP_LINREG_CTRL, 0x000c);
    // Enable internal oscillator for charge pump
    writeSgtl500Reg( SGTL5000_CHIP_CLK_TOP_CTRL, 0x0800);
    // Set VAG level, ref bias to -50%
    writeSgtl500Reg( SGTL5000_CHIP_REF_CTRL, 0x01EE);
    // Set LINREG level to 1V
    writeSgtl500Reg( SGTL5000_CHIP_LINREG_CTRL, 0x000C);
    // Set LINEOUT voltage/current
    writeSgtl500Reg( SGTL5000_CHIP_LINE_OUT_CTRL, 0x0F04);
    // Set LO volume
    writeSgtl500Reg( SGTL5000_CHIP_LINE_OUT_VOL, 0x0F0F); 
    // Power up CPUMP, Power up VAG, Turn off VDDD regulators (using ext supplies)
    writeSgtl500Reg( SGTL5000_CHIP_ANA_POWER, 0x42FB);
    // Power up digital blocks
    writeSgtl500Reg( SGTL5000_CHIP_DIG_POWER, 0x01FD); // sgtl5000 I2S out dis
    // Set clocks for 48kHz, 256*Fs   
    // 48.0 kHz, MCLK = 256x48kHz =12.288 MHz Do not use PLL
    writeSgtl500Reg( SGTL5000_CHIP_CLK_CTRL, 0x0008);    
    // Set Slave, 32-bit I2S, playing with data justification / polarity
    //writeSgtl500Reg( SGTL5000_CHIP_I2S_CTRL, 0x0000); // CPOL normal, 32-bit
    //writeSgtl500Reg( SGTL5000_CHIP_I2S_CTRL, 0x0070); // CPOL invert, 16-bit
    writeSgtl500Reg( SGTL5000_CHIP_I2S_CTRL, 0x0030);   // CPOL normal, 16-bit
    // Set I/O configuration
    // i2s in to dac (i.e.output from Kinetis tower card)   
    // I2S_IN->DAC (SGTL5000)
    writeSgtl500Reg( SGTL5000_CHIP_SSS_CTRL, 0x0010);
    // Set Unmute DAC, ADC
    //writeSgtl500Reg( SGTL5000_CHIP_ADCDAC_CTRL, 0x0230);
    writeSgtl500Reg( SGTL5000_CHIP_ADCDAC_CTRL, 0x0000);        
    writeSgtl500Reg( SGTL5000_CHIP_DAC_VOL, 0x0000);
    // Lineout Volume Adjustment   
    writeSgtl500Reg( SGTL5000_CHIP_LINE_OUT_VOL, 0x0F0F); 
    // Set Line Out Analog Ground to 1.55V
    writeSgtl500Reg( SGTL5000_CHIP_LINE_OUT_CTRL, 0x0F1E); 
    // Unmute Analog Outputs
    writeSgtl500Reg( SGTL5000_CHIP_ANA_CTRL ,0x0000);
}

/**************************************************************************//*!
 * @brief  Function controls the sgtl5000 internal equalizer
 * @param  band_addr Band 0,1,2,3,4 (115Hz, 330Hz, 990Hz, 3000Hz, 9900Hz)
 * @param  dBVal     +/-12dB
 * @return void 
 ******************************************************************************/
void Sgtl500_Set_Equalizer(unsigned char band_addr, signed char dBVal)
{
  unsigned char set_dB;
  if((band_addr > 4) || (dBVal >12) || (dBVal < -12) ) return; 
  set_dB = (unsigned char)(dBVal * 4) + 47;
  if(set_dB > 0x5F) return;
  // Write settings to SGTL5000
  writeSgtl500Reg(SGTL5000_DAP_AUDIO_EQ,0x0003);
  writeSgtl500Reg((SGTL5000_DAP_AUDIO_EQ_BASS_BAND0 + band_addr), set_dB); 
}

/**************************************************************************//*!
 * @brief  Function controls the volume settings in the range +/-12dB
 * @param  vol_left  -left channel volume level  [0..vol_steps]
 * @param  vol_right -right channel volume level [0..vol_steps]
 * @param  vol_steps -how many steps for full scale range
 * @return none 
 ******************************************************************************/
void Sgtl500_Set_Volume(unsigned char vol_left, unsigned char vol_right, unsigned char vol_steps)
{   
   uint16_t volume;
   unsigned char * p_volume = (unsigned char*)&volume;
   
   if(vol_left > vol_steps) vol_left = vol_steps;
   if(vol_right > vol_steps) vol_right = vol_steps;
   p_volume[0] = 0x80 - (vol_left * (0x80  / (vol_steps)));
   p_volume[1] = 0x80 - (vol_right * (0x80 / (vol_steps)));
   if(p_volume[0] > 0x7f) p_volume[0] = 0x7f;
   if(p_volume[1] > 0x7f) p_volume[1] = 0x7f;
      
   writeSgtl500Reg(SGTL5000_CHIP_ANA_HP_CTRL, volume);
}

/**************************************************************************//*!
 * @brief  Function controls codec settings via I2C
 * @param  regNumber -number(addr) of the SGTL5000 internal register
 * @param  regValue  -value to be written to register
 * @return none 
 ******************************************************************************/
static void writeSgtl500Reg(unsigned short regNumber, unsigned short regValue) 
{
  EnterCriticalSection();
     
  i2cData[0] = (regNumber & 0xFF00) >> 8;
  i2cData[1] = (unsigned char)(regNumber & 0x00FF);
  i2cData[2] = (regValue & 0xFF00) >> 8;
  i2cData[3] = (unsigned char)(regValue & 0x00FF);  
  
  I2C1_WriteMultiBytes(I2C_AUDIO_CODEC_ADDRESS,i2cData[0], &i2cData[1], 3); // dev. addr, reg.addr + data
  ExitCriticalSection();
}

/**************************************************************************//*!
 * @brief  Disable IRQs globally during the I2C communication
 ******************************************************************************/
static void EnterCriticalSection(void)
{
  __disable_irq(); // disable all IRQs globally
}
/**************************************************************************//*!
 * @brief  Re-enable IRQs globally during the I2C communication
 ******************************************************************************/
static void ExitCriticalSection(void)
{
  __enable_irq(); // re-enable all IRQs globally
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/


