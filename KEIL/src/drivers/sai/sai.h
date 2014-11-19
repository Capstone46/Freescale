/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      sai.h
 * @version   1.0.7.0
 * @date      Feb-13-2013
 * @brief     SAI module header file.
 *
 * Revision History:
 *  1.	xx/xx/xxxxx   Bxxxxx   Initially written
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup sai_example0
 * @{
 * @par       Source code:
 * @include   sai_test\sai_test.c
 * @par       Appconfig.h:
 * @include   sai_test\appconfig.h   
 ******************************************************************************/
/*! @} End of sai_example0                                                    */
#ifndef __SAI_H
#define __SAI_H 


#define I2S_BIT_DEPTH 16
#define MCLK_IX0 24000000L
      
/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/

typedef struct
{
  unsigned short samplerate;
  unsigned long masterClock;
  unsigned char bitClockDivider;
}SAMPLES_DESCR;   
/******************************************************************************
 * SAI definition configuration structure                                     *
 ******************************************************************************/   
typedef struct
{
uint32 TCSR,
      TCR1,
      TCR2,
      TCR3,
      TCR4,
      TCR5,
      TDR0,
      TFR0,
      TMR,
      RCSR,
      RCR1,
      RCR2,
      RCR3,
      RCR4,
      RCR5,
      RDR0,
      RFR0,
      RMR, 
      MCR,
      MDR;
} tI2S;


/******************************************************************************
* SAI ... used by SAI_init() function
*
*//*! @addtogroup sai_config
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   SAI/I2S module Master TX IRQ mode
 * @details MCLK frequency is set to 24.0MHz depending on the SIM_CLKDIV1_OUTDIV
 *          Samplerate selected by SAI0_SetSampleRate() function
 *           
 * @showinitializer
 * @note    
 ******************************************************************************/
#define SAI_MODULE_MASTER_TX_RX_IRQ_CONFIG                                     \
(tI2S){                                                                        \
/* TCSR */ 0,                                                                  \
/* TCR1 */ 0,                                                                  \
/* TCR2 */ SET(I2S_TCR2_BCD_MASK)|                                             \
/*  ..  */ CLR(I2S_TCR2_BCP_MASK),                                             \
/* TCR3 */ 0,                                                                  \
/* TCR4 */ SET(I2S_TCR4_FRSZ_MASK)|SET(I2S_TCR4_SYWD(I2S_BIT_DEPTH-1))|        \
/*  ..  */ SET(I2S_TCR4_FSE_MASK)|SET(I2S_TCR4_FSD_MASK)|SET(I2S_TCR4_MF_MASK),\
/* TCR5 */ SET(I2S_TCR5_WNW(I2S_BIT_DEPTH-1))|                                 \
/*  ..  */ SET(I2S_TCR5_W0W(I2S_BIT_DEPTH-1))|SET(I2S_TCR5_FBT(0x0f)),         \
/* TDR0 */ 0,                                                                  \
/* TFR0 */ 0,                                                                  \
/* TMR  */ SET(I2S_TMR_TWM(0x0)),                                              \
/* RCSR */ 0,                                                                  \
/* RCR1 */ 0,                                                                  \
/* RCR2 */ CLR(I2S_RCR2_BCD_MASK)|                                             \
/*  ..  */ CLR(I2S_RCR2_BCP_MASK),                                             \
/* RCR3 */ 0,                                                                  \
/* RCR4 */ SET(I2S_RCR4_FRSZ_MASK)|SET(I2S_RCR4_SYWD(I2S_BIT_DEPTH-1))|        \
/*  ..  */ SET(I2S_RCR4_FSE_MASK)|CLR(I2S_RCR4_FSD_MASK)|SET(I2S_RCR4_MF_MASK),\
/* RCR5 */ SET(I2S_RCR5_WNW(I2S_BIT_DEPTH-1))|                                 \
/*  ..  */ SET(I2S_RCR5_W0W(I2S_BIT_DEPTH-1))|SET(I2S_RCR5_FBT(0x0f)),         \
/* RDR0 */ 0,                                                                  \
/* RFR0 */ 0,                                                                  \
/* RMR  */ SET(I2S_RMR_RWM(0x0)),                                              \
/* MCR  */ 0,                                                                  \
/* MDR  */ 0,                                                                  \
}         
/*! @} End of sai_config                                                      */

/******************************************************************************
* SAI callback used in SAI_Init() function
*
*//*! @addtogroup sai_callback
* @{
*******************************************************************************/
/*! @brief SAI_CALLBACK_SRC declaration                                       */
typedef enum 
{ 
    SAI0_CALLBACK=1,    ///< SAI0 interrupt
    SAI1_CALLBACK=2,    ///< SAI1 interrupt
} SAI_CALLBACK_SRC;

/*! @brief SAI_CALLBACK_TYPE declaration                                      */
typedef enum 
{
    TXSAI_CALLBACK=1,   ///< Tx FIFO IRQ
    RXSAI_CALLBACK=2,   ///< Rx FIFO IRQ
} SAI_CALLBACK_TYPE;

/*! @brief SAI_CALLBACK function declaration                                  */
typedef void (*SAI_CALLBACK)(SAI_CALLBACK_TYPE type);
/*! @} End of sai_callback                                                    */


/******************************************************************************
* SAI function and macro definitions
*
*//*! @addtogroup sai_macro
* @{
*******************************************************************************/

/***************************************************************************//*!
 * @brief   Macro disables SAI module. 
 * @param   module      - SAI0
 * @note    Implemented as function call.
 ******************************************************************************/
#define SAI_Disable(module)      module##_Disable()

/***************************************************************************//*!
 * @brief   Macro enables SAI module. 
 * @param   module      - SAI0
 * @note    Implemented as function call.
 ******************************************************************************/
#define SAI_Enable(module)       module##_Enable()

/***************************************************************************//*!
 * @brief   SAI module initialization function.
 * @param   module  - SAI0
 * @param   cfg     - SAI module configuration structure (@ref sai_config)
 * @param   srate   - audio samplerate i.e. 8.000kHz, 44.100kHz...
 * @param   ip      - interrupt priority 0..3
 * @param   callback- pointer to SAI_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define SAI_Init(module,cfg,srate,ip,callback)  module##_Init(cfg,srate,ip,callback)
/*! @} End of sai_macro                                                       */
  
/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern void SAI0_Init (tI2S i2s, uint32 srate, uint8 ip, SAI_CALLBACK pC1);
extern void SAI0_Enable(void);
extern void SAI0_Disable(void);
extern int SAI0_SetSampleRate(int smprate);
int SAI_GetSampleRateIx(int smprate);

#endif /* __SAI_H */ 
