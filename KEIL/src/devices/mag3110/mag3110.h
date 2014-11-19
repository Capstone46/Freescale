/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2010 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   mag3110.h
*
* @brief  Header file
*
* @version 1.0.2.0
* 
* @date Apr-25-2012
* 
*******************************************************************************/
#ifndef MAG3110_H
#define MAG3110_H

#include "main.h" 
                                                                     
#define MAG3110_I2C_ADDRESS 0x0E                               
                            
//  registers address
#define MAG3110_DR_STATUS   0x00                                           
#define MAG3110_OUT_X_MSB   0x01                                        
#define MAG3110_DIE_TEMP    0x0F

#define MAG3110_CTRL_REG1   0x10
#define MMA3110_WHOIAM      0x07
#define MMA3110_ID          0xC4
#define MAG3110_REGS        0x12

//  mask
#define BIT_ZYXDR_MASK 0x80
#define RES_14BIT   4
#define RES_12BIT  16
#define RES_10BIT  64

#define XYZ_SIZE  3

// GPIO0IRQ                         UG FIX change MA to MB when needed depending where TWRPI-ADPTSTB is connected
#define MA_GPIO0IRQ PTDD_PTDD5        
#define MA_GPIO0IRQ_D PTDDD_PTDDD5      
#define MA_GPIO0IRQ_INIT MA_GPIO0IRQ=1;MA_GPIO0IRQ_D=1; 
#define MA_GPIO0IRQ_DEINIT MA_GPIO0IRQ=0;MA_GPIO0IRQ_D=0; 

#define MB_GPIO0IRQ PTDD_PTDD6        
#define MB_GPIO0IRQ_D PTDDD_PTDDD6      
#define MB_GPIO0IRQ_INIT MB_GPIO0IRQ=1;MB_GPIO0IRQ_D=1; 
#define MB_GPIO0IRQ_DEINIT MB_GPIO0IRQ=0;MB_GPIO0IRQ_D=0; 

//  typedef
typedef union
{
  Word all;
  struct
  {
    Byte hi;
    Byte lo;
  }Bytes;
}TWR_MAG3110_DATA;

typedef struct
{
  sWord mag_x;
  sWord mag_y;
  sWord mag_z;
  Byte  registers[MAG3110_REGS];
  Byte  reg_write;
  Byte  reg_addr;  
}TWR_MAG3110;

/****************************************************************************************
* Redefined IIC function for write and read
*****************************************************************************************/
#define MAG3110_SET_SLAVE_ADDRESS        IIC_MASTER_SetAddress(MAG3110_I2C_ADDRESS)
#define MAG3110_WRITE_REGISTER(x,y)     (void)IIC_MASTER_WriteByte((x),(y))
#define MAG3110_READ_REGISTERS(x,y,z)   IIC_MASTER_MultiReadBytes((x),(y),(z))
#define MAG3110_READ_REGISTER(x)        IIC_MASTER_ReadByte((x))

/****************************************************************************************
* MMA7660 API Functions
*****************************************************************************************/
void MAG3110_Init(MODULES mod);
void MAG3110_DeInit(void);
void MAG3110_ReadRawData(TWR_MAG3110* MAG3110);

#endif