#line 1 "..\\..\\..\\..\\src\\drivers\\dac\\dac.c"



 








 
#line 1 "..\\..\\..\\..\\src\\common\\common.h"



 










 





 
typedef unsigned char		uint8;   
typedef unsigned short int	uint16;  
typedef unsigned long int	uint32;  

typedef char			int8;    
typedef short int	        int16;   
typedef int		        int32;   

typedef volatile int8		vint8;   
typedef volatile int16		vint16;  
typedef volatile int32		vint32;  

typedef volatile uint8		vuint8;   
typedef volatile uint16		vuint16;  
typedef volatile uint32		vuint32;  



 

















 



	__attribute__((used)) extern volatile uint8 SystemRegisterFile[32] __attribute__((section(".sysregfile")));




 
#line 1 "..\\..\\..\\..\\src\\projects\\frdm_projects\\frdm_accel_test\\appconfig.h"



 





 




 

 

 


 


 


 


  


 
#line 73 "..\\..\\..\\..\\src\\projects\\frdm_projects\\frdm_accel_test\\appconfig.h"


  

 
#line 85 "..\\..\\..\\..\\src\\projects\\frdm_projects\\frdm_accel_test\\appconfig.h"







 
extern void pit_isr(void);      
extern void portcd_isr (void);  









 

#line 69 "..\\..\\..\\..\\src\\common\\common.h"
#line 1 "..\\..\\..\\..\\src\\cpu\\device.h"



 








 







typedef enum IRQn
{
 
  NonMaskableInt_IRQn         = -14,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVCall_IRQn                 = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      
} IRQn_Type;
 

#line 1 "C:\\Keil\\ARM\\CMSIS\\core_cm0.h"
 




















 























 













 




 






 

 











#line 99 "C:\\Keil\\ARM\\CMSIS\\core_cm0.h"

 


#line 120 "C:\\Keil\\ARM\\CMSIS\\core_cm0.h"

#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
 
 





 









     
#line 27 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
     











#line 46 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
#line 216 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     



     






     
    
 



#line 241 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     







     










     











#line 305 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"






 
#line 122 "C:\\Keil\\ARM\\CMSIS\\core_cm0.h"
#line 1 "C:\\Keil\\ARM\\CMSIS\\core_cmInstr.h"
 




















 





 



 


 









 







 







 






 








 







 







 









 









 
static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 
static __inline __asm int32_t __REVSH(int32_t value)
{
  revsh r0, r0
  bx lr
}


#line 253 "C:\\Keil\\ARM\\CMSIS\\core_cmInstr.h"



#line 582 "C:\\Keil\\ARM\\CMSIS\\core_cmInstr.h"

   

#line 123 "C:\\Keil\\ARM\\CMSIS\\core_cm0.h"
#line 1 "C:\\Keil\\ARM\\CMSIS\\core_cmFunc.h"
 




















 





 



 


 





 
 






 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}







 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}







 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}







 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}







 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}







 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}







 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}







 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}







 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}







 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}







 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}
 

#line 257 "C:\\Keil\\ARM\\CMSIS\\core_cmFunc.h"


#line 293 "C:\\Keil\\ARM\\CMSIS\\core_cmFunc.h"


#line 605 "C:\\Keil\\ARM\\CMSIS\\core_cmFunc.h"

 


#line 124 "C:\\Keil\\ARM\\CMSIS\\core_cm0.h"








 
#line 149 "C:\\Keil\\ARM\\CMSIS\\core_cm0.h"

 
#line 158 "C:\\Keil\\ARM\\CMSIS\\core_cm0.h"

 





 






 





 


 
typedef union
{
  struct
  {

    uint32_t _reserved0:27;               





    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       

    uint32_t _reserved0:15;               





    uint32_t T:1;                         
    uint32_t IT:2;                        
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t FPCA:1;                      
    uint32_t _reserved0:29;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 






 


 
typedef struct
{
  volatile uint32_t ISER[1];                  
       uint32_t RESERVED0[31];
  volatile uint32_t ICER[1];                  
       uint32_t RSERVED1[31];
  volatile uint32_t ISPR[1];                  
       uint32_t RESERVED2[31];
  volatile uint32_t ICPR[1];                  
       uint32_t RESERVED3[31];
       uint32_t RESERVED4[64];
  volatile uint32_t IP[8];                    
}  NVIC_Type;

 






 


 
typedef struct
{
  volatile const  uint32_t CPUID;                    
  volatile uint32_t ICSR;                     
       uint32_t RESERVED0;
  volatile uint32_t AIRCR;                    
  volatile uint32_t SCR;                      
  volatile uint32_t CCR;                      
       uint32_t RESERVED1;
  volatile uint32_t SHP[2];                   
  volatile uint32_t SHCSR;                    
} SCB_Type;

 















 



























 















 









 






 



 






 


 
typedef struct
{
  volatile uint32_t CTRL;                     
  volatile uint32_t LOAD;                     
  volatile uint32_t VAL;                      
  volatile const  uint32_t CALIB;                    
} SysTick_Type;

 












 



 



 









 







 
 




 

 











 





 





 



 



 

 
 











 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}








 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}










 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));
}








 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}








 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}












 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( ((((uint32_t)(IRQn) & 0x0F)-8) >> 2) )] = (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( ((((uint32_t)(IRQn) & 0x0F)-8) >> 2) )] & ~(0xFF << ( (((uint32_t)(IRQn) ) & 0x03) * 8 ))) |
        (((priority << (8 - 2)) & 0xFF) << ( (((uint32_t)(IRQn) ) & 0x03) * 8 )); }
  else {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( ((uint32_t)(IRQn) >> 2) )] = (((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( ((uint32_t)(IRQn) >> 2) )] & ~(0xFF << ( (((uint32_t)(IRQn) ) & 0x03) * 8 ))) |
        (((priority << (8 - 2)) & 0xFF) << ( (((uint32_t)(IRQn) ) & 0x03) * 8 )); }
}













 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( ((((uint32_t)(IRQn) & 0x0F)-8) >> 2) )] >> ( (((uint32_t)(IRQn) ) & 0x03) * 8 ) ) >> (8 - 2)));  }  
  else {
    return((uint32_t)((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[ ( ((uint32_t)(IRQn) >> 2) )] >> ( (((uint32_t)(IRQn) ) & 0x03) * 8 ) ) >> (8 - 2)));  }  
}





 
static __inline void NVIC_SystemReset(void)
{
  __dsb(0xF);                                                     
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = ((0x5FA << 16)      |
                 (1UL << 2));
  __dsb(0xF);                                                      
  while(1);                                                     
}

 



 



 

#line 653 "C:\\Keil\\ARM\\CMSIS\\core_cm0.h"

 








#line 41 "..\\..\\..\\..\\src\\cpu\\device.h"

			#pragma anon_unions
#line 1 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"







































 








 




 

 



 





#line 67 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"


 

 





 




 

 
typedef enum {
  INT_Initial_Stack_Pointer    = 0,                 
  INT_Initial_Program_Counter  = 1,                 
  INT_NMI                      = 2,                 
  INT_Hard_Fault               = 3,                 
  INT_Reserved4                = 4,                 
  INT_Reserved5                = 5,                 
  INT_Reserved6                = 6,                 
  INT_Reserved7                = 7,                 
  INT_Reserved8                = 8,                 
  INT_Reserved9                = 9,                 
  INT_Reserved10               = 10,                
  INT_SVCall                   = 11,                
  INT_Reserved12               = 12,                
  INT_Reserved13               = 13,                
  INT_PendableSrvReq           = 14,                
  INT_SysTick                  = 15,                
  INT_DMA0                     = 16,                
  INT_DMA1                     = 17,                
  INT_DMA2                     = 18,                
  INT_DMA3                     = 19,                
  INT_Reserved20               = 20,                
  INT_FTFA                     = 21,                
  INT_PMC                      = 22,                
  INT_LLWU                     = 23,                
  INT_I2C0                     = 24,                
  INT_I2C1                     = 25,                
  INT_SPI0                     = 26,                
  INT_SPI1                     = 27,                
  INT_LPUART0                  = 28,                
  INT_LPUART1                  = 29,                
  INT_UART0_FLEXIO             = 30,                
  INT_ADC0                     = 31,                
  INT_CMP0                     = 32,                
  INT_TPM0                     = 33,                
  INT_TPM1                     = 34,                
  INT_TPM2                     = 35,                
  INT_RTC                      = 36,                
  INT_RTC_Seconds              = 37,                
  INT_PIT                      = 38,                
  INT_I2S0                     = 39,                
  INT_USB0                     = 40,                
  INT_DAC0                     = 41,                
  INT_Reserved42               = 42,                
  INT_Reserved43               = 43,                
  INT_LPTMR0                   = 44,                
  INT_LCD                      = 45,                
  INT_PORTA                    = 46,                
  INT_PORTCD                   = 47                 
} IRQInterruptIndex;



   




 




 




 


  #pragma push
  #pragma anon_unions
#line 168 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



 




 

 
typedef struct ADC_MemMap {
  uint32_t SC1[2];                                  
  uint32_t CFG1;                                    
  uint32_t CFG2;                                    
  uint32_t R[2];                                    
  uint32_t CV1;                                     
  uint32_t CV2;                                     
  uint32_t SC2;                                     
  uint32_t SC3;                                     
  uint32_t OFS;                                     
  uint32_t PG;                                      
  uint32_t MG;                                      
  uint32_t CLPD;                                    
  uint32_t CLPS;                                    
  uint32_t CLP4;                                    
  uint32_t CLP3;                                    
  uint32_t CLP2;                                    
  uint32_t CLP1;                                    
  uint32_t CLP0;                                    
  uint8_t RESERVED_0[4];
  uint32_t CLMD;                                    
  uint32_t CLMS;                                    
  uint32_t CLM4;                                    
  uint32_t CLM3;                                    
  uint32_t CLM2;                                    
  uint32_t CLM1;                                    
  uint32_t CLM0;                                    
} volatile *ADC_MemMapPtr;



 




 


 
#line 244 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 269 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 283 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 293 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 
#line 321 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 333 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 



 



 



 



 



 



 



 



 



 



 



 



 



 






   


 
 

 




 




 


 
 
#line 452 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 





   




   




 




 

 
typedef struct BP_MemMap {
  uint32_t CTRL;                                    
  uint8_t RESERVED_0[4];
  uint32_t COMP[2];                                 
  uint8_t RESERVED_1[4032];
  uint32_t PID4;                                    
  uint32_t PID5;                                    
  uint32_t PID6;                                    
  uint32_t PID7;                                    
  uint32_t PID0;                                    
  uint32_t PID1;                                    
  uint32_t PID2;                                    
  uint32_t PID3;                                    
  uint32_t CID0;                                    
  uint32_t CID1;                                    
  uint32_t CID2;                                    
  uint32_t CID3;                                    
} volatile *BP_MemMapPtr;



 




 


 
#line 521 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 




   


 
 

 




 




 


 
 
#line 575 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 




   




   




 




 

 
typedef struct CMP_MemMap {
  uint8_t CR0;                                      
  uint8_t CR1;                                      
  uint8_t FPR;                                      
  uint8_t SCR;                                      
  uint8_t DACCR;                                    
  uint8_t MUXCR;                                    
} volatile *CMP_MemMapPtr;



 




 


 
#line 625 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 647 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 664 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 
#line 681 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 689 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 698 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 
#line 728 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct CoreDebug_MemMap {
  union {                                           
    uint32_t base_DHCSR_Read;                         
    uint32_t base_DHCSR_Write;                        
  };
  uint32_t base_DCRSR;                              
  uint32_t base_DCRDR;                              
  uint32_t base_DEMCR;                              
} volatile *CoreDebug_MemMapPtr;



 




 


 








   




 




 




   


 
 

 




 




 


 
 








   




   




 




 

 
typedef struct DAC_MemMap {
  struct {                                          
    uint8_t DATL;                                     
    uint8_t DATH;                                     
  } DAT[2];
  uint8_t RESERVED_0[28];
  uint8_t SR;                                       
  uint8_t C0;                                       
  uint8_t C1;                                       
  uint8_t C2;                                       
} volatile *DAC_MemMapPtr;



 




 


 
#line 869 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 



 



 




 
#line 912 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 920 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 







   


 
 

 




 




 


 
 
#line 957 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 





   




   




 




 

 
typedef struct DMA_MemMap {
  uint8_t RESERVED_0[256];
  struct {                                          
    uint32_t SAR;                                     
    uint32_t DAR;                                     
    union {                                           
      uint32_t DSR_BCR;                                 
      struct {                                          
        uint8_t RESERVED_0[3];
        uint8_t DSR;                                      
      } DMA_DSR_ACCESS8BIT;
    };
    uint32_t DCR;                                     
  } DMA[4];
} volatile *DMA_MemMapPtr;



 




 


 








   




 




 

 



 



 
#line 1053 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 1093 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 
#line 1137 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 








   




   




 




 

 
typedef struct DMAMUX_MemMap {
  uint8_t CHCFG[4];                                 
} volatile *DMAMUX_MemMapPtr;



 




 


 




   




 




 

 
#line 1204 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 





 




   




   




 




 

 
typedef struct DWT_MemMap {
  uint32_t CTRL;                                    
  uint8_t RESERVED_0[24];
  uint32_t PCSR;                                    
  struct {                                          
    uint32_t COMP;                                    
    uint32_t MASK;                                    
    uint32_t FUNCTION;                                
    uint8_t RESERVED_0[4];
  } COMPARATOR[2];
} volatile *DWT_MemMapPtr;



 




 


 








   




 




 




   


 
 

 




 




 


 
 
#line 1331 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 






   




   




 




 

 
typedef struct FLEXIO_MemMap {
  uint32_t VERID;                                   
  uint32_t PARAM;                                   
  uint32_t CTRL;                                    
  uint8_t RESERVED_0[4];
  uint32_t SHIFTSTAT;                               
  uint32_t SHIFTERR;                                
  uint32_t TIMSTAT;                                 
  uint8_t RESERVED_1[4];
  uint32_t SHIFTSIEN;                               
  uint32_t SHIFTEIEN;                               
  uint32_t TIMIEN;                                  
  uint8_t RESERVED_2[4];
  uint32_t SHIFTSDEN;                               
  uint8_t RESERVED_3[76];
  uint32_t SHIFTCTL[4];                             
  uint8_t RESERVED_4[112];
  uint32_t SHIFTCFG[4];                             
  uint8_t RESERVED_5[240];
  uint32_t SHIFTBUF[4];                             
  uint8_t RESERVED_6[112];
  uint32_t SHIFTBUFBBS[4];                          
  uint8_t RESERVED_7[112];
  uint32_t SHIFTBUFBYS[4];                          
  uint8_t RESERVED_8[112];
  uint32_t SHIFTBUFBIS[4];                          
  uint8_t RESERVED_9[112];
  uint32_t TIMCTL[4];                               
  uint8_t RESERVED_10[112];
  uint32_t TIMCFG[4];                               
  uint8_t RESERVED_11[112];
  uint32_t TIMCMP[4];                               
} volatile *FLEXIO_MemMapPtr;



 




 


 
#line 1421 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 1446 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 1459 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 1470 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 



 



 



 



 
#line 1515 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 1524 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 



 
#line 1559 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 1580 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 






   


 
 

 




 




 


 
 
#line 1654 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 
#line 1665 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct FTFA_MemMap {
  uint8_t FSTAT;                                    
  uint8_t FCNFG;                                    
  uint8_t FSEC;                                     
  uint8_t FOPT;                                     
  uint8_t FCCOB3;                                   
  uint8_t FCCOB2;                                   
  uint8_t FCCOB1;                                   
  uint8_t FCCOB0;                                   
  uint8_t FCCOB7;                                   
  uint8_t FCCOB6;                                   
  uint8_t FCCOB5;                                   
  uint8_t FCCOB4;                                   
  uint8_t FCCOBB;                                   
  uint8_t FCCOBA;                                   
  uint8_t FCCOB9;                                   
  uint8_t FCCOB8;                                   
  uint8_t FPROT3;                                   
  uint8_t FPROT2;                                   
  uint8_t FPROT1;                                   
  uint8_t FPROT0;                                   
} volatile *FTFA_MemMapPtr;



 




 


 
#line 1740 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 1766 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 1775 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 1788 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 



 



 



 



 



 



 



 



 



 



 



 



 



 






   


 
 

 




 




 


 
 
#line 1900 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct GPIO_MemMap {
  uint32_t PDOR;                                    
  uint32_t PSOR;                                    
  uint32_t PCOR;                                    
  uint32_t PTOR;                                    
  uint32_t PDIR;                                    
  uint32_t PDDR;                                    
} volatile *GPIO_MemMapPtr;



 




 


 
#line 1947 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 



 



 



 



 



 






   


 
 

 

 

 

 

 




 




 


 
 
#line 2024 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2031 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2038 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2045 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2052 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct I2C_MemMap {
  uint8_t A1;                                       
  uint8_t F;                                        
  uint8_t C1;                                       
  uint8_t S;                                        
  uint8_t D;                                        
  uint8_t C2;                                       
  uint8_t FLT;                                      
  uint8_t RA;                                       
  uint8_t SMB;                                      
  uint8_t A2;                                       
  uint8_t SLTH;                                     
  uint8_t SLTL;                                     
  uint8_t S2;                                       
} volatile *I2C_MemMapPtr;



 




 


 
#line 2113 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 



 
#line 2139 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2156 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2173 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 
#line 2191 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2203 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 
#line 2224 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 







   


 
 

 

 




 




 


 
 
#line 2280 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2294 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct I2S_MemMap {
  uint32_t TCSR;                                    
  uint8_t RESERVED_0[4];
  uint32_t TCR2;                                    
  uint32_t TCR3;                                    
  uint32_t TCR4;                                    
  uint32_t TCR5;                                    
  uint8_t RESERVED_1[8];
  uint32_t TDR[1];                                  
  uint8_t RESERVED_2[60];
  uint32_t TMR;                                     
  uint8_t RESERVED_3[28];
  uint32_t RCSR;                                    
  uint8_t RESERVED_4[4];
  uint32_t RCR2;                                    
  uint32_t RCR3;                                    
  uint32_t RCR4;                                    
  uint32_t RCR5;                                    
  uint8_t RESERVED_5[8];
  uint32_t RDR[1];                                  
  uint8_t RESERVED_6[60];
  uint32_t RMR;                                     
  uint8_t RESERVED_7[28];
  uint32_t MCR;                                     
  uint32_t MDR;                                     
} volatile *I2S_MemMapPtr;



 




 


 
#line 2369 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 2415 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2433 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 




 
#line 2459 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2469 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 
#line 2508 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2526 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 




 
#line 2552 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2562 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 
#line 2578 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2585 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 
#line 2625 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 





   




   




 




 

 
typedef struct LCD_MemMap {
  uint32_t GCR;                                     
  uint32_t AR;                                      
  uint32_t FDCR;                                    
  uint32_t FDSR;                                    
  uint32_t PEN[2];                                  
  uint32_t BPEN[2];                                 
  union {                                           
    uint32_t WF[16];                                  
    uint8_t WF8B[64];                                 
  };
} volatile *LCD_MemMapPtr;



 




 


 
#line 2682 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 2735 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2747 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 2761 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 





 



 



 
#line 2968 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 3993 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 
#line 4105 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 







   




   




 




 

 
typedef struct LLWU_MemMap {
  uint8_t PE1;                                      
  uint8_t PE2;                                      
  uint8_t PE3;                                      
  uint8_t PE4;                                      
  uint8_t ME;                                       
  uint8_t F1;                                       
  uint8_t F2;                                       
  uint8_t F3;                                       
  uint8_t FILT1;                                    
  uint8_t FILT2;                                    
} volatile *LLWU_MemMapPtr;



 




 


 
#line 4166 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 4194 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4207 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4220 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4233 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4250 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4267 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4284 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4301 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4310 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4319 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 
#line 4353 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct LPTMR_MemMap {
  uint32_t CSR;                                     
  uint32_t PSR;                                     
  uint32_t CMR;                                     
  uint32_t CNR;                                     
} volatile *LPTMR_MemMapPtr;



 




 


 







   




 




 

 
#line 4427 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4436 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 






   


 
 

 




 




 


 
 







   




   




 




 

 
typedef struct LPUART_MemMap {
  uint32_t BAUD;                                    
  uint32_t STAT;                                    
  uint32_t CTRL;                                    
  uint32_t DATA;                                    
  uint32_t MATCH;                                   
} volatile *LPUART_MemMapPtr;



 




 


 








   




 




 

 
#line 4562 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4599 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4655 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4686 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4693 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 

 




 




 


 
 





 








   




   




 




 

 
typedef struct MCG_MemMap {
  uint8_t C1;                                       
  uint8_t C2;                                       
  uint8_t RESERVED_0[4];
  uint8_t S;                                        
  uint8_t RESERVED_1[1];
  uint8_t SC;                                       
  uint8_t RESERVED_2[11];
  uint8_t HCTRIM;                                   
  uint8_t HTTRIM;                                   
  uint8_t HFTRIM;                                   
  uint8_t RESERVED_3[1];
  uint8_t MC;                                       
  uint8_t LTRIMRNG;                                 
  uint8_t LFTRIM;                                   
  uint8_t LSTRIM;                                   
} volatile *MCG_MemMapPtr;



 




 


 
#line 4791 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 4814 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4824 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 





 



 



 



 



 





 
#line 4859 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 






   


 
 

 




 




 


 
 
#line 4902 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct MCM_MemMap {
  uint8_t RESERVED_0[8];
  uint16_t PLASC;                                   
  uint16_t PLAMC;                                   
  uint32_t PLACR;                                   
  uint8_t RESERVED_1[48];
  uint32_t CPO;                                     
} volatile *MCM_MemMapPtr;



 




 


 







   




 




 

 



 



 
#line 4987 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 4994 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 







   




   




 




 

 
typedef struct MTB_MemMap {
  uint32_t POSITION;                                
  uint32_t MASTER;                                  
  uint32_t FLOW;                                    
  uint32_t BASE;                                    
  uint8_t RESERVED_0[3824];
  uint32_t MODECTRL;                                
  uint8_t RESERVED_1[156];
  uint32_t TAGSET;                                  
  uint32_t TAGCLEAR;                                
  uint8_t RESERVED_2[8];
  uint32_t LOCKACCESS;                              
  uint32_t LOCKSTAT;                                
  uint32_t AUTHSTAT;                                
  uint32_t DEVICEARCH;                              
  uint8_t RESERVED_3[8];
  uint32_t DEVICECFG;                               
  uint32_t DEVICETYPID;                             
  uint32_t PERIPHID[8];                             
  uint32_t COMPID[4];                               
} volatile *MTB_MemMapPtr;



 




 


 
#line 5091 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 





 
#line 5128 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 5136 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 



 



 



 
#line 5169 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 



 






   


 
 

 




 




 


 
 
#line 5238 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 





   




   




 




 

 
typedef struct MTBDWT_MemMap {
  uint32_t CTRL;                                    
  uint8_t RESERVED_0[28];
  struct {                                          
    uint32_t COMP;                                    
    uint32_t MASK;                                    
    uint32_t FCT;                                     
    uint8_t RESERVED_0[4];
  } COMPARATOR[2];
  uint8_t RESERVED_1[448];
  uint32_t TBCTRL;                                  
  uint8_t RESERVED_2[3524];
  uint32_t DEVICECFG;                               
  uint32_t DEVICETYPID;                             
  uint32_t PERIPHID[8];                             
  uint32_t COMPID[4];                               
} volatile *MTBDWT_MemMapPtr;



 




 


 
#line 5301 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 5323 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 
#line 5345 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 5353 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 






   


 
 

 




 




 


 
 
#line 5415 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 








   




   




 




 

 
typedef struct NV_MemMap {
  uint8_t BACKKEY3;                                 
  uint8_t BACKKEY2;                                 
  uint8_t BACKKEY1;                                 
  uint8_t BACKKEY0;                                 
  uint8_t BACKKEY7;                                 
  uint8_t BACKKEY6;                                 
  uint8_t BACKKEY5;                                 
  uint8_t BACKKEY4;                                 
  uint8_t FPROT3;                                   
  uint8_t FPROT2;                                   
  uint8_t FPROT1;                                   
  uint8_t FPROT0;                                   
  uint8_t FSEC;                                     
  uint8_t FOPT;                                     
} volatile *NV_MemMapPtr;



 




 


 
#line 5485 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 



 



 



 



 



 



 



 



 



 



 



 



 
#line 5561 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 5572 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 
#line 5610 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct NVIC_MemMap {
  uint32_t ISER;                                    
  uint8_t RESERVED_0[124];
  uint32_t ICER;                                    
  uint8_t RESERVED_1[124];
  uint32_t ISPR;                                    
  uint8_t RESERVED_2[124];
  uint32_t ICPR;                                    
  uint8_t RESERVED_3[380];
  uint32_t IP[8];                                   
} volatile *NVIC_MemMapPtr;



 




 


 








   




 




 

 
#line 5739 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 5804 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 5869 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 5934 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 6031 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 
#line 6067 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 




   




   




 




 

 
typedef struct OSC_MemMap {
  uint8_t CR;                                       
} volatile *OSC_MemMapPtr;



 




 


 




   




 




 

 
#line 6135 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 




   




   




 




 

 
typedef struct PIT_MemMap {
  uint32_t MCR;                                     
  uint8_t RESERVED_0[220];
  uint32_t LTMR64H;                                 
  uint32_t LTMR64L;                                 
  uint8_t RESERVED_1[24];
  struct {                                          
    uint32_t LDVAL;                                   
    uint32_t CVAL;                                    
    uint32_t TCTRL;                                   
    uint32_t TFLG;                                    
  } CHANNEL[2];
} volatile *PIT_MemMapPtr;



 




 


 
#line 6213 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 




 



 



 



 



 
#line 6256 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 





   


 
 

 




 




 


 
 
#line 6294 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 







   




   




 




 

 
typedef struct PMC_MemMap {
  uint8_t LVDSC1;                                   
  uint8_t LVDSC2;                                   
  uint8_t REGSC;                                    
} volatile *PMC_MemMapPtr;



 




 


 






   




 




 

 
#line 6368 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 6378 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 6387 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 






   




   




 




 

 
typedef struct PORT_MemMap {
  uint32_t PCR[32];                                 
  uint32_t GPCLR;                                   
  uint32_t GPCHR;                                   
  uint8_t RESERVED_0[24];
  uint32_t ISFR;                                    
} volatile *PORT_MemMapPtr;



 




 


 







   




 




 

 
#line 6492 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 6499 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 6506 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 






   


 
 

 

 

 

 

 




 




 


 
 
#line 6577 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 6613 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 6649 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 6685 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 6721 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 








   




   




 




 

 
typedef struct RCM_MemMap {
  uint8_t SRS0;                                     
  uint8_t SRS1;                                     
  uint8_t RESERVED_0[2];
  uint8_t RPFC;                                     
  uint8_t RPFW;                                     
  uint8_t FM;                                       
  uint8_t MR;                                       
  uint8_t SSRS0;                                    
  uint8_t SSRS1;                                    
} volatile *RCM_MemMapPtr;



 




 


 
#line 6780 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 6806 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 6815 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 





 



 



 



 
#line 6844 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 6853 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 
#line 6885 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct RFSYS_MemMap {
  uint32_t REG[8];                                  
} volatile *RFSYS_MemMapPtr;



 




 


 




   




 




 

 
#line 6950 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 
#line 6982 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 




   




   




 




 

 
typedef struct ROM_MemMap {
  uint32_t ENTRY[3];                                
  uint32_t TABLEMARK;                               
  uint8_t RESERVED_0[4028];
  uint32_t SYSACCESS;                               
  uint32_t PERIPHID4;                               
  uint32_t PERIPHID5;                               
  uint32_t PERIPHID6;                               
  uint32_t PERIPHID7;                               
  uint32_t PERIPHID0;                               
  uint32_t PERIPHID1;                               
  uint32_t PERIPHID2;                               
  uint32_t PERIPHID3;                               
  uint32_t COMPID[4];                               
} volatile *ROM_MemMapPtr;



 




 


 
#line 7045 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 



 



 



 



 



 



 



 



 



 



 



 






   


 
 

 




 




 


 
 
#line 7149 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 





   




   




 




 

 
typedef struct RTC_MemMap {
  uint32_t TSR;                                     
  uint32_t TPR;                                     
  uint32_t TAR;                                     
  uint32_t TCR;                                     
  uint32_t CR;                                      
  uint32_t SR;                                      
  uint32_t LR;                                      
  uint32_t IER;                                     
} volatile *RTC_MemMapPtr;



 




 


 
#line 7204 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 



 



 



 
#line 7244 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7267 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7276 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7285 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7296 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 
#line 7328 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct SCB_MemMap {
  uint8_t RESERVED_0[8];
  uint32_t ACTLR;                                   
  uint8_t RESERVED_1[3316];
  uint32_t CPUID;                                   
  uint32_t ICSR;                                    
  uint32_t VTOR;                                    
  uint32_t AIRCR;                                   
  uint32_t SCR;                                     
  uint32_t CCR;                                     
  uint8_t RESERVED_2[4];
  uint32_t SHPR2;                                   
  uint32_t SHPR3;                                   
  uint32_t SHCSR;                                   
  uint8_t RESERVED_3[8];
  uint32_t DFSR;                                    
} volatile *SCB_MemMapPtr;



 




 


 
#line 7389 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 7417 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7431 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 
#line 7445 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7452 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 




 



 
#line 7468 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 


 
#line 7482 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 
#line 7517 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct SIM_MemMap {
  uint32_t SOPT1;                                   
  uint32_t SOPT1CFG;                                
  uint8_t RESERVED_0[4092];
  uint32_t SOPT2;                                   
  uint8_t RESERVED_1[4];
  uint32_t SOPT4;                                   
  uint32_t SOPT5;                                   
  uint8_t RESERVED_2[4];
  uint32_t SOPT7;                                   
  uint8_t RESERVED_3[8];
  uint32_t SDID;                                    
  uint8_t RESERVED_4[12];
  uint32_t SCGC4;                                   
  uint32_t SCGC5;                                   
  uint32_t SCGC6;                                   
  uint32_t SCGC7;                                   
  uint32_t CLKDIV1;                                 
  uint8_t RESERVED_5[4];
  uint32_t FCFG1;                                   
  uint32_t FCFG2;                                   
  uint8_t RESERVED_6[4];
  uint32_t UIDMH;                                   
  uint32_t UIDML;                                   
  uint32_t UIDL;                                    
  uint8_t RESERVED_7[156];
  uint32_t COPC;                                    
  uint32_t SRVCOP;                                  
} volatile *SIM_MemMapPtr;



 




 


 
#line 7598 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 7626 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7633 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7653 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7665 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7682 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7690 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7712 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7729 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7750 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7771 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 


 
#line 7781 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7789 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7796 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 
#line 7823 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 






   


 
 

 




 




 


 
 
#line 7870 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct SMC_MemMap {
  uint8_t PMPROT;                                   
  uint8_t PMCTRL;                                   
  uint8_t STOPCTRL;                                 
  uint8_t PMSTAT;                                   
} volatile *SMC_MemMapPtr;



 




 


 







   




 




 

 
#line 7935 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7944 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 7953 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 






   


 
 

 




 




 


 
 







   




   




 




 

 
typedef struct SPI_MemMap {
  uint8_t S;                                        
  uint8_t BR;                                       
  uint8_t C2;                                       
  uint8_t C1;                                       
  uint8_t ML;                                       
  uint8_t MH;                                       
  uint8_t DL;                                       
  uint8_t DH;                                       
  uint8_t RESERVED_0[2];
  uint8_t CI;                                       
  uint8_t C3;                                       
} volatile *SPI_MemMapPtr;



 




 


 
#line 8041 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 8073 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8080 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8097 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8114 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 



 
#line 8147 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8160 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 

 




 




 


 
 
#line 8194 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8205 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct SysTick_MemMap {
  uint32_t CSR;                                     
  uint32_t RVR;                                     
  uint32_t CVR;                                     
  uint32_t CALIB;                                   
} volatile *SysTick_MemMapPtr;



 




 


 







   




 




 

 
#line 8272 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 
#line 8288 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 







   




   




 




 

 
typedef struct TPM_MemMap {
  uint32_t SC;                                      
  uint32_t CNT;                                     
  uint32_t MOD;                                     
  struct {                                          
    uint32_t CnSC;                                    
    uint32_t CnV;                                     
  } CONTROLS[6];
  uint8_t RESERVED_0[20];
  uint32_t STATUS;                                  
  uint8_t RESERVED_1[28];
  uint32_t POL;                                     
  uint8_t RESERVED_2[16];
  uint32_t CONF;                                    
} volatile *TPM_MemMapPtr;



 




 


 
#line 8372 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 
#line 8402 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 
#line 8425 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 
#line 8444 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8457 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8482 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 

 

 




 




 


 
 
#line 8528 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8539 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8550 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 
#line 8558 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct UART_MemMap {
  uint8_t BDH;                                      
  uint8_t BDL;                                      
  uint8_t C1;                                       
  uint8_t C2;                                       
  uint8_t S1;                                       
  uint8_t S2;                                       
  uint8_t C3;                                       
  uint8_t D;                                        
  uint8_t MA1;                                      
  uint8_t MA2;                                      
  uint8_t C4;                                       
  uint8_t C5;                                       
  uint8_t ED;                                       
  uint8_t MODEM;                                    
  uint8_t IR;                                       
  uint8_t RESERVED_0[1];
  uint8_t PFIFO;                                    
  uint8_t CFIFO;                                    
  uint8_t SFIFO;                                    
  uint8_t TWFIFO;                                   
  uint8_t TCFIFO;                                   
  uint8_t RWFIFO;                                   
  uint8_t RCFIFO;                                   
  uint8_t RESERVED_1[1];
  uint8_t C7816;                                    
  uint8_t IE7816;                                   
  uint8_t IS7816;                                   
  uint8_t WP7816;                                   
  uint8_t WN7816;                                   
  uint8_t WF7816;                                   
  uint8_t ET7816;                                   
  uint8_t TL7816;                                   
  uint8_t RESERVED_2[26];
  uint8_t AP7816A_T0;                               
  uint8_t AP7816B_T0;                               
  union {                                           
    struct {                                          
      uint8_t WP7816A_T0;                               
      uint8_t WP7816B_T0;                               
    } TYPE0;
    struct {                                          
      uint8_t WP7816A_T1;                               
      uint8_t WP7816B_T1;                               
    } TYPE1;
  };
  uint8_t WGP7816_T1;                               
  uint8_t WP7816C_T1;                               
} volatile *UART_MemMapPtr;



 




 


 
#line 8678 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 





 



 
#line 8718 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8735 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8752 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8765 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8782 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 
#line 8804 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 




 




 
#line 8823 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 





 
#line 8840 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8851 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8862 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 



 
#line 8889 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8906 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 8923 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 
#line 8942 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 



 



 



 



 
#line 8977 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 






   


 
 

 




 




 


 
 
#line 9043 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




   




 




 

 
typedef struct USB_MemMap {
  uint8_t PERID;                                    
  uint8_t RESERVED_0[3];
  uint8_t IDCOMP;                                   
  uint8_t RESERVED_1[3];
  uint8_t REV;                                      
  uint8_t RESERVED_2[3];
  uint8_t ADDINFO;                                  
  uint8_t RESERVED_3[15];
  uint8_t CTL0;                                     
  uint8_t RESERVED_4[99];
  uint8_t ISTAT;                                    
  uint8_t RESERVED_5[3];
  uint8_t INTEN;                                    
  uint8_t RESERVED_6[3];
  uint8_t ERRSTAT;                                  
  uint8_t RESERVED_7[3];
  uint8_t ERREN;                                    
  uint8_t RESERVED_8[3];
  uint8_t STAT;                                     
  uint8_t RESERVED_9[3];
  uint8_t CTL1;                                     
  uint8_t RESERVED_10[3];
  uint8_t ADDR;                                     
  uint8_t RESERVED_11[3];
  uint8_t BDTPAGE1;                                 
  uint8_t RESERVED_12[3];
  uint8_t FRMNUML;                                  
  uint8_t RESERVED_13[3];
  uint8_t FRMNUMH;                                  
  uint8_t RESERVED_14[11];
  uint8_t BDTPAGE2;                                 
  uint8_t RESERVED_15[3];
  uint8_t BDTPAGE3;                                 
  uint8_t RESERVED_16[11];
  struct {                                          
    uint8_t ENDPT;                                    
    uint8_t RESERVED_0[3];
  } ENDPOINT[16];
  uint8_t USBCTRL;                                  
  uint8_t RESERVED_17[3];
  uint8_t OBSERVE;                                  
  uint8_t RESERVED_18[3];
  uint8_t CONTROL;                                  
  uint8_t RESERVED_19[3];
  uint8_t USBTRC0;                                  
  uint8_t RESERVED_20[7];
  uint8_t USBFRMADJUST;                             
  uint8_t RESERVED_21[43];
  uint8_t CLK_RECOVER_CTRL;                         
  uint8_t RESERVED_22[3];
  uint8_t CLK_RECOVER_IRC_EN;                       
  uint8_t RESERVED_23[15];
  uint8_t CLK_RECOVER_INT_EN;                       
  uint8_t RESERVED_24[7];
  uint8_t CLK_RECOVER_INT_STATUS;                   
} volatile *USB_MemMapPtr;



 




 


 
#line 9160 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

 



 



 



 


 


 
#line 9208 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 9223 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 9238 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 9253 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 9261 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 
#line 9272 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 



 



 



 



 



 
#line 9307 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 




 
#line 9319 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 


 
#line 9333 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 



 
#line 9344 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"
 




 


 





   


 
 

 




 




 


 
 
#line 9421 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 




   




   




 




 

 
typedef struct VREF_MemMap {
  uint8_t TRM;                                      
  uint8_t SC;                                       
} volatile *VREF_MemMapPtr;



 




 


 





   




 




 

 





 
#line 9496 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


 
 

 




 




 


 
 





   




   




 


  #pragma pop
#line 9548 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   




 




 

#line 9615 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"



   


#line 9629 "..\\..\\..\\..\\src\\cpu\\headers\\MKL43Z4.h"

 
#line 50 "..\\..\\..\\..\\src\\cpu\\device.h"




			#pragma no_anon_unions






#line 1 "C:\\Keil\\ARM\\CMSIS\\arm_math.h"



























 
































































































 




 








 









 



 






































































 



 



 



 


 






 



 





#line 1 "C:\\Keil\\ARM\\CMSIS\\core_cm0.h"
 




















 








#line 126 "C:\\Keil\\ARM\\CMSIS\\core_cm0.h"

#line 662 "C:\\Keil\\ARM\\CMSIS\\core_cm0.h"

#line 262 "C:\\Keil\\ARM\\CMSIS\\arm_math.h"





#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
 
 
 
 




 








 












#line 38 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"


  



    typedef unsigned int size_t;    
#line 54 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"




extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 193 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 209 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 232 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 247 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 270 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 502 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"



 

#line 269 "C:\\Keil\\ARM\\CMSIS\\arm_math.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"




 





 












 






   









 






#line 61 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"

#line 75 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"







   




 















 
#line 112 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"











 





extern __attribute__((__pcs__("aapcs"))) unsigned __ARM_dcmp4(double  , double  );
extern __attribute__((__pcs__("aapcs"))) unsigned __ARM_fcmp4(float  , float  );
    




 

extern __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_fpclassifyf(float  );
extern __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_fpclassify(double  );
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isfinitef(float __x)
{
    return (((*(unsigned *)&(__x)) >> 23) & 0xff) != 0xff;
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isfinite(double __x)
{
    return (((*(1 + (unsigned *)&(__x))) >> 20) & 0x7ff) != 0x7ff;
}
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isinff(float __x)
{
    return ((*(unsigned *)&(__x)) << 1) == 0xff000000;
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isinf(double __x)
{
    return (((*(1 + (unsigned *)&(__x))) << 1) == 0xffe00000) && ((*(unsigned *)&(__x)) == 0);
}
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_islessgreaterf(float __x, float __y)
{
    unsigned __f = __ARM_fcmp4(__x, __y) >> 28;
    return (__f == 8) || (__f == 2);  
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_islessgreater(double __x, double __y)
{
    unsigned __f = __ARM_dcmp4(__x, __y) >> 28;
    return (__f == 8) || (__f == 2);  
}
    


 

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnanf(float __x)
{
    return (0x7f800000 - ((*(unsigned *)&(__x)) & 0x7fffffff)) >> 31;
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnan(double __x)
{
    unsigned __xf = (*(1 + (unsigned *)&(__x))) | (((*(unsigned *)&(__x)) == 0) ? 0 : 1);
    return (0x7ff00000 - (__xf & 0x7fffffff)) >> 31;
}
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnormalf(float __x)
{
    unsigned __xe = ((*(unsigned *)&(__x)) >> 23) & 0xff;
    return (__xe != 0xff) && (__xe != 0);
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnormal(double __x)
{
    unsigned __xe = ((*(1 + (unsigned *)&(__x))) >> 20) & 0x7ff;
    return (__xe != 0x7ff) && (__xe != 0);
}
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_signbitf(float __x)
{
    return (*(unsigned *)&(__x)) >> 31;
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_signbit(double __x)
{
    return (*(1 + (unsigned *)&(__x))) >> 31;
}
     
     








#line 230 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"







   
  typedef float float_t;
  typedef double double_t;
#line 251 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"



extern const int math_errhandling;
#line 261 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"

extern __declspec(__nothrow) double acos(double  );
    
    
    
extern __declspec(__nothrow) double asin(double  );
    
    
    
    

extern __declspec(__nothrow) __attribute__((const)) double atan(double  );
    
    

extern __declspec(__nothrow) double atan2(double  , double  );
    
    
    
    

extern __declspec(__nothrow) double cos(double  );
    
    
    
    
extern __declspec(__nothrow) double sin(double  );
    
    
    
    

extern void __use_accurate_range_reduction(void);
    
    

extern __declspec(__nothrow) double tan(double  );
    
    
    
    

extern __declspec(__nothrow) double cosh(double  );
    
    
    
    
extern __declspec(__nothrow) double sinh(double  );
    
    
    
    
    

extern __declspec(__nothrow) __attribute__((const)) double tanh(double  );
    
    

extern __declspec(__nothrow) double exp(double  );
    
    
    
    
    

extern __declspec(__nothrow) double frexp(double  , int *  ) __attribute__((__nonnull__(2)));
    
    
    
    
    
    

extern __declspec(__nothrow) double ldexp(double  , int  );
    
    
    
    
extern __declspec(__nothrow) double log(double  );
    
    
    
    
    
extern __declspec(__nothrow) double log10(double  );
    
    
    
extern __declspec(__nothrow) double modf(double  , double *  ) __attribute__((__nonnull__(2)));
    
    
    
    

extern __declspec(__nothrow) double pow(double  , double  );
    
    
    
    
    
    
extern __declspec(__nothrow) double sqrt(double  );
    
    
    




    inline double _sqrt(double __x) { return sqrt(__x); }




    inline float _sqrtf(float __x) { return (float)sqrt(__x); }

    



 

extern __declspec(__nothrow) __attribute__((const)) double ceil(double  );
    
    
extern __declspec(__nothrow) __attribute__((const)) double fabs(double  );
    
    

extern __declspec(__nothrow) __attribute__((const)) double floor(double  );
    
    

extern __declspec(__nothrow) double fmod(double  , double  );
    
    
    
    
    

    









 



extern __declspec(__nothrow) double acosh(double  );
    

 
extern __declspec(__nothrow) double asinh(double  );
    

 
extern __declspec(__nothrow) double atanh(double  );
    

 
extern __declspec(__nothrow) double cbrt(double  );
    

 
inline __declspec(__nothrow) __attribute__((const)) double copysign(double __x, double __y)
    

 
{
    (*(1 + (unsigned *)&(__x))) = ((*(1 + (unsigned *)&(__x))) & 0x7fffffff) | ((*(1 + (unsigned *)&(__y))) & 0x80000000);
    return __x;
}
inline __declspec(__nothrow) __attribute__((const)) float copysignf(float __x, float __y)
    

 
{
    (*(unsigned *)&(__x)) = ((*(unsigned *)&(__x)) & 0x7fffffff) | ((*(unsigned *)&(__y)) & 0x80000000);
    return __x;
}
extern __declspec(__nothrow) double erf(double  );
    

 
extern __declspec(__nothrow) double erfc(double  );
    

 
extern __declspec(__nothrow) double expm1(double  );
    

 



    

 






#line 479 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"


extern __declspec(__nothrow) double hypot(double  , double  );
    




 
extern __declspec(__nothrow) int ilogb(double  );
    

 
extern __declspec(__nothrow) int ilogbf(float  );
    

 
extern __declspec(__nothrow) int ilogbl(long double  );
    

 







    

 





    



 





    



 





    

 





    



 





    



 





    



 





    

 





    

 





    


 

extern __declspec(__nothrow) double lgamma (double  );
    


 
extern __declspec(__nothrow) double log1p(double  );
    

 
extern __declspec(__nothrow) double logb(double  );
    

 
extern __declspec(__nothrow) float logbf(float  );
    

 
extern __declspec(__nothrow) long double logbl(long double  );
    

 
extern __declspec(__nothrow) double nextafter(double  , double  );
    


 
extern __declspec(__nothrow) float nextafterf(float  , float  );
    


 
extern __declspec(__nothrow) long double nextafterl(long double  , long double  );
    


 
extern __declspec(__nothrow) double nexttoward(double  , long double  );
    


 
extern __declspec(__nothrow) float nexttowardf(float  , long double  );
    


 
extern __declspec(__nothrow) long double nexttowardl(long double  , long double  );
    


 
extern __declspec(__nothrow) double remainder(double  , double  );
    

 
extern __declspec(__nothrow) __attribute__((const)) double rint(double  );
    

 
extern __declspec(__nothrow) double scalbln(double  , long int  );
    

 
extern __declspec(__nothrow) float scalblnf(float  , long int  );
    

 
extern __declspec(__nothrow) long double scalblnl(long double  , long int  );
    

 
extern __declspec(__nothrow) double scalbn(double  , int  );
    

 
extern __declspec(__nothrow) float scalbnf(float  , int  );
    

 
extern __declspec(__nothrow) long double scalbnl(long double  , int  );
    

 




    

 



 
extern __declspec(__nothrow) __attribute__((const)) float _fabsf(float);  
inline __declspec(__nothrow) __attribute__((const)) float fabsf(float __f) { return _fabsf(__f); }
extern __declspec(__nothrow) float sinf(float  );
extern __declspec(__nothrow) float cosf(float  );
extern __declspec(__nothrow) float tanf(float  );
extern __declspec(__nothrow) float acosf(float  );
extern __declspec(__nothrow) float asinf(float  );
extern __declspec(__nothrow) float atanf(float  );
extern __declspec(__nothrow) float atan2f(float  , float  );
extern __declspec(__nothrow) float sinhf(float  );
extern __declspec(__nothrow) float coshf(float  );
extern __declspec(__nothrow) float tanhf(float  );
extern __declspec(__nothrow) float expf(float  );
extern __declspec(__nothrow) float logf(float  );
extern __declspec(__nothrow) float log10f(float  );
extern __declspec(__nothrow) float powf(float  , float  );
extern __declspec(__nothrow) float sqrtf(float  );
extern __declspec(__nothrow) float ldexpf(float  , int  );
extern __declspec(__nothrow) float frexpf(float  , int *  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) __attribute__((const)) float ceilf(float  );
extern __declspec(__nothrow) __attribute__((const)) float floorf(float  );
extern __declspec(__nothrow) float fmodf(float  , float  );
extern __declspec(__nothrow) float modff(float  , float *  ) __attribute__((__nonnull__(2)));

 
 













 
__declspec(__nothrow) long double acosl(long double );
__declspec(__nothrow) long double asinl(long double );
__declspec(__nothrow) long double atanl(long double );
__declspec(__nothrow) long double atan2l(long double , long double );
__declspec(__nothrow) long double ceill(long double );
__declspec(__nothrow) long double cosl(long double );
__declspec(__nothrow) long double coshl(long double );
__declspec(__nothrow) long double expl(long double );
__declspec(__nothrow) long double fabsl(long double );
__declspec(__nothrow) long double floorl(long double );
__declspec(__nothrow) long double fmodl(long double , long double );
__declspec(__nothrow) long double frexpl(long double , int* ) __attribute__((__nonnull__(2)));
__declspec(__nothrow) long double ldexpl(long double , int );
__declspec(__nothrow) long double logl(long double );
__declspec(__nothrow) long double log10l(long double );
__declspec(__nothrow) long double modfl(long double  , long double *  ) __attribute__((__nonnull__(2)));
__declspec(__nothrow) long double powl(long double , long double );
__declspec(__nothrow) long double sinl(long double );
__declspec(__nothrow) long double sinhl(long double );
__declspec(__nothrow) long double sqrtl(long double );
__declspec(__nothrow) long double tanl(long double );
__declspec(__nothrow) long double tanhl(long double );





 
extern __declspec(__nothrow) float acoshf(float  );
__declspec(__nothrow) long double acoshl(long double );
extern __declspec(__nothrow) float asinhf(float  );
__declspec(__nothrow) long double asinhl(long double );
extern __declspec(__nothrow) float atanhf(float  );
__declspec(__nothrow) long double atanhl(long double );
__declspec(__nothrow) long double copysignl(long double , long double );
extern __declspec(__nothrow) float cbrtf(float  );
__declspec(__nothrow) long double cbrtl(long double );
extern __declspec(__nothrow) float erff(float  );
__declspec(__nothrow) long double erfl(long double );
extern __declspec(__nothrow) float erfcf(float  );
__declspec(__nothrow) long double erfcl(long double );
extern __declspec(__nothrow) float expm1f(float  );
__declspec(__nothrow) long double expm1l(long double );
extern __declspec(__nothrow) float log1pf(float  );
__declspec(__nothrow) long double log1pl(long double );
extern __declspec(__nothrow) float hypotf(float  , float  );
__declspec(__nothrow) long double hypotl(long double , long double );
extern __declspec(__nothrow) float lgammaf(float  );
__declspec(__nothrow) long double lgammal(long double );
extern __declspec(__nothrow) float remainderf(float  , float  );
__declspec(__nothrow) long double remainderl(long double , long double );
extern __declspec(__nothrow) float rintf(float  );
__declspec(__nothrow) long double rintl(long double );






 
extern __declspec(__nothrow) double exp2(double  );  
extern __declspec(__nothrow) float exp2f(float  );
__declspec(__nothrow) long double exp2l(long double );
extern __declspec(__nothrow) double fdim(double  , double  );
extern __declspec(__nothrow) float fdimf(float  , float  );
__declspec(__nothrow) long double fdiml(long double , long double );
#line 803 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"
extern __declspec(__nothrow) double fma(double  , double  , double  );
extern __declspec(__nothrow) float fmaf(float  , float  , float  );

inline __declspec(__nothrow) long double fmal(long double __x, long double __y, long double __z)     { return (long double)fma((double)__x, (double)__y, (double)__z); }


extern __declspec(__nothrow) __attribute__((const)) double fmax(double  , double  );
extern __declspec(__nothrow) __attribute__((const)) float fmaxf(float  , float  );
__declspec(__nothrow) long double fmaxl(long double , long double );
extern __declspec(__nothrow) __attribute__((const)) double fmin(double  , double  );
extern __declspec(__nothrow) __attribute__((const)) float fminf(float  , float  );
__declspec(__nothrow) long double fminl(long double , long double );
extern __declspec(__nothrow) double log2(double  );  
extern __declspec(__nothrow) float log2f(float  );
__declspec(__nothrow) long double log2l(long double );
extern __declspec(__nothrow) long lrint(double  );
extern __declspec(__nothrow) long lrintf(float  );

inline __declspec(__nothrow) long lrintl(long double __x)     { return lrint((double)__x); }


extern __declspec(__nothrow) long long llrint(double  );
extern __declspec(__nothrow) long long llrintf(float  );

inline __declspec(__nothrow) long long llrintl(long double __x)     { return llrint((double)__x); }


extern __declspec(__nothrow) long lround(double  );
extern __declspec(__nothrow) long lroundf(float  );

inline __declspec(__nothrow) long lroundl(long double __x)     { return lround((double)__x); }


extern __declspec(__nothrow) long long llround(double  );
extern __declspec(__nothrow) long long llroundf(float  );

inline __declspec(__nothrow) long long llroundl(long double __x)     { return llround((double)__x); }


extern __declspec(__nothrow) __attribute__((const)) double nan(const char * );
extern __declspec(__nothrow) __attribute__((const)) float nanf(const char * );

inline __declspec(__nothrow) __attribute__((const)) long double nanl(const char *__t)     { return (long double)nan(__t); }
#line 856 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"
extern __declspec(__nothrow) __attribute__((const)) double nearbyint(double  );
extern __declspec(__nothrow) __attribute__((const)) float nearbyintf(float  );
__declspec(__nothrow) long double nearbyintl(long double );
extern  double remquo(double  , double  , int * );
extern  float remquof(float  , float  , int * );

inline long double remquol(long double __x, long double __y, int *__q)     { return (long double)remquo((double)__x, (double)__y, __q); }


extern __declspec(__nothrow) __attribute__((const)) double round(double  );
extern __declspec(__nothrow) __attribute__((const)) float roundf(float  );
__declspec(__nothrow) long double roundl(long double );
extern __declspec(__nothrow) double tgamma(double  );  
extern __declspec(__nothrow) float tgammaf(float  );
__declspec(__nothrow) long double tgammal(long double );
extern __declspec(__nothrow) __attribute__((const)) double trunc(double  );
extern __declspec(__nothrow) __attribute__((const)) float truncf(float  );
__declspec(__nothrow) long double truncl(long double );






#line 1034 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"











#line 1250 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"





 
#line 270 "C:\\Keil\\ARM\\CMSIS\\arm_math.h"






  

 






  

 





  

 
   
   



  

 

  typedef enum
    {
      ARM_MATH_SUCCESS = 0,               
      ARM_MATH_ARGUMENT_ERROR = -1,       
      ARM_MATH_LENGTH_ERROR = -2,         
      ARM_MATH_SIZE_MISMATCH = -3,        
      ARM_MATH_NANINF = -4,               
      ARM_MATH_SINGULAR = -5,             
      ARM_MATH_TEST_FAILURE = -6          
    } arm_status;

  

 
  typedef int8_t q7_t;

  

 
  typedef int16_t q15_t;

  

 
  typedef int32_t q31_t;

  

 
  typedef int64_t q63_t;

  

 
  typedef float float32_t;

  

 
  typedef double float64_t;

  

 



  

 






   

 


#line 378 "C:\\Keil\\ARM\\CMSIS\\arm_math.h"


  

 
  static __inline q31_t clip_q63_to_q31(
					q63_t x)
  {
    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ?
      ((0x7FFFFFFF ^ ((q31_t) (x >> 63)))) : (q31_t) x;
  }

  

 
  static __inline q15_t clip_q63_to_q15(
					q63_t x)
  {
    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ?
      ((0x7FFF ^ ((q15_t) (x >> 63)))) : (q15_t) (x >> 15);
  }

  

 
  static __inline q7_t clip_q31_to_q7(
				      q31_t x)
  {
    return ((q31_t) (x >> 24) != ((q31_t) x >> 23)) ?
      ((0x7F ^ ((q7_t) (x >> 31)))) : (q7_t) x;
  }

  

 
  static __inline q15_t clip_q31_to_q15(
					q31_t x)
  {
    return ((q31_t) (x >> 16) != ((q31_t) x >> 15)) ?
      ((0x7FFF ^ ((q15_t) (x >> 31)))) : (q15_t) x;
  }

  

 

  static __inline q63_t mult32x64(
				  q63_t x,
				  q31_t y)
  {
    return ((((q63_t) (x & 0x00000000FFFFFFFF) * y) >> 32) +
            (((q63_t) (x >> 32) * y)));
  }






#line 458 "C:\\Keil\\ARM\\CMSIS\\arm_math.h"

  

 

  static __inline uint32_t arm_recip_q31(
					 q31_t in,
					 q31_t * dst,
					 q31_t * pRecipTable)
  {

    uint32_t out, tempVal;
    uint32_t index, i;
    uint32_t signBits;

    if(in > 0)
      {
	signBits = __clz(in) - 1;
      }
    else
      {
	signBits = __clz(-in) - 1;
      }

     
    in = in << signBits;

     
    index = (uint32_t) (in >> 24u);
    index = (index & 0x0000003F);

     
    out = pRecipTable[index];

     
     
    for (i = 0u; i < 2u; i++)
      {
	tempVal = (q31_t) (((q63_t) in * out) >> 31u);
	tempVal = 0x7FFFFFFF - tempVal;
	 
	
	out = (q31_t) clip_q63_to_q31(((q63_t) out * tempVal) >> 30u);
      }

     
    *dst = out;

     
    return (signBits + 1u);

  }

  

 
  static __inline uint32_t arm_recip_q15(
					 q15_t in,
					 q15_t * dst,
					 q15_t * pRecipTable)
  {

    uint32_t out = 0, tempVal = 0;
    uint32_t index = 0, i = 0;
    uint32_t signBits = 0;

    if(in > 0)
      {
	signBits = __clz(in) - 17;
      }
    else
      {
	signBits = __clz(-in) - 17;
      }

     
    in = in << signBits;

     
    index = in >> 8;
    index = (index & 0x0000003F);

     
    out = pRecipTable[index];

     
     
    for (i = 0; i < 2; i++)
      {
	tempVal = (q15_t) (((q31_t) in * out) >> 15);
	tempVal = 0x7FFF - tempVal;
	 
	out = (q15_t) (((q31_t) out * tempVal) >> 14);
      }

     
    *dst = out;

     
    return (signBits + 1);

  }


  

 


  static __inline q31_t __SSAT(
			       q31_t x,
			       uint32_t y)
  {
    int32_t posMax, negMin;
    uint32_t i;

    posMax = 1;
    for (i = 0; i < (y - 1); i++)
      {
	posMax = posMax * 2;
      }

    if(x > 0)
      {
	posMax = (posMax - 1);

	if(x > posMax)
	  {
	    x = posMax;
	  }
      }
    else
      {
	negMin = -posMax;

	if(x < negMin)
	  {
	    x = negMin;
	  }
      }
    return (x);


  }





  

 


  

 
  static __inline q31_t __QADD8(
				q31_t x,
				q31_t y)
  {

    q31_t sum;
    q7_t r, s, t, u;

    r = (char) x;
    s = (char) y;

    r = __SSAT((q31_t) (r + s), 8);
    s = __SSAT(((q31_t) (((x << 16) >> 24) + ((y << 16) >> 24))), 8);
    t = __SSAT(((q31_t) (((x << 8) >> 24) + ((y << 8) >> 24))), 8);
    u = __SSAT(((q31_t) ((x >> 24) + (y >> 24))), 8);

    sum = (((q31_t) u << 24) & 0xFF000000) | (((q31_t) t << 16) & 0x00FF0000) |
      (((q31_t) s << 8) & 0x0000FF00) | (r & 0x000000FF);

    return sum;

  }

  

 
  static __inline q31_t __QSUB8(
				q31_t x,
				q31_t y)
  {

    q31_t sum;
    q31_t r, s, t, u;

    r = (char) x;
    s = (char) y;

    r = __SSAT((r - s), 8);
    s = __SSAT(((q31_t) (((x << 16) >> 24) - ((y << 16) >> 24))), 8) << 8;
    t = __SSAT(((q31_t) (((x << 8) >> 24) - ((y << 8) >> 24))), 8) << 16;
    u = __SSAT(((q31_t) ((x >> 24) - (y >> 24))), 8) << 24;

    sum =
      (u & 0xFF000000) | (t & 0x00FF0000) | (s & 0x0000FF00) | (r & 0x000000FF);

    return sum;
  }

  

 

  

 
  static __inline q31_t __QADD16(
				 q31_t x,
				 q31_t y)
  {

    q31_t sum;
    q31_t r, s;

    r = (short) x;
    s = (short) y;

    r = __SSAT(r + s, 16);
    s = __SSAT(((q31_t) ((x >> 16) + (y >> 16))), 16) << 16;

    sum = (s & 0xFFFF0000) | (r & 0x0000FFFF);

    return sum;

  }

  

 
  static __inline q31_t __SHADD16(
				  q31_t x,
				  q31_t y)
  {

    q31_t sum;
    q31_t r, s;

    r = (short) x;
    s = (short) y;

    r = ((r >> 1) + (s >> 1));
    s = ((q31_t) ((x >> 17) + (y >> 17))) << 16;

    sum = (s & 0xFFFF0000) | (r & 0x0000FFFF);

    return sum;

  }

  

 
  static __inline q31_t __QSUB16(
				 q31_t x,
				 q31_t y)
  {

    q31_t sum;
    q31_t r, s;

    r = (short) x;
    s = (short) y;

    r = __SSAT(r - s, 16);
    s = __SSAT(((q31_t) ((x >> 16) - (y >> 16))), 16) << 16;

    sum = (s & 0xFFFF0000) | (r & 0x0000FFFF);

    return sum;
  }

  

 
  static __inline q31_t __SHSUB16(
				  q31_t x,
				  q31_t y)
  {

    q31_t diff;
    q31_t r, s;

    r = (short) x;
    s = (short) y;

    r = ((r >> 1) - (s >> 1));
    s = (((x >> 17) - (y >> 17)) << 16);

    diff = (s & 0xFFFF0000) | (r & 0x0000FFFF);

    return diff;
  }

  

 
  static __inline q31_t __QASX(
			       q31_t x,
			       q31_t y)
  {

    q31_t sum = 0;

    sum = ((sum + clip_q31_to_q15((q31_t) ((short) (x >> 16) + (short) y))) << 16) +
      clip_q31_to_q15((q31_t) ((short) x - (short) (y >> 16)));

    return sum;
  }

  

 
  static __inline q31_t __SHASX(
				q31_t x,
				q31_t y)
  {

    q31_t sum;
    q31_t r, s;

    r = (short) x;
    s = (short) y;

    r = ((r >> 1) - (y >> 17));
    s = (((x >> 17) + (s >> 1)) << 16);

    sum = (s & 0xFFFF0000) | (r & 0x0000FFFF);

    return sum;
  }


  

 
  static __inline q31_t __QSAX(
			       q31_t x,
			       q31_t y)
  {

    q31_t sum = 0;

    sum = ((sum + clip_q31_to_q15((q31_t) ((short) (x >> 16) - (short) y))) << 16) +
      clip_q31_to_q15((q31_t) ((short) x + (short) (y >> 16)));

    return sum;
  }

  

 
  static __inline q31_t __SHSAX(
				q31_t x,
				q31_t y)
  {

    q31_t sum;
    q31_t r, s;

    r = (short) x;
    s = (short) y;

    r = ((r >> 1) + (y >> 17));
    s = (((x >> 17) - (s >> 1)) << 16);

    sum = (s & 0xFFFF0000) | (r & 0x0000FFFF);

    return sum;
  }

  

 
  static __inline q31_t __SMUSDX(
				 q31_t x,
				 q31_t y)
  {

    return ((q31_t)(((short) x * (short) (y >> 16)) -
		    ((short) (x >> 16) * (short) y)));
  }

  

 
  static __inline q31_t __SMUADX(
				 q31_t x,
				 q31_t y)
  {

    return ((q31_t)(((short) x * (short) (y >> 16)) +
		    ((short) (x >> 16) * (short) y)));
  }

  

 
  static __inline q31_t __QADD(
			       q31_t x,
			       q31_t y)
  {
    return clip_q63_to_q31((q63_t) x + y);
  }

  

 
  static __inline q31_t __QSUB(
			       q31_t x,
			       q31_t y)
  {
    return clip_q63_to_q31((q63_t) x - y);
  }

  

 
  static __inline q31_t __SMLAD(
				q31_t x,
				q31_t y,
				q31_t sum)
  {

    return (sum + ((short) (x >> 16) * (short) (y >> 16)) +
            ((short) x * (short) y));
  }

  

 
  static __inline q31_t __SMLADX(
				 q31_t x,
				 q31_t y,
				 q31_t sum)
  {

    return (sum + ((short) (x >> 16) * (short) (y)) +
            ((short) x * (short) (y >> 16)));
  }

  

 
  static __inline q31_t __SMLSDX(
				 q31_t x,
				 q31_t y,
				 q31_t sum)
  {

    return (sum - ((short) (x >> 16) * (short) (y)) +
            ((short) x * (short) (y >> 16)));
  }

  

 
  static __inline q63_t __SMLALD(
				 q31_t x,
				 q31_t y,
				 q63_t sum)
  {

    return (sum + ((short) (x >> 16) * (short) (y >> 16)) +
            ((short) x * (short) y));
  }

  

 
  static __inline q63_t __SMLALDX(
				  q31_t x,
				  q31_t y,
				  q63_t sum)
  {

    return (sum + ((short) (x >> 16) * (short) y)) +
      ((short) x * (short) (y >> 16));
  }

  

 
  static __inline q31_t __SMUAD(
				q31_t x,
				q31_t y)
  {

    return (((x >> 16) * (y >> 16)) +
            (((x << 16) >> 16) * ((y << 16) >> 16)));
  }

  

 
  static __inline q31_t __SMUSD(
				q31_t x,
				q31_t y)
  {

    return (-((x >> 16) * (y >> 16)) +
            (((x << 16) >> 16) * ((y << 16) >> 16)));
  }







  

 
  typedef struct
  {
    uint16_t numTaps;         
    q7_t *pState;             
    q7_t *pCoeffs;            
  } arm_fir_instance_q7;

  

 
  typedef struct
  {
    uint16_t numTaps;          
    q15_t *pState;             
    q15_t *pCoeffs;            
  } arm_fir_instance_q15;

  

 
  typedef struct
  {
    uint16_t numTaps;          
    q31_t *pState;             
    q31_t *pCoeffs;            
  } arm_fir_instance_q31;

  

 
  typedef struct
  {
    uint16_t numTaps;      
    float32_t *pState;     
    float32_t *pCoeffs;    
  } arm_fir_instance_f32;


  






 
  void arm_fir_q7(
		  const arm_fir_instance_q7 * S,
		   q7_t * pSrc,
		  q7_t * pDst,
		  uint32_t blockSize);


  







 
  void arm_fir_init_q7(
		       arm_fir_instance_q7 * S,
		       uint16_t numTaps,
		       q7_t * pCoeffs,
		       q7_t * pState,
		       uint32_t blockSize);


  






 
  void arm_fir_q15(
		   const arm_fir_instance_q15 * S,
		    q15_t * pSrc,
		   q15_t * pDst,
		   uint32_t blockSize);

  






 
  void arm_fir_fast_q15(
			const arm_fir_instance_q15 * S,
			 q15_t * pSrc,
			q15_t * pDst,
			uint32_t blockSize);

  








 
   
       arm_status arm_fir_init_q15(
			      arm_fir_instance_q15 * S,
			      uint16_t numTaps,
			      q15_t * pCoeffs,
			      q15_t * pState,
			      uint32_t blockSize);

  






 
  void arm_fir_q31(
		   const arm_fir_instance_q31 * S,
		    q31_t * pSrc,
		   q31_t * pDst,
		   uint32_t blockSize);

  






 
  void arm_fir_fast_q31(
			const arm_fir_instance_q31 * S,
			 q31_t * pSrc,
			q31_t * pDst,
			uint32_t blockSize);

  







 
  void arm_fir_init_q31(
			arm_fir_instance_q31 * S,
			uint16_t numTaps,
			q31_t * pCoeffs,
			q31_t * pState,
			uint32_t blockSize);

  






 
  void arm_fir_f32(
		   const arm_fir_instance_f32 * S,
		    float32_t * pSrc,
		   float32_t * pDst,
		   uint32_t blockSize);

  







 
  void arm_fir_init_f32(
			arm_fir_instance_f32 * S,
			uint16_t numTaps,
			float32_t * pCoeffs,
			float32_t * pState,
			uint32_t blockSize);


  

 
  typedef struct
  {
    int8_t numStages;          
    q15_t *pState;             
    q15_t *pCoeffs;            
    int8_t postShift;          

  } arm_biquad_casd_df1_inst_q15;


  

 
  typedef struct
  {
    uint32_t numStages;       
    q31_t *pState;            
    q31_t *pCoeffs;           
    uint8_t postShift;        

  } arm_biquad_casd_df1_inst_q31;

  

 
  typedef struct
  {
    uint32_t numStages;          
    float32_t *pState;           
    float32_t *pCoeffs;          


  } arm_biquad_casd_df1_inst_f32;



  






 

  void arm_biquad_cascade_df1_q15(
				  const arm_biquad_casd_df1_inst_q15 * S,
				   q15_t * pSrc,
				  q15_t * pDst,
				  uint32_t blockSize);

  







 

  void arm_biquad_cascade_df1_init_q15(
				       arm_biquad_casd_df1_inst_q15 * S,
				       uint8_t numStages,
				       q15_t * pCoeffs,
				       q15_t * pState,
				       int8_t postShift);


  






 

  void arm_biquad_cascade_df1_fast_q15(
				       const arm_biquad_casd_df1_inst_q15 * S,
				        q15_t * pSrc,
				       q15_t * pDst,
				       uint32_t blockSize);


  






 

  void arm_biquad_cascade_df1_q31(
				  const arm_biquad_casd_df1_inst_q31 * S,
				   q31_t * pSrc,
				  q31_t * pDst,
				  uint32_t blockSize);

  






 

  void arm_biquad_cascade_df1_fast_q31(
				       const arm_biquad_casd_df1_inst_q31 * S,
				        q31_t * pSrc,
				       q31_t * pDst,
				       uint32_t blockSize);

  







 

  void arm_biquad_cascade_df1_init_q31(
				       arm_biquad_casd_df1_inst_q31 * S,
				       uint8_t numStages,
				       q31_t * pCoeffs,
				       q31_t * pState,
				       int8_t postShift);

  






 

  void arm_biquad_cascade_df1_f32(
				  const arm_biquad_casd_df1_inst_f32 * S,
				   float32_t * pSrc,
				  float32_t * pDst,
				  uint32_t blockSize);

  






 

  void arm_biquad_cascade_df1_init_f32(
				       arm_biquad_casd_df1_inst_f32 * S,
				       uint8_t numStages,
				       float32_t * pCoeffs,
				       float32_t * pState);


  

 

  typedef struct
  {
    uint16_t numRows;      
    uint16_t numCols;      
    float32_t *pData;      
  } arm_matrix_instance_f32;

  

 

  typedef struct
  {
    uint16_t numRows;      
    uint16_t numCols;      
    q15_t *pData;          

  } arm_matrix_instance_q15;

  

 

  typedef struct
  {
    uint16_t numRows;      
    uint16_t numCols;      
    q31_t *pData;          

  } arm_matrix_instance_q31;



  






 

  arm_status arm_mat_add_f32(
			     const arm_matrix_instance_f32 * pSrcA,
			     const arm_matrix_instance_f32 * pSrcB,
			     arm_matrix_instance_f32 * pDst);

  






 

  arm_status arm_mat_add_q15(
			     const arm_matrix_instance_q15 * pSrcA,
			     const arm_matrix_instance_q15 * pSrcB,
			     arm_matrix_instance_q15 * pDst);

  






 

  arm_status arm_mat_add_q31(
			     const arm_matrix_instance_q31 * pSrcA,
			     const arm_matrix_instance_q31 * pSrcB,
			     arm_matrix_instance_q31 * pDst);


  





 

  arm_status arm_mat_trans_f32(
			       const arm_matrix_instance_f32 * pSrc,
			       arm_matrix_instance_f32 * pDst);


  





 

  arm_status arm_mat_trans_q15(
			       const arm_matrix_instance_q15 * pSrc,
			       arm_matrix_instance_q15 * pDst);

  





 

  arm_status arm_mat_trans_q31(
			       const arm_matrix_instance_q31 * pSrc,
			       arm_matrix_instance_q31 * pDst);


  






 

  arm_status arm_mat_mult_f32(
			      const arm_matrix_instance_f32 * pSrcA,
			      const arm_matrix_instance_f32 * pSrcB,
			      arm_matrix_instance_f32 * pDst);

  






 

  arm_status arm_mat_mult_q15(
			      const arm_matrix_instance_q15 * pSrcA,
			      const arm_matrix_instance_q15 * pSrcB,
			      arm_matrix_instance_q15 * pDst,
			      q15_t * pState);

  







 

  arm_status arm_mat_mult_fast_q15(
				   const arm_matrix_instance_q15 * pSrcA,
				   const arm_matrix_instance_q15 * pSrcB,
				   arm_matrix_instance_q15 * pDst,
				   q15_t * pState);

  






 

  arm_status arm_mat_mult_q31(
			      const arm_matrix_instance_q31 * pSrcA,
			      const arm_matrix_instance_q31 * pSrcB,
			      arm_matrix_instance_q31 * pDst);

  






 

  arm_status arm_mat_mult_fast_q31(
				   const arm_matrix_instance_q31 * pSrcA,
				   const arm_matrix_instance_q31 * pSrcB,
				   arm_matrix_instance_q31 * pDst);


  






 

  arm_status arm_mat_sub_f32(
			     const arm_matrix_instance_f32 * pSrcA,
			     const arm_matrix_instance_f32 * pSrcB,
			     arm_matrix_instance_f32 * pDst);

  






 

  arm_status arm_mat_sub_q15(
			     const arm_matrix_instance_q15 * pSrcA,
			     const arm_matrix_instance_q15 * pSrcB,
			     arm_matrix_instance_q15 * pDst);

  






 

  arm_status arm_mat_sub_q31(
			     const arm_matrix_instance_q31 * pSrcA,
			     const arm_matrix_instance_q31 * pSrcB,
			     arm_matrix_instance_q31 * pDst);

  






 

  arm_status arm_mat_scale_f32(
			       const arm_matrix_instance_f32 * pSrc,
			       float32_t scale,
			       arm_matrix_instance_f32 * pDst);

  







 

  arm_status arm_mat_scale_q15(
			       const arm_matrix_instance_q15 * pSrc,
			       q15_t scaleFract,
			       int32_t shift,
			       arm_matrix_instance_q15 * pDst);

  







 

  arm_status arm_mat_scale_q31(
			       const arm_matrix_instance_q31 * pSrc,
			       q31_t scaleFract,
			       int32_t shift,
			       arm_matrix_instance_q31 * pDst);


  






 

  void arm_mat_init_q31(
			arm_matrix_instance_q31 * S,
			uint16_t nRows,
			uint16_t nColumns,
			q31_t   *pData);

  






 

  void arm_mat_init_q15(
			arm_matrix_instance_q15 * S,
			uint16_t nRows,
			uint16_t nColumns,
			q15_t    *pData);

  






 

  void arm_mat_init_f32(
			arm_matrix_instance_f32 * S,
			uint16_t nRows,
			uint16_t nColumns,
			float32_t   *pData);



  

 
  typedef struct
  {
    q15_t A0; 	  

	q15_t A1;
	q15_t A2; 



    q15_t state[3];        
    q15_t Kp;            
    q15_t Ki;            
    q15_t Kd;            
  } arm_pid_instance_q15;

  

 
  typedef struct
  {
    q31_t A0;             
    q31_t A1;             
    q31_t A2;             
    q31_t state[3];       
    q31_t Kp;             
    q31_t Ki;             
    q31_t Kd;             

  } arm_pid_instance_q31;

  

 
  typedef struct
  {
    float32_t A0;           
    float32_t A1;           
    float32_t A2;           
    float32_t state[3];     
    float32_t Kp;                
    float32_t Ki;                
    float32_t Kd;                
  } arm_pid_instance_f32;



  




 
  void arm_pid_init_f32(
			arm_pid_instance_f32 * S,
			int32_t resetStateFlag);

  



 
  void arm_pid_reset_f32(
			 arm_pid_instance_f32 * S);


  




 
  void arm_pid_init_q31(
			arm_pid_instance_q31 * S,
			int32_t resetStateFlag);

 
  



 

  void arm_pid_reset_q31(
			 arm_pid_instance_q31 * S);

  




 
  void arm_pid_init_q15(
			arm_pid_instance_q15 * S,
			int32_t resetStateFlag);

  



 
  void arm_pid_reset_q15(
			 arm_pid_instance_q15 * S);


  

 
  typedef struct
  {
    uint32_t nValues;
    float32_t x1;
    float32_t xSpacing;
    float32_t *pYData;           
  } arm_linear_interp_instance_f32;

  

 

  typedef struct
  {
    uint16_t numRows;	 
    uint16_t numCols;	 
    float32_t *pData;	 
  } arm_bilinear_interp_instance_f32;

   

 

  typedef struct
  {
    uint16_t numRows;	 
    uint16_t numCols;	 
    q31_t *pData;	 
  } arm_bilinear_interp_instance_q31;

   

 

  typedef struct
  {
    uint16_t numRows;	 
    uint16_t numCols;	 
    q15_t *pData;	 
  } arm_bilinear_interp_instance_q15;

   

 

  typedef struct
  {
    uint16_t numRows; 	 
    uint16_t numCols;	 
    q7_t *pData;		 
  } arm_bilinear_interp_instance_q7;


  






 

  void arm_mult_q7(
		    q7_t * pSrcA,
		    q7_t * pSrcB,
		   q7_t * pDst,
		   uint32_t blockSize);

  






 

  void arm_mult_q15(
		     q15_t * pSrcA,
		     q15_t * pSrcB,
		    q15_t * pDst,
		    uint32_t blockSize);

  






 

  void arm_mult_q31(
		     q31_t * pSrcA,
		     q31_t * pSrcB,
		    q31_t * pDst,
		    uint32_t blockSize);

  






 

  void arm_mult_f32(
		     float32_t * pSrcA,
		     float32_t * pSrcB,
		    float32_t * pDst,
		    uint32_t blockSize);


  

 

  typedef struct
  {
    uint16_t  fftLen;                 
    uint8_t   ifftFlag;               
    uint8_t   bitReverseFlag;         
    q15_t     *pTwiddle;              
    uint16_t  *pBitRevTable;          
    uint16_t  twidCoefModifier;       
    uint16_t  bitRevFactor;           
  } arm_cfft_radix4_instance_q15;

  

 

  typedef struct
  {
    uint16_t    fftLen;               
    uint8_t     ifftFlag;             
    uint8_t     bitReverseFlag;       
    q31_t       *pTwiddle;            
    uint16_t    *pBitRevTable;        
    uint16_t    twidCoefModifier;     
    uint16_t    bitRevFactor;         
  } arm_cfft_radix4_instance_q31;

  

 

  typedef struct
  {
    uint16_t     fftLen;                
    uint8_t      ifftFlag;              
    uint8_t      bitReverseFlag;        
    float32_t    *pTwiddle;             
    uint16_t     *pBitRevTable;         
    uint16_t     twidCoefModifier;      
    uint16_t     bitRevFactor;          
	float32_t    onebyfftLen;           
  } arm_cfft_radix4_instance_f32;

  




 

  void arm_cfft_radix4_q15(
			   const arm_cfft_radix4_instance_q15 * S,
			   q15_t * pSrc);

  






 

  arm_status arm_cfft_radix4_init_q15(
				      arm_cfft_radix4_instance_q15 * S,
				      uint16_t fftLen,
				      uint8_t ifftFlag,
				      uint8_t bitReverseFlag);

  




 

  void arm_cfft_radix4_q31(
			   const arm_cfft_radix4_instance_q31 * S,
			   q31_t * pSrc);

  






 
  
  arm_status arm_cfft_radix4_init_q31(
				      arm_cfft_radix4_instance_q31 * S,
				      uint16_t fftLen,
				      uint8_t ifftFlag,
				      uint8_t bitReverseFlag);

  




 

  void arm_cfft_radix4_f32(
			   const arm_cfft_radix4_instance_f32 * S,
			   float32_t * pSrc);

  






 
  
  arm_status arm_cfft_radix4_init_f32(
				      arm_cfft_radix4_instance_f32 * S,
				      uint16_t fftLen,
				      uint8_t ifftFlag,
				      uint8_t bitReverseFlag);



  

 

  






 
  
  void arm_radix4_butterfly_f32(
				float32_t * pSrc,
				uint16_t fftLen,
				float32_t * pCoef,
				uint16_t twidCoefModifier);

  







 
  
  void arm_radix4_butterfly_inverse_f32(
					float32_t * pSrc,
					uint16_t fftLen,
					float32_t * pCoef,
					uint16_t twidCoefModifier,
					float32_t onebyfftLen);

  






 

  void arm_bitreversal_f32(
			   float32_t *pSrc,
			   uint16_t fftSize,
			   uint16_t bitRevFactor,
			   uint16_t *pBitRevTab);

  






 
  
  void arm_radix4_butterfly_q31(
				q31_t *pSrc,
				uint32_t fftLen,
				q31_t *pCoef,
				uint32_t twidCoefModifier);

  






 
  
  void arm_radix4_butterfly_inverse_q31(
					q31_t * pSrc,
					uint32_t fftLen,
					q31_t * pCoef,
					uint32_t twidCoefModifier);
  
  






 

  void arm_bitreversal_q31(
			   q31_t * pSrc,
			   uint32_t fftLen,
			   uint16_t bitRevFactor,
			   uint16_t *pBitRevTab);

  






 

  void arm_radix4_butterfly_q15(
				q15_t *pSrc16,
				uint32_t fftLen,
				q15_t *pCoef16,
				uint32_t twidCoefModifier);

  






 

  void arm_radix4_butterfly_inverse_q15(
					q15_t *pSrc16,
					uint32_t fftLen,
					q15_t *pCoef16,
					uint32_t twidCoefModifier);

  






 

  void arm_bitreversal_q15(
			   q15_t * pSrc,
			   uint32_t fftLen,
			   uint16_t bitRevFactor,
			   uint16_t *pBitRevTab);

  

 

  typedef struct
  {
    uint32_t fftLenReal;                       
    uint32_t fftLenBy2;                        
    uint8_t  ifftFlagR;                        
	uint8_t  bitReverseFlagR;                  
    uint32_t twidCoefRModifier;                  
    q15_t    *pTwiddleAReal;                   
    q15_t    *pTwiddleBReal;                   
    arm_cfft_radix4_instance_q15 *pCfft;	   
  } arm_rfft_instance_q15;

  

 

  typedef struct
  {
    uint32_t fftLenReal;                         
    uint32_t fftLenBy2;                          
    uint8_t  ifftFlagR;                          
	uint8_t  bitReverseFlagR;                    
    uint32_t twidCoefRModifier;                  
    q31_t    *pTwiddleAReal;                     
    q31_t    *pTwiddleBReal;                     
    arm_cfft_radix4_instance_q31 *pCfft;         
  } arm_rfft_instance_q31;

  

 

  typedef struct
  {
    uint32_t  fftLenReal;                        
    uint16_t  fftLenBy2;                         
    uint8_t   ifftFlagR;                         
    uint8_t   bitReverseFlagR;                   
	uint32_t  twidCoefRModifier;                 
    float32_t *pTwiddleAReal;                    
    float32_t *pTwiddleBReal;                    
    arm_cfft_radix4_instance_f32 *pCfft;         
  } arm_rfft_instance_f32;

  





 

  void arm_rfft_q15(
		    const arm_rfft_instance_q15 * S,
		    q15_t * pSrc,
		    q15_t * pDst);

  







 

  arm_status arm_rfft_init_q15(
			       arm_rfft_instance_q15 * S,
			       arm_cfft_radix4_instance_q15 * S_CFFT,
			       uint32_t fftLenReal,
			       uint32_t ifftFlagR,
			       uint32_t bitReverseFlag);

  





 

  void arm_rfft_q31(
		    const arm_rfft_instance_q31 * S,
		    q31_t * pSrc,
		    q31_t * pDst);

  







 

  arm_status arm_rfft_init_q31(
			       arm_rfft_instance_q31 * S,
			       arm_cfft_radix4_instance_q31 * S_CFFT,
			       uint32_t fftLenReal,
			       uint32_t ifftFlagR,
			       uint32_t bitReverseFlag);

  







 

  arm_status arm_rfft_init_f32(
			       arm_rfft_instance_f32 * S,
			       arm_cfft_radix4_instance_f32 * S_CFFT,
			       uint32_t fftLenReal,
			       uint32_t ifftFlagR,
			       uint32_t bitReverseFlag);

  





 

  void arm_rfft_f32(
		    const arm_rfft_instance_f32 * S,
		    float32_t * pSrc,
		    float32_t * pDst);

  

 

  typedef struct
  {
    uint16_t N;                          
    uint16_t Nby2;                       
    float32_t normalize;                 
    float32_t *pTwiddle;                 
    float32_t *pCosFactor;               
    arm_rfft_instance_f32 *pRfft;         
    arm_cfft_radix4_instance_f32 *pCfft;  
  } arm_dct4_instance_f32;

  








 

  arm_status arm_dct4_init_f32(
			       arm_dct4_instance_f32 * S,
			       arm_rfft_instance_f32 * S_RFFT,
			       arm_cfft_radix4_instance_f32 * S_CFFT,
			       uint16_t N,
			       uint16_t Nby2,
			       float32_t normalize);

  





 

  void arm_dct4_f32(
		    const arm_dct4_instance_f32 * S,
		    float32_t * pState,
		    float32_t * pInlineBuffer);

  

 

  typedef struct
  {
    uint16_t N;                          
    uint16_t Nby2;                       
    q31_t normalize;                     
    q31_t *pTwiddle;                     
    q31_t *pCosFactor;                   
    arm_rfft_instance_q31 *pRfft;         
    arm_cfft_radix4_instance_q31 *pCfft;  
  } arm_dct4_instance_q31;

  








 

  arm_status arm_dct4_init_q31(
			       arm_dct4_instance_q31 * S,
			       arm_rfft_instance_q31 * S_RFFT,
			       arm_cfft_radix4_instance_q31 * S_CFFT,
			       uint16_t N,
			       uint16_t Nby2,
			       q31_t normalize);

  





 

  void arm_dct4_q31(
		    const arm_dct4_instance_q31 * S,
		    q31_t * pState,
		    q31_t * pInlineBuffer);

  

 

  typedef struct
  {
    uint16_t N;                          
    uint16_t Nby2;                       
    q15_t normalize;                     
    q15_t *pTwiddle;                     
    q15_t *pCosFactor;                   
    arm_rfft_instance_q15 *pRfft;         
    arm_cfft_radix4_instance_q15 *pCfft;  
  } arm_dct4_instance_q15;

  








 

  arm_status arm_dct4_init_q15(
			       arm_dct4_instance_q15 * S,
			       arm_rfft_instance_q15 * S_RFFT,
			       arm_cfft_radix4_instance_q15 * S_CFFT,
			       uint16_t N,
			       uint16_t Nby2,
			       q15_t normalize);

  





 

  void arm_dct4_q15(
		    const arm_dct4_instance_q15 * S,
		    q15_t * pState,
		    q15_t * pInlineBuffer);

  






 

  void arm_add_f32(
		   float32_t * pSrcA,
		   float32_t * pSrcB,
		   float32_t * pDst,
		   uint32_t blockSize);

  






 

  void arm_add_q7(
		  q7_t * pSrcA,
		  q7_t * pSrcB,
		  q7_t * pDst,
		  uint32_t blockSize);

  






 

  void arm_add_q15(
		    q15_t * pSrcA,
		    q15_t * pSrcB,
		   q15_t * pDst,
		   uint32_t blockSize);

  






 

  void arm_add_q31(
		    q31_t * pSrcA,
		    q31_t * pSrcB,
		   q31_t * pDst,
		   uint32_t blockSize);

  






 

  void arm_sub_f32(
		    float32_t * pSrcA,
		    float32_t * pSrcB,
		   float32_t * pDst,
		   uint32_t blockSize);

  






 

  void arm_sub_q7(
		   q7_t * pSrcA,
		   q7_t * pSrcB,
		  q7_t * pDst,
		  uint32_t blockSize);

  






 

  void arm_sub_q15(
		    q15_t * pSrcA,
		    q15_t * pSrcB,
		   q15_t * pDst,
		   uint32_t blockSize);

  






 

  void arm_sub_q31(
		    q31_t * pSrcA,
		    q31_t * pSrcB,
		   q31_t * pDst,
		   uint32_t blockSize);

  






 

  void arm_scale_f32(
		      float32_t * pSrc,
		     float32_t scale,
		     float32_t * pDst,
		     uint32_t blockSize);

  







 

  void arm_scale_q7(
		     q7_t * pSrc,
		    q7_t scaleFract,
		    int8_t shift,
		    q7_t * pDst,
		    uint32_t blockSize);

  







 

  void arm_scale_q15(
		      q15_t * pSrc,
		     q15_t scaleFract,
		     int8_t shift,
		     q15_t * pDst,
		     uint32_t blockSize);

  







 

  void arm_scale_q31(
		      q31_t * pSrc,
		     q31_t scaleFract,
		     int8_t shift,
		     q31_t * pDst,
		     uint32_t blockSize);

  





 

  void arm_abs_q7(
		   q7_t * pSrc,
		  q7_t * pDst,
		  uint32_t blockSize);

  





 

  void arm_abs_f32(
		    float32_t * pSrc,
		   float32_t * pDst,
		   uint32_t blockSize);

  





 

  void arm_abs_q15(
		    q15_t * pSrc,
		   q15_t * pDst,
		   uint32_t blockSize);

  





 

  void arm_abs_q31(
		    q31_t * pSrc,
		   q31_t * pDst,
		   uint32_t blockSize);

  






 

  void arm_dot_prod_f32(
			 float32_t * pSrcA,
			 float32_t * pSrcB,
			uint32_t blockSize,
			float32_t * result);

  






 

  void arm_dot_prod_q7(
		        q7_t * pSrcA,
		        q7_t * pSrcB,
		       uint32_t blockSize,
		       q31_t * result);

  






 

  void arm_dot_prod_q15(
			 q15_t * pSrcA,
			 q15_t * pSrcB,
			uint32_t blockSize,
			q63_t * result);

  






 

  void arm_dot_prod_q31(
			 q31_t * pSrcA,
			 q31_t * pSrcB,
			uint32_t blockSize,
			q63_t * result);

  






 

  void arm_shift_q7(
		     q7_t * pSrc,
		    int8_t shiftBits,
		    q7_t * pDst,
		    uint32_t blockSize);

  






 

  void arm_shift_q15(
		      q15_t * pSrc,
		     int8_t shiftBits,
		     q15_t * pDst,
		     uint32_t blockSize);

  






 

  void arm_shift_q31(
		      q31_t * pSrc,
		     int8_t shiftBits,
		     q31_t * pDst,
		     uint32_t blockSize);

  






 

  void arm_offset_f32(
		       float32_t * pSrc,
		      float32_t offset,
		      float32_t * pDst,
		      uint32_t blockSize);

  






 

  void arm_offset_q7(
		      q7_t * pSrc,
		     q7_t offset,
		     q7_t * pDst,
		     uint32_t blockSize);

  






 

  void arm_offset_q15(
		       q15_t * pSrc,
		      q15_t offset,
		      q15_t * pDst,
		      uint32_t blockSize);

  






 

  void arm_offset_q31(
		       q31_t * pSrc,
		      q31_t offset,
		      q31_t * pDst,
		      uint32_t blockSize);

  





 

  void arm_negate_f32(
		       float32_t * pSrc,
		      float32_t * pDst,
		      uint32_t blockSize);

  





 

  void arm_negate_q7(
		      q7_t * pSrc,
		     q7_t * pDst,
		     uint32_t blockSize);

  





 

  void arm_negate_q15(
		       q15_t * pSrc,
		      q15_t * pDst,
		      uint32_t blockSize);

  





 

  void arm_negate_q31(
		       q31_t * pSrc,
		      q31_t * pDst,
		      uint32_t blockSize);
  





 
  void arm_copy_f32(
		     float32_t * pSrc,
		    float32_t * pDst,
		    uint32_t blockSize);

  





 
  void arm_copy_q7(
		    q7_t * pSrc,
		   q7_t * pDst,
		   uint32_t blockSize);

  





 
  void arm_copy_q15(
		     q15_t * pSrc,
		    q15_t * pDst,
		    uint32_t blockSize);

  





 
  void arm_copy_q31(
		     q31_t * pSrc,
		    q31_t * pDst,
		    uint32_t blockSize);
  





 
  void arm_fill_f32(
		     float32_t value,
		    float32_t * pDst,
		    uint32_t blockSize);

  





 
  void arm_fill_q7(
		    q7_t value,
		   q7_t * pDst,
		   uint32_t blockSize);

  





 
  void arm_fill_q15(
		     q15_t value,
		    q15_t * pDst,
		    uint32_t blockSize);

  





 
  void arm_fill_q31(
		     q31_t value,
		    q31_t * pDst,
		    uint32_t blockSize);









  

  void arm_conv_f32(
		     float32_t * pSrcA,
		    uint32_t srcALen,
		     float32_t * pSrcB,
		    uint32_t srcBLen,
		    float32_t * pDst);









 

  void arm_conv_q15(
		     q15_t * pSrcA,
		    uint32_t srcALen,
		     q15_t * pSrcB,
		    uint32_t srcBLen,
		    q15_t * pDst);

  







 

  void arm_conv_fast_q15(
			  q15_t * pSrcA,
			 uint32_t srcALen,
			  q15_t * pSrcB,
			 uint32_t srcBLen,
			 q15_t * pDst);

  







 

  void arm_conv_q31(
		     q31_t * pSrcA,
		    uint32_t srcALen,
		     q31_t * pSrcB,
		    uint32_t srcBLen,
		    q31_t * pDst);

  







 

  void arm_conv_fast_q31(
			  q31_t * pSrcA,
			 uint32_t srcALen,
			  q31_t * pSrcB,
			 uint32_t srcBLen,
			 q31_t * pDst);

  







 

  void arm_conv_q7(
		    q7_t * pSrcA,
		   uint32_t srcALen,
		    q7_t * pSrcB,
		   uint32_t srcBLen,
		   q7_t * pDst);

  









 

  arm_status arm_conv_partial_f32(
				   float32_t * pSrcA,
				  uint32_t srcALen,
				   float32_t * pSrcB,
				  uint32_t srcBLen,
				  float32_t * pDst,
				  uint32_t firstIndex,
				  uint32_t numPoints);

  









 

  arm_status arm_conv_partial_q15(
				   q15_t * pSrcA,
				  uint32_t srcALen,
				   q15_t * pSrcB,
				  uint32_t srcBLen,
				  q15_t * pDst,
				  uint32_t firstIndex,
				  uint32_t numPoints);

  









 

  arm_status arm_conv_partial_fast_q15(
				        q15_t * pSrcA,
				       uint32_t srcALen,
				        q15_t * pSrcB,
				       uint32_t srcBLen,
				       q15_t * pDst,
				       uint32_t firstIndex,
				       uint32_t numPoints);

  









 

  arm_status arm_conv_partial_q31(
				   q31_t * pSrcA,
				  uint32_t srcALen,
				   q31_t * pSrcB,
				  uint32_t srcBLen,
				  q31_t * pDst,
				  uint32_t firstIndex,
				  uint32_t numPoints);


  









 

  arm_status arm_conv_partial_fast_q31(
				        q31_t * pSrcA,
				       uint32_t srcALen,
				        q31_t * pSrcB,
				       uint32_t srcBLen,
				       q31_t * pDst,
				       uint32_t firstIndex,
				       uint32_t numPoints);

  









 

  arm_status arm_conv_partial_q7(
				  q7_t * pSrcA,
				 uint32_t srcALen,
				  q7_t * pSrcB,
				 uint32_t srcBLen,
				 q7_t * pDst,
				 uint32_t firstIndex,
				 uint32_t numPoints);


  

 

  typedef struct
  {
    uint8_t M;                       
    uint16_t numTaps;                
    q15_t *pCoeffs;                   
    q15_t *pState;                    
  } arm_fir_decimate_instance_q15;

  

 

  typedef struct
  {
    uint8_t M;                   
    uint16_t numTaps;            
    q31_t *pCoeffs;               
    q31_t *pState;                

  } arm_fir_decimate_instance_q31;

  

 

  typedef struct
  {
    uint8_t M;                           
    uint16_t numTaps;                    
    float32_t *pCoeffs;                   
    float32_t *pState;                    

  } arm_fir_decimate_instance_f32;



  






 

  void arm_fir_decimate_f32(
			    const arm_fir_decimate_instance_f32 * S,
			     float32_t * pSrc,
			    float32_t * pDst,
			    uint32_t blockSize);


  









 

  arm_status arm_fir_decimate_init_f32(
				       arm_fir_decimate_instance_f32 * S,
				       uint16_t numTaps,
				       uint8_t M,
				       float32_t * pCoeffs,
				       float32_t * pState,
				       uint32_t blockSize);

  






 

  void arm_fir_decimate_q15(
			    const arm_fir_decimate_instance_q15 * S,
			     q15_t * pSrc,
			    q15_t * pDst,
			    uint32_t blockSize);

  






 

  void arm_fir_decimate_fast_q15(
				 const arm_fir_decimate_instance_q15 * S,
				  q15_t * pSrc,
				 q15_t * pDst,
				 uint32_t blockSize);



  









 

  arm_status arm_fir_decimate_init_q15(
				       arm_fir_decimate_instance_q15 * S,
				       uint16_t numTaps,
				       uint8_t M,
				       q15_t * pCoeffs,
				       q15_t * pState,
				       uint32_t blockSize);

  






 

  void arm_fir_decimate_q31(
			    const arm_fir_decimate_instance_q31 * S,
			     q31_t * pSrc,
			    q31_t * pDst,
			    uint32_t blockSize);

  






 

  void arm_fir_decimate_fast_q31(
				 arm_fir_decimate_instance_q31 * S,
				  q31_t * pSrc,
				 q31_t * pDst,
				 uint32_t blockSize);


  









 

  arm_status arm_fir_decimate_init_q31(
				       arm_fir_decimate_instance_q31 * S,
				       uint16_t numTaps,
				       uint8_t M,
				       q31_t * pCoeffs,
				       q31_t * pState,
				       uint32_t blockSize);



  

 

  typedef struct
  {
    uint8_t L;                       
    uint16_t phaseLength;            
    q15_t *pCoeffs;                  
    q15_t *pState;                   
  } arm_fir_interpolate_instance_q15;

  

 

  typedef struct
  {
    uint8_t L;                       
    uint16_t phaseLength;            
    q31_t *pCoeffs;                   
    q31_t *pState;                    
  } arm_fir_interpolate_instance_q31;

  

 

  typedef struct
  {
    uint8_t L;                      
    uint16_t phaseLength;           
    float32_t *pCoeffs;              
    float32_t *pState;               
  } arm_fir_interpolate_instance_f32;


  






 

  void arm_fir_interpolate_q15(
			       const arm_fir_interpolate_instance_q15 * S,
			        q15_t * pSrc,
			       q15_t * pDst,
			       uint32_t blockSize);


  









 

  arm_status arm_fir_interpolate_init_q15(
					  arm_fir_interpolate_instance_q15 * S,
					  uint8_t L,
					  uint16_t numTaps,
					  q15_t * pCoeffs,
					  q15_t * pState,
					  uint32_t blockSize);

  






 

  void arm_fir_interpolate_q31(
			       const arm_fir_interpolate_instance_q31 * S,
			        q31_t * pSrc,
			       q31_t * pDst,
			       uint32_t blockSize);

  









 

  arm_status arm_fir_interpolate_init_q31(
					  arm_fir_interpolate_instance_q31 * S,
					  uint8_t L,
					  uint16_t numTaps,
					  q31_t * pCoeffs,
					  q31_t * pState,
					  uint32_t blockSize);


  






 

  void arm_fir_interpolate_f32(
			       const arm_fir_interpolate_instance_f32 * S,
			        float32_t * pSrc,
			       float32_t * pDst,
			       uint32_t blockSize);

  









 

  arm_status arm_fir_interpolate_init_f32(
					  arm_fir_interpolate_instance_f32 * S,
					  uint8_t L,
					  uint16_t numTaps,
					  float32_t * pCoeffs,
					  float32_t * pState,
					  uint32_t blockSize);

  

 

  typedef struct
  {
    uint8_t numStages;        
    q63_t *pState;            
    q31_t *pCoeffs;           
    uint8_t postShift;        

  } arm_biquad_cas_df1_32x64_ins_q31;


  





 

  void arm_biquad_cas_df1_32x64_q31(
				    const arm_biquad_cas_df1_32x64_ins_q31 * S,
				     q31_t * pSrc,
				    q31_t * pDst,
				    uint32_t blockSize);


  






 

  void arm_biquad_cas_df1_32x64_init_q31(
					 arm_biquad_cas_df1_32x64_ins_q31 * S,
					 uint8_t numStages,
					 q31_t * pCoeffs,
					 q63_t * pState,
					 uint8_t postShift);



  

 

  typedef struct
  {
    uint8_t   numStages;        
    float32_t *pState;          
    float32_t *pCoeffs;         
  } arm_biquad_cascade_df2T_instance_f32;


  






 

  void arm_biquad_cascade_df2T_f32(
				   const arm_biquad_cascade_df2T_instance_f32 * S,
				    float32_t * pSrc,
				   float32_t * pDst,
				   uint32_t blockSize);


  






 

  void arm_biquad_cascade_df2T_init_f32(
					arm_biquad_cascade_df2T_instance_f32 * S,
					uint8_t numStages,
					float32_t * pCoeffs,
					float32_t * pState);



  

 

  typedef struct
  {
    uint16_t numStages;                           
    q15_t *pState;                                
    q15_t *pCoeffs;                               
  } arm_fir_lattice_instance_q15;

  

 

  typedef struct
  {
    uint16_t numStages;                           
    q31_t *pState;                                
    q31_t *pCoeffs;                               
  } arm_fir_lattice_instance_q31;

  

 

  typedef struct
  {
    uint16_t numStages;                   
    float32_t *pState;                    
    float32_t *pCoeffs;                   
  } arm_fir_lattice_instance_f32;

  






 

  void arm_fir_lattice_init_q15(
				arm_fir_lattice_instance_q15 * S,
				uint16_t numStages,
				q15_t * pCoeffs,
				q15_t * pState);


  






 
  void arm_fir_lattice_q15(
			   const arm_fir_lattice_instance_q15 * S,
			    q15_t * pSrc,
			   q15_t * pDst,
			   uint32_t blockSize);

  






 

  void arm_fir_lattice_init_q31(
				arm_fir_lattice_instance_q31 * S,
				uint16_t numStages,
				q31_t * pCoeffs,
				q31_t * pState);


  






 

  void arm_fir_lattice_q31(
			   const arm_fir_lattice_instance_q31 * S,
			    q31_t * pSrc,
			   q31_t * pDst,
			   uint32_t blockSize);








 

  void arm_fir_lattice_init_f32(
				arm_fir_lattice_instance_f32 * S,
				uint16_t numStages,
				float32_t * pCoeffs,
				float32_t * pState);

  






 

  void arm_fir_lattice_f32(
			   const arm_fir_lattice_instance_f32 * S,
			    float32_t * pSrc,
			   float32_t * pDst,
			   uint32_t blockSize);

  

 
  typedef struct
  {
    uint16_t numStages;                          
    q15_t *pState;                               
    q15_t *pkCoeffs;                             
    q15_t *pvCoeffs;                             
  } arm_iir_lattice_instance_q15;

  

 
  typedef struct
  {
    uint16_t numStages;                          
    q31_t *pState;                               
    q31_t *pkCoeffs;                             
    q31_t *pvCoeffs;                             
  } arm_iir_lattice_instance_q31;

  

 
  typedef struct
  {
    uint16_t numStages;                          
    float32_t *pState;                           
    float32_t *pkCoeffs;                         
    float32_t *pvCoeffs;                         
  } arm_iir_lattice_instance_f32;

  






 

  void arm_iir_lattice_f32(
			   const arm_iir_lattice_instance_f32 * S,
			    float32_t * pSrc,
			   float32_t * pDst,
			   uint32_t blockSize);

  








 

  void arm_iir_lattice_init_f32(
				arm_iir_lattice_instance_f32 * S,
				uint16_t numStages,
				float32_t *pkCoeffs,
				float32_t *pvCoeffs,
				float32_t *pState,
				uint32_t blockSize);


  






 

  void arm_iir_lattice_q31(
			   const arm_iir_lattice_instance_q31 * S,
			    q31_t * pSrc,
			   q31_t * pDst,
			   uint32_t blockSize);


  








 

  void arm_iir_lattice_init_q31(
				arm_iir_lattice_instance_q31 * S,
				uint16_t numStages,
				q31_t *pkCoeffs,
				q31_t *pvCoeffs,
				q31_t *pState,
				uint32_t blockSize);


  






 

  void arm_iir_lattice_q15(
			   const arm_iir_lattice_instance_q15 * S,
			    q15_t * pSrc,
			   q15_t * pDst,
			   uint32_t blockSize);











 

  void arm_iir_lattice_init_q15(
				arm_iir_lattice_instance_q15 * S,
				uint16_t numStages,
				q15_t *pkCoeffs,
				q15_t *pvCoeffs,
				q15_t *pState,
				uint32_t blockSize);

  

 

  typedef struct
  {
    uint16_t numTaps;     
    float32_t *pState;    
    float32_t *pCoeffs;   
    float32_t mu;         
  } arm_lms_instance_f32;

  








 

  void arm_lms_f32(
		   const arm_lms_instance_f32 * S,
		    float32_t * pSrc,
		    float32_t * pRef,
		   float32_t * pOut,
		   float32_t * pErr,
		   uint32_t blockSize);

  








 

  void arm_lms_init_f32(
			arm_lms_instance_f32 * S,
			uint16_t numTaps,
			float32_t * pCoeffs,
			float32_t * pState,
			float32_t mu,
			uint32_t blockSize);

  

 

  typedef struct
  {
    uint16_t numTaps;     
    q15_t *pState;        
    q15_t *pCoeffs;       
    q15_t mu;             
    uint32_t postShift;   
  } arm_lms_instance_q15;


  









 

  void arm_lms_init_q15(
			arm_lms_instance_q15 * S,
			uint16_t numTaps,
			q15_t * pCoeffs,
			q15_t * pState,
			q15_t mu,
			uint32_t blockSize,
			uint32_t postShift);

  








 

  void arm_lms_q15(
		   const arm_lms_instance_q15 * S,
		    q15_t * pSrc,
		    q15_t * pRef,
		   q15_t * pOut,
		   q15_t * pErr,
		   uint32_t blockSize);


  

 

  typedef struct
  {
    uint16_t numTaps;     
    q31_t *pState;        
    q31_t *pCoeffs;       
    q31_t mu;             
    uint32_t postShift;   

  } arm_lms_instance_q31;

  








 

  void arm_lms_q31(
		   const arm_lms_instance_q31 * S,
		    q31_t * pSrc,
		    q31_t * pRef,
		   q31_t * pOut,
		   q31_t * pErr,
		   uint32_t blockSize);

  









 

  void arm_lms_init_q31(
			arm_lms_instance_q31 * S,
			uint16_t numTaps,
			q31_t *pCoeffs,
			q31_t *pState,
			q31_t mu,
			uint32_t blockSize,
			uint32_t postShift);

  

 

  typedef struct
  {
    uint16_t  numTaps;     
    float32_t *pState;     
    float32_t *pCoeffs;    
    float32_t mu;         
    float32_t energy;     
    float32_t x0;         
  } arm_lms_norm_instance_f32;

  








 

  void arm_lms_norm_f32(
			arm_lms_norm_instance_f32 * S,
			 float32_t * pSrc,
			 float32_t * pRef,
			float32_t * pOut,
			float32_t * pErr,
			uint32_t blockSize);

  








 

  void arm_lms_norm_init_f32(
			     arm_lms_norm_instance_f32 * S,
			     uint16_t numTaps,
			     float32_t * pCoeffs,
			     float32_t * pState,
			     float32_t mu,
			     uint32_t blockSize);


  

 
  typedef struct
  {
    uint16_t numTaps;      
    q31_t *pState;         
    q31_t *pCoeffs;        
    q31_t mu;              
    uint8_t postShift;     
    q31_t *recipTable;     
    q31_t energy;          
    q31_t x0;              
  } arm_lms_norm_instance_q31;

  








 

  void arm_lms_norm_q31(
			arm_lms_norm_instance_q31 * S,
			 q31_t * pSrc,
			 q31_t * pRef,
			q31_t * pOut,
			q31_t * pErr,
			uint32_t blockSize);

  









 

  void arm_lms_norm_init_q31(
			     arm_lms_norm_instance_q31 * S,
			     uint16_t numTaps,
			     q31_t * pCoeffs,
			     q31_t * pState,
			     q31_t mu,
			     uint32_t blockSize,
			     uint8_t postShift);

  

 

  typedef struct
  {
    uint16_t numTaps;     
    q15_t *pState;         
    q15_t *pCoeffs;        
    q15_t mu;             
    uint8_t postShift;    
    q15_t *recipTable;    
    q15_t energy;         
    q15_t x0;             
  } arm_lms_norm_instance_q15;

  








 

  void arm_lms_norm_q15(
			arm_lms_norm_instance_q15 * S,
			 q15_t * pSrc,
			 q15_t * pRef,
			q15_t * pOut,
			q15_t * pErr,
			uint32_t blockSize);


  









 

  void arm_lms_norm_init_q15(
			     arm_lms_norm_instance_q15 * S,
			     uint16_t numTaps,
			     q15_t * pCoeffs,
			     q15_t * pState,
			     q15_t mu,
			     uint32_t blockSize,
			     uint8_t postShift);

  







 

  void arm_correlate_f32(
			  float32_t * pSrcA,
			 uint32_t srcALen,
			  float32_t * pSrcB,
			 uint32_t srcBLen,
			 float32_t * pDst);

  







 

  void arm_correlate_q15(
			  q15_t * pSrcA,
			 uint32_t srcALen,
			  q15_t * pSrcB,
			 uint32_t srcBLen,
			 q15_t * pDst);

  







 

  void arm_correlate_fast_q15(
			       q15_t * pSrcA,
			      uint32_t srcALen,
			       q15_t * pSrcB,
			      uint32_t srcBLen,
			      q15_t * pDst);

  







 

  void arm_correlate_q31(
			  q31_t * pSrcA,
			 uint32_t srcALen,
			  q31_t * pSrcB,
			 uint32_t srcBLen,
			 q31_t * pDst);

  







 

  void arm_correlate_fast_q31(
			       q31_t * pSrcA,
			      uint32_t srcALen,
			       q31_t * pSrcB,
			      uint32_t srcBLen,
			      q31_t * pDst);

  







 

  void arm_correlate_q7(
			 q7_t * pSrcA,
			uint32_t srcALen,
			 q7_t * pSrcB,
			uint32_t srcBLen,
			q7_t * pDst);

  

 
  typedef struct
  {
    uint16_t numTaps;              
    uint16_t stateIndex;           
    float32_t *pState;             
    float32_t *pCoeffs;            
    uint16_t maxDelay;             
    int32_t *pTapDelay;            
  } arm_fir_sparse_instance_f32;

  

 

  typedef struct
  {
    uint16_t numTaps;              
    uint16_t stateIndex;           
    q31_t *pState;                 
    q31_t *pCoeffs;                
    uint16_t maxDelay;             
    int32_t *pTapDelay;            
  } arm_fir_sparse_instance_q31;

  

 

  typedef struct
  {
    uint16_t numTaps;              
    uint16_t stateIndex;           
    q15_t *pState;                 
    q15_t *pCoeffs;                
    uint16_t maxDelay;             
    int32_t *pTapDelay;            
  } arm_fir_sparse_instance_q15;

  

 

  typedef struct
  {
    uint16_t numTaps;              
    uint16_t stateIndex;           
    q7_t *pState;                  
    q7_t *pCoeffs;                 
    uint16_t maxDelay;             
    int32_t *pTapDelay;            
  } arm_fir_sparse_instance_q7;

  







 

  void arm_fir_sparse_f32(
			  arm_fir_sparse_instance_f32 * S,
			   float32_t * pSrc,
			  float32_t * pDst,
			  float32_t * pScratchIn,
			  uint32_t blockSize);

  









 

  void arm_fir_sparse_init_f32(
			       arm_fir_sparse_instance_f32 * S,
			       uint16_t numTaps,
			       float32_t * pCoeffs,
			       float32_t * pState,
			       int32_t * pTapDelay,
			       uint16_t maxDelay,
			       uint32_t blockSize);

  







 

  void arm_fir_sparse_q31(
			  arm_fir_sparse_instance_q31 * S,
			   q31_t * pSrc,
			  q31_t * pDst,
			  q31_t * pScratchIn,
			  uint32_t blockSize);

  









 

  void arm_fir_sparse_init_q31(
			       arm_fir_sparse_instance_q31 * S,
			       uint16_t numTaps,
			       q31_t * pCoeffs,
			       q31_t * pState,
			       int32_t * pTapDelay,
			       uint16_t maxDelay,
			       uint32_t blockSize);

  








 

  void arm_fir_sparse_q15(
			  arm_fir_sparse_instance_q15 * S,
			   q15_t * pSrc,
			  q15_t * pDst,
			  q15_t * pScratchIn,
			  q31_t * pScratchOut,
			  uint32_t blockSize);


  









 

  void arm_fir_sparse_init_q15(
			       arm_fir_sparse_instance_q15 * S,
			       uint16_t numTaps,
			       q15_t * pCoeffs,
			       q15_t * pState,
			       int32_t * pTapDelay,
			       uint16_t maxDelay,
			       uint32_t blockSize);

  








 

  void arm_fir_sparse_q7(
			 arm_fir_sparse_instance_q7 * S,
			  q7_t * pSrc,
			 q7_t * pDst,
			 q7_t * pScratchIn,
			 q31_t * pScratchOut,
			 uint32_t blockSize);

  









 

  void arm_fir_sparse_init_q7(
			      arm_fir_sparse_instance_q7 * S,
			      uint16_t numTaps,
			      q7_t * pCoeffs,
			      q7_t * pState,
			      int32_t *pTapDelay,
			      uint16_t maxDelay,
			      uint32_t blockSize);


  





 

  void arm_sin_cos_f32(
		       float32_t theta,
		       float32_t *pSinVal,
		       float32_t *pCcosVal);

  





 

  void arm_sin_cos_q31(
		       q31_t theta,
		       q31_t *pSinVal,
		       q31_t *pCosVal);


  





 

  void arm_cmplx_conj_f32(
			   float32_t * pSrc,
			  float32_t * pDst,
			  uint32_t numSamples);

  





 

  void arm_cmplx_conj_q31(
			   q31_t * pSrc,
			  q31_t * pDst,
			  uint32_t numSamples);

  





 

  void arm_cmplx_conj_q15(
			   q15_t * pSrc,
			  q15_t * pDst,
			  uint32_t numSamples);



  





 

  void arm_cmplx_mag_squared_f32(
				  float32_t * pSrc,
				 float32_t * pDst,
				 uint32_t numSamples);

  





 

  void arm_cmplx_mag_squared_q31(
				  q31_t * pSrc,
				 q31_t * pDst,
				 uint32_t numSamples);

  





 

  void arm_cmplx_mag_squared_q15(
				  q15_t * pSrc,
				 q15_t * pDst,
				 uint32_t numSamples);


 

 

  






















































 

  


 

  




 


  static __inline float32_t arm_pid_f32(
					arm_pid_instance_f32 * S,
					float32_t in)
  {
    float32_t out;

     
    out = (S->A0 * in) +
      (S->A1 * S->state[0]) + (S->A2 * S->state[1]) + (S->state[2]);

     
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

     
    return (out);

  }

  












 

  static __inline q31_t arm_pid_q31(
				    arm_pid_instance_q31 * S,
				    q31_t in)
  {
    q63_t acc;
	q31_t out;

     
    acc = (q63_t) S->A0 * in;

     
    acc += (q63_t) S->A1 * S->state[0];

     
    acc += (q63_t) S->A2 * S->state[1];

     
    out = (q31_t) (acc >> 31u);

     
    out += S->state[2];

     
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

     
    return (out);

  }

  













 

  static __inline q15_t arm_pid_q15(
				    arm_pid_instance_q15 * S,
				    q15_t in)
  {
    q63_t acc;
    q15_t out;

     



 	 
	acc = ((q31_t) S->A0 )* in ;

#line 4814 "C:\\Keil\\ARM\\CMSIS\\arm_math.h"


						   
	 
	acc += (q31_t) S->A1  *  S->state[0] ;
	acc += (q31_t) S->A2  *  S->state[1] ;

#line 4827 "C:\\Keil\\ARM\\CMSIS\\arm_math.h"

     
    acc += (q31_t) S->state[2] << 15;

     
    out = (q15_t) (__SSAT((acc >> 15), 16));

     
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

     
    return (out);

  }
  
  

 


  





 

  arm_status arm_mat_inverse_f32(
				 const arm_matrix_instance_f32 * src,
				 arm_matrix_instance_f32 * dst);

  
 
  

 


  



















 

  


 

  







 

  static __inline void arm_clarke_f32(
				      float32_t Ia,
				      float32_t Ib,
				      float32_t * pIalpha,
				      float32_t * pIbeta)
  {
     
    *pIalpha = Ia;

     
    *pIbeta = ((float32_t) 0.57735026919 * Ia + (float32_t) 1.15470053838 * Ib);

  }

  












 

  static __inline void arm_clarke_q31(
				      q31_t Ia,
				      q31_t Ib,
				      q31_t * pIalpha,
				      q31_t * pIbeta)
  {
    q31_t product1, product2;                     

     
    *pIalpha = Ia;

     
    product1 = (q31_t) (((q63_t) Ia * 0x24F34E8B) >> 30);

     
    product2 = (q31_t) (((q63_t) Ib * 0x49E69D16) >> 30);

     
    *pIbeta = __QADD(product1, product2);
  }

  

 

  





 
  void arm_q7_to_q31(
		     q7_t * pSrc,
		     q31_t * pDst,
		     uint32_t blockSize);


 

  

 

  













 

  


 

   






 


  static __inline void arm_inv_clarke_f32(
					  float32_t Ialpha,
					  float32_t Ibeta,
					  float32_t * pIa,
					  float32_t * pIb)
  {
     
    *pIa = Ialpha;

     
    *pIb = -0.5 * Ialpha + (float32_t) 0.8660254039 *Ibeta;

  }

  












 

  static __inline void arm_inv_clarke_q31(
					  q31_t Ialpha,
					  q31_t Ibeta,
					  q31_t * pIa,
					  q31_t * pIb)
  {
    q31_t product1, product2;                     

     
    *pIa = Ialpha;

     
    product1 = (q31_t) (((q63_t) (Ialpha) * (0x40000000)) >> 31);

     
    product2 = (q31_t) (((q63_t) (Ibeta) * (0x6ED9EBA1)) >> 31);

     
    *pIb = __QSUB(product2, product1);

  }

  

 

  





 
  void arm_q7_to_q15(
		      q7_t * pSrc,
		     q15_t * pDst,
		     uint32_t blockSize);

  

  

 

  





















 

  


 

  











 

  static __inline void arm_park_f32(
				    float32_t Ialpha,
				    float32_t Ibeta,
				    float32_t * pId,
				    float32_t * pIq,
				    float32_t sinVal,
				    float32_t cosVal)
  {
     
    *pId = Ialpha * cosVal + Ibeta * sinVal;

     
    *pIq = -Ialpha * sinVal + Ibeta * cosVal;

  }

  














 


  static __inline void arm_park_q31(
				    q31_t Ialpha,
				    q31_t Ibeta,
				    q31_t * pId,
				    q31_t * pIq,
				    q31_t sinVal,
				    q31_t cosVal)
  {
    q31_t product1, product2;                     
    q31_t product3, product4;                     

     
    product1 = (q31_t) (((q63_t) (Ialpha) * (cosVal)) >> 31);

     
    product2 = (q31_t) (((q63_t) (Ibeta) * (sinVal)) >> 31);


     
    product3 = (q31_t) (((q63_t) (Ialpha) * (sinVal)) >> 31);

     
    product4 = (q31_t) (((q63_t) (Ibeta) * (cosVal)) >> 31);

     
    *pId = __QADD(product1, product2);

     
    *pIq = __QSUB(product4, product3);
  }

  

 

  





 
  void arm_q7_to_float(
		        q7_t * pSrc,
		       float32_t * pDst,
		       uint32_t blockSize);

 
  

 

  














 

  


 

   








 

  static __inline void arm_inv_park_f32(
					float32_t Id,
					float32_t Iq,
					float32_t * pIalpha,
					float32_t * pIbeta,
					float32_t sinVal,
					float32_t cosVal)
  {
     
    *pIalpha = Id * cosVal - Iq * sinVal;

     
    *pIbeta = Id * sinVal + Iq * cosVal;

  }


  














 


  static __inline void arm_inv_park_q31(
					q31_t Id,
					q31_t Iq,
					q31_t * pIalpha,
					q31_t * pIbeta,
					q31_t sinVal,
					q31_t cosVal)
  {
    q31_t product1, product2;                     
    q31_t product3, product4;                     

     
    product1 = (q31_t) (((q63_t) (Id) * (cosVal)) >> 31);

     
    product2 = (q31_t) (((q63_t) (Iq) * (sinVal)) >> 31);


     
    product3 = (q31_t) (((q63_t) (Id) * (sinVal)) >> 31);

     
    product4 = (q31_t) (((q63_t) (Iq) * (cosVal)) >> 31);

     
    *pIalpha = __QSUB(product1, product2);

     
    *pIbeta = __QADD(product4, product3);

  }

  

 

   
  





 
  void arm_q31_to_float(
			 q31_t * pSrc,
			float32_t * pDst,
			uint32_t blockSize);

  

 

  





























 

  


 

  





 

  static __inline float32_t arm_linear_interp_f32(
						  arm_linear_interp_instance_f32 * S,
						  float32_t x)
  {

	  float32_t y;
	  float32_t x0, x1;						 
	  float32_t y0, y1;	  					 
	  float32_t xSpacing = S->xSpacing;		 
	  int32_t i;  							 
	  float32_t *pYData = S->pYData;	     

	   
	  i =   (x - S->x1) / xSpacing;

	  if(i < 0)
	  {
	      
		 y = pYData[0];
	  }
	  else if(i >= S->nValues)
	  {
	  	   
	  	  y = pYData[S->nValues-1];	
	  }
	  else
	  {	 
	  	   
		  x0 = S->x1 + i * xSpacing;
		  x1 = S->x1 + (i +1) * xSpacing;
		 
		  
		  y0 = pYData[i];
		  y1 = pYData[i + 1];
		
		   
		  y = y0 + (x - x0) * ((y1 - y0)/(x1-x0));	
		
	  }

       
	  return (y);
  }

   











 


  static __inline q31_t arm_linear_interp_q31(q31_t *pYData,
					      q31_t x, uint32_t nValues)
  {
    q31_t y;                                    
    q31_t y0, y1;                                 
    q31_t fract;                                  
    int32_t index;                               
    
     
     
     
    index = ((x & 0xFFF00000) >> 20);

	if(index >= (nValues - 1))
	{
		return(pYData[nValues - 1]);
	}
	else if(index < 0)
	{
		return(pYData[0]);
	}
	else
	{

	     
	     
	    fract = (x & 0x000FFFFF) << 11;
	
	     
	    y0 = pYData[index];
	    y1 = pYData[index + 1u];
	
	     
	    y = ((q31_t) ((q63_t) y0 * (0x7FFFFFFF - fract) >> 32));
	
	     
	    y += ((q31_t) (((q63_t) y1 * fract) >> 32));
	
	     
	    return (y << 1u);

	}

  }

  











 


  static __inline q15_t arm_linear_interp_q15(q15_t *pYData, q31_t x, uint32_t nValues)
  {
    q63_t y;                                    
    q15_t y0, y1;                               
    q31_t fract;                                
    int32_t index;                              

     
     
     
    index = ((x & 0xFFF00000) >> 20u); 

	if(index >= (nValues - 1))
	{
		return(pYData[nValues - 1]);
	}
	else if(index < 0)
	{
		return(pYData[0]);
	}
	else
	{	
	     
	     
	    fract = (x & 0x000FFFFF);
	
	     
	    y0 = pYData[index];
	    y1 = pYData[index + 1u];
	
	     
	    y = ((q63_t) y0 * (0xFFFFF - fract));
	
	     
	    y += ((q63_t) y1 * (fract));
	
	     
	    return (y >> 20);
	}


  }

  










 


  static __inline q7_t arm_linear_interp_q7(q7_t *pYData, q31_t x,  uint32_t nValues)
  {
    q31_t y;                                    
    q7_t y0, y1;                                  
    q31_t fract;                                  
    int32_t index;                               
    
     
     
     
    index = ((x & 0xFFF00000) >> 20u);


    if(index >= (nValues - 1))
	{
		return(pYData[nValues - 1]);
	}
	else if(index < 0)
	{
		return(pYData[0]);
	}
	else
	{

	     
	     
	    fract = (x & 0x000FFFFF);
	
	     
	    y0 = pYData[index];
	    y1 = pYData[index + 1u];
	
	     
	    y = ((y0 * (0xFFFFF - fract)));
	
	     
	    y += (y1 * fract);
	
	     
	    return (y >> 20u);

	}

  }
  

 

  



 

  float32_t arm_sin_f32(
			 float32_t x);

  



 

  q31_t arm_sin_q31(
		     q31_t x);

  



 

  q15_t arm_sin_q15(
		     q15_t x);

  



 

  float32_t arm_cos_f32(
			 float32_t x);

  



 

  q31_t arm_cos_q31(
		     q31_t x);

  



 

  q15_t arm_cos_q15(
		     q15_t x);


  

 


  

















 


  


 

  





 

  static __inline arm_status  arm_sqrt_f32(
					  float32_t in, float32_t *pOut)
  {
  	if(in > 0)
	{





		*pOut = sqrtf(in);


		return (ARM_MATH_SUCCESS);
	}
  	else
	{
		*pOut = 0.0f;
		return (ARM_MATH_ARGUMENT_ERROR);
	}

  }


  





 
  arm_status arm_sqrt_q31(
		      q31_t in, q31_t *pOut);

  





 
  arm_status arm_sqrt_q15(
		      q15_t in, q15_t *pOut);

  

 






  

 

  static __inline void arm_circularWrite_f32(
					     int32_t * circBuffer,
					     int32_t L,
					     uint16_t * writeOffset,
					     int32_t bufferInc,
					     const int32_t * src,
					     int32_t srcInc,
					     uint32_t blockSize)
  {
    uint32_t i = 0u;
    int32_t wOffset;

    
 
    wOffset = *writeOffset;

     
    i = blockSize;

    while(i > 0u)
      {
	 
	circBuffer[wOffset] = *src;

	 
	src += srcInc;

	 
	wOffset += bufferInc;
	if(wOffset >= L)
	  wOffset -= L;

	 
	i--;
      }

     
    *writeOffset = wOffset;
  }



  

 
  static __inline void arm_circularRead_f32(
					    int32_t * circBuffer,
					    int32_t L,
					    int32_t * readOffset,
					    int32_t bufferInc,
					    int32_t * dst,
					    int32_t * dst_base,
					    int32_t dst_length,
					    int32_t dstInc,
					    uint32_t blockSize)
  {
    uint32_t i = 0u;
    int32_t rOffset, dst_end;

    
 
    rOffset = *readOffset;
    dst_end = (int32_t) (dst_base + dst_length);

     
    i = blockSize;

    while(i > 0u)
      {
	 
	*dst = circBuffer[rOffset];

	 
	dst += dstInc;

	if(dst == (int32_t *) dst_end)
	  {
	    dst = dst_base;
	  }

	 
	rOffset += bufferInc;

	if(rOffset >= L)
	  {
	    rOffset -= L;
	  }

	 
	i--;
      }

     
    *readOffset = rOffset;
  }

  

 

  static __inline void arm_circularWrite_q15(
					     q15_t * circBuffer,
					     int32_t L,
					     uint16_t * writeOffset,
					     int32_t bufferInc,
					     const q15_t * src,
					     int32_t srcInc,
					     uint32_t blockSize)
  {
    uint32_t i = 0u;
    int32_t wOffset;

    
 
    wOffset = *writeOffset;

     
    i = blockSize;

    while(i > 0u)
      {
	 
	circBuffer[wOffset] = *src;

	 
	src += srcInc;

	 
	wOffset += bufferInc;
	if(wOffset >= L)
	  wOffset -= L;

	 
	i--;
      }

     
    *writeOffset = wOffset;
  }



  

 
  static __inline void arm_circularRead_q15(
					    q15_t * circBuffer,
					    int32_t L,
					    int32_t * readOffset,
					    int32_t bufferInc,
					    q15_t * dst,
					    q15_t * dst_base,
					    int32_t dst_length,
					    int32_t dstInc,
					    uint32_t blockSize)
  {
    uint32_t i = 0;
    int32_t rOffset, dst_end;

    
 
    rOffset = *readOffset;

    dst_end = (int32_t) (dst_base + dst_length);

     
    i = blockSize;

    while(i > 0u)
      {
	 
	*dst = circBuffer[rOffset];

	 
	dst += dstInc;

	if(dst == (q15_t *) dst_end)
	  {
	    dst = dst_base;
	  }

	 
	rOffset += bufferInc;

	if(rOffset >= L)
	  {
	    rOffset -= L;
	  }

	 
	i--;
      }

     
    *readOffset = rOffset;
  }


  

 

  static __inline void arm_circularWrite_q7(
					    q7_t * circBuffer,
					    int32_t L,
					    uint16_t * writeOffset,
					    int32_t bufferInc,
					    const q7_t * src,
					    int32_t srcInc,
					    uint32_t blockSize)
  {
    uint32_t i = 0u;
    int32_t wOffset;

    
 
    wOffset = *writeOffset;

     
    i = blockSize;

    while(i > 0u)
      {
	 
	circBuffer[wOffset] = *src;

	 
	src += srcInc;

	 
	wOffset += bufferInc;
	if(wOffset >= L)
	  wOffset -= L;

	 
	i--;
      }

     
    *writeOffset = wOffset;
  }



  

 
  static __inline void arm_circularRead_q7(
					   q7_t * circBuffer,
					   int32_t L,
					   int32_t * readOffset,
					   int32_t bufferInc,
					   q7_t * dst,
					   q7_t * dst_base,
					   int32_t dst_length,
					   int32_t dstInc,
					   uint32_t blockSize)
  {
    uint32_t i = 0;
    int32_t rOffset, dst_end;

    
 
    rOffset = *readOffset;

    dst_end = (int32_t) (dst_base + dst_length);

     
    i = blockSize;

    while(i > 0u)
      {
	 
	*dst = circBuffer[rOffset];

	 
	dst += dstInc;

	if(dst == (q7_t *) dst_end)
	  {
	    dst = dst_base;
	  }

	 
	rOffset += bufferInc;

	if(rOffset >= L)
	  {
	    rOffset -= L;
	  }

	 
	i--;
      }

     
    *readOffset = rOffset;
  }


  





 

  void arm_power_q31(
		      q31_t * pSrc,
		     uint32_t blockSize,
		     q63_t * pResult);

  





 

  void arm_power_f32(
		      float32_t * pSrc,
		     uint32_t blockSize,
		     float32_t * pResult);

  





 

  void arm_power_q15(
		      q15_t * pSrc,
		     uint32_t blockSize,
		     q63_t * pResult);

  





 

  void arm_power_q7(
		     q7_t * pSrc,
		    uint32_t blockSize,
		    q31_t * pResult);

  





 

  void arm_mean_q7(
		    q7_t * pSrc,
		   uint32_t blockSize,
		   q7_t * pResult);

  





 
  void arm_mean_q15(
		     q15_t * pSrc,
		    uint32_t blockSize,
		    q15_t * pResult);

  





 
  void arm_mean_q31(
		     q31_t * pSrc,
		    uint32_t blockSize,
		    q31_t * pResult);

  





 
  void arm_mean_f32(
		     float32_t * pSrc,
		    uint32_t blockSize,
		    float32_t * pResult);

  





 

  void arm_var_f32(
		    float32_t * pSrc,
		   uint32_t blockSize,
		   float32_t * pResult);

  





 

  void arm_var_q31(
		    q31_t * pSrc,
		   uint32_t blockSize,
		   q63_t * pResult);

  





 

  void arm_var_q15(
		    q15_t * pSrc,
		   uint32_t blockSize,
		   q31_t * pResult);

  





 

  void arm_rms_f32(
		    float32_t * pSrc,
		   uint32_t blockSize,
		   float32_t * pResult);

  





 

  void arm_rms_q31(
		    q31_t * pSrc,
		   uint32_t blockSize,
		   q31_t * pResult);

  





 

  void arm_rms_q15(
		    q15_t * pSrc,
		   uint32_t blockSize,
		   q15_t * pResult);

  





 

  void arm_std_f32(
		    float32_t * pSrc,
		   uint32_t blockSize,
		   float32_t * pResult);

  





 

  void arm_std_q31(
		    q31_t * pSrc,
		   uint32_t blockSize,
		   q31_t * pResult);

  





 

  void arm_std_q15(
		    q15_t * pSrc,
		   uint32_t blockSize,
		   q15_t * pResult);

  





 

  void arm_cmplx_mag_f32(
			  float32_t * pSrc,
			 float32_t * pDst,
			 uint32_t numSamples);

  





 

  void arm_cmplx_mag_q31(
			  q31_t * pSrc,
			 q31_t * pDst,
			 uint32_t numSamples);

  





 

  void arm_cmplx_mag_q15(
			  q15_t * pSrc,
			 q15_t * pDst,
			 uint32_t numSamples);

  







 

  void arm_cmplx_dot_prod_q15(
			       q15_t * pSrcA,
			       q15_t * pSrcB,
			      uint32_t numSamples,
			      q31_t * realResult,
			      q31_t * imagResult);

  







 

  void arm_cmplx_dot_prod_q31(
			       q31_t * pSrcA,
			       q31_t * pSrcB,
			      uint32_t numSamples,
			      q63_t * realResult,
			      q63_t * imagResult);

  







 

  void arm_cmplx_dot_prod_f32(
			       float32_t * pSrcA,
			       float32_t * pSrcB,
			      uint32_t numSamples,
			      float32_t * realResult,
			      float32_t * imagResult);

  






 

  void arm_cmplx_mult_real_q15(
			        q15_t * pSrcCmplx,
			        q15_t * pSrcReal,
			       q15_t * pCmplxDst,
			       uint32_t numSamples);

  






 

  void arm_cmplx_mult_real_q31(
			        q31_t * pSrcCmplx,
			        q31_t * pSrcReal,
			       q31_t * pCmplxDst,
			       uint32_t numSamples);

  






 

  void arm_cmplx_mult_real_f32(
			        float32_t * pSrcCmplx,
			        float32_t * pSrcReal,
			       float32_t * pCmplxDst,
			       uint32_t numSamples);

  






 

  void arm_min_q7(
		   q7_t * pSrc,
		  uint32_t blockSize,
		  q7_t * result,
		  uint32_t * index);

  






 

  void arm_min_q15(
		    q15_t * pSrc,
		   uint32_t blockSize,
		   q15_t * pResult,
		   uint32_t * pIndex);

  






 
  void arm_min_q31(
		    q31_t * pSrc,
		   uint32_t blockSize,
		   q31_t * pResult,
		   uint32_t * pIndex);

  






 

  void arm_min_f32(
		    float32_t * pSrc,
		   uint32_t blockSize,
		   float32_t * pResult,
		   uint32_t * pIndex);








 

  void arm_max_q7(
		   q7_t * pSrc,
		  uint32_t blockSize,
		  q7_t * pResult,
		  uint32_t * pIndex);








 

  void arm_max_q15(
		    q15_t * pSrc,
		   uint32_t blockSize,
		   q15_t * pResult,
		   uint32_t * pIndex);








 

  void arm_max_q31(
		    q31_t * pSrc,
		   uint32_t blockSize,
		   q31_t * pResult,
		   uint32_t * pIndex);








 

  void arm_max_f32(
		    float32_t * pSrc,
		   uint32_t blockSize,
		   float32_t * pResult,
		   uint32_t * pIndex);

  






 

  void arm_cmplx_mult_cmplx_q15(
			        q15_t * pSrcA,
			        q15_t * pSrcB,
			       q15_t * pDst,
			       uint32_t numSamples);

  






 

  void arm_cmplx_mult_cmplx_q31(
			        q31_t * pSrcA,
			        q31_t * pSrcB,
			       q31_t * pDst,
			       uint32_t numSamples);

  






 

  void arm_cmplx_mult_cmplx_f32(
			        float32_t * pSrcA,
			        float32_t * pSrcB,
			       float32_t * pDst,
			       uint32_t numSamples);

  





 
  void arm_float_to_q31(
			       float32_t * pSrc,
			      q31_t * pDst,
			      uint32_t blockSize);

  





 
  void arm_float_to_q15(
			       float32_t * pSrc,
			      q15_t * pDst,
			      uint32_t blockSize);

  





 
  void arm_float_to_q7(
			      float32_t * pSrc,
			     q7_t * pDst,
			     uint32_t blockSize);


  





 
  void arm_q31_to_q15(
		       q31_t * pSrc,
		      q15_t * pDst,
		      uint32_t blockSize);

  





 
  void arm_q31_to_q7(
		      q31_t * pSrc,
		     q7_t * pDst,
		     uint32_t blockSize);

  





 
  void arm_q15_to_float(
			 q15_t * pSrc,
			float32_t * pDst,
			uint32_t blockSize);


  





 
  void arm_q15_to_q31(
		       q15_t * pSrc,
		      q31_t * pDst,
		      uint32_t blockSize);


  





 
  void arm_q15_to_q7(
		      q15_t * pSrc,
		     q7_t * pDst,
		     uint32_t blockSize);


  

 

  

















































 

  


 

  






 

  
  static __inline float32_t arm_bilinear_interp_f32(
						    const arm_bilinear_interp_instance_f32 * S,
						    float32_t X,
						    float32_t Y)
  {
    float32_t out;
    float32_t f00, f01, f10, f11;
    float32_t *pData = S->pData;
    int32_t xIndex, yIndex, index;
    float32_t xdiff, ydiff;
    float32_t b1, b2, b3, b4;

    xIndex = (int32_t) X;
    yIndex = (int32_t) Y;

	 
	 
	if(xIndex < 0 || xIndex > (S->numRows-1) || yIndex < 0  || yIndex > ( S->numCols-1))
	{
		return(0);
	}
	
     
    index = (xIndex - 1) + (yIndex-1) *  S->numCols ;


     
    f00 = pData[index];
    f01 = pData[index + 1];

     
    index = (xIndex-1) + (yIndex) * S->numCols;


     
    f10 = pData[index];
    f11 = pData[index + 1];

     
    b1 = f00;
    b2 = f01 - f00;
    b3 = f10 - f00;
    b4 = f00 - f01 - f10 + f11;

     
    xdiff = X - xIndex;

     
    ydiff = Y - yIndex;

     
     out = b1 + b2 * xdiff + b3 * ydiff + b4 * xdiff * ydiff;

    
    return (out);

  }

  






 

  static __inline q31_t arm_bilinear_interp_q31(
						arm_bilinear_interp_instance_q31 * S,
						q31_t X,
						q31_t Y)
  {
    q31_t out;                                    
    q31_t acc = 0;                                
    q31_t xfract, yfract;                         
    q31_t x1, x2, y1, y2;                         
    int32_t rI, cI;                              
    q31_t *pYData = S->pData;                     
    uint32_t nCols = S->numCols;                  


     
     
     
    rI = ((X & 0xFFF00000) >> 20u);

     
     
     
    cI = ((Y & 0xFFF00000) >> 20u);

	 
	 
	if(rI < 0 || rI > (S->numRows-1) || cI < 0  || cI > ( S->numCols-1))
	{
		return(0);
	}

     
     
    xfract = (X & 0x000FFFFF) << 11u;

     
    x1 = pYData[(rI) + nCols * (cI)];
    x2 = pYData[(rI) + nCols * (cI) + 1u];

     
     
    yfract = (Y & 0x000FFFFF) << 11u;

     
    y1 = pYData[(rI) + nCols * (cI + 1)];
    y2 = pYData[(rI) + nCols * (cI + 1) + 1u];

     
    out = ((q31_t) (((q63_t) x1 * (0x7FFFFFFF - xfract)) >> 32));
    acc = ((q31_t) (((q63_t) out * (0x7FFFFFFF - yfract)) >> 32));

     
    out = ((q31_t) ((q63_t) x2 * (0x7FFFFFFF - yfract) >> 32));
    acc += ((q31_t) ((q63_t) out * (xfract) >> 32));

     
    out = ((q31_t) ((q63_t) y1 * (0x7FFFFFFF - xfract) >> 32));
    acc += ((q31_t) ((q63_t) out * (yfract) >> 32));

     
    out = ((q31_t) ((q63_t) y2 * (xfract) >> 32));
    acc += ((q31_t) ((q63_t) out * (yfract) >> 32));

     
    return (acc << 2u);

  }

  





 

  static __inline q15_t arm_bilinear_interp_q15(
						arm_bilinear_interp_instance_q15 * S,
						q31_t X,
						q31_t Y)
  {
    q63_t acc = 0;                                
    q31_t out;                                    
    q15_t x1, x2, y1, y2;                         
    q31_t xfract, yfract;                         
    int32_t rI, cI;                              
    q15_t *pYData = S->pData;                     
    uint32_t nCols = S->numCols;                  

     
     
     
    rI = ((X & 0xFFF00000) >> 20);

     
     
     
    cI = ((Y & 0xFFF00000) >> 20);

	 
	 
	if(rI < 0 || rI > (S->numRows-1) || cI < 0  || cI > ( S->numCols-1))
	{
		return(0);
	}

     
     
    xfract = (X & 0x000FFFFF);

     
    x1 = pYData[(rI) + nCols * (cI)];
    x2 = pYData[(rI) + nCols * (cI) + 1u];


     
     
    yfract = (Y & 0x000FFFFF);

     
    y1 = pYData[(rI) + nCols * (cI + 1)];
    y2 = pYData[(rI) + nCols * (cI + 1) + 1u];

     

     
     
    out = (q31_t) (((q63_t) x1 * (0xFFFFF - xfract)) >> 4u);
    acc = ((q63_t) out * (0xFFFFF - yfract));

     
    out = (q31_t) (((q63_t) x2 * (0xFFFFF - yfract)) >> 4u);
    acc += ((q63_t) out * (xfract));

     
    out = (q31_t) (((q63_t) y1 * (0xFFFFF - xfract)) >> 4u);
    acc += ((q63_t) out * (yfract));

     
    out = (q31_t) (((q63_t) y2 * (xfract)) >> 4u);
    acc += ((q63_t) out * (yfract));

     
     
    return (acc >> 36);

  }

  





 

  static __inline q7_t arm_bilinear_interp_q7(
					      arm_bilinear_interp_instance_q7 * S,
					      q31_t X,
					      q31_t Y)
  {
    q63_t acc = 0;                                
    q31_t out;                                    
    q31_t xfract, yfract;                         
    q7_t x1, x2, y1, y2;                          
    int32_t rI, cI;                              
    q7_t *pYData = S->pData;                      
    uint32_t nCols = S->numCols;                  

     
     
     
    rI = ((X & 0xFFF00000) >> 20);

     
     
     
    cI = ((Y & 0xFFF00000) >> 20);

	 
	 
	if(rI < 0 || rI > (S->numRows-1) || cI < 0  || cI > ( S->numCols-1))
	{
		return(0);
	}

     
     
    xfract = (X & 0x000FFFFF);

     
    x1 = pYData[(rI) + nCols * (cI)];
    x2 = pYData[(rI) + nCols * (cI) + 1u];


     
     
    yfract = (Y & 0x000FFFFF);

     
    y1 = pYData[(rI) + nCols * (cI + 1)];
    y2 = pYData[(rI) + nCols * (cI + 1) + 1u];

     
    out = ((x1 * (0xFFFFF - xfract)));
    acc = (((q63_t) out * (0xFFFFF - yfract)));

     
    out = ((x2 * (0xFFFFF - yfract)));
    acc += (((q63_t) out * (xfract)));

     
    out = ((y1 * (0xFFFFF - xfract)));
    acc += (((q63_t) out * (yfract)));

     
    out = ((y2 * (yfract)));
    acc += (((q63_t) out * (xfract)));

     
    return (acc >> 40);

  }

  

 

















 
#line 63 "..\\..\\..\\..\\src\\cpu\\device.h"





#line 70 "..\\..\\..\\..\\src\\common\\common.h"

#line 1 "..\\..\\..\\..\\src\\common\\startup.h"



 





 





 
extern void common_startup(void);

#line 75 "..\\..\\..\\..\\src\\common\\common.h"
#line 1 "..\\..\\..\\..\\src\\cpu\\arm_cm0.h"



 












 









 


 

extern void stop (void);
extern void wait (void);
extern void write_vtor (int);
extern void enable_irq (int);
extern void disable_irq (int);
extern void set_irq_priority (int, int);

#line 75 "..\\..\\..\\..\\src\\cpu\\arm_cm0.h"


 




 


 




 


 


 


 




 


 





 


 




 


 








 


 




 


 


 


 


 





	#pragma diag_suppress 175





 











 
#line 186 "..\\..\\..\\..\\src\\cpu\\arm_cm0.h"
 










 
#line 204 "..\\..\\..\\..\\src\\cpu\\arm_cm0.h"

 










 


 










 





 










 





 












 


static uint32_t volatile * const SHPR_REG_PTR[] = {&((((SCB_MemMapPtr)0xE000E000u))->SHPR2), &((((SCB_MemMapPtr)0xE000E000u))->SHPR3)};


 







 






 






 






 



 



	#pragma diag_suppress 111











 

 


 
typedef struct { uint32 CSR, RVR, CVR; } tSYSTICK;

  

 
#line 339 "..\\..\\..\\..\\src\\cpu\\arm_cm0.h"

  

 
#line 350 "..\\..\\..\\..\\src\\cpu\\arm_cm0.h"

  







 
#line 367 "..\\..\\..\\..\\src\\cpu\\arm_cm0.h"
 




 

 
 
typedef void (*SYSTICK_CALLBACK)(void);
 




 

 
 




 


 


 


 








 


 








 


 




 
extern void SYSTICK_Init(tSYSTICK cfg, SYSTICK_CALLBACK pCallback);
 
 



 
extern int main(void);

 


#line 76 "..\\..\\..\\..\\src\\common\\common.h"
#line 1 "..\\..\\..\\..\\src\\cpu\\arch_delay.h"



 








 





 
extern void arch_delay(long ticks);




#line 77 "..\\..\\..\\..\\src\\common\\common.h"

#line 15 "..\\..\\..\\..\\src\\drivers\\dac\\dac.c"
#line 1 "..\\..\\..\\..\\src\\drivers\\dac\\dac.h"



 








 

 





 
 





 
typedef struct { uint8 SR, C0, C1, C2; } tDAC;




 

 
  


 
#line 52 "..\\..\\..\\..\\src\\drivers\\dac\\dac.h"

  





 
#line 71 "..\\..\\..\\..\\src\\drivers\\dac\\dac.h"

  





 
#line 90 "..\\..\\..\\..\\src\\drivers\\dac\\dac.h"

  





 
#line 109 "..\\..\\..\\..\\src\\drivers\\dac\\dac.h"

  





 
#line 128 "..\\..\\..\\..\\src\\drivers\\dac\\dac.h"

  







 
#line 149 "..\\..\\..\\..\\src\\drivers\\dac\\dac.h"

  








 
#line 171 "..\\..\\..\\..\\src\\drivers\\dac\\dac.h"

  








 
#line 193 "..\\..\\..\\..\\src\\drivers\\dac\\dac.h"

  








 
#line 215 "..\\..\\..\\..\\src\\drivers\\dac\\dac.h"

  








 
#line 237 "..\\..\\..\\..\\src\\drivers\\dac\\dac.h"
                                         
  








 
#line 259 "..\\..\\..\\..\\src\\drivers\\dac\\dac.h"

 




 

 
 
typedef enum 
{
    DAC_TOP_CALLBACK=1,         
    DAC_BOTTOM_CALLBACK=2,      
} DAC_CALLBACK_TYPE;

 
typedef void (*DAC_CALLBACK)(DAC_CALLBACK_TYPE type);
 




 

 

 




 



 




 






 





 



 



 



 



 




 




 




 




 



 



 




 




 




 




 



 



 



 



 



 




 












 




 


 









 

 



     
extern void DAC0_Init (tDAC dac, uint16 data, uint8 ip, DAC_CALLBACK pCallback);

#line 16 "..\\..\\..\\..\\src\\drivers\\dac\\dac.c"



 
static DAC_CALLBACK volatile pCallbackDAC0=0;



 
void dac0_isr (void);



 



	#pragma diag_suppress 82

void DAC0_Init (tDAC dac, uint16 data, uint8 ip, DAC_CALLBACK pCallback)
{
  if (pCallback != 0) 
  {
    pCallbackDAC0 = pCallback;
    { ((((NVIC_MemMapPtr)0xE000E100u))->ICPR) |= (uint32)(1 << ((INT_DAC0)-16)); ((((NVIC_MemMapPtr)0xE000E100u))->ISER) |= (uint32)(1 << ((INT_DAC0)-16)); ((((NVIC_MemMapPtr)0xE000E100u))->IP[(uint16)(((INT_DAC0)-16)>>2)]) |= (uint32)((uint32)(ip)<<(uint16)(((((INT_DAC0)-16)%4)<<3)+6)); };
  } 
  ((((DAC_MemMapPtr)0x4003F000u))->DAT[0]. DATL)    = (uint8)(0x00FF&data);
  ((((DAC_MemMapPtr)0x4003F000u))->DAT[0]. DATH)    = (uint8)(0x000F&(data>>8));
  ((((DAC_MemMapPtr)0x4003F000u))->DAT[1]. DATL)    = (uint8)data;
  ((((DAC_MemMapPtr)0x4003F000u))->DAT[1]. DATH)    = (uint8)data;
  ((((DAC_MemMapPtr)0x4003F000u))->SR)       = dac.SR;
  ((((DAC_MemMapPtr)0x4003F000u))->C0)       = dac.C0;
  ((((DAC_MemMapPtr)0x4003F000u))->C1)       = dac.C1;
  ((((DAC_MemMapPtr)0x4003F000u))->C2)       = dac.C2;
}



 
void dac0_isr (void) 
{
  if (pCallbackDAC0 != (DAC_CALLBACK)0) 
  {
       
    if ((((((DAC_MemMapPtr)0x4003F000u))->SR) & 0x10u) && (((((DAC_MemMapPtr)0x4003F000u))->SR) & 0x2u))
    {
      pCallbackDAC0 (DAC_TOP_CALLBACK);
    }
       
    if ((((((DAC_MemMapPtr)0x4003F000u))->SR) & 0x8u) && (((((DAC_MemMapPtr)0x4003F000u))->SR) & 0x1u))
    {
      pCallbackDAC0 (DAC_BOTTOM_CALLBACK);
    }
  } 
}



 

