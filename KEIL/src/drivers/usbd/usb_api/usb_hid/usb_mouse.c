/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file mouse_button.c
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief  The file emulates a mouse with buttons
 *         4 buttons are used on the demo board for the emulation
 *         PTG0--------- for left click(For JS16 PTG0 is inactive)
 *         PTG1--------- for right click
 *         PTG2--------- if macro "UP_LEFT" is defined mouse moves "left"
 *                       else mouse moves "right"
 *         PTG3--------- if macro "UP_LEFT" is defined mouse moves "up"
 *                       else mouse moves "down"
 *
 *   NOTE: key pressed  == LOGIC 0
 *         key released == LOGIC 1
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* User Defined Data Types */
#include "usb_hid.h"        /* USB HID Class Header File */
#include "usb_mouse.h"      /* Mouse Application Header File */

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
void USB_Mouse_Init  (void);
void USB_Mouse_Update(uint_8 left_bt, uint_8 rigth_bt, int_8  x, int_8  y);

/****************************************************************************
 * Global Variables - None
 ****************************************************************************/

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
static void   USB_Mouse_Callback      (uint_8 controller_ID, 
                                       uint_8 event_type, 
                                       void* val);

static uint_8 USB_Mouse_Param_Callback(uint_8 request, 
                                       uint_16 value, 
                                       uint_16 wIndex,
                                       uint_8_ptr* data,
                                       USB_PACKET_SIZE* size);


/*****************************************************************************
 * Local Variables
 *****************************************************************************/
static boolean mouse_init = FALSE;          /* Application Init Flag */
#if defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=4
#elif defined(__ARMCC_VERSION)
__align(4) 
#endif
static uint_8 rpt_buf[MOUSE_BUFF_SIZE];     /* Mouse Event Report Buffer
                                               Key press */
#if defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=4
#elif defined(__ARMCC_VERSION)
__align(4) 
#endif
static uint_8 null_buf[MOUSE_BUFF_SIZE];    /* Mouse Event Report Buffer
                                               Key Release */
#if defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=4
#elif defined(__ARMCC_VERSION)
__align(4) 
#endif
static uint_8 g_app_request_params[2];      /* for get/set idle and protocol
                                               requests*/


/*****************************************************************************
 * Local Functions
 *****************************************************************************/

/******************************************************************************
 *
 *    @name        USB_App_Callback
 *
 *    @brief       This function handles the callback
 *
 *    @param       controller_ID    : Controller ID
 *    @param       event_type       : value of the event
 *    @param       val              : gives the configuration value
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called from the class layer whenever reset occurs or enum
 * is complete. after the enum is complete this function sets a variable so
 * that the application can start
 *****************************************************************************/
void USB_Mouse_Callback(
      uint_8 controller_ID,/* [IN] Controller ID */
      uint_8 event_type,   /* [IN] value of the event*/
      void* val            /* [IN] gives the configuration value*/
)
{
    UNUSED (controller_ID)
    UNUSED (val)
      
    if((event_type == USB_APP_BUS_RESET) || 
       (event_type == USB_APP_CONFIG_CHANGED))
    {
        mouse_init = FALSE;
    }
    else if(event_type == USB_APP_ENUM_COMPLETE)
    {   
      /* if enumeration is complete set mouse_init so that appl. can start */
        mouse_init = TRUE;
    }

    return;
}

/******************************************************************************
 *
 *    @name        USB_App_Param_Callback
 *
 *    @brief       This function handles callbacks for USB HID Class request
 *
 *    @param       request  : request type
 *    @param       value    : give report type and id
 *    @param       data     : pointer to the data
 *    @param       size     : size of the transfer
 *
 *    @return      status
 *                 USB_OK  :  if successful
 *                 else return error
 *
 *****************************************************************************
 * This function is called whenever a HID class request is received. This
 * function handles these class requests
 *****************************************************************************/
uint_8 USB_Mouse_Param_Callback(
      uint_8 request,        /* [IN] request type */
      uint_16 value,         /* [IN] report type and ID */
      uint_16 wIndex,		 /* [IN] interface*/
      uint_8_ptr* data,      /* [OUT] pointer to the data */
      USB_PACKET_SIZE* size  /* [OUT] size of the transfer */
)
{
  uint_8 status = USB_OK;
  uint_8 index = (uint_8)((request - 2) & USB_HID_REQUEST_TYPE_MASK);
                                            /* index == 0 for get/set idle,
                                          index == 1 for get/set protocol */

  *size = 0;
  /* handle the class request */
  switch(request)
  {
    case USB_HID_GET_REPORT_REQUEST :
      *data = &rpt_buf[0]; /* point to the report to send */
      *size = MOUSE_BUFF_SIZE; /* report size */
      break;

    case USB_HID_SET_REPORT_REQUEST :
      for(index = 0; index < MOUSE_BUFF_SIZE ; index++)
      {   /* copy the report sent by the host */
          rpt_buf[index] = *(*data + index);
      }
      break;

    case USB_HID_GET_IDLE_REQUEST :
      /* point to the current idle rate */
      *data = &g_app_request_params[index];
      *size = REQ_DATA_SIZE;
      break;

    case USB_HID_SET_IDLE_REQUEST :
      /* set the idle rate sent by the host */
      g_app_request_params[index] =(uint_8)((value & MSB_MASK) >>
                                            HIGH_BYTE_SHIFT);
      break;

    case USB_HID_GET_PROTOCOL_REQUEST :
      /* point to the current protocol code
         0 = Boot Protocol
         1 = Report Protocol*/
      *data = &g_app_request_params[index];
      *size = REQ_DATA_SIZE;
      break;

    case USB_HID_SET_PROTOCOL_REQUEST :
      /* set the protocol sent by the host
         0 = Boot Protocol
         1 = Report Protocol*/
      g_app_request_params[index] = (uint_8)(value);
      break;
  }

  return status;
}

/******************************************************************************
 *
 *   @name        TestApp_Init
 *
 *   @brief       This function is the entry for Mouse Application
 *
 *   @param       None
 *
 *   @return      None
 *
 *****************************************************************************
 * This function starts the Mouse Application
 *****************************************************************************/
void USB_Mouse_Init(void)
{
  uint_8   error;

  rpt_buf[3] = 0x00;          /* always zero */

  *((uint_32_ptr)rpt_buf) = 0;
  *((uint_32_ptr)null_buf) = 0;
   
  __disable_irq();            /* Global Intterupt disable    */  
  
  /* old documentation writes setting this bit is mandatory */
  USB0_USBTRC0 = 0x40;
  
  NVIC_ICPR = (1 << 24);      /* Clear any pending interrupts on USB */
  NVIC_ISER = (1 << 24);      /* Enable interrupts from USB module   */

  USB0_CLK_RECOVER_IRC_EN = USB_CLK_RECOVER_IRC_EN_IRC_EN_MASK|USB_CLK_RECOVER_IRC_EN_REG_EN_MASK;
  USB0_CLK_RECOVER_CTRL = USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK|USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_MASK;
  
  /* Initialize the USB interface */
  error = USB_Class_HID_Init(CONTROLLER_ID, 
                             USB_Mouse_Callback, 
                             NULL, 
                             USB_Mouse_Param_Callback);
  
  UNUSED(error);
  
  __enable_irq();             /* Global Intterupt enable */  
}

/******************************************************************************
 *
 *   @name        TestApp_Task
 *
 *   @brief       Application task function. It is called from the main loop
 *
 *   @param       None
 *
 *   @return      None
 *
 *****************************************************************************
 * Application task function. It is called from the main loop
 *****************************************************************************/
void USB_Mouse_Update(uint_8 left_bt, uint_8 rigth_bt, int_8  x, int_8  y)
{
  /* call the periodic task function */
  USB_Class_HID_Periodic_Task();

  if(mouse_init) /*check whether enumeration is complete or not */
  {   
    /* left and right buttons */
    rpt_buf[0]  = (left_bt  & 0x0F) ? 0x01 : 0x00;
    rpt_buf[0] |= (rigth_bt & 0x0F) ? 0x02 : 0x00;
    
    /* left or right movement */
    rpt_buf[1] = x;
    
    /* up or down movement */
    rpt_buf[2] = y;
    
    //if(rpt_buf[0] || rpt_buf[1] || rpt_buf[2])
    {
      (void)USB_Class_HID_Send_Data(CONTROLLER_ID, 
                                    HID_ENDPOINT, 
                                    rpt_buf,
                                    MOUSE_BUFF_SIZE);

//      if(rpt_buf[0])
//      {
//        /* required to send Click Release for Click Press Events */
//        (void)USB_Class_HID_Send_Data(CONTROLLER_ID,
//                                      HID_ENDPOINT,
//                                      null_buf,
//                                      MOUSE_BUFF_SIZE);
//      }
    }
  }
}
