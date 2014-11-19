/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      vref.h
 * @version   1.0.1.0
 * @date      Jun-20-2013
 * @brief     Voltage reference (VREF) driver header file.
 *
 * Revision History:
 *  1.	14/01/2014   B34185   Initially written for Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup vref_example0
 * @{
 * @par       Source code:
 * @include   vref0_test\vref0_test.c
 * @par       Appconfig.h:
 * @include   vref0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of vref_example0                                                   */
#ifndef __VREF_H
#define __VREF_H 
 
/******************************************************************************
 * definition configuration structure                                         *
 ******************************************************************************/
typedef struct { uint8 SC; } tVREF;

/******************************************************************************
* VREF default configurations used by VREF_init() function
*
*//*! @addtogroup vref_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
  * @brief Default VREF configuration.
  *****************************************************************************/
/**************************************************************************/ /*!
  * @brief VREF disabled.
  *****************************************************************************/
#define VREF_DISABLE_CONFIG            /* disabled mode            	      */  \
(tVREF){                                                                      \
/* SC      */ CLR(VREF_SC_VREFEN_MASK)|CLR(VREF_SC_REGEN_MASK)|               \
              CLR(VREF_SC_ICOMPEN_MASK)|SET(VREF_SC_MODE_LV(0))               \
}

/**************************************************************************/ /*!
 * @brief 	Start up VREF configuration with bandgap only (no buffer).
 * @detail	The internal VREF bandgap is enabled to generate an accurate 1.2 V 
 *		output that can be trimmed with the TRM register's TRIM[5:0] bitfield.
 * @note	The settling time of internal bandgap reference is typically 35ms,
 *		which means there is 35ms delay after the bandgap is enabled, the 
 *		SC[VREFST] can only be useful after the bandgap is stable after the 
 *		settling time.
 * @warning	When the Voltage Reference is already enabled and stabilized, changing
 *		SC[MODE_LV] will not clear SC[VREFST] but there will be some startup 
 *		time before the output voltage at the VREF_OUT pin has settled. 
 *		This is the buffer start up delay (Tstup) and the value is specified
 *		in the appropriate device data sheet. Also, there will be some settling
 *		time when a step change of the load current is applied to the VREF_OUT pin.
  *****************************************************************************/
#define VREF_BANDGAP_ONLY_CONFIG        /* bandgap only mode        */        \
(tVREF){                                                                      \
/* SC      */ SET(VREF_SC_VREFEN_MASK)|SET(VREF_SC_REGEN_MASK)|               \
              SET(VREF_SC_ICOMPEN_MASK)|SET(VREF_SC_MODE_LV(0))               \
}

/**************************************************************************/ /*!
 * @brief 	VREF works as high power buffer mode.
 * @detail 	The internal VREF bandgap is on. The high power buffer is enabled 
 *		to generate a buffered 1.2 V voltage to VREF_OUT. It can also be 
 *		used as a reference to internal analog peripherals such as an ADC 
 *		channel or analog comparator input. In this mode, a 100 nF capacitor 
 *		is required to connect between the VREF_OUT pin and VSSA.
 * @note        The settling time of internal bandgap reference is typically 35ms,
 *		which means there is 35ms delay after the bandgap is enabled, the 
 *		SC[VREFST] can only be useful after the bandgap is stable after the 
 *		settling time.
 * @warning	When the Voltage Reference is already enabled and stabilized, changing
 *              SC[MODE_LV] will not clear SC[VREFST] but there will be some startup 
 *              time before the output voltage at the VREF_OUT pin has settled. 
 *              This is the buffer start up delay (Tstup) and the value is specified
 *              in the appropriate device data sheet. Also, there will be some settling
 *              time when a step change of the load current is applied to the VREF_OUT pin.
  *****************************************************************************/
#define VREF_HIGH_POWER_CONFIG          /*     high power mode       */       \
(tVREF){                                                                      \
/* SC      */ SET(VREF_SC_VREFEN_MASK)|SET(VREF_SC_REGEN_MASK)|               \
              SET(VREF_SC_ICOMPEN_MASK)|SET(VREF_SC_MODE_LV(1))               \
}

/**************************************************************************/ /*!
 * @brief 	VREF works as low power buffer mode
 * @detail	The internal VREF bandgap is on. The low power buffer is enabled to
 *		generate a buffered 1.2 V voltage to VREF_OUT. It can also be used
 *		as a reference to internal analog peripherals such as an ADC channel
 *		or analog comparator input.
 * @note	The settling time of internal bandgap reference is typically 35ms,
 *		which means there is 35ms delay after the bandgap is enabled, the 
 *		SC[VREFST] can only be useful after the bandgap is stable after the 
 *		settling time.
 * @warning	When the Voltage Reference is already enabled and stabilized, changing
 *		SC[MODE_LV] will not clear SC[VREFST] but there will be some startup 
 *		time before the output voltage at the VREF_OUT pin has settled. 
 *		This is the buffer start up delay (Tstup) and the value is specified
 *		in the appropriate device data sheet. Also, there will be some settling
 *		time when a step change of the load current is applied to the VREF_OUT pin.
  *****************************************************************************/
#define VREF_LOW_POWER_CONFIG          /*       Low power mode       */       \
(tVREF){                                                                      \
/* SC      */ SET(VREF_SC_VREFEN_MASK)|SET(VREF_SC_REGEN_MASK)|               \
              SET(VREF_SC_ICOMPEN_MASK)|SET(VREF_SC_MODE_LV(2))               \
}
/*! @} End of vref_config                                                      */

/******************************************************************************
* VREF function and macro definitions
*
*//*! @addtogroup vref_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Set data registers.
 * @param   module  - DAC0
 * @param   data  - number from 0 to 4093 (12-bit data expected)
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define VREF_TrimVal(val)        VREF_TRIM = val|(VREF_TRIM&0xC0);
/*! @} End of vref_macro                                                      */
  
/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
/***************************************************************************//*!
 * @brief   VREF initialization function.
 * @param   vref    - @ref vref_config
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/ 
extern void VREF_Init  (tVREF vref);
   
#endif /* __VREF_H */
