/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      i2c.c
 * @version   1.0.5.0
 * @date      Apr-15-2013
 * @brief     I2C bus comtroller (I2C) driver header file.
 *
 * Revision History:
 *  1.	20/12/2011   B02785   Initially written
 *  2.	21/08/2012   B02785   Ported to Kinetis M
 *  3.	17/01/2012   B34185   Ported to Kinetis L
 ******************************************************************************/
#include "common.h"
#include "i2c.h"
#include "gpio.h"

#define I2C_TIMEOUT     1000

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static I2C_CALLBACK volatile pCallbackI2C0=NULL;
static I2C_CALLBACK volatile pCallbackI2C1=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void I2C0_isr (void);
void I2C1_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
void I2C0_Init (tI2C i2c, uint8 ip, I2C_CALLBACK pCallback)
{
  if (pCallback != NULL)
  {
    pCallbackI2C0 = pCallback;
    NVIC_SetIsr(INT_I2C0,ip);
  }
  I2C0_A1    = i2c.A1;
  I2C0_F     = i2c.F;
  I2C0_C1    = i2c.C1;
  I2C0_FLT   = i2c.FLT;
  I2C0_RA    = i2c.RA;
  I2C0_SMB   = i2c.SMB;
  I2C0_A2    = i2c.A2;
  I2C0_SLTH  = i2c.SLTH;
  I2C0_SLTL  = i2c.SLTL;
}

void I2C1_Init (tI2C i2c, uint8 ip, I2C_CALLBACK pCallback)
{
  if (pCallback != NULL)
  {
    pCallbackI2C1 = pCallback;
    NVIC_SetIsr(INT_I2C1,ip);
  }
  I2C1_A1    = i2c.A1;
  I2C1_F     = i2c.F;
  I2C1_C1    = i2c.C1;
  I2C1_FLT   = i2c.FLT;
  I2C1_RA    = i2c.RA;
  I2C1_SMB   = i2c.SMB;
  I2C1_A2    = i2c.A2;
  I2C1_SLTH  = i2c.SLTH;
  I2C1_SLTL  = i2c.SLTL;
}

/**************************************************************************//*!
 * @brief  Function writes one byte via I2C0
 * @param  (uint8)u8DevAdr - device address to be written
 * @param  (uint8)u8RegAdr - address of register to be written
 * @param  (uint8)u8Data - data to be written to register
 * @return void
 ******************************************************************************/
void I2C0_WriteByte(uint8 u8DevAdr, uint8 u8RegAdr, uint8 u8Data)
{
  uint32 timeout = 0;

  I2C_Set_TX_mode(I2C0);
  I2C_Start_Signal(I2C0);

  I2C_CycleWrite(I2C0, I2CWRITE(u8DevAdr));
  I2C_CycleWrite(I2C0, u8RegAdr);
  I2C_CycleWrite(I2C0, u8Data);

  I2C_Stop_Signal(I2C0);
  while(I2C_Get_BUSY_flag(I2C0) &&
        (timeout<I2C_TIMEOUT))
    timeout++;
}

/**************************************************************************//*!
 * @brief  Function writes one byte via I2C1
 * @param  (uint8)u8DevAdr - device address to be written
 * @param  (uint8)u8RegAdr - address of register to be written
 * @param  (uint8)u8Data - data to be written to register
 * @return void
 ******************************************************************************/
void I2C1_WriteByte(uint8 u8DevAdr, uint8 u8RegAdr, uint8 u8Data)
{
  uint32 timeout = 0;

  I2C_Set_TX_mode(I2C1);
  I2C_Start_Signal(I2C1);

  I2C_CycleWrite(I2C1, I2CWRITE(u8DevAdr));
  I2C_CycleWrite(I2C1, u8RegAdr);
  I2C_CycleWrite(I2C1, u8Data);

  I2C_Stop_Signal(I2C1);
  while(I2C_Get_BUSY_flag(I2C1) &&
        (timeout<I2C_TIMEOUT))
    timeout++;
}

/**************************************************************************//*!
 * @brief  Function reads one byte via I2C0
 * @param  (uint8)u8DevAdr - device address to be written
 * @param  (uint8)u8Adr - address of register which could be written
 * @return (uint8)dummy - one read byte
 ******************************************************************************/
uint8 I2C0_ReadByte(uint8 u8DevAdr, uint8 u8RegAdr)
{
  vuint8 dummy;
  uint32 timeout = 0;

  I2C_Set_TX_mode(I2C0);
  I2C_Start_Signal(I2C0);

  I2C_CycleWrite(I2C0, I2CWRITE(u8DevAdr));
  I2C_CycleWrite(I2C0, u8RegAdr);

  I2C_Repeat_Start_Signal(I2C0);

  I2C_CycleWrite(I2C0, I2CREAD(u8DevAdr));

  dummy = I2C_CycleRead(I2C0, TRUE);
  dummy = I2C_CycleRead(I2C0, TRUE);

  I2C_Stop_Signal(I2C0);
  while(I2C_Get_BUSY_flag(I2C0) &&
        (timeout<I2C_TIMEOUT))
    timeout++;

  return dummy;
}

/**************************************************************************//*!
 * @brief  Function reads one byte via I2C1
 * @param  (uint8)u8DevAdr - device address to be written
 * @param  (uint8)u8Adr - address of register which could be written
 * @return (uint8)dummy - one read byte
 ******************************************************************************/
uint8 I2C1_ReadByte(uint8 u8DevAdr, uint8 u8RegAdr)
{
  static vuint8 dummy;
  uint32 timeout = 0;

  I2C_Set_TX_mode(I2C1);
  I2C_Start_Signal(I2C1);

  I2C_CycleWrite(I2C1, I2CWRITE(u8DevAdr));
  I2C_CycleWrite(I2C1, u8RegAdr);

  I2C_Repeat_Start_Signal(I2C1);

  I2C_CycleWrite(I2C1, I2CREAD(u8DevAdr));

  dummy = I2C_CycleRead(I2C1, TRUE);
  dummy = I2C_CycleRead(I2C1, TRUE);

  I2C_Stop_Signal(I2C1);
  while(I2C_Get_BUSY_flag(I2C1) &&
        (timeout<I2C_TIMEOUT))
    timeout++;

  return dummy;
}

/**************************************************************************//*!
 * @brief  Function writes multiple bytes via I2C0
 * @param  (uint8)u8DevAdr - device address to be written
 * @param  (uint8)u8RegAdr - address of register to be written
 * @param  *array - pointer to first data byte
 * @param  length - length of the data
 * @return void
 ******************************************************************************/
void I2C0_WriteMultiBytes(uint8 u8DevAdr, uint8 u8RegAdr, uint8 *array, uint8 length)
{
  uint8 i;
  uint32 timeout = 0;

  I2C_Set_TX_mode(I2C0);
  I2C_Start_Signal(I2C0);

  I2C_CycleWrite(I2C0, I2CWRITE(u8DevAdr));
  I2C_CycleWrite(I2C0, u8RegAdr);

  for (i = 0; i < length; i++)
  {
    I2C_CycleWrite(I2C0, *(array++));
  }
  I2C_CycleWrite(I2C0, *(array++));

  I2C_Stop_Signal(I2C0);
  while(I2C_Get_BUSY_flag(I2C0) &&
        (timeout<I2C_TIMEOUT))
    timeout++;
}

/**************************************************************************//*!
 * @brief  Function writes multiple bytes via I2C1
 * @param  (uint8)u8DevAdr - device address to be written
 * @param  (uint8)u8RegAdr - address of register to be written
 * @param  *array - pointer to first data byte
 * @param  length - length of the data
 * @return void
 ******************************************************************************/
void I2C1_WriteMultiBytes(uint8 u8DevAdr, uint8 u8RegAdr, uint8 *array, uint8 length)
{
  uint8 i;
  uint32 timeout = 0;

  I2C_Set_TX_mode(I2C1);
  I2C_Start_Signal(I2C1);

  I2C_CycleWrite(I2C1, I2CWRITE(u8DevAdr));
  I2C_CycleWrite(I2C1, u8RegAdr);

  for (i = 0; i < length; i++)
  {
    I2C_CycleWrite(I2C1, *(array++));
  }
  I2C_CycleWrite(I2C1, *(array++));

  I2C_Stop_Signal(I2C1);
  while(I2C_Get_BUSY_flag(I2C1) &&
        (timeout<I2C_TIMEOUT))
    timeout++;
}

/**************************************************************************//*!
 * @brief  Function reads multiple bytes via I2C0
 * @param  u8DevAdr - device address to be written
 * @param  u8Adr - address of register which could be written
 * @param  *array - pointer to first data byte
 * @param  length - length of the data
 * @return void
 ******************************************************************************/
void I2C0_ReadMultiBytes(uint8 u8DevAdr, uint8 u8RegAdr, uint8 *array, uint8 length)
{
  vuint8 dummy, i;
  uint32 timeout = 0;

  I2C_Set_TX_mode(I2C0);
  I2C_Start_Signal(I2C0);

  I2C_CycleWrite(I2C0, I2CWRITE(u8DevAdr));
  I2C_CycleWrite(I2C0, u8RegAdr);

  I2C_Repeat_Start_Signal(I2C0);

  I2C_CycleWrite(I2C0, I2CREAD(u8DevAdr));

  dummy = I2C_CycleRead(I2C0, FALSE);
  for (i = 0; i < length; i++)
  {
    *(array++) = I2C_CycleRead(I2C0, FALSE);
  }
  *(array++) = I2C_CycleRead(I2C0, TRUE);

  I2C_Stop_Signal(I2C0);
  while(I2C_Get_BUSY_flag(I2C0) &&
        (timeout<I2C_TIMEOUT))
    timeout++;
}

/**************************************************************************//*!
 * @brief  Function reads multiple bytes via I2C1
 * @param  u8DevAdr - device address to be written
 * @param  u8Adr - address of register which could be written
 * @param  *array - pointer to first data byte
 * @param  length - length of the data
 * @return void
 ******************************************************************************/
void I2C1_ReadMultiBytes(uint8 u8DevAdr, uint8 u8RegAdr, uint8 *array, uint8 length)
{
  vuint8 dummy, i;
  uint32 timeout = 0;

  I2C_Set_TX_mode(I2C1);
  I2C_Start_Signal(I2C1);

  I2C_CycleWrite(I2C1, I2CWRITE(u8DevAdr));
  I2C_CycleWrite(I2C1, u8RegAdr);

  I2C_Repeat_Start_Signal(I2C1);

  I2C_CycleWrite(I2C1, I2CREAD(u8DevAdr));

  dummy = I2C_CycleRead(I2C1, FALSE);
  for (i = 0; i < length; i++)
  {
    *(array++) = I2C_CycleRead(I2C1, FALSE);
  }
  *(array++) = I2C_CycleRead(I2C1, TRUE);

  I2C_Stop_Signal(I2C1);
  while(I2C_Get_BUSY_flag(I2C1) &&
        (timeout<I2C_TIMEOUT))
    timeout++;
}


/**************************************************************************//*!
 * @brief  Function provide one cycle write process on I2C
 * @param  (uint8)u8Data - data to be written
 * @return void
 ******************************************************************************/
void I2C0_CycleWrite(uint8 u8Data)
{
  uint32 timeout;

  timeout = 0;
#if (defined (MCU_MKL43Z256))
  while (((!I2C_Get_TC_flag(I2C0)) || (!I2C_Get_EMPTY_flag(I2C0))) &&
         (timeout<I2C_TIMEOUT))
#else
  while ((!I2C_Get_TC_flag(I2C0)) &&
         (timeout<I2C_TIMEOUT))
#endif
  timeout++;
  I2C_Write_Data(I2C0,u8Data);
  timeout = 0;
  while((!I2C_Get_Irq_flag(I2C0)) &&
        (timeout<I2C_TIMEOUT))
  timeout++;
  I2C_Clear_Irq_flag(I2C0);
}

/**************************************************************************//*!
 * @brief  Function provide one cycle write process on I2C
 * @param  (uint8)u8Data - data to be written
 * @return void
 ******************************************************************************/
void I2C1_CycleWrite(uint8 u8Data)
{
  uint32 timeout;

  timeout = 0;
#if (defined (MCU_MKL43Z256))
  while (((!I2C_Get_TC_flag(I2C1)) || (!I2C_Get_EMPTY_flag(I2C1))) &&
         (timeout<I2C_TIMEOUT))
#else
  while ((!I2C_Get_TC_flag(I2C1)) &&
         (timeout<I2C_TIMEOUT))
#endif
  timeout++;
  I2C_Write_Data(I2C1,u8Data);
  timeout = 0;
  while((!I2C_Get_Irq_flag(I2C1)) &&
        (timeout<I2C_TIMEOUT))
  timeout++;
  I2C_Clear_Irq_flag(I2C1);
}

/**************************************************************************//*!
 * @brief  Function provide one cycle read process on I2C
 * @param  u8Ack - TRUE or FAULSE
 * @return I2C data
 ******************************************************************************/
uint8 I2C0_CycleRead(uint8 u8Ack)
{
  uint32 timeout;
  uint8 dummy;

  timeout = 0;
  while ((!I2C_Get_TC_flag(I2C0)) &&
         (timeout<I2C_TIMEOUT))
  timeout++;
  I2C_Set_RX_mode(I2C0);
  if (u8Ack)
  {
    I2C_Set_NACK_mode(I2C0);
  }
  else
  {
    I2C_Clr_NACK_mode(I2C0);
  }
  dummy = I2C_Read_Data(I2C0);
  timeout = 0;
  while((!I2C_Get_Irq_flag(I2C0)) &&
        (timeout<I2C_TIMEOUT))
  timeout++;
  I2C_Clear_Irq_flag(I2C0);

  return dummy;
}

/**************************************************************************//*!
 * @brief  Function provide one cycle read process on I2C
 * @param  u8Ack - TRUE or FAULSE
 * @return I2C data
 ******************************************************************************/
uint8 I2C1_CycleRead(uint8 u8Ack)
{
  uint32 timeout;
  uint8 dummy;

  timeout = 0;
  while ((!I2C_Get_TC_flag(I2C1)) &&
         (timeout<I2C_TIMEOUT))
  timeout++;
  I2C_Set_RX_mode(I2C1);
  if (u8Ack)
  {
    I2C_Set_NACK_mode(I2C1);
  }
  else
  {
    I2C_Clr_NACK_mode(I2C1);
  }
  dummy = I2C_Read_Data(I2C1);
  timeout = 0;
  while((!I2C_Get_Irq_flag(I2C1)) &&
        (timeout<I2C_TIMEOUT))
  timeout++;
  I2C_Clear_Irq_flag(I2C1);

  return dummy;
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void I2C0_isr (void)
{
  /* process I2C0 interrupt                                                   */
  if (I2C_Get_Stopf_flag(I2C0))
    I2C_Clear_Stopf_flag(I2C0);
  if (I2C_Get_Irq_flag (I2C0))
  {
      I2C_Clear_Irq_flag(I2C0);
      pCallbackI2C0 (I2C0_CALLBACK);
  }
}

void I2C1_isr (void)
{
  GPIO_Set (GPIOD, PIN_6);
  /* process I2C1 interrupt                                                   */
  if (I2C_Get_Stopf_flag(I2C1))
    I2C_Clear_Stopf_flag(I2C1);
  if (I2C_Get_Irq_flag (I2C1))
  {
      I2C_Clear_Irq_flag(I2C1);
      pCallbackI2C1 (I2C1_CALLBACK);
  }
  GPIO_Clr (GPIOD, PIN_6);
}

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
