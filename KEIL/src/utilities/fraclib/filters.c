/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      filters.c
 * @author    B34185
 * @version   1.0.2.0
 * @date      Aug-29-2012
 * @brief     FILTER driver implementation.	
 ******************************************************************************/
#include "filters.h"

/******************************************************************************
 * Filter function definition                                                 *
 ***************************************************************************//*!
 * @brief	Low-pass filter initialization
 ******************************************************************************/
void floatLPfilter_Init(_FLOAT_FILTER_DATA *pFltrData, 
                        float f0, float Ts, float Init_value)
{
  float	X0 = 0;		
  float	X1 = 0;		
  X0 = 3.14159 * f0 * Ts;
  X1 = X0 + 1;
  pFltrData->X_n1 = 0;
  pFltrData->Y_n1 = Init_value;
  pFltrData->A0 = X0 / X1;
  pFltrData->A1 = pFltrData->A0;
  X0 = X0 - 1;
  pFltrData->B1 = X0 / X1;
}

void frac32LPfilter_Init(_FRAC32_FILTER_DATA *pFltrData,
                         float f0, float Ts, Frac32 Init_value)
{
  float k0, k1;
  k0 = DOUBLE_PI_F * f0 * Ts;
  k1 = 1.0/(k0+2.0);
  pFltrData->X_n1 = FRAC32(0);
  pFltrData->Y_n1 = Init_value;
  pFltrData->A0 = FRAC32(k0*k1);
  pFltrData->A1 = pFltrData->A0;
  pFltrData->B1 = FRAC32((k0-2)*k1);
}

void frac16LPfilter_Init(_FRAC16_FILTER_DATA *pFltrData,
                         float f0, float Ts, Frac16 Init_value)
{
  float k0, k1;
  k0 = DOUBLE_PI_F * f0 * Ts;
  k1 = 1.0/(k0+2.0);
  pFltrData->X_n1 = FRAC16(0);
  pFltrData->Y_n1 = Init_value;
  pFltrData->A0 = FRAC16(k0*k1);
  pFltrData->A1 = pFltrData->A0;
  pFltrData->B1 = FRAC16((k0-2)*k1);
}

float floatLPfilter(_FLOAT_FILTER_DATA *pFltrData, float *pIn)
{
float 	Yn   = 0;		
float	PF_0 = 0;		
float 	PF_1 = 0;		
float	PF_2 = 0;		
  PF_0 = pFltrData->A0 * (*pIn);			
  PF_1 = pFltrData->A1 * pFltrData->X_n1;
  PF_2 = pFltrData->B1 * pFltrData->Y_n1;
  Yn = PF_0 + PF_1 - PF_2;
  pFltrData->X_n1 = *pIn;	
  pFltrData->Y_n1 = Yn;
return	Yn;		
}
/*
static inline Frac32 frac32LPfilter(_FRAC32_FILTER_DATA *pFltrData, Frac32 *pIn)
{
Frac32 	Yn;		
  Yn = L_mul(pFltrData->B1, pFltrData->Y_n1);
  Yn = L_mul(pFltrData->A1, pFltrData->X_n1) - Yn;
  Yn = L_mul(pFltrData->A0, *pIn) + Yn;
  pFltrData->X_n1 = *pIn;	
  pFltrData->Y_n1 = Yn;
return	Yn;		
}
*/
//---------------------------------------------------------------------------------
// End of Pre-filter Function 
//---------------------------------------------------------------------------------

