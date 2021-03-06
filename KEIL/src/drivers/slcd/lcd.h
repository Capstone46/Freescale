/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      lcd.h
 * @version   1.0.1.0
 * @date      Sep-14-2012
 * @brief     LCD controller (LCD) driver header file.
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup slcd_example0
 * @{
 * @par       Source code:
 * @include   slcd0_test\slcd0_test.c
 * @par       Appconfig.h:
 * @include   slcd0_test\appconfig.h  
 ******************************************************************************/
/*! @} End of cop_example                                                    */
#ifndef __LCD_H
#define __LCD_H 

   
#ifdef TWR_KL46Z48M
  #include "lcdhdw_TWR_KL46Z.h"
#elif defined TWR_KL43Z48M
  #include "lcdhdw_TWR_KL43Z.h"
#elif defined FRDM_KL46Z48M
  #include "lcdhdw_FRDM_KL46Z.h"
#elif defined FRDM_KL43Z48M
  #include "lcdhdw_FRDM_KL43Z.h"
#else
  #include "lcdhdw.h"
#endif

/******************************************************************************
 * definition configuration structure                                         *
 ******************************************************************************/
typedef struct { uint32 GCR, AR, FDCR; } tLCD;
typedef struct { uint32 PENL, PENH; }    tLCD_FP; 
typedef struct { uint32 BPENL, BPENH; }  tLCD_BP;
typedef struct { uint32 WF0TO0, WF7TO4, WF11TO8, WF15TO12, WF19TO16,           \
                        WF23TO20, WF27TO24, WF31TO28, WF35TO32,                \
                        WF39TO36, WF43TO40, WF47TO44, WF51TO48,                \
                        WF55TO52, WF59TO56, WF63TO60; } tLCD_CP;
   
/******************************************************************************
* LCD controller pins definition for use with LCD_Init() function.
*
*//*! @addtogroup lcd_pins
* @{
*******************************************************************************/
#define LCD_00       (uint32)(1 <<  0)  ///< Pin 0
#define LCD_01       (uint32)(1 <<  1)  ///< Pin 1
#define LCD_02       (uint32)(1 <<  2)  ///< Pin 2
#define LCD_03       (uint32)(1 <<  3)  ///< Pin 3
#define LCD_04       (uint32)(1 <<  4)  ///< Pin 4
#define LCD_05       (uint32)(1 <<  5)  ///< Pin 5
#define LCD_06       (uint32)(1 <<  6)  ///< Pin 6
#define LCD_07       (uint32)(1 <<  7)  ///< Pin 7
#define LCD_08       (uint32)(1 <<  8)  ///< Pin 8
#define LCD_09       (uint32)(1 <<  9)  ///< Pin 9
#define LCD_10       (uint32)(1 << 10)  ///< Pin 10
#define LCD_11       (uint32)(1 << 11)  ///< Pin 11
#define LCD_12       (uint32)(1 << 12)  ///< Pin 12
#define LCD_13       (uint32)(1 << 13)  ///< Pin 13
#define LCD_14       (uint32)(1 << 14)  ///< Pin 14
#define LCD_15       (uint32)(1 << 15)  ///< Pin 15
#define LCD_16       (uint32)(1 << 16)  ///< Pin 16
#define LCD_17       (uint32)(1 << 17)  ///< Pin 17
#define LCD_18       (uint32)(1 << 18)  ///< Pin 18
#define LCD_19       (uint32)(1 << 19)  ///< Pin 19
#define LCD_20       (uint32)(1 << 20)  ///< Pin 20
#define LCD_21       (uint32)(1 << 21)  ///< Pin 21
#define LCD_22       (uint32)(1 << 22)  ///< Pin 22
#define LCD_23       (uint32)(1 << 23)  ///< Pin 23
#define LCD_24       (uint32)(1 << 24)  ///< Pin 24
#define LCD_25       (uint32)(1 << 25)  ///< Pin 25
#define LCD_26       (uint32)(1 << 26)  ///< Pin 26
#define LCD_27       (uint32)(1 << 27)  ///< Pin 27
#define LCD_28       (uint32)(1 << 28)  ///< Pin 28
#define LCD_29       (uint32)(1 << 29)  ///< Pin 29
#define LCD_30       (uint32)(1 << 30)  ///< Pin 30
#define LCD_31       (uint32)(1 << 31)  ///< Pin 31
#define LCD_32       (uint32)(1 <<  0)  ///< Pin 32
#define LCD_33       (uint32)(1 <<  1)  ///< Pin 33
#define LCD_34       (uint32)(1 <<  2)  ///< Pin 34
#define LCD_35       (uint32)(1 <<  3)  ///< Pin 35
#define LCD_36       (uint32)(1 <<  4)  ///< Pin 36
#define LCD_37       (uint32)(1 <<  5)  ///< Pin 37
#define LCD_38       (uint32)(1 <<  6)  ///< Pin 38
#define LCD_39       (uint32)(1 <<  7)  ///< Pin 39
#define LCD_40       (uint32)(1 <<  8)  ///< Pin 40
#define LCD_41       (uint32)(1 <<  9)  ///< Pin 41
#define LCD_42       (uint32)(1 << 10)  ///< Pin 42
#define LCD_43       (uint32)(1 << 11)  ///< Pin 43
#define LCD_44       (uint32)(1 << 12)  ///< Pin 44
#define LCD_45       (uint32)(1 << 13)  ///< Pin 45
#define LCD_46       (uint32)(1 << 14)  ///< Pin 46
#define LCD_47       (uint32)(1 << 15)  ///< Pin 47
#define LCD_48       (uint32)(1 << 16)  ///< Pin 48
#define LCD_49       (uint32)(1 << 17)  ///< Pin 49
#define LCD_50       (uint32)(1 << 18)  ///< Pin 50
#define LCD_51       (uint32)(1 << 19)  ///< Pin 51
#define LCD_52       (uint32)(1 << 20)  ///< Pin 52
#define LCD_53       (uint32)(1 << 21)  ///< Pin 53
#define LCD_54       (uint32)(1 << 22)  ///< Pin 54
#define LCD_55       (uint32)(1 << 23)  ///< Pin 55
#define LCD_56       (uint32)(1 << 24)  ///< Pin 56
#define LCD_57       (uint32)(1 << 25)  ///< Pin 57
#define LCD_58       (uint32)(1 << 26)  ///< Pin 58
#define LCD_59       (uint32)(1 << 27)  ///< Pin 59
#define LCD_60       (uint32)(1 << 28)  ///< Pin 60
#define LCD_61       (uint32)(1 << 29)  ///< Pin 61
#define LCD_62       (uint32)(1 << 30)  ///< Pin 62
#define LCD_63       (uint32)(1 << 31)  ///< Pin 63
/*! @} End of lcd_pins                                                        */

/******************************************************************************
* LCD controller pins states definition for use with LCD_Init(),
* LCD_All_Segments_OFF and LCD_All_Segments_OFF functions.
*
*//*! @addtogroup lcd_pins_state
* @{
*******************************************************************************/
#define LCD_BP1      (uint8)0x01        ///< No of back planes 1
#define LCD_BP2      (uint8)0x02        ///< No of back planes 2
#define LCD_BP3      (uint8)0x04        ///< No of back planes 3
#define LCD_BP4      (uint8)0x08        ///< No of back planes 4
#define LCD_BP5      (uint8)0x10        ///< No of back planes 5
#define LCD_BP6      (uint8)0x20        ///< No of back planes 6
#define LCD_BP7      (uint8)0x40        ///< No of back planes 7
#define LCD_BP8      (uint8)0x80        ///< No of back planes 8
#define LCD_ON1      (uint8)0x01        ///< Segment ON 1 back plane
#define LCD_ON2      (uint8)0x03        ///< Segment ON 1 back plane
#define LCD_ON3      (uint8)0x07        ///< Segment ON 1 back plane
#define LCD_ON4      (uint8)0x0F        ///< Segment ON 1 back plane
#define LCD_ON5      (uint8)0x1F        ///< Segment ON 1 back plane
#define LCD_ON6      (uint8)0x3F        ///< Segment ON 1 back plane
#define LCD_ON7      (uint8)0x7F        ///< Segment ON 1 back plane
#define LCD_ON8      (uint8)0xFF        ///< Segment ON 1 back plane
#define LCD_OFF      (uint8)0x00        ///< Segment OFF
/*! @} End of lcd_pins_states                                                 */

/******************************************************************************
 * Default LCD configurations                                                 *
 ******************************************************************************/

/******************************************************************************
* LCD controller default configurations used by LCD_init() function
*
*//*! @addtogroup lcd_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
  * @brief   LCD controller setting:
  * @details Initialize LCD controller working mode:
  *          - No of back planes is 1, 
  *          - Input clock Default,
  *          - Power supply Internal,
  *          - Resistor bias network Disable,
  *          - Blink mode Disable,
  *****************************************************************************/
#define LCD_CHARGEPUMP_EN_SOURCE_ALT_BACKPLANES_1                              \
(tLCD){                                                                        \
/* GCR    */    CLR(LCD_GCR_RVEN_MASK)      |SET(LCD_GCR_RVTRIM(0x8))|         \
                SET(LCD_GCR_CPSEL_MASK)     |SET(LCD_GCR_LADJ(0x0))|           \
                CLR(LCD_GCR_VSUPPLY_MASK)   |CLR(LCD_GCR_LCDIEN_MASK)|         \
                CLR(LCD_GCR_FDCIEN_MASK)    |CLR(LCD_GCR_ALTDIV(0x0))|         \
                CLR(LCD_GCR_LCDDOZE_MASK)   |CLR(LCD_GCR_LCDSTP_MASK)|         \
                CLR(LCD_GCR_SOURCE_MASK)    |SET(LCD_GCR_LCLK(0x3))|           \
                SET(LCD_GCR_DUTY(0x0)),                                        \
/* AR    */     CLR(LCD_AR_LCDIF_MASK)      |CLR(LCD_AR_BLINK_MASK)|           \
                CLR(LCD_AR_ALT_MASK)        |CLR(LCD_AR_BLANK_MASK)|           \
                CLR(LCD_AR_BMODE_MASK)      |CLR(LCD_AR_BRATE(0x0)),           \
/* FDCR  */     CLR(LCD_FDCR_FDPRS(0x0))    |CLR(LCD_FDCR_FDSWW(0x0))|         \
                CLR(LCD_FDCR_FDEN_MASK)     |CLR(LCD_FDCR_FDBPEN_MASK)|        \
                CLR(LCD_FDCR_FDPINID(0x00)),                                   \
}

/**************************************************************************/ /*!
  * @brief   LCD controller setting:
  * @details Initialize LCD controller working mode:
  *          - No of back planes is 2, 
  *          - Input clock Default,
  *          - Power supply Internal,
  *          - Resistor bias network Disable,
  *          - Blink mode Disable,
  *****************************************************************************/
#define LCD_CHARGEPUMP_EN_SOURCE_ALT_DUTY1_BACKPLANES_2                        \
(tLCD){                                                                        \
/* GCR    */    CLR(LCD_GCR_RVEN_MASK)      |SET(LCD_GCR_RVTRIM(0x8))|         \
                SET(LCD_GCR_CPSEL_MASK)     |SET(LCD_GCR_LADJ(0x0))|           \
                CLR(LCD_GCR_VSUPPLY_MASK)   |CLR(LCD_GCR_LCDIEN_MASK)|         \
                CLR(LCD_GCR_FDCIEN_MASK)    |CLR(LCD_GCR_ALTDIV(0x0))|         \
                CLR(LCD_GCR_LCDDOZE_MASK)   |CLR(LCD_GCR_LCDSTP_MASK)|         \
                CLR(LCD_GCR_SOURCE_MASK)    |SET(LCD_GCR_LCLK(0x3))|           \
                SET(LCD_GCR_DUTY(0x1)),                                        \
/* AR    */     CLR(LCD_AR_LCDIF_MASK)      |CLR(LCD_AR_BLINK_MASK)|           \
                CLR(LCD_AR_ALT_MASK)        |CLR(LCD_AR_BLANK_MASK)|           \
                CLR(LCD_AR_BMODE_MASK)      |CLR(LCD_AR_BRATE(0x0)),           \
/* FDCR  */     CLR(LCD_FDCR_FDPRS(0x0))    |CLR(LCD_FDCR_FDSWW(0x0))|         \
                CLR(LCD_FDCR_FDEN_MASK)     |CLR(LCD_FDCR_FDBPEN_MASK)|        \
                CLR(LCD_FDCR_FDPINID(0x00)),                                   \
}

/**************************************************************************/ /*!
  * @brief   LCD controller setting:
  * @details Initialize LCD controller working mode:
  *          - No of back planes is 3, 
  *          - Input clock Default,
  *          - Power supply Internal,
  *          - Resistor bias network Disable,
  *          - Blink mode Disable,
  *****************************************************************************/
#define LCD_CHARGEPUMP_EN_SOURCE_ALT_BACKPLANES_3                              \
(tLCD){                                                                        \
/* GCR    */    CLR(LCD_GCR_RVEN_MASK)      |SET(LCD_GCR_RVTRIM(0x8))|         \
                SET(LCD_GCR_CPSEL_MASK)     |SET(LCD_GCR_LADJ(0x0))|           \
                CLR(LCD_GCR_VSUPPLY_MASK)   |CLR(LCD_GCR_LCDIEN_MASK)|         \
                CLR(LCD_GCR_FDCIEN_MASK)    |CLR(LCD_GCR_ALTDIV(0x0))|         \
                CLR(LCD_GCR_LCDDOZE_MASK)   |CLR(LCD_GCR_LCDSTP_MASK)|         \
                CLR(LCD_GCR_SOURCE_MASK)    |SET(LCD_GCR_LCLK(0x3))|           \
                SET(LCD_GCR_DUTY(0x2)),                                        \
/* AR    */     CLR(LCD_AR_LCDIF_MASK)      |CLR(LCD_AR_BLINK_MASK)|           \
                CLR(LCD_AR_ALT_MASK)        |CLR(LCD_AR_BLANK_MASK)|           \
                CLR(LCD_AR_BMODE_MASK)      |CLR(LCD_AR_BRATE(0x0)),           \
/* FDCR  */     CLR(LCD_FDCR_FDPRS(0x0))    |CLR(LCD_FDCR_FDSWW(0x0))|         \
                CLR(LCD_FDCR_FDEN_MASK)     |CLR(LCD_FDCR_FDBPEN_MASK)|        \
                CLR(LCD_FDCR_FDPINID(0x00)),                                   \
}
/**************************************************************************/ /*!
  * @brief   LCD controller setting:
  * @details Initialize LCD controller working mode:
  *          - No of back planes is 4, 
  *          - Input clock Default,
  *          - Power supply Internal,
  *          - Resistor bias network Disable,
  *          - Blink mode Disable,
  *****************************************************************************/
#define LCD_CHARGEPUMP_EN_SOURCE_ALT_BACKPLANES_4                              \
(tLCD){                                                                        \
/* GCR    */    CLR(LCD_GCR_RVEN_MASK)      |SET(LCD_GCR_RVTRIM(0x8))|         \
                SET(LCD_GCR_CPSEL_MASK)     |SET(LCD_GCR_LADJ(0x0))|           \
                CLR(LCD_GCR_VSUPPLY_MASK)   |CLR(LCD_GCR_LCDIEN_MASK)|         \
                CLR(LCD_GCR_FDCIEN_MASK)    |CLR(LCD_GCR_ALTDIV(0x0))|         \
                CLR(LCD_GCR_LCDDOZE_MASK)   |CLR(LCD_GCR_LCDSTP_MASK)|         \
                CLR(LCD_GCR_SOURCE_MASK)    |SET(LCD_GCR_LCLK(0x3))|           \
                SET(LCD_GCR_DUTY(0x3)),                                        \
/* AR    */     CLR(LCD_AR_LCDIF_MASK)      |CLR(LCD_AR_BLINK_MASK)|           \
                CLR(LCD_AR_ALT_MASK)        |CLR(LCD_AR_BLANK_MASK)|           \
                CLR(LCD_AR_BMODE_MASK)      |CLR(LCD_AR_BRATE(0x0)),           \
/* FDCR  */     CLR(LCD_FDCR_FDPRS(0x0))    |CLR(LCD_FDCR_FDSWW(0x0))|         \
                CLR(LCD_FDCR_FDEN_MASK)     |CLR(LCD_FDCR_FDBPEN_MASK)|        \
                CLR(LCD_FDCR_FDPINID(0x00)),                                   \
}
 
/**************************************************************************/ /*!
  * @brief   LCD controller setting:
  * @details Initialize LCD controller working mode:
  *          - No of back planes is 5, 
  *          - Input clock Default,
  *          - Power supply Internal,
  *          - Resistor bias network Disable,
  *          - Blink mode Disable,
  *****************************************************************************/
#define LCD_CHARGEPUMP_EN_SOURCE_ALT_BACKPLANES_5                              \
(tLCD){                                                                        \
/* GCR    */    CLR(LCD_GCR_RVEN_MASK)      |SET(LCD_GCR_RVTRIM(0x8))|         \
                SET(LCD_GCR_CPSEL_MASK)     |SET(LCD_GCR_LADJ(0x0))|           \
                CLR(LCD_GCR_VSUPPLY_MASK)   |CLR(LCD_GCR_LCDIEN_MASK)|         \
                CLR(LCD_GCR_FDCIEN_MASK)    |CLR(LCD_GCR_ALTDIV(0x0))|         \
                CLR(LCD_GCR_LCDDOZE_MASK)   |CLR(LCD_GCR_LCDSTP_MASK)|         \
                CLR(LCD_GCR_SOURCE_MASK)    |SET(LCD_GCR_LCLK(0x3))|           \
                SET(LCD_GCR_DUTY(0x4)),                                        \
/* AR    */     CLR(LCD_AR_LCDIF_MASK)      |CLR(LCD_AR_BLINK_MASK)|           \
                CLR(LCD_AR_ALT_MASK)        |CLR(LCD_AR_BLANK_MASK)|           \
                CLR(LCD_AR_BMODE_MASK)      |CLR(LCD_AR_BRATE(0x0)),           \
/* FDCR  */     CLR(LCD_FDCR_FDPRS(0x0))    |CLR(LCD_FDCR_FDSWW(0x0))|         \
                CLR(LCD_FDCR_FDEN_MASK)     |CLR(LCD_FDCR_FDBPEN_MASK)|        \
                CLR(LCD_FDCR_FDPINID(0x00)),                                   \
}

/**************************************************************************/ /*!
  * @brief   LCD controller setting:
  * @details Initialize LCD controller working mode:
  *          - No of back planes is 6, 
  *          - Input clock Default,
  *          - Power supply Internal,
  *          - Resistor bias network Disable,
  *          - Blink mode Disable,
  *****************************************************************************/
#define LCD_CHARGEPUMP_EN_SOURCE_ALT_BACKPLANES_6                              \
(tLCD){                                                                        \
/* GCR    */    CLR(LCD_GCR_RVEN_MASK)      |SET(LCD_GCR_RVTRIM(0x8))|         \
                SET(LCD_GCR_CPSEL_MASK)     |SET(LCD_GCR_LADJ(0x0))|           \
                CLR(LCD_GCR_VSUPPLY_MASK)   |CLR(LCD_GCR_LCDIEN_MASK)|         \
                CLR(LCD_GCR_FDCIEN_MASK)    |CLR(LCD_GCR_ALTDIV(0x0))|         \
                CLR(LCD_GCR_LCDDOZE_MASK)   |CLR(LCD_GCR_LCDSTP_MASK)|         \
                CLR(LCD_GCR_SOURCE_MASK)    |SET(LCD_GCR_LCLK(0x3))|           \
                SET(LCD_GCR_DUTY(0x5)),                                        \
/* AR    */     CLR(LCD_AR_LCDIF_MASK)      |CLR(LCD_AR_BLINK_MASK)|           \
                CLR(LCD_AR_ALT_MASK)        |CLR(LCD_AR_BLANK_MASK)|           \
                CLR(LCD_AR_BMODE_MASK)      |CLR(LCD_AR_BRATE(0x0)),           \
/* FDCR  */     CLR(LCD_FDCR_FDPRS(0x0))    |CLR(LCD_FDCR_FDSWW(0x0))|         \
                CLR(LCD_FDCR_FDEN_MASK)     |CLR(LCD_FDCR_FDBPEN_MASK)|        \
                CLR(LCD_FDCR_FDPINID(0x00)),                                   \
}

/**************************************************************************/ /*!
  * @brief   LCD controller setting:
  * @details Initialize LCD controller working mode:
  *          - No of back planes is 7, 
  *          - Input clock Default,
  *          - Power supply Internal,
  *          - Resistor bias network Disable,
  *          - Blink mode Disable,
  *****************************************************************************/
#define LCD_CHARGEPUMP_EN_SOURCE_ALT_BACKPLANES_7                              \
(tLCD){                                                                        \
/* GCR    */    CLR(LCD_GCR_RVEN_MASK)      |SET(LCD_GCR_RVTRIM(0x8))|         \
                SET(LCD_GCR_CPSEL_MASK)     |SET(LCD_GCR_LADJ(0x0))|           \
                CLR(LCD_GCR_VSUPPLY_MASK)   |CLR(LCD_GCR_LCDIEN_MASK)|         \
                CLR(LCD_GCR_FDCIEN_MASK)    |CLR(LCD_GCR_ALTDIV(0x0))|         \
                CLR(LCD_GCR_LCDDOZE_MASK)   |CLR(LCD_GCR_LCDSTP_MASK)|         \
                CLR(LCD_GCR_SOURCE_MASK)    |SET(LCD_GCR_LCLK(0x3))|           \
                SET(LCD_GCR_DUTY(0x6)),                                        \
/* AR    */     CLR(LCD_AR_LCDIF_MASK)      |CLR(LCD_AR_BLINK_MASK)|           \
                CLR(LCD_AR_ALT_MASK)        |CLR(LCD_AR_BLANK_MASK)|           \
                CLR(LCD_AR_BMODE_MASK)      |CLR(LCD_AR_BRATE(0x0)),           \
/* FDCR  */     CLR(LCD_FDCR_FDPRS(0x0))    |CLR(LCD_FDCR_FDSWW(0x0))|         \
                CLR(LCD_FDCR_FDEN_MASK)     |CLR(LCD_FDCR_FDBPEN_MASK)|        \
                CLR(LCD_FDCR_FDPINID(0x00)),                                   \
}

/**************************************************************************/ /*!
  * @brief   LCD controller setting:
  * @details Initialize LCD controller working mode:
  *          - No of back planes is 8, 
  *          - Input clock Default,
  *          - Power supply Internal,
  *          - Resistor bias network Disable,
  *          - Blink mode Disable,
  *****************************************************************************/
#define LCD_CHARGEPUMP_EN_SOURCE_ALT_BACKPLANES_8                              \
(tLCD){                                                                        \
/* GCR    */    CLR(LCD_GCR_RVEN_MASK)      |SET(LCD_GCR_RVTRIM(0x8))|         \
                SET(LCD_GCR_CPSEL_MASK)     |SET(LCD_GCR_LADJ(0x0))|           \
                CLR(LCD_GCR_VSUPPLY_MASK)   |CLR(LCD_GCR_LCDIEN_MASK)|         \
                CLR(LCD_GCR_FDCIEN_MASK)    |CLR(LCD_GCR_ALTDIV(0x0))|         \
                CLR(LCD_GCR_LCDDOZE_MASK)   |CLR(LCD_GCR_LCDSTP_MASK)|         \
                CLR(LCD_GCR_SOURCE_MASK)    |SET(LCD_GCR_LCLK(0x3))|           \
                SET(LCD_GCR_DUTY(0x7)),                                        \
/* AR    */     CLR(LCD_AR_LCDIF_MASK)      |CLR(LCD_AR_BLINK_MASK)|           \
                CLR(LCD_AR_ALT_MASK)        |CLR(LCD_AR_BLANK_MASK)|           \
                CLR(LCD_AR_BMODE_MASK)      |CLR(LCD_AR_BRATE(0x0)),           \
/* FDCR  */     CLR(LCD_FDCR_FDPRS(0x0))    |CLR(LCD_FDCR_FDSWW(0x0))|         \
                CLR(LCD_FDCR_FDEN_MASK)     |CLR(LCD_FDCR_FDBPEN_MASK)|        \
                CLR(LCD_FDCR_FDPINID(0x00)),                                   \
}

/**************************************************************************/ /*!
  * @brief   TWRPI - GD6363 LCD controller setting:
  * @details Initialize LCD controller working mode:
  *          - No of back planes is 8, 
  *          - Input clock Default,
  *          - Power supply Internal,
  *          - Resistor bias network Disable,
  *          - Blink mode Disable,
  *****************************************************************************/
#define LCD_TWR_CONFIG1                                                        \
(tLCD){                                                                        \
/* GCR    */    CLR(LCD_GCR_RVEN_MASK)      |SET(LCD_GCR_RVTRIM(0x3))|         \
                SET(LCD_GCR_CPSEL_MASK)     |SET(LCD_GCR_LADJ(0x3))|           \
                SET(LCD_GCR_VSUPPLY_MASK)   |CLR(LCD_GCR_PADSAFE_MASK)|        \
                CLR(LCD_GCR_FDCIEN_MASK)    |SET(LCD_GCR_ALTDIV(0x0))|         \
                CLR(LCD_GCR_FFR_MASK)       |CLR(LCD_GCR_ALTSOURCE_MASK)|      \
                CLR(LCD_GCR_LCDDOZE_MASK)   |CLR(LCD_GCR_LCDSTP_MASK)|         \
                CLR(LCD_GCR_LCDEN_MASK)     |CLR(LCD_GCR_SOURCE_MASK)|         \
                SET(LCD_GCR_LCLK(0x1))      |SET(LCD_GCR_DUTY(0x2)),           \
/* AR    */     CLR(LCD_AR_BLINK_MASK)|                                        \
                CLR(LCD_AR_ALT_MASK)        |CLR(LCD_AR_BLANK_MASK)|           \
                CLR(LCD_AR_BMODE_MASK)      |SET(LCD_AR_BRATE(0x3)),           \
/* FDCR  */     SET(LCD_FDCR_FDPRS(0x0))    |SET(LCD_FDCR_FDSWW(0x0))|         \
                CLR(LCD_FDCR_FDEN_MASK)     |CLR(LCD_FDCR_FDBPEN_MASK)|        \
                SET(LCD_FDCR_FDPINID(0x00)),                                   \
}

/**************************************************************************/ /*!
  * @brief   LCD controller setting:
  * @details Initialize LCD controller working mode:
  *          - No of back planes is 8, 
  *          - Input clock Default,
  *          - Power supply Internal,
  *          - Resistor bias network Disable,
  *          - Blink mode Disable,
  *****************************************************************************/
#define LCD_FRDM_CONFIG                                                        \
(tLCD){                                                                        \
/* GCR    */    CLR(LCD_GCR_RVEN_MASK)      |SET(LCD_GCR_RVTRIM(0x3))|         \
                SET(LCD_GCR_CPSEL_MASK)     |SET(LCD_GCR_LADJ(0x3))|           \
                SET(LCD_GCR_VSUPPLY_MASK)   |CLR(LCD_GCR_PADSAFE_MASK)|        \
                CLR(LCD_GCR_FDCIEN_MASK)    |SET(LCD_GCR_ALTDIV(0x0))|         \
                CLR(LCD_GCR_FFR_MASK)       |CLR(LCD_GCR_ALTSOURCE_MASK)|      \
                CLR(LCD_GCR_LCDDOZE_MASK)   |CLR(LCD_GCR_LCDSTP_MASK)|         \
                CLR(LCD_GCR_LCDEN_MASK)     |CLR(LCD_GCR_SOURCE_MASK)|         \
                SET(LCD_GCR_LCLK(0x1))      |SET(LCD_GCR_DUTY(0x3)),           \
/* AR    */     CLR(LCD_AR_BLINK_MASK)|                                        \
                CLR(LCD_AR_ALT_MASK)        |CLR(LCD_AR_BLANK_MASK)|           \
                CLR(LCD_AR_BMODE_MASK)      |SET(LCD_AR_BRATE(0x3)),           \
/* FDCR  */     SET(LCD_FDCR_FDPRS(0x0))    |SET(LCD_FDCR_FDSWW(0x0))|         \
                CLR(LCD_FDCR_FDEN_MASK)     |CLR(LCD_FDCR_FDBPEN_MASK)|        \
                SET(LCD_FDCR_FDPINID(0x00)),                                   \
}

/**************************************************************************/ /*!
  * @brief   LCD controller setting:
  * @details Default (disable) mode.
  *****************************************************************************/
#define LCD_DISABLE_CONFIG                                                     \
(tLCD){                                                                        \
/* GCR    */    CLR(LCD_GCR_RVEN_MASK)      |SET(LCD_GCR_RVTRIM(0x0))|         \
                CLR(LCD_GCR_CPSEL_MASK)     |SET(LCD_GCR_LADJ(0x0))|           \
                CLR(LCD_GCR_VSUPPLY_MASK)   |CLR(LCD_GCR_PADSAFE_MASK)|        \
                CLR(LCD_GCR_FDCIEN_MASK)    |SET(LCD_GCR_ALTDIV(0x0))|         \
                CLR(LCD_GCR_FFR_MASK)       |CLR(LCD_GCR_ALTSOURCE_MASK)|      \
                CLR(LCD_GCR_LCDDOZE_MASK)   |CLR(LCD_GCR_LCDSTP_MASK)|         \
                CLR(LCD_GCR_LCDEN_MASK)     |CLR(LCD_GCR_SOURCE_MASK)|         \
                SET(LCD_GCR_LCLK(0x0))      |SET(LCD_GCR_DUTY(0x0)),           \
/* AR    */     CLR(LCD_AR_BLINK_MASK)|                                        \
                CLR(LCD_AR_ALT_MASK)        |CLR(LCD_AR_BLANK_MASK)|           \
                CLR(LCD_AR_BMODE_MASK)      |SET(LCD_AR_BRATE(0x0)),           \
/* FDCR  */     SET(LCD_FDCR_FDPRS(0x0))    |SET(LCD_FDCR_FDSWW(0x0))|         \
                CLR(LCD_FDCR_FDEN_MASK)     |CLR(LCD_FDCR_FDBPEN_MASK)|        \
                SET(LCD_FDCR_FDPINID(0x00)),                                   \
}

/**************************************************************************/ /*!
  * @brief   LCD front plane pins initialization:
  * @details Enables LCD pins for LCD glas driving:
  *          - Use "CLR" for disable pin, 
  *          - Use "SET" for enable pin, 
  *****************************************************************************/
#define LCD_FRONT_PLANE_PINS                                                   \
(tLCD_FP){                                                                     \
/* PENL  */     CLR(LCD_00) |CLR(LCD_01) |CLR(LCD_02) |CLR(LCD_03)|            \
                CLR(LCD_04) |CLR(LCD_05) |CLR(LCD_06) |CLR(LCD_07)|            \
                CLR(LCD_08) |CLR(LCD_09) |CLR(LCD_10) |CLR(LCD_11)|            \
                CLR(LCD_12) |SET(LCD_13) |SET(LCD_14) |SET(LCD_15)|            \
                SET(LCD_16) |SET(LCD_17) |SET(LCD_18) |SET(LCD_19)|            \
                SET(LCD_20) |SET(LCD_21) |SET(LCD_22) |SET(LCD_23)|            \
                SET(LCD_24) |SET(LCD_25) |SET(LCD_26) |SET(LCD_27)|            \
                SET(LCD_28) |SET(LCD_29) |SET(LCD_30) |SET(LCD_31),            \
/* PENH  */     SET(LCD_32) |SET(LCD_33) |SET(LCD_34) |SET(LCD_35)|            \
                SET(LCD_36) |SET(LCD_37) |SET(LCD_38) |CLR(LCD_39)|            \
                CLR(LCD_40) |CLR(LCD_41) |CLR(LCD_42) |CLR(LCD_43)|            \
                CLR(LCD_44) |CLR(LCD_45) |CLR(LCD_46) |CLR(LCD_47)|            \
                CLR(LCD_48) |CLR(LCD_49) |CLR(LCD_50) |CLR(LCD_51)|            \
                CLR(LCD_52) |CLR(LCD_53) |CLR(LCD_54) |CLR(LCD_55)|            \
                CLR(LCD_56) |CLR(LCD_57) |CLR(LCD_58) |CLR(LCD_59)|            \
                CLR(LCD_60) |CLR(LCD_61) |CLR(LCD_62) |CLR(LCD_63),            \
}

/**************************************************************************/ /*!
* @brief   LCD front plane pins initialization for GD6363 with TWR-KL43:
  * @details Enables LCD pins for LCD glas driving:
  *          - Use "CLR" for disable pin, 
  *          - Use "SET" for enable pin, 
  *****************************************************************************/
#define LCD_FRONT_PLANE_PINS_TWR_KL43                                          \
(tLCD_FP){                                                                     \
/* PENL  */     SET(LCD_00) |SET(LCD_01) |CLR(LCD_02) |SET(LCD_03)|            \
                CLR(LCD_04) |CLR(LCD_05) |CLR(LCD_06) |CLR(LCD_07)|            \
                CLR(LCD_08) |CLR(LCD_09) |CLR(LCD_10) |CLR(LCD_11)|            \
                SET(LCD_12) |SET(LCD_13) |SET(LCD_14) |SET(LCD_15)|            \
                CLR(LCD_16) |CLR(LCD_17) |CLR(LCD_18) |CLR(LCD_19)|            \
                SET(LCD_20) |CLR(LCD_21) |SET(LCD_22) |SET(LCD_23)|            \
                SET(LCD_24) |CLR(LCD_25) |CLR(LCD_26) |CLR(LCD_27)|            \
                CLR(LCD_28) |CLR(LCD_29) |CLR(LCD_30) |CLR(LCD_31),            \
/* PENH  */     CLR(LCD_32) |CLR(LCD_33) |CLR(LCD_34) |CLR(LCD_35)|            \
                CLR(LCD_36) |CLR(LCD_37) |CLR(LCD_38) |CLR(LCD_39)|            \
                CLR(LCD_40) |CLR(LCD_41) |CLR(LCD_42) |CLR(LCD_43)|            \
                CLR(LCD_44) |CLR(LCD_45) |CLR(LCD_46) |CLR(LCD_47)|            \
                CLR(LCD_48) |CLR(LCD_49) |CLR(LCD_50) |CLR(LCD_51)|            \
                CLR(LCD_52) |CLR(LCD_53) |CLR(LCD_54) |CLR(LCD_55)|            \
                CLR(LCD_56) |CLR(LCD_57) |CLR(LCD_58) |CLR(LCD_59)|            \
                CLR(LCD_60) |CLR(LCD_61) |CLR(LCD_62) |CLR(LCD_63),            \
}


/**************************************************************************/ /*!
  * @brief   LCD front plane pins initialization for FRDM-KL46Z with S401M:
  * @details Enables LCD pins for LCD glas driving:
  *          - Use "CLR" for disable pin, 
  *          - Use "SET" for enable pin, 
  *****************************************************************************/
#define LCD_FRONT_PLANE_PINS_FRDM_KL46                                         \
(tLCD_FP){                                                                     \
/* PENL  */     CLR(LCD_00) |CLR(LCD_01) |CLR(LCD_02) |CLR(LCD_03)|            \
                CLR(LCD_04) |CLR(LCD_05) |CLR(LCD_06) |SET(LCD_07)|            \
                SET(LCD_08) |CLR(LCD_09) |SET(LCD_10) |SET(LCD_11)|            \
                CLR(LCD_12) |CLR(LCD_13) |CLR(LCD_14) |CLR(LCD_15)|            \
                CLR(LCD_16) |SET(LCD_17) |SET(LCD_18) |SET(LCD_19)|            \
                CLR(LCD_20) |CLR(LCD_21) |CLR(LCD_22) |CLR(LCD_23)|            \
                CLR(LCD_24) |CLR(LCD_25) |CLR(LCD_26) |CLR(LCD_27)|            \
                CLR(LCD_28) |CLR(LCD_29) |CLR(LCD_30) |CLR(LCD_31),            \
/* PENH  */     CLR(LCD_32) |CLR(LCD_33) |CLR(LCD_34) |CLR(LCD_35)|            \
                CLR(LCD_36) |SET(LCD_37) |SET(LCD_38) |CLR(LCD_39)|            \
                SET(LCD_40) |CLR(LCD_41) |CLR(LCD_42) |CLR(LCD_43)|            \
                CLR(LCD_44) |CLR(LCD_45) |CLR(LCD_46) |CLR(LCD_47)|            \
                CLR(LCD_48) |CLR(LCD_49) |CLR(LCD_50) |CLR(LCD_51)|            \
                SET(LCD_52) |SET(LCD_53) |CLR(LCD_54) |CLR(LCD_55)|            \
                CLR(LCD_56) |CLR(LCD_57) |CLR(LCD_58) |CLR(LCD_59)|            \
                CLR(LCD_60) |CLR(LCD_61) |CLR(LCD_62) |CLR(LCD_63),            \
}

/**************************************************************************/ /*!
  * @brief   LCD front plane pins initialization for FRDM-KL43Z with S401M:
  * @details Enables LCD pins for LCD glas driving:
  *          - Use "CLR" for disable pin, 
  *          - Use "SET" for enable pin, 
  *****************************************************************************/
#define LCD_FRONT_PLANE_PINS_FRDM_KL43                                         \
(tLCD_FP){                                                                     \
/* PENL  */     CLR(LCD_00) |CLR(LCD_01) |CLR(LCD_02) |CLR(LCD_03)|            \
                CLR(LCD_04) |CLR(LCD_05) |CLR(LCD_06) |CLR(LCD_07)|            \
                CLR(LCD_08) |CLR(LCD_09) |CLR(LCD_10) |CLR(LCD_11)|            \
                CLR(LCD_12) |CLR(LCD_13) |SET(LCD_14) |SET(LCD_15)|            \
                CLR(LCD_16) |CLR(LCD_17) |CLR(LCD_18) |CLR(LCD_19)|            \
                SET(LCD_20) |CLR(LCD_21) |CLR(LCD_22) |CLR(LCD_23)|            \
                SET(LCD_24) |CLR(LCD_25) |SET(LCD_26) |SET(LCD_27)|            \
                CLR(LCD_28) |CLR(LCD_29) |CLR(LCD_30) |CLR(LCD_31),            \
/* PENH  */     CLR(LCD_32) |CLR(LCD_33) |CLR(LCD_34) |CLR(LCD_35)|            \
                CLR(LCD_36) |CLR(LCD_37) |CLR(LCD_38) |CLR(LCD_39)|            \
                SET(LCD_40) |CLR(LCD_41) |SET(LCD_42) |SET(LCD_43)|            \
                SET(LCD_44) |CLR(LCD_45) |CLR(LCD_46) |CLR(LCD_47)|            \
                CLR(LCD_48) |CLR(LCD_49) |CLR(LCD_50) |CLR(LCD_51)|            \
                CLR(LCD_52) |CLR(LCD_53) |CLR(LCD_54) |CLR(LCD_55)|            \
                CLR(LCD_56) |CLR(LCD_57) |CLR(LCD_58) |SET(LCD_59)|            \
                SET(LCD_60) |CLR(LCD_61) |CLR(LCD_62) |CLR(LCD_63),            \
}

/**************************************************************************/ /*!
  * @brief   LCD back plane pins initialization:
  * @details Enables LCD backplane pins for LCD glas driving:
  *          - Use "CLR" for disable pin, 
  *          - Use "SET" for enable pin, 
  *****************************************************************************/
#define LCD_BACK_PLANE_PINS                                                    \
(tLCD_BP){                                                                     \
/* BPENL  */    CLR(LCD_00) |CLR(LCD_01) |CLR(LCD_02) |CLR(LCD_03)|            \
                CLR(LCD_04) |CLR(LCD_05) |CLR(LCD_06) |CLR(LCD_07)|            \
                CLR(LCD_08) |CLR(LCD_09) |CLR(LCD_10) |CLR(LCD_11)|            \
                CLR(LCD_12) |SET(LCD_13) |SET(LCD_14) |SET(LCD_15)|            \
                SET(LCD_16) |CLR(LCD_17) |CLR(LCD_18) |CLR(LCD_19)|            \
                CLR(LCD_20) |CLR(LCD_21) |CLR(LCD_22) |CLR(LCD_23)|            \
                CLR(LCD_24) |CLR(LCD_25) |CLR(LCD_26) |CLR(LCD_27)|            \
                CLR(LCD_28) |CLR(LCD_29) |CLR(LCD_30) |CLR(LCD_31),            \
/* BPENH  */    CLR(LCD_32) |CLR(LCD_33) |CLR(LCD_34) |CLR(LCD_35)|            \
                CLR(LCD_36) |CLR(LCD_37) |CLR(LCD_38) |CLR(LCD_39)|            \
                CLR(LCD_40) |CLR(LCD_41) |CLR(LCD_42) |CLR(LCD_43)|            \
                CLR(LCD_44) |CLR(LCD_45) |CLR(LCD_46) |CLR(LCD_47)|            \
                CLR(LCD_48) |CLR(LCD_49) |CLR(LCD_50) |CLR(LCD_51)|            \
                CLR(LCD_52) |CLR(LCD_53) |CLR(LCD_54) |CLR(LCD_55)|            \
                CLR(LCD_56) |CLR(LCD_57) |CLR(LCD_58) |CLR(LCD_59)|            \
                CLR(LCD_60) |CLR(LCD_61) |CLR(LCD_62) |CLR(LCD_63),            \
}

/**************************************************************************/ /*!
  * @brief   LCD back plane pins initialization with GD6363:
  * @details Enables LCD backplane pins for LCD glas driving:
  *          - Use "CLR" for disable pin, 
  *          - Use "SET" for enable pin, 
  *****************************************************************************/
#define LCD_BACK_PLANE_PINS_TWR_KL43                                           \
(tLCD_BP){                                                                     \
/* BPENL  */    CLR(LCD_00) |CLR(LCD_01) |CLR(LCD_02) |CLR(LCD_03)|            \
                CLR(LCD_04) |CLR(LCD_05) |CLR(LCD_06) |CLR(LCD_07)|            \
                CLR(LCD_08) |CLR(LCD_09) |CLR(LCD_10) |CLR(LCD_11)|            \
                SET(LCD_12) |SET(LCD_13) |SET(LCD_14) |SET(LCD_15)|            \
                CLR(LCD_16) |CLR(LCD_17) |CLR(LCD_18) |CLR(LCD_19)|            \
                CLR(LCD_20) |CLR(LCD_21) |CLR(LCD_22) |CLR(LCD_23)|            \
                CLR(LCD_24) |CLR(LCD_25) |CLR(LCD_26) |CLR(LCD_27)|            \
                CLR(LCD_28) |CLR(LCD_29) |CLR(LCD_30) |CLR(LCD_31),            \
/* BPENH  */    CLR(LCD_32) |CLR(LCD_33) |CLR(LCD_34) |CLR(LCD_35)|            \
                CLR(LCD_36) |CLR(LCD_37) |CLR(LCD_38) |CLR(LCD_39)|            \
                CLR(LCD_40) |CLR(LCD_41) |CLR(LCD_42) |CLR(LCD_43)|            \
                CLR(LCD_44) |CLR(LCD_45) |CLR(LCD_46) |CLR(LCD_47)|            \
                CLR(LCD_48) |CLR(LCD_49) |CLR(LCD_50) |CLR(LCD_51)|            \
                CLR(LCD_52) |CLR(LCD_53) |CLR(LCD_54) |CLR(LCD_55)|            \
                CLR(LCD_56) |CLR(LCD_57) |CLR(LCD_58) |CLR(LCD_59)|            \
                CLR(LCD_60) |CLR(LCD_61) |CLR(LCD_62) |CLR(LCD_63),            \
}

/**************************************************************************/ /*!
  * @brief   LCD back plane pins initialization for FRDM-KL46Z with S401M:
  * @details Enables LCD backplane pins for LCD glas driving:
  *          - Use "CLR" for disable pin, 
  *          - Use "SET" for enable pin, 
  *****************************************************************************/
#define LCD_BACK_PLANE_PINS_FRDM_KL46                                          \
(tLCD_BP){                                                                     \
/* BPENL  */    CLR(LCD_00) |CLR(LCD_01) |CLR(LCD_02) |CLR(LCD_03)|            \
                CLR(LCD_04) |CLR(LCD_05) |CLR(LCD_06) |CLR(LCD_07)|            \
                CLR(LCD_08) |CLR(LCD_09) |CLR(LCD_10) |CLR(LCD_11)|            \
                CLR(LCD_12) |CLR(LCD_13) |CLR(LCD_14) |CLR(LCD_15)|            \
                CLR(LCD_16) |CLR(LCD_17) |SET(LCD_18) |SET(LCD_19)|            \
                CLR(LCD_20) |CLR(LCD_21) |CLR(LCD_22) |CLR(LCD_23)|            \
                CLR(LCD_24) |CLR(LCD_25) |CLR(LCD_26) |CLR(LCD_27)|            \
                CLR(LCD_28) |CLR(LCD_29) |CLR(LCD_30) |CLR(LCD_31),            \
/* BPENH  */    CLR(LCD_32) |CLR(LCD_33) |CLR(LCD_34) |CLR(LCD_35)|            \
                CLR(LCD_36) |CLR(LCD_37) |CLR(LCD_38) |CLR(LCD_39)|            \
                SET(LCD_40) |CLR(LCD_41) |CLR(LCD_42) |CLR(LCD_43)|            \
                CLR(LCD_44) |CLR(LCD_45) |CLR(LCD_46) |CLR(LCD_47)|            \
                CLR(LCD_48) |CLR(LCD_49) |CLR(LCD_50) |CLR(LCD_51)|            \
                SET(LCD_52) |CLR(LCD_53) |CLR(LCD_54) |CLR(LCD_55)|            \
                CLR(LCD_56) |CLR(LCD_57) |CLR(LCD_58) |CLR(LCD_59)|            \
                CLR(LCD_60) |CLR(LCD_61) |CLR(LCD_62) |CLR(LCD_63),            \
}

/**************************************************************************/ /*!
  * @brief   LCD back plane pins initialization for FRDM-KL43Z with S401M:
  * @details Enables LCD backplane pins for LCD glas driving:
  *          - Use "CLR" for disable pin, 
  *          - Use "SET" for enable pin, 
  *****************************************************************************/
#define LCD_BACK_PLANE_PINS_FRDM_KL43                                          \
(tLCD_BP){                                                                     \
/* BPENL  */    CLR(LCD_00) |CLR(LCD_01) |CLR(LCD_02) |CLR(LCD_03)|            \
                CLR(LCD_04) |CLR(LCD_05) |CLR(LCD_06) |CLR(LCD_07)|            \
                CLR(LCD_08) |CLR(LCD_09) |CLR(LCD_10) |CLR(LCD_11)|            \
                CLR(LCD_12) |CLR(LCD_13) |SET(LCD_14) |SET(LCD_15)|            \
                CLR(LCD_16) |CLR(LCD_17) |CLR(LCD_18) |CLR(LCD_19)|            \
                CLR(LCD_20) |CLR(LCD_21) |CLR(LCD_22) |CLR(LCD_23)|            \
                CLR(LCD_24) |CLR(LCD_25) |CLR(LCD_26) |CLR(LCD_27)|            \
                CLR(LCD_28) |CLR(LCD_29) |CLR(LCD_30) |CLR(LCD_31),            \
/* BPENH  */    CLR(LCD_32) |CLR(LCD_33) |CLR(LCD_34) |CLR(LCD_35)|            \
                CLR(LCD_36) |CLR(LCD_37) |CLR(LCD_38) |CLR(LCD_39)|            \
                CLR(LCD_40) |CLR(LCD_41) |CLR(LCD_42) |CLR(LCD_43)|            \
                CLR(LCD_44) |CLR(LCD_45) |CLR(LCD_46) |CLR(LCD_47)|            \
                CLR(LCD_48) |CLR(LCD_49) |CLR(LCD_50) |CLR(LCD_51)|            \
                CLR(LCD_52) |CLR(LCD_53) |CLR(LCD_54) |CLR(LCD_55)|            \
                CLR(LCD_56) |CLR(LCD_57) |CLR(LCD_58) |SET(LCD_59)|            \
                SET(LCD_60) |CLR(LCD_61) |CLR(LCD_62) |CLR(LCD_63),            \
}

/**************************************************************************/ /*!
  * @brief   LCD segments initialization:
  * @details Set back planes pins for LCD panel. 
  *          - Use "LCD_OFF" for no back plane assign, 
  *          - Use "LCD_BP1" for back plane 0, 
  *          - Use "LCD_BP2" for back plane 1, 
  *          - Use "LCD_BP3" for back plane 2, 
  *          - Use "LCD_BP4" for back plane 3, 
  *          - Use "LCD_BP5" for back plane 4, 
  *          - Use "LCD_BP6" for back plane 5, 
  *          - Use "LCD_BP7" for back plane 6, 
  *          - Use "LCD_BP8" for back plane 7, 
  *****************************************************************************/
#define LCD_ASSIGN_BACK_PLANES                                                 \
(tLCD_CP){                                                                     \
/* WF3TO0   */  LCD_WF_WF3 (LCD_OFF) |LCD_WF_WF2 (LCD_OFF)|                    \
                LCD_WF_WF1 (LCD_OFF) |LCD_WF_WF0 (LCD_OFF),                    \
/* WF7TO4   */  LCD_WF_WF7 (LCD_OFF) |LCD_WF_WF6 (LCD_OFF)|                    \
                LCD_WF_WF5 (LCD_OFF) |LCD_WF_WF4 (LCD_OFF),                    \
/* WF11TO8  */  LCD_WF_WF11(LCD_OFF) |LCD_WF_WF10(LCD_OFF)|                    \
                LCD_WF_WF9 (LCD_OFF) |LCD_WF_WF8 (LCD_OFF),                    \
/* WF15TO12 */  LCD_WF_WF15(LCD_BP2) |LCD_WF_WF14(LCD_BP3)|                    \
                LCD_WF_WF13(LCD_BP4) |LCD_WF_WF12(LCD_OFF),                    \
/* WF19TO16 */  LCD_WF_WF19(LCD_OFF) |LCD_WF_WF18(LCD_OFF)|                    \
                LCD_WF_WF17(LCD_OFF) |LCD_WF_WF16(LCD_BP1),                    \
/* WF23TO20 */  LCD_WF_WF23(LCD_OFF) |LCD_WF_WF22(LCD_OFF)|                    \
                LCD_WF_WF21(LCD_OFF) |LCD_WF_WF20(LCD_OFF),                    \
/* WF27TO24 */  LCD_WF_WF27(LCD_OFF) |LCD_WF_WF26(LCD_OFF)|                    \
                LCD_WF_WF25(LCD_OFF) |LCD_WF_WF24(LCD_OFF),                    \
/* WF31TO28 */  LCD_WF_WF31(LCD_OFF) |LCD_WF_WF30(LCD_OFF)|                    \
                LCD_WF_WF29(LCD_OFF) |LCD_WF_WF28(LCD_OFF),                    \
/* WF35TO32 */  LCD_WF_WF35(LCD_OFF) |LCD_WF_WF34(LCD_OFF)|                    \
                LCD_WF_WF33(LCD_OFF) |LCD_WF_WF32(LCD_OFF),                    \
/* WF39TO36 */  LCD_WF_WF39(LCD_OFF) |LCD_WF_WF38(LCD_OFF)|                    \
                LCD_WF_WF37(LCD_OFF) |LCD_WF_WF36(LCD_OFF),                    \
/* WF43TO40 */  LCD_WF_WF43(LCD_OFF) |LCD_WF_WF42(LCD_OFF)|                    \
                LCD_WF_WF41(LCD_OFF) |LCD_WF_WF40(LCD_OFF),                    \
/* WF47TO44 */  LCD_WF_WF47(LCD_OFF) |LCD_WF_WF46(LCD_OFF)|                    \
                LCD_WF_WF45(LCD_OFF) |LCD_WF_WF44(LCD_OFF),                    \
/* WF51TO48 */  LCD_WF_WF51(LCD_OFF) |LCD_WF_WF50(LCD_OFF)|                    \
                LCD_WF_WF49(LCD_OFF) |LCD_WF_WF48(LCD_OFF),                    \
/* WF55TO52 */  LCD_WF_WF55(LCD_OFF) |LCD_WF_WF54(LCD_OFF)|                    \
                LCD_WF_WF53(LCD_OFF) |LCD_WF_WF52(LCD_OFF),                    \
/* WF59TO56 */  LCD_WF_WF59(LCD_OFF) |LCD_WF_WF58(LCD_OFF)|                    \
                LCD_WF_WF57(LCD_OFF) |LCD_WF_WF56(LCD_OFF),                    \
/* WF63TO60 */  LCD_WF_WF63(LCD_OFF) |LCD_WF_WF62(LCD_OFF)|                    \
                LCD_WF_WF61(LCD_OFF) |LCD_WF_WF60(LCD_OFF),                    \
}

/**************************************************************************/ /*!
  * @brief   LCD segments initialization with GD6363:
  * @details Set back planes pins for LCD panel. 
  *          - Use "LCD_OFF" for no back plane assign, 
  *          - Use "LCD_BP1" for back plane 0, 
  *          - Use "LCD_BP2" for back plane 1, 
  *          - Use "LCD_BP3" for back plane 2, 
  *          - Use "LCD_BP4" for back plane 3, 
  *          - Use "LCD_BP5" for back plane 4, 
  *          - Use "LCD_BP6" for back plane 5, 
  *          - Use "LCD_BP7" for back plane 6, 
  *          - Use "LCD_BP8" for back plane 7, 
  *****************************************************************************/
#define LCD_ASSIGN_BACK_PLANES_TWR_KL43                                        \
(tLCD_CP){                                                                     \
/* WF3TO0   */  LCD_WF_WF0 (LCD_OFF) |LCD_WF_WF1 (LCD_OFF)|                    \
                LCD_WF_WF2 (LCD_OFF) |LCD_WF_WF3 (LCD_OFF),                    \
/* WF7TO4   */  LCD_WF_WF4 (LCD_OFF) |LCD_WF_WF5 (LCD_OFF)|                    \
                LCD_WF_WF6 (LCD_OFF) |LCD_WF_WF7 (LCD_OFF),                    \
/* WF11TO8  */  LCD_WF_WF8 (LCD_OFF) |LCD_WF_WF9 (LCD_OFF)|                    \
                LCD_WF_WF10(LCD_OFF) |LCD_WF_WF11(LCD_OFF),                    \
/* WF15TO12 */  LCD_WF_WF12(LCD_BP1) |LCD_WF_WF13(LCD_BP2)|                    \
                LCD_WF_WF14(LCD_BP3) |LCD_WF_WF15(LCD_BP4),                    \
/* WF19TO16 */  LCD_WF_WF16(LCD_OFF) |LCD_WF_WF17(LCD_OFF)|                    \
                LCD_WF_WF18(LCD_OFF) |LCD_WF_WF19(LCD_OFF),                    \
/* WF23TO20 */  LCD_WF_WF20(LCD_OFF) |LCD_WF_WF21(LCD_OFF)|                    \
                LCD_WF_WF22(LCD_OFF) |LCD_WF_WF23(LCD_OFF),                    \
/* WF27TO24 */  LCD_WF_WF24(LCD_OFF) |LCD_WF_WF25(LCD_OFF)|                    \
                LCD_WF_WF26(LCD_OFF) |LCD_WF_WF27(LCD_OFF),                    \
/* WF31TO28 */  LCD_WF_WF28(LCD_OFF) |LCD_WF_WF29(LCD_OFF)|                    \
                LCD_WF_WF30(LCD_OFF) |LCD_WF_WF31(LCD_OFF),                    \
/* WF35TO32 */  LCD_WF_WF32(LCD_OFF) |LCD_WF_WF33(LCD_OFF)|                    \
                LCD_WF_WF34(LCD_OFF) |LCD_WF_WF35(LCD_OFF),                    \
/* WF39TO36 */  LCD_WF_WF36(LCD_OFF) |LCD_WF_WF37(LCD_OFF)|                    \
                LCD_WF_WF38(LCD_OFF) |LCD_WF_WF39(LCD_OFF),                    \
/* WF43TO40 */  LCD_WF_WF40(LCD_OFF) |LCD_WF_WF41(LCD_OFF)|                    \
                LCD_WF_WF42(LCD_OFF) |LCD_WF_WF43(LCD_OFF),                    \
/* WF47TO44 */  LCD_WF_WF44(LCD_OFF) |LCD_WF_WF45(LCD_OFF)|                    \
                LCD_WF_WF46(LCD_OFF) |LCD_WF_WF47(LCD_OFF),                    \
/* WF51TO48 */  LCD_WF_WF48(LCD_OFF) |LCD_WF_WF49(LCD_OFF)|                    \
                LCD_WF_WF50(LCD_OFF) |LCD_WF_WF51(LCD_OFF),                    \
/* WF55TO52 */  LCD_WF_WF52(LCD_OFF) |LCD_WF_WF53(LCD_OFF)|                    \
                LCD_WF_WF54(LCD_OFF) |LCD_WF_WF55(LCD_OFF),                    \
/* WF59TO56 */  LCD_WF_WF56(LCD_OFF) |LCD_WF_WF57(LCD_OFF)|                    \
                LCD_WF_WF58(LCD_OFF) |LCD_WF_WF59(LCD_OFF),                    \
/* WF63TO60 */  LCD_WF_WF60(LCD_OFF) |LCD_WF_WF61(LCD_OFF)|                    \
                LCD_WF_WF62(LCD_OFF) |LCD_WF_WF63(LCD_OFF),                    \
}

/**************************************************************************/ /*!
  * @brief   LCD segments initialization for FRDM-KL46Z with S401M:
  * @details Set back planes pins for LCD panel. 
  *          - Use "LCD_OFF" for no back plane assign, 
  *          - Use "LCD_BP1" for back plane 0, 
  *          - Use "LCD_BP2" for back plane 1, 
  *          - Use "LCD_BP3" for back plane 2, 
  *          - Use "LCD_BP4" for back plane 3,
  *****************************************************************************/
#define LCD_ASSIGN_BACK_PLANES_FRDM_KL46                                       \
(tLCD_CP){                                                                     \
/* WF3TO0   */  LCD_WF_WF0 (LCD_OFF) |LCD_WF_WF1 (LCD_OFF)|                    \
                LCD_WF_WF2 (LCD_OFF) |LCD_WF_WF3 (LCD_OFF),                    \
/* WF7TO4   */  LCD_WF_WF4 (LCD_OFF) |LCD_WF_WF5 (LCD_OFF)|                    \
                LCD_WF_WF6 (LCD_OFF) |LCD_WF_WF7 (LCD_OFF),                    \
/* WF11TO8  */  LCD_WF_WF8 (LCD_OFF) |LCD_WF_WF9 (LCD_OFF)|                    \
                LCD_WF_WF10(LCD_OFF) |LCD_WF_WF11(LCD_OFF),                    \
/* WF15TO12 */  LCD_WF_WF12(LCD_OFF) |LCD_WF_WF13(LCD_OFF)|                    \
                LCD_WF_WF14(LCD_OFF) |LCD_WF_WF15(LCD_OFF),                    \
/* WF19TO16 */  LCD_WF_WF16(LCD_OFF) |LCD_WF_WF17(LCD_OFF)|                    \
                LCD_WF_WF18(LCD_BP4) |LCD_WF_WF19(LCD_BP3),                    \
/* WF23TO20 */  LCD_WF_WF20(LCD_OFF) |LCD_WF_WF21(LCD_OFF)|                    \
                LCD_WF_WF22(LCD_OFF) |LCD_WF_WF23(LCD_OFF),                    \
/* WF27TO24 */  LCD_WF_WF24(LCD_OFF) |LCD_WF_WF25(LCD_OFF)|                    \
                LCD_WF_WF26(LCD_OFF) |LCD_WF_WF27(LCD_OFF),                    \
/* WF31TO28 */  LCD_WF_WF28(LCD_OFF) |LCD_WF_WF29(LCD_OFF)|                    \
                LCD_WF_WF30(LCD_OFF) |LCD_WF_WF31(LCD_OFF),                    \
/* WF35TO32 */  LCD_WF_WF32(LCD_OFF) |LCD_WF_WF33(LCD_OFF)|                    \
                LCD_WF_WF34(LCD_OFF) |LCD_WF_WF35(LCD_OFF),                    \
/* WF39TO36 */  LCD_WF_WF36(LCD_OFF) |LCD_WF_WF37(LCD_OFF)|                    \
                LCD_WF_WF38(LCD_OFF) |LCD_WF_WF39(LCD_OFF),                    \
/* WF43TO40 */  LCD_WF_WF40(LCD_BP1) |LCD_WF_WF41(LCD_OFF)|                    \
                LCD_WF_WF42(LCD_OFF) |LCD_WF_WF43(LCD_OFF),                    \
/* WF47TO44 */  LCD_WF_WF44(LCD_OFF) |LCD_WF_WF45(LCD_OFF)|                    \
                LCD_WF_WF46(LCD_OFF) |LCD_WF_WF47(LCD_OFF),                    \
/* WF51TO48 */  LCD_WF_WF48(LCD_OFF) |LCD_WF_WF49(LCD_OFF)|                    \
                LCD_WF_WF50(LCD_OFF) |LCD_WF_WF51(LCD_OFF),                    \
/* WF55TO52 */  LCD_WF_WF52(LCD_BP2) |LCD_WF_WF53(LCD_OFF)|                    \
                LCD_WF_WF54(LCD_OFF) |LCD_WF_WF55(LCD_OFF),                    \
/* WF59TO56 */  LCD_WF_WF56(LCD_OFF) |LCD_WF_WF57(LCD_OFF)|                    \
                LCD_WF_WF58(LCD_OFF) |LCD_WF_WF59(LCD_OFF),                    \
/* WF63TO60 */  LCD_WF_WF60(LCD_OFF) |LCD_WF_WF61(LCD_OFF)|                    \
                LCD_WF_WF62(LCD_OFF) |LCD_WF_WF63(LCD_OFF),                    \
}


/**************************************************************************/ /*!
  * @brief   LCD segments initialization for FRDN-KL43Z with S401M:
  * @details Set back planes pins for LCD panel. 
  *          - Use "LCD_OFF" for no back plane assign, 
  *          - Use "LCD_BP1" for back plane 0, 
  *          - Use "LCD_BP2" for back plane 1, 
  *          - Use "LCD_BP3" for back plane 2, 
  *          - Use "LCD_BP4" for back plane 3,
  *****************************************************************************/
#define LCD_ASSIGN_BACK_PLANES_FRDM_KL43                                       \
(tLCD_CP){                                                                     \
/* WF3TO0   */  LCD_WF_WF0 (LCD_OFF) |LCD_WF_WF1 (LCD_OFF)|                    \
                LCD_WF_WF2 (LCD_OFF) |LCD_WF_WF3 (LCD_OFF),                    \
/* WF7TO4   */  LCD_WF_WF4 (LCD_OFF) |LCD_WF_WF5 (LCD_OFF)|                    \
                LCD_WF_WF6 (LCD_OFF) |LCD_WF_WF7 (LCD_OFF),                    \
/* WF11TO8  */  LCD_WF_WF8 (LCD_OFF) |LCD_WF_WF9 (LCD_OFF)|                    \
                LCD_WF_WF10(LCD_OFF) |LCD_WF_WF11(LCD_OFF),                    \
/* WF15TO12 */  LCD_WF_WF12(LCD_OFF) |LCD_WF_WF13(LCD_OFF)|                    \
                LCD_WF_WF14(LCD_BP3) |LCD_WF_WF15(LCD_BP4),                    \
/* WF19TO16 */  LCD_WF_WF16(LCD_OFF) |LCD_WF_WF17(LCD_OFF)|                    \
                LCD_WF_WF18(LCD_OFF) |LCD_WF_WF19(LCD_OFF),                    \
/* WF23TO20 */  LCD_WF_WF20(LCD_OFF) |LCD_WF_WF21(LCD_OFF)|                    \
                LCD_WF_WF22(LCD_OFF) |LCD_WF_WF23(LCD_OFF),                    \
/* WF27TO24 */  LCD_WF_WF24(LCD_OFF) |LCD_WF_WF25(LCD_OFF)|                    \
                LCD_WF_WF26(LCD_OFF) |LCD_WF_WF27(LCD_OFF),                    \
/* WF31TO28 */  LCD_WF_WF28(LCD_OFF) |LCD_WF_WF29(LCD_OFF)|                    \
                LCD_WF_WF30(LCD_OFF) |LCD_WF_WF31(LCD_OFF),                    \
/* WF35TO32 */  LCD_WF_WF32(LCD_OFF) |LCD_WF_WF33(LCD_OFF)|                    \
                LCD_WF_WF34(LCD_OFF) |LCD_WF_WF35(LCD_OFF),                    \
/* WF39TO36 */  LCD_WF_WF36(LCD_OFF) |LCD_WF_WF37(LCD_OFF)|                    \
                LCD_WF_WF38(LCD_OFF) |LCD_WF_WF39(LCD_OFF),                    \
/* WF43TO40 */  LCD_WF_WF40(LCD_OFF) |LCD_WF_WF41(LCD_OFF)|                    \
                LCD_WF_WF42(LCD_OFF) |LCD_WF_WF43(LCD_OFF),                    \
/* WF47TO44 */  LCD_WF_WF44(LCD_OFF) |LCD_WF_WF45(LCD_OFF)|                    \
                LCD_WF_WF46(LCD_OFF) |LCD_WF_WF47(LCD_OFF),                    \
/* WF51TO48 */  LCD_WF_WF48(LCD_OFF) |LCD_WF_WF49(LCD_OFF)|                    \
                LCD_WF_WF50(LCD_OFF) |LCD_WF_WF51(LCD_OFF),                    \
/* WF55TO52 */  LCD_WF_WF52(LCD_OFF) |LCD_WF_WF53(LCD_OFF)|                    \
                LCD_WF_WF54(LCD_OFF) |LCD_WF_WF55(LCD_OFF),                    \
/* WF59TO56 */  LCD_WF_WF56(LCD_OFF) |LCD_WF_WF57(LCD_OFF)|                    \
                LCD_WF_WF58(LCD_OFF) |LCD_WF_WF59(LCD_BP1),                    \
/* WF63TO60 */  LCD_WF_WF60(LCD_BP2) |LCD_WF_WF61(LCD_OFF)|                    \
                LCD_WF_WF62(LCD_OFF) |LCD_WF_WF63(LCD_OFF),                    \
}

/**************************************************************************/ /*!
  * @brief   LCD segments initialization:
  * @details Set all LCD panel segments to ON state. 
  *          - Use "LCD_BP1" for back plane 0, 
  *          - Use "LCD_BP2" for back plane 1, 
  *          - Use "LCD_BP3" for back plane 2, 
  *          - Use "LCD_BP4" for back plane 3, 
  *          - Use "LCD_BP5" for back plane 4, 
  *          - Use "LCD_BP6" for back plane 5, 
  *          - Use "LCD_BP7" for back plane 6, 
  *          - Use "LCD_BP8" for back plane 7, 
  *          - Use "LCD_OFF" for unused segment, 
  *          - Use "LCD_ON1" for segment ON with 1 back plane, 
  *          - Use "LCD_ON2" for segment ON with 2 back planes, 
  *          - Use "LCD_ON3" for segment ON with 3 back planes,  
  *          - Use "LCD_ON4" for segment ON with 4 back planes, 
  *          - Use "LCD_ON5" for segment ON with 5 back planes, 
  *          - Use "LCD_ON6" for segment ON with 6 back planes,  
  *          - Use "LCD_ON7" for segment ON with 7 back planes,  
  *          - Use "LCD_ON8" for segment ON with 8 back planes,  
  *****************************************************************************/
#define LCD_ALL_SEGMENTS_ON                                                    \
(tLCD_CP){                                                                     \
/* WF3TO0   */  LCD_WF_WF0 (LCD_OFF) |LCD_WF_WF1 (LCD_OFF)|                    \
                LCD_WF_WF2 (LCD_OFF) |LCD_WF_WF3 (LCD_OFF),                    \
/* WF7TO4   */  LCD_WF_WF4 (LCD_OFF) |LCD_WF_WF5 (LCD_OFF)|                    \
                LCD_WF_WF6 (LCD_OFF) |LCD_WF_WF7 (LCD_OFF),                    \
/* WF11TO8  */  LCD_WF_WF8 (LCD_OFF) |LCD_WF_WF9 (LCD_OFF)|                    \
                LCD_WF_WF10(LCD_OFF) |LCD_WF_WF11(LCD_OFF),                    \
/* WF15TO12 */  LCD_WF_WF12(LCD_OFF) |LCD_WF_WF13(LCD_BP4)|                    \
                LCD_WF_WF14(LCD_BP3) |LCD_WF_WF15(LCD_BP2),                    \
/* WF19TO16 */  LCD_WF_WF16(LCD_BP1) |LCD_WF_WF17(LCD_ON4)|                    \
                LCD_WF_WF18(LCD_ON4) |LCD_WF_WF19(LCD_ON4),                    \
/* WF23TO20 */  LCD_WF_WF20(LCD_ON4) |LCD_WF_WF21(LCD_ON4)|                    \
                LCD_WF_WF22(LCD_ON4) |LCD_WF_WF23(LCD_ON4),                    \
/* WF27TO24 */  LCD_WF_WF24(LCD_ON4) |LCD_WF_WF25(LCD_ON4)|                    \
                LCD_WF_WF26(LCD_ON4) |LCD_WF_WF27(LCD_ON4),                    \
/* WF31TO28 */  LCD_WF_WF28(LCD_ON4) |LCD_WF_WF29(LCD_ON4)|                    \
                LCD_WF_WF30(LCD_ON4) |LCD_WF_WF31(LCD_ON4),                    \
/* WF35TO32 */  LCD_WF_WF32(LCD_ON4) |LCD_WF_WF33(LCD_ON4)|                    \
                LCD_WF_WF34(LCD_ON4) |LCD_WF_WF35(LCD_ON4),                    \
/* WF39TO36 */  LCD_WF_WF36(LCD_ON4) |LCD_WF_WF37(LCD_ON4)|                    \
                LCD_WF_WF38(LCD_OFF) |LCD_WF_WF39(LCD_OFF),                    \
/* WF43TO40 */  LCD_WF_WF40(LCD_OFF) |LCD_WF_WF41(LCD_OFF)|                    \
                LCD_WF_WF42(LCD_OFF) |LCD_WF_WF43(LCD_OFF),                    \
/* WF47TO44 */  LCD_WF_WF44(LCD_OFF) |LCD_WF_WF45(LCD_OFF)|                    \
                LCD_WF_WF46(LCD_OFF) |LCD_WF_WF47(LCD_OFF),                    \
/* WF51TO48 */  LCD_WF_WF48(LCD_OFF) |LCD_WF_WF49(LCD_OFF)|                    \
                LCD_WF_WF50(LCD_OFF) |LCD_WF_WF51(LCD_OFF),                    \
/* WF55TO52 */  LCD_WF_WF52(LCD_OFF) |LCD_WF_WF53(LCD_OFF)|                    \
                LCD_WF_WF54(LCD_OFF) |LCD_WF_WF55(LCD_OFF),                    \
/* WF59TO56 */  LCD_WF_WF56(LCD_OFF) |LCD_WF_WF57(LCD_OFF)|                    \
                LCD_WF_WF58(LCD_OFF) |LCD_WF_WF59(LCD_OFF),                    \
/* WF63TO60 */  LCD_WF_WF60(LCD_OFF) |LCD_WF_WF61(LCD_OFF)|                    \
                LCD_WF_WF62(LCD_OFF) |LCD_WF_WF63(LCD_OFF),                    \
}

/**************************************************************************/ /*!
  * @brief   LCD segments initialization with GD6363:
  * @details Set all LCD panel segments to ON state. 
  *          - Use "LCD_BP1" for back plane 0, 
  *          - Use "LCD_BP2" for back plane 1, 
  *          - Use "LCD_BP3" for back plane 2, 
  *          - Use "LCD_BP4" for back plane 3, 
  *          - Use "LCD_BP5" for back plane 4, 
  *          - Use "LCD_BP6" for back plane 5, 
  *          - Use "LCD_BP7" for back plane 6, 
  *          - Use "LCD_BP8" for back plane 7, 
  *          - Use "LCD_OFF" for unused segment, 
  *          - Use "LCD_ON1" for segment ON with 1 back plane, 
  *          - Use "LCD_ON2" for segment ON with 2 back planes, 
  *          - Use "LCD_ON3" for segment ON with 3 back planes,  
  *          - Use "LCD_ON4" for segment ON with 4 back planes, 
  *          - Use "LCD_ON5" for segment ON with 5 back planes, 
  *          - Use "LCD_ON6" for segment ON with 6 back planes,  
  *          - Use "LCD_ON7" for segment ON with 7 back planes,  
  *          - Use "LCD_ON8" for segment ON with 8 back planes,  
  *****************************************************************************/
#define LCD_ALL_SEGMENTS_ON_TWR_KL43                                           \
(tLCD_CP){                                                                     \
/* WF3TO0   */  LCD_WF_WF0 (LCD_OFF) |LCD_WF_WF1 (LCD_OFF)|                    \
                LCD_WF_WF2 (LCD_OFF) |LCD_WF_WF3 (LCD_OFF),                    \
/* WF7TO4   */  LCD_WF_WF4 (LCD_OFF) |LCD_WF_WF5 (LCD_OFF)|                    \
                LCD_WF_WF6 (LCD_OFF) |LCD_WF_WF7 (LCD_OFF),                    \
/* WF11TO8  */  LCD_WF_WF8 (LCD_OFF) |LCD_WF_WF9 (LCD_BP8)|                    \
                LCD_WF_WF10(LCD_BP7) |LCD_WF_WF11(LCD_BP6),                    \
/* WF15TO12 */  LCD_WF_WF12(LCD_BP5) |LCD_WF_WF13(LCD_BP4)|                    \
                LCD_WF_WF14(LCD_BP3) |LCD_WF_WF15(LCD_BP2),                    \
/* WF19TO16 */  LCD_WF_WF16(LCD_BP1) |LCD_WF_WF17(LCD_ON8)|                    \
                LCD_WF_WF18(LCD_ON8) |LCD_WF_WF19(LCD_ON8),                    \
/* WF23TO20 */  LCD_WF_WF20(LCD_ON8) |LCD_WF_WF21(LCD_ON8)|                    \
                LCD_WF_WF22(LCD_ON8) |LCD_WF_WF23(LCD_ON8),                    \
/* WF27TO24 */  LCD_WF_WF24(LCD_ON8) |LCD_WF_WF25(LCD_ON8)|                    \
                LCD_WF_WF26(LCD_ON8) |LCD_WF_WF27(LCD_ON8),                    \
/* WF31TO28 */  LCD_WF_WF28(LCD_ON8) |LCD_WF_WF29(LCD_OFF)|                    \
                LCD_WF_WF30(LCD_OFF) |LCD_WF_WF31(LCD_ON8),                    \
/* WF35TO32 */  LCD_WF_WF32(LCD_ON8) |LCD_WF_WF33(LCD_ON8)|                    \
                LCD_WF_WF34(LCD_ON8) |LCD_WF_WF35(LCD_ON8),                    \
/* WF39TO36 */  LCD_WF_WF36(LCD_ON8) |LCD_WF_WF37(LCD_ON8)|                    \
                LCD_WF_WF38(LCD_OFF) |LCD_WF_WF39(LCD_OFF),                    \
/* WF43TO40 */  LCD_WF_WF40(LCD_OFF) |LCD_WF_WF41(LCD_OFF)|                    \
                LCD_WF_WF42(LCD_OFF) |LCD_WF_WF43(LCD_ON8),                    \
/* WF47TO44 */  LCD_WF_WF44(LCD_OFF) |LCD_WF_WF45(LCD_OFF)|                    \
                LCD_WF_WF46(LCD_OFF) |LCD_WF_WF47(LCD_OFF),                    \
/* WF51TO48 */  LCD_WF_WF48(LCD_OFF) |LCD_WF_WF49(LCD_OFF)|                    \
                LCD_WF_WF50(LCD_OFF) |LCD_WF_WF51(LCD_OFF),                    \
/* WF55TO52 */  LCD_WF_WF52(LCD_OFF) |LCD_WF_WF53(LCD_OFF)|                    \
                LCD_WF_WF54(LCD_OFF) |LCD_WF_WF55(LCD_OFF),                    \
/* WF59TO56 */  LCD_WF_WF56(LCD_OFF) |LCD_WF_WF57(LCD_OFF)|                    \
                LCD_WF_WF58(LCD_OFF) |LCD_WF_WF59(LCD_OFF),                    \
/* WF63TO60 */  LCD_WF_WF60(LCD_OFF) |LCD_WF_WF61(LCD_OFF)|                    \
                LCD_WF_WF62(LCD_OFF) |LCD_WF_WF63(LCD_OFF),                    \
}

/**************************************************************************/ /*!
  * @brief   LCD segments initialization with S401M:
  * @details Set all LCD panel segments to ON state. 
  *          - Use "LCD_BP1" for back plane 0, 
  *          - Use "LCD_BP2" for back plane 1, 
  *          - Use "LCD_BP3" for back plane 2, 
  *          - Use "LCD_BP4" for back plane 3, 
  *          - Use "LCD_OFF" for unused segment, 
  *          - Use "LCD_ON1" for segment ON with 1 back plane, 
  *          - Use "LCD_ON2" for segment ON with 2 back planes, 
  *          - Use "LCD_ON3" for segment ON with 3 back planes,  
  *          - Use "LCD_ON4" for segment ON with 4 back planes, 
  *          - Use "LCD_ON5" for segment ON with 5 back planes, 
  *          - Use "LCD_ON6" for segment ON with 6 back planes,  
  *          - Use "LCD_ON7" for segment ON with 7 back planes,  
  *          - Use "LCD_ON8" for segment ON with 8 back planes,  
  *****************************************************************************/
#define LCD_ALL_SEGMENTS_ON_FRDM_KL43                                          \
(tLCD_CP){                                                                     \
/* WF3TO0   */  LCD_WF_WF0 (LCD_OFF) |LCD_WF_WF1 (LCD_OFF)|                    \
                LCD_WF_WF2 (LCD_OFF) |LCD_WF_WF3 (LCD_OFF),                    \
/* WF7TO4   */  LCD_WF_WF4 (LCD_OFF) |LCD_WF_WF5 (LCD_OFF)|                    \
                LCD_WF_WF6 (LCD_OFF) |LCD_WF_WF7 (LCD_ON8),                    \
/* WF11TO8  */  LCD_WF_WF8 (LCD_ON8) |LCD_WF_WF9 (LCD_OFF)|                    \
                LCD_WF_WF10(LCD_ON8) |LCD_WF_WF11(LCD_ON8),                    \
/* WF15TO12 */  LCD_WF_WF12(LCD_OFF) |LCD_WF_WF13(LCD_OFF)|                    \
                LCD_WF_WF14(LCD_OFF) |LCD_WF_WF15(LCD_OFF),                    \
/* WF19TO16 */  LCD_WF_WF16(LCD_OFF) |LCD_WF_WF17(LCD_ON8)|                    \
                LCD_WF_WF18(LCD_BP4) |LCD_WF_WF19(LCD_BP3),                    \
/* WF23TO20 */  LCD_WF_WF20(LCD_OFF) |LCD_WF_WF21(LCD_OFF)|                    \
                LCD_WF_WF22(LCD_OFF) |LCD_WF_WF23(LCD_OFF),                    \
/* WF27TO24 */  LCD_WF_WF24(LCD_OFF) |LCD_WF_WF25(LCD_OFF)|                    \
                LCD_WF_WF26(LCD_OFF) |LCD_WF_WF27(LCD_OFF),                    \
/* WF31TO28 */  LCD_WF_WF28(LCD_OFF) |LCD_WF_WF29(LCD_OFF)|                    \
                LCD_WF_WF30(LCD_OFF) |LCD_WF_WF31(LCD_OFF),                    \
/* WF35TO32 */  LCD_WF_WF32(LCD_OFF) |LCD_WF_WF33(LCD_OFF)|                    \
                LCD_WF_WF34(LCD_OFF) |LCD_WF_WF35(LCD_OFF),                    \
/* WF39TO36 */  LCD_WF_WF36(LCD_OFF) |LCD_WF_WF37(LCD_ON8)|                    \
                LCD_WF_WF38(LCD_ON8) |LCD_WF_WF39(LCD_OFF),                    \
/* WF43TO40 */  LCD_WF_WF40(LCD_BP1) |LCD_WF_WF41(LCD_OFF)|                    \
                LCD_WF_WF42(LCD_OFF) |LCD_WF_WF43(LCD_OFF),                    \
/* WF47TO44 */  LCD_WF_WF44(LCD_OFF) |LCD_WF_WF45(LCD_OFF)|                    \
                LCD_WF_WF46(LCD_OFF) |LCD_WF_WF47(LCD_OFF),                    \
/* WF51TO48 */  LCD_WF_WF48(LCD_OFF) |LCD_WF_WF49(LCD_OFF)|                    \
                LCD_WF_WF50(LCD_OFF) |LCD_WF_WF51(LCD_OFF),                    \
/* WF55TO52 */  LCD_WF_WF52(LCD_BP2) |LCD_WF_WF53(LCD_ON8)|                    \
                LCD_WF_WF54(LCD_OFF) |LCD_WF_WF55(LCD_OFF),                    \
/* WF59TO56 */  LCD_WF_WF56(LCD_OFF) |LCD_WF_WF57(LCD_OFF)|                    \
                LCD_WF_WF58(LCD_OFF) |LCD_WF_WF59(LCD_OFF),                    \
/* WF63TO60 */  LCD_WF_WF60(LCD_OFF) |LCD_WF_WF61(LCD_OFF)|                    \
                LCD_WF_WF62(LCD_OFF) |LCD_WF_WF63(LCD_OFF),                    \
}

/**************************************************************************/ /*!
  * @brief   LCD segments initialization:
  * @details Set all LCD panel segments to ON state. 
  *          - Use "LCD_BP1" for back plane 0, 
  *          - Use "LCD_BP2" for back plane 1, 
  *          - Use "LCD_BP3" for back plane 2, 
  *          - Use "LCD_BP4" for back plane 3, 
  *          - Use "LCD_BP5" for back plane 4, 
  *          - Use "LCD_BP6" for back plane 5, 
  *          - Use "LCD_BP7" for back plane 6, 
  *          - Use "LCD_BP8" for back plane 7, 
  *          - Use "LCD_OFF" for unused segment, 
  *****************************************************************************/
#define LCD_ALL_SEGMENTS_OFF                                                   \
(tLCD_CP){                                                                     \
/* WF3TO0   */  LCD_WF_WF0 (LCD_OFF) |LCD_WF_WF1 (LCD_OFF)|                    \
                LCD_WF_WF2 (LCD_OFF) |LCD_WF_WF3 (LCD_OFF),                    \
/* WF7TO4   */  LCD_WF_WF4 (LCD_OFF) |LCD_WF_WF5 (LCD_OFF)|                    \
                LCD_WF_WF6 (LCD_OFF) |LCD_WF_WF7 (LCD_OFF),                    \
/* WF11TO8  */  LCD_WF_WF8 (LCD_OFF) |LCD_WF_WF9 (LCD_OFF)|                    \
                LCD_WF_WF10(LCD_OFF) |LCD_WF_WF11(LCD_OFF),                    \
/* WF15TO12 */  LCD_WF_WF12(LCD_OFF) |LCD_WF_WF13(LCD_BP4)|                    \
                LCD_WF_WF14(LCD_BP3) |LCD_WF_WF15(LCD_BP2),                    \
/* WF19TO16 */  LCD_WF_WF16(LCD_BP1) |LCD_WF_WF17(LCD_OFF)|                    \
                LCD_WF_WF18(LCD_OFF) |LCD_WF_WF19(LCD_OFF),                    \
/* WF23TO20 */  LCD_WF_WF20(LCD_OFF) |LCD_WF_WF21(LCD_OFF)|                    \
                LCD_WF_WF22(LCD_OFF) |LCD_WF_WF23(LCD_OFF),                    \
/* WF27TO24 */  LCD_WF_WF24(LCD_OFF) |LCD_WF_WF25(LCD_OFF)|                    \
                LCD_WF_WF26(LCD_OFF) |LCD_WF_WF27(LCD_OFF),                    \
/* WF31TO28 */  LCD_WF_WF28(LCD_OFF) |LCD_WF_WF29(LCD_OFF)|                    \
                LCD_WF_WF30(LCD_OFF) |LCD_WF_WF31(LCD_OFF),                    \
/* WF35TO32 */  LCD_WF_WF32(LCD_OFF) |LCD_WF_WF33(LCD_OFF)|                    \
                LCD_WF_WF34(LCD_OFF) |LCD_WF_WF35(LCD_OFF),                    \
/* WF39TO36 */  LCD_WF_WF36(LCD_OFF) |LCD_WF_WF37(LCD_OFF)|                    \
                LCD_WF_WF38(LCD_OFF) |LCD_WF_WF39(LCD_OFF),                    \
/* WF43TO40 */  LCD_WF_WF40(LCD_OFF) |LCD_WF_WF41(LCD_OFF)|                    \
                LCD_WF_WF42(LCD_OFF) |LCD_WF_WF43(LCD_OFF),                    \
/* WF47TO44 */  LCD_WF_WF44(LCD_OFF) |LCD_WF_WF45(LCD_OFF)|                    \
                LCD_WF_WF46(LCD_OFF) |LCD_WF_WF47(LCD_OFF),                    \
/* WF51TO48 */  LCD_WF_WF48(LCD_OFF) |LCD_WF_WF49(LCD_OFF)|                    \
                LCD_WF_WF50(LCD_OFF) |LCD_WF_WF51(LCD_OFF),                    \
/* WF55TO52 */  LCD_WF_WF52(LCD_OFF) |LCD_WF_WF53(LCD_OFF)|                    \
                LCD_WF_WF54(LCD_OFF) |LCD_WF_WF55(LCD_OFF),                    \
/* WF59TO56 */  LCD_WF_WF56(LCD_OFF) |LCD_WF_WF57(LCD_OFF)|                    \
                LCD_WF_WF58(LCD_OFF) |LCD_WF_WF59(LCD_OFF),                    \
/* WF63TO60 */  LCD_WF_WF60(LCD_OFF) |LCD_WF_WF61(LCD_OFF)|                    \
                LCD_WF_WF62(LCD_OFF) |LCD_WF_WF63(LCD_OFF),                    \
}

/**************************************************************************/ /*!
  * @brief   LCD segments initialization with GD6363:
  * @details Set all LCD panel segments to ON state. 
  *          - Use "LCD_BP1" for back plane 0, 
  *          - Use "LCD_BP2" for back plane 1, 
  *          - Use "LCD_BP3" for back plane 2, 
  *          - Use "LCD_BP4" for back plane 3, 
  *          - Use "LCD_BP5" for back plane 4, 
  *          - Use "LCD_BP6" for back plane 5, 
  *          - Use "LCD_BP7" for back plane 6, 
  *          - Use "LCD_BP8" for back plane 7, 
  *          - Use "LCD_OFF" for unused segment, 
  *****************************************************************************/
#define LCD_ALL_SEGMENTS_OFF_TWR_KL43                                          \
(tLCD_CP){                                                                     \
/* WF3TO0   */  LCD_WF_WF0 (LCD_OFF) |LCD_WF_WF1 (LCD_OFF)|                    \
                LCD_WF_WF2 (LCD_OFF) |LCD_WF_WF3 (LCD_OFF),                    \
/* WF7TO4   */  LCD_WF_WF4 (LCD_OFF) |LCD_WF_WF5 (LCD_OFF)|                    \
                LCD_WF_WF6 (LCD_OFF) |LCD_WF_WF7 (LCD_OFF),                    \
/* WF11TO8  */  LCD_WF_WF8 (LCD_OFF) |LCD_WF_WF9 (LCD_BP8)|                    \
                LCD_WF_WF10(LCD_BP7) |LCD_WF_WF11(LCD_BP6),                    \
/* WF15TO12 */  LCD_WF_WF12(LCD_BP5) |LCD_WF_WF13(LCD_BP4)|                    \
                LCD_WF_WF14(LCD_BP3) |LCD_WF_WF15(LCD_BP2),                    \
/* WF19TO16 */  LCD_WF_WF16(LCD_BP1) |LCD_WF_WF17(LCD_OFF)|                    \
                LCD_WF_WF18(LCD_OFF) |LCD_WF_WF19(LCD_OFF),                    \
/* WF23TO20 */  LCD_WF_WF20(LCD_OFF) |LCD_WF_WF21(LCD_OFF)|                    \
                LCD_WF_WF22(LCD_OFF) |LCD_WF_WF23(LCD_OFF),                    \
/* WF27TO24 */  LCD_WF_WF24(LCD_OFF) |LCD_WF_WF25(LCD_OFF)|                    \
                LCD_WF_WF26(LCD_OFF) |LCD_WF_WF27(LCD_OFF),                    \
/* WF31TO28 */  LCD_WF_WF28(LCD_OFF) |LCD_WF_WF29(LCD_OFF)|                    \
                LCD_WF_WF30(LCD_OFF) |LCD_WF_WF31(LCD_OFF),                    \
/* WF35TO32 */  LCD_WF_WF32(LCD_OFF) |LCD_WF_WF33(LCD_OFF)|                    \
                LCD_WF_WF34(LCD_OFF) |LCD_WF_WF35(LCD_OFF),                    \
/* WF39TO36 */  LCD_WF_WF36(LCD_OFF) |LCD_WF_WF37(LCD_OFF)|                    \
                LCD_WF_WF38(LCD_OFF) |LCD_WF_WF39(LCD_OFF),                    \
/* WF43TO40 */  LCD_WF_WF40(LCD_OFF) |LCD_WF_WF41(LCD_OFF)|                    \
                LCD_WF_WF42(LCD_OFF) |LCD_WF_WF43(LCD_OFF),                    \
/* WF47TO44 */  LCD_WF_WF44(LCD_OFF) |LCD_WF_WF45(LCD_OFF)|                    \
                LCD_WF_WF46(LCD_OFF) |LCD_WF_WF47(LCD_OFF),                    \
/* WF51TO48 */  LCD_WF_WF48(LCD_OFF) |LCD_WF_WF49(LCD_OFF)|                    \
                LCD_WF_WF50(LCD_OFF) |LCD_WF_WF51(LCD_OFF),                    \
/* WF55TO52 */  LCD_WF_WF52(LCD_OFF) |LCD_WF_WF53(LCD_OFF)|                    \
                LCD_WF_WF54(LCD_OFF) |LCD_WF_WF55(LCD_OFF),                    \
/* WF59TO56 */  LCD_WF_WF56(LCD_OFF) |LCD_WF_WF57(LCD_OFF)|                    \
                LCD_WF_WF58(LCD_OFF) |LCD_WF_WF59(LCD_OFF),                    \
/* WF63TO60 */  LCD_WF_WF60(LCD_OFF) |LCD_WF_WF61(LCD_OFF)|                    \
                LCD_WF_WF62(LCD_OFF) |LCD_WF_WF63(LCD_OFF),                    \
}

/**************************************************************************/ /*!
  * @brief   LCD segments initialization with S401M:
  * @details Set all LCD panel segments to ON state. 
  *          - Use "LCD_BP1" for back plane 0, 
  *          - Use "LCD_BP2" for back plane 1, 
  *          - Use "LCD_BP3" for back plane 2, 
  *          - Use "LCD_BP4" for back plane 3, 
  *          - Use "LCD_OFF" for unused segment, 
  *          - Use "LCD_ON1" for segment ON with 1 back plane, 
  *          - Use "LCD_ON2" for segment ON with 2 back planes, 
  *          - Use "LCD_ON3" for segment ON with 3 back planes,  
  *          - Use "LCD_ON4" for segment ON with 4 back planes, 
  *          - Use "LCD_ON5" for segment ON with 5 back planes, 
  *          - Use "LCD_ON6" for segment ON with 6 back planes,  
  *          - Use "LCD_ON7" for segment ON with 7 back planes,  
  *          - Use "LCD_ON8" for segment ON with 8 back planes,  
  *****************************************************************************/
#define LCD_ALL_SEGMENTS_OFF_FRDM_KL43                                         \
(tLCD_CP){                                                                     \
/* WF3TO0   */  LCD_WF_WF0 (LCD_OFF) |LCD_WF_WF1 (LCD_OFF)|                    \
                LCD_WF_WF2 (LCD_OFF) |LCD_WF_WF3 (LCD_OFF),                    \
/* WF7TO4   */  LCD_WF_WF4 (LCD_OFF) |LCD_WF_WF5 (LCD_OFF)|                    \
                LCD_WF_WF6 (LCD_OFF) |LCD_WF_WF7 (LCD_OFF),                    \
/* WF11TO8  */  LCD_WF_WF8 (LCD_OFF) |LCD_WF_WF9 (LCD_OFF)|                    \
                LCD_WF_WF10(LCD_OFF) |LCD_WF_WF11(LCD_OFF),                    \
/* WF15TO12 */  LCD_WF_WF12(LCD_OFF) |LCD_WF_WF13(LCD_OFF)|                    \
                LCD_WF_WF14(LCD_OFF) |LCD_WF_WF15(LCD_OFF),                    \
/* WF19TO16 */  LCD_WF_WF16(LCD_OFF) |LCD_WF_WF17(LCD_OFF)|                    \
                LCD_WF_WF18(LCD_BP4) |LCD_WF_WF19(LCD_BP3),                    \
/* WF23TO20 */  LCD_WF_WF20(LCD_OFF) |LCD_WF_WF21(LCD_OFF)|                    \
                LCD_WF_WF22(LCD_OFF) |LCD_WF_WF23(LCD_OFF),                    \
/* WF27TO24 */  LCD_WF_WF24(LCD_OFF) |LCD_WF_WF25(LCD_OFF)|                    \
                LCD_WF_WF26(LCD_OFF) |LCD_WF_WF27(LCD_OFF),                    \
/* WF31TO28 */  LCD_WF_WF28(LCD_OFF) |LCD_WF_WF29(LCD_OFF)|                    \
                LCD_WF_WF30(LCD_OFF) |LCD_WF_WF31(LCD_OFF),                    \
/* WF35TO32 */  LCD_WF_WF32(LCD_OFF) |LCD_WF_WF33(LCD_OFF)|                    \
                LCD_WF_WF34(LCD_OFF) |LCD_WF_WF35(LCD_OFF),                    \
/* WF39TO36 */  LCD_WF_WF36(LCD_OFF) |LCD_WF_WF37(LCD_OFF)|                    \
                LCD_WF_WF38(LCD_OFF) |LCD_WF_WF39(LCD_OFF),                    \
/* WF43TO40 */  LCD_WF_WF40(LCD_BP1) |LCD_WF_WF41(LCD_OFF)|                    \
                LCD_WF_WF42(LCD_OFF) |LCD_WF_WF43(LCD_OFF),                    \
/* WF47TO44 */  LCD_WF_WF44(LCD_OFF) |LCD_WF_WF45(LCD_OFF)|                    \
                LCD_WF_WF46(LCD_OFF) |LCD_WF_WF47(LCD_OFF),                    \
/* WF51TO48 */  LCD_WF_WF48(LCD_OFF) |LCD_WF_WF49(LCD_OFF)|                    \
                LCD_WF_WF50(LCD_OFF) |LCD_WF_WF51(LCD_OFF),                    \
/* WF55TO52 */  LCD_WF_WF52(LCD_BP2) |LCD_WF_WF53(LCD_OFF)|                    \
                LCD_WF_WF54(LCD_OFF) |LCD_WF_WF55(LCD_OFF),                    \
/* WF59TO56 */  LCD_WF_WF56(LCD_OFF) |LCD_WF_WF57(LCD_OFF)|                    \
                LCD_WF_WF58(LCD_OFF) |LCD_WF_WF59(LCD_OFF),                    \
/* WF63TO60 */  LCD_WF_WF60(LCD_OFF) |LCD_WF_WF61(LCD_OFF)|                    \
                LCD_WF_WF62(LCD_OFF) |LCD_WF_WF63(LCD_OFF),                    \
}

/*! @} End of lcd_config                                                      */

/******************************************************************************
* LCD callback registered by LCD_InstallCallback() function
*
*//*! @addtogroup lcd_callback
* @{
*******************************************************************************/
/*! @brief LCD_CALLBACK type declaration                                      */
typedef enum 
{ 
  LCD_LCDIF_CALLBACK=1,   ///< LCD frame-frequency interrupt
  LCD_FDCF_CALLBACK =2,   ///< LCD fault detection complete interrupt
} LCD_CALLBACK_TYPE;

/*! @brief PIT_CALLBACK function declaration                                  */
typedef void (*LCD_CALLBACK)(LCD_CALLBACK_TYPE type);
/*! @} End of lcd_callback                                                    */

/******************************************************************************
* LCD function and macro definitions
*
*//*! @addtogroup lcd_macro
* @{
*******************************************************************************/

/***************************************************************************//*!
 * @brief   Function installs callback function for vector 31.
 * @details This function is used to install callback function for interrupt 
 *          vector 31.
 * @param   ip        Interrupt priority 0..3
 * @param   callback  Pointer to @ref LCD_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 * @warning LCDIF and FDCF interrupt sources are ORed into single interrupt vector.
 ******************************************************************************/
#define LCD_InstallCallback(ip,callback)

/*! @} End of lcd_macro                                                       */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/    
extern void LCD_InstallCallbackLCD (uint8 ip, LCD_CALLBACK pCallback);
extern void LCD_Init (tLCD lcd, tLCD_FP lcd_fp, tLCD_BP lcd_bp, tLCD_CP lcd_cp);
extern void LCD_GOTO (uint8 pos);
extern void LCD_Write_Char (uint8 c);
extern void LCD_Delete_Char (uint8 pos);
extern void LCD_Write_Segments (tLCD_CP lcd_cp);


#endif /* __LCD_H */

