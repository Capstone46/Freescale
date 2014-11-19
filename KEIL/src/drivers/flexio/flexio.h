/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flexio.h
 * @version   1.0.9.0
 * @date      May-22-2013
 * @brief     FlexIO module driver header file.
 *
 * Revision History:
 *  1.	15/01/2014   B34185   Initially written for Kinetis L
 *  2.	18/03/2014   B34185   The shifter buffer initialization not provided in init func.
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup flexio_example0
 * @{
 * @par       Source code:
 * @include   flexio0_test\flexio0_test.c
 * @par       Appconfig.h:
 * @include   flexio0_test\appconfig.h
 ******************************************************************************/
/*! @} End of flexio_example0                                                 */
#ifndef __FLEXIO_H
#define __FLEXIO_H

/******************************************************************************
 * FLEXIO definition configuration structure                                  *
 ******************************************************************************/
typedef struct { uint32 CTRL; }tFLEXIO;

/******************************************************************************
 * FLEXIO shifter definition configuration structure                          *
 ******************************************************************************/
typedef struct { uint32 SHIFTSIEN, SHIFTEIEN, SHIFTSDEN, SHIFTCTL, SHIFTCFG; }tFLEXIO_SHIFTER;

/******************************************************************************
 * FLEXIO timer definition configuration structure                            *
 ******************************************************************************/
typedef struct { uint32 TIMIEN, TIMCTL, TIMCFG; }tFLEXIO_TIMER;

/******************************************************************************
* FLEXIO callback used in FLEXIO_Init() function
*
*//*! @addtogroup flexio_callback
* @{
*******************************************************************************/
typedef enum {
    FLEXIO_SHIFTER0_CALLBACK=1,
    FLEXIO_SHIFTER1_CALLBACK=2,
    FLEXIO_SHIFTER2_CALLBACK=4,
    FLEXIO_SHIFTER3_CALLBACK=8,
    FLEXIO_SHIFTER0ERR_CALLBACK=16,
    FLEXIO_SHIFTER1ERR_CALLBACK=32,
    FLEXIO_SHIFTER2ERR_CALLBACK=64,
    FLEXIO_SHIFTER3ERR_CALLBACK=128,
    FLEXIO_TIMER0_CALLBACK=256,
    FLEXIO_TIMER1_CALLBACK=512,
    FLEXIO_TIMER2_CALLBACK=1042,
    FLEXIO_TIMER3_CALLBACK=2048,
} FLEXIO_CALLBACK_TYPE;
/*! FLEXIO_CALLBACK function declaration                                         */
typedef void (*FLEXIO_CALLBACK)(FLEXIO_CALLBACK_TYPE type, void* user_data);
/*! @} End of flexio_callback                                                    */

/******************************************************************************
 * FLEXIO callback specification definition structure                            *
 ******************************************************************************/
typedef struct { FLEXIO_CALLBACK pCallBack; uint32_t SHIFTERR_MASK; uint32_t SHIFTFLG_MASK; uint32_t TIMERFLG_MASK; void* user_data;} tFLEXIO_CALLBACK_DESC;

#ifndef FLEXIO_MAX_CALLBACKS
  #define FLEXIO_MAX_CALLBACKS  5
#endif

/******************************************************************************
* FLEXIO shifter/timer status flags definition.
*
*//*! @addtogroup flexio_flag
* @{
*******************************************************************************/
#define FLEXIO_SHIFTER_ALL                ///< all flags mask
/*! @} End of flexio_flag                                                     */

/******************************************************************************
* FLEXIO shifter module macros definition.
*
*//*! @addtogroup flexio_shifter
* @{
*******************************************************************************/
#define FLEXIO_SHIFTER0         0x0       ///< shifter module 0
#define FLEXIO_SHIFTER1         0x1       ///< shifter module 1
#define FLEXIO_SHIFTER2         0x2       ///< shifter module 2
#define FLEXIO_SHIFTER3         0x3       ///< shifter module 3
/*! @} End of flexio_shifter                                                  */

/******************************************************************************
* FLEXIO shifter module masks macros definition.
*
*//*! @addtogroup flexio_shifter_masks
* @{
*******************************************************************************/
#define FLEXIO_SHIFTER0_MASK         (1<<(SHIFTER0))       ///< shifter module mask 0
#define FLEXIO_SHIFTER1_MASK         (1<<(SHIFTER1))       ///< shifter module mask 1
#define FLEXIO_SHIFTER2_MASK         (1<<(SHIFTER2))       ///< shifter module mask 2
#define FLEXIO_SHIFTER3_MASK         (1<<(SHIFTER3))       ///< shifter module mask 3
/*! @} End of flexio_shifter_masks                                            */

/******************************************************************************
* FLEXIO timer module macros definition.
*
*//*! @addtogroup flexio_timer
* @{
*******************************************************************************/
#define FLEXIO_TIMER0           0x0       ///< timer module 0
#define FLEXIO_TIMER1           0x1       ///< timer module 1
#define FLEXIO_TIMER2           0x2       ///< timer module 2
#define FLEXIO_TIMER3           0x3       ///< timer module 3
/*! @} End of flexio_timer                                                    */

/******************************************************************************
* FLEXIO timer module masks macros definition.
*
*//*! @addtogroup flexio_timer_mask
* @{
*******************************************************************************/
#define FLEXIO_TIMER0_MASK           (1<<(TIMER0))       ///< timer module mask 0
#define FLEXIO_TIMER1_MASK           (1<<(TIMER1))       ///< timer module mask 1
#define FLEXIO_TIMER2_MASK           (1<<(TIMER2))       ///< timer module mask 2
#define FLEXIO_TIMER3_MASK           (1<<(TIMER3))       ///< timer module mask 3
/*! @} End of flexio_timer_mask                                                */

/******************************************************************************
* FLEXIO edge of timer for shifting selection.
*
*//*! @addtogroup flexio_timeredge
* @{
*******************************************************************************/
#define FLEXIO_TIMER_POSITIVE_EDGE    0x0      ///< shift on positive edge on timer clock
#define FLEXIO_TIMER_NEGATIVE_EDGE    0x1      ///< shift on negative edge on timer clock
/*! @} End of flexio_timeredge                                                */

/******************************************************************************
* FLEXIO shifter/timer pin configuration.
*
*//*! @addtogroup flexio_pincfg
* @{
*******************************************************************************/
#define FLEXIO_PIN_DISABLED         0x0     ///< output disabled
#define FLEXIO_PIN_OD_BI_OUTPUT     0x1     ///< open drain or bi-directional output enable
#define FLEXIO_PIN_BI_OUTPUTDATA    0x2     ///< bi-directional output data
#define FLEXIO_PIN_OUTPUT           0x3     ///< output enabled
/*! @} End of flexio_pincfg                                                   */

/******************************************************************************
* FLEXIO shifter/timer pin selection.
*
*//*! @addtogroup flexio_pinsel
* @{
*******************************************************************************/
#define FLEXIO_PIN0            0x0     ///< shifter/timer pin 0
#define FLEXIO_PIN1            0x1     ///< shifter/timer pin 1
#define FLEXIO_PIN2            0x2     ///< shifter/timer pin 2
#define FLEXIO_PIN3            0x3     ///< shifter/timer pin 3
#define FLEXIO_PIN4            0x4     ///< shifter/timer pin 4
#define FLEXIO_PIN5            0x5     ///< shifter/timer pin 5
#define FLEXIO_PIN6            0x6     ///< shifter/timer pin 6
#define FLEXIO_PIN7            0x7     ///< shifter/timer pin 7
/*! @} End of flexio_pinsel                                                   */

/******************************************************************************
* FLEXIO shifter pin / timer trigger polarity.
*
*//*! @addtogroup flexio_polarity
* @{
*******************************************************************************/
#define FLEXIO_POLARITY_HIGH        0x0     ///< active high
#define FLEXIO_POLARITY_LOW         0x1     ///< active low
/*! @} End of flexio_polarity                                                 */

/******************************************************************************
* FLEXIO shifter modes macros.
*
*//*! @addtogroup flexio_shiftermode
* @{
*******************************************************************************/
#define FLEXIO_SHIFTER_DISABLED        0x0       ///< shifter disabled
#define FLEXIO_SHIFTER_RX_MODE         0x1       ///< shifter receive mod
#define FLEXIO_SHIFTER_TX_MODE         0x2       ///< shifter transmit mode
#define FLEXIO_SHIFTER_RXTX_MODE       0x3       ///< shifter receive/transmit mode
#define FLEXIO_SHIFTER_MATCHSTORE_MODE 0x4       ///< shifter match store mode
#define FLEXIO_SHIFTER_MATCHCONT_MODE  0x5       ///< shifter match continuous mode
/*! @} End of flexio_shiftermode                                              */

/******************************************************************************
* FLEXIO shifter input source.
*
*//*! @addtogroup flexio_insrc
* @{
*******************************************************************************/
#define FLEXIO_INSRC_PIN               0x0       ///< pin as input source
#define FLEXIO_INSRC_NEXT_SHIFTER_OUT  0x1       ///< shifter n + 1 output as input source
/*! @} End of flexio_insrc                                                    */

/******************************************************************************
* FLEXIO shifter stop bit.
*
*//*! @addtogroup flexio_stopbit
* @{
*******************************************************************************/
#define FLEXIO_STOPBIT_DISABLED        0x0       ///< stop bit disabled
#define FLEXIO_STOPBIT_LOG0            0x2       ///< stop bit enabled on logic 0
#define FLEXIO_STOPBIT_LOG1            0x3       ///< stop bit enabled on logic 1
/*! @} End of flexio_stopbit                                                  */

/******************************************************************************
* FLEXIO shifter start bit.
*
*//*! @addtogroup flexio_startbit
* @{
*******************************************************************************/
#define FLEXIO_STARTBIT_DISABLED_ON_EN         0x0       ///< start bit disabled, transmitter loads data on anable
#define FLEXIO_STARTBIT_DISABLED_ON_FIRST      0x1       ///< start bit disabled, transmitter loads data on first shift
#define FLEXIO_STARTBIT_LOG0                   0x2       ///< start bit enabled on logic 0
#define FLEXIO_STARTBIT_LOG1                   0x3       ///< start bit enabled on logic 1
/*! @} End of flexio_startbit                                                 */

/******************************************************************************
* FLEXIO timer triggers.
*
*//*! @addtogroup flexio_timertrg
* @{
*******************************************************************************/
#define FLEXIO_TIMTRG_PIN0                0x0       ///< pin 0 input
#define FLEXIO_TIMTRG_PIN1                0x2       ///< pin 1 input
#define FLEXIO_TIMTRG_PIN2                0x4       ///< pin 2 input
#define FLEXIO_TIMTRG_PIN3                0x6       ///< pin 3 input
#define FLEXIO_TIMTRG_PIN4                0x8       ///< pin 4 input
#define FLEXIO_TIMTRG_PIN5                0xA       ///< pin 5 input
#define FLEXIO_TIMTRG_PIN6                0xC       ///< pin 6 input
#define FLEXIO_TIMTRG_PIN7                0xE       ///< pin 7 input
#define FLEXIO_TIMTRG_SHIFT0              0x1       ///< shifter 0 status flag
#define FLEXIO_TIMTRG_SHIFT1              0x5       ///< shifter 1 status flag
#define FLEXIO_TIMTRG_SHIFT2              0x9       ///< shifter 2 status flag
#define FLEXIO_TIMTRG_SHIFT3              0xD       ///< shifter 3 status flag
#define FLEXIO_TIMTRG_TIM0TRGOUT          0x3       ///< timer 0 trigger output
#define FLEXIO_TIMTRG_TIM1TRGOUT          0x7       ///< timer 1 trigger output
#define FLEXIO_TIMTRG_TIM2TRGOUT          0xB       ///< timer 2 trigger output
#define FLEXIO_TIMTRG_TIM3TRGOUT          0xF       ///< timer 3 trigger output


#define FLEXIO_TIMTRG_PIN(ix)        ((ix) * 2)          ///< pin x input
#define FLEXIO_TIMTRG_SHIFTER(ix)    (((ix) * 4) + 1)    ///< shifter x status flag
#define FLEXIO_TIMTRG_TIMER(ix)      (((ix) * 4) + 3)    ///< timer x trigger output
/*! @} End of flexio_timertrg                                                 */

/******************************************************************************
* FLEXIO timer modes.
*
*//*! @addtogroup flexio_timermode
* @{
*******************************************************************************/
#define FLEXIO_TIMER_DISABLED             0x0       ///< timer disabled
#define FLEXIO_TIMER_8BIT_BAUD_MODE       0x1       ///< 8-bit counter baud/bit mode
#define FLEXIO_TIMER_8BIT_PWM_MODE        0x2       ///< 8-bit PWM mode
#define FLEXIO_TIMER_16BIT_MODE           0x3       ///< 16-bit counter
/*! @} End of flexio_timermode                                                */

/******************************************************************************
* FLEXIO timer clock definition.
*
*//*! @addtogroup flexio_timerclock
* @{
*******************************************************************************/
#define FLEXIO_LOG1_ON_EN          0x0       ///< timer clock is log.1 on enable
#define FLEXIO_LOG0_ON_EN          0x1       ///< timer clock is log.0 on enable
#define FLEXIO_LOG1_ON_EN_RST      0x2       ///< timer clock is log.1 on enable and on reset
#define FLEXIO_LOG0_ON_EN_RST      0x3       ///< timer clock is log.0 on enable and on reset
/*! @} End of flexio_timerclock                                               */

/******************************************************************************
* FLEXIO timer increment definition.
*
*//*! @addtogroup flexio_timerinc
* @{
*******************************************************************************/
#define FLEXIO_INC_ALWAYS              0x0       ///< timer always increment
#define FLEXIO_INC_PIN                 0x2       ///< timer increment on pin input
#define FLEXIO_INC_TRIGGER             0x3       ///< timer increment on trigger input
/*! @} End of flexio_timerinc                                               */

/******************************************************************************
* FLEXIO timer reset definition.
*
*//*! @addtogroup flexio_timerrst
* @{
*******************************************************************************/
#define FLEXIO_RST_NEVER               0x0       ///< timer never resets
#define FLEXIO_RST_PIN_OUT             0x2       ///< timer resets on pin equal to timer output
#define FLEXIO_RST_TRIGGER_OUT         0x3       ///< timer resets on trigger equal to timer output
#define FLEXIO_RST_PIN_REDGE           0x4       ///< timer resets on pin rising edge
#define FLEXIO_RST_TRIGGER_REDGE       0x6       ///< timer resets on trigger rising edge
#define FLEXIO_RST_TRIGGER_BOTHEDGES   0x7       ///< timer resets on trigger rising or falling edge
/*! @} End of flexio_timerrst                                               */

/******************************************************************************
* FLEXIO timer disable definition.
*
*//*! @addtogroup flexio_timerdison
* @{
*******************************************************************************/
#define FLEXIO_DIS_NEVER                       0x0       ///< timer never disables
#define FLEXIO_DIS_PREVIOUS_TIM_DIS            0x1       ///< timer disables on timer n-1 disables
#define FLEXIO_DIS_ON_COMPARE                  0x2       ///< timer disables on timer compare
#define FLEXIO_DIS_ON_COMPARE_TRIGGER_LOW      0x3       ///< timer disables on timer comare and trigger low
#define FLEXIO_DIS_PIN_BOTHEDGES               0x4       ///< timer disables on pin rising or falling edge
#define FLEXIO_DIS_PIN_BOTHEDGES_TRIGGER_HIGH  0x5       ///< timer disables on pin rising or falling edge provided trigger is high
#define FLEXIO_DIS_TRIGGER_FEDGE               0x6       ///< timer disables on trigger falling edge
/*! @} End of flexio_timerdison                                               */

/******************************************************************************
* FLEXIO timer enable definition.
*
*//*! @addtogroup flexio_timerenon
* @{
*******************************************************************************/
#define FLEXIO_EN_NEVER                       0x0       ///< timer never enables
#define FLEXIO_EN_PREVIOUS_TIM_DIS            0x1       ///< timer enables on timer n-1 disables
#define FLEXIO_EN_TRIGGER_HIGH                0x2       ///< timer enables on timer trigger high
#define FLEXIO_EN_TRIGGER_PIN_HIGH            0x3       ///< timer enables on timer trigger high and pin high
#define FLEXIO_EN_PIN_REDGE                   0x4       ///< timer enables on pin rising edge
#define FLEXIO_EN_PIN_REDGE_TRIGGER_HIGH      0x5       ///< timer enables on pin rising and trigger high
#define FLEXIO_EN_TRIGGER_REDGE               0x6       ///< timer enables on trigger rising edge
#define FLEXIO_EN_TRIGGER_BOTHEDGEs           0x7       ///< timer enables on trigger rising and falling edge
/*! @} End of flexio_timerenon                                               */

/******************************************************************************
* FLEXIO timer enable definition.
*
*//*! @addtogroup flexio_timerstop
* @{
*******************************************************************************/
#define FLEXIO_STOP_DISABLED                   0x0       ///< timer never enables
#define FLEXIO_STOP_ON_COMPARE                 0x1       ///< timer enables on timer n-1 disables
#define FLEXIO_STOP_ON_TIMER_DISABLED          0x2       ///< timer enables on timer trigger high
#define FLEXIO_STOP_ON_COMPARE_TIMER_DISABLED  0x3       ///< timer enables on timer trigger high and pin high
/*! @} End of flexio_timerstop                                               */

/******************************************************************************
* FLEXIO used by FLEXIO_init() function
*
*//*! @addtogroup flexio_config
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   FLEXIO disable.
 * @note    Implemented as function call.
 ******************************************************************************/
#define FLEXIO_ENABLE_CONFIG                                                    \
(tFLEXIO){                                                                      \
/* CTRL */    CLR(FLEXIO_CTRL_DOZEN_MASK)|CLR(FLEXIO_CTRL_DBGE_MASK)|           \
              CLR(FLEXIO_CTRL_FASTACC_MASK)|CLR(FLEXIO_CTRL_SWRST_MASK)|        \
              CLR(FLEXIO_CTRL_FLEXEN_MASK),                                     \
}

/***************************************************************************//*!
 * @brief   FLEXIO enabled with normal register acces.
 * @note    Implemented as function call.
 ******************************************************************************/
#define FLEXIO_ENABLE_NORMAL_CONFIG                                             \
(tFLEXIO){                                                                      \
/* CTRL */    CLR(FLEXIO_CTRL_DOZEN_MASK)|CLR(FLEXIO_CTRL_DBGE_MASK)|           \
              CLR(FLEXIO_CTRL_FASTACC_MASK)|CLR(FLEXIO_CTRL_SWRST_MASK)|        \
              SET(FLEXIO_CTRL_FLEXEN_MASK),                                     \
}

/***************************************************************************//*!
 * @brief   FLEXIO enabled with fast register acces.
 * @note    Implemented as function call.
 ******************************************************************************/
#define FLEXIO_ENABLE_FASTACC_CONFIG                                            \
(tFLEXIO){                                                                      \
/* CTRL */    CLR(FLEXIO_CTRL_DOZEN_MASK)|CLR(FLEXIO_CTRL_DBGE_MASK)|           \
              SET(FLEXIO_CTRL_FASTACC_MASK)|CLR(FLEXIO_CTRL_SWRST_MASK)|        \
              SET(FLEXIO_CTRL_FLEXEN_MASK),                                     \
}

/***************************************************************************//*!
 * @brief   FLEXIO enabled in dozen mode.
 * @note    Implemented as function call.
 ******************************************************************************/
#define FLEXIO_ENABLE_DOZEN_CONFIG                                             \
(tFLEXIO){                                                                      \
/* CTRL */    SET(FLEXIO_CTRL_DOZEN_MASK)|CLR(FLEXIO_CTRL_DBGE_MASK)|           \
              CLR(FLEXIO_CTRL_FASTACC_MASK)|CLR(FLEXIO_CTRL_SWRST_MASK)|        \
              SET(FLEXIO_CTRL_FLEXEN_MASK),                                     \
}

/***************************************************************************//*!
 * @brief   FLEXIO enabled in debug and dozen modes.
 * @note    Implemented as function call.
 ******************************************************************************/
#define FLEXIO_ENABLE_DOZEN_DEBUG_CONFIG                                        \
(tFLEXIO){                                                                      \
/* CTRL */    SET(FLEXIO_CTRL_DOZEN_MASK)|SET(FLEXIO_CTRL_DBGE_MASK)|           \
              CLR(FLEXIO_CTRL_FASTACC_MASK)|CLR(FLEXIO_CTRL_SWRST_MASK)|        \
              SET(FLEXIO_CTRL_FLEXEN_MASK),                                     \
}

/***************************************************************************//*!
 * @brief   FLEXIO enabled with no affect to CTRL register on SW reset.
 * @note    Implemented as function call.
 ******************************************************************************/
#define FLEXIO_ENABLE_CTRLRST_CONFIG                                            \
(tFLEXIO){                                                                      \
/* CTRL */    CLR(FLEXIO_CTRL_DOZEN_MASK)|CLR(FLEXIO_CTRL_DBGE_MASK)|           \
              CLR(FLEXIO_CTRL_FASTACC_MASK)|SET(FLEXIO_CTRL_SWRST_MASK)|        \
              SET(FLEXIO_CTRL_FLEXEN_MASK),                                     \
}
/*! @} End of flexio_config                                                   */

// FlexIO shifter configuration macros
/******************************************************************************
* FLEXIO used by FLEXIO_SHIFT_init() function
*
*//*! @addtogroup flexio_shiftconfig
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   FLEXIO shifter configuration.
 * @note    Implemented as function call.
 ******************************************************************************/
#define FLEXIO_SHIFTER_CONFIG                                                   \
(tFLEXIO_SHIFTER){                                                              \
/*SHIFTSIEN */SET(FLEXIO_SHIFTSIEN_SSIE(0x0)),                                  \
/*SHIFTEIEN */SET(FLEXIO_SHIFTEIEN_SEIE(0x0)),                                  \
/*SHIFTSDEN */SET(FLEXIO_SHIFTSDEN_SSDE(0x0)),                                  \
/* SHIFTCTL */SET(FLEXIO_SHIFTCTL_TIMSEL(0x0))|CLR(FLEXIO_SHIFTCTL_TIMPOL_MASK)|\
              SET(FLEXIO_SHIFTCTL_PINCFG(0x0))|SET(FLEXIO_SHIFTCTL_PINSEL(0x0))|\
              SET(FLEXIO_SHIFTCTL_PINPOL_MASK)|SET(FLEXIO_SHIFTCTL_SMOD(0x0)),  \
/* SHIFTCFG */CLR(FLEXIO_SHIFTCFG_INSRC_MASK)|SET(FLEXIO_SHIFTCFG_SSTOP_MASK)|  \
              SET(FLEXIO_SHIFTCFG_SSTART_MASK),                                 \
}
/*! @} End of flexio_shiftconfig                                              */

// FlexIO timer configuration macros
/******************************************************************************
* FLEXIO used by FLEXIO_TIMER_init() function
*
*//*! @addtogroup flexio_timerconfig
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   FLEXIO timer configuration.
 * @note    Implemented as function call.
 ******************************************************************************/
#define FLEXIO_TIMER_CONFIG                                                     \
(tFLEXIO_TIMER){                                                                \
/* TIMIEN */  SET(FLEXIO_TIMIEN_TEIE(0x0)),                                     \
/* TIMCTL */  SET(FLEXIO_TIMCTL_TRGSEL(0x0))|CLR(FLEXIO_TIMCTL_TRGPOL_MASK)|    \
              CLR(FLEXIO_TIMCTL_TRGSRC_MASK)|SET(FLEXIO_TIMCTL_PINCFG(0x0))|    \
              SET(FLEXIO_TIMCTL_PINSEL(0x0))|CLR(FLEXIO_TIMCTL_PINPOL_MASK)|    \
              SET(FLEXIO_TIMCTL_TIMOD(0x0)),                                    \
/* TIMCFG */  SET(FLEXIO_TIMCFG_TIMOUT(0x0))|SET(FLEXIO_TIMCFG_TIMDEC(0x0))| \
              SET(FLEXIO_TIMCFG_TIMRST(0x0))|SET(FLEXIO_TIMCFG_TIMDIS(0x0))|    \
              SET(FLEXIO_TIMCFG_TIMENA(0x0))|SET(FLEXIO_TIMCFG_TSTOP(0x0))|    \
              CLR(FLEXIO_TIMCFG_TSTART_MASK),                                 \
}
/*! @} End of flexio_timerconfig                                              */

/******************************************************************************
* FLEXIO function and macro definitions
*
*//*! @addtogroup flexio_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro disables FLEXIO module.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_Disable()    REG_SetVal(FLEXIO_CTRL,FLEXIO_CTRL_FLEXEN,0x0);

/***************************************************************************//*!
 * @brief   Macro enables FLEXIO module.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_Enable()    REG_SetVal(FLEXIO_CTRL,FLEXIO_CTRL_FLEXEN,0x1);

/***************************************************************************//*!
 * @brief   Macro disables FLEXIO SW reset.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_SwRstDisable()    REG_SetVal(FLEXIO_CTRL,FLEXIO_CTRL_SWRST,0x0);

/***************************************************************************//*!
 * @brief   Macro enables FLEXIO SW reset.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_SwRstEnable()    REG_SetVal(FLEXIO_CTRL,FLEXIO_CTRL_SWRST,0x1);

/***************************************************************************//*!
 * @brief   Macro set normal regisetr access to FlexIO.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_FastAccessDisable()    REG_SetVal(FLEXIO_CTRL,FLEXIO_CTRL_FASTACC,0x0);

/***************************************************************************//*!
 * @brief   Macro enables fast regisetr access to FlexIO.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_FastAccessEnable()    REG_SetVal(FLEXIO_CTRL,FLEXIO_CTRL_FASTACC,0x1);

/***************************************************************************//*!
 * @brief   Macro set normal regisetr access to FlexIO.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_DebugDisable()    REG_SetVal(FLEXIO_CTRL,FLEXIO_CTRL_DBGE,0x0);

/***************************************************************************//*!
 * @brief   Macro enables fast regisetr access to FlexIO.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_DebugEnable()    REG_SetVal(FLEXIO_CTRL,FLEXIO_CTRL_DBGE,0x1);

/***************************************************************************//*!
 * @brief   Macro disables dozen mode to FlexIO.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_DozeDisable()    REG_SetVal(FLEXIO_CTRL,FLEXIO_CTRL_DOZEN,0x0);

/***************************************************************************//*!
 * @brief   Macro enables dozen mode to FlexIO.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_DozeEnable()    REG_SetVal(FLEXIO_CTRL,FLEXIO_CTRL_DOZEN,0x1);

/***************************************************************************//*!
 * @brief   Macro clears specified shifter status flag.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ClrShifterFlag(flag)  FLEXIO_SHIFTSTAT = flag;

/***************************************************************************//*!
 * @brief   Macro clears specified shifter error flags.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ClrErrShifterFlag(flag)  FLEXIO_SHIFTERR = flag;

/***************************************************************************//*!
 * @brief   Macro clears specified timer status flag.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ClrTimerFlag(flag)  FLEXIO_TIMSTAT = flag;

/***************************************************************************//*!
 * @brief   Macro clears specified shifter status interrupt generation.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterIrqDisable(flag)  FLEXIO_SHIFTSIEN &= FLEXIO_SHIFTSIEN_SSIE_MASK&(~flag);

/***************************************************************************//*!
 * @brief   Macro enables specified shifter status interrupt generation.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterIrqEnable(flag)  FLEXIO_SHIFTSIEN |= FLEXIO_SHIFTSIEN_SSIE_MASK&(flag);

/***************************************************************************//*!
 * @brief   Macro clears specified shifter error interrupt generation.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterErrIrqDisable(flag)  FLEXIO_SHIFTEIEN &= FLEXIO_SHIFTEIEN_SEIE_MASK&(~flag);

/***************************************************************************//*!
 * @brief   Macro enables specified shifter error interrupt generation.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterErrIrqEnable(flag)  REG_SetVal(FLEXIO_SHIFTEIEN,FLEXIO_SHIFTEIEN_SEIE,flag);

/***************************************************************************//*!
 * @brief   Macro clears specified timer status interrupt generation.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerIrqDisable(flag)  FLEXIO_TIMIEN &= FLEXIO_TIMIEN_TEIE_MASK&(~flag);

/***************************************************************************//*!
 * @brief   Macro enables specified timer status interrupt generation.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerIrqEnable(flag)  FLEXIO_TIMIEN |= FLEXIO_TIMIEN_TEIE_MASK&(flag); 

/***************************************************************************//*!
 * @brief   Macro clears specified shifter status DMA generation.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterDmaDisable(flag)  FLEXIO_SHIFTSDEN &= FLEXIO_SHIFTSDEN_SSDE_MASK&(~flag);

/***************************************************************************//*!
 * @brief   Macro enables specified shifter status DMA generation.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterDmaEnable(flag)  REG_SetVal(FLEXIO_SHIFTSDEN,FLEXIO_SHIFTSDEN_SSDE,flag);

/***************************************************************************//*!
 * @brief   Macro gets specified shifter status flag.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_GetShifterFlag(flag)  REG_GetVal(FLEXIO_SHIFTSTAT,FLEXIO_SHIFTSTAT_SSF,flag)

/***************************************************************************//*!
 * @brief   Macro gets specified shifter error flags.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_GetErrShifterFlag(flag)  REG_GetVal(FLEXIO_SHIFTERR,FLEXIO_SHIFTERR_SEF,flag)

/***************************************************************************//*!
 * @brief   Macro gets specified timer status flag.
 * @param   flag - @ref flexio_flag (can be or-ed)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_GetTimerFlag(flag)  REG_GetVal(FLEXIO_TIMSTAT,FLEXIO_TIMSTAT_TSF,flag)

/***************************************************************************//*!
 * @brief   Macro select specified timer for  specified shifter.
 * @param   shifter - @ref flexio_shifter
 * @param   timer - @ref flexio_timer
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterTimerSel(shifter,timer) REG_SetVal(FLEXIO_SHIFTCTL(shifter),FLEXIO_SHIFTCTL_TIMSEL,timer);

/***************************************************************************//*!
 * @brief   Macro configures timer polarity - shift on edge of timer clock.
 * @param   shifter - @ref flexio_shifter
 * @param   edge - @ref flexio_timeredge
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterTimerPol(shifter,edge)  REG_SetVal(FLEXIO_SHIFTCTL(shifter),FLEXIO_SHIFTCTL_TIMPOL,edge);

/***************************************************************************//*!
 * @brief   Macro configures shifter pin configuration.
 * @param   shifter - @ref flexio_shifter
 * @param   pincfg - @ref flexio_pincfg
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterPinCfg(shifter,pincfg)  REG_SetVal(FLEXIO_SHIFTCTL(shifter),FLEXIO_SHIFTCTL_PINCFG,pincfg);

/***************************************************************************//*!
 * @brief   Macro configures shifter pin selection.
 * @param   shifter - @ref flexio_shifter
 * @param   pincfg - @ref flexio_pincfg
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterPinSel(shifter,pinsel)  REG_SetVal(FLEXIO_SHIFTCTL(shifter),FLEXIO_SHIFTCTL_PINSEL,pinsel);

/***************************************************************************//*!
 * @brief   Macro configures shifter pin polarity selection.
 * @param   shifter - @ref flexio_shifter
 * @param   pinpol - @ref flexio_polarity
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterPinPol(shifter,pinpol)  REG_SetVal(FLEXIO_SHIFTCTL(shifter),FLEXIO_SHIFTCTL_PINPOL,pinpol);

/***************************************************************************//*!
 * @brief   Macro for shifter mode selection.
 * @param   shifter - @ref flexio_shifter
 * @param   mode - @ref flexio_shiftermode
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterMode(shifter,mode)  REG_SetVal(FLEXIO_SHIFTCTL(shifter),FLEXIO_SHIFTCTL_SMOD,mode);

/***************************************************************************//*!
 * @brief   Macro configures shifter input source.
 * @param   shifter - @ref flexio_shifter
 * @param   insrc - @ref flexio_insrc
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterInSrc(shifter,insrc)  REG_SetVal(FLEXIO_SHIFTCFG(shifter),FLEXIO_SHIFTCFG_INSRC,insrc);

/***************************************************************************//*!
 * @brief   Macro configures shifter stop bit.
 * @param   shifter - @ref flexio_shifter
 * @param   sstop - @ref flexio_stopbit
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterStopBit(shifter,sstop)  REG_SetVal(FLEXIO_SHIFTCFG(shifter),FLEXIO_SHIFTCFG_SSTOP,sstop);

/***************************************************************************//*!
 * @brief   Macro configures shifter start bit.
 * @param   shifter - @ref flexio_shifter
 * @param   sstart - @ref flexio_startbit
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ShifterStartBit(shifter,sstart)  REG_SetVal(FLEXIO_SHIFTCFG(shifter),FLEXIO_SHIFTCFG_SSTART,sstart);

#define FLEXIO_WriteBuffer_DEFAULT(shifter, data)        REG_SetVal(FLEXIO_SHIFTBUF(shifter),FLEXIO_SHIFTBUF_SHIFTBUF,data);
#define FLEXIO_WriteBuffer_BITBYTE_SWAPED(shifter, data) REG_SetVal(FLEXIO_SHIFTBUFBBS(shifter),FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS,data);
#define FLEXIO_WriteBuffer_BYTE_SWAPED(shifter, data)    REG_SetVal(FLEXIO_SHIFTBUFBYS(shifter),FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS,data);
#define FLEXIO_WriteBuffer_BIT_SWAPED(shifter, data)     REG_SetVal(FLEXIO_SHIFTBUFBIS(shifter),FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS,data);
/***************************************************************************//*!
 * @brief   Macro write 32-bit value to specified shifter buffer.
 * @param   swap - DEFAULT|BITBYTE_SWAPED|BYTE_SWAPED|BIT_SWAPED
 * @param   data - 32-bit data
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_WriteShifterBuffer(shifter,swap,data)  FLEXIO_WriteBuffer_##swap##(shifter, data)

#define FLEXIO_ReadBuffer_DEFAULT(shifter)        (uint32)FLEXIO_SHIFTBUF(shifter)
#define FLEXIO_ReadBuffer_BITBYTE_SWAPED(shifter) (uint32)FLEXIO_SHIFTBUFBBS(shifter)
#define FLEXIO_ReadBuffer_BYTE_SWAPED(shifter)    (uint32)FLEXIO_SHIFTBUFBYS(shifter)
#define FLEXIO_ReadBuffer_BIT_SWAPED(shifter)     (uint32)FLEXIO_SHIFTBUFBIS(shifter)
/***************************************************************************//*!
 * @brief   Macro write 32-bit value to specified shifter buffer.
 * @param   shifter - @ref flexio_shifter
 * @param   swap - DEFAULT|BITBYTE_SWAPED|BYTE_SWAPED|BIT_SWAPED
 * @return  Specified shifter buffer value
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_ReadShifterBuffer(shifter,swap)     FLEXIO_ReadBuffer_##swap##(shifter)

/***************************************************************************//*!
 * @brief   Macro select specified timer trigger.
 * @param   timer - @ref flexio_timer
 * @param   trig - @ref flexio_timertrg
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerTrgSel(timer,trig)  REG_SetVal(FLEXIO_TIMCTL(timer),FLEXIO_TIMCTL_TRGSEL,trig);

/***************************************************************************//*!
 * @brief   Macro select specified timer trigger.
 * @param   timer - @ref flexio_timer
 * @param   trigpol - @ref flexio_polarity
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerTrgPol(timer,trigpol)  REG_SetVal(FLEXIO_TIMCTL(timer),FLEXIO_TIMCTL_TRGPOL,trigpol);

#define FLEXIO_TrgSrc_EXT_TRG(timer)      REG_SetVal(FLEXIO_TIMCTL(timer),FLEXIO_TIMCTL_TRGSRC,0x0);
#define FLEXIO_TrgSrc_INT_TRG(timer)      REG_SetVal(FLEXIO_TIMCTL(timer),FLEXIO_TIMCTL_TRGSRC,0x1);
/***************************************************************************//*!
 * @brief   Macro select specified timer trigger source.
 * @param   timer - @ref flexio_timer
 * @param   trgsrc - EXT_TRG|INT_TRG
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerTrgSrc(timer,trgsrc)  FLEXIO_TrgSrc_##trgsrc##(timer)

/***************************************************************************//*!
 * @brief   Macro configures timer pin.
 * @param   timer - @ref flexio_timer
 * @param   pincfg - @ref flexio_pincfg
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerPinCfg(timer,pincfg)  REG_SetVal(FLEXIO_TIMCTL(timer),FLEXIO_TIMCTL_PINCFG,pincfg);

/***************************************************************************//*!
 * @brief   Macro selects timer pin.
 * @param   timer - @ref flexio_timer
 * @param   pinsel - @ref flexio_pinsel
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerPinSel(timer,pinsel)  REG_SetVal(FLEXIO_TIMCTL(timer),FLEXIO_TIMCTL_PINSEL,pinsel);

/***************************************************************************//*!
 * @brief   Macro configures timer pin polarity.
 * @param   timer - @ref flexio_timer
 * @param   pinpol - @ref flexio_polarity
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerPinPol(timer,pinpol)  REG_SetVal(FLEXIO_TIMCTL(timer),FLEXIO_TIMCTL_PINPOL,pinpol);

/***************************************************************************//*!
 * @brief   Macro configures timer mode.
 * @param   timer - @ref flexio_timer
 * @param   mode - @ref flexio_timermode
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerMode(timer,mode)    REG_SetVal(FLEXIO_TIMCTL(timer),FLEXIO_TIMCTL_TIMOD,mode);

/***************************************************************************//*!
 * @brief   Macro configures timer clock.
 * @param   timer - @ref flexio_timer
 * @param   clock - @ref flexio_timerclock
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerClock(timer,clock)    REG_SetVal(FLEXIO_TIMCFG(timer),FLEXIO_TIMCFG_TIMOUT,clock);

/***************************************************************************//*!
 * @brief   Macro configures timer increment.
 * @param   timer - @ref flexio_timer
 * @param   inc - @ref flexio_timerinc
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerInc(timer,inc)    REG_SetVal(FLEXIO_TIMCFG(timer),FLEXIO_TIMCFG_TIMDEC,inc);

/***************************************************************************//*!
 * @brief   Macro configures timer reset.
 * @param   timer - @ref flexio_timer
 * @param   rst - @ref flexio_timerrst
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerResets(timer,rst)    REG_SetVal(FLEXIO_TIMCFG(timer),FLEXIO_TIMCFG_TIMRST,rst);

/***************************************************************************//*!
 * @brief   Macro configures when timer is disabling.
 * @param   timer - @ref flexio_timer
 * @param   dsblon - @ref flexio_timerdison
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerDisablesOn(timer,dison)    REG_SetVal(FLEXIO_TIMCFG(timer),FLEXIO_TIMCFG_TIMDIS,dison);

/***************************************************************************//*!
 * @brief   Macro configures when timer is enabling.
 * @param   timer - @ref flexio_timer
 * @param   enon - @ref flexio_timerenon
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerEnablesOn(timer,enon)    REG_SetVal(FLEXIO_TIMCFG(timer),FLEXIO_TIMCFG_TIMENA,enon);

/***************************************************************************//*!
 * @brief   Macro configures when timer is enabling.
 * @param   timer - @ref flexio_timer
 * @param   tstop - @ref flexio_timerstop
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerStopBit(timer,tstop)    REG_SetVal(FLEXIO_TIMCFG(timer),FLEXIO_TIMCFG_TSTOP,tstop);

#define FLEXIO_StartBit_START_ENABLED(timer)    REG_SetVal(FLEXIO_TIMCFG(timer),FLEXIO_TIMCFG_TSTART,0x1);
#define FLEXIO_StartBit_START_DISABLED(timer)   REG_SetVal(FLEXIO_TIMCFG(timer),FLEXIO_TIMCFG_TSTART,0x0);
/***************************************************************************//*!
 * @brief   Macro configures when timer is enabling.
 * @param   timer - @ref flexio_timer
 * @param   tstart - START_ENABLED|START_DISABLED
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_TimerStartBit(timer,tstart)    FLEXIO_StartBit_##tstart##(timer)

/***************************************************************************//*!
 * @brief   Macro configures when timer is enabling.
 * @param   timer - @ref flexio_timer
 * @param   comval - 16-bit compare value
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FLEXIO_SetTimerCompareVal(timer,comval)    REG_SetVal(FLEXIO_TIMCMP(timer),FLEXIO_TIMCMP_CMP,comval);

/***************************************************************************//*!
 * @brief   FLEXIO module initialization function.
 * @param   module  -
 * @param   cfg     - FLEXIO module configuration structure (@ref flexio_config)
 * @param   ip      - interrupt priority 0..3
 * @param   callback- @ref flexio_callback
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
//#define FLEXIO_Init(cfg,ip,callback)  module##_Init(cfg,ip,callback)

/***************************************************************************//*!
 * @brief   FLEXIO shifter module initialization function.
 * @param   module - @ref flexio_shifter
 * @param   cfg - @ref flexio_shifter_config
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define FLEXIO_SHIFTER_Init(module,cfg)  FLEXIO_##module##_Init(cfg)

/***************************************************************************//*!
 * @brief   FLEXIO timer module initialization function.
 * @param   module - @ref flexio_timer
 * @param   cfg     - @ref flexio_timer_config
 * @param   compval - 32-bit timer compare value
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define FLEXIO_TIMER_Init(module,cfg,compval)  FLEXIO_##module##_Init(cfg,compval)

#define FLEXIO_MAKE_MASK(ix)    (1<<(ix))
/*! @} End of flexio_macro                                                    */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern void FLEXIO_Init(tFLEXIO flexio, uint8 ip, FLEXIO_CALLBACK pCallback);

extern void FLEXIO_SHIFTER0_Init(tFLEXIO_SHIFTER flexio_shifter);
extern void FLEXIO_SHIFTER1_Init(tFLEXIO_SHIFTER flexio_shifter);
extern void FLEXIO_SHIFTER2_Init(tFLEXIO_SHIFTER flexio_shifter);
extern void FLEXIO_SHIFTER3_Init(tFLEXIO_SHIFTER flexio_shifter);

extern void FLEXIO_TIMER0_Init(tFLEXIO_TIMER flexio_timer, uint32 u32TimerComVal);
extern void FLEXIO_TIMER1_Init(tFLEXIO_TIMER flexio_timer, uint32 u32TimerComVal);
extern void FLEXIO_TIMER2_Init(tFLEXIO_TIMER flexio_timer, uint32 u32TimerComVal);
extern void FLEXIO_TIMER3_Init(tFLEXIO_TIMER flexio_timer, uint32 u32TimerComVal);
extern int32_t FLEXIO_RegisterCallback(tFLEXIO_CALLBACK_DESC *pCallBackDesc, uint32 high_priority);
extern int32_t FLEXIO_UnRegisterCallback(FLEXIO_CALLBACK pCallBack);
#endif /* __DMA_H */
