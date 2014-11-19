/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      arch_delay.s
 * @version   1.0.2.0
 * @date      Jan-17-2013
 * @brief     Module with generic delay function delaying software execution 
 *            for given number of core clock ticks.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	10/08/2012   R55013   Ported to Cortex-M0+
 ******************************************************************************/

;     AREA   arch_delay, CODE, READONLY      ; name this block of code
  SECTION .text : CODE
      EXPORT  arch_delay
arch_delay
      subs  r0,#8   ; subtract function entry and exit code execution ticks
loop: subs  r0,#5
      bpl   loop   
      bx    lr
      end
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/