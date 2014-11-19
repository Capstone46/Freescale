/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      uart.h
 * @version   1.0.8.0
 * @date      Feb-13-2013
 * @brief     Universal Asynchronous Receiver/Transmitter (UART) driver header 
 *            file.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	01/08/2012   B34185   Ported to Kinetis L
 *  3.	27/03/2014   B34185   UARTxx_MODULE_POOLMODE_CONFIG corrected 
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup uart_example0
 * @{
 * @par       Source code:
 * @include   uart0_test\uart0_test.c
 * @par       Appconfig.h:
 * @include   uart0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of uart_example0                                                   */
#ifndef __UART_H
#define __UART_H

#if (defined (MCU_MKL43Z256))
// just for backward compatibility
#define UART    UART0
#endif
 
/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct { uint8 BDH, BDL, C1, C2, S2, C3, MA1, MA2, C4, C5; } tUART;

/******************************************************************************
* UART flag definition
*
*//*! @addtogroup uart_flags
* @{
*******************************************************************************/
/* UART Flags                                                                 */
#define S1_PF          (uint32)(1 << 0)         ///< parity error flag
#define S1_FE          (uint32)(1 << 1)         ///< framing error flag
#define S1_NF          (uint32)(1 << 2)         ///< noise flag
#define S1_OR          (uint32)(1 << 3)         ///< receiver overrun flag
#define S1_IDLE        (uint32)(1 << 4)         ///< idle line flag
#define S2_RXEDGIF     (uint32)(1 << 14)        ///< RX pin active edge interrupt flag
#define S2_LBKDIF      (uint32)(1 << 15)        ///< LIN break detect interrupt flag
/*! @} End of uart_flags                                                      */

//br=57600; clk=96e6;
//sbr=floor((clk/(16*br)))
//brfa=round(((clk/(16*br))-floor((clk/(16*br))))*32)
#define CALC_SBR(brate,bclk)  (uint16)((double)bclk/(16.0*(double)brate))
#define CALC_BRFA(brate,bclk) (uint16)(((((double)bclk/(16.0*(double)brate))- \
                                      (double)CALC_SBR(brate,bclk))*32.0)+0.5)

// Single-wire TxD pin direction
#define PIN_IN          0
#define PIN_OUT         1
// Match address enable bits
#define MAEN1             0x80
#define MAEN2             0x40

/******************************************************************************
* UART default configurations used by UART_init() function
*
*//*! @addtogroup uart_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief Default UART configuration (disable module).
 *****************************************************************************/
#define UART_DISABLE_CONFIG  /* disable mode                  */ 							\
(tUART){                                                                      \
/* BDH      */ 0l,                              															\
/* BDL      */ 0x4l,                              														\
/* C1       */ CLR(UART_C1_LOOPS_MASK)|CLR(UART_C1_DOZEEN_MASK)|              \
               CLR(UART_C1_RSRC_MASK)|CLR(UART_C1_M_MASK)|                    \
               CLR(UART_C1_WAKE_MASK)|CLR(UART_C1_ILT_MASK)|                  \
               CLR(UART_C1_PE_MASK)|CLR(UART_C1_PT_MASK),                     \
/* C2       */ CLR(UART_C2_TIE_MASK)|CLR(UART_C2_TCIE_MASK)|                  \
               CLR(UART_C2_RIE_MASK)|CLR(UART_C2_ILIE_MASK)|                  \
               CLR(UART_C2_TE_MASK)|CLR(UART_C2_RE_MASK)|                     \
               CLR(UART_C2_RWU_MASK)|CLR(UART_C2_SBK_MASK),                   \
/* S2       */ SET(UART_S2_RXEDGIF_MASK)|CLR(UART_S2_MSBF_MASK)|              \
               CLR(UART_S2_RXINV_MASK)|CLR(UART_S2_RWUID_MASK)|               \
               CLR(UART_S2_BRK13_MASK),                                       \
/* C3       */ CLR(UART_C3_T8_MASK)|CLR(UART_C3_TXDIR_MASK)|                  \
               CLR(UART_C3_TXINV_MASK)|CLR(UART_C3_ORIE_MASK)|                \
               CLR(UART_C3_NEIE_MASK)|CLR(UART_C3_FEIE_MASK)|                 \
               CLR(UART_C3_PEIE_MASK),                                        \
/* MA1      */ 0l,                                                            \
/* MA2      */ 0l,                                                            \
/* C4       */ CLR(UART_C4_MEAN1(0))|CLR(UART_C4_MEAN1_MASK)|                 \
               CLR(UART_C4_M10_MASK),                                         \
/* C5       */ CLR(UART_C5_TDMAE_MASK)|CLR(UART_C5_RDMAE_MASK)|               \
               CLR(UART_C5_BOTHEDGE_MASK)|CLR(UART_C5_RESYNCDIS_MASK),        \
}

/**************************************************************************/ /*!
 * @brief General UART configuration (primarily for UART0) for polling mode. 
 * @param   brate     Baud rate.
 * @param   bclk      Buss clock in Hz.
 *****************************************************************************/
#define UART_MODULE_CONFIG1(brate,bclk)  /* pooling mode                  */ \
(tUART){                                                                      \
/* BDH      */ CLR(UART_BDH_RXEDGIE_MASK)|CLR(UART_BDH_SBNS_MASK)|            \
               ((CALC_SBR(brate,bclk)>>8)&0x1f),                              \
/* BDL      */ ((CALC_SBR(brate,bclk)>>0)&0xff),                              \
/* C1       */ CLR(UART_C1_LOOPS_MASK)|CLR(UART_C1_DOZEEN_MASK)|              \
               CLR(UART_C1_RSRC_MASK)|CLR(UART_C1_M_MASK)|                    \
               CLR(UART_C1_WAKE_MASK)|CLR(UART_C1_ILT_MASK)|                  \
               CLR(UART_C1_PE_MASK)|CLR(UART_C1_PT_MASK),                     \
/* C2       */ CLR(UART_C2_TIE_MASK)|CLR(UART_C2_TCIE_MASK)|                  \
               CLR(UART_C2_RIE_MASK)|CLR(UART_C2_ILIE_MASK)|                  \
               SET(UART_C2_TE_MASK)|SET(UART_C2_RE_MASK)|                     \
               CLR(UART_C2_RWU_MASK)|CLR(UART_C2_SBK_MASK),                   \
/* S2       */ CLR(UART_S2_RXEDGIF_MASK)|CLR(UART_S2_MSBF_MASK)|              \
               CLR(UART_S2_RXINV_MASK)|CLR(UART_S2_RWUID_MASK)|               \
               CLR(UART_S2_BRK13_MASK),                                       \
/* C3       */ CLR(UART_C3_T8_MASK)|CLR(UART_C3_TXDIR_MASK)|                  \
               CLR(UART_C3_TXINV_MASK)|CLR(UART_C3_ORIE_MASK)|                \
               CLR(UART_C3_NEIE_MASK)|CLR(UART_C3_FEIE_MASK)|                 \
               CLR(UART_C3_PEIE_MASK),                                        \
/* MA1      */ 0l,                                                            \
/* MA2      */ 0l,                                                            \
/* C4       */ CLR(UART_C4_MEAN1(0))|CLR(UART_C4_MEAN1_MASK)|                 \
               CLR(UART_C4_M10_MASK)|((CALC_BRFA(brate,bclk)>>0)&0x1f),       \
/* C5       */ CLR(UART_C5_TDMAE_MASK)|CLR(UART_C5_RDMAE_MASK)|               \
               CLR(UART_C5_BOTHEDGE_MASK)|CLR(UART_C5_RESYNCDIS_MASK),        \
}

// just for compatibility with older version
#define UART0_MODULE_CONFIG1(brate,bclk)                                      \
        UART0_MODULE_POLLMODE_CONFIG(brate,bclk)

/**************************************************************************/ /*!
 * @brief UART0 configuration for polling mode.
 * @param   brate     Baud rate.
 * @param   bclk      Buss clock in Hz.
 *****************************************************************************/
#define UART0_MODULE_POLLMODE_CONFIG(brate,bclk)  /* pooling mode          */ \
(tUART){                                                                      \
/* BDH      */ CLR(UART_BDH_RXEDGIE_MASK)|CLR(UART_BDH_SBNS_MASK)|            \
               ((CALC_SBR(brate,bclk)>>8)&0x1f),                              \
/* BDL      */ ((CALC_SBR(brate,bclk)>>0)&0xff),                              \
/* C1       */ CLR(UART_C1_LOOPS_MASK)|CLR(UART0_C1_UART0DOZEEN_MASK)|        \
               CLR(UART_C1_RSRC_MASK)|CLR(UART_C1_M_MASK)|                    \
               CLR(UART_C1_WAKE_MASK)|CLR(UART_C1_ILT_MASK)|                  \
               CLR(UART_C1_PE_MASK)|CLR(UART_C1_PT_MASK),                     \
/* C2       */ CLR(UART_C2_TIE_MASK)|CLR(UART_C2_TCIE_MASK)|                  \
               CLR(UART_C2_RIE_MASK)|CLR(UART_C2_ILIE_MASK)|                  \
               SET(UART_C2_TE_MASK)|SET(UART_C2_RE_MASK)|                     \
               CLR(UART_C2_RWU_MASK)|CLR(UART_C2_SBK_MASK),                   \
/* S2       */ CLR(UART_S2_RXEDGIF_MASK)|CLR(UART_S2_RXINV_MASK)|             \
               CLR(UART_S2_RWUID_MASK)|CLR(UART_S2_BRK13_MASK)|               \
               CLR(UART0_S2_LBKDE_MASK)|CLR(UART0_S2_RAF_MASK),               \
/* C3       */ CLR(UART_C3_T8_MASK)|CLR(UART_C3_TXDIR_MASK)|                  \
               CLR(UART_C3_TXINV_MASK)|CLR(UART_C3_ORIE_MASK)|                \
               CLR(UART_C3_NEIE_MASK)|CLR(UART_C3_FEIE_MASK)|                 \
               CLR(UART_C3_PEIE_MASK),                                        \
/* MA1      */ 0l,                                                            \
/* MA2      */ 0l,                                                            \
/* C4       */ CLR(UART0_C4_MAEN1_MASK)|CLR(UART0_C4_MAEN2_MASK)|             \
               CLR(UART0_C4_M10_MASK)|(0x0F&0x1f),                            \
/* C5       */ CLR(UART0_C5_TDMAE_MASK)|CLR(UART0_C5_RDMAE_MASK)|             \
               CLR(UART0_C5_BOTHEDGE_MASK)|CLR(UART0_C5_RESYNCDIS_MASK),      \
}

// just for compatibility with older version
#define UART_MODULE_POLLMODE_CONFIG(brate,bclk)                                \
        UART12_MODULE_POLLMODE_CONFIG(brate,bclk)      
#define UART_MODULE_POOLMODE_CONFIG(brate,bclk)                                \
        UART12_MODULE_POLLMODE_CONFIG(brate,bclk)

/**************************************************************************/ /*!
 * @brief Common UART1 and UART2 configuration for polling mode.
 * @param   brate     Baud rate.
 * @param   bclk      Buss clock in Hz.
 *****************************************************************************/
#define UART12_MODULE_POLLMODE_CONFIG(brate,bclk)  /* pooling mode         */ \
(tUART){                                                                      \
/* BDH      */ CLR(UART_BDH_RXEDGIE_MASK)|CLR(UART_BDH_SBNS_MASK)|            \
               ((CALC_SBR(brate,bclk)>>8)&0x1f),                              \
/* BDL      */ ((CALC_SBR(brate,bclk)>>0)&0xff),                              \
/* C1       */ CLR(UART_C1_LOOPS_MASK)|CLR(UART_C1_UARTSWAI_MASK)|            \
               CLR(UART_C1_RSRC_MASK)|CLR(UART_C1_M_MASK)|                    \
               CLR(UART_C1_WAKE_MASK)|CLR(UART_C1_ILT_MASK)|                  \
               CLR(UART_C1_PE_MASK)|CLR(UART_C1_PT_MASK),                     \
/* C2       */ CLR(UART_C2_TIE_MASK)|CLR(UART_C2_TCIE_MASK)|                  \
               CLR(UART_C2_RIE_MASK)|CLR(UART_C2_ILIE_MASK)|                  \
               SET(UART_C2_TE_MASK)|SET(UART_C2_RE_MASK)|                     \
               CLR(UART_C2_RWU_MASK)|CLR(UART_C2_SBK_MASK),                   \
/* S2       */ CLR(UART_S2_RXEDGIF_MASK)|                                     \
               CLR(UART_S2_RXINV_MASK)|CLR(UART_S2_RWUID_MASK)|               \
               CLR(UART_S2_BRK13_MASK),                                       \
/* C3       */ CLR(UART_C3_T8_MASK)|CLR(UART_C3_TXDIR_MASK)|                  \
               CLR(UART_C3_TXINV_MASK)|CLR(UART_C3_ORIE_MASK)|                \
               CLR(UART_C3_NEIE_MASK)|CLR(UART_C3_FEIE_MASK)|                 \
               CLR(UART_C3_PEIE_MASK),                                        \
/* MA1      */ 0l,                                                            \
/* MA2      */ 0l,                                                            \
/* C4       */ CLR(UART_C4_TDMAS_MASK)|CLR(UART_C4_RDMAS_MASK),               \
/* C5       */ 0l,                                                            \
}

/**************************************************************************/ /*!
 * @brief General UART configuration (for UART0 as well as for UART1, UART2)
 *        for interrupt mode.
 * @param   brate     Baud rate.
 * @param   bclk      Bus clock in Hz.
 *****************************************************************************/
#define UART0_MODULE_INTRMODE_CONFIG(brate,bclk) /* interrupts            */  \
(tUART){                                                                      \
/* BDH      */ CLR(UART_BDH_RXEDGIE_MASK)|CLR(UART_BDH_SBNS_MASK)|            \
               ((CALC_SBR(brate,bclk)>>8)&0x1f),                              \
/* BDL      */ ((CALC_SBR(brate,bclk)>>0)&0xff),                              \
/* C1       */ CLR(UART_C1_LOOPS_MASK)|CLR(UART0_C1_UART0DOZEEN_MASK)|        \
               CLR(UART_C1_RSRC_MASK)|CLR(UART_C1_M_MASK)|                    \
               CLR(UART_C1_WAKE_MASK)|CLR(UART_C1_ILT_MASK)|                  \
               CLR(UART_C1_PE_MASK)|CLR(UART_C1_PT_MASK),                     \
/* C2       */ CLR(UART_C2_TIE_MASK)|CLR(UART_C2_TCIE_MASK)|                  \
               SET(UART_C2_RIE_MASK)|CLR(UART_C2_ILIE_MASK)|                  \
               SET(UART_C2_TE_MASK)|SET(UART_C2_RE_MASK)|                     \
               CLR(UART_C2_RWU_MASK)|CLR(UART_C2_SBK_MASK),                   \
/* S2       */ CLR(UART_S2_RXEDGIF_MASK)|CLR(UART_S2_RXINV_MASK)|             \
               CLR(UART_S2_RWUID_MASK)|CLR(UART_S2_BRK13_MASK)|               \
               CLR(UART0_S2_LBKDE_MASK)|CLR(UART0_S2_RAF_MASK),               \
/* C3       */ CLR(UART_C3_T8_MASK)|CLR(UART_C3_TXDIR_MASK)|                  \
               CLR(UART_C3_TXINV_MASK)|CLR(UART_C3_ORIE_MASK)|                \
               CLR(UART_C3_NEIE_MASK)|CLR(UART_C3_FEIE_MASK)|                 \
               CLR(UART_C3_PEIE_MASK),                                        \
/* MA1      */ 0l,                                                            \
/* MA2      */ 0l,                                                            \
/* C4       */ CLR(UART0_C4_MAEN1_MASK)|CLR(UART0_C4_MAEN2_MASK)|             \
               CLR(UART0_C4_M10_MASK)|(0x0F&0x1f),                            \
/* C5       */ CLR(UART0_C5_TDMAE_MASK)|CLR(UART0_C5_RDMAE_MASK)|             \
               CLR(UART0_C5_BOTHEDGE_MASK)|CLR(UART0_C5_RESYNCDIS_MASK),      \
}

// just for compatibility with older version
#define UART_MODULE_INTRMODE_CONFIG(brate,bclk)                                \
        UART12_MODULE_INTRMODE_CONFIG(brate,bclk)

/**************************************************************************/ /*!
 * @brief General UART configuration (for UART0 as well as for UART1, UART2)
 *        for interrupt mode.
 * @param   brate     Baud rate.
 * @param   bclk      Bus clock in Hz.
 *****************************************************************************/
#define UART12_MODULE_INTRMODE_CONFIG(brate,bclk) /* interrupts           */  \
(tUART){                                                                      \
/* BDH      */ CLR(UART_BDH_RXEDGIE_MASK)|CLR(UART_BDH_SBNS_MASK)|            \
               ((CALC_SBR(brate,bclk)>>8)&0x1f),                              \
/* BDL      */ ((CALC_SBR(brate,bclk)>>0)&0xff),                              \
/* C1       */ CLR(UART_C1_LOOPS_MASK)|CLR(UART_C1_UARTSWAI_MASK)|            \
               CLR(UART_C1_RSRC_MASK)|CLR(UART_C1_M_MASK)|                    \
               CLR(UART_C1_WAKE_MASK)|CLR(UART_C1_ILT_MASK)|                  \
               CLR(UART_C1_PE_MASK)|CLR(UART_C1_PT_MASK),                     \
/* C2       */ CLR(UART_C2_TIE_MASK)|CLR(UART_C2_TCIE_MASK)|                  \
               SET(UART_C2_RIE_MASK)|CLR(UART_C2_ILIE_MASK)|                  \
               SET(UART_C2_TE_MASK)|SET(UART_C2_RE_MASK)|                     \
               CLR(UART_C2_RWU_MASK)|CLR(UART_C2_SBK_MASK),                   \
/* S2       */ CLR(UART_S2_RXEDGIF_MASK)|                                     \
               CLR(UART_S2_RXINV_MASK)|CLR(UART_S2_RWUID_MASK)|               \
               CLR(UART_S2_BRK13_MASK),                                       \
/* C3       */ CLR(UART_C3_T8_MASK)|CLR(UART_C3_TXDIR_MASK)|                  \
               CLR(UART_C3_TXINV_MASK)|CLR(UART_C3_ORIE_MASK)|                \
               CLR(UART_C3_NEIE_MASK)|CLR(UART_C3_FEIE_MASK)|                 \
               CLR(UART_C3_PEIE_MASK),                                        \
/* MA1      */ 0l,                                                            \
/* MA2      */ 0l,                                                            \
/* C4       */ CLR(UART_C4_TDMAS_MASK)|CLR(UART_C4_RDMAS_MASK),               \
/* C5       */ 0l,                                                            \
}
/*! @} End of uart_config                                                     */

/******************************************************************************
* UART callback used by UART_Init() function
*
*//*! @addtogroup uart_callback
* @{
*******************************************************************************/
/*! @brief UART_CALLBACK source declaration                                   */
typedef enum 
{
  TX_CALLBACK=1, 
  RX_CALLBACK=2, 
  ER_CALLBACK=4
} UART_CALLBACK_TYPE;
/*! UART_CALLBACK function declaration                                        */
typedef void (*UART_CALLBACK)(UART_CALLBACK_TYPE eType, int8 status);
/*! @} End of uart_callback                                                   */ 

/******************************************************************************
* UART function and macro definitions
*
*//*! @addtogroup uart_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro disables transmit interrupt request for specified module.
 * @param   module  - UART0|UART1|UART2 (for KLx5|KLx6) and UART0 (for KLx3)
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_TxIsrDisable(module)   module##_C2 &=~UART_C2_TIE_MASK 

/***************************************************************************//*!
 * @brief   Macro enables transmit interrupt request for specified module.
 * @param   module  - UART0|UART1|UART2 (for KLx5|KLx6) and UART0 (for KLx3)
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_TxIsrEnable(module)    module##_C2 |= UART_C2_TIE_MASK

/***************************************************************************//*!
 * @brief   Macro reads character.
 * @param   module  - UART0|UART1|UART2 (for KLx5|KLx6) and UART0 (for KLx3)
 * @return  Received character.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_GetChar(module)        module##_D

/***************************************************************************//*!
 * @brief   Macro sends character.
 * @param   module  - UART0|UART1|UART2 (for KLx5|KLx6) and UART0 (for KLx3)
 * @param   c       - character to be sent
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_PutChar(module,c)      module##_D = (c)

/***************************************************************************//*!
 * @brief   Macro returns transmitter state.
 * @param   module  - UART0|UART1|UART2 (for KLx5|KLx6) and UART0 (for KLx3)
 * @return  FALSE   - transmitter busy 
 * @return  TRUE    - transmitter idle
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_TxIdle(module)        (module##_S1 & UART_S1_TDRE_MASK)

/***************************************************************************//*!
 * @brief   Macro returns receiver state.
 * @param   module  - UART0|UART1|UART2 (for KLx5|KLx6) and UART0 (for KLx3)
 * @return  FALSE   - no character available 
 * @return  TRUE    - character ready
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_RxFull(module)        (module##_S1 & UART_S1_RDRF_MASK)

/***************************************************************************//*!
 * @brief   Macro returns trasfer complete state.
 * @param   module  - UART0|UART1|UART2 (for KLx5|KLx6) and UART0 (for KLx3)
 * @return  FALSE   - character transmit non-complete 
 * @return  TRUE    - character transmit complete
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_TxComplete(module)    (module##_S1 & UART_S1_TC_MASK)

/***************************************************************************//*!
 * @brief  Macro clears UART flags.
 * @param   module  - UART0
 * @param  mask    - S1_PF|S1_FE|S1_NF|S1_OR|S1_IDLE|S1_LBKDIF|S1_RXDIGF or 
 *                   use alternatively 0xC01F to clear all flags.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_ClrFlags(module, mask)                                            \
                              {                                                \
                                module##_S2 |= (uint8)((mask>>8)&0xC0);        \
                                module##_S1 |= (uint8)((mask>>0)&0x1f);        \
                              }

/***************************************************************************//*!
 * @brief   Macro sends string..
 * @param   module  - UART0|UART1|UART2 (for KLx5|KLx6) and UART0 (for KLx3)
 * @param   str     - NULL terminated string.
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_PutStr(module,str)     {                                         \
                                      register uint16 i=0;                    \
                                      while(str[i] != 0)                      \
                                      {                                       \
                                        while (!UART_TxIdle(module));         \
                                        UART_PutChar(module,str[i]);          \
                                        i++;                                  \
                                      }                                       \
                                      while (!UART_TxComplete(module));       \
                                    }                                        

/***************************************************************************//*!
 * @brief   Macro disables loop mode.
 * @param   module  - UART0|UART1|UART2
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_LoopDisable(module)   module##_C1 &=~UART_C1_LOOPS_MASK

/***************************************************************************//*!
 * @brief   Macro enable loop mode.
 * @param   module  - UART0|UART1|UART2
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_LoopEnable(module)   module##_C1 |= UART_C1_LOOPS_MASK 

/***************************************************************************//*!
 * @brief   Macro enable single-wire mode.
 * @param   module  - UART0|UART1|UART2
 * @param   dir  - PIN_IN (TxD pin is as input)
 * @param   dir  - PIN_OUT (TxD pin is as output)
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_SingleWireEnable(module,dir)                                       \
                                        {                                       \
                                        module##_C1 |= (UART_C1_LOOPS_MASK|     \
                                                       UART_C1_RSRC_MASK);      \
                                        REG_SetVal(module##_C3,UART_C3_TXDIR,   \
                                        (dir&0x01));                            \
                                        }

/***************************************************************************//*!
 * @brief   Macro disable single-wire mode.
 * @param   module  - UART0|UART1|UART2
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_SingleWireDisable(module)                                           \
                                        {                                       \
                                        module##_C1 &= ~(UART_C1_LOOPS_MASK|    \
                                                       UART_C1_RSRC_MASK);      \
                                        module##_C3 &= ~UART_C3_TXDIR_MASK;     \
                                        }

/***************************************************************************//*!
 * @brief   Macro disable match address mode.
 * @param   module  - UART0
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_MatchAdrDisable(module)                                            \
                                        {                                       \
                                        module##_C4 &= ~(module##_C4_MAEN1_MASK|   \
                                                       module##_C4_MAEN2_MASK);    \
                                        module##_MA1 = 0x00;                    \
                                        module##_MA2 = 0x00;                    \
                                        }

/***************************************************************************//*!
 * @brief   Macro enable match address mode.
 * @param   module  - UART0
 * @param   ma  - MAEN1|MAEN2
 * @param   adr1  - address of first match
 * @param   adr2  - address of second match
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define UART_MatchAdrConfig(module, ma, adr1, adr2)                             \
                                  {                                             \
                                  module##_C4 |= (uint8)ma;                     \
                                  module##_MA1 = ((ma&MAEN1)?(uint8)adr1:0x00); \
                                  module##_MA2 = ((ma&MAEN2)?(uint8)adr2:0x00); \
                                  }

/* Function redefinition                                                      */
#if (defined (MCU_MKL43Z256))
/***************************************************************************//*!
 * @brief   UART initialization function.
 * @param   module  - UART|UART0
 * @param   cfg     - UART module configuration structure passed by value: 
 *                    UART_MODULE_POOLMODE_CONFIG(brate,bclk),
 *                    UART_MODULE_INTRMODE_CONFIG(brate,bclk),
 *                    where "brate" is baud rate [Bd] and "bclk" bus clock speed
 *                    [Hz]
 * @param   ip      - interrupt priority 0..3
 * @param   callback- pointer to UART_CALLBACK function
 * @return  none
 * @note    Implemented as function call. Be careful with UART1, 2 
 *          configuration macros inplementation here.
 ******************************************************************************/
#define UART_Init(module,cfg,ip,callback)   module##_KLx3_Init(cfg,ip,callback)
/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern void UART_KLx3_Init (tUART sci, uint8 ip, UART_CALLBACK pCallback);
extern void UART0_KLx3_Init (tUART sci, uint8 ip, UART_CALLBACK pCallback);
#else
/***************************************************************************//*!
 * @brief   UART initialization function.
 * @param   module  - UART0|UART1|UART2 (depend on device used)
 * @param   cfg     - UART module configuration structure passed by value: 
 *                    UART0_MODULE_POOLMODE_CONFIG(brate,bclk),
 *                    UART12_MODULE_POOLMODE_CONFIG(brate,bclk),
 *                    UART0_MODULE_INTRMODE_CONFIG(brate,bclk),
 *                    UART12_MODULE_INTRMODE_CONFIG(brate,bclk),
 *                    where "brate" is baud rate [Bd] and "bclk" bus clock speed
 *                    [Hz]
 * @param   ip      - interrupt priority 0..3
 * @param   callback- pointer to UART_CALLBACK function
 * @return  none
 * @note    Implemented as function call. Be careful with UART0 and UART1, 2 
 *          configuration macros inplementation here.
 ******************************************************************************/
#define UART_Init(module,cfg,ip,callback)   module##_Init(cfg,ip,callback)

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/   
extern void UART0_Init (tUART sci, uint8 ip, UART_CALLBACK pCallback);
extern void UART1_Init (tUART sci, uint8 ip, UART_CALLBACK pCallback);
extern void UART2_Init (tUART sci, uint8 ip, UART_CALLBACK pCallback);
#endif
/*! @} End of uart_macro                                                      */

#endif /* __UART_H */ 
