/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      mma845x.h
 * @author    B34185
 * @version   1.0.3.0
 * @date      Apr-24-2013
 * @brief     MMA845x driver header file.
 ******************************************************************************/
#ifndef __MMA845X_H
#define __MMA845X_H

#include "i2c.h"
                                                                     
#define MMA845X_I2C_ADDRESS     0x1D                               
#define MMA845X_OUT_ALERT       0x40                               
#define MMA845X_REGS            50
#define MMA84X_PERIODE          10

/*******************************************************************************
* Redefined I2C function for write and read
*******************************************************************************/
//#define MMA845X_I2C0_WRITE_REGISTERS(x,y,z)  (void)I2C0_WriteMultiBytes(MMA845X_I2C_ADDRESS,(x),(y),(z))
//#define MMA845X_I2C1_WRITE_REGISTERS(x,y,z)  (void)I2C1_WriteMultiBytes(MMA845X_I2C_ADDRESS,(x),(y),(z))
//#define MMA845X_I2C0_READ_REGISTERS(x,y,z)   (void)I2C0_ReadMultiBytes(MMA845X_I2C_ADDRESS,(x),(y),(z))
//#define MMA845X_I2C1_READ_REGISTERS(x,y,z)   (void)I2C1_ReadMultiBytes(MMA845X_I2C_ADDRESS,(x),(y),(z))
//
//#define MMA845X_I2C0_WRITE_REGISTER(x,y)     (void)I2C0_WriteByte(MMA845X_I2C_ADDRESS,x,y)
//#define MMA845X_I2C1_WRITE_REGISTER(x,y)     (void)I2C1_WriteByte(MMA845X_I2C_ADDRESS,x,y)
//#define MMA845X_I2C0_READ_REGISTER(x)        (uint8)I2C0_ReadByte(MMA845X_I2C_ADDRESS,x)
//#define MMA845X_I2C1_READ_REGISTER(x)        (uint8)I2C1_ReadByte(MMA845X_I2C_ADDRESS,x)

#define MMA845X_WRITE_REGISTERS(module,x,y,z)  (void)module##_WriteMultiBytes(MMA845X_I2C_ADDRESS,(x),(y),(z))
#define MMA845X_READ_REGISTERS(module,x,y,z)   (void)module##_ReadMultiBytes(MMA845X_I2C_ADDRESS,(x),(y),(z))

#define MMA845X_WRITE_REGISTER(module,x,y)     (void)module##_WriteByte(MMA845X_I2C_ADDRESS,x,y)
#define MMA845X_READ_REGISTER(module,x)        (uint8)module##_ReadByte(MMA845X_I2C_ADDRESS,x)

//  registers address
#define MMA845x_STATUS_REG              0x00                                           
#define MMA845x_OUT_X_MSB_REG           0x01
#define MMA845x_OUT_X_LSB_REG           0x02
#define MMA845x_OUT_Y_MSB_REG           0x03
#define MMA845x_OUT_Y_LSB_REG           0x04
#define MMA845x_OUT_Z_MSB_REG           0x05
#define MMA845x_OUT_Z_LSB_REG           0x06
#define MMA845x_F_SETUP_REG             0x09
#define MMA845x_TRIG_CFG_REG            0x0A
#define MMA845x_SYSMOD_REG              0x0B
#define MMA845x_INT_SOURCE_REG          0x0C
#define MMA845x_WHO_AM_I_REG            0x0D
#define MMA845x_XYZ_DATA_CFG_REG        0x0E
#define MMA845x_HP_FILTER_CUTOFF_REG    0x0F
#define MMA845x_PL_STATUS_REG           0x10
#define MMA845x_PL_CFG_REG              0x11
#define MMA845x_PL_COUNT_REG            0x12
#define MMA845x_PL_BF_ZCOMP_REG         0x13
#define MMA845x_P_L_THS_REG_REG         0x14
#define MMA845x_FF_MT_CFG_REG           0x15
#define MMA845x_FF_MT_SRC_REG           0x16
#define MMA845x_FF_MT_THS_REG           0x17
#define MMA845x_FF_MT_COUNT_REG         0x18
#define MMA845x__CFG_REG                0x1D
#define MMA845x_TRANSIENT_SCR_REG       0x1E
#define MMA845x_TRANSIENT_THS_REG       0x1F
#define MMA845x_TRANSIENT_COUNT_REG     0x20
#define MMA845x_PULSE_CFG_REG           0x21
#define MMA845x_PULSE_SRC_REG           0x22
#define MMA845x_PULSE_THSX_REG          0x23
#define MMA845x_PULSE_THSY_REG          0x24
#define MMA845x_PULSE_THSZ_REG          0x25
#define MMA845x_PULSE_TMLT_REG          0x26
#define MMA845x_PULSE_LTCY_REG          0x27
#define MMA845x_PULSE_WIND_REG          0x28
#define MMA845x_ASLP_COUNT_REG          0x29
#define MMA845x_CTRL_REG1_REG           0x2A
#define MMA845x_CTRL_REG2_REG           0x2B
#define MMA845x_CTRL_REG3_REG           0x2C
#define MMA845x_CTRL_REG4_REG           0x2D
#define MMA845x_CTRL_REG5_REG           0x2E
#define MMA845x_OFF_X_REG               0x2F
#define MMA845x_OFF_Y_REG               0x30
#define MMA845x_OFF_Z_REG               0x31

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

#define BIT_ZYXDR_MASK                  0x80
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
}TWR_MMA845X_DATA;

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
}TWR_MMA845X;

typedef enum
{
  MMA8451_ID = 0x1A,
  MMA8452_ID = 0x2A,                                        
  MMA8453_ID = 0x3A,
}MMA845X_IDS;                                               
                                                            

typedef union 
{
  int16 m_signed_int;
  uint16 m_unsigned_int;
}INT_UINT_CONVERSION;

/***************************************************************************//*!
 * @brief   MMA845X initialization for I2Cx module. 
 * @param   void
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_Init(module)            MMA845x_##module##_Init()

/***************************************************************************//*!
 * @brief   MMA845X de-initialization for I2Cx module. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_DeInit(module)          MMA845x_##module##_DeInit()

/***************************************************************************//*!
 * @brief   Activate MMA845X reset. Put all registers into the default state. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_Reset(module)          MMA845x_##module##_Reset()

/***************************************************************************//*!
 * @brief   Set MMA845X dynamic range mode I2Cx module. 
 * @param   module - I2C0|I2C1
 * @param   mask - FULL_SCALE_2G|FULL_SCALE_4G|FULL_SCALE_8G
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_DynamicRange(module, mask) MMA845x_##module##_DynamicRange(mask)  

/***************************************************************************//*!
 * @brief   Set MMA845X auto wake sampling frequency I2Cx module. 
 * @param   module - I2C0|I2C1
 * @param   mask - WAKE_50HZ|WAKE_12_5HZ|WAKE_6_25HZ|WAKE_1_56HZ
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_AutoWake(module, mask) MMA845x_##module##_AutoWake(mask)

/***************************************************************************//*!
 * @brief   Set MMA845X dynamic range mode I2Cx module. 
 * @param   module - I2C0|I2C1
 * @param   mask - DR_800HZ|DR_400HZ|DR_200HZ|DR_100HZ|DR_50HZ|DR_12_5_HZ|        
 *                 DR_6_25_HZ|DR_1_563_HZ  
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_DataRate(module, mask) MMA845x_##module##_DataRate(mask)

/***************************************************************************//*!
 * @brief   Put MMA845X into low noisemode I2Cx module. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_LowNoiseEnable(module)  MMA845x_##module##_LowNoiseEnable()

/***************************************************************************//*!
 * @brief   Disable MMA845X low noise mode I2Cx module. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_LowNoiseDisable(module)  MMA845x_##module##_LowNoiseDisable()

/***************************************************************************//*!
 * @brief   Put MMA845X in to the fast read mode I2Cx module. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_FastReadEnable(module)  MMA845x_##module##_FastReadEnable()
   
/***************************************************************************//*!
 * @brief   Disable MMA845X fast read mode I2Cx module. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_FastReadDisable(module)  MMA845x_##module##_FastReadDisable()
   
/***************************************************************************//*!
 * @brief   Put MMA845X into active mode I2Cx module. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_Active(module)          MMA845x_##module##_Active()
   
/***************************************************************************//*!
 * @brief   Put MMA845X into standby mode I2Cx module. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_Standby(module)          MMA845x_##module##_Standby()
   
/***************************************************************************//*!
 * @brief   Put MMA845X into self test I2Cx module. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_SelfTestEnable(module)  MMA845x_##module##_SelfTestEnable()
   
/***************************************************************************//*!
 * @brief   Disable self test on MMA845X I2Cx module. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_SelfTestDisable(module) MMA845x_##module##_SelfTestDisable()
   
/***************************************************************************//*!
 * @brief   Put MMA845X into auto sleep mode I2Cx module. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_AutoSleepEnable(module)  MMA845x_##module##_AutoSleepEnable()
   
/***************************************************************************//*!
 * @brief   Disable auto sleep mode on MMA845X I2Cx module. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_AutoSleepDisable(module) MMA845x_##module##_AutoSleepDisable()

/***************************************************************************//*!
 * @brief   Set MMA845X over sampling mode I2Cx module. 
 * @param   module - I2C0|I2C1
 * @param   mask - MODS_NORMAL|MODS_LOW_NOISE|MODS_HIGH_RESOLUTION        
 *                 MODS_LOW_POWER|MODS_SLEEP_NORMAL|MODS_SLEEP_LOW_NOISE        
 *                 MODS_SLEEP_HIGH_RESOLUTION|MODS_SLEEP_LOW_POWER        
 *                 MODS_BOTH_NORMAL|MODS_BOTH_LOW_NOISE|MODS_BOTH_HIGH_RESOLUTION   
 *                 MODS_BOTH_LOW_POWER  
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_OverSampling(module, mask) MMA845x_##module##_OverSampling(mask)     

/***************************************************************************//*!
 * @brief   The FIFO input buffer is blocked when transitioning from WAKE to 
 *          SLEEP mode or from SLEEP to WAKE mode until the FIFO is flushed.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_FIFOEnable(module)  MMA845x_##module##_FIFOEnable()

/***************************************************************************//*!
* @brief    FIFO gate is bypassed.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_FIFOBypassed(module)  MMA845x_##module##_FIFOBypassed()

/***************************************************************************//*!
 * @brief   Transient function interrupt can wake up system.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_WakeTransEnable(module)  MMA845x_##module##_WakeTransEnable()

/***************************************************************************//*!
 * @brief   Transient function is bypassed in SLEEP mode.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_WakeTransDisable(module)  MMA845x_##module##_WakeTransDisable()

/***************************************************************************//*!
 * @brief   Orientation function interrupt can wake up system.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_WakeOrientationEnable(module)  MMA845x_##module##_WakeOrientationEnable()

/***************************************************************************//*!
 * @brief   Orientation function is bypassed in SLEEP mode.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_WakeOrientationDisable(module)  MMA845x_##module##_WakeOrientationDisable()

/***************************************************************************//*!
 * @brief    Pulse function interrupt can wake up system.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_WakePulseEnable(module)  MMA845x_##module##_WakePulseEnable()

/***************************************************************************//*!
 * @brief   Pulse function is bypassed in SLEEP mode.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_WakePulseDisable(module)  MMA845x_##module##_WakePulseDisable()

/***************************************************************************//*!
 * @brief   Freefall/Motion function interrupt can wake up system.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_WakeFreefallMotionEnable(module)  MMA845x_##module##_WakeFreefallMotionEnable()

/***************************************************************************//*!
 * @brief   Freefall/Motion function is bypassed in SLEEP mode.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_WakeFreefallMotionDisable(module)  MMA845x_##module##_WakeFreefallMotionDisable()

/***************************************************************************//*!
 * @brief   Interrupt polarity ACTIVE high.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_IntPolarityHigh(module)  MMA845x_##module##_IntPolarityHigh()

/***************************************************************************//*!
 * @brief   Interrupt polarity ACTIVE low.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_IntPolarityLow(module)  MMA845x_##module##_IntPolarityLow()

/***************************************************************************//*!
 * @brief   Open Drain selection on interrupt pad.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_OpenDrainEnable(module)  MMA845x_##module##_OpenDrainEnable()

/***************************************************************************//*!
 * @brief   Push-Pull selection on interrupt pad.
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_PushPullEnable(module)  MMA845x_##module##_PushPullEnable()

/***************************************************************************//*!
 * @brief   Interrupt enable.
 * @param   module - I2C0|I2C1
 * @param   mask - INT_EN_ASLP_MASK|INT_EN_FIFO_MASK|INT_EN_TRANS_MASK|
 *                 INT_EN_LNDPRT_MASK|INT_EN_PULSE_MASK|INT_EN_FF_MT_MASK|
 *                 INT_EN_DRDY_MASK
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_InterruptEnable(module, mask)  MMA845x_##module##_InterruptEnable(mask)

/***************************************************************************//*!
 * @brief   Interrupt disable.
 * @param   module - I2C0|I2C1
 * @param   mask - INT_EN_ASLP_MASK|INT_EN_FIFO_MASK|INT_EN_TRANS_MASK|
 *                 INT_EN_LNDPRT_MASK|INT_EN_PULSE_MASK|INT_EN_FF_MT_MASK|
 *                 INT_EN_DRDY_MASK
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_InterruptDisable(module, mask)  MMA845x_##module##_InterruptDisable(mask)

/***************************************************************************//*!
 * @brief   Interrupt is routed on INT1 pin.
 * @param   module - I2C0|I2C1
 * @param   mask - INT_CFG_ASLP_MASK|INT_CFG_FIFO_MASK|INT_CFG_TRANS_MASK|
 *                 INT_CFG_LNDPRT_MASK|INT_CFG_PULSE_MASK|INT_CFG_FF_MT_MASK|
 *                 INT_CFG_DRDY_MASK
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_InterruptOnINT1(module, mask)  MMA845x_##module##_InterruptOnINT1(mask)

/***************************************************************************//*!
 * @brief   Interrupt is routed on INT2 pin.
 * @param   module - I2C0|I2C1
 * @param   mask - INT_CFG_ASLP_MASK|INT_CFG_FIFO_MASK|INT_CFG_TRANS_MASK|
 *                 INT_CFG_LNDPRT_MASK|INT_CFG_PULSE_MASK|INT_CFG_FF_MT_MASK|
 *                 INT_CFG_DRDY_MASK
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_InterruptOnINT2(module, mask)  MMA845x_##module##_InterruptOnINT2(mask)

/***************************************************************************//*!
 * @brief   Set MMA845X High-pass filter cut-off frequency ratio. 
 * @param   module - I2C0|I2C1
 * @param   mask - HP_FILTER_CUTOFF_0|HP_FILTER_CUTOFF_1|HP_FILTER_CUTOFF_2        
 *                 HP_FILTER_CUTOFF_3  
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_HPF_CutOff(module, mask) MMA845x_##module##_HPF_CutOff(mask)  

/***************************************************************************//*!
 * @brief   Set filter type by writting into XYZ_DATA_CFG_REG register. 
 * @param   module - I2C0|I2C1
 * @param   mask - LOW_PASS_FILTERED_DATA_OUT|HIGH_PASS_FILTERED_DATA_OUT
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_OutputDataFilterType(module, mask)                             \
        MMA845x_##module##_OutputDataFilterType(mask)
   
/***************************************************************************//*!
 * @brief   MMA845X read data for I2Cx module. 
 * @param   module - I2C0|I2C1
 * @return  void
 * @note    Implemented as function call.
 ******************************************************************************/
#define MMA845x_ReadRawData(module,ptr_module)  MMA845x_##module##_ReadRawData(ptr_module)

/****************************************************************************************
* MMA845x API Functions
*****************************************************************************************/
extern void MMA845x_I2C0_Init (void);
extern void MMA845x_I2C1_Init (void);
extern void MMA845x_I2C0_DeInit (void);
extern void MMA845x_I2C1_DeInit (void);
extern void MMA845x_I2C0_DynamicRange (uint8 mask);
extern void MMA845x_I2C1_DynamicRange (uint8 mask);
extern void MMA845x_I2C0_AutoWake (uint8 mask);
extern void MMA845x_I2C1_AutoWake (uint8 mask);
extern void MMA845x_I2C0_DataRate (uint8 mask);
extern void MMA845x_I2C1_DataRate (uint8 mask);
extern void MMA845x_I2C0_LowNoiseEnable (void);
extern void MMA845x_I2C1_LowNoiseEnable (void);
extern void MMA845x_I2C0_LowNoiseDisable (void);
extern void MMA845x_I2C1_LowNoiseDisable (void);
extern void MMA845x_I2C0_FastReadEnable (void);
extern void MMA845x_I2C1_FastReadEnable (void);
extern void MMA845x_I2C0_FastReadDisable (void);
extern void MMA845x_I2C1_FastReadDisable (void);
extern void MMA845x_I2C0_Active (void);
extern void MMA845x_I2C1_Active (void);
extern void MMA845x_I2C0_Standby (void);
extern void MMA845x_I2C1_Standby (void);
extern void MMA845x_I2C0_SelfTestEnable (void);
extern void MMA845x_I2C1_SelfTestEnable (void);
extern void MMA845x_I2C0_SelfTestDisable (void);
extern void MMA845x_I2C1_SelfTestDisable (void);
extern void MMA845x_I2C0_Reset (void);
extern void MMA845x_I2C1_Reset (void);
extern void MMA845x_I2C0_AutoSleepEnable (void);
extern void MMA845x_I2C1_AutoSleepEnable (void);
extern void MMA845x_I2C0_AutoSleepDisable (void);
extern void MMA845x_I2C1_AutoSleepDisable (void);
extern void MMA845x_I2C0_OverSampling (uint8 mask);
extern void MMA845x_I2C1_OverSampling (uint8 mask);

extern void MMA845x_I2C0_FIFOEnable(void);
extern void MMA845x_I2C1_FIFOEnable(void);
extern void MMA845x_I2C0_FIFOBypassed(void);
extern void MMA845x_I2C1_FIFOBypassed(void);
extern void MMA845x_I2C0_WakeTransEnable(void);
extern void MMA845x_I2C1_WakeTransEnable(void);
extern void MMA845x_I2C0_WakeTransDisable(void);
extern void MMA845x_I2C1_WakeTransDisable(void);
extern void MMA845x_I2C0_WakeOrientationEnable(void);
extern void MMA845x_I2C1_WakeOrientationEnable(void);
extern void MMA845x_I2C0_WakeOrientationDisable(void);
extern void MMA845x_I2C1_WakeOrientationDisable(void);
extern void MMA845x_I2C0_WakePulseEnable(void);
extern void MMA845x_I2C1_WakePulseEnable(void);
extern void MMA845x_I2C0_WakePulseDisable(void);
extern void MMA845x_I2C1_WakePulseDisable(void);
extern void MMA845x_I2C0_WakeFreefallMotionEnable(void);
extern void MMA845x_I2C1_WakeFreefallMotionEnable(void);
extern void MMA845x_I2C0_WakeFreefallMotionDisable(void);
extern void MMA845x_I2C1_WakeFreefallMotionDisable(void);
extern void MMA845x_I2C0_IntPolarityHigh(void);
extern void MMA845x_I2C1_IntPolarityHigh(void);
extern void MMA845x_I2C0_IntPolarityLow(void);
extern void MMA845x_I2C1_IntPolarityLow(void);
extern void MMA845x_I2C0_OpenDrainEnable(void);
extern void MMA845x_I2C1_OpenDrainEnable(void);
extern void MMA845x_I2C0_PushPullEnable(void);
extern void MMA845x_I2C1_PushPullEnable(void);
extern void MMA845x_I2C0_InterruptEnable(uint8 mask);
extern void MMA845x_I2C1_InterruptEnable(uint8 mask);
extern void MMA845x_I2C0_InterruptDisable(uint8 mask);
extern void MMA845x_I2C1_InterruptDisable(uint8 mask);
extern void MMA845x_I2C0_InterruptOnINT1(uint8 mask);
extern void MMA845x_I2C1_InterruptOnINT1(uint8 mask);
extern void MMA845x_I2C0_InterruptOnINT2(uint8 mask);
extern void MMA845x_I2C1_InterruptOnINT2(uint8 mask);

extern void MMA845x_I2C0_HPF_CutOff (uint8 mask);
extern void MMA845x_I2C1_HPF_CutOff (uint8 mask);
extern void MMA845x_I2C0_OutputDataFilterType (uint8 mask);
extern void MMA845x_I2C1_OutputDataFilterType (uint8 mask);

extern void MMA845x_I2C0_ReadRawData (TWR_MMA845X* ptr_mma845x);
extern void MMA845x_I2C1_ReadRawData (TWR_MMA845X* ptr_mma845x);

#endif /* __MMA845X_H */

