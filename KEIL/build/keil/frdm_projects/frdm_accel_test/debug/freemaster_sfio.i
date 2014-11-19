#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_sfio.c"






 














 

#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster.h"






 















 




 


 
#line 1 "..\\..\\..\\..\\src\\projects\\frdm_projects\\frdm_accel_test\\freemaster_cfg.h"






 






 







 













 





 





 







 






 













 







 







 







#line 33 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster.h"



 

typedef unsigned char* FMSTR_ADDR;    
typedef unsigned short FMSTR_SIZE;    
typedef unsigned char FMSTR_BOOL;     

 
typedef unsigned char FMSTR_APPCMD_CODE;
typedef unsigned char FMSTR_APPCMD_DATA, *FMSTR_APPCMD_PDATA;
typedef unsigned char FMSTR_APPCMD_RESULT;

 
typedef FMSTR_APPCMD_RESULT (*FMSTR_PAPPCMDFUNC)(FMSTR_APPCMD_CODE,FMSTR_APPCMD_PDATA,FMSTR_SIZE);



 

#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"






 









 




#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster.h"






 















 

#line 96 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster.h"

#line 23 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"
#line 24 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"



 

 


 
#line 40 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"

 
typedef FMSTR_SIZE FMSTR_TSA_TINDEX;
typedef FMSTR_SIZE FMSTR_TSA_TSIZE;

 
 
#line 59 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"

 
 
typedef struct
{
    union { const char*  p; FMSTR_ADDR n; } name;
    union { const char*  p; FMSTR_ADDR n; } type;
    union { const void* p; FMSTR_ADDR n; } addr;
    union { const void* p; FMSTR_ADDR n; } info;
} FMSTR_TSA_ENTRY;

 
#line 79 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"

 
 









 





    


    
















 
 
 
 

#line 136 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_tsa.h"

 


 



 
 



        





        





 

 
const FMSTR_TSA_ENTRY* FMSTR_TsaGetTable(FMSTR_TSA_TINDEX nTableIndex, FMSTR_TSA_TSIZE* pTableSize);



#line 55 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster.h"



 

 




 







 

 
FMSTR_BOOL FMSTR_Init(void);     
void FMSTR_Poll(void);     

void FMSTR_Isr(void);      
void FMSTR_Isr2(void);     

 
void FMSTR_Recorder(void);
void FMSTR_TriggerRec(void);
void FMSTR_SetUpRecBuff(FMSTR_ADDR nBuffAddr, FMSTR_SIZE nBuffSize);

 
FMSTR_APPCMD_CODE  FMSTR_GetAppCmd(void);
FMSTR_APPCMD_PDATA FMSTR_GetAppCmdData(FMSTR_SIZE* pDataLen);
FMSTR_BOOL         FMSTR_RegisterAppCmdCall(FMSTR_APPCMD_CODE nAppCmdCode, FMSTR_PAPPCMDFUNC pCallbackFunc);

void FMSTR_AppCmdAck(FMSTR_APPCMD_RESULT nResultCode);
void FMSTR_AppCmdSetResponseData(FMSTR_ADDR nResultDataAddr, FMSTR_SIZE nResultDataLen);



#line 25 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_sfio.c"
#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"






 









 









#line 28 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"










 



 
 

#line 53 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 62 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 71 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 80 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 89 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 98 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 107 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 116 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 125 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 134 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"






 









 






 
#line 31 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"
	#pragma diag_suppress 174
	#pragma diag_suppress 177
	#pragma diag_suppress 174
	#pragma diag_suppress 550




 

 




 




 








 

#line 69 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"



 

typedef unsigned char  FMSTR_U8;          
typedef unsigned short FMSTR_U16;         
typedef unsigned long  FMSTR_U32;         

typedef signed char    FMSTR_S8;          
typedef signed short   FMSTR_S16;         
typedef signed long    FMSTR_S32;         





typedef unsigned char  FMSTR_FLAGS;       
typedef unsigned char  FMSTR_SIZE8;       
typedef signed short   FMSTR_INDEX;       

typedef unsigned char  FMSTR_BCHR;        
typedef unsigned char* FMSTR_BPTR;        

typedef unsigned char  FMSTR_SCISR;       



 

void FMSTR_CopyMemory(FMSTR_ADDR nDestAddr, FMSTR_ADDR nSrcAddr, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_CopyToBuffer(FMSTR_BPTR pDestBuff, FMSTR_ADDR nSrcAddr, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_CopyFromBuffer(FMSTR_ADDR nDestAddr, FMSTR_BPTR pSrcBuff, FMSTR_SIZE8 nSize);
void FMSTR_CopyFromBufferWithMask(FMSTR_ADDR nDestAddr, FMSTR_BPTR pSrcBuff, FMSTR_SIZE8 nSize);

 

void FMSTR_SetExAddr(FMSTR_BOOL bNextAddrIsEx);






FMSTR_BPTR FMSTR_ValueFromBuffer16(FMSTR_U16* pDest, FMSTR_BPTR pSrc);
FMSTR_BPTR FMSTR_ValueFromBuffer32(FMSTR_U32* pDest, FMSTR_BPTR pSrc);
FMSTR_BPTR FMSTR_ValueToBuffer16(FMSTR_BPTR pDest, FMSTR_U16 src);
FMSTR_BPTR FMSTR_ValueToBuffer32(FMSTR_BPTR pDest, FMSTR_U32 src);




 




#line 133 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"




#line 144 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"








 
#line 168 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"
    FMSTR_BPTR FMSTR_AddressFromBuffer(FMSTR_ADDR* pAddr, FMSTR_BPTR pSrc);
    FMSTR_BPTR FMSTR_AddressToBuffer(FMSTR_BPTR pDest, FMSTR_ADDR nAddr);


#line 178 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"







 

 





 

 




 

#line 216 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"



 

 
#line 230 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 
#line 248 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 
#line 261 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"



 

 



 





 



 



 


 


 


 




 

 








 
#line 317 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 
#line 332 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 





 


 
#line 355 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 
#line 363 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 




 


 





 
#line 386 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 
#line 394 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 



 
typedef struct
{
    FMSTR_U8 nDataIx;
} FMSTR_FCAN_TCTX;

 




 






 





 





 


 



 
typedef struct
{
    FMSTR_U8 nDataIx;
} FMSTR_FCAN_RCTX;

 



 
#line 453 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_Kxx.h"

 



 




 





#line 138 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"












 







 











 

#line 178 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"







 


 




 





 

void FMSTR_InitSerial(void);
FMSTR_BOOL FMSTR_InitMQX(void);
void FMSTR_SendResponse(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nLength);
void FMSTR_ProcessSCI(void);
void FMSTR_ProcessJTAG(void);

FMSTR_BOOL FMSTR_ProtocolDecoder(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetBoardInfo(FMSTR_BPTR pMessageIO);

FMSTR_BPTR FMSTR_ReadMem(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_ReadVar(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_WriteMem(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_WriteVar(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_WriteVarMask(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_WriteMemMask(FMSTR_BPTR pMessageIO);

void FMSTR_InitAppCmds(void);
FMSTR_BPTR FMSTR_StoreAppCmd(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetAppCmdStatus(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetAppCmdRespData(FMSTR_BPTR pMessageIO);

void FMSTR_InitScope(void);
FMSTR_BPTR FMSTR_SetUpScope(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_ReadScope(FMSTR_BPTR pMessageIO);

void FMSTR_InitRec(void);
FMSTR_BPTR FMSTR_SetUpRec(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_StartRec(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_StopRec(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetRecStatus(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetRecBuff(FMSTR_BPTR pMessageIO);
FMSTR_BOOL FMSTR_IsInRecBuffer(FMSTR_ADDR nAddr, FMSTR_SIZE8 nSize);
FMSTR_SIZE FMSTR_GetRecBuffSize(void);

void FMSTR_InitTsa(void);
FMSTR_BPTR FMSTR_GetTsaInfo(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetStringLen(FMSTR_BPTR pMessageIO);
FMSTR_BOOL FMSTR_CheckTsaSpace(FMSTR_ADDR nAddr, FMSTR_SIZE8 nSize, FMSTR_BOOL bWriteAccess);
FMSTR_U16  FMSTR_StrLen(FMSTR_ADDR nAddr);

void FMSTR_InitSfio(void);
FMSTR_BPTR FMSTR_SfioFrame(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_SfioGetResp(FMSTR_BPTR pMessageIO);

void FMSTR_InitPipes(void);
FMSTR_BPTR FMSTR_PipeFrame(FMSTR_BPTR pMessageIO);

void FMSTR_InitCan(void);
void FMSTR_SetCanCmdID(FMSTR_U32 canID);
void FMSTR_SetCanRespID(FMSTR_U32 canID);
FMSTR_BOOL FMSTR_TxCan(void);
FMSTR_BOOL FMSTR_RxCan(void);
void FMSTR_ProcessCanRx(void);
void FMSTR_ProcessCanTx(void);



 









 

 






 
#line 287 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 295 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 311 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 
 












#line 333 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"





 
#line 346 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 




 
 








    






 
#line 439 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 
#line 471 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

#line 481 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 
#line 492 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 
#line 503 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 








 






 




















 




 




 




 




 




 




    
     



    
     









 






 












 














 




 
#line 642 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 




 




 




#line 695 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 


         
#line 706 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 
#line 715 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"

 




 
#line 759 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"
     



     





     





     





     





     
#line 794 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"
    
     
#line 802 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_private.h"
    




#line 26 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_sfio.c"
#line 1 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"






 









 






 
  
#line 42 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"



 
  
 
#line 59 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"

 






 
#line 75 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"

 





 

 



  
 




 
#line 110 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"



 







 


 






 

 
#line 140 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_protocol.h"

 






#line 27 "..\\..\\..\\..\\src\\utilities\\freemaster\\freemaster_sfio.c"

