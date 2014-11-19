/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      lpuart.h
 * @version   1.0.8.0
 * @date      Feb-13-2013
 * @brief     Low Power Universal Asynchronous Receiver/Transmitter (UART)  
 *            driver header file.
 *
 * Revision History:
 *  1.	07/0/2010   B34185   Initially written
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup lpuart_example0
 * @{
 * @par       Source code:
 * @include   lpuart0_test\lpuart0_test.c
 * @par       Appconfig.h:
 * @include   lpuart0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of lpuart_example0                                                 */
#ifndef __LPUART_H
#define __LPUART_H 
 
#if (defined (MCU_MKL43Z256))
/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct { uint32 BAUD, STAT, CTRL, MATCH; } tLPUART;

/******************************************************************************
* LPUART flag definition
*
*//*! @addtogroup lpuart_flags
* @{
*******************************************************************************/
/* UART Flags                                                                 */
#define STAT_MA2F        (uint32)(1 << 14)         ///< match 2 error flag
#define STAT_MA1F        (uint32)(1 << 15)         ///< match 1 error flag
#define STAT_PF          (uint32)(1 << 16)         ///< parity error flag
#define STAT_FE          (uint32)(1 << 17)         ///< framing error flag
#define STAT_NF          (uint32)(1 << 18)         ///< noise flag
#define STAT_OR          (uint32)(1 << 19)         ///< receiver overrun flag
#define STAT_IDLE        (uint32)(1 << 20)         ///< idle line flag
#define STAT_RXEDGIF     (uint32)(1 << 30)         ///< RX pin active edge interrupt flag
#define STAT_LBKDIF      (uint32)(1 << 31)         ///< LIN break detect interrupt flag
#define STAT_ALL         (uint32)(0xC01FC000)      ///< all flags mask
/*! @} End of lpuart_flags                                                      */

//br=57600; clk=96e6;
//sbr=floor((clk/(16*br)))
//brfa=round(((clk/(16*br))-floor((clk/(16*br))))*32)
#define CALC_SBR(brate,bclk)  (uint16)((double)bclk/(16.0*(double)brate))
#define CALC_BRFA(brate,bclk) (uint16)(((((double)bclk/(16.0*(double)brate))- \
                                      (double)CALC_SBR(brate,bclk))*32.0)+0.5)

/******************************************************************************
* LPUART Single-wire TxD pin direction
*
*//*! @addtogroup lpuart_pindir
* @{
*******************************************************************************/
#define LPUART_PIN_IN          0
#define LPUART_PIN_OUT         1
/*! @} End of lpuart_pindir                                                   */

/******************************************************************************
* LPUART Match address enable bits.
*
*//*! @addtogroup lpuart_matchen
* @{
*******************************************************************************/
#define LPUART_MAEN1             0x80000000
#define LPUART_MAEN2             0x40000000
/*! @} End of lpuart_matchen                                                  */

/******************************************************************************
* LPUART break charecter generation length.
*
*//*! @addtogroup lpuart_breakcharlength
* @{
*******************************************************************************/
#define BRK13_SHORT             0x0
#define BRK13_LONG              0x1
/*! @} End of lpuart_breakcharlength                                                  */


/******************************************************************************
* LPUART default configurations used by LPUART_init() function
*
*//*! @addtogroup lpuart_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief LPUART disables configuration.
 *****************************************************************************/
#define LPUART_DISABLE_CONFIG                     /* disable mode          */  \
(tLPUART){                                                                      \
/* BAUD     */ CLR(LPUART_BAUD_MAEN1_MASK)|CLR(LPUART_BAUD_MAEN2_MASK)|         \
               CLR(LPUART_BAUD_M10_MASK)|                                       \
               CLR(LPUART_BAUD_TDMAE_MASK)|CLR(LPUART_BAUD_RDMAE_MASK)|         \
               SET(LPUART_BAUD_MATCFG(0x0))|CLR(LPUART_BAUD_BOTHEDGE_MASK)|     \
               CLR(LPUART_BAUD_RESSYNCDIS_MASK)|CLR(LPUART_BAUD_LBKDIE_MASK)|   \
               CLR(LPUART_BAUD_RXEDGIE)|CLR(LPUART_BAUD_SBNS_MASK),             \
/* STAT     */ CLR(LPUART_STAT_MSBF_MASK)|CLR(LPUART_STAT_RXINV_MASK)|          \
               CLR(LPUART_STAT_RWUID_MASK)|CLR(LPUART_STAT_BRK13_MASK)|         \
               CLR(LPUART_STAT_LBKDE_MASK),                                     \
/* CTRL     */ CLR(LPUART_CTRL_R8T9_MASK)|CLR(LPUART_CTRL_R9T8_MASK)|           \
               CLR(LPUART_CTRL_TXDIR_MASK)|CLR(LPUART_CTRL_TXINV_MASK)|         \
               CLR(LPUART_CTRL_ORIE_MASK)|CLR(LPUART_CTRL_NEIE_MASK)|           \
               CLR(LPUART_CTRL_FEIE_MASK)|CLR(LPUART_CTRL_PEIE_MASK)|           \
               CLR(LPUART_CTRL_TIE_MASK)|CLR(LPUART_CTRL_TCIE_MASK)|            \
               CLR(LPUART_CTRL_RIE_MASK)|CLR(LPUART_CTRL_ILIE_MASK)|            \
               CLR(LPUART_CTRL_TE_MASK)|CLR(LPUART_CTRL_RE_MASK)|               \
               CLR(LPUART_CTRL_RWU_MASK)|CLR(LPUART_CTRL_SBK_MASK)|             \
               CLR(LPUART_CTRL_MA1IE_MASK)|CLR(LPUART_CTRL_MA2IE_MASK)|         \
               SET(LPUART_CTRL_IDLECFG(0x0))|CLR(LPUART_CTRL_LOOPS_MASK)|       \
               CLR(LPUART_CTRL_DOZEEN_MASK)|CLR(LPUART_CTRL_RSRC_MASK)|         \
               CLR(LPUART_CTRL_M_MASK)|CLR(LPUART_CTRL_WAKE_MASK)|              \
               CLR(LPUART_CTRL_ILT_MASK)|CLR(LPUART_CTRL_PE_MASK)|              \
               CLR(LPUART_CTRL_PT_MASK),                                        \
/* MATCH    */ SET(LPUART_MATCH_MA2(0x0))|SET(LPUART_MATCH_MA1(0x0)),           \
}

/**************************************************************************/ /*!
 * @brief General LPUART configuration for polling mode. 
 * @param   brate     Baud rate.
 * @param   bclk      Buss clock in Hz.
 *****************************************************************************/
#define LPUART_POLLMODE_CONFIG(brate,bclk)                                      \
(tLPUART){                                                                      \
/* BAUD     */ CLR(LPUART_BAUD_MAEN1_MASK)|CLR(LPUART_BAUD_MAEN2_MASK)|         \
               CLR(LPUART_BAUD_M10_MASK)|((CALC_BRFA(brate,bclk)<<23)&0x1f000000)|\
               CLR(LPUART_BAUD_TDMAE_MASK)|CLR(LPUART_BAUD_RDMAE_MASK)|         \
               SET(LPUART_BAUD_MATCFG(0x0))|CLR(LPUART_BAUD_BOTHEDGE_MASK)|     \
               CLR(LPUART_BAUD_RESSYNCDIS_MASK)|CLR(LPUART_BAUD_LBKDIE_MASK)|   \
               CLR(LPUART_BAUD_RXEDGIE)|CLR(LPUART_BAUD_SBNS_MASK)|             \
               (CALC_SBR(brate,bclk)&0x1FFF),                                   \
/* STAT     */ CLR(LPUART_STAT_MSBF_MASK)|CLR(LPUART_STAT_RXINV_MASK)|          \
               CLR(LPUART_STAT_RWUID_MASK)|CLR(LPUART_STAT_BRK13_MASK)|         \
               CLR(LPUART_STAT_LBKDE_MASK),                                     \
/* CTRL     */ CLR(LPUART_CTRL_R8T9_MASK)|CLR(LPUART_CTRL_R9T8_MASK)|           \
               CLR(LPUART_CTRL_TXDIR_MASK)|CLR(LPUART_CTRL_TXINV_MASK)|         \
               CLR(LPUART_CTRL_ORIE_MASK)|CLR(LPUART_CTRL_NEIE_MASK)|           \
               CLR(LPUART_CTRL_FEIE_MASK)|CLR(LPUART_CTRL_PEIE_MASK)|           \
               CLR(LPUART_CTRL_TIE_MASK)|CLR(LPUART_CTRL_TCIE_MASK)|            \
               CLR(LPUART_CTRL_RIE_MASK)|CLR(LPUART_CTRL_ILIE_MASK)|            \
               SET(LPUART_CTRL_TE_MASK)|SET(LPUART_CTRL_RE_MASK)|               \
               CLR(LPUART_CTRL_RWU_MASK)|CLR(LPUART_CTRL_SBK_MASK)|             \
               CLR(LPUART_CTRL_MA1IE_MASK)|CLR(LPUART_CTRL_MA2IE_MASK)|         \
               SET(LPUART_CTRL_IDLECFG(0x0))|CLR(LPUART_CTRL_LOOPS_MASK)|       \
               CLR(LPUART_CTRL_DOZEEN_MASK)|CLR(LPUART_CTRL_RSRC_MASK)|         \
               CLR(LPUART_CTRL_M_MASK)|CLR(LPUART_CTRL_WAKE_MASK)|              \
               CLR(LPUART_CTRL_ILT_MASK)|CLR(LPUART_CTRL_PE_MASK)|              \
               CLR(LPUART_CTRL_PT_MASK),                                        \
/* MATCH    */ SET(LPUART_MATCH_MA2(0x0))|SET(LPUART_MATCH_MA1(0x0)),           \
}

/**************************************************************************/ /*!
 * @brief   General LPUART configuration for interrupt mode. Receive data 
 *          register full flag will cause IRQ.
 * @param   brate     Baud rate.
 * @param   bclk      Buss clock in Hz.
 *****************************************************************************/
#define LPUART_RDRF_IRQ_CONFIG(brate,bclk)         /* IRQ mode          */     \
(tLPUART){                                                                      \
/* BAUD     */ CLR(LPUART_BAUD_MAEN1_MASK)|CLR(LPUART_BAUD_MAEN2_MASK)|         \
               CLR(LPUART_BAUD_M10_MASK)|((CALC_BRFA(brate,bclk)<<23)&0x1f000000)|\
               CLR(LPUART_BAUD_TDMAE_MASK)|CLR(LPUART_BAUD_RDMAE_MASK)|         \
               SET(LPUART_BAUD_MATCFG(0x0))|CLR(LPUART_BAUD_BOTHEDGE_MASK)|     \
               CLR(LPUART_BAUD_RESSYNCDIS_MASK)|CLR(LPUART_BAUD_LBKDIE_MASK)|   \
               CLR(LPUART_BAUD_RXEDGIE)|CLR(LPUART_BAUD_SBNS_MASK)|             \
               (CALC_SBR(brate,bclk)&0x1FFF),                                   \
/* STAT     */ CLR(LPUART_STAT_MSBF_MASK)|CLR(LPUART_STAT_RXINV_MASK)|          \
               CLR(LPUART_STAT_RWUID_MASK)|CLR(LPUART_STAT_BRK13_MASK)|         \
               CLR(LPUART_STAT_LBKDE_MASK),                                     \
/* CTRL     */ CLR(LPUART_CTRL_R8T9_MASK)|CLR(LPUART_CTRL_R9T8_MASK)|           \
               CLR(LPUART_CTRL_TXDIR_MASK)|CLR(LPUART_CTRL_TXINV_MASK)|         \
               CLR(LPUART_CTRL_ORIE_MASK)|CLR(LPUART_CTRL_NEIE_MASK)|           \
               CLR(LPUART_CTRL_FEIE_MASK)|CLR(LPUART_CTRL_PEIE_MASK)|           \
               CLR(LPUART_CTRL_TIE_MASK)|CLR(LPUART_CTRL_TCIE_MASK)|            \
               SET(LPUART_CTRL_RIE_MASK)|CLR(LPUART_CTRL_ILIE_MASK)|            \
               SET(LPUART_CTRL_TE_MASK)|SET(LPUART_CTRL_RE_MASK)|               \
               CLR(LPUART_CTRL_RWU_MASK)|CLR(LPUART_CTRL_SBK_MASK)|             \
               CLR(LPUART_CTRL_MA1IE_MASK)|CLR(LPUART_CTRL_MA2IE_MASK)|         \
               SET(LPUART_CTRL_IDLECFG(0x0))|CLR(LPUART_CTRL_LOOPS_MASK)|       \
               CLR(LPUART_CTRL_DOZEEN_MASK)|CLR(LPUART_CTRL_RSRC_MASK)|         \
               CLR(LPUART_CTRL_M_MASK)|CLR(LPUART_CTRL_WAKE_MASK)|              \
               CLR(LPUART_CTRL_ILT_MASK)|CLR(LPUART_CTRL_PE_MASK)|              \
               CLR(LPUART_CTRL_PT_MASK),                                        \
/* MATCH    */ SET(LPUART_MATCH_MA2(0x0))|SET(LPUART_MATCH_MA1(0x0)),           \
}

/**************************************************************************/ /*!
 * @brief   General LPUART configuration for receive DMA mode. Receive data 
 *          register full flag will cause DMA request.
 * @param   brate     Baud rate.
 * @param   bclk      Buss clock in Hz.
 *****************************************************************************/
#define LPUART_RDRF_DMA_CONFIG(brate,bclk)         /* DMA mode          */     \
(tLPUART){                                                                      \
/* BAUD     */ CLR(LPUART_BAUD_MAEN1_MASK)|CLR(LPUART_BAUD_MAEN2_MASK)|         \
               CLR(LPUART_BAUD_M10_MASK)|((CALC_BRFA(brate,bclk)<<23)&0x1f000000)|\
               CLR(LPUART_BAUD_TDMAE_MASK)|SET(LPUART_BAUD_RDMAE_MASK)|         \
               SET(LPUART_BAUD_MATCFG(0x0))|CLR(LPUART_BAUD_BOTHEDGE_MASK)|     \
               CLR(LPUART_BAUD_RESSYNCDIS_MASK)|CLR(LPUART_BAUD_LBKDIE_MASK)|   \
               CLR(LPUART_BAUD_RXEDGIE)|CLR(LPUART_BAUD_SBNS_MASK)|             \
               (CALC_SBR(brate,bclk)&0x1FFF),                                   \
/* STAT     */ CLR(LPUART_STAT_MSBF_MASK)|CLR(LPUART_STAT_RXINV_MASK)|          \
               CLR(LPUART_STAT_RWUID_MASK)|CLR(LPUART_STAT_BRK13_MASK)|         \
               CLR(LPUART_STAT_LBKDE_MASK),                                     \
/* CTRL     */ CLR(LPUART_CTRL_R8T9_MASK)|CLR(LPUART_CTRL_R9T8_MASK)|           \
               CLR(LPUART_CTRL_TXDIR_MASK)|CLR(LPUART_CTRL_TXINV_MASK)|         \
               CLR(LPUART_CTRL_ORIE_MASK)|CLR(LPUART_CTRL_NEIE_MASK)|           \
               CLR(LPUART_CTRL_FEIE_MASK)|CLR(LPUART_CTRL_PEIE_MASK)|           \
               CLR(LPUART_CTRL_TIE_MASK)|CLR(LPUART_CTRL_TCIE_MASK)|            \
               SET(LPUART_CTRL_RIE_MASK)|CLR(LPUART_CTRL_ILIE_MASK)|            \
               SET(LPUART_CTRL_TE_MASK)|SET(LPUART_CTRL_RE_MASK)|               \
               CLR(LPUART_CTRL_RWU_MASK)|CLR(LPUART_CTRL_SBK_MASK)|             \
               CLR(LPUART_CTRL_MA1IE_MASK)|CLR(LPUART_CTRL_MA2IE_MASK)|         \
               SET(LPUART_CTRL_IDLECFG(0x0))|CLR(LPUART_CTRL_LOOPS_MASK)|       \
               CLR(LPUART_CTRL_DOZEEN_MASK)|CLR(LPUART_CTRL_RSRC_MASK)|         \
               CLR(LPUART_CTRL_M_MASK)|CLR(LPUART_CTRL_WAKE_MASK)|              \
               CLR(LPUART_CTRL_ILT_MASK)|CLR(LPUART_CTRL_PE_MASK)|              \
               CLR(LPUART_CTRL_PT_MASK),                                        \
/* MATCH    */ SET(LPUART_MATCH_MA2(0x0))|SET(LPUART_MATCH_MA1(0x0)),           \
}

/**************************************************************************/ /*!
 * @brief   General LPUART configuration for transmitt DMA mode. Transmit data
 *          register empty flag will cause DMA request.
 * @param   brate     Baud rate.
 * @param   bclk      Buss clock in Hz.
 *****************************************************************************/
#define LPUART_TDRE_DMA_CONFIG(brate,bclk)         /* DMA mode          */     \
(tLPUART){                                                                      \
/* BAUD     */ CLR(LPUART_BAUD_MAEN1_MASK)|CLR(LPUART_BAUD_MAEN2_MASK)|         \
               CLR(LPUART_BAUD_M10_MASK)|((CALC_BRFA(brate,bclk)<<23)&0x1f000000)|\
               SET(LPUART_BAUD_TDMAE_MASK)|CLR(LPUART_BAUD_RDMAE_MASK)|         \
               SET(LPUART_BAUD_MATCFG(0x0))|CLR(LPUART_BAUD_BOTHEDGE_MASK)|     \
               CLR(LPUART_BAUD_RESSYNCDIS_MASK)|CLR(LPUART_BAUD_LBKDIE_MASK)|   \
               CLR(LPUART_BAUD_RXEDGIE)|CLR(LPUART_BAUD_SBNS_MASK)|             \
               (CALC_SBR(brate,bclk)&0x1FFF),                                   \
/* STAT     */ CLR(LPUART_STAT_MSBF_MASK)|CLR(LPUART_STAT_RXINV_MASK)|          \
               CLR(LPUART_STAT_RWUID_MASK)|CLR(LPUART_STAT_BRK13_MASK)|         \
               CLR(LPUART_STAT_LBKDE_MASK),                                     \
/* CTRL     */ CLR(LPUART_CTRL_R8T9_MASK)|CLR(LPUART_CTRL_R9T8_MASK)|           \
               CLR(LPUART_CTRL_TXDIR_MASK)|CLR(LPUART_CTRL_TXINV_MASK)|         \
               CLR(LPUART_CTRL_ORIE_MASK)|CLR(LPUART_CTRL_NEIE_MASK)|           \
               CLR(LPUART_CTRL_FEIE_MASK)|CLR(LPUART_CTRL_PEIE_MASK)|           \
               SET(LPUART_CTRL_TIE_MASK)|CLR(LPUART_CTRL_TCIE_MASK)|            \
               CLR(LPUART_CTRL_RIE_MASK)|CLR(LPUART_CTRL_ILIE_MASK)|            \
               SET(LPUART_CTRL_TE_MASK)|SET(LPUART_CTRL_RE_MASK)|               \
               CLR(LPUART_CTRL_RWU_MASK)|CLR(LPUART_CTRL_SBK_MASK)|             \
               CLR(LPUART_CTRL_MA1IE_MASK)|CLR(LPUART_CTRL_MA2IE_MASK)|         \
               SET(LPUART_CTRL_IDLECFG(0x0))|CLR(LPUART_CTRL_LOOPS_MASK)|       \
               CLR(LPUART_CTRL_DOZEEN_MASK)|CLR(LPUART_CTRL_RSRC_MASK)|         \
               CLR(LPUART_CTRL_M_MASK)|CLR(LPUART_CTRL_WAKE_MASK)|              \
               CLR(LPUART_CTRL_ILT_MASK)|CLR(LPUART_CTRL_PE_MASK)|              \
               CLR(LPUART_CTRL_PT_MASK),                                        \
/* MATCH    */ SET(LPUART_MATCH_MA2(0x0))|SET(LPUART_MATCH_MA1(0x0)),           \
}

/**************************************************************************/ /*!
 * @brief   General LPUART configuration for DMA mode. Receive data 
 *          register full flag and transmitt data register empty will cause 
 *          DMA request.
 * @param   brate     Baud rate.
 * @param   bclk      Buss clock in Hz.
 *****************************************************************************/
#define LPUART_RDRF_TDRE_DMA_CONFIG(brate,bclk)         /* DMA mode          */   \
(tLPUART){                                                                      \
/* BAUD     */ CLR(LPUART_BAUD_MAEN1_MASK)|CLR(LPUART_BAUD_MAEN2_MASK)|         \
               CLR(LPUART_BAUD_M10_MASK)|((CALC_BRFA(brate,bclk)<<23)&0x1f000000)|\
               SET(LPUART_BAUD_TDMAE_MASK)|SET(LPUART_BAUD_RDMAE_MASK)|         \
               SET(LPUART_BAUD_MATCFG(0x0))|CLR(LPUART_BAUD_BOTHEDGE_MASK)|     \
               CLR(LPUART_BAUD_RESSYNCDIS_MASK)|CLR(LPUART_BAUD_LBKDIE_MASK)|   \
               CLR(LPUART_BAUD_RXEDGIE)|CLR(LPUART_BAUD_SBNS_MASK)|             \
               (CALC_SBR(brate,bclk)&0x1FFF),                                   \
/* STAT     */ CLR(LPUART_STAT_MSBF_MASK)|CLR(LPUART_STAT_RXINV_MASK)|          \
               CLR(LPUART_STAT_RWUID_MASK)|CLR(LPUART_STAT_BRK13_MASK)|         \
               CLR(LPUART_STAT_LBKDE_MASK),                                     \
/* CTRL     */ CLR(LPUART_CTRL_R8T9_MASK)|CLR(LPUART_CTRL_R9T8_MASK)|           \
               CLR(LPUART_CTRL_TXDIR_MASK)|CLR(LPUART_CTRL_TXINV_MASK)|         \
               CLR(LPUART_CTRL_ORIE_MASK)|CLR(LPUART_CTRL_NEIE_MASK)|           \
               CLR(LPUART_CTRL_FEIE_MASK)|CLR(LPUART_CTRL_PEIE_MASK)|           \
               SET(LPUART_CTRL_TIE_MASK)|CLR(LPUART_CTRL_TCIE_MASK)|            \
               SET(LPUART_CTRL_RIE_MASK)|CLR(LPUART_CTRL_ILIE_MASK)|            \
               SET(LPUART_CTRL_TE_MASK)|SET(LPUART_CTRL_RE_MASK)|               \
               CLR(LPUART_CTRL_RWU_MASK)|CLR(LPUART_CTRL_SBK_MASK)|             \
               CLR(LPUART_CTRL_MA1IE_MASK)|CLR(LPUART_CTRL_MA2IE_MASK)|         \
               SET(LPUART_CTRL_IDLECFG(0x0))|CLR(LPUART_CTRL_LOOPS_MASK)|       \
               CLR(LPUART_CTRL_DOZEEN_MASK)|CLR(LPUART_CTRL_RSRC_MASK)|         \
               CLR(LPUART_CTRL_M_MASK)|CLR(LPUART_CTRL_WAKE_MASK)|              \
               CLR(LPUART_CTRL_ILT_MASK)|CLR(LPUART_CTRL_PE_MASK)|              \
               CLR(LPUART_CTRL_PT_MASK),                                        \
/* MATCH    */ SET(LPUART_MATCH_MA2(0x0))|SET(LPUART_MATCH_MA1(0x0)),           \
}
/*! @} End of lpuart_config                                                     */

/******************************************************************************
* LPUART callback used by LPUART_Init() function
*
*//*! @addtogroup lpuart_callback
* @{
*******************************************************************************/
/*! @brief LPUART_CALLBACK source declaration                                   */
typedef enum 
{
  LPUART_TX_CALLBACK=1, 
  LPUART_RX_CALLBACK=2, 
  LPUART_ER_CALLBACK=4
} LPUART_CALLBACK_TYPE;
/*! LPUART_CALLBACK function declaration                                        */
typedef void (*LPUART_CALLBACK)(LPUART_CALLBACK_TYPE type, int32 status);
/*! @} End of lpuart_callback                                                   */ 

/******************************************************************************
* LPUART function and macro definitions
*
*//*! @addtogroup lpuart_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro disables receiver interrupt.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_ParityDisable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_PE,0x0);

/***************************************************************************//*!
 * @brief   Macro enables receiver interrupt.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_ParityEnable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_PE,0x1);

/***************************************************************************//*!
 * @brief   Macro enables odd parity.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_SetOddParity(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_PT,0x1);

/***************************************************************************//*!
 * @brief   Macro enables even parity.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_SetEvenParity(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_PT,0x0);

/***************************************************************************//*!
 * @brief   Macro enables 9 bit mode.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_Set9BitMode(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_M,0x1);

/***************************************************************************//*!
 * @brief   Macro enables 8 bit mode.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_Set8BitMode(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_M,0x0);

/***************************************************************************//*!
 * @brief   Macro disables receiver interrupt.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_RxIrqDisable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_RIE,0x0);

/***************************************************************************//*!
 * @brief   Macro enables receiver interrupt.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_RxIrqEnable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_RIE,0x1);

/***************************************************************************//*!
 * @brief   Macro disables transmitter interrupt.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_TxIrqDisable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_TIE,0x0);

/***************************************************************************//*!
 * @brief   Macro enables transmitter interrupt.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_TxIrqEnable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_TIE,0x1);

/***************************************************************************//*!
 * @brief   Macro disables transmitt complete interrupt.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_TxCIrqDisable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_TCIE,0x0);

/***************************************************************************//*!
 * @brief   Macro enables transmitt complete interrupt.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_TxCIrqEnable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_TCIE,0x1);

/***************************************************************************//*!
 * @brief   Macro disables receiver.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_RxDisable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_RE,0x0);

/***************************************************************************//*!
 * @brief   Macro enables receiver.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_RxEnable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_RE,0x1);

/***************************************************************************//*!
 * @brief   Macro disables transmitter.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_TxDisable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_TE,0x0);

/***************************************************************************//*!
 * @brief   Macro enables transmitter.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_TxEnable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_TE,0x1);

/***************************************************************************//*!
 * @brief   Macro disables MSB bit first.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_MSBFirstDisable(module)   REG_SetVal(##module##_STAT,LPUART_STAT_MSBF,0x0);

/***************************************************************************//*!
 * @brief   Macro enables MSB bit first.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_MSBFirstEnable(module)   REG_SetVal(##module##_STAT,LPUART_STAT_MSBF,0x1);

/***************************************************************************//*!
 * @brief   Macro disables receive data inversion.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_RxInvDisable(module)   REG_SetVal(##module##_STAT,LPUART_STAT_RXINV,0x0);

/***************************************************************************//*!
 * @brief   Macro enables receive data inversion.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_RxInvEnable(module)   REG_SetVal(##module##_STAT,LPUART_STAT_RXINV,0x1);

/***************************************************************************//*!
 * @brief   Macro disables receive wake up idle detect.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_RxWakeupIdleDisable(module)   REG_SetVal(##module##_STAT,LPUART_STAT_RWUID,0x0);

/***************************************************************************//*!
 * @brief   Macro enables receive wake up idle detect.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_RxWakeupIdleEnable(module)   REG_SetVal(##module##_STAT,LPUART_STAT_RWUID,0x1);

/***************************************************************************//*!
 * @brief   Macro disables receive wake up idle detect.
 * @param   module  - LPUART0|LPUART1
 * @param   module  - @ref lpuart_breakcharlength
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_BreakCharLength(module, length)   REG_SetVal(##module##_STAT,LPUART_STAT_RWUID,length);

/***************************************************************************//*!
 * @brief   Macro disables receive wake up idle detect.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_LINBreakDisable(module)   REG_SetVal(##module##_STAT,LPUART_STAT_LBKDE,0x0);

/***************************************************************************//*!
 * @brief   Macro enables receive wake up idle detect.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_LINBreakEnable(module)   REG_SetVal(##module##_STAT,LPUART_STAT_LBKDE,0x1);

/***************************************************************************//*!
 * @brief   Macro disables transmit interrupt request for specified module.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_TxIrqDisable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_TIE,0x0);

/***************************************************************************//*!
 * @brief   Macro enables transmit interrupt request for specified module.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_TxIrqEnable(module)    REG_SetVal(##module##_CTRL,LPUART_CTRL_TIE,0x1);

/***************************************************************************//*!
 * @brief   Macro reads character.
 * @param   module  - LPUART0|LPUART1
 * @return  Received character.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_GetChar(module)        (uint8)(module##_DATA&0xFF)

/***************************************************************************//*!
 * @brief   Macro reads 10-bits data.
 * @param   module  - LPUART0|LPUART1
 * @return  Received data - 16 bit word.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_GetData(module)        (uint16)(module##_DATA&0x3FF)

/***************************************************************************//*!
 * @brief   Macro sends character.
 * @param   module  - LPUART0|LPUART1
 * @param   c       - character to be sent
 * @return  none
 * @note    Implemented as inlined macro.
 * @warning FRETSC bit is affected.
 ******************************************************************************/
#define LPUART_PutChar(module,c)          module##_DATA = (uint32)(c)

/***************************************************************************//*!
 * @brief   Macro sends data.
 * @param   module  - LPUART0|LPUART1
 * @param   c       - 10 bit data to be sent
 * @return  none
 * @note    Implemented as inlined macro.
 * @warning FRETSC bit is affected.
 ******************************************************************************/
#define LPUART_PutData(module,c)          module##_DATA = (uint32)(c)

/***************************************************************************//*!
 * @brief   Macro returns transmitter state.
 * @param   module  - LPUART0|LPUART1
 * @return  FALSE   - transmitter busy 
 * @return  TRUE    - transmitter idle
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_TxIdle(module)        (module##_STAT & LPUART_STAT_TDRE_MASK)

/***************************************************************************//*!
 * @brief   Macro returns receiver state.
 * @param   module  - LPUART0|LPUART1
 * @return  FALSE   - no character available 
 * @return  TRUE    - character ready
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_RxFull(module)        (module##_STAT & LPUART_STAT_RDRF_MASK)

/***************************************************************************//*!
 * @brief   Macro returns trasfer complete state.
 * @param   module  - LPUART0|LPUART1
 * @return  FALSE   - character transmit non-complete 
 * @return  TRUE    - character transmit complete
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_TxComplete(module)    (module##_STAT & LPUART_STAT_TC_MASK)

/***************************************************************************//*!
 * @brief   Macro clears LPUART flags.
 * @param   module  - LPUART0|LPUART1
 * @param   mask    - @ref lpuart_flags.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_ClrFlags(module, mask)  module##_STAT |= (uint32)(mask&0xC01FC000);

/***************************************************************************//*!
 * @brief   Macro sends string..
 * @param   module  - LPUART0|LPUART1
 * @param   str     - NULL terminated string.
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_PutStr(module,str)     {                                         \
                                      register uint16 i=0;                      \
                                      while(str[i] != 0)                        \
                                      {                                         \
                                        while (!LPUART_TxIdle(module));         \
                                        LPUART_PutChar(module,str[i]);          \
                                        i++;                                    \
                                      }                                         \
                                      while (!LPUART_TxComplete(module));       \
                                      }                                    

/***************************************************************************//*!
 * @brief   Macro disables loop mode.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_LoopDisable(module)   REG_SetVal(##module##_CTRL,LPUART_CTRL_LOOPS,0x0);

/***************************************************************************//*!
 * @brief   Macro enable loop mode.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_LoopEnable(module)      REG_SetVal(##module##_CTRL,LPUART_CTRL_LOOPS,0x1);

/***************************************************************************//*!
 * @brief   Macro enable single-wire mode.
 * @param   module  - LPUART0|LPUART1
 * @param   dir  - @ref lpuart_pindir
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_SingleWireEnable(module,dir)                                       \
                                        {                                       \
                                        module##_CTRL |=                        \
                                                      (LPUART_CTRL_LOOPS_MASK|  \
                                                       LPUART_CTRL_RSRC_MASK);  \
                                        REG_SetVal(module##_CTRL,LPUART_CTRL_TXDIR,\
                                        (dir&0x01));                            \
                                        }

/***************************************************************************//*!
 * @brief   Macro disable single-wire mode.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_SingleWireDisable(module)  {                                       \
                                        module##_CTRL &=                        \
                                                     ~(LPUART_CTRL_LOOPS_MASK|  \
                                                       LPUART_CTRL_RSRC_MASK|   \
                                                       LPUART_CTRL_TXDIR_MASK); \
                                        }

/***************************************************************************//*!
 * @brief   Macro disable match address mode.
 * @param   module  - LPUART0|LPUART1
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_MatchAdrDisable(module)                                          \
                   {                                                            \
                    module##_BAUD &= ~(LPUART_BAUD_MAEN1_MASK|LPUART_BAUD_MAEN2_MASK);\
                    module##_MATCH = 0x00;                                      \
                    }

/***************************************************************************//*!
 * @brief   Macro enable match address mode.
 * @param   module  - LPUART0|LPUART1
 * @param   ma  - @ref lpuart_matchen
 * @param   adr1  - address of first match
 * @param   adr2  - address of second match
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define LPUART_MatchAdrConfig(module, ma, adr1, adr2)                           \
                          {                                                     \
                          module##_BAUD = (ma)|(module##_BAUD&0x3FFFFFFF);      \
                          REG_SetVal(module##_MATCH,LPUART_MATCH_MA1,adr1);     \
                          REG_SetVal(module##_MATCH,LPUART_MATCH_MA2,adr2);     \
                          }

/* Function redefinition                                                      */
/***************************************************************************//*!
 * @brief   LPUART initialization function.
 * @param   module  - LPUART0|LPUART1
 * @param   cfg     - @ref lpuart_config
 * @param   ip      - interrupt priority 0..3
 * @param   callback- pointer to LPUART_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define LPUART_Init(module,cfg,ip,callback)   module##_Init(cfg,ip,callback)
/*! @} End of lpuart_macro                                                      */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/   
extern void LPUART0_Init (tLPUART sci, uint8 ip, LPUART_CALLBACK pCallback);
extern void LPUART1_Init (tLPUART sci, uint8 ip, LPUART_CALLBACK pCallback);

#endif

#endif /* __LPUART_H */ 
