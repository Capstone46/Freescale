/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      dma.h
 * @version   1.0.6.0
 * @date      Feb-22-2013
 * @brief     Direct memory access (DMA) driver header file.
 *
 * Revision History:
 *  1.	15/01/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup dma_example0
 * @{
 * @par       Source code:
 * @include   dma0_test\dma0_test.c
 * @par       Appconfig.h:
 * @include   dma0_test\appconfig.h   
 ******************************************************************************/
/*! @} End of dma_example0                                                    */
#ifndef __DMA_H
#define __DMA_H 

/******************************************************************************
 * DMAMUX definition configuration structure                                     *
 ******************************************************************************/
typedef struct { uint32 MUX_CHCFG; }tDMAMUX;

/******************************************************************************
 * DMA definition configuration structure                                     *
 ******************************************************************************/
typedef struct { uint32 BCR, DCR; }tDMA;
 
/******************************************************************************
* DMA channel source definition for use with DMAMUXx_Init() macro.
*
*//*! @addtogroup dma_channelsrc
* @{
*******************************************************************************/
#define DMA_SRC_DISABLE         0       ///< DMA channel disable
#define DMA_SRC_UART0_RX        2       ///< UART0 receive (async DMA capable)
#define DMA_SRC_UART0_TX        3       ///< UART0 transmit (async DMA capable)
#define DMA_SRC_UART1_RX        4       ///< UART1 receive
#define DMA_SRC_UART1_TX        5       ///< UART1 transmit
#define DMA_SRC_UART2_RX        6       ///< UART2 receive
#define DMA_SRC_UART2_TX        7       ///< UART2 transmit
#define DMA_SRC_SPI0_RX         16      ///< SPI0 receive
#define DMA_SRC_SPI0_TX         17      ///< SPI0 transmit
#define DMA_SRC_SPI1_RX         18      ///< SPI1 receive
#define DMA_SRC_SPI1_TX         19      ///< SPI1 transmit
#define DMA_SRC_I2C0            22      ///< I2C0
#define DMA_SRC_I2C1            23      ///< I2C1
#define DMA_SRC_TPM0_CH0        24      ///< TPM0 channel 0 (async DMA capable)
#define DMA_SRC_TPM0_CH1        25      ///< TPM0 channel 1 (async DMA capable)
#define DMA_SRC_TPM0_CH2        26      ///< TPM0 channel 2 (async DMA capable)
#define DMA_SRC_TPM0_CH3        27      ///< TPM0 channel 3 (async DMA capable)
#define DMA_SRC_TPM0_CH4        28      ///< TPM0 channel 4 (async DMA capable)
#define DMA_SRC_TPM0_CH5        29      ///< TPM0 channel 5 (async DMA capable)
#define DMA_SRC_TPM1_CH0        32      ///< TPM1 channel 0 (async DMA capable)
#define DMA_SRC_TPM1_CH1        33      ///< TPM1 channel 1 (async DMA capable)
#define DMA_SRC_TPM2_CH0        34      ///< TPM2 channel 0 (async DMA capable)
#define DMA_SRC_TPM2_CH1        35      ///< TPM2 channel 1 (async DMA capable)
#define DMA_SRC_ADC0            40      ///< ADC0 (async DMA capable)
#define DMA_SRC_CPM             42      ///< CMP0 (async DMA capable)
#define DMA_SRC_DAC0            45      ///< DAC0
#define DMA_SRC_PORTA           49      ///< PORTA control module (async DMA capable)
#define DMA_SRC_PORTD           52      ///< PORTD control module (async DMA capable)
#define DMA_SRC_TPM0_OVF        54      ///< TPM0 overflow (async DMA capable)
#define DMA_SRC_TPM1_OVF        55      ///< TPM0 overflow (async DMA capable)
#define DMA_SRC_TPM2_OVF        56      ///< TPM0 overflow (async DMA capable)
#define DMA_SRC_TSI             57      ///< TSI (async DMA capable)
#define DMA_SRC_DMA_MUX_AE0     60      ///< DMA MUX always enabled
#define DMA_SRC_DMA_MUX_AE1     62
#define DMA_SRC_DMA_MUX_AE2     63
#define DMA_SRC_DMA_MUX_AE3     64
/*! @} End of dma_channelsrc                                                  */

/******************************************************************************
* DMA transfer size macro.
*
*//*! @addtogroup dma_transfersize
* @{
*******************************************************************************/
#define DMA_LONGWORD      0             ///< long word transfer
#define DMA_BYTE          1             ///< byte word transfer
#define DMA_WORD          2             ///< word transfer
/*! @} End of dma_transfersize                                                */

/******************************************************************************
* DMA multiplexer configurations used by DMAMUXx_init() function
*
*//*! @addtogroup dmamux_config
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   DMA channel enable with channel source selection.
 * @param   src  - DMA channel source (@ref dma_channelsrc)
 * @note    Implemented as function call.
 ******************************************************************************/
#define DMAMUX_CONFIG1(src)                                                    \
(tDMAMUX){                                                                     \
/* MUX_CFG */ SET(DMAMUX_CHCFG_ENBL_MASK)|CLR(DMAMUX_CHCFG_TRIG_MASK)|         \
              SET(DMAMUX_CHCFG_SOURCE(src)),                                   \
}

#define DMAMUX_NORMAL_CONFIG(src)       DMAMUX_CONFIG1(src)

/***************************************************************************//*!
 * @brief   DMA channel disable with channel source selection.
 * @param   src  - DMA channel source (@ref dma_channelsrc)
 * @note    Implemented as function call.
 ******************************************************************************/
#define DMAMUX_CH_DISABLE_CONFIG(src)                                          \
(tDMAMUX){                                                                     \
/* MUX_CFG */ CLR(DMAMUX_CHCFG_ENBL_MASK)|CLR(DMAMUX_CHCFG_TRIG_MASK)|         \
              SET(DMAMUX_CHCFG_SOURCE(src)),                                   \
}

/***************************************************************************//*!
 * @brief   DMA channel enable with periodic trig. and channel source selection.
 * @param   src  - DMA channel source (@ref dma_channelsrc)
 * @note    Implemented as function call.
 ******************************************************************************/
#define DMAMUX_TRGIGGER_CONFIG(src)                                            \
(tDMAMUX){                                                                     \
/* MUX_CFG */ SET(DMAMUX_CHCFG_ENBL_MASK)|SET(DMAMUX_CHCFG_TRIG_MASK)|         \
              SET(DMAMUX_CHCFG_SOURCE(src)),                                   \
}
/*! @} End of dmamux_config                                                   */

/******************************************************************************
* DMA controller module configurations used by DMA_init() function
*
*//*! @addtogroup dma_config
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   DMA transfer from one source to destination buffer.
 * @param   bcnt  - number of bytes to be transfered in block (up to 0xFFFFF)
 * @param   ssize  - source transfer size (@ref dma_transfersize)
 * @param   dsize  - destination transfer size (@ref dma_transfersize)
 * @note    Implemented as function call.
 ******************************************************************************/
#define DMA_DINC_SINGLE_ERQ_IRQ_CONFIG(bcnt,ssize,dsize)                       \
(tDMA){                                                                        \
/* BCR     */ SET(DMA_DSR_BCR_BCR(bcnt)),                                      \
/* DCR     */ SET(DMA_DCR_EINT_MASK)|SET(DMA_DCR_CS_MASK)|CLR(DMA_DCR_AA_MASK)|\
              CLR(DMA_DCR_EADREQ_MASK)|CLR(DMA_DCR_SINC_MASK)|                 \
              SET(DMA_DCR_SSIZE(ssize))|SET(DMA_DCR_DINC_MASK)|                \
              SET(DMA_DCR_DSIZE(dsize))|CLR(DMA_DCR_START_MASK)|               \
              SET(DMA_DCR_SMOD(0))|SET(DMA_DCR_DMOD(0))|                       \
              CLR(DMA_DCR_D_REQ_MASK)|SET(DMA_DCR_LINKCC(0))|                  \
              SET(DMA_DCR_LCH1(0))|SET(DMA_DCR_LCH2(0))|SET(DMA_DCR_ERQ_MASK), \
}

/***************************************************************************//*!
 * @brief   DMA transfer from source buffer to one destination.
 * @param   bcnt  - number of bytes to be transfered in block (up to 0xFFFFF)
 * @param   ssize  - source transfer size (@ref dma_transfersize)
 * @param   dsize  - destination transfer size (@ref dma_transfersize)
 * @note    Implemented as function call.
 ******************************************************************************/
#define DMA_SINC_SINGLE_ERQ_IRQ_CONFIG(bcnt,ssize,dsize)                       \
(tDMA){                                                                        \
/* BCR     */ SET(DMA_DSR_BCR_BCR(bcnt)),                                      \
/* DCR     */ SET(DMA_DCR_EINT_MASK)|SET(DMA_DCR_CS_MASK)|CLR(DMA_DCR_AA_MASK)|\
              CLR(DMA_DCR_EADREQ_MASK)|SET(DMA_DCR_SINC_MASK)|                 \
              SET(DMA_DCR_SSIZE(ssize))|CLR(DMA_DCR_DINC_MASK)|                \
              SET(DMA_DCR_DSIZE(dsize))|CLR(DMA_DCR_START_MASK)|               \
              SET(DMA_DCR_SMOD(0))|SET(DMA_DCR_DMOD(0))|                       \
              CLR(DMA_DCR_D_REQ_MASK)|SET(DMA_DCR_LINKCC(0))|                  \
              SET(DMA_DCR_LCH1(0))|SET(DMA_DCR_LCH2(0))|SET(DMA_DCR_ERQ_MASK), \
}

/***************************************************************************//*!
 * @brief   DMA transfer from one source to one destination.
 * @param   bcnt  - number of bytes to be transfered in block (up to 0xFFFFF)
 * @param   ssize  - source transfer size (@ref dma_transfersize)
 * @param   dsize  - destination transfer size (@ref dma_transfersize)
 * @note    Implemented as function call.
 ******************************************************************************/
#define DMA_SINGLE_ERQ_IRQ_CONFIG(bcnt,ssize,dsize)                       		\
(tDMA){                                                                        \
/* BCR     */ SET(DMA_DSR_BCR_BCR(bcnt)),                                      \
/* DCR     */ SET(DMA_DCR_EINT_MASK)|SET(DMA_DCR_CS_MASK)|CLR(DMA_DCR_AA_MASK)|\
              CLR(DMA_DCR_EADREQ_MASK)|CLR(DMA_DCR_SINC_MASK)|                 \
              SET(DMA_DCR_SSIZE(ssize))|CLR(DMA_DCR_DINC_MASK)|                \
              SET(DMA_DCR_DSIZE(dsize))|CLR(DMA_DCR_START_MASK)|               \
              SET(DMA_DCR_SMOD(0))|SET(DMA_DCR_DMOD(0))|                       \
              CLR(DMA_DCR_D_REQ_MASK)|SET(DMA_DCR_LINKCC(0))|                  \
              SET(DMA_DCR_LCH1(0))|SET(DMA_DCR_LCH2(0))|SET(DMA_DCR_ERQ_MASK), \
}

/***************************************************************************//*!
 * @brief   Asynchronous DMA transfer from one source to destination buffer.
 * @param   bcnt  - number of bytes to be transfered in block (up to 0xFFFFF)
 * @param   ssize  - source transfer size (@ref dma_transfersize)
 * @param   dsize  - destination transfer size (@ref dma_transfersize)
 * @note    Implemented as function call.
 ******************************************************************************/
#define DMA_ASYNC_DINC_SINGLE_ERQ_IRQ_CONFIG(bcnt,ssize,dsize)                 \
(tDMA){                                                                        \
/* BCR     */ SET(DMA_DSR_BCR_BCR(bcnt)),                                      \
/* DCR     */ SET(DMA_DCR_EINT_MASK)|SET(DMA_DCR_CS_MASK)|CLR(DMA_DCR_AA_MASK)|\
              SET(DMA_DCR_EADREQ_MASK)|CLR(DMA_DCR_SINC_MASK)|                 \
              SET(DMA_DCR_SSIZE(ssize))|SET(DMA_DCR_DINC_MASK)|                \
              SET(DMA_DCR_DSIZE(dsize))|CLR(DMA_DCR_START_MASK)|               \
              SET(DMA_DCR_SMOD(0))|SET(DMA_DCR_DMOD(0))|                       \
              CLR(DMA_DCR_D_REQ_MASK)|SET(DMA_DCR_LINKCC(0))|                  \
              SET(DMA_DCR_LCH1(0))|SET(DMA_DCR_LCH2(0))|SET(DMA_DCR_ERQ_MASK), \
}

/***************************************************************************//*!
 * @brief   Asynchronous DMA transfer from source buffer to one destination.
 * @param   bcnt  - number of bytes to be transfered in block (up to 0xFFFFF)
 * @param   ssize  - source transfer size (@ref dma_transfersize)
 * @param   dsize  - destination transfer size (@ref dma_transfersize)
 * @note    Implemented as function call.
 ******************************************************************************/
#define DMA_ASYNC_SINC_SINGLE_ERQ_IRQ_CONFIG(bcnt,ssize,dsize)                 \
(tDMA){                                                                        \
/* BCR     */ SET(DMA_DSR_BCR_BCR(bcnt)),                                      \
/* DCR     */ SET(DMA_DCR_EINT_MASK)|SET(DMA_DCR_CS_MASK)|CLR(DMA_DCR_AA_MASK)|\
              SET(DMA_DCR_EADREQ_MASK)|SET(DMA_DCR_SINC_MASK)|                 \
              SET(DMA_DCR_SSIZE(ssize))|CLR(DMA_DCR_DINC_MASK)|                \
              SET(DMA_DCR_DSIZE(dsize))|CLR(DMA_DCR_START_MASK)|               \
              SET(DMA_DCR_SMOD(0))|SET(DMA_DCR_DMOD(0))|                       \
              CLR(DMA_DCR_D_REQ_MASK)|SET(DMA_DCR_LINKCC(0))|                  \
              SET(DMA_DCR_LCH1(0))|SET(DMA_DCR_LCH2(0))|SET(DMA_DCR_ERQ_MASK), \
}

/***************************************************************************//*!
 * @brief   DMA transfer from source buffer to destination buffer.
 * @param   bcnt  - number of bytes to be transfered in block (up to 0xFFFFF)
 * @param   ssize  - source transfer size (@ref dma_transfersize)
 * @param   dsize  - destination transfer size (@ref dma_transfersize)
 * @note    Implemented as function call.
 ******************************************************************************/
#define DMA_SINC_DINC_SINGLE_ERQ_IRQ_CONFIG(bcnt,ssize,dsize)                  \
(tDMA){                                                                        \
/* BCR     */ SET(DMA_DSR_BCR_BCR(bcnt)),                                      \
/* DCR     */ SET(DMA_DCR_EINT_MASK)|SET(DMA_DCR_CS_MASK)|CLR(DMA_DCR_AA_MASK)|\
              CLR(DMA_DCR_EADREQ_MASK)|SET(DMA_DCR_SINC_MASK)|                 \
              SET(DMA_DCR_SSIZE(ssize))|SET(DMA_DCR_DINC_MASK)|                \
              SET(DMA_DCR_DSIZE(dsize))|CLR(DMA_DCR_START_MASK)|               \
              SET(DMA_DCR_SMOD(0))|SET(DMA_DCR_DMOD(0))|                       \
              CLR(DMA_DCR_D_REQ_MASK)|SET(DMA_DCR_LINKCC(0))|                  \
              SET(DMA_DCR_LCH1(0))|SET(DMA_DCR_LCH2(0))|SET(DMA_DCR_ERQ_MASK), \
}
/*! @} End of dma_config                                                      */

/******************************************************************************
* DMA callback used in DMA_Init() function
*
*//*! @addtogroup dma_callback
* @{
*******************************************************************************/
typedef enum {
              CH0_CALLBACK=1,   ///< DMA channel 0 
              CH1_CALLBACK=2,   ///< DMA channel 1
              CH2_CALLBACK=3,   ///< DMA channel 2
              CH3_CALLBACK=4    ///< DMA channel 3
             } DMA_CALLBACK_TYPE;
/*! DMA_CALLBACK function declaration                                         */
typedef void (*DMA_CALLBACK)(DMA_CALLBACK_TYPE type);
/*! @} End of dma_callback                                                    */

/******************************************************************************
* DMA function and macro definitions
*
*//*! @addtogroup dma_macro
* @{
*******************************************************************************/
#define DMA_DMA0_Disable(inp)     REG_SetVal(DMAMUX0_CHCFG0, DMAMUX_CHCFG_ENBL,0)
#define DMA_DMA1_Disable(inp)     REG_SetVal(DMAMUX0_CHCFG1, DMAMUX_CHCFG_ENBL,0)
#define DMA_DMA2_Disable(inp)     REG_SetVal(DMAMUX0_CHCFG2, DMAMUX_CHCFG_ENBL,0)
#define DMA_DMA3_Disable(inp)     REG_SetVal(DMAMUX0_CHCFG3, DMAMUX_CHCFG_ENBL,0)
/***************************************************************************//*!
 * @brief   Macro disables DMA channel (for DMAMUX reconfiguration). 
 * @param   channel - DMA0|DMA1|DMA2|DMA3
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DMA_Disable(channel)       DMA_##channel##_Disable()

#define DMA_DMA0_Enable(inp)      REG_SetVal(DMAMUX0_CHCFG0, DMAMUX_CHCFG_ENBL,1)
#define DMA_DMA1_Enable(inp)      REG_SetVal(DMAMUX0_CHCFG1, DMAMUX_CHCFG_ENBL,1)
#define DMA_DMA2_Enable(inp)      REG_SetVal(DMAMUX0_CHCFG2, DMAMUX_CHCFG_ENBL,1)
#define DMA_DMA3_Enable(inp)      REG_SetVal(DMAMUX0_CHCFG3, DMAMUX_CHCFG_ENBL,1)
/***************************************************************************//*!
 * @brief   Macro enables DMA channel. 
 * @param   channel      - DMA0|DMA1|DMA2|DMA3
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DMA_Enable(channel)       DMA_##channel##_Enable()

#define DMA_DMA0_Start(inp)      REG_SetVal(DMA_DCR0, DMA_DCR_START,1)
#define DMA_DMA1_Start(inp)      REG_SetVal(DMA_DCR1, DMA_DCR_START,1)
#define DMA_DMA2_Start(inp)      REG_SetVal(DMA_DCR2, DMA_DCR_START,1)
#define DMA_DMA3_Start(inp)      REG_SetVal(DMA_DCR3, DMA_DCR_START,1)
/***************************************************************************//*!
 * @brief   Macro starts DMA transfer independently on peripheral request.
 * @param   channel      - DMA0|DMA1|DMA2|DMA3
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DMA_Start(channel)       DMA_##channel##_Start()

#define DMA_DMA0_SourceAdr(adr)      REG_SetVal(DMA_SAR0, DMA_SAR_SAR,adr)
#define DMA_DMA1_SourceAdr(adr)      REG_SetVal(DMA_SAR1, DMA_SAR_SAR,adr)
#define DMA_DMA2_SourceAdr(adr)      REG_SetVal(DMA_SAR2, DMA_SAR_SAR,adr)
#define DMA_DMA3_SourceAdr(adr)      REG_SetVal(DMA_SAR3, DMA_SAR_SAR,adr)
/***************************************************************************//*!
 * @brief   Macro sets DMA source address.
 * @param   channel      - DMA0|DMA1|DMA2|DMA3
 * @param   adr      - source address (aligned on a 0-modulo-ssize boundary)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DMA_SourceAdr(channel,adr)       DMA_##channel##_SourceAdr(adr)

#define DMA_DMA0_DestinationAdr(adr)      REG_SetVal(DMA_DAR0, DMA_DAR_DAR,adr)
#define DMA_DMA1_DestinationAdr(adr)      REG_SetVal(DMA_DAR1, DMA_DAR_DAR,adr)
#define DMA_DMA2_DestinationAdr(adr)      REG_SetVal(DMA_DAR2, DMA_DAR_DAR,adr)
#define DMA_DMA3_DestinationAdr(adr)      REG_SetVal(DMA_DAR3, DMA_DAR_DAR,adr)
/***************************************************************************//*!
 * @brief   Macro sets DMA source address.
 * @param   channel      - DMA0|DMA1|DMA2|DMA3
 * @param   adr      - source address (aligned on a 0-modulo-ssize boundary)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DMA_DestinationAdr(channel,adr)       DMA_##channel##_DestinationAdr(adr)

/* Function redefinition                                                      */
/***************************************************************************//*!
 * @brief   DMAMUX0 initialization function.
 * @param   channel  - CH0|CH1|CH2|CH3
 * @param   cfg  - DMAMUX configuration structure (@ref dmamux_config)
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define DMAMUX0_Init(channel,cfg)             DMAMUX0_##channel##_Init(cfg)

/***************************************************************************//*!
 * @brief   DMA module initialization function.
 * @param   channel  - DMA0|DMA1|DMA2|DMA3
 * @param   cfg     - DMA module configuration structure (@ref dma_config)
 * @param   sadr    - source address
 * @param   dadr    - destination address
 * @param   ip      - interrupt priority 0..3
 * @param   callback- pointer to DMA_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define DMA_Init(channel,cfg,sadr,dadr,ip,callback)  channel##_Init(cfg,sadr,dadr,ip,callback)
/*! @} End of dma_macro                                                       */
  
/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern void DMAMUX0_CH0_Init(tDMAMUX dmamux); 
extern void DMAMUX0_CH1_Init(tDMAMUX dmamux); 
extern void DMAMUX0_CH2_Init(tDMAMUX dmamux); 
extern void DMAMUX0_CH3_Init(tDMAMUX dmamux);

extern void DMA0_Init(tDMA dma, uint32* sard, uint32* dadr, uint8 ip, DMA_CALLBACK pCallback);
extern void DMA1_Init(tDMA dma, uint32* sard, uint32* dadr, uint8 ip, DMA_CALLBACK pCallback); 
extern void DMA2_Init(tDMA dma, uint32* sard, uint32* dadr, uint8 ip, DMA_CALLBACK pCallback); 
extern void DMA3_Init(tDMA dma, uint32* sard, uint32* dadr, uint8 ip, DMA_CALLBACK pCallback); 
#endif /* __DMA_H */ 
