;/*****************************************************************************
; * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
; * ALL RIGHTS RESERVED.
; ***************************************************************************//*!
; * @file      crt0.s
; * @version   1.0.3.0
; * @date      May-08-2013
; * @brief     startup function (low level part).
; *
; * Revision History:
; *  1.	08/05/2013   B34185	 Initially written
; *  2.	03/12/2013   B34185	 Re-written for Kinetis L
; *  3.	20/01/2014   B34185	 BOOT_STACK_ADDRESS eliminated
; ******************************************************************************/

;         AREA   Crt0, CODE, READONLY      ; name this block of code
                AREA    |.text|, CODE, READONLY

__startup   	PROC
                EXPORT  __startup             [WEAK]
				MOVS    R0,#0x0               ; Initialize the GPRs
				MOV     R1,R0
				MOV     R2,R0
				MOV     R3,R0
				MOV     R4,R0
				MOV     R5,R0
				MOV     R6,R0
				MOV     R7,R0
				MOV     R8,R0
				MOV     R9,R0
				MOV     R10,R0
				MOV     R11,R0
				MOV     R12,R0
				CPSID   i                   ; Disable interrupts by default
                IMPORT  start
                BL     	start
__done                          			; endless loop
                B       __done
                ENDP

                END
;/******************************************************************************
; * End of module                                                              *
; ******************************************************************************/