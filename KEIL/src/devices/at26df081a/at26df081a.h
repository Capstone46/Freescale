/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      at26df081a.h
 * @author    B34196
 * @version   0.0.0.0
 * @date      Mar-13-2014
 * @brief     8-megabit SPI Serial Flash Memory driver header file.
 ******************************************************************************/
#ifndef __AT26DF081A_H
#define __AT26DF081A_H

#include "drivers.h"

extern  uint8   at26df081a_enabled;
extern  uint8   *spi_buff_rx_pointer;
extern  uint8   *spi_buff_tx_pointer;
extern  uint8   data_exchange_completed;
extern  uint16  spi_tx_cnt, spi_rx_cnt, spi_cnt, spi_cnt2; /* SPI counters */

/* SPI signal defines                                                         */
#define SPI0_SS                         PIN_0            /* PTD0 */
#define SPI0_SCK                        PIN_1            /* PTD1 */
#define SPI0_MOSI                       PIN_2            /* PTD2 */
#define SPI0_MISO                       PIN_3            /* PTD3 */

//==============================================================================
// SPI FLASH Command definitions 
//==============================================================================
#define READ_ARRAY                      0x0B   // Read data from array 
#define READ_ARRAY_LOW_FREQ             0x03   // Read data from array at low frequency

#define BLOCK_ERASE_4K                  0x20
#define BLOCK_ERASE_32K                 0x52
#define BLOCK_ERASE_64K                 0xD8
#define CHIP_ERASE                      0x60    //also 0xC7
#define BYTE_PAGE_PROGRAM               0x02    //also 0xAF
#define SEQUENTIAL_PROG_MODE            0xAD

#define WRITE_ENABLE                    0x06
#define WRITE_DISABLE                   0x04
#define PROTECT_SECTOR                  0x36
#define UNPROTECT_SECTOR                0x39

#define READ_PROTECT_SECTOR_REGS        0x3C

#define READ_STATUS_REGISTER            0x05
#define WRITE_STATUS_REGISTER           0x01

#define READ_MFG_DEV_ID                 0x9F
#define DEEP_POWER_DOWN                 0xB9
#define RESUME_DEEP_POWER_DOWN          0xAB

//==============================================================================
// SPI FLASH Status Register 
//==============================================================================

#define SR_SPRL_MASK                    (1<<7)
#define SR_SPM_MASK                     (1<<6)
#define SR_EPE_MASK                     (1<<5)
#define SR_WPP_MASK                     (1<<4)
#define SR_SWP_MASK                     (3<<2)
#define SR_WEL_MASK                     (1<<1)
#define SR_BUSY_MASK                    (1<<0)


//==============================================================================
// Prototypes
//==============================================================================

void at26df081a__SPI0_Write_Enable (void);
void at26df081a__SPI0_Write_Disable (void);
void at26df081a__SPI0_Protect_Sector (uint32 address);
void at26df081a__SPI0_Unprotect_Sector (uint32 address);
void at26df081a__SPI0_Block_Erase_4k (uint32 address);
void at26df081a__SPI0_Block_Erase_32k (uint32 address);
void at26df081a__SPI0_Block_Erase_64k (uint32 address);
void at26df081a__SPI0_Read_Array (uint32 address, uint8 *buffout, uint16 rxcnt);
uint8 at26df081a__SPI0_Write_Array (uint32 address, uint8 *buff, uint8 txcnt);
uint8 at26df081a__SPI0_Read_Status_Register (void);
uint8 at26df081a__SPI0_Read_Busy_Flag (void);
uint8 at26df081a__SPI0_Read_Write_Enable_Flag (void);


void at26df081a__SPI0_Read_Manufacturer_and_Device_ID (uint8 *buffout);


extern void SPI0_CommByte_INT(uint8 *txdata,uint16 txcnt,uint8 *rxdata, uint16 rxcnt);
extern void (*SPI0_CommByte_Function)(uint8 *txdata,uint16 txcnt,uint8 *rxdata, uint16 rxcnt);

#endif /* __AT26DF081A_H */

