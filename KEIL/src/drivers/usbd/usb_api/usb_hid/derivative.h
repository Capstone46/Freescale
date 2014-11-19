/*
 * Note: This file is recreated by the project wizard whenever the MCU is
 *       changed and should not be edited by hand
 */

/* Include the derivative-specific header file */

/*
 * Include the platform specific header file
 */
#ifndef _H_DERIVATIVE_
#define _H_DERIVATIVE_

#include "appconfig.h"
#include "device.h"


#if defined(MCU_MKL43Z256)
/* Remap USB0 FS OTG to USB FS Device */
//#define USB0_PERID                               USB_PERID
//#define USB0_IDCOMP                              USB_IDCOMP
//#define USB0_REV                                 USB_REV
//#define USB0_ADDINFO                             USB_ADDINFO
#define USB0_OTGCTL                              USB0_CTL0
#define USB_OTGCTL_OTGEN_MASK                    0
#define USB_OTGCTL_DPHIGH_MASK                   USB_CTL0_DPHIGH_MASK

//#define USB0_ISTAT                               USB_ISTAT
//#define USB0_INTEN                               USB_INTEN
//#define USB0_ERRSTAT                             USB_ERRSTAT
//#define USB0_ERREN                               USB_ERREN
//#define USB0_STAT                                USB_STAT
#define USB0_CTL                                 USB0_CTL1
#define USB_CTL_USBENSOFEN_MASK                  USB_CTL1_USBEN_MASK
#define USB_CTL_ODDRST_MASK                      USB_CTL1_ODDRST_MASK
#define USB_CTL_TXSUSPENDTOKENBUSY_MASK          USB_CTL1_TXSUSPENDTOKENBUSY_MASK
#define USB_CTL_RESUME_MASK                      0

//#define USB0_ADDR                                USB_ADDR
//#define USB0_BDTPAGE1                            USB_BDTPAGE1
//#define USB0_FRMNUML                             USB_FRMNUML
//#define USB0_FRMNUMH                             USB_FRMNUMH
#define USB0_TOKEN                               
#define USB0_SOFTHLD                             
//#define USB0_BDTPAGE2                            USB_BDTPAGE2
//#define USB0_BDTPAGE3                            USB_BDTPAGE3
//#define USB0_ENDPT0                              USB_ENDPT0
//#define USB0_ENDPT1                              USB_ENDPT1
//#define USB0_ENDPT2                              USB_ENDPT2
//#define USB0_ENDPT3                              USB_ENDPT3
//#define USB0_ENDPT4                              USB_ENDPT4
//#define USB0_ENDPT5                              USB_ENDPT5
//#define USB0_ENDPT6                              USB_ENDPT6
//#define USB0_ENDPT7                              USB_ENDPT7
//#define USB0_ENDPT8                              USB_ENDPT8
//#define USB0_ENDPT9                              USB_ENDPT9
//#define USB0_ENDPT10                             USB_ENDPT10
//#define USB0_ENDPT11                             USB_ENDPT11
//#define USB0_ENDPT12                             USB_ENDPT12
//#define USB0_ENDPT13                             USB_ENDPT13
//#define USB0_ENDPT14                             USB_ENDPT14
//#define USB0_ENDPT15                             USB_ENDPT15
//#define USB0_USBCTRL                             USB_USBCTRL
//#define USB0_OBSERVE                             USB_OBSERVE
//#define USB0_CONTROL                             USB_CONTROL
//#define USB0_USBTRC0                             USB_USBTRC0
//#define USB0_USBFRMADJUST                        USB_USBFRMADJUST
#endif

#endif


