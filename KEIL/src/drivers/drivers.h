/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      drivers.h
 * @version   1.0.3.0
 * @date      Apr-24-2013
 * @brief     Header files with all driver's header files.
 *
 * Revision History:
 *  1.	07/01/2013   B34185   Initially written
 ******************************************************************************/
#ifndef __DRIVERS_H
#define __DRIVERS_H

#include "adc.h"
#include "bme.h"
#include "cmp.h"
#include "dac.h"
#include "dma.h"
#include "ftfa.h"
#include "gpio.h"
#include "i2c.h"
#include "llwu.h"
#include "lptmr.h"
#include "mcm.h"
#include "osc.h"
#include "pit.h"
#include "pmc.h"
#include "rcm.h"
#include "rtc.h"
#include "sim.h"
#include "lcd.h"
#include "sai.h"
#include "smc.h"
#include "spi.h"
#include "tpm.h"
#include "uart.h"
#if (defined (MCU_MKL46Z256))
  #include "mcg.h"
  #include "tsi.h"
#elif (defined (MCU_MKL43Z256))
  #include "flexio.h"
  #include "flexio_uart/flexio_uart.h"
  #include "flexio_i2c/flexio_i2c.h"
  #include "flexio_i2s/flexio_i2s.h"
  #include "flexio_spi_master/flexio_spi_master.h"
  #include "flexio_spi_slave/flexio_spi_slave.h"
  #include "lpuart.h"
  #include "mcg_lite.h"
  #include "vref.h"
#endif

#endif /* __DRIVERS_H */
