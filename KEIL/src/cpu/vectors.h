/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      vectors.h
 * @version   1.0.1.0
 * @date      Jun-20-2013
 * @brief     Interrupt vector table header file.
 * @note      This vector table is a superset table, so interrupt sources might be 
 *            listed that are not available on the specific Kinetis device you are 
 *            using.
 *
 * Revision History:
 *  1.	01/01/2010   AISG     Initially written
 *  2.	30/04/2013   B34185   Ported to Kinetis K
 *  3.	17/11/2013   B34185   Ported to Kinetis L (in general, vector numbers used by *.h)
 ******************************************************************************/
#ifndef __VECTORS_H
#define __VECTORS_H  

// function prototype for default_isr in vectors.c
void default_isr(void);

/* Interrupt Vector Table Function Pointers */
typedef void pointer(void);

extern void __startup(void);
#if defined(__IAR_SYSTEMS_ICC__)
	extern void __iar_program_start(void);
	extern unsigned long __BOOT_STACK_ADDRESS[];
#elif defined(__ARMCC_VERSION)
	extern unsigned long Image$$ARM_LIB_STACK$$Base;
	#define __BOOT_STACK_ADDRESS	&Image$$ARM_LIB_STACK$$Base
#endif


                                        // Address     Vector IRQ   Source module   Source description
#define VECTOR_000      (pointer*)__BOOT_STACK_ADDRESS	//          ARM core        Initial Supervisor SP
#define VECTOR_001      __startup				// 0x0000_0004 1 -          ARM core        Initial Program Counter
#define VECTOR_002      default_isr     // 0x0000_0008 2 -          ARM core        Non-maskable Interrupt (NMI)
#define VECTOR_003      default_isr     // 0x0000_000C 3 -          ARM core        Hard Fault
#define VECTOR_004      default_isr     // 0x0000_0010 4 -
#define VECTOR_005      default_isr     // 0x0000_0014 5 -          
#define VECTOR_006      default_isr     // 0x0000_0018 6 -          
#define VECTOR_007      default_isr     // 0x0000_001C 7 -                           
#define VECTOR_008      default_isr     // 0x0000_0020 8 -                           
#define VECTOR_009      default_isr     // 0x0000_0024 9 -
#define VECTOR_010      default_isr     // 0x0000_0028 10 -
#define VECTOR_011      default_isr     // 0x0000_002C 11 -         ARM core         Supervisor call (SVCall)
#define VECTOR_012      default_isr     // 0x0000_0030 12 -         
#define VECTOR_013      default_isr     // 0x0000_0034 13 -                          
#define VECTOR_014      default_isr     // 0x0000_0038 14 -         ARM core         Pendable request for system service (PendableSrvReq)
#define VECTOR_015      default_isr     // 0x0000_003C 15 -         ARM core         System tick timer (SysTick)
#define VECTOR_016      default_isr     // 0x0000_0040 16     0     DMA              DMA Channel 0 transfer complete
#define VECTOR_017      default_isr     // 0x0000_0044 17     1     DMA              DMA Channel 1 transfer complete
#define VECTOR_018      default_isr     // 0x0000_0048 18     2     DMA              DMA Channel 2 transfer complete
#define VECTOR_019      default_isr     // 0x0000_004C 19     3     DMA              DMA Channel 3 transfer complete
#define VECTOR_020      default_isr     // 0x0000_0050 20     4     
#define VECTOR_021      default_isr     // 0x0000_0054 21     5     
#define VECTOR_022      default_isr     // 0x0000_0058 22     6     
#define VECTOR_023      default_isr     // 0x0000_005C 23     7     
#define VECTOR_024      default_isr     // 0x0000_0060 24     8     
#define VECTOR_025      default_isr     // 0x0000_0064 25     9     
#define VECTOR_026      default_isr     // 0x0000_0068 26    10    
#define VECTOR_027      default_isr     // 0x0000_006C 27    11     
#define VECTOR_028      default_isr     // 0x0000_0070 28    12     
#define VECTOR_029      default_isr     // 0x0000_0074 29    13     
#define VECTOR_030      default_isr     // 0x0000_0078 30    14     
#define VECTOR_031      default_isr     // 0x0000_007C 31    15     
#define VECTOR_032      default_isr     // 0x0000_0080 32    16     
#define VECTOR_033      default_isr     // 0x0000_0084 33    17     
#define VECTOR_034      default_isr     // 0x0000_0088 34    18     
#define VECTOR_035      default_isr     // 0x0000_008C 35    19     
#define VECTOR_036      default_isr     // 0x0000_0090 36    20     
#define VECTOR_037      default_isr     // 0x0000_0094 37    21     
#define VECTOR_038      default_isr     // 0x0000_0098 38    22     
#define VECTOR_039      default_isr     // 0x0000_009C 39    23	    
#define VECTOR_040      default_isr     // 0x0000_00A0 40    24     
#define VECTOR_041      default_isr     // 0x0000_00A4 41    25     
#define VECTOR_042      default_isr     // 0x0000_00A8 42    26     
#define VECTOR_043      default_isr     // 0x0000_00AC 43    27     
#define VECTOR_044      default_isr     // 0x0000_00B0 44    28     
#define VECTOR_045      default_isr     // 0x0000_00B4 45    29     
#define VECTOR_046      default_isr     // 0x0000_00B8 46    30     
#define VECTOR_047      default_isr     // 0x0000_00BC 47    31     
#define VECTOR_PADDING  (pointer*)0xffffffff/*not used*/
#define KIBBLE_CONFIG   (pointer*)0xffffffff/*kibble configuration field*/

/* Flash configuration field values below */
/* Please be careful when modifying any of
 * the values below as it can secure the 
 * flash (possibly permanently).
 */
#define CONFIG_1		(pointer*)0xffffffff 
#define CONFIG_2		(pointer*)0xffffffff 
#define CONFIG_3		(pointer*)0xffffffff
#define CONFIG_4		(pointer*)0xfffffffe
//#define CONFIG_4		(pointer*)0xfffffffe //b5=1,b4=1,b0=1 div1 fast
//#define CONFIG_4	(pointer*)0xffffdffe //b5=0,b4=1,b0=1 div1 slow works
//#define CONFIG_4	(pointer*)0xffffcefe //b5=0,b4=0,b0=0;div8 slow
//#define CONFIG_4	(pointer*)0xffffeefe //b5=1,b4=0,b0=0 div8 fast 
//#define CONFIG_4	(pointer*)0xffffcffe //b5=0,b4=0,b0=1;div4 slow
//#define CONFIG_4	(pointer*)0xffffeffe //b5=1,b4=0,b0=1;div4 fast
//#define CONFIG_4	(pointer*)0xfffffefe //b5=1,b4=1,b0=0;div2 fast
//#define CONFIG_4	(pointer*)0xffffdefe //b5=0,b4=1,b0=0;div2 slow 

#endif /*__VECTORS_H*/

