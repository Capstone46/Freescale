/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      dac.h
 * @version   1.0.4.0
 * @date      Jan-22-2013
 * @brief     Digital to Analog converter (DAC) driver header file.
 *
 * Revision History:
 *  1.	15/01/2013   B34185   Initially written for Kinetis L
 *  2.	26/03/2014   B34185   dac callback re-defined
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup dac_example0
 * @{
 * @par       Source code:
 * @include   dac0_test\dac0_test.c
 * @par       Appconfig.h:
 * @include   dac0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of dac_example0                                                    */
#ifndef __DAC_H
#define __DAC_H 

/******************************************************************************
 * definition configuration structure                                         *
 ******************************************************************************/
typedef struct { uint8 SR, C0, C1, C2; } tDAC;

/******************************************************************************
* DAC default configurations used by DAC_init() function
*
*//*! @addtogroup dac_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
  * @brief DAC setting:
  * - disabled mode
  *****************************************************************************/
#define DAC_DISABLE_CONFIG                                                    \
(tDAC){                                                                       \
/* SR     */  CLR(DAC_SR_DACBFRPTF_MASK)|CLR(DAC_SR_DACBFRPBF_MASK),          \
/* C0     */  CLR(DAC_C0_DACEN_MASK)|CLR(DAC_C0_DACRFS_MASK)|                 \
              CLR(DAC_C0_DACTRGSEL_MASK)|CLR(DAC_C0_DACSWTRG_MASK)|           \
              CLR(DAC_C0_LPEN_MASK)|CLR(DAC_C0_DACBTIEN_MASK)|                \
              CLR(DAC_C0_DACBBIEN_MASK),                                      \
/* C1     */  CLR(DAC_C1_DMAEN_MASK)|CLR(DAC_C1_DACBFMD_MASK)|                \
              CLR(DAC_C1_DACBFEN_MASK),                                       \
/* C2     */  CLR(DAC_C2_DACBFRP_MASK)|CLR(DAC_C2_DACBFUP_MASK),              \
}

/**************************************************************************/ /*!
  * @brief DAC setting:
  * - DAC buffer is not enabled
  * - Voltage REF1 selected (VREFH)
  * - SW trigger selected
  * - high power enabled
  *****************************************************************************/
#define DAC_NOBUFFER_REF1_SWTRG_HP_CONFIG                                     \
(tDAC){                                                                       \
/* SR     */  CLR(DAC_SR_DACBFRPTF_MASK)|CLR(DAC_SR_DACBFRPBF_MASK),          \
/* C0     */  SET(DAC_C0_DACEN_MASK)|CLR(DAC_C0_DACRFS_MASK)|                 \
              SET(DAC_C0_DACTRGSEL_MASK)|CLR(DAC_C0_DACSWTRG_MASK)|           \
              CLR(DAC_C0_LPEN_MASK)|CLR(DAC_C0_DACBTIEN_MASK)|                \
              CLR(DAC_C0_DACBBIEN_MASK),                                      \
/* C1     */  CLR(DAC_C1_DMAEN_MASK)|CLR(DAC_C1_DACBFMD_MASK)|                \
              CLR(DAC_C1_DACBFEN_MASK),                                       \
/* C2     */  CLR(DAC_C2_DACBFRP_MASK)|CLR(DAC_C2_DACBFUP_MASK),              \
}

/**************************************************************************/ /*!
  * @brief DAC setting:
  * - DAC buffer is not enabled
  * - Voltage REF1 selected (VREFH)
  * - HW trigger selected
  * - high power enabled
  *****************************************************************************/
#define DAC_NOBUFFER_REF1_HWTRG_HP_CONFIG                                     \
(tDAC){                                                                       \
/* SR     */  CLR(DAC_SR_DACBFRPTF_MASK)|CLR(DAC_SR_DACBFRPBF_MASK),          \
/* C0     */  SET(DAC_C0_DACEN_MASK)|CLR(DAC_C0_DACRFS_MASK)|                 \
              CLR(DAC_C0_DACTRGSEL_MASK)|CLR(DAC_C0_DACSWTRG_MASK)|           \
              CLR(DAC_C0_LPEN_MASK)|CLR(DAC_C0_DACBTIEN_MASK)|                \
              CLR(DAC_C0_DACBBIEN_MASK),                                      \
/* C1     */  CLR(DAC_C1_DMAEN_MASK)|SET(DAC_C1_DACBFMD(0x0))|                \
              CLR(DAC_C1_DACBFEN_MASK),                                       \
/* C2     */  CLR(DAC_C2_DACBFRP_MASK)|CLR(DAC_C2_DACBFUP_MASK),              \
}

/**************************************************************************/ /*!
  * @brief DAC setting:
  * - DAC buffer is not enabled
  * - Voltage REF2 selected (VDDA)
  * - SW trigger selected
  * - high power enabled
  *****************************************************************************/
#define DAC_NOBUFFER_REF2_SWTRG_HP_CONFIG                                     \
(tDAC){                                                                       \
/* SR     */  CLR(DAC_SR_DACBFRPTF_MASK)|CLR(DAC_SR_DACBFRPBF_MASK),          \
/* C0     */  SET(DAC_C0_DACEN_MASK)|SET(DAC_C0_DACRFS_MASK)|                 \
              SET(DAC_C0_DACTRGSEL_MASK)|CLR(DAC_C0_DACSWTRG_MASK)|           \
              CLR(DAC_C0_LPEN_MASK)|CLR(DAC_C0_DACBTIEN_MASK)|                \
              CLR(DAC_C0_DACBBIEN_MASK),                                      \
/* C1     */  CLR(DAC_C1_DMAEN_MASK)|CLR(DAC_C1_DACBFMD_MASK)|                \
              CLR(DAC_C1_DACBFEN_MASK),                                       \
/* C2     */  CLR(DAC_C2_DACBFRP_MASK)|CLR(DAC_C2_DACBFUP_MASK),              \
}

/**************************************************************************/ /*!
  * @brief DAC setting:
  * - DAC buffer is not enabled
  * - Voltage REF1 selected (VREFH)
  * - SW trigger selected
  * - low power enabled
  *****************************************************************************/
#define DAC_NOBUFFER_REF1_SWTRG_LP_CONFIG                                     \
(tDAC){                                                                       \
/* SR     */  CLR(DAC_SR_DACBFRPTF_MASK)|CLR(DAC_SR_DACBFRPBF_MASK),          \
/* C0     */  SET(DAC_C0_DACEN_MASK)|CLR(DAC_C0_DACRFS_MASK)|                 \
              SET(DAC_C0_DACTRGSEL_MASK)|CLR(DAC_C0_DACSWTRG_MASK)|           \
              SET(DAC_C0_LPEN_MASK)|CLR(DAC_C0_DACBTIEN_MASK)|                \
              CLR(DAC_C0_DACBBIEN_MASK),                                      \
/* C1     */  CLR(DAC_C1_DMAEN_MASK)|CLR(DAC_C1_DACBFMD_MASK)|                \
              CLR(DAC_C1_DACBFEN_MASK),                                       \
/* C2     */  CLR(DAC_C2_DACBFRP_MASK)|CLR(DAC_C2_DACBFUP_MASK),              \
}

/**************************************************************************/ /*!
  * @brief DAC setting:
  * - DAC buffer is enabled (support only two word data buffer)
  * - Voltage REF1 selected (VREFH)
  * - SW trigger selected
  * - high power enabled
  * - Normal buffer work mode selected
  * - value of upper limit of the DAC buffer set to 1 (max). 
  *****************************************************************************/
#define DAC_BUFFER_NORMAL_REF1_SWTRG_HP_CONFIG                                \
(tDAC){                                                                       \
/* SR     */  CLR(DAC_SR_DACBFRPTF_MASK)|CLR(DAC_SR_DACBFRPBF_MASK),          \
/* C0     */  SET(DAC_C0_DACEN_MASK)|CLR(DAC_C0_DACRFS_MASK)|                 \
              SET(DAC_C0_DACTRGSEL_MASK)|CLR(DAC_C0_DACSWTRG_MASK)|           \
              CLR(DAC_C0_LPEN_MASK)|CLR(DAC_C0_DACBTIEN_MASK)|                \
              CLR(DAC_C0_DACBBIEN_MASK),                                      \
/* C1     */  CLR(DAC_C1_DMAEN_MASK)|SET(DAC_C1_DACBFMD(0x0))|                \
              SET(DAC_C1_DACBFEN_MASK),                                       \
/* C2     */  CLR(DAC_C2_DACBFRP_MASK)|SET(DAC_C2_DACBFUP_MASK),              \
}

/**************************************************************************/ /*!
  * @brief DAC setting:
  * - DAC buffer is enabled (support only two word data buffer)
  * - Voltage REF1 selected (VREFH)
  * - SW trigger selected
  * - high power enabled
  * - Buffer read poiter top interrupt enabled
  * - Normal buffer work mode selected
  * - value of upper limit of the DAC buffer set to 1 (max). 
  *****************************************************************************/
#define DAC_BUFFER_NORMAL_REF1_SWTRG_HP_IRQTOP_CONFIG                         \
(tDAC){                                                                       \
/* SR     */  CLR(DAC_SR_DACBFRPTF_MASK)|CLR(DAC_SR_DACBFRPBF_MASK),          \
/* C0     */  SET(DAC_C0_DACEN_MASK)|CLR(DAC_C0_DACRFS_MASK)|                 \
              SET(DAC_C0_DACTRGSEL_MASK)|CLR(DAC_C0_DACSWTRG_MASK)|           \
              CLR(DAC_C0_LPEN_MASK)|SET(DAC_C0_DACBTIEN_MASK)|                \
              CLR(DAC_C0_DACBBIEN_MASK),                                      \
/* C1     */  CLR(DAC_C1_DMAEN_MASK)|SET(DAC_C1_DACBFMD(0x0)|                 \
              SET(DAC_C1_DACBFEN_MASK),                                       \
/* C2     */  CLR(DAC_C2_DACBFRP_MASK)|SET(DAC_C2_DACBFUP_MASK),              \
}

/**************************************************************************/ /*!
  * @brief DAC setting:
  * - DAC buffer is enabled (support only two word data buffer)
  * - Voltage REF1 selected (VREFH)
  * - SW trigger selected
  * - high power enabled
  * - Buffer read poiter top interrupt enabled
  * - One-Time Scan mode of buffer selected
  * - value of upper limit of the DAC buffer set to 1 (max). 
  *****************************************************************************/
#define DAC_BUFFER_ONETIMESCAN_REF1_SWTRG_HP_IRQTOP_CONFIG                    \
(tDAC){                                                                       \
/* SR     */  CLR(DAC_SR_DACBFRPTF_MASK)|CLR(DAC_SR_DACBFRPBF_MASK),          \
/* C0     */  SET(DAC_C0_DACEN_MASK)|CLR(DAC_C0_DACRFS_MASK)|                 \
              SET(DAC_C0_DACTRGSEL_MASK)|CLR(DAC_C0_DACSWTRG_MASK)|           \
              CLR(DAC_C0_LPEN_MASK)|SET(DAC_C0_DACBTIEN_MASK)|                \
              CLR(DAC_C0_DACBBIEN_MASK),                                      \
/* C1     */  CLR(DAC_C1_DMAEN_MASK)|SET(DAC_C1_DACBFMD(0x2))|                \
              SET(DAC_C1_DACBFEN_MASK),                                       \
/* C2     */  CLR(DAC_C2_DACBFRP_MASK)|SET(DAC_C2_DACBFUP_MASK),              \
}

/**************************************************************************/ /*!
  * @brief DAC setting:
  * - DAC buffer is enabled (support only two word data buffer)
  * - Voltage REF1 selected (VREFH)
  * - HW trigger selected
  * - high power enabled
  * - Normal buffer work mode selected
  * - no interrupt
  * - value of upper limit of the DAC buffer set to 1 (max). 
  *****************************************************************************/
#define DAC_BUFFER_NORMAL_REF1_HWTRG_HP_CONFIG                                \
(tDAC){                                                                       \
/* SR     */  CLR(DAC_SR_DACBFRPTF_MASK)|CLR(DAC_SR_DACBFRPBF_MASK),          \
/* C0     */  SET(DAC_C0_DACEN_MASK)|CLR(DAC_C0_DACRFS_MASK)|                 \
              CLR(DAC_C0_DACTRGSEL_MASK)|CLR(DAC_C0_DACSWTRG_MASK)|           \
              CLR(DAC_C0_LPEN_MASK)|CLR(DAC_C0_DACBTIEN_MASK)|                \
              CLR(DAC_C0_DACBBIEN_MASK),                                      \
/* C1     */  CLR(DAC_C1_DMAEN_MASK)|SET(DAC_C1_DACBFMD(0x0))|                \
              SET(DAC_C1_DACBFEN_MASK),                                       \
/* C2     */  CLR(DAC_C2_DACBFRP_MASK)|SET(DAC_C2_DACBFUP_MASK),              \
}

/**************************************************************************/ /*!
  * @brief DAC setting:
  * - DAC buffer is enabled (support only two word data buffer)
  * - Voltage REF1 selected (VREFH)
  * - HW trigger selected
  * - high power enabled
  * - One-Time Scan mode of buffer selected
  * - no interrupt
  * - value of upper limit of the DAC buffer set to 1 (max). 
  *****************************************************************************/
#define DAC_BUFFER_ONETIMESCAN_REF1_HWTRG_HP_CONFIG                           \
(tDAC){                                                                       \
/* SR     */  CLR(DAC_SR_DACBFRPTF_MASK)|CLR(DAC_SR_DACBFRPBF_MASK),          \
/* C0     */  SET(DAC_C0_DACEN_MASK)|CLR(DAC_C0_DACRFS_MASK)|                 \
              CLR(DAC_C0_DACTRGSEL_MASK)|CLR(DAC_C0_DACSWTRG_MASK)|           \
              CLR(DAC_C0_LPEN_MASK)|CLR(DAC_C0_DACBTIEN_MASK)|                \
              CLR(DAC_C0_DACBBIEN_MASK),                                      \
/* C1     */  CLR(DAC_C1_DMAEN_MASK)|SET(DAC_C1_DACBFMD(0x2))|                \
              SET(DAC_C1_DACBFEN_MASK),                                       \
/* C2     */  CLR(DAC_C2_DACBFRP_MASK)|SET(DAC_C2_DACBFUP_MASK),              \
}
                                         
/**************************************************************************/ /*!
  * @brief DAC setting:
  * - DAC buffer is enabled (support only two word data buffer)
  * - Voltage REF1 selected (VREFH)
  * - HW trigger selected
  * - high power enabled
  * - FIFO mode of buffer selected
  * - no interrupt
  * - value of upper limit of the DAC buffer set to 1 (max). 
  *****************************************************************************/
#define DAC_BUFFER_FIFO_REF1_HWTRG_HP_CONFIG                                  \
(tDAC){                                                                       \
/* SR     */  CLR(DAC_SR_DACBFRPTF_MASK)|CLR(DAC_SR_DACBFRPBF_MASK),          \
/* C0     */  SET(DAC_C0_DACEN_MASK)|CLR(DAC_C0_DACRFS_MASK)|                 \
              CLR(DAC_C0_DACTRGSEL_MASK)|CLR(DAC_C0_DACSWTRG_MASK)|           \
              CLR(DAC_C0_LPEN_MASK)|CLR(DAC_C0_DACBTIEN_MASK)|                \
              CLR(DAC_C0_DACBBIEN_MASK),                                      \
/* C1     */  CLR(DAC_C1_DMAEN_MASK)|SET(DAC_C1_DACBFMD(0x3))|                \
              SET(DAC_C1_DACBFEN_MASK),                                       \
/* C2     */  CLR(DAC_C2_DACBFRP_MASK)|SET(DAC_C2_DACBFUP_MASK),              \
}

/*! @} End of dac_config                                                      */

/******************************************************************************
* DAC callback used by DAC_init() function
*
*//*! @addtogroup dac_callback
* @{
*******************************************************************************/
/*! @brief DAC_CALLBACK type declaration                                      */
typedef enum 
{
    DAC_TOP_CALLBACK=1,         ///< read pointer top possition
    DAC_BOTTOM_CALLBACK=2,      ///< read pointer bottom possition
} DAC_CALLBACK_TYPE;

/*! DAC_CALLBACK function declaration                                         */
typedef void (*DAC_CALLBACK)(DAC_CALLBACK_TYPE type);
/*! @} End of dac_callback                                                    */

/******************************************************************************
* DAC function and macro definitions
*
*//*! @addtogroup dac_macro
* @{
*******************************************************************************/
#define DAC0_GetData()                  (((uint16)DAC0_DAT0H<<8)|(uint16)DAC0_DAT0L)
/***************************************************************************//*!
 * @brief   Get data of DAC data registers.
 * @param   module  - DAC0
 * @return  16-bit data value of DAC output
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_GetData(module)             module##_GetData()

#define DAC0_SetData(data)              *(uint16*)&DAC0_DAT0L = (uint16)data;
/***************************************************************************//*!
 * @brief   Set data registers.
 * @param   module  - DAC0
 * @param   data  - number from 0 to 4093 (12-bit data expected)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_SetData(module,data)        module##_SetData(data)

#define DAC0_Buff0_Data(data)           {DAC0_DAT0L = (uint8)(0x00FF&data);    \
                                         DAC0_DAT0H = (uint8)((0xFF00&data)>>8);}//*((uint16*)&DAC0_DAT0L) = (uint16)data;
#define DAC0_Buff1_Data(data)           {DAC0_DAT1L = (uint8)(0x00FF&data);     \
                                         DAC0_DAT1H = (uint8)((0xFF00&data)>>8);}//*((uint16*)&DAC0_DAT1L) = (uint16)data;
/***************************************************************************//*!
 * @brief   Set specific data buffer value.
 * @param   module  - DAC0
 * @param   buff  - number from 0 to 1
 * @param   data  - number from 0 to 4093 (12-bit data expected)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_SetBufferData(module,buff,data)    module##_Buff##buff##_Data(data)

#define DAC0_Enable()                   DAC0_C0 |= DAC_C0_DACEN_MASK
/***************************************************************************//*!
 * @brief   Enable DAC module.
 * @param   module  - DAC0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_Enable(module)              module##_Enable()

#define DAC0_Disable()                  DAC0_C0 &= ~DAC_C0_DACEN_MASK
/***************************************************************************//*!
 * @brief   Disable DAC module.
 * @param   module  - DAC0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_Disable(module)             module##_Disable()

#define DAC0_Vref_VREFH()               DAC0_C0 &= ~DAC_C0_DACRFS_MASK
#define DAC0_Vref_VDDA()                DAC0_C0 |= DAC_C0_DACRFS_MASK
/***************************************************************************//*!
 * @brief   Select voltage reference for DAC module.
 * @param   module  - DAC0
 * @param   vref  - VREFH or VDDA
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_Vref(module,vref)           module##_Vref_##vref##()

#define DAC0_SelTrig_SW()               DAC0_C0 |= DAC_C0_DACTRGSEL_MASK
#define DAC0_SelTrig_HW()               DAC0_C0 &= ~DAC_C0_DACTRGSEL_MASK
/***************************************************************************//*!
 * @brief   Select between SW and HW triggers.
 * @param   module  - DAC0
 * @param   trig  - SW or HW
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_SelTrig(module,trig)        module##_SelTrig_##trig##()

#define DAC0_SwTrigger()                DAC0_C0 |= DAC_C0_DACSWTRG_MASK
/***************************************************************************//*!
 * @brief   Generate SW trigger.
 * @param   module  - DAC0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_SwTrigger(module)           module##_SwTrigger()

#define DAC0_PowerControl_LP()          DAC0_C0 |= DAC_C0_LPEN_MASK
#define DAC0_PowerControl_HP()          DAC0_C0 &= ~DAC_C0_LPEN_MASK
/***************************************************************************//*!
 * @brief   Select between high and low power modes of DAC.
 * @param   module  - DAC0
 * @param   pmode  - HP (high power) or LP (low power)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_PowerControl(module,pmode)  module##_PowerControl_##pmode##()

#define DAC0_BufferMode_NORMAL()        DAC0_C1 &= ~DAC_C1_DACBFMD_MASK 
#define DAC0_BufferMode_ONE_TIME_SCAN() DAC0_C1 = DAC_C1_DACBFMD_MASK
/***************************************************************************//*!
 * @brief   Select between normal and one-time scan buffer work mode of DAC.
 * @param   module  - DAC0
 * @param   bmode  - NORMAL or ONE_TIME_SCAN
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_BufferMode(module,bmode)    module##_BufferMode_##bmode##()

#define DAC0_BufferEnable()             DAC0_C1 |= DAC_C1_DACBFEN_MASK
/***************************************************************************//*!
 * @brief   Enable DAC buffer.
 * @param   module  - DAC0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_BufferEnable(module)        module##_BufferEnable()

#define DAC0_BufferDisable()            DAC0_C1 &= ~DAC_C1_DACBFEN_MASK
/***************************************************************************//*!
 * @brief   Enable DAC buffer.
 * @param   module  - DAC0
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_BufferDisable(module)       module##_BufferDisable()

#define DAC0_GetBuffPtr()               ((DAC0_C2&0xF0)>>4)
/***************************************************************************//*!
 * @brief   Get current position of buffer pointer.
 * @param   module  - DAC0
 * @return  DAC buffer current position value
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_GetBuffPtr(module)          module##_GetBuffPtr()

//#define DAC0_SetBuffPtr(bval)           DAC0_C2 = (bval<<4)|(DAC0_C2&0x0F)
///***************************************************************************//*!
// * @brief   Set position of buffer pointer(supports only two words data buffer).
// * @param   module  - DAC0
// * @param   bval  - 0 or 1 (cannot exceed upper buffer limit)
// * @note    Implemented as inlined macro.
// ******************************************************************************/
//#define DAC_SetBuffPtr(module,bval)     module##_SetBuffPtr(bval)

#define DAC0_SetBuffLimit(bval)         DAC0_C2 =  (bval)|(DAC0_C2&0xF0)
/***************************************************************************//*!
 * @brief   Set upper limit of buffer (just two buffer values in this case).
 * @param   module  - DAC0
 * @param   bval  - 0 or 1 (for KL25)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DAC_SetBuffLimit(module,bval)   module##_SetBuffLimit(bval)

/***************************************************************************//*!
 * @brief   DAC initialization function.
 * @details This function initializes selected DAC module
 * @param   module  - DAC0
 * @param   cfg     - Use one of the configuration structures @ref dac_config
 * @param   data    - 11-bit initialiation value of DAC output 
 * @param   ip        Interrupt priority 0..3
 * @param   callback  Pointer to @ref DAC_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define DAC_Init(module,cfg,data,ip,callback) module##_Init(cfg,data,ip,callback)
/*! @} End of dac_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/    
extern void DAC0_Init (tDAC dac, uint16 data, uint8 ip, DAC_CALLBACK pCallback);

#endif /* __DAC_H */
