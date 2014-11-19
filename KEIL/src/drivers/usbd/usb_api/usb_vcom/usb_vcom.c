/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file virtual_com.c
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief  The file emulates a USB PORT as Loopback Serial Port.
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* Contains User Defined Data Types */
#include "usb_cdc.h"        /* USB CDC Class Header File */
#include "usb_vcom.h"       /* Virtual COM Port Application Header File */
#include <stdio.h>

/* skip the inclusion in dependency state */
#ifndef __NO_SETJMP
#include <stdio.h>
#endif

#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 * Constant and Macro's - None
 *****************************************************************************/

/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/
void USB_VCOM_Init(void);
void USB_VCOM_Update(void);


/****************************************************************************
 * Global Variables
 ****************************************************************************/
#if HIGH_SPEED_DEVICE
uint_32 g_cdcBuffer[DIC_BULK_OUT_ENDP_PACKET_SIZE >> 1];
#endif

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
static void USB_VCOM_Callback  (uint_8 controller_ID,
                                uint_8 event_type, 
                                void* val);

static void USB_Notify_Callback(uint_8 controller_ID,
                                uint_8 event_type, 
                                void* val);

/*****************************************************************************
 * Local Variables
 *****************************************************************************/
/* Virtual COM Application start Init Flag */
static volatile boolean start_app = FALSE;

/* Virtual COM Application Carrier Activate Flag */
static volatile boolean start_transactions = TRUE;

/* Receive Buffer */
static uint_8 g_curr_recv_buf[DATA_BUFF_SIZE];

/* Send Buffer */
//static uint_8 g_curr_send_buf[DATA_BUFF_SIZE];

/* Receive Data Size */
static uint_8 g_recv_size;

/* Send Data Size */
//static uint_8 g_send_size;

/*****************************************************************************
 * Local Functions
 *****************************************************************************/


/***************************************************************************//*!
 * @brief   USB VCOM initialization
 * @details This function starts the Virtual COM-Port application
 * @param   Non.
 * @return  Non.
 * @note    It is called from the main loop
 * @warning Non.
 ******************************************************************************/
void USB_VCOM_Init(void)
{
  uint_8   error;

  g_recv_size = 0;
  //g_send_size = 0;
  
  __disable_irq();            /* Global Intterupt disable    */  
  
  /* old documentation writes setting this bit is mandatory */
  USB0_USBTRC0 = 0x40;

  NVIC_ICPR = (1 << 24);      /* Clear any pending interrupts on USB */
  NVIC_ISER = (1 << 24);      /* Enable interrupts from USB module   */

  USB0_CLK_RECOVER_IRC_EN = USB_CLK_RECOVER_IRC_EN_IRC_EN_MASK|USB_CLK_RECOVER_IRC_EN_REG_EN_MASK;
  USB0_CLK_RECOVER_CTRL = USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK|USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_MASK;

  /* Initialize the USB interface */
  error = USB_Class_CDC_Init(CONTROLLER_ID,
                             USB_VCOM_Callback,
                             NULL,
                             USB_Notify_Callback, 
                             TRUE);
  if(error != USB_OK)
  {
    /* Error initializing USB-CDC Class */
    return;
  }
  
  __enable_irq();             /* Global Intterupt enable */  
}


/***************************************************************************//*!
 * @brief   USB VCOM periodic task execition
 * @details Function provided executing a delayed internal functions
 * @param   Non.
 * @return  Non.
 * @note    It is called from the main loop
 * @warning Non.
 ******************************************************************************/
void USB_VCOM_PeriodicTask(void)
{ 
  /* call the periodic task function */
  USB_Class_CDC_Periodic_Task();
}


/***************************************************************************//*!
 * @brief   USB VCOM data send
 * @details Function provided a sending data to USB port
 * @param   data - pointer to data buffer (array)
 *          len  - data buffer size
 * @return  number of corectly send bytes
 * @note    It is called from the main loop
 * @warning Non.
 ******************************************************************************/
uint_8 USB_VCOM_Send(uint_8 *data, uint_8 len)
{         
  uint_8 error, count = 0;

  /*check whether enumeration is complete or not */
  if((start_app == TRUE) && (start_transactions == TRUE))
  {
    if(len > 0)
    {
      if(len > DATA_BUFF_SIZE)
      {
        count = DATA_BUFF_SIZE;
      }
      else
      {
        count = len;
      }
      
      /* Send Data to USB Host*/
      error = USB_Class_CDC_Interface_DIC_Send_Data(CONTROLLER_ID, data, count);
      if(error != USB_OK)
      {
        /* Send Data Error Handling Code goes here */
      }
    }
  }
  
  return count;
}


/***************************************************************************//*!
 * @brief   USB VCOM data receive
* @details Function provided a receiving data from USB port
 * @param   data - pointer to data buffer (array)
 *          len  - data buffer size
 * @return  number of corectly received bytes
 * @note    It is called from the main loop
 * @warning Non.
 ******************************************************************************/
uint_8 USB_VCOM_Receive(uint_8 *data, uint_8 len)
{
  uint_8 i, count = 0;

  /*check whether enumeration is complete or not */
  if((start_app == TRUE) && (start_transactions == TRUE))
  {
    /* Loopback Application Code */
    if(g_recv_size > 0)
    {
      if(len < g_recv_size)
      {
        count = len;
      }
      else
      {
        count = g_recv_size;
      }
      
      /* Copy Received Buffer to Send Buffer */
      for (i = 0; i < count; i++)
      {
        data[i] = g_curr_recv_buf[i];
      }
      
      g_recv_size = 0;
    }
  }
  
  return count;
}


/******************************************************************************
 *
 *    @name        USB_App_Callback
 *
 *    @brief       This function handles Class callback
 *
 *    @param       controller_ID    : Controller ID
 *    @param       event_type       : Value of the event
 *    @param       val              : gives the configuration value
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called from the class layer whenever reset occurs or enum
 * is complete. After the enum is complete this function sets a variable so
 * that the application can start.
 * This function also receives DATA Send and RECEIVED Events
 *****************************************************************************/
static void USB_VCOM_Callback (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event_type,      /* [IN] value of the event */
    void* val               /* [IN] gives the configuration value */
)
{
    UNUSED (controller_ID)
    UNUSED (val)
    if(event_type == USB_APP_BUS_RESET)
    {
        start_app=FALSE;
    }
    else if(event_type == USB_APP_ENUM_COMPLETE)
    {    	
#if HIGH_SPEED_DEVICE
    	// prepare for the next receive event
    	USB_Class_CDC_Interface_DIC_Recv_Data(&controller_ID,
    	                                      (uint_8_ptr)g_cdcBuffer, 
    	                                      DIC_BULK_OUT_ENDP_PACKET_SIZE);
#endif
        start_app=TRUE;
    }
    else if((event_type == USB_APP_DATA_RECEIVED)&&
            (start_transactions == TRUE))
    {
        /* Copy Received Data buffer to Application Buffer */
        USB_PACKET_SIZE BytesToBeCopied;
        APP_DATA_STRUCT* dp_rcv = (APP_DATA_STRUCT*)val;
        uint_8 index;
        BytesToBeCopied = (USB_PACKET_SIZE)((dp_rcv->data_size > DATA_BUFF_SIZE) ?
                                      DATA_BUFF_SIZE:dp_rcv->data_size);
        for(index = 0; index<BytesToBeCopied ; index++)
        {
            g_curr_recv_buf[index]= dp_rcv->data_ptr[index];
        }
        g_recv_size = index;
    }
    else if((event_type == USB_APP_SEND_COMPLETE) && (start_transactions == TRUE))
    {
        /* Previous Send is complete. Queue next receive */
#if HIGH_SPEED_DEVICE
    	(void)USB_Class_CDC_Interface_DIC_Recv_Data(CONTROLLER_ID, 
                                                    g_cdcBuffer, 
                                                    DIC_BULK_OUT_ENDP_PACKET_SIZE);
#else
        (void)USB_Class_CDC_Interface_DIC_Recv_Data(CONTROLLER_ID, NULL, 0);
#endif
    }

    return;
}

/******************************************************************************
 *
 *    @name        USB_Notify_Callback
 *
 *    @brief       This function handles PSTN Sub Class callbacks
 *
 *    @param       controller_ID    : Controller ID
 *    @param       event_type       : PSTN Event Type
 *    @param       val              : gives the configuration value
 *
 *    @return      None
 *
 *****************************************************************************
 * This function handles USB_APP_CDC_CARRIER_ACTIVATED and
 * USB_APP_CDC_CARRIER_DEACTIVATED PSTN Events
 *****************************************************************************/
static void USB_Notify_Callback (
  uint_8 controller_ID,   /* [IN] Controller ID */
  uint_8 event_type,      /* [IN] PSTN Event Type */
  void* val               /* [IN] gives the configuration value */
)
{
  UNUSED (controller_ID)
  UNUSED (val)
    
  if(start_app == TRUE)
  {
    if(event_type == USB_APP_CDC_CARRIER_ACTIVATED)
    {
      start_transactions = TRUE;
    }
    else if(event_type == USB_APP_CDC_CARRIER_DEACTIVATED)
    {
      //start_transactions = FALSE;
    }
  }
  
  return;
}

/* EOF */
