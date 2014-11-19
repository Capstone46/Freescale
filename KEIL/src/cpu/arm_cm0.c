/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      arm_cm0.c
 * @version   1.0.4.0
 * @date      Mar-1-2013
 * @brief     arm_cm0 driver implementation.
 *
 * Revision History:
 *  1.	01/01/2010   AISG     Initially written
 *  2.	01/08/2012   B34185   Ported to Kinetis L
 *  3.	24/09/2012   R55013   Ported to Kinetis M
 *  4.	17/01/2013   B34185   Re-written for Kinetis L
 *  5.	26/02/2013   B34185   Kinetis L - Systick feature added
 ******************************************************************************/
#include "common.h"
#include "arm_cm0.h"

/***********************************************************************/
/*
 * Configures the ARM system control register for STOP (deep sleep) mode
 * and then executes the WFI instruction to enter the mode.
 *
 * Parameters:
 * none
 *
 * Note: Might want to change this later to allow for passing in a parameter
 *       to optionally set the sleep on exit bit.
 */

void stop (void)
{
	/* Set the SLEEPDEEP bit to enable deep sleep mode (STOP) */
	SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK;	

	/* WFI instruction will start entry into STOP mode */
	asm("WFI");
}
/***********************************************************************/
/*
 * Configures the ARM system control register for WAIT (sleep) mode
 * and then executes the WFI instruction to enter the mode.
 *
 * Parameters:
 * none
 *
 * Note: Might want to change this later to allow for passing in a parameter
 *       to optionally set the sleep on exit bit.
 */

void wait (void)
{
	/* Clear the SLEEPDEEP bit to make sure we go into WAIT (sleep) mode instead
	 * of deep sleep.
	 */
	SCB_SCR &= ~SCB_SCR_SLEEPDEEP_MASK;	

	/* WFI instruction will start entry into WAIT mode */
	asm("WFI");
}
/***********************************************************************/
/*
 * Change the value of the vector table offset register to the specified value.
 *
 * Parameters:
 * vtor     new value to write to the VTOR
 */

void write_vtor (int vtor)
{
        /* Write the VTOR with the new value */
        SCB_VTOR = vtor;	
}


/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static SYSTICK_CALLBACK pCallbackSYSTICK=NULL;

/******************************************************************************
 * interrupt function prototypes                                              *
 ******************************************************************************/
void systick_isr (void);

/******************************************************************************
 * SYSTICK initialization function                                            *
 ******************************************************************************/
void SYSTICK_Init(tSYSTICK cfg, SYSTICK_CALLBACK pCallback)
{
  volatile unsigned int dummy = SYST_CSR;
  
  if (pCallback != NULL)  
  { 
    pCallbackSYSTICK = pCallback;
  }
  SYST_RVR = cfg.RVR;
  SYST_CSR = cfg.CSR;
}

/******************************************************************************
 * SYSTICK interrupt functions definitions                                    *
 ******************************************************************************/
void systick_isr(void)
{
  volatile unsigned int dummy = SYST_CSR;
  
  pCallbackSYSTICK ();
}

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/



