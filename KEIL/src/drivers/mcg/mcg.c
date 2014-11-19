/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      mcg.c
 * @version   1.0.4.0
 * @date      Apr-30-2013
 * @brief     Multipurpose clock generator (MCG) driver source file.
 *
 * Revision History:
 *  1.	05/04/2013   B34185   Initially written
 *  2.	26/11/2013   B34185   Re-writen for Kinetis L
 ******************************************************************************/
#include "common.h"
#include "mcg.h"

#if (defined (MCU_MKL46Z256))
/******************************************************************************
 * macro definitions                                                          *
 ******************************************************************************/
#define WAIT_FOR_STATUS_FLAG(reg,name1,name2)                                 \
{                                                                             \
  while (((MCG_S&MCG_S_##name2##_MASK)>>MCG_S_##name2##_SHIFT)!=              \
    ((reg&##reg##_##name1##_MASK)>>##reg##_##name1##_SHIFT));                 \
}
    
/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static MCG_CALLBACK volatile pCallbackMCG=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void mcg_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
#endif
/***************************************************************************//*!
 * @brief   FLL initialization function.
 * @param   mcg - @ref mcg_config
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
void FLL_Init (tMCG fll)
{   
  MCG_SC = fll.SC;
  MCG_C8 = fll.C8;
  MCG_C7 = fll.C7;
  // change FRDIV before FLL DCO range selection (to avoid DCO output overrange)
  MCG_C1 = (fll.C1&MCG_C1_FRDIV(3))|(MCG_C1&(~MCG_C1_FRDIV(3))); 
  MCG_C4 = fll.C4;
  // wait for FLL factor setup properly
  while ((MCG_C4 & MCG_C4_DRST_DRS_MASK) != (fll.C4 & MCG_C4_DRST_DRS_MASK));
  // if external reference running do not process any change to it yet
  // if slow or fast IRC is changing during this function call do not change it yet
  switch(MCG_S&0x1C)
  {
    // if currently FEE or FBE is running 
    case 0x0: 
    case 0x08: MCG_C2 = (fll.C2&0x3C)|MCG_C2; break;
    // if currently FBI is running
    case 0x14: MCG_C2 = (fll.C2&0x3D)|MCG_C2; break;
    default: MCG_C2 = fll.C2; break;
  }
  // if oscilator selected wait for initialization cycles done
  if (MCG_C2 & MCG_C2_EREFS0_MASK) 
  { 
    WAIT_FOR_STATUS_FLAG (MCG_C2, EREFS0, OSCINIT0); 
  }
  MCG_C1 = fll.C1;
  // delay inserted because of errata ERRATA ID: 5573
  arch_delay(10000);  
  // wait for FLL reference clock selection 
  WAIT_FOR_STATUS_FLAG (MCG_C1, IREFS, IREFST);
  // wait for MSGOUTCLK selection (valid for all modes except PLL)
  WAIT_FOR_STATUS_FLAG (MCG_C1, CLKS, CLKST);
  // make additional changes of MCG_C2 here
  MCG_C2 = fll.C2;
  // wait for internal reference selection fixation
  WAIT_FOR_STATUS_FLAG (MCG_C2, IRCS, IRCST);
  MCG_C6 = fll.C6;
  // wait for FLL selection fixation (when moving from PBE to FBE)
  WAIT_FOR_STATUS_FLAG (MCG_C6, PLLS, PLLST);
}

/***************************************************************************//*!
 * @brief   PLL initialization function.
 * @param   mcg - @ref mcg_config
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
void PLL_Init (tMCG pll)
{   
  // avoid entering pll from other than bypass external or PEE modes
  if (!(MCG_S&MCG_S_CLKST(0x2)))
    return;
  MCG_C8 = pll.C8;  
  //we assume that the external reference is already set by the mode selected before
  //follow the MCG mode state diagram
  MCG_C2 = pll.C2;
  //if crystal oscilator selected wait for initialization cycles done 
  //before PLLCLKEN0 is being set OSCINIT0 should be checked
  if (MCG_C2 & MCG_C2_EREFS0_MASK) { WAIT_FOR_STATUS_FLAG (MCG_C2, EREFS0, OSCINIT0);}
  MCG_C5 = pll.C5;
  MCG_C6 = pll.C6;
  // wait for PLL source selection
  WAIT_FOR_STATUS_FLAG (MCG_C6, PLLS, PLLST);
  // wait for PLL lock 
  WAIT_FOR_STATUS_FLAG (MCG_S, LOCK0, LOCK0);
  // now PBE selected ...

  // Select output of PLL as system clock if required
  MCG_C1 = pll.C1;
  asm("nop");
  if (!(MCG_C1&MCG_C1_CLKS_MASK))
  {
    // wait for PLL output selection (when moving from PBE to PEE)
    while (((MCG_S&MCG_S_CLKST_MASK) != MCG_S_CLKST_MASK) && ((MCG_C1&MCG_C1_CLKS_MASK) != 0x00));
  }
  else
  {
    // wait for ext. reference clock selection (when moving from PEE to PBE)
    WAIT_FOR_STATUS_FLAG (MCG_C1, CLKS, CLKST);
  }
}

void MCG_InstallCallback (uint8 ip, MCG_CALLBACK pCallback)
{ 
  if (pCallback != NULL) 
  { 
    pCallbackMCG = pCallback; 
    NVIC_SetIsr(INT_MCG, ip);
  }
  else  
  { 
    NVIC_ClrIsr(INT_MCG);
  }
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void mcg_isr (void) 
{ 
  if (pCallbackMCG != (MCG_CALLBACK)NULL)
  {
    if (MCG_SC & MCG_SC_LOCS0_MASK)
    {
      MCG_SC = (MCG_SC&~(!MCG_SC_LOCS0_MASK))|MCG_SC_LOCS0_MASK;      /* clear interrupt flag         */
      pCallbackMCG (LOC_CALLBACK);
    }
    if (MCG_S & MCG_S_LOLS_MASK)
    {
      MCG_S = (MCG_S&(!MCG_S_LOLS_MASK))|MCG_S_LOLS_MASK;        /* clear interrupt flag          */
      pCallbackMCG (LOL_CALLBACK);
    }
  }
}

#endif

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
