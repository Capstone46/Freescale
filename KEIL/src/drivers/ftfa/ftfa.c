/*****************************************************************************
 * (c) Copyright 2010-2012, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      ftfa.c
 * @version   1.0.6.0
 * @date      Jan-18-2013
 * @brief     Flash memory module (FTFA) driver source file.
 *
 * Revision History:
 *  1.	15/01/2013   B34185   Initially written for Kinetis L
 ******************************************************************************/
#include "common.h"
#include "ftfa.h"


/***************************************************************************//*!
 * @brief   Read 1s section command.
 * @param   pSrc      - pointer to flash address of the first longword 
 *                      (longword aligned)
 * @param   NumLongs  - number of longwords to be verified
 * @param   MarginChoice - Read-1s margin level choice (fMARGIN_TYPE)
 * @return  EFCMD_OK  - read-1s was OK
 *          EFCMD_ACCESS  - an error occur (see RM for more details)
 *          EFCMD_COMPLETE - read-1s failed
 *          EFCMD_ALIGN - pSrc address is not 32-bit aligned
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__ARMCC_VERSION)
#pragma arm section code="CodeRelocateRam"
#endif
int FTFA_Read1sSection (unsigned long *pSrc, unsigned short NumLongs, \
                                  fMARGIN_TYPE MarginChoice)
{
  if ((uint32)pSrc%4)
    return EFCMD_ALIGN;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)); 

  if ((FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK) || \
      (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)) 
    { 
      FTFA_FSTAT |= FTFA_FSTAT_FPVIOL_MASK|FTFA_FSTAT_ACCERR_MASK; 
    }
  
  FTFA_FCCOB0 = FCMD_RD1SEC;
  FTFA_FCCOB1 = (uint8)((uint32)pSrc>> 16);
  FTFA_FCCOB2 = (uint8)((uint32)pSrc>>  8);
  FTFA_FCCOB3 = (uint8)((uint32)pSrc>>  0);
  FTFA_FCCOB4 = (uint8)(NumLongs >> 8);
  FTFA_FCCOB5 = (uint8)(NumLongs >> 0);
  FTFA_FCCOB6 = (uint8)MarginChoice;
  FTFA_FCCOB7 = (uint8)(0x00);
  
  FTFA_FSTAT |= FTFA_FSTAT_CCIF_MASK;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)) {}
  
  if (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)
    return EFCMD_ACCESS;
  if (FTFA_FSTAT & FTFA_FSTAT_MGSTAT0_MASK)
    return EFCMD_COMPLETE;
  return EFCMD_OK;
}

/***************************************************************************//*!
 * @brief   Function check previously programmed program flash longword.
 * @param   pSrc      - pointer to flash address (longword aligned)
 * @param   MarginChoice - Margin level choice (fMARGIN_TYPE, except NORMAL)
 * @param   ExpData  - pointer to expected data
 * @return  EFCMD_OK  - expected data match the content at given margin level
 *          EFCMD_ACCESS  - an error occur (see RM for more details)
 *          EFCMD_COMPLETE - comparisson failed at given margin level
 *          EFCMD_ALIGN - pSrc address is not longword aligned
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__ARMCC_VERSION)
#pragma arm section code="CodeRelocateRam"
#endif
int FTFA_ProgramCheck (unsigned long *pSrc, fMARGIN_TYPE MarginChoice,\
                                 unsigned long ExpData)
{
  if ((uint32)pSrc%4)
    return EFCMD_ALIGN;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)); 

  if ((FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK) || \
      (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)) 
    { 
      FTFA_FSTAT |= FTFA_FSTAT_FPVIOL_MASK|FTFA_FSTAT_ACCERR_MASK; 
    }
  
  FTFA_FCCOB0 = FCMD_PGMCHL;
  FTFA_FCCOB1 = (uint8)((uint32)pSrc>> 16);
  FTFA_FCCOB2 = (uint8)((uint32)pSrc>>  8);
  FTFA_FCCOB3 = (uint8)((uint32)pSrc>>  0);
  FTFA_FCCOB4 = (uint8)MarginChoice;
  FTFA_FCCOB5 = (uint8)(0x00);
  FTFA_FCCOB6 = (uint8)(0x00);
  FTFA_FCCOB7 = (uint8)(0x00);
  FTFA_FCCOB8 = (uint8)((uint32)ExpData>> 24);
  FTFA_FCCOB9 = (uint8)((uint32)ExpData>> 16);
  FTFA_FCCOBA = (uint8)((uint32)ExpData>> 8);
  FTFA_FCCOBB = (uint8)((uint32)ExpData>> 0);
  
  FTFA_FSTAT |= FTFA_FSTAT_CCIF_MASK;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)) {}
  
  if (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)
    return EFCMD_ACCESS;
  if (FTFA_FSTAT & FTFA_FSTAT_MGSTAT0_MASK)
    return EFCMD_COMPLETE;
  return EFCMD_OK;
}

/***************************************************************************//*!
 * @brief   Function allows the user to read from special-purpose memory.
 *          Special-purpose memory includes program flash IFR space (0x0000 - 
 *          0x00FF) and Version ID field (at address 0x0000-0x0007).
 * @param   pSrc      - pointer to flash address (longword aligned)
 * @param   pData  - pointer to long where read data to be stored 
 * @param   ResrcCode - resource select code (fRESOURCECODE_TYPE)
 * @return  EFCMD_OK  - command process succesfull(OK)
 *          EFCMD_ACCESS  - an error occur (see RM for more details)
 *          EFCMD_ALIGN - pSrc address is not longword aligned
 * @note    Implemented as function call. Placed into RAM. TBD!!!
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__ARMCC_VERSION)
#pragma arm section code="CodeRelocateRam"
#endif 
int FTFA_ReadResource (unsigned long *pSrc, unsigned long *pData,     \
                                 fRESOURCECODE_TYPE ResrcCode)
{
  if ((uint32)pSrc%4)
    return EFCMD_ALIGN;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)); 

  if ((FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK) || \
      (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)) 
    { 
      FTFA_FSTAT |= FTFA_FSTAT_FPVIOL_MASK|FTFA_FSTAT_ACCERR_MASK; 
    }
  
  FTFA_FCCOB0 = FCMD_RDRSRC;
  FTFA_FCCOB1 = (uint8)((uint32)pSrc>> 16);
  FTFA_FCCOB2 = (uint8)((uint32)pSrc>>  8);
  FTFA_FCCOB3 = (uint8)((uint32)pSrc>>  0);
  FTFA_FCCOB8 = (uint8)ResrcCode;
  
  FTFA_FSTAT |= FTFA_FSTAT_CCIF_MASK;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)) {} 
  
  if (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)
    return EFCMD_ACCESS;
  if (FTFA_FSTAT & FTFA_FSTAT_MGSTAT0_MASK)
    return EFCMD_COMPLETE;// no need

  *pData = (((uint32)FTFA_FCCOB4<<24)|((uint32)FTFA_FCCOB5<<16)|\
           ((uint32)FTFA_FCCOB6<<8)|((uint32)FTFA_FCCOB7<<0));  
  return EFCMD_OK;
}

/***************************************************************************//*!
 * @brief   Function provide program of four previously-erased bytes (Longword).
 * @param   pDst      - pointer to destimation address
 * @param   val       - long word to be written
 * @return  positive - number of written bytes (OK)
 *          EFCMD_ACCESS - an error occur (see RM for more details)
 *          EFCMD_COMPLETE - any error has been encountered during verify oper.
 *          EFCMD_ALIGN - pSrc address is not longword aligned
 *          EFCMD_PROTECTED - flash address points to a protected area
 * @note    Implemented as function call. Placed into RAM. Based on generic 
 *          flash command write sequence flowchart (see in RM)
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__ARMCC_VERSION)
#pragma arm section code="CodeRelocateRam"
#endif
int FTFA_ProgramLongword (unsigned long *pDst, unsigned long val) 
{
  if ((uint32)pDst%4)
    return EFCMD_ALIGN;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)); 

  if ((FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK) || \
      (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)) 
    { 
      FTFA_FSTAT |= FTFA_FSTAT_FPVIOL_MASK|FTFA_FSTAT_ACCERR_MASK; 
    }
  
  FTFA_FCCOB0 = FCMD_PGM4;
  FTFA_FCCOB1 = (uint8)((uint32)pDst>> 16);
  FTFA_FCCOB2 = (uint8)((uint32)pDst>>  8);
  FTFA_FCCOB3 = (uint8)((uint32)pDst>>  0);
  FTFA_FCCOB4 = (uint8)(val >> 24);
  FTFA_FCCOB5 = (uint8)(val >> 16);
  FTFA_FCCOB6 = (uint8)(val >>  8);
  FTFA_FCCOB7 = (uint8)(val >>  0);
  
  FTFA_FSTAT |= FTFA_FSTAT_CCIF_MASK;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)) {}
  
  if (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)
    return EFCMD_ACCESS;
  if (FTFA_FSTAT & FTFA_FSTAT_MGSTAT0_MASK)
    return EFCMD_COMPLETE;
  if (FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK)
    return EFCMD_PROTECTED;
  
  return sizeof(unsigned long);
}

/***************************************************************************//*!
 * @brief   Function provides erase of all addresses in a flash sector.
 * @param   pDst      - pointer to flash address in the sector to be erased
 * @return  EFCMD_OK - erases flash sector completes properly
 *          EFCMD_ACCESS - an error occur (see RM for more details)
 *          EFCMD_COMPLETE - any error has been encountered during verify oper.
 *          EFCMD_ALIGN - pSrc address is not longword aligned
 *          EFCMD_PROTECTED - selected program flash is protected
 *          EFCMD_SUSPENSION - suspension has been detected during erase sector  
 *               command execution (follow the process of resuming or aborting 
 *               in order to avoid mistakes with the next flash command),
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__ARMCC_VERSION)
#pragma arm section code="CodeRelocateRam"
#endif
int FTFA_EraseFlashSector (void *pDst) 
{
  if ((uint32)pDst%4)
    return EFCMD_ALIGN;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)); 

  if ((FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK) || \
      (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)) 
    { 
      FTFA_FSTAT |= FTFA_FSTAT_FPVIOL_MASK|FTFA_FSTAT_ACCERR_MASK; 
    }
  
  FTFA_FCCOB0 = FCMD_ERSSCR;
  FTFA_FCCOB1 = (uint8)((uint32)pDst>> 16);
  FTFA_FCCOB2 = (uint8)((uint32)pDst>>  8);
  FTFA_FCCOB3 = (uint8)((uint32)pDst>>  0);
  
  FTFA_FSTAT |= FTFA_FSTAT_CCIF_MASK;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)) {}
  
  if (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)
    return EFCMD_ACCESS;
  if (FTFA_FSTAT & FTFA_FSTAT_MGSTAT0_MASK)
    return EFCMD_COMPLETE;
  if (FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK)
    return EFCMD_PROTECTED;
  if (FTFA_FCNFG & FTFA_FCNFG_ERSSUSP_MASK)
    return EFCMD_SUSPENSION;
  return EFCMD_OK;
}

/***************************************************************************//*!
 * @brief   Function provides check if program flash blocks have been erased to
 *          specified read margin level.
 * @param   MarginChoice - Margin level choice 
 * @return  EFCMD_OK - read 1s all blocks operation has completed
 *          EFCMD_ACCESS - an invalid margin choice is specified
 *          EFCMD_COMPLETE - read-1s fails
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__ARMCC_VERSION)
#pragma arm section code="CodeRelocateRam"
#endif
int FTFA_Read1sAllBlocks (fMARGIN_TYPE MarginChoice)
{
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)); 

  if ((FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK) || \
      (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)) 
    { 
      FTFA_FSTAT |= FTFA_FSTAT_FPVIOL_MASK|FTFA_FSTAT_ACCERR_MASK; 
    }
  
  FTFA_FCCOB0 = FCMD_RD1ALL;
  FTFA_FCCOB1 = (uint8)MarginChoice;
  
  FTFA_FSTAT |= FTFA_FSTAT_CCIF_MASK;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)) {}
  
  if (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)
    return EFCMD_ACCESS;
  if (FTFA_FSTAT & FTFA_FSTAT_MGSTAT0_MASK)
    return EFCMD_COMPLETE;
  return EFCMD_OK;
}

/***************************************************************************//*!
 * @brief   Function provides read access to reserved 64-byte field located in 
 *          the program flash 0 IFR.
 * @param   RdIndex - record index (0x00-0x0F)
 *          pVal - pointer to long with returned 32-bit read once value
 * @return  EFCMD_OK - read once command successful
 *          EFCMD_ACCESS - read once command failed
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__ARMCC_VERSION)
#pragma arm section code="CodeRelocateRam"
#endif
int FTFA_ReadOnce (unsigned long RdIndex, unsigned long *pVal)
{
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)); 

  if ((FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK) || \
      (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)) 
    { 
      FTFA_FSTAT |= FTFA_FSTAT_FPVIOL_MASK|FTFA_FSTAT_ACCERR_MASK; 
    }
  
  FTFA_FCCOB0 = FCMD_RDONCE;
  FTFA_FCCOB1 = (uint8)RdIndex;
  
  FTFA_FSTAT |= FTFA_FSTAT_CCIF_MASK;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)) {}
  
  if (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)
    return EFCMD_ACCESS;

  *pVal = (((uint32)FTFA_FCCOB4<<24)|((uint32)FTFA_FCCOB5<<16)|\
           ((uint32)FTFA_FCCOB6<<8)|((uint32)FTFA_FCCOB7<<0));  
  return EFCMD_OK;
}

/***************************************************************************//*!
 * @brief   Function enables programming to reserved 64-byte field in the 
 *          program flash of IFR.
 * @param   RdIndex - record index (0x00-0x0F)
 *          Val -  32-bit value to be programed
 * @return  EFCMD_OK - program once command successful
 *          EFCMD_ACCESS - program once command failed (see RM for more details)
 *          EFCMD_COMPLETE - any errors have been encountered during the verify 
 *                      operation
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__ARMCC_VERSION)
#pragma arm section code="CodeRelocateRam"
#endif
int FTFA_ProgramOnce (unsigned long RdIndex, unsigned long val)
{
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)); 

  if ((FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK) || \
      (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)) 
    { 
      FTFA_FSTAT |= FTFA_FSTAT_FPVIOL_MASK|FTFA_FSTAT_ACCERR_MASK; 
    }
  
  FTFA_FCCOB0 = FCMD_PGMONCE;
  FTFA_FCCOB1 = (uint8)RdIndex;
  FTFA_FCCOB4 = (uint8)(val >> 24);
  FTFA_FCCOB5 = (uint8)(val >> 16);
  FTFA_FCCOB6 = (uint8)(val >>  8);
  FTFA_FCCOB7 = (uint8)(val >>  0);
  
  FTFA_FSTAT |= FTFA_FSTAT_CCIF_MASK;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)) {}
  
  if (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)
    return EFCMD_ACCESS;
  if (FTFA_FSTAT & FTFA_FSTAT_MGSTAT0_MASK)
    return EFCMD_COMPLETE;
  return EFCMD_OK;
}

/***************************************************************************//*!
 * @brief   Function provides erase of all flash memory.
 * @param   none.
 * @return  EFCMD_OK - erase all blocks successful
 *          EFCMD_ACCESS - command not available in current mode/security
 *          EFCMD_COMPLETE - any errors have been encountered during the verify 
 *                      operation
 *          EFCMD_PROTECTED - any region of the program flash memory is protected
 * @note    Implemented as function call. Placed into RAM.
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__ARMCC_VERSION)
#pragma arm section code="CodeRelocateRam"
#endif
int FTFA_EraseAllBloks (void)
{
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)); 

  if ((FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK) || \
      (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)) 
    { 
      FTFA_FSTAT |= FTFA_FSTAT_FPVIOL_MASK|FTFA_FSTAT_FPVIOL_MASK; 
    }
  
  FTFA_FCCOB0 = FCMD_ERSALL;
  
  FTFA_FSTAT |= FTFA_FSTAT_CCIF_MASK;
  
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)) {}
  
  if (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)
    return EFCMD_ACCESS;
  if (FTFA_FSTAT & FTFA_FSTAT_MGSTAT0_MASK)
    return EFCMD_COMPLETE;
  if (FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK)
    return EFCMD_PROTECTED;
  return EFCMD_OK;
}

/***************************************************************************//*!
 * @brief   Read long word from memory (uncommanded flash read).
 * @param   pSrc      - pointer to source address
 * @param   pDst      - pointer to destination address
 * @return  number of read bytes - if no errror occur
 *          EFCMD_RDCOLLISION - if read collision error occur (read data cannot 
 *                      be guaranteed)
 * @note    Implemented as function call.
 ******************************************************************************/
int FTFA_ReadLongword (unsigned long *pSrc, unsigned long *pDst) 
{
  while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK));
  *pDst = *pSrc;
  if (FTFA_FSTAT & FTFA_FSTAT_RDCOLERR_MASK)
    return EFCMD_RDCOLLISION;
  return sizeof(unsigned long);
}

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
int FTFA_ProgramAray (unsigned long *pDst, unsigned long *pSrc, int size)
{
  register int longwords = 0;
  register unsigned long *pUlongDst = pDst; 
  register unsigned long *pUlongSrc = pSrc;
  
  for (longwords = 0; longwords < size; longwords++)
  {
    if (FTFA_ProgramLongword (pUlongDst++, *(pUlongSrc++)) <= 0)
      return (longwords - size);
  }
  return longwords;
} 

/***************************************************************************//*!
 * @brief   Read long word array from NVM memory.
 * @param   pSrc      - pointer to starting address in the NVM memory
 * @param   pDst      - pointer to destination array (RAM)
 * @param   size      - array size in number of long words
 * @return  number of read long words
 * @note    Implemented as function call.
 ******************************************************************************/
int FTFA_ReadAray (unsigned long *pSrc, unsigned long *pDst, int size)
{
  register int longwords = 0;
  register unsigned long *pUlongDst = pDst; 
  register unsigned long *pUlongSrc = pSrc;
   
  for (longwords = 0; longwords < size; longwords++)
  {
    if (FTFA_ReadLongword (pUlongSrc++, pUlongDst++) <= 0)
      return (longwords - size);
  }
  return longwords;
}

/*****************************************************************************
 * End of module                                                             *
 *****************************************************************************/
