/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file mouse_button.h
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief The file contains Macro's and functions needed by the Mouse
 *        Application
 *
 *****************************************************************************/


#ifndef _USB_MOUSE_H
#define _USB_MOUSE_H

#include "types.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define  CONTROLLER_ID     (0)       /* ID to identify USB CONTROLLER */

/* #define UP_LEFT   This macro enables up and left mouse movement via PTG2-3*/
#ifdef UP_LEFT
#define SHIFT_VAL          (0xF8)    /* send -8 for up and left movement */
#else
#define SHIFT_VAL          (0x08)    /* send +8 for down and right movement */
#endif

#define  MOUSE_BUFF_SIZE   (4)   /* report buffer size */
#define  REQ_DATA_SIZE     (1)

#define  KBI_STAT_MASK     (0x0F)
#define  LEFT_CLICK        (0x01) /* Left click */
#define  RIGHT_CLICK       (0x02) /* Right click */
#define  MOVE_LEFT_RIGHT   (0x04) /* Left-Right movement*/
#define  MOVE_UP_DOWN      (0x08) /* Up-Down movement*/

/*****************************************************************************
 * Global variables
 *****************************************************************************/


/*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern void USB_Mouse_Init  (void);
extern void USB_Mouse_Update(uint_8 left_bt, uint_8 rigth_bt, int_8  x, int_8  y);
#endif
