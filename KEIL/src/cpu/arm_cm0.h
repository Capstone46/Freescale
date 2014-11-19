/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      arm_cm0.h
 * @version   1.0.12.0
 * @date      May-7-2013
 * @brief     Header file.
 *
 * Revision History:
 *  1.	01/01/2010   AISG     Initially written
 *  2.	01/08/2012   B34185   Ported to Kinetis L
 *  3.	24/09/2012   R55013   Ported to Kinetis M
 *  4.	17/01/2013   B34185   Re-written for Kinetis L
 *  5.	26/02/2013   B34185   Kinetis L - Systick feature added
 *  6.	07/05/2013   B34185   NVIC_SetIsr modified
 ******************************************************************************/
#ifndef _CPU_ARM_CM0_H
#define _CPU_ARM_CM0_H

#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pe111
#elif defined(__ARMCC_VERSION)
	#define asm	__asm
#endif

/*ARM Cortex M0 implementation for interrupt priority shift*/
#define ARM_INTERRUPT_LEVEL_BITS          6

/***********************************************************************/
// function prototypes for arm_cm0.c
extern void stop (void);
extern void wait (void);
extern void write_vtor (int);
extern void enable_irq (int);
extern void disable_irq (int);
extern void set_irq_priority (int, int);

#if defined(__IAR_SYSTEMS_ICC__)
/******************************************************************************
* Cortex-M0+ function and macro definitions
*
*//*! @addtogroup cm0plus_macros
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro returns state of global interrupt disable bit from Priority
 *          Mask Register (PRIMASK).
 * @details This macro returns state of global interrupt disable bit from
 *          Priority Mask Register (PRIMASK).
 * @return  TRUE    all interrupts disabled.
 * @return  FALSE   all interrupts enabled.
 * @note    Implemented as inlined function.
 ******************************************************************************/
inline uint32 GetInterruptMask (void)
{
  register uint32 mask;
  asm("MRS %[Rd],PRIMASK":[Rd]"=r"(mask));
  return mask;
}

/***************************************************************************//*!
 * @brief   Macro controls state of global interrupt disable bit in Priority
 *          Mask Register (PRIMASK).
 * @details This macro controls state of global interrupt disable bit in
 *          Priority Mask Register (PRIMASK).
 * @param   mask    TRUE (all interrupts disabled), FALSE (all interrupts enabled)
 * @note    Implemented as inlined function.
 ******************************************************************************/
inline void SetInterruptMask (uint32 mask)
{
  asm("MSR PRIMASK,%[Rs]":[Rs]"+r"(mask));
}
#elif defined(__ARMCC_VERSION)

#endif
/***************************************************************************//*!
 * @brief   Macro enables all interrupts.
 * @details This macro enables all interrupts by clearing disable bit in Priority
 *          Mask Register (PRIMASK).
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define EnableInterrupts        asm(" CPSIE i");

/***************************************************************************//*!
 * @brief   Macro disables all interrupts.
 * @details This macro disables all interrupts by setting disable bit in Priority
 *          Mask Register (PRIMASK).
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DisableInterrupts       asm(" CPSID i");

/***************************************************************************//*!
 * @brief   Macro enables all fault exceptions.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define EnableFaultInterrupts   asm(" CPSIE f");

/***************************************************************************//*!
 * @brief   Macro disables all interrupts.
 * @details This macro disables all interrupts by setting disable bit in Priority
 *          Mask Register (PRIMASK).
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define DisableFaultInterrupts  asm(" CPSID f");

/***************************************************************************//*!
 * @brief   Macro sets BASEPRI bits. The processor does not process any
 *          exception with a priority value greater than or equal to BASEPRI
 * @param   level     - 0x00    = no effect\n
 *                      nonzero = base priority for exception processing
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define MaskInterrupts(level)   __set_BASEPRI((level)<<ARM_INTERRUPT_LEVEL_BITS)

/***************************************************************************//*!
 * @brief   Macro switches to unprivilege (user) mode of execution.
 * @details This macro switches to unprivilege (user) mode of execution. It can be
 *          called from software running in privilege (supervisor) mode.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define ARMCM0_UserMode()       __set_CONTROL(__get_CONTROL()| 0x00000001l)

/***************************************************************************//*!
 * @brief   Macro switches to privilege (supervisor) mode of execution.
 * @details This macro switches to privilege (supervisor) mode of execution.
 *          It can be called from software running in handler or privilege
 *          (supervisor) modes.
 * @note    Implemented as inlined macro.
 * @warning Calling it from unprivilege (user) mode of execution causes not
 *          entering into privilege (supervisor) mode of execution.
 *          Call @ref ARMCM0_SVCall() from privilege to user mode.
 ******************************************************************************/
#define ARMCM0_SupervisorMode() __set_CONTROL(__get_CONTROL()&~0x00000001l)

/***************************************************************************//*!
 * @brief   Macro performs supervisor call.
 * @details This macro performs supervisor call. Service routine exexutes in handler
 *          mode.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define ARMCM0_SVCall()         asm("SVC #0x00")

/***************************************************************************//*!
 * @brief   Macro to switch stack pointer to process stack pointer.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define ARMCM0_ProcessStackPointer() __set_CONTROL(__get_CONTROL()| 0x00000002l)

/***************************************************************************//*!
 * @brief   Macro to switch stack pointer back to main stack pointer.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define ARMCM0_MainStackPointer()   __set_CONTROL(__get_CONTROL()&~ 0x00000002l)

#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pe175
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 175
#endif

#define IRQ(x)              ((x)-16)
#define IPR_INDEX(x)        (uint16)(IRQ(x)>>2)
#define IPR_SHIFT(x)        (uint16)(((IRQ(x)%4)<<3)+ARM_INTERRUPT_LEVEL_BITS)
/***************************************************************************//*!
 * @brief   Macro enables interrupt request and sets its priority.
 * @details This macro enables interrupt request and sets its priority.
 * @param   src   Select interrupt request:
 *                INT_DMA0,INT_DMA1,INT_DMA2,INT_DMA3,INT_MCM,INT_FTFA,INT_LVD_LVW,
 *                INT_LLW,INT_I2C0,INT_I2C1,INT_SPI0,INT_SPI1,INT_UART0,
 *                INT_UART1,INT_UART2,INT_ADC0,INT_CMP0,INT_TPM0,INT_TPM1,
 *                INT_TPM2,INT_RTC,INT_RTC_Seconds,INT_PIT,INT_Reserved39,
 *                INT_USB0,INT_DAC0,INT_TSI0,INT_MCG,INT_LPTimer,INT_Reserved45,
 *                INT_PORTA,INT_PORTD
 * @param   ipr   Interrupt priority 0..3; lower means higher priority
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define NVIC_SetIsr(src,ipr){                                                  \
                              NVIC_ICPR_REG(NVIC_BASE_PTR) |=                  \
                              (uint32)(1 << IRQ(src));                         \
                              NVIC_ISER_REG(NVIC_BASE_PTR) |=                  \
                              (uint32)(1 << IRQ(src));                         \
                              NVIC_IP_REG(NVIC_BASE_PTR,IPR_INDEX(src)) |=     \
                              (uint32)((uint32)(ipr)<<IPR_SHIFT(src));         \
                            }
/***************************************************************************//*!
 * @brief   Macro disables interrupt request.
 * @details This macro disables interrupt request.
 * @param   src   Select interrupt request:
 *                INT_DMA0,INT_DMA1,INT_DMA2,INT_DMA3,INT_MCM,INT_FTFA,INT_LVD_LVW,
 *                INT_LLW,INT_I2C0,INT_I2C1,INT_SPI0,INT_SPI1,INT_UART0,
 *                INT_UART1,INT_UART2,INT_ADC0,INT_CMP0,INT_TPM0,INT_TPM1,
 *                INT_TPM2,INT_RTC,INT_RTC_Seconds,INT_PIT,INT_Reserved39,
 *                INT_USB0,INT_DAC0,INT_TSI0,INT_MCG,INT_LPTimer,INT_Reserved45,
 *                INT_PORTA,INT_PORTD
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define NVIC_ClrIsr(src)    {                                                  \
                              NVIC_ICER_REG(NVIC_BASE_PTR) =                   \
                              (uint32)(1 << IRQ(src));                         \
                              NVIC_IP_REG(NVIC_BASE_PTR,IPR_INDEX(src)) &=     \
                              ~((uint32)((uint32)0x03<<IPR_SHIFT(src)));       \
                            }

/***************************************************************************//*!
 * @brief   Macro returns interrupt request prority.
 * @details This macro gets interrupt request priority.
 * @param   src   Select interrupt request:
 *                INT_DMA0,INT_DMA1,INT_DMA2,INT_DMA3,INT_MCM,INT_FTFA,INT_LVD_LVW,
 *                INT_LLW,INT_I2C0,INT_I2C1,INT_SPI0,INT_SPI1,INT_UART0,
 *                INT_UART1,INT_UART2,INT_ADC0,INT_CMP0,INT_TPM0,INT_TPM1,
 *                INT_TPM2,INT_RTC,INT_RTC_Seconds,INT_PIT,INT_Reserved39,
 *                INT_USB0,INT_DAC0,INT_TSI0,INT_MCG,INT_LPTimer,INT_Reserved45,
 *                INT_PORTA,INT_PORTD
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define NVIC_GetIsrPrt(src)  (((NVIC_IP_REG((NVIC_BASE_PTR),(IPR_INDEX(src)))) >> (IPR_SHIFT(src))) & 0x03)

/***************************************************************************//*!
 * @brief   Macro generates interrupt request.
 * @details This macro generates interrupt request.
 * @param   src   Select interrupt request:
 *                INT_DMA0,INT_DMA1,INT_DMA2,INT_DMA3,INT_MCM,INT_FTFA,INT_LVD_LVW,
 *                INT_LLW,INT_I2C0,INT_I2C1,INT_SPI0,INT_SPI1,INT_UART0,
 *                INT_UART1,INT_UART2,INT_ADC0,INT_CMP0,INT_TPM0,INT_TPM1,
 *                INT_TPM2,INT_RTC,INT_RTC_Seconds,INT_PIT,INT_Reserved39,
 *                INT_USB0,INT_DAC0,INT_TSI0,INT_MCG,INT_LPTimer,INT_Reserved45,
 *                INT_PORTA,INT_PORTD
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define NVIC_CallIsr(src) {                                                    \
                            NVIC_ISPR_REG(NVIC_BASE_PTR) |=                    \
                            (uint32)(1 << IRQ(src));                           \
                          }

/***************************************************************************//*!
 * @brief   Macro clears pending bits for interrupt request.
 * @details This macro clears pending bits for interrupt request.
 * @param   src   Select interrupt request:
 *                INT_DMA0,INT_DMA1,INT_DMA2,INT_DMA3,INT_MCM,INT_FTFA,INT_LVD_LVW,
 *                INT_LLW,INT_I2C0,INT_I2C1,INT_SPI0,INT_SPI1,INT_UART0,
 *                INT_UART1,INT_UART2,INT_ADC0,INT_CMP0,INT_TPM0,INT_TPM1,
 *                INT_TPM2,INT_RTC,INT_RTC_Seconds,INT_PIT,INT_Reserved39,
 *                INT_USB0,INT_DAC0,INT_TSI0,INT_MCG,INT_LPTimer,INT_Reserved45,
 *                INT_PORTA,INT_PORTD
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define NVIC_ClrPendingIsr(src) {                                              \
                                NVIC_ICPR_REG(NVIC_BASE_PTR) |=                \
                                (uint32)(1 << IRQ(src));                       \
                                }

/***************************************************************************//*!
 * @brief   Macro returns pending interrupt state.
 * @details This macro returns pending interrupt state.
 * @param   src   Select interrupt request:
 *                INT_DMA0,INT_DMA1,INT_DMA2,INT_DMA3,INT_MCM,INT_FTFA,INT_LVD_LVW,
 *                INT_LLW,INT_I2C0,INT_I2C1,INT_SPI0,INT_SPI1,INT_UART0,
 *                INT_UART1,INT_UART2,INT_ADC0,INT_CMP0,INT_TPM0,INT_TPM1,
 *                INT_TPM2,INT_RTC,INT_RTC_Seconds,INT_PIT,INT_Reserved39,
 *                INT_USB0,INT_DAC0,INT_TSI0,INT_MCG,INT_LPTimer,INT_Reserved45,
 *                INT_PORTA,INT_PORTD
 * @return  TRUE  interrupt is pending
 * @return  FALSE interrupt is not pending
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define NVIC_GetPendingIsr(src) (NVIC_ISPR&((uint32)(1<<(IRQ(src))))>>(IRQ(src)))

static uint32_t volatile * const SHPR_REG_PTR[] = {&SCB_SHPR2, &SCB_SHPR3};
#define SHPR_INDEX(x)       (uint32)(((x)-4)/4)
#define SHPR_SHIFT(x)       (uint32)(8*((x)%4))
/***************************************************************************//*!
 * @brief   Macro enables fault exception and sets its priority.
 * @param   src       <b>Fault Exceptions List:</b>
 *                    INT_NMI|INT_Hard_Fault|INT_MemManage_Fault|INT_Bus_Fault|
 *                    INT_Usage_Fault| INT_SVCall|INT_DebugMonitor|
 *                    INT_PendableSrvReq|INT_SysTick
 * @param   ipr     - interrupt priority <0-3>; lower means higher priority.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FAULT_SetIsr(src,ipr) {                                               \
                              SCB_SHCSR |= (uint32)(1l<<(src-4+16));          \
                              *SHPR_REG_PTR[SHPR_INDEX(src)] |=               \
                              (((uint32)((uint32)ipr<<4))<<SHPR_SHIFT(src));  \
                              }

/***************************************************************************//*!
 * @brief   Macro disables fault exception.
 * @param   src       <b>Fault Exceptions List:</b>
 *                    INT_NMI|INT_Hard_Fault|INT_MemManage_Fault|INT_Bus_Fault|
 *                    INT_Usage_Fault| INT_SVCall|INT_DebugMonitor|
 *                    INT_PendableSrvReq|INT_SysTick
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FAULT_ClrIsr(src)     {                                               \
                              SCB_SHCSR &= ~((uint32)(1l<<(src-4+16)));       \
                              *SHPR_REG_PTR[SHPR_INDEX(src)] &=               \
                              ~(((uint32)((uint32)0xf<<4))<<SHPR_SHIFT(src)); \
                              }

/***************************************************************************//*!
 * @brief   Macro generates system reset.
 * @details This macro generates system reset.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pe111
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 111
#endif

#define NVIC_SystemReset()    {                                               \
                                SCB_AIRCR = SCB_AIRCR_VECTKEY(0x5FA)|         \
                                            SCB_AIRCR_SYSRESETREQ_MASK;       \
                                while(1);                                     \
                              }

/******************************************************************************
* SYSTICK configuration macro definitions used by SYSTICK_Init() fucntion.
*
*//*! @addtogroup systick_config
* @{
*******************************************************************************/
/******************************************************************************
 * definition configuration structures                                        *
 ******************************************************************************/
typedef struct { uint32 CSR, RVR, CVR; } tSYSTICK;

/**************************************************************************/ /*!
 * @brief SysTick disable configuration.
 *****************************************************************************/
#define SYSTICK_DISABLE_CONFIG                                                 \
(tSYSTICK){                                                                    \
/* CSR    */  CLR(SysTick_CSR_COUNTFLAG_MASK)|SET(SysTick_CSR_CLKSOURCE_MASK)| \
              CLR(SysTick_CSR_TICKINT_MASK)|CLR(SysTick_CSR_ENABLE_MASK),      \
/* RVR    */  SET(SysTick_RVR_RELOAD(0xFFFFFF)),                               \
/* CVR    */  SET(SysTick_CVR_CURRENT(0x0)),                                   \
}

/**************************************************************************/ /*!
 * @brief SysTick counting down to zero enable with no expection configuration.
 *****************************************************************************/
#define SYSTICK_ENABLE_NO_EXCEPTION_CONFIG                                     \
(tSYSTICK){                                                                    \
/* CSR    */  CLR(SysTick_CSR_COUNTFLAG_MASK)|SET(SysTick_CSR_CLKSOURCE_MASK)| \
              CLR(SysTick_CSR_TICKINT_MASK)|SET(SysTick_CSR_ENABLE_MASK),      \
/* RVR    */  SET(SysTick_RVR_RELOAD(0xFFFFFF)),                               \
/* CVR    */  SET(SysTick_CVR_CURRENT(0x0)),                                   \
}

/**************************************************************************/ /*!
 * @brief SysTick counting down to zero enable with expection enabled
 *        configuration.
 * @param rval - 24-bit value to load into the SYST_CVR when the counter is
 *              enabled and when it reaches 0 (in range 0x00000001-0x00FFFFFF).
 * @note    To generate a multi-shot timer with a period of N processor clock
 *          cycles, use a RELOAD value of N-1. For example, if the SysTick
 *          interrupt is required every 100 clock pulses, set RELOAD to 99.
 *****************************************************************************/
#define SYSTICK_ENABLE_EXCEPTION_CONFIG(rval)                                  \
(tSYSTICK){                                                                    \
/* CSR    */  CLR(SysTick_CSR_COUNTFLAG_MASK)|SET(SysTick_CSR_CLKSOURCE_MASK)| \
              SET(SysTick_CSR_TICKINT_MASK)|SET(SysTick_CSR_ENABLE_MASK),      \
/* RVR    */  SET(SysTick_RVR_RELOAD(rval)),                                   \
/* CVR    */  SET(SysTick_CVR_CURRENT(0x0)),                                   \
}
/*! @} End of systick_config                                                  */

/******************************************************************************
* SYSTICK callback function
*
*//*! @addtogroup systick_callback
* @{
*******************************************************************************/
/*! @brief SYSTICK_CALLBACK function declaration                              */
typedef void (*SYSTICK_CALLBACK)(void);
/*! @} End of systick_callback                                                */

/******************************************************************************
* SYSTICK function and macro definitions
*
*//*! @addtogroup systick_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro resets systick.
 * @details This macro clears the field to 0, and also clears the
 *          SYST_CSR.COUNTFLAG bit to 0.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define	SYSTICK_Reset()	                SYST_CVR = 0x0;

/***************************************************************************//*!
 * @brief   Macro returns the current value of the SysTick counter.
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define	SYSTICK_GetCurrentVal()	        (uint32)SYST_CVR;

/***************************************************************************//*!
 * @brief   Macro sets starting SysTick value.
 * @details This macro specifies the start value to load into the SYST_CVR.
 * @param   val - 24-bit value to load into the SYST_CVR when the counter is
 *                enabled and when it reaches 0 (in range 0x00000001-0x00FFFFFF).
 * @note    Implemented as inlined macro.
 * @note    To generate a multi-shot timer with a period of N processor clock
 *          cycles, use a RELOAD value of N-1. For example, if the SysTick
 *          interrupt is required every 100 clock pulses, set RELOAD to 99.
 ******************************************************************************/
#define	SYSTICK_StartVal(val)             SYST_RVR = (uint32)val;

/***************************************************************************//*!
 * @brief   Macro gets number of SysTick ticks done after SysTick reset.
 * @details This macro returns number of SysTick ticks after SYSTICK_Reset()
 *          performed. Two extra ticks are substated because of LDR instruction
 *          necessary to load for current SysTick value into to Rx register.
 * @return  (uint32) Number of SysTick ticks.
 * @note    Implemented as inlined macro.
 * @warning This macro does not consider SysTick overflow. Consider the maximum
            number of tick to 16777213 (0xFFFFFF - 2).
 ******************************************************************************/
#define SYSTICK_GetTicks()	        (uint32)(SYST_RVR - SYST_CVR - 2)

/***************************************************************************//*!
 * @brief   This function provides SysTick timer initialization.
 * @param   cfg - @ref systick_config
 * @param   pCallback  Pointer to @ref SYSTICK_CALLBACK function
 * @note    Implemented as inlined macro.
 ******************************************************************************/
extern void SYSTICK_Init(tSYSTICK cfg, SYSTICK_CALLBACK pCallback);
/*! @} End of systick_macro                                                   */
/*! @} End of cm0plus_macros                                                  */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern int main(void);

/***********************************************************************/
#endif	/* _CPU_ARM_CM0_H */

