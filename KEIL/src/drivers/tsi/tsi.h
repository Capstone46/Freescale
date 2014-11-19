/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      tsi.h
 * @version   1.0.5.0
 * @date      Mar-8-2013
 * @brief     Touch sensing input (TSI) driver source code.
 *
 * Revision History:
 *  1.	28/02/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup tsi_example0
 * @{
 * @par       Source code:
 * @include   tsi0_test\tsi0_test.c
 * @par       Appconfig.h:
 * @include   tsi0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of tsi_example0                                                    */
#ifndef __TSI_H
#define __TSI_H 
 
/******************************************************************************
 * TSI calibration data structure definition                                  *
 ******************************************************************************/
typedef struct { uint32 THRESH[16], THRESL[16]; } tTSI_CALIB;

/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct { uint32 GENCS, DATA;  } tTSI;

/******************************************************************************
* TSI channel list to be used by TSI_Init() function
*
*//*! @addtogroup tsi_channels
* @{
*******************************************************************************/
#define	TSI_CH0		(uint32)0x0	///< TSI channel 0
#define	TSI_CH1		(uint32)0x1	///< TSI channel 1
#define	TSI_CH2		(uint32)0x2	///< TSI channel 2
#define	TSI_CH3		(uint32)0x3	///< TSI channel 3
#define	TSI_CH4		(uint32)0x4	///< TSI channel 4
#define	TSI_CH5		(uint32)0x5	///< TSI channel 5
#define	TSI_CH6		(uint32)0x6	///< TSI channel 6
#define	TSI_CH7		(uint32)0x7	///< TSI channel 7
#define	TSI_CH8		(uint32)0x8	///< TSI channel 8
#define	TSI_CH9		(uint32)0x9	///< TSI channel 9
#define	TSI_CH10	(uint32)0xA	///< TSI channel 10
#define	TSI_CH11	(uint32)0xB	///< TSI channel 11
#define	TSI_CH12	(uint32)0xC	///< TSI channel 12
#define	TSI_CH13	(uint32)0xD	///< TSI channel 13
#define	TSI_CH14	(uint32)0xE	///< TSI channel 14
#define	TSI_CH15	(uint32)0xF	///< TSI channel 15
/*! @} End of tsi_config                                                      */

/******************************************************************************
* These macros indicate the prescaler of the output of electrode oscillator to 
* be used by TSI_Init() function
*
*//*! @addtogroup tsi_prescalers
* @{
*******************************************************************************/
#define	EOF_DIV_BY_1	(uint32)0x0	///< Electrode Oscillator Frequency divided by 1
#define	EOF_DIV_BY_2	(uint32)0x1	///< Electrode Oscillator Frequency divided by 2
#define	EOF_DIV_BY_4	(uint32)0x2	///< Electrode Oscillator Frequency divided by 4
#define	EOF_DIV_BY_8	(uint32)0x3	///< Electrode Oscillator Frequency divided by 8
#define	EOF_DIV_BY_16	(uint32)0x4	///< Electrode Oscillator Frequency divided by 16
#define	EOF_DIV_BY_32	(uint32)0x5	///< Electrode Oscillator Frequency divided by 32
#define	EOF_DIV_BY_64	(uint32)0x6	///< Electrode Oscillator Frequency divided by 64
#define	EOF_DIV_BY_128	(uint32)0x7	///< Electrode Oscillator Frequency divided by 128
/*! @} End of tsi_prescalers                                                  */

/******************************************************************************
* These macros indicates number of scans performed for each trigger.
*
*//*! @addtogroup tsi_numscans
* @{
*******************************************************************************/
#define	SCAN_01X        (uint32)0x0	///< perform scan once per electrode
#define	SCAN_02X        (uint32)0x1	///< perform scan twice per electrode
#define	SCAN_03X        (uint32)0x2	///< perform scan 3 times per electrode
#define	SCAN_04X        (uint32)0x3	///< perform scan 4 times per electrode
#define	SCAN_05X        (uint32)0x4	///< perform scan 5 times per electrode
#define	SCAN_06X        (uint32)0x5	///< perform scan 6 times per electrode
#define	SCAN_07X        (uint32)0x6	///< perform scan 7 times per electrode
#define	SCAN_08X        (uint32)0x7	///< perform scan 8 times per electrode
#define	SCAN_09X        (uint32)0x8	///< perform scan 9 times per electrode
#define	SCAN_10X        (uint32)0x9	///< perform scan 10 times per electrode
#define	SCAN_11X        (uint32)0xA	///< perform scan 11 times per electrode
#define	SCAN_12X        (uint32)0xB	///< perform scan 12 times per electrode
#define	SCAN_13X        (uint32)0xC	///< perform scan 13 times per electrode
#define	SCAN_14X        (uint32)0xD	///< perform scan 14 times per electrode
#define	SCAN_15X        (uint32)0xE	///< perform scan 15 times per electrode
#define	SCAN_16X        (uint32)0xF	///< perform scan 16 times per electrode
#define	SCAN_17X        (uint32)0x10	///< perform scan 17 times per electrode
#define	SCAN_18X        (uint32)0x11	///< perform scan 18 times per electrode
#define	SCAN_19X        (uint32)0x12	///< perform scan 19 times per electrode
#define	SCAN_20X        (uint32)0x13	///< perform scan 20 times per electrode
#define	SCAN_21X        (uint32)0x14	///< perform scan 21 times per electrode
#define	SCAN_22X        (uint32)0x15	///< perform scan 22 times per electrode
#define	SCAN_23X        (uint32)0x16	///< perform scan 23 times per electrode
#define	SCAN_24X        (uint32)0x17	///< perform scan 24 times per electrode
#define	SCAN_25X        (uint32)0x18	///< perform scan 25 times per electrode
#define	SCAN_26X        (uint32)0x19	///< perform scan 26 times per electrode
#define	SCAN_27X        (uint32)0x1A	///< perform scan 27 times per electrode
#define	SCAN_28X        (uint32)0x1B	///< perform scan 28 times per electrode
#define	SCAN_29X        (uint32)0x1C	///< perform scan 29 times per electrode
#define	SCAN_30X        (uint32)0x1D	///< perform scan 30 times per electrode
#define	SCAN_31X        (uint32)0x1E	///< perform scan 31 times per electrode
#define	SCAN_32X        (uint32)0x1F	///< perform scan 32 times per electrode
/*! @} End of tsi_numscans                                                    */

/******************************************************************************
* TSI charging current for oscilators used in TSI_Init() function
*
*//*! @addtogroup tsi_chargecurr
* @{
*******************************************************************************/
#define	TSI_500nA       (uint32)0x0	///< TSI 500nA oscilator charging current
#define	TSI_1uA		(uint32)0x1	///< TSI 1uA oscilator charging current
#define	TSI_2uA		(uint32)0x2	///< TSI 2uA oscilator charging current
#define	TSI_4uA		(uint32)0x3	///< TSI 4uA oscilator charging current
#define	TSI_8uA		(uint32)0x4	///< TSI 8uA oscilator charging current
#define	TSI_16uA        (uint32)0x5	///< TSI 16uA oscilator charging current
#define	TSI_32uA	(uint32)0x6	///< TSI 32uA oscilator charging current
#define	TSI_64uA	(uint32)0x7	///< TSI 64uA oscilator charging current
/*! @} End of tsi_chargecurr                                                  */

/******************************************************************************
* These macros indicate the oscillator's voltage rails as below used in 
* TSI_Init() function
*
*//*! @addtogroup tsi_deltavoltage
* @{
*******************************************************************************/
#define	DV_1_03V        (uint32)0x0	///< DV = 1.03 V; VP = 1.33 V; Vm = 0.30 V
#define	DV_0_73V	(uint32)0x1	///< DV = 0.73 V; VP = 1.18 V; Vm = 0.45 V
#define	DV_0_43V	(uint32)0x2	///< DV = 0.43 V; VP = 1.03 V; Vm = 0.60 V
#define	DV_0_29V	(uint32)0x3	///< DV = 0.29 V; VP = 0.95 V; Vm = 0.67 V
/*! @} End of tsi_deltavoltage                                                 */

/******************************************************************************
* These macros specifies sensitivity factors used in TSI_Calib () function to
* more precisely configure treshhold values (considering HW - touch electrodes
* design). 
*
*//*! @addtogroup tsi_sensitivity
* @{
*******************************************************************************/
#define	TSI_VERY_LOW_SENSITIVITY        (uint16)0x0	///< use 100% extra treshhold range e.g. calculated THRESH = 500, TRESL = 450 -> use THRESH = 1000, TRESL = 0 
#define	TSI_LOW_SENSITIVITY	        (uint16)0x1	///< use 50% extra treshhold range
#define	TSI_MIDDLE_SENSITIVITY	        (uint16)0x2	///< use 25% extra treshhold range
#define	TSI_HIGH_SENSITIVITY	        (uint16)0x3	///< use 12.5% extra treshhold range
#define	TSI_VERY_HIGH_SENSITIVITY	(uint16)0x4	///< use 6.25% extra treshhold range
#define	TSI_ULTRA_HIGH_SENSITIVITY	(uint16)0x20	///< use 0% extra treshhold range
/*! @} End of tsi_sensitivity                                                 */

/******************************************************************************
* These macros specifies TSI analog modes setup used by TSI_Mode() function. 
*
*//*! @addtogroup tsi_modes
* @{
*******************************************************************************/
#define	TSI_CAPACITIVE_SENSING          (uint16)0x00	///< TSI in capacitive sensing(non-noise detection) mode. 
#define	TSI_NON_NOISE_DETECT            (uint16)0x00	///< TSI in capacitive sensing(non-noise detection) mode. 
#define	TSI_NOISE_DETECT_FREQ_LIM_DIS   (uint16)0x04	///< TSI analog to work in single threshold noise detection mode and the frequency limitation circuit is disabled
#define	TSI_NOISE_DETECT_FREQ_LIM_EN    (uint16)0x08	///< Set TSI analog to work in single threshold noise detection mode and the frequency limitation circuit is enabled to work in higher frequencies operations.
#define	TSI_AUTO_NOISE_DETECT	        (uint16)0x0C	///< Set TSI analog to work in automatic noise detection mode.
/*! @} End of tsi_modes                                                       */

/******************************************************************************
* TSI configurations used by TSI_Init() function
*
*//*! @addtogroup tsi_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief Default TSI configuration.
 *****************************************************************************/
#define TSI_DISABLE_CONFIG                                                     \
(tTSI){                                                                        \
/* GENCS  */  SET(TSI_GENCS_OUTRGF_MASK)|CLR(TSI_GENCS_ESOR_MASK)|             \
              SET(TSI_GENCS_MODE(0x0))|SET(TSI_GENCS_REFCHRG(0x0))|            \
              SET(TSI_GENCS_DVOLT(0x0))|SET(TSI_GENCS_EXTCHRG(0x0))|           \
              SET(TSI_GENCS_PS(0x0))|SET(TSI_GENCS_NSCN(0x00))| 	       \
              CLR(TSI_GENCS_TSIEN_MASK)|CLR(TSI_GENCS_TSIIEN_MASK)|	       \
              CLR(TSI_GENCS_STPE_MASK)|CLR(TSI_GENCS_STM_MASK)|		       \
              SET(TSI_GENCS_EOSF_MASK)|CLR(TSI_GENCS_CURSW_MASK),	       \
/* DATA  */   SET(TSI_DATA_TSICH(0x0))|CLR(TSI_DATA_DMAEN_MASK)| 	       \
              CLR(TSI_DATA_SWTS_MASK),					       \
}

/**************************************************************************/ /*!
 * @brief TSI working in capacitive sensing mode with end of scan IRQ enabled
 *        and selectable prescaler, number of scans, charging currents and delta
 *        voltage.
 * @param   ch  - @ref tsi_channels
 * @param   ps  - @ref tsi_prescalers
 * @param   nos  - @ref tsi_numscans
 * @param   refcurr  - @ref tsi_chargecurr
 * @param   extcurr  - @ref tsi_chargecurr
 * @param   dv  - @ref tsi_deltavoltage
 *****************************************************************************/
#define TSI_CAP_SENSE_MODE_EOS_IRQ_CONFIG(ch,ps,nos,refcurr,extcurr,dv)        \
(tTSI){                                                                        \
/* GENCS */   SET(TSI_GENCS_OUTRGF_MASK)|SET(TSI_GENCS_ESOR_MASK)|             \
              SET(TSI_GENCS_MODE(0x0))|SET(TSI_GENCS_REFCHRG(refcurr))|        \
              SET(TSI_GENCS_DVOLT(dv))|SET(TSI_GENCS_EXTCHRG(extcurr))|        \
              SET(TSI_GENCS_PS(ps))|SET(TSI_GENCS_NSCN(nos))| 	               \
              SET(TSI_GENCS_TSIEN_MASK)|SET(TSI_GENCS_TSIIEN_MASK)|	       \
              CLR(TSI_GENCS_STPE_MASK)|CLR(TSI_GENCS_STM_MASK)|		       \
              SET(TSI_GENCS_EOSF_MASK)|CLR(TSI_GENCS_CURSW_MASK),	       \
/* DATA  */   SET(TSI_DATA_TSICH(ch))|CLR(TSI_DATA_DMAEN_MASK)| 	       \
              CLR(TSI_DATA_SWTS_MASK),					       \
}

/**************************************************************************/ /*!
 * @brief TSI working in capacitive sensing mode with out of range scan IRQ 
 *        enabled and selectable prescaler, number of scans, charging currents 
 *        and delta voltage. Treshhold range is selectable.
 * @param   ch  - @ref tsi_channels
 * @param   ps  - @ref tsi_prescalers
 * @param   nos  - @ref tsi_numscans
 * @param   refcurr  - @ref tsi_chargecurr
 * @param   extcurr  - @ref tsi_chargecurr
 * @param   dv  - @ref tsi_deltavoltage
 *****************************************************************************/
#define TSI_CAP_SENSE_MODE_OUTRG_IRQ_CONFIG(ch,ps,nos,refcurr,extcurr,dv)      \
(tTSI){                                                                        \
/* GENCS */   SET(TSI_GENCS_OUTRGF_MASK)|CLR(TSI_GENCS_ESOR_MASK)|             \
              SET(TSI_GENCS_MODE(0x0))|SET(TSI_GENCS_REFCHRG(refcurr))|        \
              SET(TSI_GENCS_DVOLT(dv))|SET(TSI_GENCS_EXTCHRG(extcurr))|        \
              SET(TSI_GENCS_PS(ps))|SET(TSI_GENCS_NSCN(nos))| 	               \
              SET(TSI_GENCS_TSIEN_MASK)|SET(TSI_GENCS_TSIIEN_MASK)|	       \
              CLR(TSI_GENCS_STPE_MASK)|CLR(TSI_GENCS_STM_MASK)|		       \
              SET(TSI_GENCS_EOSF_MASK)|CLR(TSI_GENCS_CURSW_MASK),	       \
/* DATA  */   SET(TSI_DATA_TSICH(ch))|CLR(TSI_DATA_DMAEN_MASK)| 	       \
              CLR(TSI_DATA_SWTS_MASK),					       \
}
/*! @} End of tsi_config                                                    */

/******************************************************************************
* TSI callback registered by TSI_Init() function
*
*//*! @addtogroup tsi_callback
* @{
*******************************************************************************/
/*! TPM_CALLBACK type declaration                                             */
typedef enum 
{ 
  OUTRGF_CALLBACK=0x001,        ///< out of range detection
  EOSF_CALLBACK=0x002           ///< end of scan detection
} TSI_CALLBACK_TYPE;            ///< TSI Callback types
/*! TSI_CALLBACK type declaration                                             */
typedef void (*TSI_CALLBACK)(TSI_CALLBACK_TYPE type);
/*! @} End of TSI_callback                                                    */

/******************************************************************************
* TSI function and macro definitions
*
*//*! @addtogroup tsi_macro
* @{
*******************************************************************************/
#define TSI0_OUTRG_IRQ_Enable()         REG_SetVal(TSI0_GENCS,TSI_GENCS_ESOR,0x0);
/***************************************************************************//*!
 * @brief   Macro enables out of range interrupt.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_OUTRG_IRQ_Enable(module)	module##_OUTRG_IRQ_Enable()

#define TSI0_EOS_IRQ_Enable()           REG_SetVal(TSI0_GENCS,TSI_GENCS_ESOR,0x1);
/***************************************************************************//*!
 * @brief   Macro enables end of scan interrupt.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_EOS_IRQ_Enable(module)	module##_EOS_IRQ_Enable()

#define TSI0_Mode(mode)                 REG_SetVal(TSI0_GENCS,TSI_GENCS_MODE,mode);
/***************************************************************************//*!
 * @brief   Macro enables end of scan interrupt.
 * @param   module  - TSI0
 * @param   mode  - @ref tsi_modes
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_Mode(module,mode)	        module##_Mode(mode)

#define TSI0_SetRefCurr(curr)           REG_SetVal(TSI0_GENCS,TSI_GENCS_REFCHRG,curr);
/***************************************************************************//*!
 * @brief   Macro sets reference oscillator charging/discharging current.
 * @param   module  - TSI0
 * @param   curr  - @ref tsi_chargecurr
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_SetRefCurr(module,curr)	module##_SetRefCurr(curr)

#define TSI0_SetExtCurr(curr)           REG_SetVal(TSI0_GENCS,TSI_GENCS_EXTCHRG,curr);
/***************************************************************************//*!
 * @brief   Macro sets external (electrode) oscillator charging/discharging 
 *          current.
 * @param   module  - TSI0
 * @param   curr  - @ref tsi_chargecurr
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_SetExtCurr(module,curr)	module##_SetExtCurr(curr)

#define TSI0_dVolt(dV)                  REG_SetVal(TSI0_GENCS,TSI_GENCS_DVOLT,dV);
/***************************************************************************//*!
 * @brief   Macro sets the oscillator's voltage rails.
 * @param   module  - TSI0
 * @param   dV  - @ref tsi_deltavoltage
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_dVolt(module,dV)	        module##_dVolt(dV)

#define TSI0_SetPrescaler(ps)           REG_SetVal(TSI0_GENCS,TSI_GENCS_PS,ps);
/***************************************************************************//*!
 * @brief   Macro sets the prescaler of the electrode oscillator frequency.
 * @param   module  - TSI0
 * @param   ps  - @ref tsi_prescalers
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_SetPrescaler(module,ps)	module##_SetPrescaler(ps)

#define TSI0_SetNumOfScans(nos)         REG_SetVal(TSI0_GENCS,TSI_GENCS_NSCN,nos);
/***************************************************************************//*!
 * @brief   Macro sets number of scans performed on each electrode per one 
 *          request (trigger).
 * @param   module  - TSI0
 * @param   nos  - @ref tsi_numscans
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_SetNumOfScans(module,nos)	module##_SetNumOfScans(nos)

#define TSI0_Enable()                  REG_SetVal(TSI0_GENCS,TSI_GENCS_TSIEN,0x1);
/***************************************************************************//*!
 * @brief   Macro enables TSI module.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_Enable(module)	        module##_Enable()

#define TSI0_Disable()                  REG_SetVal(TSI0_GENCS,TSI_GENCS_TSIEN,0x0);
/***************************************************************************//*!
 * @brief   Macro disables TSI module.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_Disable(module)	        module##_Disable()

#define TSI0_IrqEnable()                REG_SetVal(TSI0_GENCS,TSI_GENCS_TSIIEN,0x1);
/***************************************************************************//*!
 * @brief   Macro enables TSI interrupt.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_IrqEnable(module)	        module##_IrqEnable()

#define TSI0_IrqDisable()               REG_SetVal(TSI0_GENCS,TSI_GENCS_TSIIEN,0x0);
/***************************************************************************//*!
 * @brief   Macro disables TSI interrupt.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_IrqDisable(module)	        module##_IrqDisable()

#define TSI0_StopEnable()                REG_SetVal(TSI0_GENCS,TSI_GENCS_STPE,0x1);
/***************************************************************************//*!
 * @brief   Macro enables TSI to running in low power modes.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_StopEnable(module)	        module##_StopEnable()

#define TSI0_StopDisable()              REG_SetVal(TSI0_GENCS,TSI_GENCS_STPE,0x0);
/***************************************************************************//*!
 * @brief   Macro disables TSI to running in low power modes.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_StopDisable(module)	        module##_StopDisable()

#define TSI0_HwTrgEnable()              REG_SetVal(TSI0_GENCS,TSI_GENCS_STM,0x1);
/***************************************************************************//*!
 * @brief   Macro enables hardware trigger scan.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 * @warning User is allowed to change this bit when TSI is not working in progress.
 ******************************************************************************/
#define TSI_HwTrgEnable(module)	        module##_HwTrgEnable()

#define TSI0_SwTrgEnable()              REG_SetVal(TSI0_GENCS,TSI_GENCS_STM,0x0);
/***************************************************************************//*!
 * @brief   Macro enables software trigger scan.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 * @warning User is allowed to change this bit when TSI is not working in progress.
 ******************************************************************************/
#define TSI_SwTrgEnable(module)	        module##_SwTrgEnable()

#define TSI0_CurrSrcsSwapDisable()       REG_SetVal(TSI0_GENCS,TSI_GENCS_CURSW,0x0);
/***************************************************************************//*!
 * @brief   Macro disables swaping of current source pair.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_CurrSrcsSwapDisable(module)	module##_CurrSrcsSwapDisable()

#define TSI0_CurrSrcsSwapEnable()       REG_SetVal(TSI0_GENCS,TSI_GENCS_CURSW,0x1);
/***************************************************************************//*!
 * @brief   Macro swaps current source pair.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_CurrSrcsSwapEnable(module)	module##_CurrSrcsSwapEnable()

#define TSI0_EOSF_Status()              (TSI0_GENCS&TSI_GENCS_EOSF_MASK)
#define TSI0_OUTRGF_Status()            (TSI0_GENCS&TSI_GENCS_OUTRGF_MASK)
#define TSI0_SCNIP_Status()             (TSI0_GENCS&TSI_GENCS_SCNIP_MASK)
#define TSI0_ESOR_Status()              (TSI0_GENCS&TSI_GENCS_ESOR_MASK)
/***************************************************************************//*!
 * @brief   Macro returns TSI status flag.
 * @param   module  - TSI0
 * @param   flag    - EOSF | OUTRGF | SCNIP | ESOR
 * @return  TPM timer STATUS register value
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_GetStatus(module,flag)      module##_##flag##_Status()

#define TSI0_ClrEOSF()                  TSI0_GENCS = (TSI0_GENCS&(~TSI_GENCS_EOSF_MASK))|TSI_GENCS_EOSF_MASK;
/***************************************************************************//*!
 * @brief   Macro clears end of scan flag.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_ClrEOSF(module)	        module##_ClrEOSF()

#define TSI0_ClrOUTRGF()                TSI0_GENCS = (TSI0_GENCS&(~TSI_GENCS_OUTRGF_MASK))|TSI_GENCS_OUTRGF_MASK;
/***************************************************************************//*!
 * @brief   Macro clears out of range flag.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_ClrOUTRGF(module)	        module##_ClrOUTRGF()

#define TSI0_ChanSel(ch)                REG_SetVal(TSI0_DATA,TSI_DATA_TSICH,ch);
/***************************************************************************//*!
 * @brief   Macro specifies current channel to be measured.
 * @param   module  - TSI0
 * @param   ch  - @ref tsi_channels
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_ChanSel(module,ch)	module##_ChanSel(ch)

#define TSI0_GetChanNum()       (uint32)((TSI0_DATA&TSI_DATA_TSICH_MASK)>>TSI_DATA_TSICH_SHIFT)
/***************************************************************************//*!
 * @brief   Macro returns currently used channel number.
 * @param   module  - TSI0
 * @return  uint32 - currently used channel number
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_GetChanNum(module)	 module##_GetChanNum()

#define TSI0_DmaEnable()         REG_SetVal(TSI0_DATA,TSI_DATA_DMAEN,0x1);
/***************************************************************************//*!
 * @brief   Macro enables DMA transfer.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_DmaEnable(module)	 module##_DmaEnable()

#define TSI0_DmaDisable()        REG_SetVal(TSI0_DATA,TSI_DATA_DMAEN,0x0);
/***************************************************************************//*!
 * @brief   Macro disbales DMA transfer.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_DmaDisable(module)	  module##_DmaDisable()

#define TSI0_SwTrgStart()         REG_SetVal(TSI0_DATA,TSI_DATA_SWTS,0x1);
/***************************************************************************//*!
 * @brief   Macro starts the scan.
 * @param   module  - TSI0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_SwTrgStart(module)	   module##_SwTrgStart()

#define TSI0_GetCntVal()           (uint16)(TSI0_DATA&TSI_DATA_TSICNT_MASK)
/***************************************************************************//*!
 * @brief   Macro starts the scan.
 * @param   module  - TSI0
 * @return  uint16 - value of accumulated scan counter value ticked by reference
 *									 oscilator
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_GetCntVal(module)	    	module##_GetCntVal()

#define TSI0_SetTreshold_HIGH(val)      REG_SetVal(TSI0_TSHD,TSI_TSHD_THRESH,val);
#define TSI0_SetTreshold_LOW(val)       REG_SetVal(TSI0_TSHD,TSI_TSHD_THRESL,val);
/***************************************************************************//*!
 * @brief   Macro sets the channel treshhold values.
 * @param   module  - TSI0
 * @param   level  - HIGH or LOW
 * @param   val  - value from (0 0xFFFF)
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_SetTreshold(module,level,val)    module##_SetTreshold_##level##(val)

#define TSI0_GetTreshold_HIGH()      ((TSI0_TSHD&TSI_TSHD_THRESH_MASK)>>TSI_TSHD_THRESH_SHIFT)
#define TSI0_GetTreshold_LOW()       (TSI0_TSHD&TSI_TSHD_THRESL_MASK)
/***************************************************************************//*!
 * @brief   Macro returns the channel treshhold values.
 * @param   module  - TSI0
 * @param   level  - HIGH or LOW
 * @return  treshold value from (0 0xFFFF)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TSI_GetTreshold(module,level)    module##_GetTreshold_##level##()

/***************************************************************************//*!
 * @brief   TSI initialization function.
 * @details This function initializes selected TSI channel.  
 * @param   module    TSI0
 * @param   cfg       Use one of following configuration structures 
 *                    @ref tsi_config
 * @param   thrl      treshold upper (high) limit
 * @param   thrh      treshold lower (low) limit
 * @param   ip        Interrupt priority 0..3
 * @param   callback  Pointer to @ref TSI_CALLBACK function
 * @note    Implemented as function call.
 ******************************************************************************/
#define TSI_Init(module,cfg,thrl,thrh,ip,callback) module##_Init(cfg,thrl,thrh,ip,callback)

/***************************************************************************//*!
 * @brief   TSI used chanels calibration function. Function performs calibration 
 *          of selected TSI channels and updates calibration treshhold values.
 * @param   module  - TSI0
 * @param   cfg     - @ref tsi_config
 * @param   achan  - pointer to channels array
 * @param   asize  - size of channels array
 * @param   sens  - @ref tsi_sensitivity
 * @param   *pCALIB - pointer to tCALIB data structure.
 * @return  0 - SUCCESS 
 * @return  > 1 - ERROR - channel number+1 which caused an error of calibration
 * @note    Implemented as function call.
 ******************************************************************************/
#define TSI_Calib(module,cfg,achan,asize,sens,pCALIB)                          \
        module##_Calib(cfg,achan,asize,sens,pCALIB)

/*! @} End of tsi_macro                                                     */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern int32 TSI0_Calib (tTSI tsi, uint8* p_u8Chan, uint8 u8NumChans, uint16 u16Sen, tTSI_CALIB *pCALIB);
extern void TSI0_Init  (tTSI tsi, uint32 threshl, uint32 threshh, uint8 ip, TSI_CALLBACK pCallback);
#endif /* __TSI_H */
