/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      gpio.c
 * @version   1.0.4.0
 * @date      Jan-17-2013
 * @brief     General-Purpose Input/Output (GPIO) driver source code.
 *
 * Revision History:
 *  1.	15/01/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
#include "common.h"
#include "gpio.h"

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static PORT_CALLBACK volatile pCallbackPORTA=NULL;
static PORT_CALLBACK volatile pCallbackPORTC=NULL;
static PORT_CALLBACK volatile pCallbackPORTD=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void porta_isr (void);
void portcd_isr (void);

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
void PORTA_Init (tPORT port, uint32 pin_mask, uint8 ip, PORT_CALLBACK pCallback)
{
  register uint16 i;
  
  if (pCallback != NULL) { pCallbackPORTA = pCallback; NVIC_SetIsr(INT_PORTA,ip);}
  
  for (i=0; i<32; i++)
    if(pin_mask & (uint32)(1l << i)) { PORTA_BASE_PTR->PCR[i] = port.PCR; }  
  PORTA_ISFR &= ~pin_mask;  
}

void PORTB_Init (tPORT port, uint32 pin_mask, uint8 ip, PORT_CALLBACK pCallback)
{
  register uint16 i;

  for (i=0; i<32; i++)
    if(pin_mask & (uint32)(1l << i)) { PORTB_BASE_PTR->PCR[i] = port.PCR; }
  PORTB_ISFR &= ~pin_mask;  
}

void PORTC_Init (tPORT port, uint32 pin_mask, uint8 ip, PORT_CALLBACK pCallback)
{
  register uint16 i;
  
  if (pCallback != NULL) { pCallbackPORTC = pCallback; NVIC_SetIsr(INT_PORTCD,ip);}
  
  for (i=0; i<32; i++)
    if(pin_mask & (uint32)(1l << i)) { PORTC_BASE_PTR->PCR[i] = port.PCR; }
  PORTC_ISFR &= ~pin_mask;
}

void PORTD_Init (tPORT port, uint32 pin_mask, uint8 ip, PORT_CALLBACK pCallback)
{
  register uint16 i;

  if (pCallback != NULL) { pCallbackPORTD = pCallback; NVIC_SetIsr(INT_PORTCD,ip);}
    
  for (i=0; i<32; i++)
    if(pin_mask & (uint32)(1l << i)) { PORTD_BASE_PTR->PCR[i] = port.PCR; } 
  PORTD_ISFR &= ~pin_mask;  
}

void PORTE_Init (tPORT port, uint32 pin_mask, uint8 ip, PORT_CALLBACK pCallback)
{
  register uint16 i;
  
  for (i=0; i<32; i++)
    if(pin_mask & (uint32)(1l << i)) { PORTE_BASE_PTR->PCR[i] = port.PCR; } 
  PORTE_ISFR &= ~pin_mask;  
}

void GPIOA_Init (tGPIO gpio, uint32 pin_mask)
{
  GPIOA_PDDR = (GPIOA_PDDR & ~pin_mask) | (gpio.PDDR & pin_mask); 
}

void GPIOB_Init (tGPIO gpio, uint32 pin_mask)
{
  GPIOB_PDDR = (GPIOB_PDDR & ~pin_mask) | (gpio.PDDR & pin_mask);
}

void GPIOC_Init (tGPIO gpio, uint32 pin_mask)
{
  GPIOC_PDDR = (GPIOC_PDDR & ~pin_mask) | (gpio.PDDR & pin_mask);
}

void GPIOD_Init (tGPIO gpio, uint32 pin_mask)
{
  GPIOD_PDDR = (GPIOD_PDDR & ~pin_mask) | (gpio.PDDR & pin_mask);
}

void GPIOE_Init (tGPIO gpio, uint32 pin_mask)
{
  GPIOE_PDDR = (GPIOE_PDDR & ~pin_mask) | (gpio.PDDR & pin_mask);
}

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void porta_isr (void) 
{ 
  register uint32 temp32 = PORTA_ISFR;
  PORTA_ISFR = temp32;             /* clear peripheral interrupt flags       */
  /* process interrupt callback function                                      */  
  if (pCallbackPORTA != (PORT_CALLBACK)NULL) { pCallbackPORTA (temp32); }
}

void portcd_isr (void) 
{ 
  register uint32 u32TempC = PORTC_ISFR, u32TempD = PORTD_ISFR;
  PORTC_ISFR = u32TempC;             /* clear peripheral interrupt flags       */
  PORTD_ISFR = u32TempD;             /* clear peripheral interrupt flags       */
  /* process interrupt callback function                                      */  
  if (pCallbackPORTC != (PORT_CALLBACK)NULL)  
  { 
    pCallbackPORTC (u32TempC); 
  }
  if (pCallbackPORTD != (PORT_CALLBACK)NULL)  
  { 
    pCallbackPORTD (u32TempD); 
  }
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
