/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      tpm.h
 * @version   1.0.9.0
 * @date      Apr-24-2013
 * @brief     TPM driver header file.
 *
 * Revision History:
 *  1.	11/01/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup tpm_example0
 * @{
 * @par       Source code:
 * @include   tpm0_test\tpm0_test.c
 * @par       Appconfig.h:
 * @include   tpm0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of tpm_example1                                                    */
#ifndef __TPM_H
#define __TPM_H 
 
/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct {uint32 SC, CONF;} tTPM;
typedef struct {uint32 CnSC;} tTPM_CH;

/******************************************************************************
* TPM trigger option selection
*
*//*! @addtogroup tpm_triggers
* @{
*******************************************************************************/
typedef enum    {                                                              
                  TPMTRG_EXTRIG_IN=0x00,        ///< External trigger pin input
                  TPMTRG_HSCMP0=0x01,           ///< HS comparator 0 output
                  TPMTRG_PIT0=0x04,             ///< PIT trigger 0   
                  TPMTRG_PIT1=0x05,             ///< PIT trigger 1
                  TPMTRG_TPM0OVF=0x08,          ///< TPM0 overflow
                  TPMTRG_TPM1OVF=0x09,          ///< TPM1 overflow
                  TPMTRG_TPM2OVF=0x0A,          ///< TPM2 overflow
                  TPMTRG_RTCALARM=0x0C,         ///< RTC alarm
                  TPMTRG_RTCSEC=0x0D,           ///< RTC seconds
                  TPMTRG_LPTMR=0x0E,            ///< LPTMR trigger     
                } tTPMTRIGGER_TYPE;
/*! @} End of tpm_triggers                                                    */

/******************************************************************************
* TPM channel's output names definition
*
*//*! @addtogroup tpm_channels
* @{
*******************************************************************************/
#define CHO_0         (uint32)(1<<0)            ///< TPMx channel output 0
#define CHO_1         (uint32)(1<<1)            ///< TPMx channel output 1
#define CHO_2         (uint32)(1<<2)            ///< TPMx channel output 2
#define CHO_3         (uint32)(1<<3)            ///< TPMx channel output 3
#define CHO_4         (uint32)(1<<4)            ///< TPMx channel output 4
#define CHO_5         (uint32)(1<<5)            ///< TPMx channel output 5
/*! @} End of tpm_channels                                                    */

/******************************************************************************
* TPM default configurations used by TPM_Init() function
*
*//*! @addtogroup tpm_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief Edge aligned timer mode with source clock divided by 1.
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY1_EDGEALIGN_CONFIG                             \
(tTPM)  {                                                                     \
/* SC      */ CLR(TPM_SC_DMA_MASK)|CLR(TPM_SC_TOIE_MASK)|                     \
              CLR(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0)),   \
/* CONF    */ SET(TPM_CONF_TRGSEL(0x0))|CLR(TPM_CONF_CROT_MASK)|              \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/**************************************************************************/ /*!
 * @brief Edge aligned timer mode with source clock divided by 1 and with 
 *        external trigger selection option. 
 * @param trgnum     Number of trigger to be used (@ref tpm_triggers)
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY1_EDGEALIGN_CONFIG_EXTTRG(trgnum)              \
(tTPM)  {                                                                     \
/* SC      */ CLR(TPM_SC_DMA_MASK)|CLR(TPM_SC_TOIE_MASK)|                     \
              CLR(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0)),   \
/* CONF    */ SET(TPM_CONF_TRGSEL(trgnum))|CLR(TPM_CONF_CROT_MASK)|           \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/**************************************************************************/ /*!
 * @brief Edge aligned timer mode with source clock divided by 128.
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY128_EDGEALIGN_CONFIG                           \
(tTPM)  {                                                                     \
/* SC      */ CLR(TPM_SC_DMA_MASK)|CLR(TPM_SC_TOIE_MASK)|                     \
              CLR(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0x07)),\
/* CONF    */ SET(TPM_CONF_TRGSEL(0x0))|CLR(TPM_CONF_CROT_MASK)|              \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/**************************************************************************/ /*!
 * @brief Edge aligned timer mode with source clock divided by 1 and interrupt 
 *        enabled.
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY1_EDGEALIGN_IRQ_CONFIG                         \
(tTPM)  {                                                                     \
/* SC      */ CLR(TPM_SC_DMA_MASK)|SET(TPM_SC_TOIE_MASK)|                     \
              CLR(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0)),   \
/* CONF    */ SET(TPM_CONF_TRGSEL(0x0))|CLR(TPM_CONF_CROT_MASK)|              \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/**************************************************************************/ /*!
 * @brief Edge aligned timer mode with source clock divided by 1 and interrupt 
 *        enabled and with trigger selection option.
 * @param trgnum     Number of trigger to be used (@ref tpm_triggers)
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY1_EDGEALIGN_IRQ_CONFIG_TRG(trgnum)             \
(tTPM)  {                                                                     \
/* SC      */ CLR(TPM_SC_DMA_MASK)|SEI(TPM_SC_TOIE_MASK)|                     \
              CLR(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0)),   \
/* CONF    */ SET(TPM_CONF_TRGSEL(trgnum))|CLR(TPM_CONF_CROT_MASK)|           \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/**************************************************************************/ /*!
 * @brief Edge aligned timer mode with source clock divided by 128 and interrupt 
 *        enabled.
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY128_EDGEALIGN_IRQ_CONFIG                       \
(tTPM)  {                                                                     \
/* SC      */ CLR(TPM_SC_DMA_MASK)|SET(TPM_SC_TOIE_MASK)|                     \
              CLR(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0x07)),\
/* CONF    */ SET(TPM_CONF_TRGSEL(0x0))|CLR(TPM_CONF_CROT_MASK)|              \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/**************************************************************************/ /*!
 * @brief Edge aligned timer mode with source clock divided by 1 and DMA 
 *        enabled.
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY1_EDGEALIGN_DMA_CONFIG                         \
(tTPM)  {                                                                     \
/* SC      */ SET(TPM_SC_DMA_MASK)|CLR(TPM_SC_TOIE_MASK)|                     \
              CLR(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0)),   \
/* CONF    */ SET(TPM_CONF_TRGSEL(0x0))|CLR(TPM_CONF_CROT_MASK)|              \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/**************************************************************************/ /*!
 * @brief Edge aligned timer mode with source clock divided by 1 and interrupt 
 *        enabled and with trigger selection option.
 * @param trgnum     Number of trigger to be used (@ref tpm_triggers)
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY1_EDGEALIGN_DMA_CONFIG_TRG(trgnum)             \
(tTPM)  {                                                                     \
/* SC      */ SET(TPM_SC_DMA_MASK)|CLR(TPM_SC_TOIE_MASK)|                     \
              CLR(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0)),   \
/* CONF    */ SET(TPM_CONF_TRGSEL(trgnum))|CLR(TPM_CONF_CROT_MASK)|           \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/**************************************************************************/ /*!
 * @brief Edge aligned timer mode with source clock divided by 128 and DMA 
 *        enabled.
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY128_EDGEALIGN_DMA_CONFIG                       \
(tTPM)  {                                                                     \
/* SC      */ SET(TPM_SC_DMA_MASK)|SET(TPM_SC_TOIE_MASK)|                     \
              CLR(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0x07)),\
/* CONF    */ SET(TPM_CONF_TRGSEL(0x0))|CLR(TPM_CONF_CROT_MASK)|              \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/**************************************************************************/ /*!
 * @brief Center aligned timer mode with source clock divided by 1.
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY1_CENTERALIGN_CONFIG                           \
(tTPM)  {                                                                     \
/* SC      */ CLR(TPM_SC_DMA_MASK)|CLR(TPM_SC_TOIE_MASK)|                     \
              SET(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0)),   \
/* CONF    */ SET(TPM_CONF_TRGSEL(0x0))|CLR(TPM_CONF_CROT_MASK)|              \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/**************************************************************************/ /*!
 * @brief Center aligned timer mode with source clock divided by 1 and with 
 *        trigger selection option.
 * @param trgnum     Number of trigger to be used (@ref tpm_triggers)
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY1_CENTERALIGN_CONFIG_TRG(trgnum)               \
(tTPM)  {                                                                     \
/* SC      */ CLR(TPM_SC_DMA_MASK)|CLR(TPM_SC_TOIE_MASK)|                     \
              SET(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0)),   \
/* CONF    */ SET(TPM_CONF_TRGSEL(trgnum))|CLR(TPM_CONF_CROT_MASK)|           \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/**************************************************************************/ /*!
 * @brief Center aligned timer mode with source clock divided by 1 and interrupt 
 *        enabled.
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY1_CENTERALIGN_IRQ_CONFIG                       \
(tTPM)  {                                                                     \
/* SC      */ CLR(TPM_SC_DMA_MASK)|SET(TPM_SC_TOIE_MASK)|                     \
              SET(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0)),   \
/* CONF    */ SET(TPM_CONF_TRGSEL(0x0))|CLR(TPM_CONF_CROT_MASK)|              \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}

/**************************************************************************/ /*!
 * @brief Center aligned timer mode with source clock divided by 1 and DMA 
 *        enabled.
 *****************************************************************************/
#define TPM_MODULE_SYSCLK_DIVBY1_CENTERALIGN_DMA_CONFIG                       \
(tTPM)  {                                                                     \
/* SC      */ SET(TPM_SC_DMA_MASK)|SET(TPM_SC_TOIE_MASK)|                     \
              SET(TPM_SC_CPWMS_MASK)|SET(TPM_SC_CMOD(1))|SET(TPM_SC_PS(0)),   \
/* CONF    */ SET(TPM_CONF_TRGSEL(0x0))|CLR(TPM_CONF_CROT_MASK)|              \
              CLR(TPM_CONF_CSOO_MASK)|CLR(TPM_CONF_CSOT_MASK)|                \
              CLR(TPM_CONF_GTBEEN_MASK)|SET(TPM_CONF_DBGMODE(0x0))|           \
              CLR(TPM_CONF_DOZEEN_MASK),                                      \
}
/*! @} End of tpm_config                                                      */

// Channels config
/******************************************************************************
* TPM channel configurations used by TPM_CHAN_Init() function
*
*//*! @addtogroup tpm_chanconfig
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief Timer channel input capture mode - rising edge detection.
 *****************************************************************************/
#define TPM_CHANNEL_CAPTURE_RISINGEDGE_CONFIG                                 \
(tTPM_CH)  {                                                                  \
/* CnSC    */ CLR(TPM_CnSC_CHIE_MASK)|CLR(TPM_CnSC_MSB_MASK)|                 \
              CLR(TPM_CnSC_MSA_MASK)|CLR(TPM_CnSC_ELSB_MASK)|                 \
              SET(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}

/**************************************************************************/ /*!
 * @brief Timer channel input capture mode - falling edge detection.
 *****************************************************************************/
#define TPM_CHANNEL_CAPTURE_FALLINGEDGE_CONFIG                                \
(tTPM_CH)  {                                                                  \
/* CnSC    */ CLR(TPM_CnSC_CHIE_MASK)|CLR(TPM_CnSC_MSB_MASK)|                 \
              CLR(TPM_CnSC_MSA_MASK)|SET(TPM_CnSC_ELSB_MASK)|                 \
              CLR(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}

/**************************************************************************/ /*!
 * @brief Timer channel input capture mode - both edges detection.
 *****************************************************************************/
#define TPM_CHANNEL_CAPTURE_BOTHEDGES_CONFIG                                  \
(tTPM_CH)  {                                                                  \
/* CnSC    */ CLR(TPM_CnSC_CHIE_MASK)|CLR(TPM_CnSC_MSB_MASK)|                 \
              CLR(TPM_CnSC_MSA_MASK)|SET(TPM_CnSC_ELSB_MASK)|                 \
              SET(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}

/**************************************************************************/ /*!
 * @brief Timer channel output compare mode with toggled output on match.
 *****************************************************************************/
#define TPM_CHANNEL_COMPARE_TGLOUTPUT_CONFIG                                  \
(tTPM_CH)  {                                                                  \
/* CnSC    */ CLR(TPM_CnSC_CHIE_MASK)|CLR(TPM_CnSC_MSB_MASK)|                 \
              SET(TPM_CnSC_MSA_MASK)|CLR(TPM_CnSC_ELSB_MASK)|                 \
              SET(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}

/**************************************************************************/ /*!
 * @brief Timer channel output compare mode with cleared output on match.
 *****************************************************************************/
#define TPM_CHANNEL_COMPARE_CLROUTPUT_CONFIG                                  \
(tTPM_CH)  {                                                                  \
/* CnSC    */ CLR(TPM_CnSC_CHIE_MASK)|CLR(TPM_CnSC_MSB_MASK)|                 \
              SET(TPM_CnSC_MSA_MASK)|SET(TPM_CnSC_ELSB_MASK)|                 \
              CLR(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}

/**************************************************************************/ /*!
 * @brief Timer channel output compare mode with set output on match.
 *****************************************************************************/
#define TPM_CHANNEL_COMPARE_SETOUTPUT_CONFIG                                  \
(tTPM_CH)  {                                                                  \
/* CnSC    */ CLR(TPM_CnSC_CHIE_MASK)|CLR(TPM_CnSC_MSB_MASK)|                 \
              SET(TPM_CnSC_MSA_MASK)|SET(TPM_CnSC_ELSB_MASK)|                 \
              SET(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}

/**************************************************************************/ /*!
 * @brief Timer channel output compare mode with toggled output on match. Channel
 *        interrupt enabled.
 *****************************************************************************/
#define TPM_CHANNEL_COMPARE_TGLOUTPUT_IRQ_CONFIG                              \
(tTPM_CH)  {                                                                  \
/* CnSC    */ SET(TPM_CnSC_CHIE_MASK)|CLR(TPM_CnSC_MSB_MASK)|                 \
              SET(TPM_CnSC_MSA_MASK)|CLR(TPM_CnSC_ELSB_MASK)|                 \
              SET(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}

/**************************************************************************/ /*!
 * @brief Timer channel normal PWM mode (high true pulses).
 *****************************************************************************/
#define TPM_CHANNEL_PWMNORMAL_CONFIG                                          \
(tTPM_CH)  {                                                                  \
/* CnSC    */ CLR(TPM_CnSC_CHIE_MASK)|SET(TPM_CnSC_MSB_MASK)|                 \
              CLR(TPM_CnSC_MSA_MASK)|SET(TPM_CnSC_ELSB_MASK)|                 \
              CLR(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}

/**************************************************************************/ /*!
 * @brief Timer channel inverted PWM mode (low true pulses).
 *****************************************************************************/
#define TPM_CHANNEL_PWMINVERT_CONFIG                                          \
(tTPM_CH)  {                                                                  \
/* CnSC   */  CLR(TPM_CnSC_CHIE_MASK)|SET(TPM_CnSC_MSB_MASK)|                 \
              CLR(TPM_CnSC_MSA_MASK)|CLR(TPM_CnSC_ELSB_MASK)|                 \
              SET(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}

/**************************************************************************/ /*!
 * @brief Timer channel normal PWM mode (high true pulses) with channel IRQ
 *        enabled.
 *****************************************************************************/
#define TPM_CHANNEL_PWMNORMAL_IRQ_CONFIG                                      \
(tTPM_CH)  {                                                                  \
/* CnSC    */ SET(TPM_CnSC_CHIE_MASK)|SET(TPM_CnSC_MSB_MASK)|                 \
              CLR(TPM_CnSC_MSA_MASK)|SET(TPM_CnSC_ELSB_MASK)|                 \
              CLR(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}

/**************************************************************************/ /*!
 * @brief Timer channel inverted PWM mode (low true pulses) with channel IRQ
 *        enabled.
 *****************************************************************************/
#define TPM_CHANNEL_PWMINVERT_IRQ_CONFIG                                      \
(tTPM_CH)  {                                                                  \
/* CnSC   */  SET(TPM_CnSC_CHIE_MASK)|SET(TPM_CnSC_MSB_MASK)|                 \
              CLR(TPM_CnSC_MSA_MASK)|CLR(TPM_CnSC_ELSB_MASK)|                 \
              SET(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}

/**************************************************************************/ /*!
 * @brief Timer channel output compare mode with pulse output low on match.
 *****************************************************************************/
#define TPM_CHANNEL_COMPARE_PULSEOUTLOW_CONFIG                                \
(tTPM_CH)  {                                                                  \
/* CnSC    */ CLR(TPM_CnSC_CHIE_MASK)|SET(TPM_CnSC_MSB_MASK)|                 \
              SET(TPM_CnSC_MSA_MASK)|SET(TPM_CnSC_ELSB_MASK)|                 \
              CLR(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}

/**************************************************************************/ /*!
 * @brief Timer channel output compare mode with pulse output high on match.
 *****************************************************************************/
#define TPM_CHANNEL_COMPARE_PULSEOUTHIGH_CONFIG                               \
(tTPM_CH)  {                                                                  \
/* CnSC    */ CLR(TPM_CnSC_CHIE_MASK)|SET(TPM_CnSC_MSB_MASK)|                 \
              SET(TPM_CnSC_MSA_MASK)|SET(TPM_CnSC_ELSB_MASK)|                 \
              SET(TPM_CnSC_ELSA_MASK)|CLR(TPM_CnSC_DMA_MASK),                 \
}
/*! @} End of tpm_chanconfig                                                  */

/******************************************************************************
* TPM callback registered by TPM_Init() function
*
*//*! @addtogroup tpm_callback
* @{
*******************************************************************************/
/*! TPM_CALLBACK type declaration                                             */
typedef enum 
{ 
  CH0F_CALLBACK_MASK=0x001,CH1F_CALLBACK_MASK=0x002,CH2F_CALLBACK_MASK=0x004, \
  CH3F_CALLBACK_MASK=0x008,CH4F_CALLBACK_MASK=0x010,CH5F_CALLBACK_MASK=0x020, \
  TOF_CALLBACK_MASK=0x100 
} TPM_CALLBACK_TYPE;
/*! @brief TPM_CALLBACK function declaration                                  */
typedef void (*TPM_CALLBACK)(TPM_CALLBACK_TYPE type);
/*! @} End of tpm_callback                                                    */

/******************************************************************************
* TPM function and macro definitions
*
*//*! @addtogroup tpm_macro
* @{
*******************************************************************************/
#define TPM0_Disable()          REG_SetVal(TPM0_SC,TPM_SC_CMOD,0x0);
#define TPM1_Disable()          REG_SetVal(TPM1_SC,TPM_SC_CMOD,0x0);
#define TPM2_Disable()          REG_SetVal(TPM2_SC,TPM_SC_CMOD,0x0);
/***************************************************************************//*!
 * @brief   Macro dislables TPM module.
 * @param   module  - TPM0|TPM1|TPM2
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TPM_Disable(module)     module##_Disable()

#define TPM0_Enable_TPMCLK()    REG_SetVal(TPM0_SC,TPM_SC_CMOD,0x1);
#define TPM1_Enable_TPMCLK()    REG_SetVal(TPM1_SC,TPM_SC_CMOD,0x1);
#define TPM2_Enable_TPMCLK()    REG_SetVal(TPM2_SC,TPM_SC_CMOD,0x1);
#define TPM0_Enable_EXTCLK()    REG_SetVal(TPM0_SC,TPM_SC_CMOD,0x2);
#define TPM1_Enable_EXTCLK()    REG_SetVal(TPM1_SC,TPM_SC_CMOD,0x2);
#define TPM2_Enable_EXTCLK()    REG_SetVal(TPM2_SC,TPM_SC_CMOD,0x2);
/***************************************************************************//*!
 * @brief   Macro enables TPM module.
 * @param   module  - TPM0 | TPM1 | TPM2
 * @param   clksel  - TPMCLK | EXTCLK
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TPM_Enable(module,clksel)     module##_Enable_##clksel##()

#define TPM0CH0_GetStatus()           TPM0_STATUS&TPM_STATUS_CH0F_MASK
#define TPM0CH1_GetStatus()           TPM0_STATUS&TPM_STATUS_CH1F_MASK
#define TPM0CH2_GetStatus()           TPM0_STATUS&TPM_STATUS_CH2F_MASK
#define TPM0CH3_GetStatus()           TPM0_STATUS&TPM_STATUS_CH3F_MASK
#define TPM0CH4_GetStatus()           TPM0_STATUS&TPM_STATUS_CH4F_MASK
#define TPM0CH5_GetStatus()           TPM0_STATUS&TPM_STATUS_CH5F_MASK
#define TPM1CH0_GetStatus()           TPM1_STATUS&TPM_STATUS_CH0F_MASK
#define TPM1CH1_GetStatus()           TPM1_STATUS&TPM_STATUS_CH1F_MASK
#define TPM2CH0_GetStatus()           TPM2_STATUS&TPM_STATUS_CH0F_MASK
#define TPM2CH1_GetStatus()           TPM2_STATUS&TPM_STATUS_CH1F_MASK
/***************************************************************************//*!
 * @brief   Macro returns TPM channel status.
 * @param   module  - TPM0|TPM1|TPM2
 * @param   chan    - CH0|CH1|CH2|CH3|CH4|CH5
 * @return  TPM timer STATUS register value
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TPM_CHAN_GetStatus(module,chan)        module##chan##_GetStatus()

#define TPM0CH0_ClrFlag()           TPM0_C0SC |= TPM_CnSC_CHF_MASK;
#define TPM0CH1_ClrFlag()           TPM0_C1SC |= TPM_CnSC_CHF_MASK;
#define TPM0CH2_ClrFlag()           TPM0_C2SC |= TPM_CnSC_CHF_MASK;
#define TPM0CH3_ClrFlag()           TPM0_C3SC |= TPM_CnSC_CHF_MASK;
#define TPM0CH4_ClrFlag()           TPM0_C4SC |= TPM_CnSC_CHF_MASK;
#define TPM0CH5_ClrFlag()           TPM0_C5SC |= TPM_CnSC_CHF_MASK;
#define TPM1CH0_ClrFlag()           TPM1_C0SC |= TPM_CnSC_CHF_MASK;
#define TPM1CH1_ClrFlag()           TPM1_C1SC |= TPM_CnSC_CHF_MASK;
#define TPM2CH0_ClrFlag()           TPM2_C0SC |= TPM_CnSC_CHF_MASK;
#define TPM2CH1_ClrFlag()           TPM2_C1SC |= TPM_CnSC_CHF_MASK;
/***************************************************************************//*!
 * @brief   Macro clears TPM channel status flag.
 * @param   module  - TPM0|TPM1|TPM2
 * @param   chan    - CH0|CH1|CH2|CH3|CH4|CH5
 * @return  TPM timer STATUS register value
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TPM_CHAN_ClrFlag(module,chan)        module##chan##_ClrFlag()

#define TPM0CH0_GetValue()                    TPM0_C0V
#define TPM0CH1_GetValue()                    TPM0_C1V
#define TPM0CH2_GetValue()                    TPM0_C2V
#define TPM0CH3_GetValue()                    TPM0_C3V
#define TPM0CH4_GetValue()                    TPM0_C4V
#define TPM0CH5_GetValue()                    TPM0_C5V
#define TPM1CH0_GetValue()                    TPM1_C0V
#define TPM1CH1_GetValue()                    TPM1_C1V
#define TPM2CH0_GetValue()                    TPM2_C0V
#define TPM2CH1_GetValue()                    TPM2_C1V
/***************************************************************************//*!
 * @brief   Macro returns TPM channel value.
 * @param   module  - TPM0|TPM1|TPM2
 * @param   chan    - CH0|CH1|CH2|CH3|CH4|CH5
 * @return  TPM timer CnV register value
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TPM_CHAN_GetValue(module,chan)        module##chan##_GetValue()

#define TPM0CH0_SetValue(x)           { TPM0_C0V = x; }
#define TPM0CH1_SetValue(x)           { TPM0_C1V = x; }
#define TPM0CH2_SetValue(x)           { TPM0_C2V = x; }
#define TPM0CH3_SetValue(x)           { TPM0_C3V = x; }
#define TPM0CH4_SetValue(x)           { TPM0_C4V = x; }
#define TPM0CH5_SetValue(x)           { TPM0_C5V = x; }
#define TPM1CH0_SetValue(x)           { TPM1_C0V = x; }
#define TPM1CH1_SetValue(x)           { TPM1_C1V = x; }
#define TPM2CH0_SetValue(x)           { TPM2_C0V = x; }
#define TPM2CH1_SetValue(x)           { TPM2_C1V = x; } 
/***************************************************************************//*!
 * @brief   Macro sets TPM channel value.
 * @param   module  - TPM0|TPM1|TPM2
 * @param   chan    - CH0|CH1|CH2|CH3|CH4|CH5
 * @param   value   - channel value (CV register)  
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TPM_CHAN_SetValue(module,chan,value)  module##chan##_SetValue(value)

#define TPM0_SetModulo(x)                      { TPM0_MOD = x; }
#define TPM1_SetModulo(x)                      { TPM1_MOD = x; }
#define TPM2_SetModulo(x)                      { TPM2_MOD = x; }
/***************************************************************************//*!
 * @brief   Macro sets TPM block modulo value.
 * @param   module  - TPM0|TPM1|TPM2
 * @param   modVal  - counter modulo value (MOD register)  
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define TPM_SetModulo(module,modVal)          { module##_SetModulo(modVal); }

#define TPM0_TrgSel(trg)        { REG_SetVal(TPM0_CONF,TPM_CONF_TRGSEL,trg); }
#define TPM1_TrgSel(trg)        { REG_SetVal(TPM1_CONF,TPM_CONF_TRGSEL,trg); }
#define TPM2_TrgSel(trg)        { REG_SetVal(TPM2_CONF,TPM_CONF_TRGSEL,trg); }
/***************************************************************************//*!
 * @brief   TPM input trigger for starting or reloading counter selection.
 * @param   module  - TPM0|TPM1|TPM2
 * @param   trg     - @ref tpm_triggers
 * @return  none
 * @note    Implemented as function call. 
 * @warning This field should only be changed when the TPM counter is disabled.
 ******************************************************************************/  
#define TPM_TrgSel(module,trg)          module##_TrgSel(trg)

#define TPM0_CntReloadOnTrg()           { TPM0_CONF |= TPM_CONF_CROT_MASK; }
#define TPM1_CntReloadOnTrg()           { TPM1_CONF |= TPM_CONF_CROT_MASK; }
#define TPM2_CntReloadOnTrg()           { TPM2_CONF |= TPM_CONF_CROT_MASK; }
/***************************************************************************//*!
 * @brief   TPM counter reload on trigger. When set, the LPTPM counter will 
 *          reload with zero (and initialize PWM outputs to their default value) 
 *          when a rising edge is detected on the selected trigger input.
 *          The trigger input is ignored if the LPTPM counter is paused during 
 *          debug mode or doze mode.
 * @param   module  - TPM0|TPM1|TPM2
 * @return  none
 * @note    Implemented as function call.
 * @warning This field should only be changed when the TPM counter is disabled.
 ******************************************************************************/  
#define TPM_CntReloadOnTrg(module)      module##_CntReloadOnTrg()

#define TPM0_CntStopOnOvf()           { TPM0_CONF |= TPM_CONF_CSOO_MASK; }
#define TPM1_CntStopOnOvf()           { TPM1_CONF |= TPM_CONF_CSOO_MASK; }
#define TPM2_CntStopOnOvf()           { TPM2_CONF |= TPM_CONF_CSOO_MASK; }
/***************************************************************************//*!
 * @brief   TPM counter stop on overflow. When set, the LPTPM counter will stop 
 *          incrementing once the counter equals the MOD value and incremented 
 *          (this also sets the TOF).
 * @param   module  - TPM0|TPM1|TPM2
 * @return  none
 * @note    Implemented as function call.
 * @warning This field should only be changed when the TPM counter is disabled.
 ******************************************************************************/  
#define TPM_CntStopOnOvf(module)        module##_CntStopOnOvf()

#define TPM0_CntStartOnTrg()           { TPM0_CONF |= TPM_CONF_CSOT_MASK; }
#define TPM1_CntStartOnTrg()           { TPM1_CONF |= TPM_CONF_CSOT_MASK; }
#define TPM2_CntStartOnTrg()           { TPM2_CONF |= TPM_CONF_CSOT_MASK; }
/***************************************************************************//*!
 * @brief   TPM counter start on trigger. When set, the LPTPM counter will not 
 *          start incrementing after it is enabled until a rising edge on the
 *          selected trigger input is detected.
 * @param   module  - TPM0|TPM1|TPM2
 * @return  none
 * @note    Implemented as function call.
 * @warning This field should only be changed when the TPM counter is disabled.
 ******************************************************************************/  
#define TPM_CntStartOnTrg(module)        module##_CntStartOnTrg()

#define TPM0_SetGTB()                  { TPM0_CONF |= TPM_CONF_GTBEEN_MASK; }
#define TPM1_SetGTB()                  { TPM1_CONF |= TPM_CONF_GTBEEN_MASK; }
#define TPM2_SetGTB()                  { TPM2_CONF |= TPM_CONF_GTBEEN_MASK; }
/***************************************************************************//*!
 * @brief   TPM global time base modules initialization function.
 * @param   module  - TPM0|TPM1|TPM2
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/  
#define TPM_Set_GTB(module)             module##_SetGTB()

#define TPM0_DebugMode_STOP()           { TPM0_CONF &= ~TPM_CONF_DBGMODE_MASK; }
#define TPM1_DebugMode_STOP()           { TPM1_CONF &= ~TPM_CONF_DBGMODE_MASK; }
#define TPM2_DebugMode_STOP()           { TPM2_CONF &= ~TPM_CONF_DBGMODE_MASK; }
#define TPM0_DebugMode_RUN()            { TPM0_CONF |= TPM_CONF_DBGMODE_MASK; }
#define TPM1_DebugMode_RUN()            { TPM1_CONF |= TPM_CONF_DBGMODE_MASK; }
#define TPM2_DebugMode_RUN()            { TPM2_CONF |= TPM_CONF_DBGMODE_MASK; }
/***************************************************************************//*!
 * @brief   Configures the TPM behavior in debug mode.
 * @param   module  - TPM0|TPM1|TPM2
 * @param   mode    - STOP | RUN
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/  
#define TPM_DebugMode(module,mode)             module##_DebugMode_##mode##()

#define TPM0_DozeEnable()               { TPM0_CONF |= TPM_CONF_DOZEEN_MASK; }
#define TPM1_DozeEnable()               { TPM1_CONF |= TPM_CONF_DOZEEN_MASK; }
#define TPM2_DozeEnable()               { TPM2_CONF |= TPM_CONF_DOZEEN_MASK; }
/***************************************************************************//*!
 * @brief   Configures the TPM behavior in wait mode - paused in doze mode.
 * @param   module  - TPM0|TPM1|TPM2
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/  
#define TPM_DozeEnable(module)          module##_DozeEnable()

#define TPM0_DozeDisable()              { TPM0_CONF &= ~TPM_CONF_DOZEEN_MASK; }
#define TPM1_DozeDisable()              { TPM1_CONF &= ~TPM_CONF_DOZEEN_MASK; }
#define TPM2_DozeDisable()              { TPM2_CONF &= ~TPM_CONF_DOZEEN_MASK; }
/***************************************************************************//*!
 * @brief   Configures the TPM behavior in wait mode - continues in doze mode.
 * @param   module  - TPM0|TPM1|TPM2
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/  
#define TPM_DozeDisable(module)         module##_DozeDisable()

/* Function redefinition                                                      */
/***************************************************************************//*!
 * @brief   TPM initialization function.
 * @param   module  - TPM0|TPM1|TPM2
 * @param   cfg     - @ref tpm_config
 * @param   modVal  - counter modulo value (MOD register)  
 * @param   ip      - interrupt priority 0..3
 * @param   callback- pointer to TPM_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define TPM_Init(module,cfg,modVal,ip,callback)  module##_Init(cfg,   \
                                                        modVal,ip,callback)

/***************************************************************************//*!
 * @brief   TPM channel initialization function.
 * @param   module  - TPM0|TPM1|TPM2
 * @param   ch      - CH0|CH1|CH2|CH3|CH4|CH5
 * @param   cfg     - @ref tpm_chanconfig
 * @param   value   - channel value
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/  
#define TPM_CHAN_Init(module,ch,cfg,value)    module##ch##_Init(cfg,value)
/*! @} End of tpm_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/    
extern void TPM0_Init (tTPM TPM, uint16 modVal, uint8 ip, TPM_CALLBACK pCallback);
extern void TPM1_Init (tTPM TPM, uint16 modVal, uint8 ip, TPM_CALLBACK pCallback);
extern void TPM2_Init (tTPM TPM, uint16 modVal, uint8 ip, TPM_CALLBACK pCallback);

extern void TPM0CH0_Init (tTPM_CH TPM_ch, uint16 value);
extern void TPM0CH1_Init (tTPM_CH TPM_ch, uint16 value);
extern void TPM0CH2_Init (tTPM_CH TPM_ch, uint16 value);
extern void TPM0CH3_Init (tTPM_CH TPM_ch, uint16 value);
extern void TPM0CH4_Init (tTPM_CH TPM_ch, uint16 value);
extern void TPM0CH5_Init (tTPM_CH TPM_ch, uint16 value);
extern void TPM1CH0_Init (tTPM_CH TPM_ch, uint16 value);
extern void TPM1CH1_Init (tTPM_CH TPM_ch, uint16 value);
extern void TPM2CH0_Init (tTPM_CH TPM_ch, uint16 value);
extern void TPM2CH1_Init (tTPM_CH TPM_ch, uint16 value);
#endif /* __TPM_H */ 
