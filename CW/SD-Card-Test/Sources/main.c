/* ###################################################################
 **     Filename    : main.c
 **     Project     : SD-Card-Test
 **     Processor   : MKL46Z256VMC4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2014-11-21, 23:20, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */         
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "FAT1.h"
#include "SD1.h"
#include "SS1.h"
#include "TmDt1.h"
#include "UTIL1.h"
#include "SM1.h"
#include "WAIT1.h"
#include "TMOUT1.h"
#include "CS1.h"
#include "FRTOS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
//#include "FAT1.c"
//#include "SD1.c"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	/* For example: for(;;) { } */

	static FATFS fs;
	static FIL fp;

	//Initialise the SD Card
	//SD1_Init(&fs);
	
	
	for(;;) { 

		UINT bw;

		//Mount file system
		FAT1_mount(&fs, "SD1", 0); /* mount file system */
		
		// Create/Open a new file
		if (FAT1_open(&fp, "./test.txt", FA_CREATE_ALWAYS|FA_WRITE)!=FR_OK) { /* open file, will always create it if not already on disk */
			for(;;){} /* error! */
		}
		
		//Write to file
		if (FAT1_write(&fp, "Hello World!", sizeof("Hello World!")-1, &bw)!=FR_OK) { /* write string to file */
			for(;;){} /* error! */
		}

		//Close file
		(void)FAT1_close(&fp); /* close file */
		
		//Unmount file system
		FAT1_mount(NULL, "SD1", 0); /* unmount file system */

	}

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.3 [05.09]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
