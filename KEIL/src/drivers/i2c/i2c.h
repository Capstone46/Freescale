/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      i2c.h
 * @version   1.0.4.0
 * @date      Apr-15-2013
 * @brief     I2C bus comtroller (I2C) driver header file.
 *
 * Revision History:
 *  1.	20/12/2011   B02785   Initially written
 *  2.	21/08/2012   B02785   Ported to Kinetis M
 *  3.	17/01/2013   B34185   Ported to Kinetis L
 *  4.	15/04/2013   B34185   PGA review correction
 *  5.	29/05/2013   B34185   backward compatibility status register definition removed
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup i2c_example0
 * @{
 * @par       Source code:
 * @include   i2c0_test\i2c0_test.c
 * @par       Appconfig.h:
 * @include   i2c0_test\appconfig.h
 ******************************************************************************/
/*! @} End of i2c_example0                                                    */
#ifndef __I2C_H
#define __I2C_H

/******************************************************************************
 * definition configuration structure                                         *
 ******************************************************************************/
typedef struct { uint8 A1, F, C1, C2, FLT, RA, SMB, A2, SLTH, SLTL; } tI2C;

#define I2CWRITE(DevAdr)        (uint8)((DevAdr<<1)&0xFE)
#define I2CREAD(DevAdr)         (uint8)((DevAdr<<1)|0x01)

/******************************************************************************
* I2C module polling configurations used by I2C_init() function
*
*//*! @addtogroup i2c_config
* @{
*******************************************************************************/
#define I2C_MODULE_M_CONFIG(mul,icr)                                          \
(tI2C){                                                                       \
/* A1     */  CLR(I2C_A1_AD(0)),                                              \
/* F      */  SET(I2C_F_MULT(mul))|SET(I2C_F_ICR(icr)),                       \
/* C1     */  SET(I2C_C1_IICEN_MASK)|CLR(I2C_C1_IICIE_MASK)|                  \
              CLR(I2C_C1_MST_MASK)|CLR(I2C_C1_TX_MASK)|                       \
              CLR(I2C_C1_TXAK_MASK)|CLR(I2C_C1_RSTA_MASK)|                    \
              CLR(I2C_C1_WUEN_MASK)|CLR(I2C_C1_DMAEN_MASK),                   \
/* C2     */  CLR(I2C_C2_GCAEN_MASK)|CLR(I2C_C2_ADEXT_MASK)|                  \
              CLR(I2C_C2_HDRS_MASK)|CLR(I2C_C2_SBRC_MASK)|                    \
              CLR(I2C_C2_RMEN_MASK)|SET(I2C_C2_AD(0)),                        \
/* FLT    */  SET(I2C_FLT_FLT(0)),                                            \
/* RA     */  SET(I2C_RA_RAD(0)),                                             \
/* SMB    */  CLR(I2C_SMB_FACK_MASK)|CLR(I2C_SMB_ALERTEN_MASK)|               \
              CLR(I2C_SMB_SIICAEN_MASK)|CLR(I2C_SMB_TCKSEL_MASK)|             \
              CLR(I2C_SMB_SLTF_MASK)|CLR(I2C_SMB_SHTF2_MASK)|                 \
              CLR(I2C_SMB_SHTF2IE_MASK),                                      \
/* A2     */  SET(I2C_A2_SAD(0)),                                             \
/* SLTH   */  SET(I2C_SLTH_SSLT(0)),                                          \
/* SLTL   */  SET(I2C_SLTL_SSLT(0)),                                          \
}

#define I2C_MODULE_MASTER_BAUD_100K_CLK_48MHZ     I2C_MODULE_M_CONFIG(0x0,0x27)
#define I2C_MODULE_MASTER_BAUD_100K_CLK_24MHZ     I2C_MODULE_M_CONFIG(0x0,0x1F)
#define I2C_MODULE_MASTER_BAUD_100K_CLK_12MHZ     I2C_MODULE_M_CONFIG(0x0,0x17)
#define I2C_MODULE_MASTER_BAUD_50K_CLK_48MHZ      I2C_MODULE_M_CONFIG(0x1,0x27)
#define I2C_MODULE_MASTER_BAUD_50K_CLK_24MHZ      I2C_MODULE_M_CONFIG(0x1,0x1F)
#define I2C_MODULE_MASTER_BAUD_50K_CLK_12MHZ      I2C_MODULE_M_CONFIG(0x1,0x17)
#define I2C_MODULE_MASTER_BAUD_400K_CLK_48MHZ     I2C_MODULE_M_CONFIG(0x2,0x05)
#define I2C_MODULE_MASTER_BAUD_400K_CLK_24MHZ     I2C_MODULE_M_CONFIG(0x1,0x05)
#define I2C_MODULE_MASTER_BAUD_400K_CLK_12MHZ     I2C_MODULE_M_CONFIG(0x0,0x05)

// just for compatibility with previous versions
#define I2C_MODULE_100K_MASTER_IRQ_DIS_CONFIG   I2C_MODULE_MASTER_BAUD_100K_CLK_48MHZ
/**************************************************************************/ /*!
 * @brief I2C setting:
 *        baud rate 100KBd
 *        module enable after initialization
 *        irq. disable
 * @param baute - baude rate as 400K|100K|50K (device dependent)
 * @param modclk - module clock as 48MHZ|24MHZ|12MHZ
  *****************************************************************************/
#define I2C_MODULE_MASTER_CONFIG(baute,modclk)  I2C_MODULE_MASTER_##baute##_##modclk

/******************************************************************************
* I2C module interrupt configurations used by I2C_init() function
*
*//*! @addtogroup i2c_config
* @{
*******************************************************************************/
#define I2C_MODULE_M_IRQ_CONFIG(mul,icr)                                      \
(tI2C){                                                                       \
/* A1     */  CLR(I2C_A1_AD(0)),                                              \
/* F      */  SET(I2C_F_MULT(mul))|SET(I2C_F_ICR(icr)),                       \
/* C1     */  SET(I2C_C1_IICEN_MASK)|SET(I2C_C1_IICIE_MASK)|                  \
              CLR(I2C_C1_MST_MASK)|CLR(I2C_C1_TX_MASK)|                       \
              CLR(I2C_C1_TXAK_MASK)|CLR(I2C_C1_RSTA_MASK)|                    \
              CLR(I2C_C1_WUEN_MASK)|CLR(I2C_C1_DMAEN_MASK),                   \
/* C2     */  CLR(I2C_C2_GCAEN_MASK)|CLR(I2C_C2_ADEXT_MASK)|                  \
              CLR(I2C_C2_HDRS_MASK)|CLR(I2C_C2_SBRC_MASK)|                    \
              CLR(I2C_C2_RMEN_MASK)|SET(I2C_C2_AD(0)),                        \
/* FLT    */  SET(I2C_FLT_FLT(0)),                                            \
/* RA     */  SET(I2C_RA_RAD(0)),                                             \
/* SMB    */  CLR(I2C_SMB_FACK_MASK)|CLR(I2C_SMB_ALERTEN_MASK)|               \
              CLR(I2C_SMB_SIICAEN_MASK)|CLR(I2C_SMB_TCKSEL_MASK)|             \
              CLR(I2C_SMB_SLTF_MASK)|CLR(I2C_SMB_SHTF2_MASK)|                 \
              CLR(I2C_SMB_SHTF2IE_MASK),                                      \
/* A2     */  SET(I2C_A2_SAD(0)),                                             \
/* SLTH   */  SET(I2C_SLTH_SSLT(0)),                                          \
/* SLTL   */  SET(I2C_SLTL_SSLT(0)),                                          \
}

#define I2C_MODULE_MASTER_IRQ_BAUD_100K_CLK_48MHZ     I2C_MODULE_M_IRQ_CONFIG(0x0,0x27)
#define I2C_MODULE_MASTER_IRQ_BAUD_100K_CLK_24MHZ     I2C_MODULE_M_IRQ_CONFIG(0x0,0x1F)
#define I2C_MODULE_MASTER_IRQ_BAUD_100K_CLK_12MHZ     I2C_MODULE_M_IRQ_CONFIG(0x0,0x17)
#define I2C_MODULE_MASTER_IRQ_BAUD_50K_CLK_48MHZ      I2C_MODULE_M_IRQ_CONFIG(0x1,0x27)
#define I2C_MODULE_MASTER_IRQ_BAUD_50K_CLK_24MHZ      I2C_MODULE_M_IRQ_CONFIG(0x1,0x1F)
#define I2C_MODULE_MASTER_IRQ_BAUD_50K_CLK_12MHZ      I2C_MODULE_M_IRQ_CONFIG(0x1,0x17)
#define I2C_MODULE_MASTER_IRQ_BAUD_400K_CLK_48MHZ     I2C_MODULE_M_IRQ_CONFIG(0x2,0x05)
#define I2C_MODULE_MASTER_IRQ_BAUD_400K_CLK_24MHZ     I2C_MODULE_M_IRQ_CONFIG(0x1,0x05)
#define I2C_MODULE_MASTER_IRQ_BAUD_400K_CLK_12MHZ     I2C_MODULE_M_IRQ_CONFIG(0x0,0x05)

// just for compatibility with previous versions
#define I2C_MODULE_100K_MASTER_IRQ_EN_CONFIG   I2C_MODULE_MASTER_IRQ_BAUD_100K_CLK_48MHZ
/**************************************************************************/ /*!
 * @brief I2C setting:
 *        baud rate 100KBd
 *        module enable after initialization
 *        irq. disable
 * @param baute - baude rate as 400K|100K|50K (device dependent)
 * @param modclk - module clock as 48MHZ|24MHZ|12MHZ
  *****************************************************************************/
#define I2C_MODULE_MASTER_IRQ_CONFIG(baute,modclk)  I2C_MODULE_MASTER_IRQ_##baute##_##modclk

/*! @} End of i2c_config                                                      */

/******************************************************************************
* I2C callback used by I2C_Init() function
*
*//*! @addtogroup i2c_callback
* @{
*******************************************************************************/
/*! @brief I2C_CALLBACK type declaration                                      */
typedef enum
{
  I2C0_CALLBACK=1,      ///< I2C0 interrupt
  I2C1_CALLBACK=2,      ///< I2C1 interrupt
} I2C_CALLBACK_TYPE;

/*! @brief I2C_CALLBACK function declaration                                  */
typedef void (*I2C_CALLBACK)(I2C_CALLBACK_TYPE type);
/*! @} End of i2c_callback                                                    */

/******************************************************************************
* I2C function and macro definitions
*
*//*! @addtogroup i2c_macro
* @{
*******************************************************************************/
#define I2C0_Start_Signal         REG_SetVal(I2C0_C1,I2C_C1_MST,0x1)
#define I2C1_Start_Signal         REG_SetVal(I2C1_C1,I2C_C1_MST,0x1)
/***************************************************************************//*!
 * @brief   Macro generate Start condition on the bus.
 * @details This macro generate Start condition.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Start_Signal(module)  module##_Start_Signal

#define I2C0_Stop_Signal          REG_SetVal(I2C0_C1,I2C_C1_MST,0x0)
#define I2C1_Stop_Signal          REG_SetVal(I2C1_C1,I2C_C1_MST,0x0)
/***************************************************************************//*!
 * @brief   Macro generate Stop condition on the bus.
 * @details This macro generate Stop condition.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Stop_Signal(module)   module##_Stop_Signal

#define I2C0_Repeat_Start_Signal  REG_SetVal(I2C0_C1, I2C_C1_RSTA,0x1)
#define I2C1_Repeat_Start_Signal  REG_SetVal(I2C1_C1, I2C_C1_RSTA,0x1)
/***************************************************************************//*!
 * @brief   Macro generate Repeat Start condition on the bus.
 * @details This macro generate Repeat Start condition.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Repeat_Start_Signal(module)     module##_Repeat_Start_Signal

#define I2C0_Write_Data(data)     (I2C0_D = data)
#define I2C1_Write_Data(data)     (I2C1_D = data)
/***************************************************************************//*!
 * @brief   Macro Write data for transfer.
 * @details Write data to Data register for transfer start.
 * @param   module    I2C0,I2C1
 * @param   data     @ref uint8 load register value
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Write_Data(module,data)  module##_Write_Data(data)

#define I2C0_Read_Data            (uint8)I2C0_D
#define I2C1_Read_Data            (uint8)I2C1_D
/***************************************************************************//*!
 * @brief   Macro Return data form last transfer
 * @details Read last received data from Data register.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Read_Data(module)     module##_Read_Data

#define I2C0_Get_TC_flag         (I2C0_S&I2C_S_TCF_MASK)
#define I2C1_Get_TC_flag         (I2C1_S&I2C_S_TCF_MASK)
/***************************************************************************//*!
 * @brief   Macro Return transfer complete flag
 * @details Read Status register.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Get_TC_flag(module)   module##_Get_TC_flag

#define I2C0_Get_BUSY_flag        (I2C0_S&I2C_S_BUSY_MASK)
#define I2C1_Get_BUSY_flag        (I2C1_S&I2C_S_BUSY_MASK)
/***************************************************************************//*!
 * @brief   Macro Return transfer complete flag
 * @details Read Status register.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Get_BUSY_flag(module) module##_Get_BUSY_flag

#define I2C0_Get_Irq_flag         (I2C0_S&I2C_S_IICIF_MASK)
#define I2C1_Get_Irq_flag         (I2C1_S&I2C_S_IICIF_MASK)
/***************************************************************************//*!
 * @brief   Macro Return Irq. flag
 * @details Read Status register.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Get_Irq_flag(module)  module##_Get_Irq_flag

#define I2C0_Clear_Irq_flag       REG_SetVal(I2C0_S, I2C_S_IICIF,0x1)
#define I2C1_Clear_Irq_flag       I2C1_S |= 0x02;//REG_SetVal(I2C1_S, I2C_S_IICIF,0x1)
/***************************************************************************//*!
 * @brief   Macro clear Irq. flag
 * @details Write to Status register.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Clear_Irq_flag(module)  module##_Clear_Irq_flag




#define I2C0_Get_Stopf_flag         (I2C0_FLT&I2C_FLT_STOPF_MASK)
#define I2C1_Get_Stopf_flag         (I2C1_FLT&I2C_FLT_STOPF_MASK)
/***************************************************************************//*!
 * @brief   Macro Return bus stop detect flag.
 * @details Read glitch filter register.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Get_Stopf_flag(module)  module##_Get_Stopf_flag

#define I2C0_Clear_Stopf_flag       REG_SetVal(I2C0_FLT, I2C_FLT_STOPF,0x1)
#define I2C1_Clear_Stopf_flag       REG_SetVal(I2C1_FLT, I2C_FLT_STOPF,0x1)
/***************************************************************************//*!
 * @brief   Macro clear bus stop detect flag.
 * @details Write to glitch filter register.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Clear_Stopf_flag(module)  module##_Clear_Stopf_flag







#define I2C0_Set_RX_mode          REG_SetVal(I2C0_C1, I2C_C1_TX,0x0)
#define I2C1_Set_RX_mode          REG_SetVal(I2C1_C1, I2C_C1_TX,0x0)
/***************************************************************************//*!
 * @brief   Macro change I2C mode RX
 * @details Clear I2Cx_C1.TX for change RX mode.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Set_RX_mode(module)   module##_Set_RX_mode

#define I2C0_Set_TX_mode          REG_SetVal(I2C0_C1, I2C_C1_TX,0x1)
#define I2C1_Set_TX_mode          REG_SetVal(I2C1_C1, I2C_C1_TX,0x1)
/***************************************************************************//*!
 * @brief   Macro change I2C mode TX
 * @details Set I2Cx_C1.TX for change TX mode.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Set_TX_mode(module)   module##_Set_TX_mode

#define I2C0_Set_NACK_mode        REG_SetVal(I2C0_C1, I2C_C1_TXAK,0x1)
#define I2C1_Set_NACK_mode        REG_SetVal(I2C1_C1, I2C_C1_TXAK,0x1)
/***************************************************************************//*!
 * @brief   Macro change I2C mode NACK
 * @details Set I2Cx_C1.TXAK for change TX mode.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Set_NACK_mode(module) module##_Set_NACK_mode

#define I2C0_Clr_NACK_mode        REG_SetVal(I2C0_C1, I2C_C1_TXAK,0x0)
#define I2C1_Clr_NACK_mode        REG_SetVal(I2C1_C1, I2C_C1_TXAK,0x0)
/***************************************************************************//*!
 * @brief   Macro change I2C mode NACK
 * @details Clear I2Cx_C1.TXAK for change RX mode.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Clr_NACK_mode(module)  module##_Clr_NACK_mode

#if (defined (MCU_MKL43Z256))

#define I2C0_Get_EMPTY_flag         (I2C0_S2&I2C_S2_EMPTY_MASK)
#define I2C1_Get_EMPTY_flag         (I2C1_S2&I2C_S2_EMPTY_MASK)
/***************************************************************************//*!
 * @brief   Macro returns RX/TX buffer empty flag
 * @details Read Status register.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Get_EMPTY_flag(module)   module##_Get_EMPTY_flag

#define I2C0_Get_ERROR_flag         (I2C0_S2&I2C_S2_ERROR_MASK)
#define I2C1_Get_ERROR_flag         (I2C1_S2&I2C_S2_ERROR_MASK)
/***************************************************************************//*!
 * @brief   Macro returns read/write error flag (when 3 or more r/w errors).
 * @details Read Status register.
 * @param   module    I2C0,I2C1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define I2C_Get_ERROR_flag(module)   module##_Get_ERROR_flag

#endif

/* Function redefinition                                                      */

/***************************************************************************//*!
 * @brief   I2C initialization function.
 * @details This function initializes selected timer channel of the
 *          I2C bus (I2C) block.
 * @param   module    I2C0,I2C1
 * @param   cfg       Use one of following configuration structures
 *                    @ref i2c_config
 * @param   ip      - interrupt priority 0..3
 * @param   callback- pointer to I2C_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define I2C_Init(module,cfg,ip,callback)        module##_Init(cfg,ip,callback)

/***************************************************************************//*!
 * @brief   I2C write data to register function.
 * @param   module    I2C0,I2C1
 * @param   Adr       register address
 * @param   Data      data to be written to register
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define I2C_WriteReg(module,Adr,Data)           module##_WriteReg(cfg,Adr,Data)

/***************************************************************************//*!
 * @brief   I2C read data from register function.
 * @param   module    I2C0,I2C1
 * @param   Adr       register address
 * @return  uint8     read data
 * @note    Implemented as function call.
 ******************************************************************************/
#define I2C_ReadReg(module,Adr)                 (uint8)module##_ReadReg(cfg,Adr)

/***************************************************************************//*!
 * @brief   I2C cycle write data function.
 * @param   module    I2C0,I2C1
 * @param   Data      data to be written to register
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define I2C_CycleWrite(module,Data)           module##_CycleWrite(Data)

/***************************************************************************//*!
 * @brief   I2C cycle read data function.
 * @param   module    I2C0,I2C1
 * @param   ack - TRUE or FAULSE
 * @return  I2C data
 * @note    Implemented as function call.
 ******************************************************************************/
#define I2C_CycleRead(module,ack)           module##_CycleRead(ack)

/*! @} End of i2c_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern void I2C0_Init (tI2C i2c, uint8 ip, I2C_CALLBACK pCallback);
extern void I2C1_Init (tI2C i2c, uint8 ip, I2C_CALLBACK pCallback);

extern void I2C0_WriteByte(uint8 u8DevAdr, uint8 u8RegAdr, uint8 u8Data);
extern void I2C1_WriteByte(uint8 u8DevAdr, uint8 u8RegAdr, uint8 u8Data);

extern uint8 I2C0_ReadByte(uint8 u8DevAdr, uint8 u8RegAdr);
extern uint8 I2C1_ReadByte(uint8 u8DevAdr, uint8 u8RegAdr);

extern void I2C0_WriteMultiBytes(uint8 u8DevAdr, uint8 u8RegAdr, uint8 *array, uint8 length);
extern void I2C1_WriteMultiBytes(uint8 u8DevAdr, uint8 u8RegAdr, uint8 *array, uint8 length);

extern void I2C0_ReadMultiBytes(uint8 u8DevAdr, uint8 u8RegAdr, uint8 *array, uint8 length);
extern void I2C1_ReadMultiBytes(uint8 u8DevAdr, uint8 u8RegAdr, uint8 *array, uint8 length);

extern void I2C0_CycleWrite(uint8 u8Data);
extern void I2C1_CycleWrite(uint8 u8Data);

extern uint8 I2C0_CycleRead(uint8 u8Ack);
extern uint8 I2C1_CycleRead(uint8 u8Ack);
#endif /* __I2C_H */
