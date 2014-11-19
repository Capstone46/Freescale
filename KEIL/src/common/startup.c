/*****************************************************************************
 * (c) Copyright 2010, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      startup.c
 * @author    MSG
 * @version   1.0.1.0
 * @date      Jun-20-2013
 * @brief     Generic Kinetis startup code.
 *
 *
 * Revision History:
 *  1.	01/01/2010   AISG     Initially written
 *  2.	25/11/2013   B34185   Ported to Kinetis L (KL43 based)
 ******************************************************************************/
#include "common.h"

#if defined(__IAR_SYSTEMS_ICC__)
	#pragma section = ".data"
	#pragma section = ".data_init"
	#pragma section = ".bss"
	#pragma section = "CodeRelocate"
	#pragma section = "CodeRelocateRam"
#elif defined(__ARMCC_VERSION)
	#define MAKE_ADDRESS_WORD_ALIGNED(adr)		(adr+3)&(~0x3)	
#endif

/******************************************************************************
 * Common_startup function definition                                         *
 ******************************************************************************/
void common_startup(void)
{  
    /* Declare a counter we'll use in all of the copy loops */
    uint32 n;
 
    /* Addresses for VECTOR_TABLE come from the linker file */
#if defined(__IAR_SYSTEMS_ICC__)
	extern uint32 __VECTOR_TABLE[];
        extern uint32 __VECTOR_RAM[];
	/* Get the addresses for the .data section (initialized data section) */
	uint8* data_ram = __section_begin(".data");
	uint8* data_rom = __section_begin(".data_init");
	uint8* data_rom_end = __section_end(".data_init");
	/* Get the addresses for the .bss section (zero-initialized data) */
	uint8* bss_start = __section_begin(".bss");
	uint8* bss_end = __section_end(".bss");
	/* Get addresses for any code sections that need to be copied from ROM to RAM.
	 * The IAR tools have a predefined keyword that can be used to mark individual
	 * functions for execution from RAM. Add "__ramfunc" before the return type in
	 * the function prototype for any routines you need to execute from RAM instead 
	 * of ROM. ex: __ramfunc void foo(void);
	 */
	uint8* code_relocate_ram = __section_begin("CodeRelocateRam");
	uint8* code_relocate = __section_begin("CodeRelocate");
	uint8* code_relocate_end = __section_end("CodeRelocate");
#elif defined(__ARMCC_VERSION)
	extern uint32 Image$$ER_VECTOR_TABLE$$Base;
	extern uint32 Image$$ER_ROM$$Base, Image$$ER_ROM$$Limit;
	extern uint32 Image$$ER_RAM_VECTOR_TABLE$$Base, Image$$ER_RAM_VECTOR_TABLE$$Length, Image$$ER_RAM_VECTOR_TABLE$$Limit;
	extern uint32 Image$$ER_RAM_CODE$$Base, Image$$ER_RAM_CODE$$Length;
	extern uint32 Image$$ER_RAM_DATA$$Base, Image$$ER_RAM_DATA$$Length;
	extern uint32 Image$$ER_RAM_BSS$$ZI$$Base, Image$$ER_RAM_BSS$$ZI$$Length;
	extern uint32 Image$$ARM_LIB_STACK$$Base, Image$$ARM_LIB_STACK$$Limit;
	extern uint32 Image$$ARM_LIB_HEAP$$Base, Image$$ARM_LIB_HEAP$$Limit;
	
 		/* Get the addresses for the VECTOR_TABLE
		 VECTOR_TABLE address has to be 32-bit aligned 											*/
	uint8* __VECTOR_TABLE = (uint8*)&Image$$ER_VECTOR_TABLE$$Base;
 	
 	/* Get the addresses for the ram vector section (initialized data section)
 		 __VECTOR_RAM address has to be 32-bit aligned 											*/
 	uint8* __VECTOR_RAM;
	__VECTOR_RAM = (uint8*)&Image$$ER_RAM_VECTOR_TABLE$$Base;
	 uint8* __VECTOR_RAM_END = (uint8*)&Image$$ER_RAM_CODE$$Base;
 	
 	/* Test if vector table re-location is required
 		 VECTOR_TABLE address has to be 32-bit aligned 											*/
 	if ((uint8*)__VECTOR_RAM_END != __VECTOR_RAM)
 	{
 		__VECTOR_RAM = (uint8*)&Image$$ER_RAM_VECTOR_TABLE$$Base;
 	}
 	else 
 	{
 		__VECTOR_RAM = (uint8*)&Image$$ER_VECTOR_TABLE$$Base;
 	}
        
        /* Get the addresses for the .data section (initialized data section)
		 data_rom address has to be 32-bit aligned													*/
	uint32 data_temp0, data_temp1;
	uint8* data_ram;
	data_ram = (uint8*)&Image$$ER_RAM_DATA$$Base;
	data_temp0 = MAKE_ADDRESS_WORD_ALIGNED((uint32)&Image$$ER_ROM$$Limit+\
                                               (uint32)&Image$$ER_RAM_CODE$$Length);
  uint8* data_rom = (uint8*)data_temp0;
	data_temp1 = data_temp0+MAKE_ADDRESS_WORD_ALIGNED((uint32)&Image$$ER_RAM_DATA$$Length);
	uint8* data_rom_end = (uint8*)data_temp1;
	/* Get the addresses for the .bss section (zero-initialized data) */
	uint32 bss_temp0;
	uint8* bss_start;
	bss_start = (uint8*)&Image$$ER_RAM_BSS$$ZI$$Base;
	bss_temp0 = MAKE_ADDRESS_WORD_ALIGNED((uint32)&Image$$ER_RAM_BSS$$ZI$$Base+\
                                              (uint32)&Image$$ER_RAM_BSS$$ZI$$Length);
	uint8* bss_end = (uint8*)bss_temp0;
	/* Get addresses for any code sections that need to be copied from ROM to RAM.
	 * The IAR tools have a predefined keyword that can be used to mark individual
	 * functions for execution from RAM. Add "__ramfunc" before the return type in
	 * the function prototype for any routines you need to execute from RAM instead 
	 * of ROM. ex: __ramfunc void foo(void);
	 */
	uint32 code_relocate_temp0, code_relocate_temp1;
 	uint8* code_relocate_ram = (uint8*)&Image$$ER_RAM_CODE$$Base;
	code_relocate_temp0 = MAKE_ADDRESS_WORD_ALIGNED((uint32)&Image$$ER_ROM$$Limit);
 	uint8* code_relocate = (uint8*)code_relocate_temp0;
	code_relocate_temp1 = MAKE_ADDRESS_WORD_ALIGNED((uint32)&Image$$ER_ROM$$Limit+\
                                                        (uint32)&Image$$ER_RAM_CODE$$Length);
	uint8* code_relocate_end = (uint8*)code_relocate_temp1;
	
#endif

    /* Copy the vector table from pflash (_VECTOR_TABLE) to RAM (_VECTOR_RAM) */
    if (__VECTOR_RAM != __VECTOR_TABLE)
    {
        for (n = 0; n < 0x104; n++)
            __VECTOR_RAM[n] = __VECTOR_TABLE[n];
    }
    /* Point the VTOR to the new copy of the vector table */
    write_vtor((uint32)__VECTOR_TABLE);
    
    /* Copy initialized data from ROM to RAM */
    n = data_rom_end - data_rom;
    while (n--)
      *data_ram++ = *data_rom++;
    
    /* Clear the zero-initialized data section */
    n = bss_end - bss_start;
    while(n--)
      *bss_start++ = 0;
    
    /* Copy functions from ROM to RAM */
    n = code_relocate_end - code_relocate;
    while (n--)
      *code_relocate_ram++ = *code_relocate++;
}

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
