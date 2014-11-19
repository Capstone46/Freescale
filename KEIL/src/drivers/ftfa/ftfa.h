/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      ftfa.h
 * @version   1.0.8.0
 * @date      Feb-22-2013
 * @brief     Flash memory module (FTFA) driver source file.
 *
 * Revision History:
 *  1.	15/01/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
/******************************************************************************
 *//*! @addtogroup ftfa_example0
 * @{
 * @par       Source code:
 * @include   ftfa0_test\ftfa_test.c
 * @par       Appconfig.h:
 * @include   ftfa0_test\appconfig.h   
 ******************************************************************************/
/*! @} End of ftfa_example0                                                     */
#ifndef __FTFA_H
#define __FTFA_H

/******************************************************************************
* Flash command type.
*
*//*! @addtogroup ftfa_cmd_list
* @{
*******************************************************************************/   
typedef enum    {                                                              
                  FCMD_RD1SEC=0x01,     ///< Read 1s Section Command
                  FCMD_PGMCHL=0x02,     ///< Program Check Command
                  FCMD_RDRSRC=0x03,     ///< Read Resource Command         
                  FCMD_PGM4=0x06,       ///< Program Longword Command
                  FCMD_ERSSCR=0x09,     ///< Erase Flash Sector Command
                  FCMD_RD1ALL=0x40,     ///< Read 1s All Blocks Command           
                  FCMD_RDONCE=0x41,     ///< Read Once Command
                  FCMD_PGMONCE=0x43,    ///< Program Once Command
                  FCMD_ERSALL=0x44,     ///< Erase All Blocks Command    
                  FCMD_VFYKEY=0x45,     ///< Verify Backdoor Access Key Command                                       
                } fCMD_TYPE;
/*! @} End of ftfa_cmd_list                                                   */

/******************************************************************************
* Flash margin level choise for read is section type.
*
*//*! @addtogroup ftfa_margin_list
* @{
*******************************************************************************/     
typedef enum    {                                                              
                  MARGIN_NORMAL=0x00,           ///< Use the 'normal' read level for 1s
                  MARGIN_USER=0x01,             ///< Apply the 'User' margin to the normal read-1 level
                  MARGIN_FACTORY=0x02,          ///< Apply the 'Factory' margin to the normal read-1 level
                } fMARGIN_TYPE;
/*! @} End of ftfa_margin_list                                                */

/******************************************************************************
* Flash Resource select codes type.
*
*//*! @addtogroup ftfa_resourcecode_list
* @{
*******************************************************************************/ 
typedef enum    {                                                              
                  PFLASH0_IFR=0x00,             ///< Program Flash 0 IFR
                  PFLASH0_VERID=0x01,           ///< Version ID                  
                } fRESOURCECODE_TYPE;
/*! @} End of ftfa_resourcecode_list                                          */

/******************************************************************************
* Flash command execution error code type.
*
*//*! @addtogroup ftfa_cmderr_list
* @{
*******************************************************************************/
/*! Flash command execution error codes type   */     
typedef enum    {                                                              
                  EFCMD_OK=1,                   ///< read-1s was OK
                  EFCMD_ACCESS=0,               ///< an error occur (see RM for more details)
                  EFCMD_COMPLETE=(-1),          ///< read-1s failed              
                  EFCMD_ALIGN=(-2),             ///< pSrc address is not 32-bit aligned
                  EFCMD_PROTECTED=(-3),         ///< flash address points to a protected area
                  EFCMD_SUSPENSION=(-4),        ///< suspension has been detected during erase sector command execution (follow the process of resuming or aborting in order to avoid mistakes with the next flash command)
                  EFCMD_RDCOLLISION=(-5),       ///< if read collision error occur (read data cannot be guaranteed                                     
                } fERRORCMD_TYPE;                
/*! @} End of ftfa_cmderr_list                                                */

/******************************************************************************
 * data type definitions                                                      *
 ******************************************************************************/

/******************************************************************************
* FTFA macro definitions
*
*//*! @addtogroup ftfa_macro
* @{
*******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
	#pragma diag_suppress=Pa082  
#elif defined(__ARMCC_VERSION)
	#pragma diag_suppress 82  
#endif

/***************************************************************************//*!
 * @brief   Macro controls whether the erase flash sector is going to be 
 *          suspended (if set during FCMD_ERSSCR command execution) or 
 *          suspension of FCMD_ERSSCR is aborted (if cleared after proper 
 *          suspension generated to avoid resuming of suspended FCMD_ERSSCR in
 *          the next flash command execution).
 * @param   x - 1 (ERSSUSP set) 
 * @param   x - 0 (ERSSUSP abort)
 * @return  none
 * @note    Implemented as inlined macro.
 ******************************************************************************/
#define FTFA_CtrlERSSUSP(x)                                                    \
{                                                                              \
  REG_SetVal(FTFA_FCNFG,FTFA_FCNFG_ERSSUSP,(x&0x01));                          \
}
/*! @} End of ftfa_macro                                                      */
                    
/******************************************************************************
* FTFA function definitions
*
*//*! @addtogroup ftfa_function
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Read 1s section command.
 * @param   pSrc      - pointer to flash address of the first longword 
 *                      (longword aligned)
 * @param   NumLongs  - number of longwords to be verified
 * @param   MarginChoice - Read-1s margin level choice @ref ftfa_margin_list
 * @return  @ref ftfa_cmderr_list 
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
extern int FTFA_Read1sSection (unsigned long *pSrc, unsigned short   \
                                         NumLongs, fMARGIN_TYPE MarginChoice);
                                         
/***************************************************************************//*!
 * @brief   Function check previously programmed program flash longword.
 * @param   pSrc      - pointer to flash address (longword aligned)
 * @param   MarginChoice - Read-1s margin level choice @ref ftfa_margin_list, except NORMAL)
 * @param   ExpData  - pointer to expected data
 * @return  @ref ftfa_cmderr_list 
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
extern int FTFA_ProgramCheck (unsigned long *pSrc, fMARGIN_TYPE      \
                                        MarginChoice, unsigned long ExpData);

/***************************************************************************//*!
 * @brief   Function allows the user to read from special-purpose memory.
 *          Special-purpose memory includes program flash IFR space (0x0000 - 
 *          0x00FF) and Version ID field (at address 0x0000-0x0007).
 * @param   pSrc      - pointer to flash address (longword aligned)
 * @param   pData  - pointer to long where read data to be stored 
 * @param   ResrcCode - resource select code (@ref ftfa_resourcecode_list)
 * @return  @ref ftfa_cmderr_list 
 * @note    Implemented as function call. Placed into RAM. TBD!!!
 ******************************************************************************/
extern int FTFA_ReadResource (unsigned long *pSrc, unsigned long     \
                                        *pData, fRESOURCECODE_TYPE ResrcCode);

/***************************************************************************//*!
 * @brief   Function provide program of four previously-erased bytes (Longword).
 * @param   pDst      - pointer to destimation address
 * @param   val       - long word to be written
 * @return  positive - number of written bytes (OK)
 *          or @ref ftfa_cmderr_list 
 * @note    Implemented as function call. Placed into RAM. Based on generic 
 *          flash command write sequence flowchart (see in RM)
 ******************************************************************************/
extern int FTFA_ProgramLongword (unsigned long *pDst, unsigned long val);

/***************************************************************************//*!
 * @brief   Function provides erase of all addresses in a flash sector.
 * @param   pDst      - pointer to flash address in the sector to be erased
 * @return  @ref ftfa_cmderr_list 
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
extern int FTFA_EraseFlashSector (void *pDst);

/***************************************************************************//*!
 * @brief   Function provides check if program flash blocks have been erased to
 *          specified read margin level.
 * @param   MarginChoice - Read-1s margin level choice @ref ftfa_margin_list
 * @return  @ref ftfa_cmderr_list 
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
extern int FTFA_Read1sAllBlocks (fMARGIN_TYPE MarginChoice);

/***************************************************************************//*!
 * @brief   Function provides read access to reserved 64-byte field located in 
 *          the program flash 0 IFR.
 * @param   RdIndex - record index (0x00-0x0F)
 * @param   pVal - pointer to long with returned 32-bit read once value
 * @return  @ref ftfa_cmderr_list
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
extern int FTFA_ReadOnce (unsigned long RdIndex, unsigned long *pVal);

/***************************************************************************//*!
 * @brief   Function enables programming to reserved 64-byte field in the 
 *          program flash of IFR.
 * @param   RdIndex - record index (0x00-0x0F)
 * @param   val -  32-bit value to be programed
 * @return  @ref ftfa_cmderr_list
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
extern int FTFA_ProgramOnce (unsigned long RdIndex, unsigned long val);

/***************************************************************************//*!
 * @brief   Function provides erase of all flash memory.
 * @return  @ref ftfa_cmderr_list 
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
extern int FTFA_EraseAllBloks (void);

/***************************************************************************//*!
 * @brief   Read long word from memory (uncommanded flash read).
 * @param   pSrc      - pointer to source address
 * @param   pDst      - pointer to destination address
 * @return  number of read bytes - if no errror occur
 *          @ref ftfa_cmderr_list 
 * @note    Implemented as function call.
 ******************************************************************************/
extern int FTFA_ReadLongword    (unsigned long *pSrc, unsigned long *pDst);

/***************************************************************************//*!
 * @brief   Program long word array into NVM memory.
 * @param   pDst      - pointer to starting address in the NVM memory
 * @param   pSrc      - pointer to source array (RAM) 
 * @param   size      - array size in number of long words
 * @return  positive - number of written long words
 *          negative - process failed (absolute value represetns number of 
 *                     longwords which were not programmed)
 * @note    Implemented as function call.
 ******************************************************************************/
extern int FTFA_ProgramAray (unsigned long *pDst, unsigned long *pSrc, int size);

/***************************************************************************//*!
 * @brief   Read long word array from NVM memory.
 * @param   pSrc      - pointer to starting address in the NVM memory
 * @param   pDst      - pointer to destination array (RAM)
 * @param   size      - array size in number of long words
 * @return  number of read long words
 * @note    Implemented as function call.
 ******************************************************************************/
extern int FTFA_ReadAray (unsigned long *pSrc, unsigned long *pDst, int size);

/*! @} End of ftfa_function                                                   */

#endif /* __FTFA_H */

