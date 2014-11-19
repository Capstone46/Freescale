/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      at26df081a.c
 * @author    created by B34196
 * @version   0.0.0.0
 * @date      Mar-13-2014
 * @brief     8-megabit SPI Serial Flash Memory driver implementation.
 * @par       Driver example:
 * @include   	
 ******************************************************************************/
#include "common.h"
#include "spi.h"
#include "at26df081a.h"

uint8 at26df081a_enabled = FALSE;
uint8 data_exchange_completed = TRUE;
uint16 spi_tx_cnt, spi_rx_cnt, spi_cnt, spi_cnt2; /* SPI counters */


#if SPI_MODE_SELECTION == SPI_POLLING
void (*SPI0_CommByte_Function)(uint8 *txdata,uint16 txcnt,uint8 *rxdata, uint16 rxcnt)= &SPI0_CommByte;
#elif SPI_MODE_SELECTION == SPI_INTERRUPT
  void (*SPI0_CommByte_Function)(uint8 *txdata,uint16 txcnt,uint8 *rxdata, uint16 rxcnt)= &SPI0_CommByte_INT;
#endif
  
  
/**************************************************************************//*!
* @brief    Write Enable command over SPI0 
******************************************************************************/

void at26df081a__SPI0_Write_Enable (void)

{
  uint8 buffin;
  
  if (at26df081a_enabled){
  buffin= WRITE_ENABLE;
  
  
  SPI0_CommByte_Function ( &buffin ,1 ,NULL ,0 );
  }
  asm("nop");
}
  
/**************************************************************************//*!
* @brief    Write Disable command over SPI0 
******************************************************************************/

void at26df081a__SPI0_Write_Disable (void)

{
  uint8 buffin;
  
  if (at26df081a_enabled){
  buffin= WRITE_DISABLE;
  
  
  SPI0_CommByte_Function ( &buffin ,1 ,NULL ,0 );
  }
  asm("nop");
}  

/**************************************************************************//*!
* @brief    Protect Sector command over SPI0 
******************************************************************************/

void at26df081a__SPI0_Protect_Sector (uint32 address)

{
  uint8 buffin[4];
  at26df081a__SPI0_Write_Enable ();
  
  if (at26df081a_enabled & at26df081a__SPI0_Read_Write_Enable_Flag ()){
  
   
  buffin[0]= PROTECT_SECTOR;
  buffin[1]=((uint8)((address>>16)&0xFF));
  buffin[2]=((uint8)((address>>8)&0xFF));
  buffin[3]=((uint8)((address)&0xFF));
  
  
  SPI0_CommByte_Function ( buffin ,4 ,NULL ,0 );
  }
  asm("nop");
}  

/**************************************************************************//*!
* @brief    Unprotect Sector command over SPI0 
******************************************************************************/

void at26df081a__SPI0_Unprotect_Sector (uint32 address)

{
  uint8 buffin[4];
  at26df081a__SPI0_Write_Enable ();
  if (at26df081a_enabled & at26df081a__SPI0_Read_Write_Enable_Flag ())
  {
 
  buffin[0]= UNPROTECT_SECTOR;
  buffin[1]=((uint8)((address>>16)&0xFF));
  buffin[2]=((uint8)((address>>8)&0xFF));
  buffin[3]=((uint8)((address)&0xFF));
   
  SPI0_CommByte_Function ( buffin ,4 ,NULL ,0 );
  }
  asm("nop");
}  

/**************************************************************************//*!
* @brief    Block Erase 4kB command over SPI0 
******************************************************************************/

void at26df081a__SPI0_Block_Erase_4k (uint32 address)

{
  uint8 buffin[4];
  at26df081a__SPI0_Write_Enable ();
  
  if (at26df081a_enabled & at26df081a__SPI0_Read_Write_Enable_Flag ()){
    
  buffin[0]= BLOCK_ERASE_4K;
  buffin[1]=((uint8)((address>>16)&0xFF));
  buffin[2]=((uint8)((address>>8)&0xFF));
  buffin[3]=((uint8)((address)&0xFF));
  
  SPI0_CommByte_Function ( buffin ,4 ,NULL ,0 );
  }
  asm("nop");
}  

/**************************************************************************//*!
* @brief    Block Erase 32kB command over SPI0 
******************************************************************************/

void at26df081a__SPI0_Block_Erase_32k (uint32 address)

{
  uint8 buffin[4];
  at26df081a__SPI0_Write_Enable ();
  
  if (at26df081a_enabled & at26df081a__SPI0_Read_Write_Enable_Flag ()){
    
  buffin[0]= BLOCK_ERASE_32K;
  buffin[1]=((uint8)((address>>16)&0xFF));
  buffin[2]=((uint8)((address>>8)&0xFF));
  buffin[3]=((uint8)((address)&0xFF));
  
  SPI0_CommByte_Function ( buffin ,4 ,NULL ,0 );
  }
  asm("nop");
}  

/**************************************************************************//*!
* @brief    Block Erase 64kB command over SPI0 
******************************************************************************/

void at26df081a__SPI0_Block_Erase_64k (uint32 address)

{
  uint8 buffin[4];
  at26df081a__SPI0_Write_Enable ();
  
  if (at26df081a_enabled & at26df081a__SPI0_Read_Write_Enable_Flag ()){
    
  buffin[0]= BLOCK_ERASE_64K;
  buffin[1]=((uint8)((address>>16)&0xFF));
  buffin[2]=((uint8)((address>>8)&0xFF));
  buffin[3]=((uint8)((address)&0xFF));
  
  SPI0_CommByte_Function ( buffin ,4 ,NULL ,0 );
  }
  asm("nop");
}  

/**************************************************************************//*!
* @brief    Byte / Page Program over SPI0 (up to 256bytes)
******************************************************************************/

uint8 at26df081a__SPI0_Write_Array (uint32 address, uint8 *buff, uint8 txcnt)

{
  static uint8 buffin[(256+4)]; //up to 256bytes of data+command+address
  uint8 index;
  uint8 remainingBytes;
  if (at26df081a__SPI0_Read_Busy_Flag ()) return FALSE;//check if busy
  at26df081a__SPI0_Write_Enable ();//write enable 
  
  //---
  if (at26df081a_enabled){
  buffin[0]= BYTE_PAGE_PROGRAM;
  buffin[1]=((uint8)((address>>16)&0xFF));
  buffin[2]=((uint8)((address>>8)&0xFF));
  buffin[3]=((uint8)((address)&0xFF));
  
  
  if ((0xFF-buffin[3])>=txcnt){ //data fits into remaining space of the page
      for (index=0; index<txcnt; index++) buffin[index+4] = *buff++;
      SPI0_CommByte_Function ( buffin ,(txcnt+4) ,NULL ,0 );
   }
  
  
  else{ //data are over the page boundary
      remainingBytes = (txcnt - (0xFF-buffin[3]+1));
      
      for (index=0; index<(0xFF-buffin[3]+1); index++) 
            buffin[index+4] = *buff++;
      SPI0_CommByte_Function ( buffin ,((0xFF-buffin[3]+1)+4) ,NULL ,0 );
         
     
      for (index=0; index<(remainingBytes); index++) 
            buffin[index+4] = *buff++;
      
      buffin[2]++ ; //increments the page
      buffin[3] =0; //starts from the beginning of the page
      
      while (at26df081a__SPI0_Read_Busy_Flag ()) ;//wait if busy
      at26df081a__SPI0_Write_Enable ();//new write enable for the rest of data
      
      SPI0_CommByte_Function ( buffin ,(remainingBytes+4) ,NULL ,0 );
   }
  
  }
  
  /*
  for (index=0; index<txcnt; index++)
    {
    buffin[index+4] = *buff++;
    }
  //to do address alignment
  if (at26df081a_enabled){
  buffin[0]= BYTE_PAGE_PROGRAM;
  buffin[1]=((uint8)((address>>16)&0xFF));
  buffin[2]=((uint8)((address>>8)&0xFF));
  buffin[3]=((uint8)((address)&0xFF));
  
  SPI_CommByte (SPI0, buffin ,(txcnt+4) ,NULL ,0 );
  }
  */
  
  asm("nop");
  return TRUE;
}




/**************************************************************************//*!
* @brief    READ ARRAY over SPI0
******************************************************************************/

void at26df081a__SPI0_Read_Array (uint32 address, uint8 *buffout, uint16 rxcnt)

{
  uint8 buffin[5];
  
  if (at26df081a_enabled){
  buffin[0]= READ_ARRAY;
  buffin[1]=((uint8)((address>>16)&0xFF));
  buffin[2]=((uint8)((address>>8)&0xFF));
  buffin[3]=((uint8)((address)&0xFF));
  buffin[4]=0x00; //do not care byte
  
  SPI0_CommByte_Function ( buffin ,5 ,buffout ,rxcnt );
  }
  asm("nop");
}

/**************************************************************************//*!
* @brief    READ STATUS REGISTER over SPI0
******************************************************************************/
uint8 at26df081a__SPI0_Read_Status_Register (void)

{
  static uint8 buffin;
  static uint8 buffout;
  if (at26df081a_enabled){
  buffin= READ_STATUS_REGISTER;
  SPI0_CommByte_Function (&buffin,1,&buffout,1);
  }
  return buffout;
}

/**************************************************************************//*!
* @brief    Read busy flag over SPI0 
*               (1  means device is busy with an internal operation)
******************************************************************************/
uint8 at26df081a__SPI0_Read_Busy_Flag (void)

{
  uint8 buffin;
  uint8 buffout;
  if (at26df081a_enabled){
  buffin= READ_STATUS_REGISTER;
  SPI0_CommByte_Function (&buffin,1,&buffout,1);
  }
  if (buffout & SR_BUSY_MASK) return TRUE; 
  else return FALSE;
}

/**************************************************************************//*!
* @brief    Read Write enable latch status flag over SPI0 
*               (1  means write is enabled)
******************************************************************************/
uint8 at26df081a__SPI0_Read_Write_Enable_Flag (void)

{
  uint8 buffin;
  uint8 buffout;
  if (at26df081a_enabled){
  buffin= READ_STATUS_REGISTER;
  SPI0_CommByte_Function (&buffin,1,&buffout,1);
  }
  
  if (buffout & SR_WEL_MASK) return TRUE; 
  else return FALSE;
}

/**************************************************************************//*!
* @brief    Read Manufacturer and Device ID over SPI0
******************************************************************************/
void at26df081a__SPI0_Read_Manufacturer_and_Device_ID (uint8 *buffout)

{
  static uint8 buffin;
  if (at26df081a_enabled){
  buffin= READ_MFG_DEV_ID;
  SPI0_CommByte_Function (&buffin,1,buffout,4);
  asm("nop");
  }
}




/**************************************************************************//*!
* @brief    SPI0 CommByte wrapper for interrupt functionality
******************************************************************************/

void SPI0_CommByte_INT(uint8 *txdata,uint16 txcnt,uint8 *rxdata, uint16 rxcnt)
{

  while (!data_exchange_completed) //dangerous spot - needs option for exit
    asm("nop");
  spi_tx_cnt = (txcnt); 
  spi_rx_cnt = rxcnt; 
  spi_buff_tx_pointer= (txdata);
  spi_buff_rx_pointer= (rxdata);
  data_exchange_completed = FALSE;
  spi_cnt=(spi_tx_cnt + spi_rx_cnt);
  spi_cnt2 = spi_rx_cnt;

  SPI_TxIsrEnable(SPI0);  /* start the  packet  */
};






