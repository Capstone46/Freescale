/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      start.c
 * @version   1.0.3.0
 * @date      Jun-12-2013
 * @brief     startup function (high level part).
 *
 * Revision History:
 *  1.	01/01/2010   AISG     Initially written
 *  2.	01/08/2012   B34185   Ported to Kinetis L and M
 ******************************************************************************/
#include "start.h"
#include "common.h"
#include "sim.h"

/******************************************************************************
 * Common_startup function definition - function calls all of the needed      *
 * startup routines and then branches to the main process.                    *
 ******************************************************************************/
void start(void)
{ 
#ifndef WDOG_ENABLED
  /* Disable the watchdog timer */
  SIM_COPC = 0x00;
#endif
  if(RCM_MR&0x6)
    {
      RCM_FM = 0x0;
      RCM_MR = 0x6;
    }
  /* Copy any vector or data sections that need to be in RAM */
  common_startup();

  /* Jump to main process */
  main();

  /* No actions to perform after this so wait forever */
  while(1);
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/

