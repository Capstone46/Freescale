/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      fxos8700.c
 * @author    modified by B34185
 * @version   1.0.5.0
 * @date      Apr-24-2013
 * @brief     FXOS8700 acceleromenter/magnetometer driver implementation.
 * @par       Driver example:
 * @include   i2c_test\i2c_test.c
 ******************************************************************************/
#include "common.h"
#include "i2c.h"
#include "flexio.h"
#include "flexio_i2c/flexio_i2c.h"
#include "fxos8700.h"

static uint8 FXOS8700_enabled = FALSE;
static FXOS8700_IDS whoiam;

/**************************************************************************//*!
* @brief    The I2C0 module Initialization for FXOS8700
* @param    void
******************************************************************************/
void FXOS8700_I2C0_Init(void)
{
 if(FXOS8700_enabled != TRUE)
 {
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG, 0x01);
  whoiam = (FXOS8700_IDS)FXOS8700_READ_REGISTER(I2C0, FXOS8700_WHO_AM_I_REG);
  FXOS8700_enabled = TRUE;
 }
}

/**************************************************************************//*!
* @brief    The I2C1 module Initialization for FXOS8700
* @param    void
******************************************************************************/
void FXOS8700_I2C1_Init(void)
{
 if(FXOS8700_enabled != TRUE)
 {
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG, 0x01);
  whoiam = (FXOS8700_IDS)FXOS8700_READ_REGISTER(I2C1, FXOS8700_WHO_AM_I_REG);
  FXOS8700_enabled = TRUE;
 }
}

/**************************************************************************//*!
* @brief    Deintitialization for purposes of module id driver's
******************************************************************************/
void FXOS8700_I2C0_DeInit(void)
{
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG, 0x00);
  FXOS8700_enabled = FALSE;
}

/**************************************************************************//*!
* @brief    Deintitialization for purposes of module id driver's
******************************************************************************/
void FXOS8700_I2C1_DeInit(void)
{
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG, 0x00);
  FXOS8700_enabled = FALSE;
}

/**************************************************************************//*!
* @brief    Write the xg dynamic range value into XYZ_DATA_CFG register
* @param    mask - FULL_SCALE_2G|FULL_SCALE_4G|FULL_SCALE_8G
******************************************************************************/
void FXOS8700_I2C0_DynamicRange (uint8 mask)
{
  uint8 n;

  FXOS8700_Standby(I2C0);
  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_XYZ_DATA_CFG_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_XYZ_DATA_CFG_REG, n & ~FULL_SCALE_MASK);
  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_XYZ_DATA_CFG_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_XYZ_DATA_CFG_REG, n | mask);
  FXOS8700_Active(I2C0);
}

/**************************************************************************//*!
* @brief    Write the xg dynamic range value into XYZ_DATA_CFG register
* @param    mask - FULL_SCALE_2G|FULL_SCALE_4G|FULL_SCALE_8G
******************************************************************************/
void FXOS8700_I2C1_DynamicRange (uint8 mask)
{
  uint8 n;

  FXOS8700_Standby(I2C1);
  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_XYZ_DATA_CFG_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_XYZ_DATA_CFG_REG, n & ~FULL_SCALE_MASK);
  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_XYZ_DATA_CFG_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_XYZ_DATA_CFG_REG, n | mask);
  FXOS8700_Active(I2C1);
}

/**************************************************************************//*!
 * @brief    Write auto wake sampling frequency when device is in SLEEP mode
 *           into CTRL_REG1 register.
 * @param    mask - WAKE_50HZ|WAKE_12_5HZ|WAKE_6_25HZ|WAKE_1_56HZ
******************************************************************************/
void FXOS8700_I2C0_AutoWake (uint8 mask)
{
  uint8 n;

  FXOS8700_Standby(I2C0);
  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG, n & ~WAKE_MASK);
  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG, n | mask);
  FXOS8700_Active(I2C0);
}

/**************************************************************************//*!
 * @brief    Write auto wake sampling frequency when device is in SLEEP mode
 *           into CTRL_REG1 register.
 * @param    mask - WAKE_50HZ|WAKE_12_5HZ|WAKE_6_25HZ|WAKE_1_56HZ
******************************************************************************/
void FXOS8700_I2C1_AutoWake (uint8 mask)
{
  uint8 n;

  FXOS8700_Standby(I2C1);
  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG, n & ~WAKE_MASK);
  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG, n | mask);
  FXOS8700_Active(I2C1);
}

/**************************************************************************//*!
 * @brief    Write the data rate value into CTRL_REG1 register
 * @param    mask - DR_800HZ|DR_400HZ|DR_200HZ|DR_100HZ|DR_50HZ|DR_12_5_HZ|
 *                  DR_6_25_HZ|DR_1_563_HZ
******************************************************************************/
void FXOS8700_I2C0_DataRate (uint8 mask)
{
  uint8 n;

  FXOS8700_Standby(I2C0);
  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG, n & ~DR_MASK);
  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG, n | mask);
  FXOS8700_Active(I2C0);
}

/**************************************************************************//*!
 * @brief    Write the data rate value into CTRL_REG1 register
 * @param    mask - DR_800HZ|DR_400HZ|DR_200HZ|DR_100HZ|DR_50HZ|DR_12_5_HZ|
 *                  DR_6_25_HZ|DR_1_563_HZ
******************************************************************************/
void FXOS8700_I2C1_DataRate (uint8 mask)
{
  uint8 n;

  FXOS8700_Standby(I2C1);
  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG, n & ~DR_MASK);
  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG, n | mask);
  FXOS8700_Active(I2C1);
}

/**************************************************************************//*!
* @brief    Put sensor into reduced noise mode
******************************************************************************/
void FXOS8700_I2C0_LowNoiseEnable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG, n | LOW_NOISE_MASK);
}

/**************************************************************************//*!
* @brief    Put sensor into reduced noise mode
******************************************************************************/
void FXOS8700_I2C1_LowNoiseEnable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG, n | LOW_NOISE_MASK);
}

/**************************************************************************//*!
* @brief    Disable reduced noise mode of sensor.
******************************************************************************/
void FXOS8700_I2C0_LowNoiseDisable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG, n & ~LOW_NOISE_MASK);
}

/**************************************************************************//*!
* @brief    Disable reduced noise mode of sensor.
******************************************************************************/
void FXOS8700_I2C1_LowNoiseDisable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG, n & ~LOW_NOISE_MASK);
}

/**************************************************************************//*!
* @brief    Put sensor into fast read mode
******************************************************************************/
void FXOS8700_I2C0_FastReadEnable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG, n | FAST_READ_MASK);
}

/**************************************************************************//*!
* @brief    Put sensor into fast read mode
******************************************************************************/
void FXOS8700_I2C1_FastReadEnable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG, n | FAST_READ_MASK);
}

/**************************************************************************//*!
* @brief    Disable fast read mode
******************************************************************************/
void FXOS8700_I2C0_FastReadDisable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG, n & ~FAST_READ_MASK);
}

/**************************************************************************//*!
* @brief    Disable fast read mode
******************************************************************************/
void FXOS8700_I2C1_FastReadDisable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG, n & ~FAST_READ_MASK);
}

/**************************************************************************//*!
* @brief    Put sensor into Active Mode by setting the Active bit
******************************************************************************/
void FXOS8700_I2C0_Active (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG, n | ACTIVE_MASK);
}

/**************************************************************************//*!
* @brief    Put sensor into Active Mode by setting the Active bit
******************************************************************************/
void FXOS8700_I2C1_Active (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG, n | ACTIVE_MASK);
}

/**************************************************************************//*!
* @brief    Put sensor into Standby Mode by clearing the Active bit
******************************************************************************/
void FXOS8700_I2C0_Standby (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG1_REG, n & ~ACTIVE_MASK);
}

/**************************************************************************//*!
* @brief    Put sensor into Standby Mode by clearing the Active bit
******************************************************************************/
void FXOS8700_I2C1_Standby (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG1_REG, n & ~ACTIVE_MASK);
}

/**************************************************************************//*!
* @brief    Put sensor into self test.
******************************************************************************/
void FXOS8700_I2C0_SelfTestEnable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG, n | SELF_TEST_MASK);
}

/**************************************************************************//*!
* @brief    Put sensor into self test.
******************************************************************************/
void FXOS8700_I2C1_SelfTestEnable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG, n | SELF_TEST_MASK);
}

/**************************************************************************//*!
* @brief    Disable self test.
******************************************************************************/
void FXOS8700_I2C0_SelfTestDisable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG, n & ~SELF_TEST_MASK);
}

/**************************************************************************//*!
* @brief    Disable self test.
******************************************************************************/
void FXOS8700_I2C1_SelfTestDisable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG, n & ~SELF_TEST_MASK);
}

/**************************************************************************//*!
* @brief    Activate the software reset
******************************************************************************/
void FXOS8700_I2C0_Reset (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG, n | RESET_MASK);
}

/**************************************************************************//*!
* @brief    Activate the software reset
******************************************************************************/
void FXOS8700_I2C1_Reset (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG, n | RESET_MASK);
}



/**************************************************************************//*!
* @brief    Auto sleep enable.
******************************************************************************/
void FXOS8700_I2C0_AutoSleepEnable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG, n | AUTO_SLEEP_MASK);
}

/**************************************************************************//*!
* @brief    Auto sleep enable.
******************************************************************************/
void FXOS8700_I2C1_AutoSleepEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG, n | AUTO_SLEEP_MASK);
}

/**************************************************************************//*!
* @brief    Auto sleep disable.
******************************************************************************/
void FXOS8700_I2C0_AutoSleepDisable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG, n & ~AUTO_SLEEP_MASK);
}

/**************************************************************************//*!
* @brief    Auto sleep disable.
******************************************************************************/
void FXOS8700_I2C1_AutoSleepDisable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG, n & ~AUTO_SLEEP_MASK);
}

/**************************************************************************//*!
 * @brief    Write the over sampling value into CTRL_REG2 register
 * @param    mask - MODS_NORMAL|MODS_LOW_NOISE|MODS_HIGH_RESOLUTION
 *                  MODS_LOW_POWER|MODS_SLEEP_NORMAL|MODS_SLEEP_LOW_NOISE
 *                  MODS_SLEEP_HIGH_RESOLUTION|MODS_SLEEP_LOW_POWER
 *                  MODS_BOTH_NORMAL|MODS_BOTH_LOW_NOISE|MODS_BOTH_HIGH_RESOLUTION
 *                  MODS_BOTH_LOW_POWER
******************************************************************************/
void FXOS8700_I2C0_OverSampling (uint8 mask)
{
  uint8 n;

  FXOS8700_Standby(I2C0);
  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG, n & ~MODS_BOTH_LOW_POWER);
  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG2_REG, n | mask);
  FXOS8700_Active(I2C0);
}

/**************************************************************************//*!
 * @brief    Write the over sampling value into CTRL_REG2 register
 * @param    mask - MODS_NORMAL|MODS_LOW_NOISE|MODS_HIGH_RESOLUTION
 *                  MODS_LOW_POWER|MODS_SLEEP_NORMAL|MODS_SLEEP_LOW_NOISE
 *                  MODS_SLEEP_HIGH_RESOLUTION|MODS_SLEEP_LOW_POWER
 *                  MODS_BOTH_NORMAL|MODS_BOTH_LOW_NOISE|MODS_BOTH_HIGH_RESOLUTION
 *                  MODS_BOTH_LOW_POWER
******************************************************************************/
void FXOS8700_I2C1_OverSampling (uint8 mask)
{
  uint8 n;

  FXOS8700_Standby(I2C1);
  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG, n & ~MODS_BOTH_LOW_POWER);
  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG2_REG, n | mask);
  FXOS8700_Active(I2C1);
}

/**************************************************************************//*!
 * @brief    The FIFO input buffer is blocked when transitioning from WAKE to
 *           SLEEP mode or from SLEEP to WAKE mode until the FIFO is flushed.
******************************************************************************/
void FXOS8700_I2C0_FIFOEnable (void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n | FIFO_GATE_MASK);
}

/**************************************************************************//*!
 * @brief    The FIFO input buffer is blocked when transitioning from WAKE to
 *           SLEEP mode or from SLEEP to WAKE mode until the FIFO is flushed.
******************************************************************************/
void FXOS8700_I2C1_FIFOEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n | FIFO_GATE_MASK);
}

/**************************************************************************//*!
* @brief    FIFO gate is bypassed.
******************************************************************************/
void FXOS8700_I2C0_FIFOBypassed(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n & ~FIFO_GATE_MASK);
}

/**************************************************************************//*!
* @brief    FIFO gate is bypassed.
******************************************************************************/
void FXOS8700_I2C1_FIFOBypassed(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n & ~FIFO_GATE_MASK);
}

/**************************************************************************//*!
 * @brief    Transient function interrupt can wake up system.
******************************************************************************/
void FXOS8700_I2C0_WakeTransEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n | WAKE_TRANS_MASK);
}

/**************************************************************************//*!
 * @brief    Transient function interrupt can wake up system.
******************************************************************************/
void FXOS8700_I2C1_WakeTransEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n | WAKE_TRANS_MASK);
}

/**************************************************************************//*!
 * @brief    Transient function is bypassed in SLEEP mode.
******************************************************************************/
void FXOS8700_I2C0_WakeTransDisable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n & ~WAKE_TRANS_MASK);
}

/**************************************************************************//*!
 * @brief    Transient function is bypassed in SLEEP mode.
******************************************************************************/
void FXOS8700_I2C1_WakeTransDisable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n & ~WAKE_TRANS_MASK);
}

/**************************************************************************//*!
 * @brief    Orientation function interrupt can wake up system.
******************************************************************************/
void FXOS8700_I2C0_WakeOrientationEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n | WAKE_LNDPRT_MASK);
}

/**************************************************************************//*!
 * @brief    Orientation function interrupt can wake up system.
******************************************************************************/
void FXOS8700_I2C1_WakeOrientationEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n | WAKE_LNDPRT_MASK);
}

/**************************************************************************//*!
 * @brief    Orientation function is bypassed in SLEEP mode.
******************************************************************************/
void FXOS8700_I2C0_WakeOrientationDisable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n & ~WAKE_LNDPRT_MASK);
}

/**************************************************************************//*!
 * @brief    Orientation function is bypassed in SLEEP mode.
******************************************************************************/
void FXOS8700_I2C1_WakeOrientationDisable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n & ~WAKE_LNDPRT_MASK);
}

/**************************************************************************//*!
 * @brief    Pulse function interrupt can wake up system.
******************************************************************************/
void FXOS8700_I2C0_WakePulseEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n | WAKE_PULSE_MASK);
}

/**************************************************************************//*!
 * @brief    Pulse function interrupt can wake up system.
******************************************************************************/
void FXOS8700_I2C1_WakePulseEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n | WAKE_PULSE_MASK);
}

/**************************************************************************//*!
 * @brief    Pulse function is bypassed in SLEEP mode.
******************************************************************************/
void FXOS8700_I2C0_WakePulseDisable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n & ~WAKE_PULSE_MASK);
}

/**************************************************************************//*!
 * @brief    Pulse function is bypassed in SLEEP mode.
******************************************************************************/
void FXOS8700_I2C1_WakePulseDisable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n & ~WAKE_PULSE_MASK);
}

/**************************************************************************//*!
 * @brief    Freefall/Motion function interrupt can wake up system.
******************************************************************************/
void FXOS8700_I2C0_WakeFreefallMotionEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n | WAKE_FF_MT_MASK);
}

/**************************************************************************//*!
 * @brief    Freefall/Motion function interrupt can wake up system.
******************************************************************************/
void FXOS8700_I2C1_WakeFreefallMotionEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n | WAKE_FF_MT_MASK);
}

/**************************************************************************//*!
 * @brief    Freefall/Motion function is bypassed in SLEEP mode.
******************************************************************************/
void FXOS8700_I2C0_WakeFreefallMotionDisable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n & ~WAKE_FF_MT_MASK);
}

/**************************************************************************//*!
 * @brief    Freefall/Motion function is bypassed in SLEEP mode.
******************************************************************************/
void FXOS8700_I2C1_WakeFreefallMotionDisable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n & ~WAKE_FF_MT_MASK);
}

/**************************************************************************//*!
 * @brief    Interrupt polarity ACTIVE high.
******************************************************************************/
void FXOS8700_I2C0_IntPolarityHigh(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n | INT_POLARITY_MASK);
}

/**************************************************************************//*!
 * @brief    Interrupt polarity ACTIVE high.
******************************************************************************/
void FXOS8700_I2C1_IntPolarityHigh(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n | INT_POLARITY_MASK);
}

/**************************************************************************//*!
 * @brief    Interrupt polarity ACTIVE low.
******************************************************************************/
void FXOS8700_I2C0_IntPolarityLow(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n & ~INT_POLARITY_MASK);
}

/**************************************************************************//*!
 * @brief    Interrupt polarity ACTIVE low.
******************************************************************************/
void FXOS8700_I2C1_IntPolarityLow(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n & ~INT_POLARITY_MASK);
}

/**************************************************************************//*!
 * @brief    Open Drain selection on interrupt pad.
******************************************************************************/
void FXOS8700_I2C0_OpenDrainEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n | PP_OD_MASK);
}

/**************************************************************************//*!
 * @brief    Open Drain selection on interrupt pad.
******************************************************************************/
void FXOS8700_I2C1_OpenDrainEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n | PP_OD_MASK);
}

/**************************************************************************//*!
 * @brief    Push-Pull selection on interrupt pad.
******************************************************************************/
void FXOS8700_I2C0_PushPullEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG3_REG, n & ~PP_OD_MASK);
}

/**************************************************************************//*!
 * @brief    Push-Pull selection on interrupt pad.
******************************************************************************/
void FXOS8700_I2C1_PushPullEnable(void)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG3_REG, n & ~PP_OD_MASK);
}

/**************************************************************************//*!
 * @brief    Interrupt enable.
 * @param    mask - INT_EN_ASLP_MASK|INT_EN_FIFO_MASK|INT_EN_TRANS_MASK|
 *                  INT_EN_LNDPRT_MASK|INT_EN_PULSE_MASK|INT_EN_FF_MT_MASK|
 *                  INT_EN_DRDY_MASK
******************************************************************************/
void FXOS8700_I2C0_InterruptEnable(uint8 mask)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG4_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG4_REG, n | mask);
}

/**************************************************************************//*!
 * @brief    Interrupt enable.
 * @param    mask - INT_EN_ASLP_MASK|INT_EN_FIFO_MASK|INT_EN_TRANS_MASK|
 *                  INT_EN_LNDPRT_MASK|INT_EN_PULSE_MASK|INT_EN_FF_MT_MASK|
 *                  INT_EN_DRDY_MASK
******************************************************************************/
void FXOS8700_I2C1_InterruptEnable(uint8 mask)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG4_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG4_REG, n | mask);
}

/**************************************************************************//*!
 * @brief    Interrupt disable.
 * @param    mask - INT_EN_ASLP_MASK|INT_EN_FIFO_MASK|INT_EN_TRANS_MASK|
 *                  INT_EN_LNDPRT_MASK|INT_EN_PULSE_MASK|INT_EN_FF_MT_MASK|
 *                  INT_EN_DRDY_MASK
******************************************************************************/
void FXOS8700_I2C0_InterruptDisable(uint8 mask)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG4_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG4_REG, n & ~mask);
}

/**************************************************************************//*!
 * @brief    Interrupt disable.
 * @param    mask - INT_EN_ASLP_MASK|INT_EN_FIFO_MASK|INT_EN_TRANS_MASK|
 *                  INT_EN_LNDPRT_MASK|INT_EN_PULSE_MASK|INT_EN_FF_MT_MASK|
 *                  INT_EN_DRDY_MASK
******************************************************************************/
void FXOS8700_I2C1_InterruptDisable(uint8 mask)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG4_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG4_REG, n & ~mask);
}

/**************************************************************************//*!
 * @brief    Interrupt is routed on INT1 pin.
 * @param    mask - INT_CFG_ASLP_MASK|INT_CFG_FIFO_MASK|INT_CFG_TRANS_MASK|
 *                  INT_CFG_LNDPRT_MASK|INT_CFG_PULSE_MASK|INT_CFG_FF_MT_MASK|
 *                  INT_CFG_DRDY_MASK
******************************************************************************/
void FXOS8700_I2C0_InterruptOnINT1(uint8 mask)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG5_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG5_REG, n | mask);
}

/**************************************************************************//*!
 * @brief    Interrupt is routed on INT1 pin.
 * @param    mask - INT_CFG_ASLP_MASK|INT_CFG_FIFO_MASK|INT_CFG_TRANS_MASK|
 *                  INT_CFG_LNDPRT_MASK|INT_CFG_PULSE_MASK|INT_CFG_FF_MT_MASK|
 *                  INT_CFG_DRDY_MASK
******************************************************************************/
void FXOS8700_I2C1_InterruptOnINT1(uint8 mask)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG5_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG5_REG, n | mask);
}

/**************************************************************************//*!
 * @brief    Interrupt is routed on INT2 pin.
 * @param    mask - INT_CFG_ASLP_MASK|INT_CFG_FIFO_MASK|INT_CFG_TRANS_MASK|
 *                  INT_CFG_LNDPRT_MASK|INT_CFG_PULSE_MASK|INT_CFG_FF_MT_MASK|
 *                  INT_CFG_DRDY_MASK
******************************************************************************/
void FXOS8700_I2C0_InterruptOnINT2(uint8 mask)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_CTRL_REG5_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_CTRL_REG5_REG, n & ~mask);
}

/**************************************************************************//*!
 * @brief    Interrupt is routed on INT2 pin.
 * @param    mask - INT_CFG_ASLP_MASK|INT_CFG_FIFO_MASK|INT_CFG_TRANS_MASK|
 *                  INT_CFG_LNDPRT_MASK|INT_CFG_PULSE_MASK|INT_CFG_FF_MT_MASK|
 *                  INT_CFG_DRDY_MASK
******************************************************************************/
void FXOS8700_I2C1_InterruptOnINT2(uint8 mask)
{
  uint8 n;

  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_CTRL_REG5_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_CTRL_REG5_REG, n & ~mask);
}

/**************************************************************************//*!
 * @brief    Write the high pass filter cut-off value into HP_FILTER_CUTOFF register
 * @param    mask - HP_FILTER_CUTOFF_0|HP_FILTER_CUTOFF_1|HP_FILTER_CUTOFF_2
 *                  HP_FILTER_CUTOFF_3
******************************************************************************/
void FXOS8700_I2C0_HPF_CutOff (uint8 mask)
{
  uint8 n;

  FXOS8700_Standby(I2C0);
  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_HP_FILTER_CUTOFF_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_HP_FILTER_CUTOFF_REG, n & ~HP_FILTER_CUTOFF_3);
  n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_HP_FILTER_CUTOFF_REG);
  FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_HP_FILTER_CUTOFF_REG, n | mask);
  FXOS8700_Active(I2C0);
}

/**************************************************************************//*!
 * @brief    Write the high pass filter cut-off value into HP_FILTER_CUTOFF register
 * @param    mask - HP_FILTER_CUTOFF_0|HP_FILTER_CUTOFF_1|HP_FILTER_CUTOFF_2
 *                  HP_FILTER_CUTOFF_3
******************************************************************************/
void FXOS8700_I2C1_HPF_CutOff (uint8 mask)
{
  uint8 n;

  FXOS8700_Standby(I2C1);
  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_HP_FILTER_CUTOFF_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_HP_FILTER_CUTOFF_REG, n & ~HP_FILTER_CUTOFF_3);
  n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_HP_FILTER_CUTOFF_REG);
  FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_HP_FILTER_CUTOFF_REG, n | mask);
  FXOS8700_Active(I2C1);
}

/**************************************************************************//*!
 * @brief    Set filter type by writting into XYZ_DATA_CFG_REG register
 * @param    mask - LOW_PASS_FILTERED_DATA_OUT|HIGH_PASS_FILTERED_DATA_OUT
******************************************************************************/
void FXOS8700_I2C0_OutputDataFilterType (uint8 mask)
{
  uint8 n;

  FXOS8700_Standby(I2C0);
  if (mask)
  {
    n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_XYZ_DATA_CFG_REG);
    FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_XYZ_DATA_CFG_REG, n | HIGH_PASS_FILTERED_DATA_OUT);
  }
  else
  {
    n = FXOS8700_READ_REGISTER(I2C0, FXOS8700_XYZ_DATA_CFG_REG);
    FXOS8700_WRITE_REGISTER(I2C0, FXOS8700_XYZ_DATA_CFG_REG, n & ~HIGH_PASS_FILTERED_DATA_OUT);
  }
  FXOS8700_Active(I2C0);
}

/**************************************************************************//*!
 * @brief    Set filter type by writting into XYZ_DATA_CFG_REG register
 * @param    mask - LOW_PASS_FILTERED_DATA_OUT|HIGH_PASS_FILTERED_DATA_OUT
******************************************************************************/
void FXOS8700_I2C1_OutputDataFilterType (uint8 mask)
{
  uint8 n;

  FXOS8700_Standby(I2C1);
  if (mask)
  {
    n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_XYZ_DATA_CFG_REG);
    FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_XYZ_DATA_CFG_REG, n | HIGH_PASS_FILTERED_DATA_OUT);
  }
  else
  {
    n = FXOS8700_READ_REGISTER(I2C1, FXOS8700_XYZ_DATA_CFG_REG);
    FXOS8700_WRITE_REGISTER(I2C1, FXOS8700_XYZ_DATA_CFG_REG, n & ~HIGH_PASS_FILTERED_DATA_OUT);
  }
  FXOS8700_Active(I2C1);
}

// test

// end test

/**************************************************************************//*!
* @brief    Function reads current data from sensor's register via I2C0
* @param    *fxos8700 - pointer to main FXOS8700 structure
******************************************************************************/
void FXOS8700_I2C0_ReadRawData(TWR_FXOS8700* ptr_fxos8700)
{
  uint8 ix;
  static uint8 measure = 0;
  TWR_FXOS8700_DATA xyz_regs[XYZ_SIZE];
  static uint8 latest_write;
  static uint8 latest_address;
  #define BASE              512
  #define PEAK_NOISE_MINUS  -1000
  #define PEAK_NOISE_PLUS   1000
  TWR_FXOS8700 workaround;

  if(FXOS8700_enabled == TRUE)
  {
    if(FXOS8700_READ_REGISTER(I2C0, FXOS8700_STATUS_REG) & BIT_ZYXDR_MASK)
    {
      //Add MMA8451/MMA8452/MMA8453 and display which device is connected in FreeMASTER
      FXOS8700_READ_REGISTERS (I2C0, FXOS8700_OUT_X_MSB_REG,\
                                        (uint8*)&(xyz_regs[0].Bytes.hi),
                                         6);
    }
    //  reading from all internal register
    if(--measure == 0)
    {
      for(ix=0; ix<FXOS8700_REGS; ix++)
        ptr_fxos8700->registers[ix] = FXOS8700_READ_REGISTER(I2C0, ix);
      measure = FXOS8700_PERIODE;
    }
    switch(whoiam)
    {
#if (YXZ_TYPE == UNSIGNED)
			case  FXOS8700_ID:
        workaround.x = (uint16)(BASE + ((int16)(xyz_regs[0].all) / RES_10BIT));
        workaround.y = (uint16)(BASE + ((int16)(xyz_regs[1].all) / RES_10BIT));
        workaround.z = (uint16)(BASE + ((int16)(xyz_regs[2].all) / RES_10BIT));
      break;
#elif (YXZ_TYPE == SIGNED)
			case  FXOS8700_ID:
        workaround.x = (int16)(xyz_regs[0].all);
        workaround.y = (int16)(xyz_regs[1].all);
        workaround.z = (int16)(xyz_regs[2].all);
      break;
#endif
    }
    if( ((int16)(ptr_fxos8700->x - workaround.x)) > PEAK_NOISE_PLUS ||\
        ((int16)(ptr_fxos8700->x - workaround.x)) < PEAK_NOISE_MINUS )
      ptr_fxos8700->x = workaround.x;
    if( ((int16)(ptr_fxos8700->y - workaround.y)) > PEAK_NOISE_PLUS ||\
         (int16)(ptr_fxos8700->y - workaround.y) < PEAK_NOISE_MINUS )
      ptr_fxos8700->y = workaround.y;
    if( (int16)(ptr_fxos8700->z - workaround.z) > PEAK_NOISE_PLUS ||\
        (int16)(ptr_fxos8700->z - workaround.z) < PEAK_NOISE_MINUS )
      ptr_fxos8700->z = workaround.z;
    if(latest_write != ptr_fxos8700->reg_write ||\
       latest_address != ptr_fxos8700->reg_addr)
    {
      FXOS8700_WRITE_REGISTER(I2C0, ptr_fxos8700->reg_addr,ptr_fxos8700->reg_write);
      latest_write = ptr_fxos8700->reg_write;
      latest_address = ptr_fxos8700->reg_addr;
    }
    ptr_fxos8700->id = whoiam;
  }
  else
  {
      ptr_fxos8700->x = 0;
      ptr_fxos8700->y = 0;
      ptr_fxos8700->z = 0;
      ptr_fxos8700->id = 0;
  }
}

/**************************************************************************//*!
* @brief    Function reads current data from sensor's register via I2C1
* @param    *fxos8700 - pointer to main FXOS8700 structure
******************************************************************************/
void FXOS8700_I2C1_ReadRawData(TWR_FXOS8700* ptr_fxos8700)
{
  uint8 ix;
  static uint8 measure = 0;
  static TWR_FXOS8700_DATA xyz_regs[XYZ_SIZE];
  static uint8 latest_write;
  static uint8 latest_address;
  #define BASE              512
  #define PEAK_NOISE_MINUS  -1000
  #define PEAK_NOISE_PLUS   1000
  TWR_FXOS8700 workaround;

  if(FXOS8700_enabled == TRUE)
  {
    if(FXOS8700_READ_REGISTER(I2C1, FXOS8700_STATUS_REG) & BIT_ZYXDR_MASK)
    {
      //Add MMA8451/MMA8452/MMA8453 and display which device is connected in FreeMASTER
      FXOS8700_READ_REGISTERS (I2C1, FXOS8700_OUT_X_MSB_REG,\
                                        (uint8*)&(xyz_regs[0].Bytes.hi),
                                         6);
    }
    //  reading from all internal register
    if(--measure == 0)
    {
      for(ix=0; ix<FXOS8700_REGS; ix++)
        ptr_fxos8700->registers[ix] = FXOS8700_READ_REGISTER(I2C1, ix);
      measure = FXOS8700_PERIODE;
    }
    switch(whoiam)
    {
#if (YXZ_TYPE == UNSIGNED)
    case  FXOS8700_ID:
        workaround.x = (uint16)(BASE + ((int16)(xyz_regs[0].all) / RES_10BIT));
        workaround.y = (uint16)(BASE + ((int16)(xyz_regs[1].all) / RES_10BIT));
        workaround.z = (uint16)(BASE + ((int16)(xyz_regs[2].all) / RES_10BIT));
      break;
#elif (YXZ_TYPE == SIGNED)
    case  FXOS8700_ID:
        workaround.x = (int16)(xyz_regs[0].all);
        workaround.y = (int16)(xyz_regs[1].all);
        workaround.z = (int16)(xyz_regs[2].all);
      break;
#endif
    }
    if( ((int16)(ptr_fxos8700->x - workaround.x)) > PEAK_NOISE_PLUS ||\
        ((int16)(ptr_fxos8700->x - workaround.x)) < PEAK_NOISE_MINUS )
      ptr_fxos8700->x = workaround.x;
    if( ((int16)(ptr_fxos8700->y - workaround.y)) > PEAK_NOISE_PLUS ||\
         (int16)(ptr_fxos8700->y - workaround.y) < PEAK_NOISE_MINUS )
      ptr_fxos8700->y = workaround.y;
    if( (int16)(ptr_fxos8700->z - workaround.z) > PEAK_NOISE_PLUS ||\
        (int16)(ptr_fxos8700->z - workaround.z) < PEAK_NOISE_MINUS )
      ptr_fxos8700->z = workaround.z;
    if(latest_write != ptr_fxos8700->reg_write ||\
       latest_address != ptr_fxos8700->reg_addr)
    {
      FXOS8700_WRITE_REGISTER(I2C1, ptr_fxos8700->reg_addr,ptr_fxos8700->reg_write);
      latest_write = ptr_fxos8700->reg_write;
      latest_address = ptr_fxos8700->reg_addr;
    }
    ptr_fxos8700->id = whoiam;
  }
  else
  {
      ptr_fxos8700->x = 0;
      ptr_fxos8700->y = 0;
      ptr_fxos8700->z = 0;
      ptr_fxos8700->id = 0;
  }
}

















