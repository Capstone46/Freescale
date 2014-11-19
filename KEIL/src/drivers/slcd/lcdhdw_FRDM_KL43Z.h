
/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      LCDHDW.h
 * @author    R55013
 * @version   1.0.1.0
 * @date      Dec-6-2010
 * @brief     LCD driver configuration file for LCD type S401M implemented in FRDM-KL43 board.
 ******************************************************************************/
#ifndef __LCDHWD_H
    #define __LCDHWD_H

    #define DIM(x)                (sizeof(x)/sizeof(x[0]))

    #define _LCD_CHARNUM          (4)                   // number of LCD segment
    #define _LCDTYPE              (2)                   // 1 byte to complete one character
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
    #define   Char1x     CharacterPlace(24)     
    #define   Char1y     CharacterPlace(20)     
    #define   Char2x     CharacterPlace(27)      
    #define   Char2y     CharacterPlace(26)      
    #define   Char3x     CharacterPlace(42)     
    #define   Char3y     CharacterPlace(40)     
    #define   Char4x     CharacterPlace(44)     
    #define   Char4y     CharacterPlace(43)     


/* Special symbols ON */
// 1st char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1D_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1D_ON    SymbolON(20,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1E_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1E_ON    SymbolON(20,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1F_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1F_ON    SymbolON(20,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1G_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1G_ON    SymbolON(20,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_DP1_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_DP1_ON    SymbolON(24,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1C_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1C_ON    SymbolON(24,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1B_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1B_ON    SymbolON(24,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1A_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1A_ON    SymbolON(24,3)

// 2nd char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2D_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2D_ON    SymbolON(26,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2E_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2E_ON    SymbolON(26,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2F_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2F_ON    SymbolON(26,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2G_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2G_ON    SymbolON(26,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_DP2_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_DP2_ON    SymbolON(27,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2C_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2C_ON    SymbolON(27,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2B_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2B_ON    SymbolON(27,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2A_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2A_ON    SymbolON(27,3)

// 3rd char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3D_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3D_ON    SymbolON(40,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3E_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3E_ON    SymbolON(40,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3F_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3F_ON    SymbolON(40,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3G_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3G_ON    SymbolON(40,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_DP3_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_DP3_ON    SymbolON(42,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3C_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3C_ON    SymbolON(42,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3B_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3B_ON    SymbolON(42,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3A_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3A_ON    SymbolON(42,3)

// 4th char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11D_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4D_ON    SymbolON(43,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11E_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4E_ON    SymbolON(43,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11F_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4F_ON    SymbolON(43,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11G_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4G_ON    SymbolON(43,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_COL_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_COL_ON    SymbolON(44,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_12C_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4C_ON    SymbolON(44,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_12B_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4B_ON    SymbolON(44,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_12A_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4A_ON    SymbolON(44,3)


/* Special symbols OFF */
// 1st char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1D_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1D_OFF    SymbolOFF(20,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1E_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1E_OFF    SymbolOFF(20,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1F_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1F_OFF    SymbolOFF(20,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1G_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1G_OFF    SymbolOFF(20,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_DP1_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_DP1_OFF    SymbolOFF(24,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1C_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1C_OFF    SymbolOFF(24,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1B_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1B_OFF    SymbolOFF(24,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1A_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1A_OFF    SymbolOFF(24,3)

// 2nd char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2D_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2D_OFF    SymbolOFF(26,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2E_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2E_OFF    SymbolOFF(26,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2F_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2F_OFF    SymbolOFF(26,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2G_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2G_OFF    SymbolOFF(26,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_DP2_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_DP2_OFF    SymbolOFF(27,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2C_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2C_OFF    SymbolOFF(27,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2B_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2B_OFF    SymbolOFF(27,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2A_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2A_OFF    SymbolOFF(27,3)

// 3rd char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3D_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3D_OFF    SymbolOFF(40,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3E_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3E_OFF    SymbolOFF(40,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3F_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3F_OFF    SymbolOFF(40,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3G_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3G_OFF    SymbolOFF(40,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_DP3_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_DP3_OFF    SymbolOFF(42,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3C_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3C_OFF    SymbolOFF(42,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3B_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3B_OFF    SymbolOFF(42,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3A_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3A_OFF    SymbolOFF(42,3)

// 4th char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11D_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4D_OFF    SymbolOFF(43,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11E_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4E_OFF    SymbolOFF(43,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11F_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4F_OFF    SymbolOFF(43,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11G_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4G_OFF    SymbolOFF(43,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_COL_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_COL_OFF    SymbolOFF(44,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_12C_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4C_OFF    SymbolOFF(44,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_12B_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4B_OFF    SymbolOFF(44,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_12A_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4A_OFF    SymbolOFF(44,3)


/* Special symbols TOGGLE */
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_COL_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_COL_TGL    SymbolTGL(44,0)

  
/* Segments ON  */
#define Segment0_ON             {SegmentsON(20,0x0f);   SegmentsON(24,0x0e);}
#define Segment1_ON             {SegmentsON(26,0x0f);   SegmentsON(27,0x0e);}
#define Segment2_ON             {SegmentsON(40,0x0f);   SegmentsON(42,0x0e);}
#define Segment3_ON             {SegmentsON(43,0x0f);   SegmentsON(44,0x0e);}


/* Segments OFF  */
#define Segment0_OFF            {SegmentsOFF(20,0x0f);  SegmentsOFF(24,0x0e);}
#define Segment1_OFF            {SegmentsOFF(26,0x0f);  SegmentsOFF(27,0x0e);}
#define Segment2_OFF            {SegmentsOFF(40,0x0f);  SegmentsOFF(42,0x0e);}
#define Segment3_OFF            {SegmentsOFF(43,0x0f);  SegmentsOFF(44,0x0e);}


/*Map segment to COM mask - LINE0*/
#define  L0SEGA             0x08
#define  L0SEGB             0x04
#define  L0SEGC             0x02
#define  L0SEGD             0x01
#define  L0SEGE             0x02
#define  L0SEGF             0x08
#define  L0SEGG             0x04


#endif /* __LCDHWD_H */

