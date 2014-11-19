
/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      LCDHDW.h
 * @author    B34185
 * @version   1.0.1.0
 * @date      Dec-6-2010
 * @brief     LCD driver configuration file for LCD type GD6363 with TWR-KL43.
 ******************************************************************************/
#ifndef __LCDHWD_H
    #define __LCDHWD_H

    #define DIM(x)                (sizeof(x)/sizeof(x[0]))

    #define _LCD_CHARNUM          (4)                   // number of LCD segment
    #define _LCDTYPE              (2)                   // 2 byte to complete one character
    #define  CharacterPlace(LCDn) *((unsigned char *)&LCD_WF3TO0 + LCDn)

    #define SymbolON(LCDn, mask)                                              \
    {                                                                         \
      *((unsigned char *)&LCD_WF3TO0 + LCDn) |= (1<<(mask));                  \
    }
    
    #define SymbolOFF(LCDn, mask)                                             \
    {                                                                         \
      *((unsigned char *)&LCD_WF3TO0 + LCDn) &= ~(1<<(mask));                 \
    }

    #define SymbolTGL(LCDn, mask)                                             \
    {                                                                         \
      *((unsigned char *)&LCD_WF3TO0 + LCDn) ^= (1<<(mask));                  \
    }
    
    #define SegmentsON(LCDn, mask)                                            \
    {                                                                         \
      *((unsigned char *)&LCD_WF3TO0 + LCDn) |= (mask);                       \
    }

    #define SegmentsOFF(LCDn, mask)                                           \
    {                                                                         \
      *((unsigned char *)&LCD_WF3TO0 + LCDn) &= ~(mask);                      \
    }
    
    /* Indicate how character is connected to LCDn          */
    #define   Char1x     CharacterPlace(0)      ///> T2/T3/AM/PM - LCD_P0
    #define   Char1y     CharacterPlace(0)      ///> T2/T3/AM/PM - LCD_P0
    #define   Char2x     CharacterPlace(22)     ///> 1A/1B/1C/1D - LCD_P22
    #define   Char2y     CharacterPlace(24)     ///> 1F/1G/1E/P1 - LCD_P24
    #define   Char3x     CharacterPlace(3)      ///> 2A/2B/2C/2D - LCD_P3      
    #define   Char3y     CharacterPlace(20)     ///> 2F/2G/2E/COL - LCD_P20       
    #define   Char4x     CharacterPlace(23)     ///> 3A/3B/3C/3D - LCD_P23
    #define   Char4y     CharacterPlace(1)      ///> 3F/3G/3E/T1 - LCD_P1      
        
/* Special symbols ON */
// 1st char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_T2_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_T2_ON    SymbolON(0,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_T3_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_T3_ON    SymbolON(0,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_AM_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_AM_ON    SymbolON(0,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_PM_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_PM_ON    SymbolON(0,3)

// 2nd char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1A_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1A_ON    SymbolON(22,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1B_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1B_ON    SymbolON(22,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1C_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1C_ON    SymbolON(22,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1D_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1D_ON    SymbolON(22,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1F_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1F_ON    SymbolON(24,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1G_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1G_ON    SymbolON(24,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2E_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1E_ON    SymbolON(24,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_P1_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_P1_ON    SymbolON(24,3)

// 3rd char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2A_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2A_ON    SymbolON(3,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2B_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2B_ON    SymbolON(3,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2C_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2C_ON    SymbolON(3,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2D_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2D_ON    SymbolON(3,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2F_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2F_ON    SymbolON(20,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2G_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2G_ON    SymbolON(20,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2E_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2E_ON    SymbolON(20,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_COL_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_COL_ON    SymbolON(20,3)

// 4th char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3A_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3A_ON    SymbolON(23,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3B_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3B_ON    SymbolON(23,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3C_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3C_ON    SymbolON(23,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3D_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3D_ON    SymbolON(23,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3F_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3F_ON    SymbolON(1,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3G_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3G_ON    SymbolON(1,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3E_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3E_ON    SymbolON(1,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_T1_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_T1_ON    SymbolON(1,3)



/* Special symbols OFF */
// 1st char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_T2_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_T2_OFF    SymbolOFF(0,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_T3_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_T3_OFF    SymbolOFF(0,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_AM_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_AM_OFF    SymbolOFF(0,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_PM_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_PM_OFF    SymbolOFF(0,3)

// 2nd char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1A_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1A_OFF    SymbolOFF(22,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1B_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1B_OFF    SymbolOFF(22,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1C_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1C_OFF    SymbolOFF(22,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1D_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1D_OFF    SymbolOFF(22,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1F_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1F_OFF    SymbolOFF(24,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1G_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1G_OFF    SymbolOFF(24,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2E_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1E_OFF    SymbolOFF(24,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_P1_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_P1_OFF    SymbolOFF(24,3)

// 3rd char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2A_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2A_OFF    SymbolOFF(3,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2B_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2B_OFF    SymbolOFF(3,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2C_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2C_OFF    SymbolOFF(3,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2D_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2D_OFF    SymbolOFF(3,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2F_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2F_OFF    SymbolOFF(20,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2G_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2G_OFF    SymbolOFF(20,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2E_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2E_OFF    SymbolOFF(20,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_COL_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_COL_OFF    SymbolOFF(20,3)

// 4th char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3A_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3A_OFF    SymbolOFF(23,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3B_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3B_OFF    SymbolOFF(23,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3C_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3C_OFF    SymbolOFF(23,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3D_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3D_OFF    SymbolOFF(23,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3F_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3F_OFF    SymbolOFF(1,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3G_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3G_OFF    SymbolOFF(1,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3E_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3E_OFF    SymbolOFF(1,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_T1_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_T1_OFF    SymbolOFF(1,3)



/* Special symbols TOGGLE */
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_COL_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_COL_TGL    SymbolTGL(20,3)

/* Segments ON  */
#define Segment0_ON             {SegmentsON(1,0x08); SegmentsON(1,0x08);}
#define Segment1_ON             {SegmentsON(22,0x0f);SegmentsON(24,0x07);}
#define Segment2_ON             {SegmentsON(3,0x0f); SegmentsON(20,0x07);}
#define Segment3_ON             {SegmentsON(23,0x0f);SegmentsON(1,0x07);}


/* Segments OFF  */
#define Segment0_OFF            {SegmentsOFF(1,0x08); SegmentsOFF(1,0x08);}
#define Segment1_OFF            {SegmentsOFF(22,0x0f);SegmentsOFF(24,0x07);}
#define Segment2_OFF            {SegmentsOFF(3,0x0f); SegmentsOFF(20,0x07);}
#define Segment3_OFF            {SegmentsOFF(23,0x0f);SegmentsOFF(1,0x07);}


/*Map segment to COM mask - LINE0*/
#define  L0SEGA             0x01
#define  L0SEGB             0x02
#define  L0SEGC             0x04
#define  L0SEGD             0x08
#define  L0SEGE             0x04
#define  L0SEGF             0x01
#define  L0SEGG             0x02

#endif /* __LCDHWD_H */ 
