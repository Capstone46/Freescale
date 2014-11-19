
/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      LCDHDW.h
 * @author    R55013
 * @version   1.0.1.0
 * @date      Dec-6-2010
 * @brief     LCD driver configuration file for LCD type S401M..
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
    #define   Char1x     CharacterPlace(17)     
    #define   Char1y     CharacterPlace(37)     
    #define   Char2x     CharacterPlace(8)      
    #define   Char2y     CharacterPlace(7)      
    #define   Char3x     CharacterPlace(38)     
    #define   Char3y     CharacterPlace(53)     
    #define   Char4x     CharacterPlace(11)     
    #define   Char4y     CharacterPlace(10)     


/* Special symbols ON */
// 1st char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1D_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1D_ON    SymbolON(37,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1E_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1E_ON    SymbolON(37,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1F_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1F_ON    SymbolON(37,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1G_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1G_ON    SymbolON(37,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_DP1_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_DP1_ON    SymbolON(17,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1C_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1C_ON    SymbolON(17,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1B_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1B_ON    SymbolON(17,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1A_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1A_ON    SymbolON(17,3)

// 2nd char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2D_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2D_ON    SymbolON(7,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2E_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2E_ON    SymbolON(7,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2F_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2F_ON    SymbolON(7,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2G_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2G_ON    SymbolON(7,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_DP2_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_DP2_ON    SymbolON(8,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2C_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2C_ON    SymbolON(8,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2B_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2B_ON    SymbolON(8,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2A_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2A_ON    SymbolON(8,3)

// 3rd char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3D_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3D_ON    SymbolON(53,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3E_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3E_ON    SymbolON(53,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3F_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3F_ON    SymbolON(53,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3G_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3G_ON    SymbolON(53,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_DP3_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_DP3_ON    SymbolON(38,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3C_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3C_ON    SymbolON(38,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3B_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3B_ON    SymbolON(38,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3A_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3A_ON    SymbolON(38,3)

// 4th char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11D_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4D_ON    SymbolON(10,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11E_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4E_ON    SymbolON(10,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11F_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4F_ON    SymbolON(10,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11G_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4G_ON    SymbolON(10,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_COL_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_COL_ON    SymbolON(11,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_12C_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4C_ON    SymbolON(11,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_12B_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4B_ON    SymbolON(11,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_12A_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4A_ON    SymbolON(11,3)




/* Special symbols OFF */
// 1st char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1D_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1D_OFF    SymbolOFF(37,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1E_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1E_OFF    SymbolOFF(37,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1F_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1F_OFF    SymbolOFF(37,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1G_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1G_OFF    SymbolOFF(37,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_DP1_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_DP1_OFF    SymbolOFF(17,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1C_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1C_OFF    SymbolOFF(17,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1B_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1B_OFF    SymbolOFF(17,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_1A_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_1A_OFF    SymbolOFF(17,3)

// 2nd char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2D_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2D_OFF    SymbolOFF(7,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2E_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2E_OFF    SymbolOFF(7,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2F_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2F_OFF    SymbolOFF(7,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2G_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2G_OFF    SymbolOFF(7,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_DP2_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_DP2_OFF    SymbolOFF(8,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2C_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2C_OFF    SymbolOFF(8,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2B_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2B_OFF    SymbolOFF(8,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_2A_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_2A_OFF    SymbolOFF(8,3)

// 3rd char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3D_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3D_OFF    SymbolOFF(53,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3E_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3E_OFF    SymbolOFF(53,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3F_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3F_OFF    SymbolOFF(53,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3G_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3G_OFF    SymbolOFF(53,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_DP3_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_DP3_OFF    SymbolOFF(38,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3C_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3C_OFF    SymbolOFF(38,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3B_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3B_OFF    SymbolOFF(38,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_3A_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_3A_OFF    SymbolOFF(38,3)

// 4th char
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11D_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4D_OFF    SymbolOFF(10,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11E_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4E_OFF    SymbolOFF(10,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11F_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4F_OFF    SymbolOFF(10,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_11G_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4G_OFF    SymbolOFF(10,3)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_COL_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_COL_OFF    SymbolOFF(11,0)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_12C_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4C_OFF    SymbolOFF(11,1)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_12B_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4B_OFF    SymbolOFF(11,2)

/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_12A_OFF segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_4A_OFF    SymbolOFF(11,3)


/* Special symbols TOGGLE */
/***************************************************************************//*!
* @brief   Macro displays _LCD_CHAR_V_COL_ON segments.
* @note    Implemented as inlined macro.
******************************************************************************/
#define _LCD_CHAR_V_COL_TGL    SymbolTGL(11,0)

  
/* Segments ON  */
#define Segment0_ON             {SegmentsON(37,0x0f);   SegmentsON(17,0x0e);}
#define Segment1_ON             {SegmentsON(7,0x0f);    SegmentsON(8,0x0e);}
#define Segment2_ON             {SegmentsON(53,0x0f);   SegmentsON(38,0x0e);}
#define Segment3_ON             {SegmentsON(10,0x0f);   SegmentsON(11,0x0e);}


/* Segments OFF  */
#define Segment0_OFF            {SegmentsOFF(37,0x0f);  SegmentsOFF(17,0x0e);}
#define Segment1_OFF            {SegmentsOFF(7,0x0f);   SegmentsOFF(8,0x0e);}
#define Segment2_OFF            {SegmentsOFF(53,0x0f);  SegmentsOFF(38,0x0e);}
#define Segment3_OFF            {SegmentsOFF(10,0x0f);  SegmentsOFF(11,0x0e);}


/*Map segment to COM mask - LINE0*/
#define  L0SEGA             0x08
#define  L0SEGB             0x04
#define  L0SEGC             0x02
#define  L0SEGD             0x01
#define  L0SEGE             0x02
#define  L0SEGF             0x08
#define  L0SEGG             0x04


#endif /* __LCDHWD_H */ 