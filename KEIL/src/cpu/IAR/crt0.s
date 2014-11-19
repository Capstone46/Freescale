/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      crt0.s
 * @version   1.0.3.0
 * @date      Apr-30-2013
 * @brief     startup function (low level part).
 *
 * Revision History:
 *  1.	01/01/2010   AISG     Initially written
 *  2.	01/08/2012   B34185   Ported to Kinetis L and M
 *  3.	30/04/2013   B34185   Disable interrupts instead if enable
 ******************************************************************************/
 
;         AREA   Crt0, CODE, READONLY      ; name this block of code
  SECTION .noinit : CODE

    EXPORT  __startup
__startup
    LDR     r0,=0                  ; Initialize the GPRs
    MOV     r1,r0
    MOV     r2,r0
    MOV     r3,r0
    MOV     r4,r0
    MOV     r5,r0
    MOV     r6,r0
    MOV     r7,r0
    MOV     r8,r0
    MOV     r9,r0
    MOV     r10,r0
    MOV     r11,r0
    MOV     r12,r0

    CPSID   i                       ; Mask interrupts
    import start
    BL      start                   ; call the C code
__done
    B       __done

    END
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/