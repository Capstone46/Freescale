/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      arch_delay.h
 * @version   1.0.1.0
 * @date      Jun-20-2013
 * @brief     Header file.
 *
 * Revision History:
 *  1.	01/01/2010   R55013   Initially written
 *  2.	16/01/2013   B34185   Ported to Kinetis L
 ******************************************************************************/
#ifndef __ARCH_DELAY_H
#define __ARCH_DELAY_H

/******************************************************************************
 * Arch_delay fnction prototype                                               *
 ******************************************************************************/
extern void arch_delay(long ticks);

#define TIME2TICKS_MS(clock, time) (((time) * (clock))/ 1000)
#define TIME2TICKS_US(clock, time) (((time) * (clock))/ 1000000)

#endif /* __ARCH_DELAY_H */
