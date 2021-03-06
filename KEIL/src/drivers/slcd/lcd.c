/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      lcd.c
 * @version   1.0.2.0
 * @date      Sep-14-2012
 * @brief     LCD controller (LCD) driver source code.
 ******************************************************************************/
#include "common.h"
#include "lcd.h"

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/
static LCD_CALLBACK volatile pCallbackLCD=NULL;

/******************************************************************************
 * interrupt functions prototype                                              *
 ******************************************************************************/
void LCD_isr (void);

/******************************************************************************
 * local variable                                                             *
 ******************************************************************************/
uint8 LCD_CharPosition;

/******************************************************************************
 * Public functions definitions                                               *
 ******************************************************************************/
 #if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82
#endif
static unsigned char * const bpaPlace1[] =
{
  (unsigned char *)&Char1x,  
  (unsigned char *)&Char1y,  
  (unsigned char *)&Char2x,  
  (unsigned char *)&Char2y,  
  (unsigned char *)&Char3x,  
  (unsigned char *)&Char3y,  
  (unsigned char *)&Char4x,  
  (unsigned char *)&Char4y,
};
                                          
static const unsigned char baAscii1 [] =
{
#if _LCDTYPE == 1
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = 0 ,   offset =0
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = 1 ,   offset =2
    ( L0SEGA+ L0SEGB+!L0SEGC+!L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = 2 ,   offset =4
    ( L0SEGA+ L0SEGB+ L0SEGC+!L0SEGF+ L0SEGG+!L0SEGE+ L0SEGD),   //Char = 3 ,   offset =6
    (!L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+ L0SEGG+!L0SEGE+!L0SEGD),   //Char = 4 ,   offset =8
    ( L0SEGA+!L0SEGB+ L0SEGC+ L0SEGF+ L0SEGG+!L0SEGE+ L0SEGD),   //Char = 5 ,   offset =10
    (!L0SEGA+!L0SEGB+ L0SEGC+ L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = 6 ,   offset =12
    ( L0SEGA+ L0SEGB+ L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = 7 ,   offset =14
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = 8 ,   offset =16
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+ L0SEGG+!L0SEGE+!L0SEGD),   //Char = 9 ,   offset =18
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = : ,   offset =20
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = ; ,   offset =22
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = < ,   offset =24
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = = ,   offset =26
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = > ,   offset =28
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = ? ,   offset =30
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = @ ,   offset =32
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = A ,   offset =34
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = B ,   offset =36
    ( L0SEGA+!L0SEGB+!L0SEGC+ L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = C ,   offset =38
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = D ,   offset =40
    ( L0SEGA+!L0SEGB+!L0SEGC+ L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = E ,   offset =42
    ( L0SEGA+!L0SEGB+!L0SEGC+ L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = F ,   offset =44
    (!L0SEGA+!L0SEGB+ L0SEGC+ L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = G ,   offset =46
    (!L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = H ,   offset =48
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = I ,   offset =50
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+ L0SEGD),   //Char = J ,   offset =52
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = K ,   offset =54
    (!L0SEGA+!L0SEGB+!L0SEGC+ L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = L ,   offset =56
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = M ,   offset =58
    (!L0SEGA+!L0SEGB+ L0SEGC+!L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = N ,   offset =60
    (!L0SEGA+!L0SEGB+ L0SEGC+!L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = O ,   offset =62
    ( L0SEGA+ L0SEGB+!L0SEGC+ L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = P ,   offset =64
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = Q ,   offset =66
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = R ,   offset =68
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+ L0SEGG+!L0SEGE+!L0SEGD),   //Char = S ,   offset =70
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = T ,   offset =72
    (!L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = U ,   offset =74
    (!L0SEGA+ L0SEGB+!L0SEGC+ L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = V ,   offset =76
    (!L0SEGA+ L0SEGB+ L0SEGC+ L0SEGF+!L0SEGG+ L0SEGE+!L0SEGD),   //Char = W ,   offset =78
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = X ,   offset =80
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = Y ,   offset =82
    ( L0SEGA+!L0SEGB+!L0SEGC+!L0SEGF+!L0SEGG+!L0SEGE+ L0SEGD),   //Char = Z ,   offset =84
#elif _LCDTYPE == 2 
#if (defined FRDM_KL46Z48M)|(defined FRDM_KL43Z48M)
    ( L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = 0 ,   offset =0
    (!L0SEGA+ L0SEGB+ L0SEGC),     (!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = 1 ,   offset =2
    ( L0SEGA+ L0SEGB+!L0SEGC),     (!L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = 2 ,   offset =4
    ( L0SEGA+ L0SEGB+ L0SEGC),     (!L0SEGF+ L0SEGG+!L0SEGE+ L0SEGD),   //Char = 3 ,   offset =6
    (!L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+!L0SEGE+!L0SEGD),   //Char = 4 ,   offset =8
    ( L0SEGA+!L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+!L0SEGE+ L0SEGD),   //Char = 5 ,   offset =10
    (!L0SEGA+!L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = 6 ,   offset =12
    ( L0SEGA+ L0SEGB+ L0SEGC),     (!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = 7 ,   offset =14
    ( L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = 8 ,   offset =16
    ( L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+!L0SEGE+!L0SEGD),   //Char = 9 ,   offset =18
    (!L0SEGA+!L0SEGB+!L0SEGC),     (!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = : ,   offset =20
    (!L0SEGA+!L0SEGB+!L0SEGC),     (!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = ; ,   offset =22
    (!L0SEGA+!L0SEGB+!L0SEGC),     (!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = < ,   offset =24
    (!L0SEGA+!L0SEGB+!L0SEGC),     (!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = = ,   offset =26
    (!L0SEGA+!L0SEGB+!L0SEGC),     (!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = > ,   offset =28
    (!L0SEGA+!L0SEGB+!L0SEGC),     (!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = ? ,   offset =30
    ( L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = @ ,   offset =32
    ( L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = A ,   offset =34
    (!L0SEGA+!L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = B ,   offset =36
    ( L0SEGA+!L0SEGB+!L0SEGC),     ( L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = C ,   offset =38
    (!L0SEGA+ L0SEGB+ L0SEGC),     ( !L0SEGF+L0SEGG+ L0SEGE+ L0SEGD),   //Char = D ,   offset =40
    ( L0SEGA+!L0SEGB+!L0SEGC),     ( L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = E ,   offset =42
    ( L0SEGA+!L0SEGB+!L0SEGC),     ( L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = F ,   offset =44
    ( L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+!L0SEGE+ L0SEGD),   //Char = G ,   offset =46
    (!L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = H ,   offset =48
    (!L0SEGA+ L0SEGB+ L0SEGC),     (!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = I ,   offset =50
    (!L0SEGA+ L0SEGB+ L0SEGC),     (!L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = J ,   offset =52
    (!L0SEGA+!L0SEGB+!L0SEGC),     (!L0SEGF+!L0SEGG+!L0SEGE+!L0SEGD),   //Char = K ,   offset =54
    (!L0SEGA+!L0SEGB+!L0SEGC),     ( L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = L ,   offset =56
    ( L0SEGA+!L0SEGB+ L0SEGC),     (!L0SEGF+!L0SEGG+ L0SEGE+!L0SEGD),   //Char = M ,   offset =58
    (!L0SEGA+!L0SEGB+ L0SEGC),     (!L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = N ,   offset =60
    ( L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = O ,   offset =62
    ( L0SEGA+ L0SEGB+!L0SEGC),     ( L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = P ,   offset =64
    ( L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+!L0SEGE+!L0SEGD),   //Char = Q ,   offset =66
    (!L0SEGA+!L0SEGB+!L0SEGC),     (!L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = R ,   offset =68
    ( L0SEGA+!L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+!L0SEGE+ L0SEGD),   //Char = S ,   offset =70
    (!L0SEGA+!L0SEGB+!L0SEGC),     ( L0SEGF+ L0SEGG+ L0SEGE+ L0SEGD),   //Char = T ,   offset =72
    (!L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = U ,   offset =74
    (!L0SEGA+!L0SEGB+ L0SEGC),     (!L0SEGF+!L0SEGG+ L0SEGE+ L0SEGD),   //Char = V ,   offset =76
    (!L0SEGA+ L0SEGB+!L0SEGC),     ( L0SEGF+!L0SEGG+!L0SEGE+ L0SEGD),   //Char = W ,   offset =78
    (!L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+!L0SEGE+!L0SEGD),   //Char = X ,   offset =80
    (!L0SEGA+ L0SEGB+ L0SEGC),     ( L0SEGF+ L0SEGG+!L0SEGE+ L0SEGD),   //Char = Y ,   offset =82
    ( L0SEGA+ L0SEGB+!L0SEGC),     (!L0SEGF+ L0SEGG+ L0SEGE+!L0SEGD),   //Char = Z ,   offset =84  
#elif (defined TWR_KL46Z48M)|(defined TWR_KL43Z48M)
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = 0 ,   offset =0
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = 1 ,   offset =2
    ( L0SEGA+ L0SEGB+!L0SEGC+ L0SEGD),     (!L0SEGF+ L0SEGG+ L0SEGE),   //Char = 2 ,   offset =4
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     (!L0SEGF+ L0SEGG+!L0SEGE),   //Char = 3 ,   offset =6
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     ( L0SEGF+ L0SEGG+!L0SEGE),   //Char = 4 ,   offset =8
    ( L0SEGA+!L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+!L0SEGE),   //Char = 5 ,   offset =10
    ( L0SEGA+!L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = 6 ,   offset =12
    ( L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = 7 ,   offset =14
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = 8 ,   offset =16
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+!L0SEGE),   //Char = 9 ,   offset =18
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = : ,   offset =20
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = ; ,   offset =22
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = < ,   offset =24
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = = ,   offset =26
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = > ,   offset =28
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = ? ,   offset =30
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = @ ,   offset =32
    ( L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = A ,   offset =34
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = B ,   offset =36
    ( L0SEGA+!L0SEGB+!L0SEGC+ L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = C ,   offset =38
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = D ,   offset =40
    ( L0SEGA+!L0SEGB+!L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = E ,   offset =42
    ( L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = F ,   offset =44
    (!L0SEGA+!L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = G ,   offset =46
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = H ,   offset =48
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = I ,   offset =50
    (!L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = J ,   offset =52
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = K ,   offset =54
    (!L0SEGA+!L0SEGB+!L0SEGC+ L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = L ,   offset =56
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = M ,   offset =58
    (!L0SEGA+!L0SEGB+ L0SEGC+!L0SEGD),     (!L0SEGF+ L0SEGG+ L0SEGE),   //Char = N ,   offset =60
    (!L0SEGA+!L0SEGB+ L0SEGC+ L0SEGD),     (!L0SEGF+ L0SEGG+ L0SEGE),   //Char = O ,   offset =62
    ( L0SEGA+ L0SEGB+!L0SEGC+!L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = P ,   offset =64
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = Q ,   offset =66
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+ L0SEGG+ L0SEGE),   //Char = R ,   offset =68
    ( L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     ( L0SEGF+ L0SEGG+!L0SEGE),   //Char = S ,   offset =70
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = T ,   offset =72
    (!L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = U ,   offset =74
    (!L0SEGA+ L0SEGB+!L0SEGC+!L0SEGD),     ( L0SEGF+!L0SEGG+!L0SEGE),   //Char = V ,   offset =76
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = W ,   offset =78
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = X ,   offset =80
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = Y ,   offset =82
    ( L0SEGA+!L0SEGB+!L0SEGC+ L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = Z ,   offset =84
#else
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = 0 ,   offset =0
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = 1 ,   offset =2
    ( L0SEGA+ L0SEGB+!L0SEGC+ L0SEGD),     (!L0SEGF+ L0SEGG+ L0SEGE),   //Char = 2 ,   offset =4
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     (!L0SEGF+ L0SEGG+!L0SEGE),   //Char = 3 ,   offset =6
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     ( L0SEGF+ L0SEGG+!L0SEGE),   //Char = 4 ,   offset =8
    ( L0SEGA+!L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+!L0SEGE),   //Char = 5 ,   offset =10
    ( L0SEGA+!L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = 6 ,   offset =12
    ( L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = 7 ,   offset =14
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = 8 ,   offset =16
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+!L0SEGE),   //Char = 9 ,   offset =18
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = : ,   offset =20
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = ; ,   offset =22
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = < ,   offset =24
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = = ,   offset =26
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = > ,   offset =28
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = ? ,   offset =30
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = @ ,   offset =32
    ( L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = A ,   offset =34
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = B ,   offset =36
    ( L0SEGA+!L0SEGB+!L0SEGC+ L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = C ,   offset =38
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = D ,   offset =40
    ( L0SEGA+!L0SEGB+!L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = E ,   offset =42
    ( L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = F ,   offset =44
    (!L0SEGA+!L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = G ,   offset =46
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = H ,   offset =48
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = I ,   offset =50
    (!L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = J ,   offset =52
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = K ,   offset =54
    (!L0SEGA+!L0SEGB+!L0SEGC+ L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = L ,   offset =56
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = M ,   offset =58
    (!L0SEGA+!L0SEGB+ L0SEGC+!L0SEGD),     (!L0SEGF+ L0SEGG+ L0SEGE),   //Char = N ,   offset =60
    (!L0SEGA+!L0SEGB+ L0SEGC+ L0SEGD),     (!L0SEGF+ L0SEGG+ L0SEGE),   //Char = O ,   offset =62
    ( L0SEGA+ L0SEGB+!L0SEGC+!L0SEGD),     ( L0SEGF+ L0SEGG+ L0SEGE),   //Char = P ,   offset =64
    ( L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = Q ,   offset =66
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+ L0SEGG+ L0SEGE),   //Char = R ,   offset =68
    ( L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     ( L0SEGF+ L0SEGG+!L0SEGE),   //Char = S ,   offset =70
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = T ,   offset =72
    (!L0SEGA+ L0SEGB+ L0SEGC+ L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = U ,   offset =74
    (!L0SEGA+ L0SEGB+!L0SEGC+!L0SEGD),     ( L0SEGF+!L0SEGG+!L0SEGE),   //Char = V ,   offset =76
    (!L0SEGA+ L0SEGB+ L0SEGC+!L0SEGD),     ( L0SEGF+!L0SEGG+ L0SEGE),   //Char = W ,   offset =78
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = X ,   offset =80
    (!L0SEGA+!L0SEGB+!L0SEGC+!L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = Y ,   offset =82
    ( L0SEGA+!L0SEGB+!L0SEGC+ L0SEGD),     (!L0SEGF+!L0SEGG+!L0SEGE),   //Char = Z ,   offset =84
#endif
#endif
};

void LCD_InstallCallbackLCD (uint8 ip, LCD_CALLBACK pCallback)
{
  if (pCallback != NULL) { pCallbackLCD = pCallback; }
  NVIC_SetIsr(INT_LCD,ip);
}

void LCD_Init (tLCD lcd, tLCD_FP lcd_fp, tLCD_BP lcd_bp, tLCD_CP lcd_cp)
{
  /* Enable LCD controller pins                                               */
  LCD_PENL     = lcd_fp.PENL;
  LCD_PENH     = lcd_fp.PENH;
  /* Enable LCD backplane controller pins                                     */
  LCD_BPENL    = lcd_bp.BPENL;
  LCD_BPENH    = lcd_bp.BPENH;
  /* Assign back planes  - 0 is BP1, 1 is BP2 etc                             */
  LCD_WF3TO0   = lcd_cp.WF0TO0;        
  LCD_WF7TO4   = lcd_cp.WF7TO4;        
  LCD_WF11TO8  = lcd_cp.WF11TO8;        
  LCD_WF15TO12 = lcd_cp.WF15TO12;        
  LCD_WF19TO16 = lcd_cp.WF19TO16;        
  LCD_WF23TO20 = lcd_cp.WF23TO20;        
  LCD_WF27TO24 = lcd_cp.WF27TO24;        
  LCD_WF31TO28 = lcd_cp.WF31TO28;        
  LCD_WF35TO32 = lcd_cp.WF35TO32;        
  LCD_WF39TO36 = lcd_cp.WF39TO36;        
  LCD_WF43TO40 = lcd_cp.WF43TO40;        
  LCD_WF47TO44 = lcd_cp.WF47TO44;        
  LCD_WF51TO48 = lcd_cp.WF51TO48;        
  LCD_WF55TO52 = lcd_cp.WF55TO52;        
  LCD_WF59TO56 = lcd_cp.WF59TO56;        
  LCD_WF63TO60 = lcd_cp.WF63TO60;        
  /* LCD controller control register setting                                  */
  LCD_AR       = lcd.AR;
  LCD_FDCR     = lcd.FDCR;
  LCD_GCR     |= lcd.GCR;
  /* LCD controller enable                                                    */
  LCD_GCR     |= LCD_GCR_LCDEN_MASK;
}

void LCD_GOTO (uint8 charPos) 
{ 
  LCD_CharPosition =  charPos; 
}

void LCD_Write_Char (uint8 c)
{
    unsigned char lbCounter, lbIndex;

    /* Only ASCII character if value not writeable write as @ */
    if (c >='a' && c <='z') c -= 32;  // UpperCase
    if (c < '0' || c > 'Z') c = ':';  // default value as space

    c -= '0';                   // Remove the offset to search in the ASCII table
    c *= _LCDTYPE;              // Compensate matrix offset
    lbCounter = _LCDTYPE;       // Number of writings to complete one char

    while (lbCounter--  && LCD_CharPosition < _LCD_CHARNUM  )
    {
        lbIndex = (unsigned char)(lbCounter + LCD_CharPosition * _LCDTYPE);                    
        *bpaPlace1[lbIndex] |= baAscii1[c + lbCounter];
    }
    LCD_CharPosition++;    //point to next Char position to write
}

void LCD_Delete_Char (uint8 pos)
{
    uint8 lbCounter, lbIndex;
    
    LCD_CharPosition = pos;
    lbCounter = _LCDTYPE;   //number of writings to complete one char
    while (lbCounter--  && LCD_CharPosition < _LCD_CHARNUM  )
    {
        lbIndex = (unsigned char)(lbCounter + LCD_CharPosition * _LCDTYPE); 
       *bpaPlace1[lbIndex] = 0;
    }
}

void LCD_Write_Segments(tLCD_CP lcd_cp )
{
  
  LCD_WF3TO0   = lcd_cp.WF0TO0;        
  LCD_WF7TO4   = lcd_cp.WF7TO4;        
  LCD_WF11TO8  = lcd_cp.WF11TO8;        
  LCD_WF15TO12 = lcd_cp.WF15TO12;        
  LCD_WF19TO16 = lcd_cp.WF19TO16;        
  LCD_WF23TO20 = lcd_cp.WF23TO20;        
  LCD_WF27TO24 = lcd_cp.WF27TO24;        
  LCD_WF31TO28 = lcd_cp.WF31TO28;        
  LCD_WF35TO32 = lcd_cp.WF35TO32;        
  LCD_WF39TO36 = lcd_cp.WF39TO36;        
  LCD_WF43TO40 = lcd_cp.WF43TO40;        
  LCD_WF47TO44 = lcd_cp.WF47TO44;        
  LCD_WF51TO48 = lcd_cp.WF51TO48;        
  LCD_WF55TO52 = lcd_cp.WF55TO52;        
  LCD_WF59TO56 = lcd_cp.WF59TO56;        
  LCD_WF63TO60 = lcd_cp.WF63TO60;        
}  

/******************************************************************************
 * interrupt functions definitions                                            *
 ******************************************************************************/
void LCD_isr (void) 
{
  register uint32 tmp;
  
  if (pCallbackLCD != (LCD_CALLBACK)NULL) 
  {
      
      tmp = (LCD_AR & (LCD_AR_BLINK_MASK|LCD_AR_ALT_MASK|LCD_AR_BLANK_MASK|    \
                       LCD_AR_BMODE_MASK|LCD_AR_BRATE_MASK) );
    
      tmp = (LCD_FDSR & LCD_FDSR_FDCNT_MASK );
    
      /* process LCD_FDSR_FDCF interrupt                                      */
      if (tmp == LCD_FDSR_FDCF_MASK)
      {
        pCallbackLCD (LCD_FDCF_CALLBACK);
        LCD_FDSR |= LCD_FDSR_FDCF_MASK;                            
      }

  } 
}
