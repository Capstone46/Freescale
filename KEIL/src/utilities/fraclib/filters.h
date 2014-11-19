/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      filters.h
 * @author    B34185
 * @version   1.0.2.0
 * @date      Aug-29-2012
 * @brief     Filter driver header file.
 ******************************************************************************/
#ifndef __FILTERS_H
#define __FILTERS_H 

#include "FRACLIB_Inlines.h"
#include "FRACLIB_Types.h"

#define DOUBLE_PI_F  6.283185307179f

/******************************************************************************
 * Filters data structure definition                                           *
 ******************************************************************************/
typedef struct
{ float f0, Ts, A0, A1, B1, X_n1, Y_n1, Y_init; }_FLOAT_FILTER_DATA;

typedef struct
{float f0; float Ts; Frac32 A0, A1, B1, X_n1, Y_n1, Y_init; }_FRAC32_FILTER_DATA;

typedef struct
{float f0; float Ts; Frac16 A0, A1, B1, X_n1, Y_n1, Y_init; }_FRAC16_FILTER_DATA;

/******************************************************************************
 * Filters function prototypes                                                 *
 ***************************************************************************//*!
 * @brief	output function: Y(n) = A0.X(n) + A1.X(n-1) - B1.Y(n-1)
 * 		coeffiecients:   A0 = A1 = Ts / (2tau + Ts)
 * 				 B1 = (Ts - 2tau) / (2tau + Ts)
 * 		parameters:	 Tsamp - sampling frequency
 * 				 tau - time constant -> tau = RC
 * 				 f0 - cut of frequency
 ******************************************************************************/
void floatLPfilter_Init(_FLOAT_FILTER_DATA *pFltrData, float f0, float Ts,      \
                        float Init_value);
float floatLPfilter(_FLOAT_FILTER_DATA *pFltrData, float *pIn);

void frac32LPfilter_Init(_FRAC32_FILTER_DATA *pFltrData, float f0, float Ts,    \
                         Frac32 Init_value);

//static inline Frac32 frac32LPfilter(_FRAC32_FILTER_DATA *pFltrData, Frac32 *pIn);
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

void frac16LPfilter_Init(_FRAC16_FILTER_DATA *pFltrData, float f0, float Ts,    \
                         Frac16 Init_value);

static inline Frac16 frac16LPfilter(_FRAC16_FILTER_DATA *pFltrData, Frac16 *pIn)
{
Frac16 	Yn;		
  Yn = S_mul_ss(pFltrData->B1, pFltrData->Y_n1);
  Yn = S_mul_ss(pFltrData->A1, pFltrData->X_n1) - Yn;
  Yn = S_mul_ss(pFltrData->A0, *pIn) + Yn;
  pFltrData->X_n1 = *pIn;	
  pFltrData->Y_n1 = Yn;
return	Yn;		
}

#endif /* __FILTERS_H */ 



