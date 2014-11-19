/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      mcg_lite.c
 * @version   1.0.9.0
 * @date      May-22-2013
 * @brief     Multipurpose clock generator lite driver source file.
 *
 * Revision History:
 *  1.	16/12/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
#include "common.h"
#include "mcg_lite.h"


#if (defined (MCU_MKL43Z256))

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
void MCG_LITE_Init (tMCG_LITE mcglite)
{   
  // switch to HIRC mode when moving between LIRC2 and LIRC8 modes
  if (((MCG_S&MCG_S_CLKST(0x1)) && (mcglite.C1&MCG_C1_CLKS(0x1))) &&
      ((MCG_C2&MCG_C2_IRCS_MASK) != (mcglite.C2&MCG_C2_IRCS_MASK)))
  {
    MCG_MC |= MCG_MC_HIRCEN_MASK;
    MCG_C1 = MCG_C1_CLKS(0x0);
    WAIT_FOR_STATUS_FLAG (MCG_C1, CLKS, CLKST);
  }
  // set LIRC first divider  
  MCG_SC = mcglite.SC;
  // configure external clock if selected (if not let the previous configuration)
  // or switch between 2MHz and 8Mhz LIRC
  MCG_C2 = (MCG_C2&0x3C)|mcglite.C2;
  // if oscilator selected as ext. clock source wait for initialization cycles done
  if (MCG_C2 & MCG_C2_EREFS0_MASK) 
  { 
    WAIT_FOR_STATUS_FLAG (MCG_C2, EREFS0, OSCINIT0); 
  }
  // Enable HIRC if required
  // Note: do not disable HIRC yet if currently in HIRC mode
  MCG_MC |= (mcglite.MC&MCG_MC_HIRCEN_MASK);
  // select clock source
  MCG_C1 = mcglite.C1;
  // Write all correct required data
  MCG_C2 = mcglite.C2;
  // wait for proper clock source selection (valid for all modes EXTCLK, HIRC, LIRC)
  WAIT_FOR_STATUS_FLAG (MCG_C1, CLKS, CLKST);
  // disable HIRC if required and select second LIRC divider
  MCG_MC = mcglite.MC;
}
#endif
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/


   
   



