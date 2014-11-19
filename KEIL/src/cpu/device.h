/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      device.h
 * @version   1.0.1.0
 * @date      Jun-20-2013
 * @brief     Device header file for CMSIS support (arm_math included).
 *
 * Revision History:
 *  1.	17/05/2013   B34185   Initially written
 *  2.	25/11/2013   B34185   Updated for CM0 devices
 ******************************************************************************/
#ifndef __DEVICE_H
#define __DEVICE_H

#ifdef __cplusplus
  extern "C" {
#endif

typedef enum IRQn
{
/******  Cortex-M4 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4/M0 Memory Management Interrupt           */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                      */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                    */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4/M0 SV Call Interrupt                    */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                 */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4/M0 Pend SV Interrupt                    */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M4/M0 System Tick Interrupt                */
} IRQn_Type;
/* __NVIC_PRIO_BITS and others have to be defined for CMSIS 2.x or newer  *************************/

#if defined(MCU_MKL25Z128)||defined(MCU_MKL46Z256)||defined(MCU_MKL43Z256)
		#define __CM0_REV                 0x0001    /*!< Core Revision r0p1                               */
		#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels          */
		#define __Vendor_SysTickConfig    1         /*!< Set to 1 if different SysTick Config is used     */
		#define __MPU_PRESENT             0         /*!< MPU present or not                               */
		#include "core_cm0.h"
		#if defined ( __CC_ARM   )
			#pragma anon_unions
		#endif
		#if   (defined(MCU_MKL25Z128))
		  #include "MKL25Z128LK4.h"
		#elif (defined(MCU_MKL46Z256))
		  #include "MKL46Z4.h"
		#elif (defined(MCU_MKL43Z256))
		  #include "MKL43Z4.h"
		#else  
		  #error "No valid CPU defined."
		#endif
		#if defined ( __CC_ARM   )
			#pragma no_anon_unions
		#endif
#else
  #error "No valid CPU defined."
#endif

// For CMSIS DSP Library
#define ARM_MATH_CM0
#include "arm_math.h"

#ifdef __cplusplus
}
#endif

#endif /* __DEVICE_H */
