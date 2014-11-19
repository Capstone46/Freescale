/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : WAIT1.c
**     Project     : GitHubGuyKL46Project
**     Processor   : MKL46Z256VLL4
**     Component   : Wait
**     Version     : Component 01.057, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-11-17, 14:38, # CodeGen: 19
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         Wait10Cycles  - void WAIT1_Wait10Cycles(void);
**         Wait100Cycles - void WAIT1_Wait100Cycles(void);
**         WaitCycles    - void WAIT1_WaitCycles(word cycles);
**         Waitms        - void WAIT1_Waitms(word ms);
**         Waitus        - void WAIT1_Waitus(word us);
**         Waitns        - void WAIT1_Waitns(word ns);
**         WaitOSms      - void WAIT1_WaitOSms(void);
**
**     License   :  Open Source (LGPL)
**     Copyright : (c) Copyright Erich Styger, 2012, all rights reserved.
**     This an open source software implementing waiting routines using Processor Expert.
**     This is a free software and is opened for education,  research  and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file WAIT1.c
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup WAIT1_module WAIT1 module documentation
**  @{
*/         

/* MODULE WAIT1. */

#include "WAIT1.h"

/* tell the compiler not to inline functions in this module, as they are timing critical */

/*
** ===================================================================
**     Method      :  WAIT1_Wait10Cycles (component Wait)
**     Description :
**         Wait for approximately 10 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void WAIT1_Wait10Cycles(void)
{
  /* This function will wait 10 CPU cycles (including call overhead). */
  /* NOTE: this is not really accurate, as not sure yet about the cycle counts. Assuming 1 cycle for a NOP */
  asm(
   "nop \n\t"
   "nop \n\t"
   "nop \n\t"
   "nop \n\t"
   "nop \n\t"
   "nop \n\t"
   "nop \n\t"
   "nop \n\t"
   "nop \n\t"
   "nop \n\t"
  );
}

/*
** ===================================================================
**     Method      :  WAIT1_Wait100Cycles (component Wait)
**     Description :
**         Wait for 100 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void WAIT1_Wait100Cycles(void)
{
  /* This function will spend 100 CPU cycles (including call overhead). */
  volatile byte i;
  for(i=0; i<133; i++) {
    /* NOTE: this is not really accurate, as not sure yet about the cycle counts. Assuming 0.75 cycle for a NOP */
    asm(
     "nop \n\t"
    );
  } /* just something to wait, NOT the requested 100 cycles */
}
/*
** ===================================================================
**     Method      :  WAIT1_WaitCycles (component Wait)
**     Description :
**         Wait for 100 CPU cycles.
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/
void WAIT1_WaitCycles(word cycles)
{
  while(cycles > 100) {
    WAIT1_Wait100Cycles();
    cycles -= 100;
  }
}

/*
** ===================================================================
**     Method      :  WAIT1_Waitms (component Wait)
**     Description :
**         Wait for a specified time in milliseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ms              - How many milliseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/
void WAIT1_Waitms(word ms)
{
  /* we do not have Cpu_Delay100US() for Kinetis: using a different (not exact) method */
  while (ms>0) {
    WAIT1_WaitCycles(1000);
    ms--;
  }
}
/*
** ===================================================================
**     Method      :  WAIT1_Waitus (component Wait)
**     Description :
**         Wait for a specified time in microseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us              - How many microseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/
/* implemented as macro version. See header file. */
/*
** ===================================================================
**     Method      :  WAIT1_Waitns (component Wait)
**     Description :
**         Wait for a specified time in nano seconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ns              - How many ns the function has to wait
**     Returns     : Nothing
** ===================================================================
*/
/* implemented as macro version. See header file. */
/*
** ===================================================================
**     Method      :  WAIT1_WaitOSms (component Wait)
**     Description :
**         If an RTOS is enabled, this routine will use a non-blocking
**         wait method. Otherwise it will do a busy/blocking wait.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if 0
void WAIT1_WaitOSms(void)
{
  /* Method is implemented as macro in the header file */
}
#endif

/* END WAIT1. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
