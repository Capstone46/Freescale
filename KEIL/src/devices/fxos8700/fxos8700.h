/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      fxos8700.h
 * @author    B34185
 * @version   1.0.3.0
 * @date      Apr-24-2013
 * @brief     FXOS8700 driver header file.
 ******************************************************************************/
#ifndef __FXOS8700_H
#define __FXOS8700_H

#include "i2c.h"

#define FXOS8700_I2C_ADDRESS     0x1F
#define FXOS8700_OUT_ALERT       0x40
#define FXOS8700_REGS            50
#define FXOS8700_PERIODE         10

/*******************************************************************************
* Redefined I2C function for write and read
*******************************************************************************/
//#define FXOS8700_I2C0_WRITE_REGISTERS(x,y,z)  (void)I2C0_WriteMultiBytes(FXOS8700_I2C_ADDRESS,(x),(y),(z))
//#define FXOS8700_I2C1_WRITE_REGISTERS(x,y,z)  (void)I2C1_WriteMultiBytes(FXOS8700_I2C_ADDRESS,(x),(y),(z))
//#define FXOS8700_I2C0_READ_REGISTERS(x,y,z)   (void)I2C0_ReadMultiBytes(FXOS8700_I2C_ADDRESS,(x),(y),(z))
//#define FXOS8700_I2C1_READ_REGISTERS(x,y,z)   (void)I2C1_ReadMultiBytes(FXOS8700_I2C_ADDRESS,(x),(y),(z))
//
//#define FXOS8700_I2C0_WRITE_REGISTER(x,y)     (void)I2C0_WriteByte(FXOS8700_I2C_ADDRESS,x,y)
//#define FXOS8700_I2C1_WRITE_REGISTER(x,y)     (void)I2C1_WriteByte(FXOS8700_I2C_ADDRESS,x,y)
//#define FXOS8700_I2C0_READ_REGISTER(x)        (uint8)I2C0_ReadByte(FXOS8700_I2C_ADDRESS,x)
//#define FXOS8700_I2C1_READ_REGISTER(x)        (uint8)I2C1_ReadByte(FXOS8700_I2C_ADDRESS,x)


#ifndef FXOS8700_WRITE_REGISTERS
  #define FXOS8700_WRITE_REGISTERS(module,x,y,z)  (void)module##_WriteMultiBytes(FXOS8700_I2C_ADDRESS,(x),(y),(z))
#endif

#ifndef FXOS8700_READ_REGISTERS
  #define FXOS8700_READ_REGISTERS(module,x,y,z)   (void)module##_ReadMultiBytes(FXOS8700_I2C_ADDRESS,(x),(y),(z))
#endif

#ifndef FXOS8700_WRITE_REGISTER
  #define FXOS8700_WRITE_REGISTER(module,x,y)     (void)module##_WriteByte(FXOS8700_I2C_ADDRESS,x,y)
#endif

#ifndef FXOS8700_READ_REGISTER
  #define FXOS8700_READ_REGISTER(module,x)        (uint8)module##_ReadByte(FXOS8700_I2C_ADDRESS,x)
#endif

//  registers address
// acceleromenter base registers
#define FXOS8700_STATUS_REG              0x00
#define FXOS8700_OUT_X_MSB_REG           0x01
#define FXOS8700_OUT_X_LSB_REG           0x02
#define FXOS8700_OUT_Y_MSB_REG           0x03
#define FXOS8700_OUT_Y_LSB_REG           0x04
#define FXOS8700_OUT_Z_MSB_REG           0x05
#define FXOS8700_OUT_Z_LSB_REG           0x06
#define FXOS8700_F_SETUP_REG             0x09
#define FXOS8700_TRIG_CFG_REG            0x0A
#define FXOS8700_SYSMOD_REG              0x0B
#define FXOS8700_INT_SOURCE_REG          0x0C
#define FXOS8700_WHO_AM_I_REG            0x0D
#define FXOS8700_XYZ_DATA_CFG_REG        0x0E
#define FXOS8700_HP_FILTER_CUTOFF_REG    0x0F
#define FXOS8700_PL_STATUS_REG           0x10
#define FXOS8700_PL_CFG_REG              0x11
#define FXOS8700_PL_COUNT_REG            0x12
#define FXOS8700_PL_BF_ZCOMP_REG         0x13
#define FXOS8700_P_L_THS_REG_REG         0x14
#define FXOS8700_FF_MT_CFG_REG           0x15
#define FXOS8700_FF_MT_SRC_REG           0x16
#define FXOS8700_FF_MT_THS_REG           0x17
#define FXOS8700_FF_MT_COUNT_REG         0x18
#define FXOS8700__CFG_REG                0x1D
#define FXOS8700_TRANSIENT_SCR_REG       0x1E
#define FXOS8700_TRANSIENT_THS_REG       0x1F
#define FXOS8700_TRANSIENT_COUNT_REG     0x20
#define FXOS8700_PULSE_CFG_REG           0x21
#define FXOS8700_PULSE_SRC_REG           0x22
#define FXOS8700_PULSE_THSX_REG          0x23
#define FXOS8700_PULSE_THSY_REG          0x24
#define FXOS8700_PULSE_THSZ_REG          0x25
#define FXOS8700_PULSE_TMLT_REG          0x26
#define FXOS8700_PULSE_LTCY_REG          0x27
#define FXOS8700_PULSE_WIND_REG          0x28
#define FXOS8700_ASLP_COUNT_REG          0x29
#define FXOS8700_CTRL_REG1_REG           0x2A
#define FXOS8700_CTRL_REG2_REG           0x2B
#define FXOS8700_CTRL_REG3_REG           0x2C
#define FXOS8700_CTRL_REG4_REG           0x2D
#define FXOS8700_CTRL_REG5_REG           0x2E
#define FXOS8700_OFF_X_REG               0x2F
#define FXOS8700_OFF_Y_REG               0x30
#define FXOS8700_OFF_Z_REG               0x31
// Magnetometer base register
#define FXOS8700_M_CTRL_REG2_REG         0x5C

// Register masks definition


// Dynamic ranges masks
#define FULL_SCALE_2G                   0x00
#define FULL_SCALE_4G                   0x01
#define FULL_SCALE_8G                   0x02
#define FULL_SCALE_MASK                 0x03
//Auto wake masks
#define WAKE_50HZ                       0x00<<6
#define WAKE_12_5HZ                     0x01<<6
#define WAKE_6_25HZ                     0x02<<6
#define WAKE_1_56HZ                     0x03<<6
#define WAKE_MASK                       0x03<<6
// Data rate masks
#define DR_800HZ                        0x00<<3
#define DR_400HZ                        0x01<<3
#define DR_200HZ                        0x02<<3
#define DR_100HZ                        0x03<<3
#define DR_50HZ                         0x04<<3
#define DR_12_5_HZ                      0x05<<3
#define DR_6_25_HZ                      0x06<<3
#define DR_1_563_HZ                     0x07<<3
#define DR_MASK                         0x07<<3
// Low noise mask
#define LOW_NOISE_MASK                  0x01<<2
// Fast read mask
#define FAST_READ_MASK                  0x01<<1
// Activity mask
#define ACTIVE_MASK                     (uint8)0x01

// CTRL2_REG mask definition
// Self test mask
#define SELF_TEST_MASK                  0x01<<7
// Software reset mask
#define RESET_MASK                      (uint8)0x01<<6
// Auto Sleep mask
#define AUTO_SLEEP_MASK                 0x01<<2
// Oversampling modes masks
#define MODS_NORMAL                     0x00
#define MODS_LOW_NOISE                  0x01
#define MODS_HIGH_RESOLUTION            0x02
#define MODS_LOW_POWER                  0x03
#define MODS_SLEEP_NORMAL               MODS_NORMAL
#define MODS_SLEEP_LOW_NOISE            0x01<<3
#define MODS_SLEEP_HIGH_RESOLUTION      0x02<<3
#define MODS_SLEEP_LOW_POWER            0x03<<3
#define MODS_BOTH_NORMAL                MODS_NORMAL
#define MODS_BOTH_LOW_NOISE             0x01|(0x01<<3)
#define MODS_BOTH_HIGH_RESOLUTION       0x02|(0x02<<3)
#define MODS_BOTH_LOW_POWER             0x03|(0x03<<3)
#define MODS_MASK                       0x03|(0x03<<3)

// CTRL3_REG mask definition
// fifo gate mask
#define FIFO_GATE_MASK                  0x01<<7
// Wake trans mask
#define WAKE_TRANS_MASK                 0x01<<6
// wake orientation mask
#define WAKE_LNDPRT_MASK                0x01<<5
// Wake pulse mask
#define WAKE_PULSE_MASK                 0x01<<4
// Wake trans mask
#define WAKE_FF_MT_MASK                 0x01<<3
// interrupt polarity mask
#define INT_POLARITY_MASK               0x01<<1
// push-pull/open drain mask
#define PP_OD_MASK                      0x01<<0

// CTRL4_REG mask definition
// Auto-SLEEP/WAKE interrupt mask
#define INT_EN_ASLP_MASK                0x01<<7
// FIFO interrupt mask
#define INT_EN_FIFO_MASK                0x01<<6
// Transient interrupt mask
#define INT_EN_TRANS_MASK               0x01<<5
// Orientation (Landscape/Portrait) interrupt mask
#define INT_EN_LNDPRT_MASK              0x01<<4
// Pulse Detection interrupt mask
#define INT_EN_PULSE_MASK               0x01<<3
// Freefall/Motion interrupt mask
#define INT_EN_FF_MT_MASK               0x01<<2
// Data Ready interrupt mask
#define INT_EN_DRDY_MASK                0x01<<0

// CTRL5_REG mask definition
// Auto-SLEEP/WAKE config mask
#define INT_CFG_ASLP_MASK               0x01<<7
// FIFO config mask
#define INT_CFG_FIFO_MASK               0x01<<6
// Transient config mask
#define INT_CFG_TRANS_MASK              0x01<<5
// Orientation (Landscape/Portrait) config mask
#define INT_CFG_LNDPRT_MASK             0x01<<4
// Pulse Detection config mask
#define INT_CFG_PULSE_MASK              0x01<<3
// Freefall/Motion config mask
#define INT_CFG_FF_MT_MASK              0x01<<2
// Data Ready config mask
#define INT_CFG_DRDY_MASK               0x01<<0

// High-pass filter cut-off setting masks
#define HP_FILTER_CUTOFF_0              0x00
#define HP_FILTER_CUTOFF_1              0x01
#define HP_FILTER_CUTOFF_2              0x02
#define HP_FILTER_CUTOFF_3              0x03
#define HP_FILTER_CUTOFF_MASK           0x03
// Filter type setting
#define LOW_PASS_FILTERED_DATA_OUT      0x00
#define HIGH_PASS_FILTERED_DATA_OUT     0x10

#define BIT_ZYXDR_MASK                  0x88
#define RES_14BIT                       2
#define RES_12BIT                       4
#define RES_10BIT                       6


#define XYZ_SIZE                3

#define UNSIGNED                0
#define SIGNED                  1
#define YXZ_TYPE                SIGNED

//  typedefs
typedef union
{
  uint16 all;
  struct
  {
    uint8 lo;
    uint8 hi;
  }Bytes;
}TWR_FXOS8700_DATA;

typedef struct
{
  uint8 reg_write;
  uint8 reg_addr;
#if (YXZ_TYPE == UNSIGNED)
  uint16 x;
  uint16 y;
  uint16 z;
#elif (YXZ_TYPE == SIGNED)
  int16 x;
  int16 y;
  int16 z;
#endif
  uint8 id;
  uint8 registers[50];
}TWR_FXOS8700;

typedef enum
{
  FXOS8700_ID = 0xC7
}FXOS8700_IDS;

#ifndef __MMA845X_H
typedef union
{
  int16 m_signed_int;
  uint16 m_unsigned_int;
}INT_UINT_CONVERSION;
#endif

/***************************************************************************//*!
 * @brief   FXOS8700 initialization for I2Cx module.
 * @param   void
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_Init(module)            FXOS8700_##module##_Init()

/***************************************************************************//*!
 * @brief   FXOS8700 de-initialization for I2Cx module.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_DeInit(module)          FXOS8700_##module##_DeInit()

/***************************************************************************//*!
 * @brief   Activate FXOS8700 reset. Put all registers into the default state.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_Reset(module)          FXOS8700_##module##_Reset()

/***************************************************************************//*!
 * @brief   Set FXOS8700 dynamic range mode I2Cx module.
 * @param   module - I2C0|I2C1
 * @param   mask - FULL_SCALE_2G|FULL_SCALE_4G|FULL_SCALE_8G
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_DynamicRange(module, mask) FXOS8700_##module##_DynamicRange(mask)

/***************************************************************************//*!
 * @brief   Set FXOS8700 auto wake sampling frequency I2Cx module.
 * @param   module - I2C0|I2C1
 * @param   mask - WAKE_50HZ|WAKE_12_5HZ|WAKE_6_25HZ|WAKE_1_56HZ
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_AutoWake(module, mask) FXOS8700_##module##_AutoWake(mask)

/***************************************************************************//*!
 * @brief   Set FXOS8700 dynamic range mode I2Cx module.
 * @param   module - I2C0|I2C1
 * @param   mask - DR_800HZ|DR_400HZ|DR_200HZ|DR_100HZ|DR_50HZ|DR_12_5_HZ|
 *                 DR_6_25_HZ|DR_1_563_HZ
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_DataRate(module, mask) FXOS8700_##module##_DataRate(mask)

/***************************************************************************//*!
 * @brief   Put FXOS8700 into low noisemode I2Cx module.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_LowNoiseEnable(module)  FXOS8700_##module##_LowNoiseEnable()

/***************************************************************************//*!
 * @brief   Disable FXOS8700 low noise mode I2Cx module.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_LowNoiseDisable(module)  FXOS8700_##module##_LowNoiseDisable()

/***************************************************************************//*!
 * @brief   Put FXOS8700 in to the fast read mode I2Cx module.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_FastReadEnable(module)  FXOS8700_##module##_FastReadEnable()

/***************************************************************************//*!
 * @brief   Disable FXOS8700 fast read mode I2Cx module.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_FastReadDisable(module)  FXOS8700_##module##_FastReadDisable()

/***************************************************************************//*!
 * @brief   Put FXOS8700 into active mode I2Cx module.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_Active(module)          FXOS8700_##module##_Active()

/***************************************************************************//*!
 * @brief   Put FXOS8700 into standby mode I2Cx module.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_Standby(module)          FXOS8700_##module##_Standby()

/***************************************************************************//*!
 * @brief   Put FXOS8700 into self test I2Cx module.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_SelfTestEnable(module)  FXOS8700_##module##_SelfTestEnable()

/***************************************************************************//*!
 * @brief   Disable self test on FXOS8700 I2Cx module.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_SelfTestDisable(module) FXOS8700_##module##_SelfTestDisable()

/***************************************************************************//*!
 * @brief   Put FXOS8700 into auto sleep mode I2Cx module.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_AutoSleepEnable(module)  FXOS8700_##module##_AutoSleepEnable()

/***************************************************************************//*!
 * @brief   Disable auto sleep mode on FXOS8700 I2Cx module.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_AutoSleepDisable(module) FXOS8700_##module##_AutoSleepDisable()

/***************************************************************************//*!
 * @brief   Set FXOS8700 over sampling mode I2Cx module.
 * @param   module - I2C0|I2C1
 * @param   mask - MODS_NORMAL|MODS_LOW_NOISE|MODS_HIGH_RESOLUTION
 *                 MODS_LOW_POWER|MODS_SLEEP_NORMAL|MODS_SLEEP_LOW_NOISE
 *                 MODS_SLEEP_HIGH_RESOLUTION|MODS_SLEEP_LOW_POWER
 *                 MODS_BOTH_NORMAL|MODS_BOTH_LOW_NOISE|MODS_BOTH_HIGH_RESOLUTION
 *                 MODS_BOTH_LOW_POWER
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_OverSampling(module, mask) FXOS8700_##module##_OverSampling(mask)

/***************************************************************************//*!
 * @brief   The FIFO input buffer is blocked when transitioning from WAKE to
 *          SLEEP mode or from SLEEP to WAKE mode until the FIFO is flushed.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_FIFOEnable(module)  FXOS8700_##module##_FIFOEnable()

/***************************************************************************//*!
* @brief    FIFO gate is bypassed.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_FIFOBypassed(module)  FXOS8700_##module##_FIFOBypassed()

/***************************************************************************//*!
 * @brief   Transient function interrupt can wake up system.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_WakeTransEnable(module)  FXOS8700_##module##_WakeTransEnable()

/***************************************************************************//*!
 * @brief   Transient function is bypassed in SLEEP mode.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_WakeTransDisable(module)  FXOS8700_##module##_WakeTransDisable()

/***************************************************************************//*!
 * @brief   Orientation function interrupt can wake up system.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_WakeOrientationEnable(module)  FXOS8700_##module##_WakeOrientationEnable()

/***************************************************************************//*!
 * @brief   Orientation function is bypassed in SLEEP mode.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_WakeOrientationDisable(module)  FXOS8700_##module##_WakeOrientationDisable()

/***************************************************************************//*!
 * @brief    Pulse function interrupt can wake up system.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_WakePulseEnable(module)  FXOS8700_##module##_WakePulseEnable()

/***************************************************************************//*!
 * @brief   Pulse function is bypassed in SLEEP mode.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_WakePulseDisable(module)  FXOS8700_##module##_WakePulseDisable()

/***************************************************************************//*!
 * @brief   Freefall/Motion function interrupt can wake up system.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_WakeFreefallMotionEnable(module)  FXOS8700_##module##_WakeFreefallMotionEnable()

/***************************************************************************//*!
 * @brief   Freefall/Motion function is bypassed in SLEEP mode.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_WakeFreefallMotionDisable(module)  FXOS8700_##module##_WakeFreefallMotionDisable()

/***************************************************************************//*!
 * @brief   Interrupt polarity ACTIVE high.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_IntPolarityHigh(module)  FXOS8700_##module##_IntPolarityHigh()

/***************************************************************************//*!
 * @brief   Interrupt polarity ACTIVE low.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_IntPolarityLow(module)  FXOS8700_##module##_IntPolarityLow()

/***************************************************************************//*!
 * @brief   Open Drain selection on interrupt pad.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_OpenDrainEnable(module)  FXOS8700_##module##_OpenDrainEnable()

/***************************************************************************//*!
 * @brief   Push-Pull selection on interrupt pad.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_PushPullEnable(module)  FXOS8700_##module##_PushPullEnable()

/***************************************************************************//*!
 * @brief   Interrupt enable.
 * @param   module - I2C0|I2C1
 * @param   mask - INT_EN_ASLP_MASK|INT_EN_FIFO_MASK|INT_EN_TRANS_MASK|
 *                 INT_EN_LNDPRT_MASK|INT_EN_PULSE_MASK|INT_EN_FF_MT_MASK|
 *                 INT_EN_DRDY_MASK
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_InterruptEnable(module, mask)  FXOS8700_##module##_InterruptEnable(mask)

/***************************************************************************//*!
 * @brief   Interrupt disable.
 * @param   module - I2C0|I2C1
 * @param   mask - INT_EN_ASLP_MASK|INT_EN_FIFO_MASK|INT_EN_TRANS_MASK|
 *                 INT_EN_LNDPRT_MASK|INT_EN_PULSE_MASK|INT_EN_FF_MT_MASK|
 *                 INT_EN_DRDY_MASK
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_InterruptDisable(module, mask)  FXOS8700_##module##_InterruptDisable(mask)

/***************************************************************************//*!
 * @brief   Interrupt is routed on INT1 pin.
 * @param   module - I2C0|I2C1
 * @param   mask - INT_CFG_ASLP_MASK|INT_CFG_FIFO_MASK|INT_CFG_TRANS_MASK|
 *                 INT_CFG_LNDPRT_MASK|INT_CFG_PULSE_MASK|INT_CFG_FF_MT_MASK|
 *                 INT_CFG_DRDY_MASK
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_InterruptOnINT1(module, mask)  FXOS8700_##module##_InterruptOnINT1(mask)

/***************************************************************************//*!
 * @brief   Interrupt is routed on INT2 pin.
 * @param   module - I2C0|I2C1
 * @param   mask - INT_CFG_ASLP_MASK|INT_CFG_FIFO_MASK|INT_CFG_TRANS_MASK|
 *                 INT_CFG_LNDPRT_MASK|INT_CFG_PULSE_MASK|INT_CFG_FF_MT_MASK|
 *                 INT_CFG_DRDY_MASK
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_InterruptOnINT2(module, mask)  FXOS8700_##module##_InterruptOnINT2(mask)

/***************************************************************************//*!
 * @brief   Set FXOS8700 High-pass filter cut-off frequency ratio.
 * @param   module - I2C0|I2C1
 * @param   mask - HP_FILTER_CUTOFF_0|HP_FILTER_CUTOFF_1|HP_FILTER_CUTOFF_2
 *                 HP_FILTER_CUTOFF_3
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_HPF_CutOff(module, mask) FXOS8700_##module##_HPF_CutOff(mask)

/***************************************************************************//*!
 * @brief   Set filter type by writting into XYZ_DATA_CFG_REG register.
 * @param   module - I2C0|I2C1
 * @param   mask - LOW_PASS_FILTERED_DATA_OUT|HIGH_PASS_FILTERED_DATA_OUT
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_OutputDataFilterType(module, mask)                             \
        FXOS8700_##module##_OutputDataFilterType(mask)

/***************************************************************************//*!
 * @brief   FXOS8700 read data for I2Cx module.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define FXOS8700_ReadRawData(module,ptr_module)  FXOS8700_##module##_ReadRawData(ptr_module)

/****************************************************************************************
* FXOS8700 API Functions
*****************************************************************************************/
extern void FXOS8700_I2C0_Init (void);
extern void FXOS8700_I2C1_Init (void);
extern void FXOS8700_I2C0_DeInit (void);
extern void FXOS8700_I2C1_DeInit (void);
extern void FXOS8700_I2C0_DynamicRange (uint8 mask);
extern void FXOS8700_I2C1_DynamicRange (uint8 mask);
extern void FXOS8700_I2C0_AutoWake (uint8 mask);
extern void FXOS8700_I2C1_AutoWake (uint8 mask);
extern void FXOS8700_I2C0_DataRate (uint8 mask);
extern void FXOS8700_I2C1_DataRate (uint8 mask);
extern void FXOS8700_I2C0_LowNoiseEnable (void);
extern void FXOS8700_I2C1_LowNoiseEnable (void);
extern void FXOS8700_I2C0_LowNoiseDisable (void);
extern void FXOS8700_I2C1_LowNoiseDisable (void);
extern void FXOS8700_I2C0_FastReadEnable (void);
extern void FXOS8700_I2C1_FastReadEnable (void);
extern void FXOS8700_I2C0_FastReadDisable (void);
extern void FXOS8700_I2C1_FastReadDisable (void);
extern void FXOS8700_I2C0_Active (void);
extern void FXOS8700_I2C1_Active (void);
extern void FXOS8700_I2C0_Standby (void);
extern void FXOS8700_I2C1_Standby (void);
extern void FXOS8700_I2C0_SelfTestEnable (void);
extern void FXOS8700_I2C1_SelfTestEnable (void);
extern void FXOS8700_I2C0_SelfTestDisable (void);
extern void FXOS8700_I2C1_SelfTestDisable (void);
extern void FXOS8700_I2C0_Reset (void);
extern void FXOS8700_I2C1_Reset (void);
extern void FXOS8700_I2C0_AutoSleepEnable (void);
extern void FXOS8700_I2C1_AutoSleepEnable (void);
extern void FXOS8700_I2C0_AutoSleepDisable (void);
extern void FXOS8700_I2C1_AutoSleepDisable (void);
extern void FXOS8700_I2C0_OverSampling (uint8 mask);
extern void FXOS8700_I2C1_OverSampling (uint8 mask);

extern void FXOS8700_I2C0_FIFOEnable(void);
extern void FXOS8700_I2C1_FIFOEnable(void);
extern void FXOS8700_I2C0_FIFOBypassed(void);
extern void FXOS8700_I2C1_FIFOBypassed(void);
extern void FXOS8700_I2C0_WakeTransEnable(void);
extern void FXOS8700_I2C1_WakeTransEnable(void);
extern void FXOS8700_I2C0_WakeTransDisable(void);
extern void FXOS8700_I2C1_WakeTransDisable(void);
extern void FXOS8700_I2C0_WakeOrientationEnable(void);
extern void FXOS8700_I2C1_WakeOrientationEnable(void);
extern void FXOS8700_I2C0_WakeOrientationDisable(void);
extern void FXOS8700_I2C1_WakeOrientationDisable(void);
extern void FXOS8700_I2C0_WakePulseEnable(void);
extern void FXOS8700_I2C1_WakePulseEnable(void);
extern void FXOS8700_I2C0_WakePulseDisable(void);
extern void FXOS8700_I2C1_WakePulseDisable(void);
extern void FXOS8700_I2C0_WakeFreefallMotionEnable(void);
extern void FXOS8700_I2C1_WakeFreefallMotionEnable(void);
extern void FXOS8700_I2C0_WakeFreefallMotionDisable(void);
extern void FXOS8700_I2C1_WakeFreefallMotionDisable(void);
extern void FXOS8700_I2C0_IntPolarityHigh(void);
extern void FXOS8700_I2C1_IntPolarityHigh(void);
extern void FXOS8700_I2C0_IntPolarityLow(void);
extern void FXOS8700_I2C1_IntPolarityLow(void);
extern void FXOS8700_I2C0_OpenDrainEnable(void);
extern void FXOS8700_I2C1_OpenDrainEnable(void);
extern void FXOS8700_I2C0_PushPullEnable(void);
extern void FXOS8700_I2C1_PushPullEnable(void);
extern void FXOS8700_I2C0_InterruptEnable(uint8 mask);
extern void FXOS8700_I2C1_InterruptEnable(uint8 mask);
extern void FXOS8700_I2C0_InterruptDisable(uint8 mask);
extern void FXOS8700_I2C1_InterruptDisable(uint8 mask);
extern void FXOS8700_I2C0_InterruptOnINT1(uint8 mask);
extern void FXOS8700_I2C1_InterruptOnINT1(uint8 mask);
extern void FXOS8700_I2C0_InterruptOnINT2(uint8 mask);
extern void FXOS8700_I2C1_InterruptOnINT2(uint8 mask);

extern void FXOS8700_I2C0_HPF_CutOff (uint8 mask);
extern void FXOS8700_I2C1_HPF_CutOff (uint8 mask);
extern void FXOS8700_I2C0_OutputDataFilterType (uint8 mask);
extern void FXOS8700_I2C1_OutputDataFilterType (uint8 mask);

extern void FXOS8700_I2C0_ReadRawData (TWR_FXOS8700* ptr_fxos8700);
extern void FXOS8700_I2C1_ReadRawData (TWR_FXOS8700* ptr_fxos8700);

#endif /* __FXOS8700_H */

