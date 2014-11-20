/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      vectors.c
 * @version   1.0.1.0
 * @date      Jun-20-2013
 * @brief     Interrupt vector table source code for Kinetis.
 * @note      This vector table is a superset table, so interrupt sources might be 
 *            listed that are not available on the specific Kinetis device you are 
 *            using.
 *
 * Revision History:
 *  1.	01/01/2010   AISG     Initially written
 *  2.	30/04/2013   B34185   Ported to Kinetis K
 ******************************************************************************/
#include "vectors.h"
#include "appconfig.h"
#include "common.h"

/******************************************************************************
* Vector Table
******************************************************************************/
typedef void (*vector_entry)(void);

#if defined(__IAR_SYSTEMS_ICC__)
	// Suppress the warning message in IAR with non - alligned member in structure.
	#pragma diag_suppress=Pa039
	#pragma location = ".intvec"
	const vector_entry  __vector_table[] = //@ ".intvec" =
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress=61
	__attribute__((section(".intvec"))) const vector_entry __vector_table[] __attribute__((used)) =
#endif
{
   VECTOR_000,           /* Initial SP           */
   VECTOR_001,           /* Initial PC           */
   VECTOR_002,
   VECTOR_003,
   VECTOR_004,
   VECTOR_005,
   VECTOR_006,
   VECTOR_007,
   VECTOR_008,
   VECTOR_009,
   VECTOR_010,
   VECTOR_011,
   VECTOR_012,
   VECTOR_013,
   VECTOR_014,
   VECTOR_015,
   VECTOR_016,
   VECTOR_017,
   VECTOR_018,
   VECTOR_019,
   VECTOR_020,
   VECTOR_021,
   VECTOR_022,
   VECTOR_023,
   VECTOR_024,
   VECTOR_025,
   VECTOR_026,
   VECTOR_027,
   VECTOR_028,
   VECTOR_029,
   VECTOR_030,
   VECTOR_031,
   VECTOR_032,
   VECTOR_033,
   VECTOR_034,
   VECTOR_035,
   VECTOR_036,
   VECTOR_037,
   VECTOR_038,
   VECTOR_039,
   VECTOR_040,
   VECTOR_041,
   VECTOR_042,
   VECTOR_043,
   VECTOR_044,
   VECTOR_045,
   VECTOR_046,
   VECTOR_047,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   KIBBLE_CONFIG,       ///> kibble configuration field
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   VECTOR_PADDING,
   CONFIG_1,
   CONFIG_2,
   CONFIG_3,
   CONFIG_4
};


/***************************************************************************//*!
 * @brief   Default interrupt service routine (IRQ for not defined vectors
            jump into this routine).
 * @details Default interrupt service routine with active and pending IRQ read
 *          posibility.
 * @return  void.
 * @note    VECTORNUM represents Interrupt Control State Register ICSR.
 ******************************************************************************/
void default_isr(void)
{
  #define VECTORNUM                     (*(volatile uint32_t*)(0xE000ED04))
  
  __asm("BKPT #0x03");
  return;
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/