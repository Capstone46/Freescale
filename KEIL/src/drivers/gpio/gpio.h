/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      gpio.h
 * @version   1.0.4.0
 * @date      Jan-30-2013
 * @brief     General-Purpose Input/Output (GPIO) driver header file.
 *
 * Revision History:
 *  1.	15/01/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup gpio_example0
 * @{
 * @par       Source code:
 * @include   gpio0_test\gpio0_test.c
 * @par       Appconfig.h:
 * @include   gpio0_test\appconfig.h   
 ******************************************************************************/
/*! @} End of gpio_example0                                                   */
#ifndef __GPIO_H
#define __GPIO_H 

#if (defined (MCU_MKL46Z256))
	// just for compability KL46 with KL43 headers
	#define INT_PORTC_PORTD  47	//INT_PORTD 
#endif
/******************************************************************************
 * definition configuration structure                                         *
 ******************************************************************************/
typedef struct { uint32 PCR;  } tPORT; 
typedef struct { uint32 PDDR; } tGPIO; 

/******************************************************************************
* PIN names definition
*
*//*! @addtogroup pin_names
* @{
*******************************************************************************/
#define PIN_0         (uint32)(1 <<  0)
#define PIN_1         (uint32)(1 <<  1)
#define PIN_2         (uint32)(1 <<  2)
#define PIN_3         (uint32)(1 <<  3)
#define PIN_4         (uint32)(1 <<  4)
#define PIN_5         (uint32)(1 <<  5)
#define PIN_6         (uint32)(1 <<  6)
#define PIN_7         (uint32)(1 <<  7)
#define PIN_8         (uint32)(1 <<  8)
#define PIN_9         (uint32)(1 <<  9)
#define PIN_10        (uint32)(1 << 10)
#define PIN_11        (uint32)(1 << 11)
#define PIN_12        (uint32)(1 << 12)
#define PIN_13        (uint32)(1 << 13)
#define PIN_14        (uint32)(1 << 14)
#define PIN_15        (uint32)(1 << 15)
#define PIN_16        (uint32)(1 << 16)
#define PIN_17        (uint32)(1 << 17)
#define PIN_18        (uint32)(1 << 18)
#define PIN_19        (uint32)(1 << 19)
#define PIN_20        (uint32)(1 << 20)
#define PIN_21        (uint32)(1 << 21)
#define PIN_22        (uint32)(1 << 22)
#define PIN_23        (uint32)(1 << 23)
#define PIN_24        (uint32)(1 << 24)
#define PIN_25        (uint32)(1 << 25)
#define PIN_26        (uint32)(1 << 26)
#define PIN_27        (uint32)(1 << 27)
#define PIN_28        (uint32)(1 << 28)
#define PIN_29        (uint32)(1 << 29)
#define PIN_30        (uint32)(1 << 30)
#define PIN_31        (uint32)(1 << 31)
/*! @} End of pin_names                                                       */

/******************************************************************************
* PORT default configurations used by PORT_init() function
*
*//*! @addtogroup port_config
* @{
*******************************************************************************/
/**************************************************************************/ /*!
 * @brief Disables pin with internal pull-up off (default mode after reset).
 *****************************************************************************/
#define PORT_MODULE_DISABLED_MODE   /* GPIO pin disabled                  */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(0))|CLR(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               CLR(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Disables pin with internal pull-up on.
 *****************************************************************************/
#define PORT_MODULE_DISABLED_PULLUP /* GPIO pin disabled, pull-up on      */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(0))|CLR(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|SET(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin to Alternative 0 (GPIO) mode with high drive strength.
 *****************************************************************************/
#define PORT_MODULE_ALT0_MODE       /* ALT0 push-pull mode high strength  */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(0))|SET(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               CLR(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin to Alternative 1 (GPIO) mode with high drive strength.
 *****************************************************************************/
#define PORT_MODULE_ALT1_MODE       /* ALT1 push-pull mode high strength  */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(1))|SET(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               CLR(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin to Alternative 2 (GPIO) mode with high drive strength.
 *****************************************************************************/
#define PORT_MODULE_ALT2_MODE       /* ALT2 push-pull mode high strength  */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(2))|SET(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               CLR(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin to Alternative 3 (GPIO) mode with high drive strength.
 *****************************************************************************/
#define PORT_MODULE_ALT3_MODE       /* ALT3 push-pull mode high strength  */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(3))|SET(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               CLR(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin to Alternative 4 (GPIO) mode with high drive strength.
 *****************************************************************************/
#define PORT_MODULE_ALT4_MODE       /* ALT4 push-pull mode high strength  */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(4))|SET(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               CLR(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin to Alternative 5 (GPIO) mode with high drive strength.
 *****************************************************************************/
#define PORT_MODULE_ALT5_MODE       /* ALT5 push-pull mode high strength  */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(5))|SET(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               CLR(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin to Alternative 6 (GPIO) mode with high drive strength.
 *****************************************************************************/
#define PORT_MODULE_ALT6_MODE       /* ALT6 push-pull mode high strength  */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(6))|SET(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|SET(PORT_PCR_SRE_MASK)|                  \
               CLR(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin to Alternative 7 (GPIO) mode with high drive strength.
 *****************************************************************************/
#define PORT_MODULE_ALT7_MODE       /* ALT7 push-pull mode high strength  */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(7))|SET(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               CLR(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin for button use (polling mode).
 *****************************************************************************/
#define PORT_MODULE_BUTTON_MODE     /* GPIO mode, pull-up                 */   \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               SET(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|SET(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin for button use (rissing edge IRQ).
 *****************************************************************************/
#define PORT_MODULE_BUTTON_IRQRE_MODE /* GPIO mode, pull-up enabled, IRQ on */ \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(9))|                   \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               SET(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|SET(PORT_PCR_PS_MASK),                    \
}
// just for compatibility with older version
#define PORT_MODULE_BUTTON_IRQ_MODE     PORT_MODULE_BUTTON_IRQRE_MODE

/**************************************************************************/ /*!
 * @brief Configures pin for button use (falling edge IRQ).
 *****************************************************************************/                   
#define PORT_MODULE_BUTTON_IRQFE_MODE /* GPIO mode, pull-up enabled, IRQ on */ \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(10))|                  \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               SET(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|SET(PORT_PCR_PS_MASK),                    \
}
                   
/**************************************************************************/ /*!
 * @brief Configures pin for button use (both edges IRQ).
 *****************************************************************************/
#define PORT_MODULE_BUTTON_IRQBE_MODE /* GPIO mode, pull-up enabled, IRQ on */ \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(11))|                  \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               SET(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|SET(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin for button use (IRQ detection on logic 0).
 *****************************************************************************/                   
#define PORT_MODULE_BUTTON_IRQLO0_MODE /* GPIO mode, pull-up enabled, IRQ on */ \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(8))|                   \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               SET(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|SET(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin for button use (IRQ detection on logic 1).
 *****************************************************************************/                    
#define PORT_MODULE_BUTTON_IRQLO1_MODE /* GPIO mode, pull-up enabled, IRQ on */ \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(12))|                  \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               SET(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|SET(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin for button use (DMA request on rissing edge).
 *****************************************************************************/                    
#define PORT_MODULE_BUTTON_DMARE_MODE /* GPIO mode, pull-up enabled, DMA on */ \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(1))|                   \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               SET(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|SET(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin for button use (DMA request on falling edge).
 *****************************************************************************/                    
#define PORT_MODULE_BUTTON_DMAFE_MODE /* GPIO mode, pull-up enabled, DMA on */ \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(2))|                   \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               SET(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|SET(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin for button use (DMA request on both edges).
 *****************************************************************************/                    
#define PORT_MODULE_BUTTON_DMABE_MODE /* GPIO mode, pull-up enabled, DMA on */ \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(3))|                   \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               SET(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|SET(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin to alternative 1 with pull up enable.
 *****************************************************************************/                    
#define PORT_MODULE_ALT1_PULLUP_MODE       /* GPIO mode, pull-up */            \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|SET(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin to alternative 1 with pull down enable.
 *****************************************************************************/                   
#define PORT_MODULE_ALT1_PULLDOWN_MODE       /* GPIO mode, pull-down */        \
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               SET(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin to alternative 1 with open drain.
 *****************************************************************************/
#define PORT_MODULE_ALT1_OPENDRAIN_MODE /* GPIO mode, Open drain enabled     */\
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               CLR(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin to alternative 1 with open drain and high strength.
 *****************************************************************************/                   
#define PORT_MODULE_ALT1_OPENDRAIN_HIGHSTRENGTH_MODE /* GPIO mode, OD&HS     */\
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(1))|SET(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|CLR(PORT_PCR_SRE_MASK)|                  \
               CLR(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}

/**************************************************************************/ /*!
 * @brief Configures pin for LED use.
 *****************************************************************************/  
#define PORT_MODULE_LED_MODE                               /* LED mode,      */\
(tPORT){                                                                       \
/* PCR      */ CLR(PORT_PCR_ISF_MASK)|SET(PORT_PCR_IRQC(0))|                   \
               SET(PORT_PCR_MUX(1))|CLR(PORT_PCR_DSE_MASK)|                    \
               CLR(PORT_PCR_PFE_MASK)|SET(PORT_PCR_SRE_MASK)|                  \
               CLR(PORT_PCR_PE_MASK)|CLR(PORT_PCR_PS_MASK),                    \
}
/*! @} End of port_config                                                     */

/******************************************************************************
* GPIO default configurations used by GPIO_init() function
*
*//*! @addtogroup gpio_config
* @{
*******************************************************************************/
/******************************************************************************
 * PIN default configurations                                                 *
 ******************************************************************************/
#define GPIO_PIN_OUTPUT             /* GPIO pin configured in output mode */  \
(tGPIO){                                                                      \
/* PDDR     */ SET(GPIO_PDDR_PDD_MASK),                                       \
}

#define GPIO_PIN_INPUT              /* GPIO pin configured in input mode  */  \
(tGPIO){                                                                      \
/* PDDR     */ CLR(GPIO_PDDR_PDD_MASK),                                       \
}
/*! @} End of gpio_config                                                     */

/******************************************************************************
* PORT callback used in PORT_Init() function
*
*//*! @addtogroup port_callback
* @{
*******************************************************************************/
/*! @brief PORT_CALLBACK function declaration                                 */
typedef void (*PORT_CALLBACK)(vuint32 pin_number);
/*! @} End of port_callback                                                   */

/******************************************************************************
* GPIO function and macro definitions
*
*//*! @addtogroup gpio_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Macro toglle port pins.
 * @param   port    - PORTA|PORTB|PORTC|PORTD|PORTE  
 * @param   mask    - 0-31  
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define PORT_ClrIrqFlag(port,pin)   (##port##_PCR##pin##) |= PORT_PCR_ISF_MASK;

/***************************************************************************//*!
 * @brief   Macro drives data to output (write data to gpio port).
 * @param   port    - GPIOA|GPIOB|GPIOC|GPIOD|GPIOE  
 * @param   mask    - PIN_0..PIN_32
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define GPIO_DataOutput(port,data)   port##_PDOR=(data);

/***************************************************************************//*!
 * @brief   Macro returns state of port pins.
 * @param   port    - GPIOA|GPIOB|GPIOC|GPIOD|GPIOE  
 * @return  32-bit status of the port pins
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define GPIO_Get(port)        port##_PDIR     /* reading value from GPIO port */

/***************************************************************************//*!
 * @brief   Macro set port pins.
 * @param   port    - GPIOA|GPIOB|GPIOC|GPIOD|GPIOE  
 * @param   mask    - PIN_0..PIN_32  
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define GPIO_Set(port,mask)   port##_PSOR=(mask); /* set bits on GPIO port    */

/***************************************************************************//*!
 * @brief   Macro clear port pins.
 * @param   port    - GPIOA|GPIOB|GPIOC|GPIOD|GPIOE  
 * @param   mask    - PIN_0..PIN_32  
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define GPIO_Clr(port,mask)   port##_PCOR=(mask); /* clear bits on GPIO port  */

/***************************************************************************//*!
 * @brief   Macro toglle port pins.
 * @param   port    - GPIOA|GPIOB|GPIOC|GPIOD|GPIOE  
 * @param   mask    - PIN_0..PIN_32  
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define GPIO_Tgl(port,mask)   port##_PTOR=(mask); /* toggle bits on GPIO port */

/* Function redefinition                                                      */
/***************************************************************************//*!
 * @brief   PORT initialization function.
 * @param   port    - PORTA|PORTB|PORTC|PORTD|PORTE
 * @param   cfg     - PORT configuration structure passed by value: 
 *                    PORT_MODULE_DISABLED_MODE,
 *                    PORT_MODULE_DISABLED_PULLUP,
 *                    PORT_MODULE_LED_MODE,
 *                    PORT_MODULE_ALT1_MODE,
 *                    PORT_MODULE_ALT2_MODE,
 *                    PORT_MODULE_ALT3_MODE,
 *                    PORT_MODULE_ALT4_MODE,
 *                    PORT_MODULE_ALT5_MODE,
 *                    PORT_MODULE_ALT6_MODE,
 *                    PORT_MODULE_ALT7_MODE,
 *                    PORT_MODULE_BUTTON_IRQ_MODE,
 *                    PORT_MODULE_BUTTON_MODE,
 *                    PORT_MODULE_ALT2_OPEN_DRAIN,
 *                    PORT_MODULE_ALT4_OPEN_DRAIN.
 * @param   mask    - PIN_0..PIN_32 
 * @param   ip      - interrupt priority 0..15
 * @param   callback- pointer to PORT_CALLBACK function
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define PORT_Init(port,cfg,mask,ip,callback)  port##_Init(cfg,mask,ip,callback)

/***************************************************************************//*!
 * @brief   GPIO initialization function.
 * @param   gpio    - GPIOA|GPIOB|GPIOC|GPIOD|GPIOE
 * @param   cfg     - GPIO configuration structure passed by value: 
 *                    GPIO_PIN_OUTPUT,
 *                    GPIO_PIN_INPUT.
 * @param   mask    - PIN_0..PIN_32 
 * @return  none
 * @note    Implemented as function call.
 ******************************************************************************/
#define GPIO_Init(gpio,cfg,mask)               gpio##_Init(cfg,mask)
/*! @} End of gpio_macro                                                      */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/    
extern void PORTA_Init (tPORT port, uint32 pin_mask, uint8 ip, PORT_CALLBACK pCallback);
extern void PORTB_Init (tPORT port, uint32 pin_mask, uint8 ip, PORT_CALLBACK pCallback);
extern void PORTC_Init (tPORT port, uint32 pin_mask, uint8 ip, PORT_CALLBACK pCallback);
extern void PORTD_Init (tPORT port, uint32 pin_mask, uint8 ip, PORT_CALLBACK pCallback);
extern void PORTE_Init (tPORT port, uint32 pin_mask, uint8 ip, PORT_CALLBACK pCallback);

extern void GPIOA_Init (tGPIO gpio, uint32 pin_mask);
extern void GPIOB_Init (tGPIO gpio, uint32 pin_mask);
extern void GPIOC_Init (tGPIO gpio, uint32 pin_mask);
extern void GPIOD_Init (tGPIO gpio, uint32 pin_mask);
extern void GPIOE_Init (tGPIO gpio, uint32 pin_mask);
   
#endif /* __GPIO_H */
